#pragma once

#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename C, typename F>
	requires (ql::is_container<C>() && ql::is_invocable_with<F, ql::container_subtype<C>>() && ql::return_size<F>() == 1 &&
						ql::is_same<ql::return_type<F>, bool>())
	constexpr auto filter(C container, F&& func)
	{
		C result;
		for (auto& i : container)
		{
			if (std::forward<F>(func)(i))
			{
				result.push_back(i);
			}
		}
		return result;
	}

}	 // namespace ql

template <typename C, typename F>
requires (ql::is_container<C>() && ql::is_invocable_with<F, ql::container_subtype<C>>() && ql::return_size<F>() == 1 &&
					ql::is_same<ql::return_type<F>, bool>())
constexpr void operator<<(C container, F&& func)
{
	return ql::filter(container, std::forward<F>(func));
}
