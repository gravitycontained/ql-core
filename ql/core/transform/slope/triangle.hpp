#pragma once

namespace ql
{
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
}