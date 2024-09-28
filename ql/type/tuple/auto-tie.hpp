#pragma once

#include <tuple>
#include <functional>

#include <ql/definition/definition.hpp>
#include <ql/type/tuple/type.hpp>
#include <ql/type/variadic/size.hpp>

namespace ql
{
	template <typename T>
	constexpr auto reference_if_lvalue(auto&& value)
	{
		if constexpr(std::is_lvalue_reference_v<T>)
			return std::ref(value);
		else
			return std::forward<T>(value);
	}

	template <typename... Args>
	constexpr auto auto_tie(Args&&... values)
	{
		auto&& tupleRef = std::forward_as_tuple(std::forward<Args>(values)...);
		using tuple = std::tuple<Args...>;

		constexpr auto size = ql::variadic_size<Args...>();
		auto unpack = [&]<ql::size... i>(std::index_sequence<i...>)
		{
			return std::make_tuple(reference_if_lvalue<ql::tuple_type<i, tuple>>(
					std::get<i>(tupleRef))...);
		};
		return unpack(std::make_index_sequence<size>());
	}
}