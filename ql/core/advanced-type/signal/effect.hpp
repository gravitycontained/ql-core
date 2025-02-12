#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/advanced-type/signal/connection/connection.hpp>

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

	template <typename T>
	concept has_connection = requires(T t) {
		{ t.connection } -> std::convertible_to<ql::connection>;
	};

	template <typename T, typename... Args>
	requires (ql::has_connection<T> && ql::are_signals<Args...>() && ql::is_callable<ql::variadic_type_back<Args...>>())
	void effect(T& host, Args&&... objects)
	{
		auto&& tied = ql::auto_tie(std::forward<Args>(objects)...);
		auto&& function = ql::tuple_value_back(tied);

		constexpr auto size = ql::variadic_size<Args...>();
		ql::constexpr_iterate<size - 1>([&](auto i)
		{
			ql::tuple_value<i>(tied).addListener(function);
		});

		host.connection.emplace_back(std::make_unique<ql::single_connection>(std::move(
			[tied, function]() mutable
			{
				ql::constexpr_iterate<size - 1>([&](auto i)
				{
					ql::tuple_value<i>(tied).removeListener(function);
				});
			}
		)));
	}
}	 // namespace ql
