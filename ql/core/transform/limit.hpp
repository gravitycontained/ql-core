#pragma once

#include <ql/core/type/arithmetic/is-arithmetic.hpp>

namespace ql
{
	template <typename T>
	constexpr T min(T a, T b)
	{
		return (a < b ? a : b);
	}

	template <typename T, typename... Args>
	constexpr T min(T a, T b, Args... rest)
	{
		return ql::min(ql::min(a, b), rest...);
	}

	template <typename T>
	constexpr T max(T a, T b)
	{
		return (a > b ? a : b);
	}

	template <typename T, typename... Args>
	constexpr T max(T a, T b, Args... rest)
	{
		return ql::max(ql::max(a, b), rest...);
	}

	template <typename T>
	constexpr T clamp(T value, T min = T{0}, T max = T{1})
	{
		return ql::min(max, ql::max(min, value));
	}

	template <typename T>
	constexpr T abs(T n)
	{
		if constexpr (ql::is_signed<T>())
		{
			return (n < T{} ? -n : n);
		}
		else
		{
			return n;
		}
	}
}	 // namespace ql