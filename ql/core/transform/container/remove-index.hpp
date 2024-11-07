#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename C, typename I>
	requires (ql::is_container<C>() && ql::has_push_back<C>() && ql::has_reserve<C>() && ql::is_integer<I>())
	constexpr C removed_index(const C& container, I index)
	{
		C result;
		if (container.empty())
		{
			return result;
		}

		result.reserve(container.size() - 1);
		for (ql::size i = 0u; i < container.size(); ++i)
		{
			if (i != index)
			{
				result.push_back(container[i]);
			}
		}
		return result;
	}

	template <typename C, typename I>
	requires (ql::is_container<C>() && ql::has_push_back<C>() && ql::has_reserve<C>() && ql::is_integer<I>())
	constexpr void remove_index(C& container, I index)
	{
		if (index < I{0} || index >= container.size())
		{
			return;
		}
		container = removed_index(container, index);
	}
}	 // namespace ql