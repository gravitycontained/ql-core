#pragma once

#include <ql/core/type/container/subtype.hpp>
#include <ql/core/type/container/is-container.hpp>

#include <ql/core/type/declval.hpp>
#include <ql/core/type/conditional.hpp>
#include <ql/core/type/string/type.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T>
		requires (ql::is_string_type<T>())
		constexpr auto string_underlying_type(T value)
		{
			if constexpr (ql::is_container<T>())
			{
				return ql::declval<ql::container_subtype<T>>();
			}
			else
			{
				return ql::declval<ql::full_decay<T>>();
			}
		}
	}	 // namespace detail

	template <typename T>
	requires (ql::is_string_type<T>())
	using string_underlying_type = decltype(ql::detail::string_underlying_type(ql::declval<T>()));

	template <typename T>
	requires (ql::is_string_type<T>())
	using string_type = typename std::basic_string<ql::string_underlying_type<T>>;
}	 // namespace ql