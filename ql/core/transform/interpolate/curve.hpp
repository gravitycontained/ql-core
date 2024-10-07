#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/transform/limit.hpp>

namespace ql
{
	template <typename F>
	constexpr F curve_slope(F progress, F slope = 2.0)
	{
		return std::pow(1 - std::pow(1 - progress, slope), 1.0 / slope);
	}

	template <typename F>
	constexpr F double_curve_slope(F progress, F slope = 2.0)
	{
		if (progress < F{0.5})
		{
			return ql::curve_slope(progress * 2, 1.0 / slope) / 2;
		}
		else
		{
			return (ql::curve_slope((progress - F{0.5}) * 2, slope) / 2) + F{0.5};
		}
	}

	template <typename F>
	constexpr F smooth_slope_impl(F progress, F slope, F cutoff, F sub)
	{
		auto stretch = (1 - cutoff);
		auto multiply = 1.0 / (1 - sub);
		return (curve_slope(progress * stretch + cutoff, slope) - sub) * multiply;
	}

	template <typename F>
	constexpr F smooth_curve(F progress, F slope)
	{
		return ql::curve_slope(ql::clamp(progress), slope);
	}

	template <typename F>
	constexpr F smooth_curve_triangle(F progress, F slope)
	{
		if (progress >= 0.5)
		{
			return smooth_curve_triangle(1.0 - progress, slope);
		}
		return smooth_curve(progress * 2, slope);
	}

	template <typename F>
	constexpr F triangle_progression(F progress)
	{
		if (progress < 0.5)
		{
			return progress * 2;
		}
		else
		{
			return (1 - (progress - 0.5) * 2);
		}
	}

	template <typename F>
	constexpr F triangle_progression_fmod1(F n)
	{
		return triangle_progression(std::fmod(n, F{1}));
	}

	template <typename F>
	constexpr F smooth_curve_s(F progress, F slope)
	{
		if (progress >= 0.5)
		{
			return 1 - smooth_curve_s(1 - progress, slope);
		}
		return 0.5 - smooth_curve(1 - progress * 2.0, slope) / 2;
	}
}	 // namespace ql