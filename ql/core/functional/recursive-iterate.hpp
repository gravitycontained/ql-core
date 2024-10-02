#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{

	struct iterate_info
	{
		bool first;
		bool last;
		ql::size depth;
	};

	namespace detail
	{
		template <typename F, typename... Args>
		requires (ql::is_callable<F>())
		constexpr void recursive_value_apply(F&& function, ql::size depth, bool first, bool last, Args&&... args)
		{
			auto apply = [&]<typename T>(T&& value)
			{
				if constexpr (ql::is_container<T>() && !ql::is_long_string_type<T>())
				{
					bool first = true;

					ql::size index = 0;
					for (auto& i : std::forward<T>(value))
					{
						auto last = index == std::forward<T>(value).size() - 1;

						ql::detail::recursive_value_apply(std::forward<F>(function), depth + 1, first, last, i);

						first = false;
						++index;
					}
				}
				else if constexpr (ql::is_tuple<T>())
				{
					auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
					{
						((ql::detail::recursive_value_apply(
								 std::forward<F>(function), depth + 1, Ints == 0, Ints == ql::tuple_size<T>() - 1,
								 ql::tuple_value<Ints>(std::forward<T>(value))
						 )),
						 ...);
					};
					unpack(std::make_index_sequence<ql::tuple_size<T>()>());
				}
				else if constexpr (ql::is_pair<T>())
				{
					ql::detail::recursive_value_apply(std::forward<F>(function), depth + 1, true, false, std::forward<T>(value).first);
					ql::detail::recursive_value_apply(std::forward<F>(function), depth + 1, false, true, std::forward<T>(value).second);
				}
				else
				{
					std::forward<F>(function)(std::forward<T>(value), ql::iterate_info{first, last, depth});
				}
			};

			(apply(std::forward<Args>(args)), ...);
		}
	}	 // namespace detail

	template <typename F, typename... Args>
	requires (ql::is_callable<F>())
	constexpr void recursive_value_apply(F&& function, Args&&... args)
	{
		ql::detail::recursive_value_apply(std::forward<F>(function), 0, true, true, std::forward<Args>(args)...);
	}
}	 // namespace ql