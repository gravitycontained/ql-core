#pragma once

#include <ql/core/type/type.hpp>

#include <ql/core/container/container.hpp>

#include <algorithm>

namespace ql
{
	template <typename C, typename F>
	requires (ql::is_container<C>() && ql::is_sortable<C>())
	constexpr void sort(C& container, F compare)
	{
		if constexpr (ql::is_sorted_container<C>())
		{
			return;
		}
		else
		{
			std::sort(ql::begin(container), ql::end(container), compare);
		}
	}
}	 // namespace ql