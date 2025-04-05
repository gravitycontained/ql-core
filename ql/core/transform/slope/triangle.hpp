#pragma once

namespace ql
{
	template <typename F>
	constexpr F triangle_progression(F progress)
	{
		if (progress < F{ 0.5 })
		{
			return progress * 2;
		}
		else
		{
			return (1 - (progress - F{ 0.5 }) * 2);
		}
	}
}