#pragma once

#include <ql/core/type/string/subtype.hpp>
#include <ql/core/type/declval.hpp>

namespace ql
{
	namespace detail
	{
		// basic_string_view signature
		template <typename T>
		constexpr auto string_view_signature(std::basic_string_view<T>)
		{
			return std::true_type{};
		}

		template <typename T>
		constexpr auto string_view_signature(T)
		{
			return std::false_type{};
		}

	}	 // namespace detail

	template <typename T>
	constexpr bool is_string_view()
	{
		return decltype(ql::detail::string_view_signature(ql::declval<T>())){};
	}

	template <typename T>
	requires (ql::is_string_type<T>() && !ql::is_string_view<T>())
	using string_view = typename std::basic_string_view<ql::string_underlying_type<T>>;

	// string_view to basic_string type
	template <typename T>
	requires (ql::is_string_view<T>())
	using string_view_to_basic_string = typename std::basic_string<ql::string_underlying_type<T>>;

}	 // namespace ql