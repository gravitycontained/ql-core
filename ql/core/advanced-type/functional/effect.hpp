#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename... Args>
	constexpr auto are_signals()
	{
		return ql::all_true(ql::constexpr_apply<ql::variadic_size<Args...>() - 1>(
				[&](auto i) { return ql::is_signal<ql::variadic_type<i, Args...>>(); }
		));
	}

	template <typename... Args>
	constexpr void effect(Args&&... objects)
	requires (
			are_signals<Args...>() && ql::is_callable<ql::variadic_type_back<Args...>>()

			/*
			* use this when the active error is no longer hallucinated:

			*/
	)
	{
		auto&& function = ql::variadic_value_back(std::forward<Args>(objects)...);

		constexpr auto size = ql::variadic_size<Args...>();
		ql::constexpr_iterate<size - 1>([&](auto i)
																		{ ql::tuple_value<i>(ql::auto_tie(std::forward<Args>(objects)...)).addListener(function); });
	}
}	 // namespace ql
