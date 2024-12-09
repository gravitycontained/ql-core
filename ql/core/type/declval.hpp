#pragma once

#include <type_traits>
#include <functional>

namespace ql
{
	template <typename T>
	constexpr auto declval()
	{
		using pointer = std::decay_t<T>*;
		return *(pointer{});
	}

	template <typename T>
	constexpr T declval_fully_qualified()
	{
		using pointer = std::decay_t<T>*;
		return *(pointer{});
	}
}	 // namespace ql