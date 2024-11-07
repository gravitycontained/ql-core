#pragma once

#include <ql/core/definition/definition.hpp>

namespace ql
{
	template <typename T>
	constexpr auto recursive_type_flattening()
	{
		if constexpr (ql::is_container<T>())
		{
			return ql::recursive_type_flattening<ql::container_subtype<T>>();
		}
		else if constexpr (ql::is_tuple<T>())
		{
			constexpr auto size = ql::tuple_size<T>();
			return ql::constexpr_and_chain<size>([&](auto i)
																					 { return ql::recursive_type_check<ql::tuple_type<i, T>>(std::forward<F>(function)); });
		}
		else if constexpr (ql::is_pair<T>())
		{
			return ql::constexpr_and_chain<2>([&](auto i)
																				{ return ql::recursive_type_check<ql::tuple_type<i, T>>(std::forward<F>(function)); });
		}
		else
		{
			return std::forward<F>(function).template operator()<T>();
		}
	}
}	 // namespace ql