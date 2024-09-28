#pragma once

#include <ql/type/arithmetic/is-arithmetic.hpp>
#include <ql/transform/cast/cast.hpp>
#include <limits>

namespace ql
{
	namespace detail
	{
		template <typename T>
		requires (ql::is_floating_point<T>())
		constexpr double sqrt_helper(T x, T a, T b)
		{
			return a == b ? a : ql::detail::sqrt_helper(x, T{0.5} * (a + x / a), a);
		}
	}	 // namespace detail 

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr auto sqrt(T x)
	{
		using f_type = ql::conditional<ql::if_true<ql::is_floating_point<T>()>, T, ql::f64>;
		return x >= 0 && x < std::numeric_limits<double>::infinity()
							 ? ql::type_cast<T>(
										 ql::detail::sqrt_helper<f_type>(ql::type_cast<f_type>(x), ql::type_cast<f_type>(x), f_type{0.0}))
							 : std::numeric_limits<double>::quiet_NaN();
	}
}	 // namespace ql