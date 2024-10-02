#pragma once

#include <tuple>

#include <ql/core/type/container/subtype.hpp>
#include <ql/core/type/compare/compare.hpp>
#include <ql/core/type/tuple/is-tuple.hpp>
#include <ql/core/type/tuple/size.hpp>
#include <ql/core/type/string/has-to-string.hpp>
#include <ql/core/type/functional/functional.hpp>

#include <ql/core/advanced-type/color/print-color.hpp>

#include <ql/core/constexpr/chain.hpp>

#include <iostream>
#include <sstream>

namespace ql
{
	namespace detail
	{
		template <typename T>
		concept is_cout_printable_c = requires(const T t) { std::cout << t; };

		template <typename T>
		constexpr auto is_cout_printable = is_cout_printable_c<T>;

		template <typename T>
		concept is_wcout_printable_c = requires(const T t) { std::wcout << t; };

		template <typename T>
		constexpr auto is_wcout_printable = is_wcout_printable_c<T>;

		template <typename T>
		concept is_u32_printable_c = requires(const T t, std::basic_ostringstream<char32_t> stream) { stream << t; };

		template <typename T>
		concept is_any_printable_c = is_cout_printable_c<T> || is_wcout_printable_c<T> || is_u32_printable_c<T>;

		template <typename T>
		constexpr bool is_any_printable()
		{
			return is_any_printable_c<T>;
		}
	}	 // namespace detail

	template <typename... Args>
	constexpr bool is_printable()
	{
		return ql::recursive_type_check<std::tuple<Args...>>(
				[]<typename T>()
				{ return ql::has_to_string<T>() || ql::detail::is_any_printable<T>() || ql::is_same_decayed<T, ql::print_color>(); }
		);
	}
}	 // namespace ql