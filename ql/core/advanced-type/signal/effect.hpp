#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename... Args>
	constexpr auto are_signals()
	{
		return ql::all_tuple_true(ql::constexpr_apply<ql::variadic_size<Args...>() - 1>(
				[&](auto i) { return ql::is_signal<ql::variadic_type<i, Args...>>(); }
		));
	}

	template <typename... Args>
	requires (ql::are_signals<Args...>() && ql::is_callable<ql::variadic_type_back<Args...>>())
	constexpr void effect(Args&&... objects)
	{
		auto&& tied = ql::auto_tie(std::forward<Args>(objects)...);
		auto&& function = ql::tuple_value_back(tied);

		constexpr auto size = ql::variadic_size<Args...>();
		ql::constexpr_iterate<size - 1>([&](auto i)
		{
			ql::tuple_value<i>(tied).addListener(function);
		});
	}
}	 // namespace ql
