#pragma once

#include <tuple>
#include <ql/core/type/declval.hpp>

namespace ql
{
	namespace detail
	{
		template <typename... Ts>
		constexpr auto tuple_signature(std::tuple<Ts...>)
		{
			return std::true_type{};
		}

		template <typename T>
		constexpr auto tuple_signature(T)
		{
			return std::false_type{};
		}

		template <typename... Ts>
		constexpr auto pair_signature(std::pair<Ts...>)
		{
			return std::true_type{};
		}

		template <typename T>
		constexpr auto pair_signature(T)
		{
			return std::false_type{};
		}
	}	 // namespace detail

	template <typename T>
	constexpr bool is_pair()
	{
		return decltype(ql::detail::pair_signature(ql::declval<T>())){};
	}

	template <typename T>
	constexpr bool is_tuple()
	{
		return ql::is_pair<T>() || decltype(ql::detail::tuple_signature(ql::declval<T>())){};
	}

}	 // namespace ql