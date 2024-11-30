#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/transform/limit.hpp>

namespace ql
{
	template <typename F>
	constexpr F slope_curve(F progress, F slope = 2.0)
	{
		return std::pow(1 - std::pow(1 - ql::clamp(progress), slope), 1.0 / slope);
	}

	template <typename F>
	constexpr F slope_double_curve(F progress, F slope = 2.0)
	{
		if (progress < F{0.5})
		{
			return ql::slope_curve(progress * 2, 1.0 / slope) / 2;
		}
		else
		{
			return (ql::slope_curve((progress - F{0.5}) * 2, slope) / 2) + F{0.5};
		}
	}

	template <typename F>
	constexpr F slope_smooth_impl(F progress, F slope, F cutoff, F sub)
	{
		auto stretch = (1 - cutoff);
		auto multiply = 1.0 / (1 - sub);
		return (ql::slope_curve(progress * stretch + cutoff, slope) - sub) * multiply;
	}

	template <typename F>
	constexpr F slope_smooth_curve_triangle(F progress, F slope)
	{
		if (progress >= 0.5)
		{
			return ql::slope_smooth_curve_triangle(1.0 - progress, slope);
		}
		return ql::slope_curve(progress * 2, slope);
	}

	template <typename F>
	constexpr F slope_smooth_curve_s(F progress, F slope)
	{
		if (progress >= 0.5)
		{
			return 1 - ql::slope_smooth_curve_s(1 - progress, slope);
		}
		return 0.5 - ql::slope_curve(1 - progress * 2.0, slope) / 2;
	}
}	 // namespace ql