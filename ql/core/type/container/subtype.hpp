#pragma once

#include <ql/core/type/container/is-container.hpp>
#include <ql/core/type/string/type.hpp>
#include <ql/core/type/declval.hpp>

#include <vector>

namespace ql
{
	template <typename C>
	requires (ql::is_container<C>())
	using container_subtype = typename std::iterator_traits<decltype(std::declval<C>().begin())>::value_type;

	namespace detail
	{
		template <typename U, template <typename, typename...> class C, typename T, typename... rest>
		auto container_change_subtype(const C<T, rest...>& c)
		{
			if constexpr (ql::is_long_string_type<T>())
			{
				return ql::declval<C<U>>();
			}
			else if constexpr (ql::is_container<T>())
			{
				return ql::declval<C<decltype(container_subtype_cast<U>(T{}))>>();
			}
			else
			{
				return ql::declval<C<U>>();
			}
		}
	}	 // namespace detail

	template <typename C, typename T>
	struct container_change_subtype_t
	{
		using type = decltype(ql::detail::container_change_subtype<T>(ql::declval<C>()));
	};

	template <typename C, typename T>
	using container_change_subtype = typename container_change_subtype_t<C, T>::type;
}	 // namespace ql