
#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/constexpr/index.hpp>
#include <ql/core/functional/auto-tie.hpp>

#include <ql/core/type/functional/functional.hpp>

namespace ql
{

	template <ql::size N, typename F>
	requires (ql::is_callable<F>() && ql::return_size<F>() == 1)
	constexpr auto constexpr_apply(F&& function)
	{
		auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
		{ return ql::auto_tie(std::forward<F>(function)(ql::constexpr_index<Ints, N>{})...); };
		return unpack(std::make_index_sequence<N>());
	}

	template <ql::size N, typename F>
	requires (ql::is_callable<F>() && ql::return_size<F>() == 0)
	constexpr void constexpr_apply(F&& function)
	{
		auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
		{ (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}), ...);
		};
		unpack(std::make_index_sequence<N>());
	}
}	 // namespace ql