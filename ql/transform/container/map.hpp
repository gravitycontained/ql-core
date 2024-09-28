#pragma once

#include <ql/type/type.hpp>

namespace ql
{
	template <typename C, typename F>
	requires (ql::is_container<C>() && std::is_invocable_v < F,
						ql::reference<ql::container_subtype<C>>> && ql::return_size<F>() == 0)
	constexpr void map(C& container, F&& func)
	{
		for (auto& i : container)
		{
			std::forward<F>(func)(i);
		}
	}

	template <typename C, typename F>
	requires (ql::is_container<C>() && std::is_invocable_v<F, ql::container_subtype<C>> && ql::return_size<F>() == 1)
	constexpr auto map(C container, F&& func)
	{
		for (auto& i : container)
		{
			i = std::forward<F>(func)(i);
		}
		return container;
	}

}	 // namespace ql

template <typename C, typename F>
requires (ql::is_container<C>() && std::is_invocable_v<F, ql::reference<ql::container_subtype<C>>> &&
					ql::return_size<F>() == 0)
constexpr void operator>>(C& container, F&& func)
{
	ql::map(container, std::forward<F>(func));
}

template <typename C, typename F>
requires (ql::is_container<C>() && std::is_invocable_v<F, ql::container_subtype<C>> && ql::return_size<F>() == 1)
constexpr C operator>>(C container, F&& func)
{
	return ql::map(container, std::forward<F>(func));
}
