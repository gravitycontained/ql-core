#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{
	namespace detail
	{
		template <typename F, typename... Args>
		requires (ql::is_callable<F>())
		constexpr void recursive_value_iterate(F&& function, Args&&... args)
		{
			auto apply = [&]<typename T>(T&& value)
			{
				if constexpr (ql::is_container<T>() && !ql::is_long_string_type<T>())
				{
					for (auto& i : std::forward<T>(value))
					{
						ql::detail::recursive_value_iterate(std::forward<F>(function), i);
					}
				}
				else if constexpr (ql::is_tuple<T>())
				{
					ql::constexpr_iterate<ql::tuple_size<T>()>(
							[&](auto index)
							{
								auto&& i = ql::tuple_value<index>(std::forward<T>(value));
								ql::detail::recursive_value_iterate(std::forward<F>(function), i);
							}
					);
				}
				else
				{
					std::forward<F>(function)(std::forward<T>(value));
				}
			};

			(apply(std::forward<Args>(args)), ...);
		}
	}	 // namespace detail

	/*
	example:

	constexpr auto tuple = ql::to_tuple(1, std::array{5, 6, 7}, 3, ql::to_tuple(4, 5, "test"), std::make_pair(4, "ok"));

	ql::recursive_value_iterate(
			[](auto value)
			{ ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ", value: ", value); },
			tuple
	);
	*/
	template <typename F, typename... Args>
	requires (ql::is_callable<F>())
	constexpr void recursive_value_iterate(F&& function, Args&&... args)
	{
		ql::detail::recursive_value_iterate(std::forward<F>(function), std::forward<Args>(args)...);
	}
}	 // namespace ql