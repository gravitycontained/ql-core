#pragma once

#include <tuple>

#include <ql/type-traits/container/subtype.hpp>
#include <ql/type-traits/compare/compare.hpp>
#include <ql/type-traits/tuple/is-tuple.hpp>
#include <ql/type-traits/string/has-to-string.hpp>

#include <ql/constexpr/chain.hpp>

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
		concept is_std_printable_c = is_cout_printable_c<T> || is_wcout_printable_c<T> || is_u32_printable_c<T>;

		template <typename T>
		constexpr bool is_std_printable()
		{
			return is_std_printable_c<T>;
		}

		template <typename T>
		constexpr bool is_printable()
		{
			if constexpr (ql::has_to_string<T>())
			{
				return true;
			}
			else if constexpr (ql::is_container<T>())
			{
				return ql::detail::is_printable<ql::container_subtype<T>>();
			}
			else if constexpr (ql::is_tuple<T>())
			{
				constexpr auto size = ql::tuple_size<T>();
				return ql::constexpr_and_chain<size>([&](auto i) { return ql::detail::is_printable<ql::tuple_type<i, T>>(); });
			}
			else if constexpr (ql::is_pair<T>())
			{
				auto check = [&]<typename... Ts>(std::pair<Ts...>)
				{
					constexpr auto b = (ql::detail::is_printable<Ts>() && ...);
					if constexpr (b)
					{
						return std::true_type{};
					}
					else
					{
						return std::false_type{};
					}
				};
				return decltype(check(ql::declval<T>()))::value;
			}
			else
			{
				return (static_cast<bool>(ql::detail::is_std_printable_c<T>));
			}
		}
	}	 // namespace detail

	template <typename... Args>
	constexpr bool is_printable()
	{
		return ((ql::detail::is_printable<Args>()) && ...);
	}
}	 // namespace ql