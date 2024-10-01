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
		template <typename T, typename F>
		requires (ql::is_callable<F>())
		constexpr void apply_iterate(T&& value, F&& function, ql::size depth = 0, bool first = true, bool last = false)
		{
			if constexpr (ql::is_container<T>() && !ql::is_long_string_type<T>())
			{
				bool first = true;

				ql::size index = 0;
				for (auto& i : value)
				{
					auto last = index == value.size() - 1;

					ql::detail::apply_iterate(i, std::forward<F>(function), depth + 1, first, last);

					first = false;
					++index;
				}
			}
			else if constexpr (ql::is_tuple<T>())
			{
				auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
				{
					((ql::detail::apply_iterate(
							 std::get<Ints>(value), std::forward<F>(function), depth + 1, Ints == 0, Ints == ql::tuple_size<T>() - 1
					 )),
					 ...);
				};
				unpack(std::make_index_sequence<ql::tuple_size<T>()>());
			}
			else if constexpr (ql::is_pair<T>())
			{
				ql::detail::apply_iterate(value.first, std::forward<F>(function), depth + 1, true, false);
				ql::detail::apply_iterate(value.second, std::forward<F>(function), depth + 1, false, true);
			}
			else
			{
				std::forward<F>(function)(ql::iterate_info{first, last, depth}, value);
			}
		}
	}	 // namespace detail

	template <typename T, typename F>
	requires (ql::is_callable<F>())
	constexpr void apply_iterate(T&& value, F&& function)
	{
		ql::detail::apply_iterate(std::forward<T>(value), std::forward<F>(function));
	}
}	 // namespace ql