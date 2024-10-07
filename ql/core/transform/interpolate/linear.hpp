#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

#include <span>

namespace ql
{
	template <typename T, typename F>
	// requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto linear_interpolation(T a, T b, F delta)
	{
		return static_cast<T>(a * (F{1} - delta) + (b * delta));
	}

	template <typename T, typename F>
	// requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto linear_interpolation_2D(T xx, T xy, T yx, T yy, F fx, F fy)
	{
		return ql::linear_interpolation(ql::linear_interpolation(xx, xy, fx), ql::linear_interpolation(yx, yy, fx), fy);
	}

	template <typename T>
	std::vector<std::decay_t<T>>
	linear_container_interpolation(std::span<T> data, ql::size interpolations, ql::size index_skip_size = 1u)
	{
		if (data.empty())
		{
			return {};
		}
		if (data.size() == 1u)
		{
			return std::vector<std::decay_t<T>>{data[0]};
		}

		std::vector<std::decay_t<T>> result(ql::size_cast(data.size() / index_skip_size * interpolations));
		if (result.size() == data.size())
		{
			for (ql::u32 i = 0; i < result.size(); ++i)
			{
				result[i] = data[i];
			}
			return result;
		}

		std::decay_t<T> a, b;

		for (ql::u32 i = 0u; i < result.size(); ++i)
		{
			auto f = i / ql::f64_cast(result.size() - 1);

			auto index = ql::u32_cast(f * (data.size() / index_skip_size - 1));

			a = b = data[index * index_skip_size];

			if ((index * index_skip_size) + 1 < data.size())
			{
				b = data[(index * index_skip_size) + 1];
			}

			auto left_over = ((data.size() / index_skip_size - 1) * f) - index;

			result[i] = ql::linear_interpolation(a, b, left_over);
		}

		return result;
	}

}	 // namespace ql