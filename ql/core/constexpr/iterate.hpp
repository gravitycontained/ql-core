#pragma once

#include <utility>
#include <ql/core/definition/definition.hpp>
#include <ql/core/constexpr/index.hpp>
#include <ql/core/type/functional/functional.hpp>
#include <ql/core/type/tuple/is-tuple.hpp>

namespace ql
{
	template <ql::size N, typename F>
	constexpr void constexpr_iterate(F function)
	{
		auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
		{
			(std::forward<F>(function)(ql::constexpr_index<Ints, N>{}), ...);
		};

		unpack(std::make_index_sequence<N>());
	}

	template <typename T, typename F>
	requires (ql::is_tuple<T>() && ql::is_callable<F>())
	constexpr void tuple_iterate(T&& tuple, F function)
	{
		constexpr auto N = ql::tuple_size<T>();
		ql::constexpr_iterate<N>([&](auto i) { std::forward<F>(function)(ql::tuple_value<i>(tuple)); });
	}
}	 // namespace ql