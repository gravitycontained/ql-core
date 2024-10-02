#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

#include <ql/core/transform/limit.hpp>

#include <span>
#include <type_traits>
#include <vector>
#include <tuple>

namespace ql
{

	template <typename T, typename F>
	// requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto cubic_interpolation(T a, T b, T c, T d, F delta)
	{
		return (d - c - a + b) * (delta * delta * delta) + (a * 2 - b * 2 - d + c) * (delta * delta) + (c - a) * delta + b;
	}

	template <typename T, typename F>
	// requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto cubic_interpolation(T a, T b, F delta)
	{
		return ql::cubic_interpolation(a, a, b, b, delta);
	}

	template <typename T, typename F>
	// requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto
	cubic_interpolation_2D(T a1, T b1, T c1, T d1, T a2, T b2, T c2, T d2, T a3, T b3, T c3, T d3, T a4, T b4, T c4, T d4, F fx, F fy)
	{
		return ql::cubic_interpolation(
				ql::cubic_interpolation(a1, b1, c1, d1, fx), ql::cubic_interpolation(a2, b2, c2, d2, fx),
				ql::cubic_interpolation(a3, b3, c3, d3, fx), ql::cubic_interpolation(a4, b4, c4, d4, fx), fy
		);
	}

	template <typename T, typename F>
	// requires (ql::behaves_arithmetic<T>() && ql::is_floating_point<F>())
	constexpr auto cubic_interpolation_2D(T xx, T xy, T yx, T yy, F fx, F fy)
	{
		return ql::cubic_interpolation(ql::cubic_interpolation(xx, xy, fx), ql::cubic_interpolation(yx, yy, fx), fy);
	}

	template <typename T>
	std::pair<std::decay_t<T>, std::decay_t<T>> cubic_container_interpolation_min_max(
			std::span<T> data,
			ql::size interpolations,
			ql::f64 interpolation_offset = 0.0,
			ql::size index_skip_size = 1u,
			std::decay_t<T> low = ql::type_max<T>(),
			std::decay_t<T> high = ql::type_min<T>()
	)
	{
		if (data.empty())
		{
			return std::make_pair(T{}, T{});
		}
		if (data.size() == 1u)
		{
			return std::make_pair(data[0], data[0]);
		}

		interpolation_offset = ql::clamp(interpolation_offset);

		auto index_offset = interpolation_offset * interpolations;

		std::decay_t<T> a, b, c, d;

		auto size = ql::size_cast(data.size() / index_skip_size * interpolations - index_offset);
		for (ql::u32 i = 0u; i < size; ++i)
		{
			ql::f64 f = (i + index_offset) / ql::f64_cast(size - 1);

			ql::size index = ql::size_cast(f * (data.size() / index_skip_size - 1));

			c = a = b = data[index * index_skip_size];
			if (index >= 1u)
			{
				a = data[(index - 1) * index_skip_size];
			}

			if ((index + 1) * index_skip_size < data.size())
			{
				c = data[(index + 1) * index_skip_size];
			}
			d = c;

			if ((index + 2) * index_skip_size < data.size())
			{
				d = data[(index + 2) * index_skip_size];
			}

			auto left_over = ((data.size() / index_skip_size - 1) * f) - index;

			auto point = ql::cubic_interpolation(a, b, c, d, left_over);

			low = ql::min(point, low);
			high = ql::max(point, high);
		}

		return std::make_pair(low, high);
	}

	template <typename T>
	std::vector<std::decay_t<T>>
	cubic_container_interpolation(std::span<T> data, ql::size interpolations, ql::size index_skip_size = 1u)
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

		std::decay_t<T> a, b, c, d;

		for (ql::u32 i = 0u; i < result.size(); ++i)
		{
			ql::f64 f = i / ql::f64_cast(result.size() - 1);

			ql::size index = ql::size_cast(f * (data.size() / index_skip_size - 1));

			c = a = b = data[index * index_skip_size];
			if (index >= 1u)
			{
				a = data[(index - 1) * index_skip_size];
			}

			if ((index + 1) * index_skip_size < data.size())
			{
				c = data[(index + 1) * index_skip_size];
			}
			d = c;

			if ((index + 2) * index_skip_size < data.size())
			{
				d = data[(index + 2) * index_skip_size];
			}

			auto left_over = ((data.size() / index_skip_size - 1) * f) - index;

			result[i] = ql::cubic_interpolation(a, b, c, d, left_over);
		}

		return result;
	}

}	 // namespace ql