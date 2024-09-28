#pragma once

#include <ql/core/type/type.hpp>

namespace ql
{

	template <typename T, typename F>
	requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto cubic_interpolation(T a, T b, T c, T d, F delta)
	{
		return (d - c - a + b) * (delta * delta * delta) + (a * 2 - b * 2 - d + c) * (delta * delta) + (c - a) * delta + b;
	}

	template <typename T, typename F>
	requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto cubic_interpolation(T a, T b, F delta)
	{
		return ql::cubic_interpolation(a, a, b, b, delta);
	}

	template <typename T, typename F>
	requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto
	cubic_interpolation_2D(T a1, T b1, T c1, T d1, T a2, T b2, T c2, T d2, T a3, T b3, T c3, T d3, T a4, T b4, T c4, T d4, F fx, F fy)
	{
		return ql::cubic_interpolation(ql::cubic_interpolation(a1, b1, c1, d1, fx), ql::cubic_interpolation(a2, b2, c2, d2, fx),
																	 ql::cubic_interpolation(a3, b3, c3, d3, fx), ql::cubic_interpolation(a4, b4, c4, d4, fx), fy);
	}

	template <typename T, typename F>
	requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto cubic_interpolation_2D(T xx, T xy, T yx, T yy, F fx, F fy)
	{
		return ql::cubic_interpolation(ql::cubic_interpolation(xx, xy, fx), ql::cubic_interpolation(yx, yy, fx), fy);
	}
}	 // namespace ql