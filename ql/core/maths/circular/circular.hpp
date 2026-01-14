#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/maths/circular/line-circle.hpp>
#include <ql/core/maths/circular/rotate.hpp>

#include <ql/core/type/type.hpp>
#include <ql/core/transform/cast/cast.hpp>

namespace ql
{
	template <typename T, typename R = ql::conditional<ql::if_true<ql::is_floating_point<T>()>, T, ql::f64>>
	requires (ql::is_arithmetic<T>())
	constexpr R radians(T value)
	{
		return ql::type_cast<R>(value * (ql::pi / R{180}));
	}
}	 // namespace ql