#pragma once

#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename T, typename F>
	requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto linear_interpolation(T a, T b, F delta)
	{
		return static_cast<T>(a * (F{1} - delta) + (b * delta));
	}

	template <typename T, typename F>
	requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto linear_interpolation_2D(T xx, T xy, T yx, T yy, F fx, F fy)
	{
		return ql::linear_interpolation(ql::linear_interpolation(xx, xy, fx), ql::linear_interpolation(yx, yy, fx), fy);
	}
}