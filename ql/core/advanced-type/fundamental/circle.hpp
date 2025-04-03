#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/advanced-type/fundamental/vector.hpp>

namespace ql
{
	template <typename T>
	struct circle_t
	{
		ql::vector2<T> position;
		T radius;
	};

	using circle = circle_t<ql::f32>;
}