#pragma once

#include <ql/core/type/arithmetic/is-arithmetic.hpp>
#include <ql/core/transform/cast/cast.hpp>

#include <ql/core/transform/bit/bit.hpp>
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
							 ? ql::type_cast<T>(ql::detail::sqrt_helper<f_type>(ql::type_cast<f_type>(x), ql::type_cast<f_type>(x), f_type{0.0})
								 )
							 : std::numeric_limits<double>::quiet_NaN();
	}

	template <typename T, typename U>
	constexpr auto div_mod(T a, U b)
	{
		auto div = a / b;
		auto mod = a % b;
		return std::make_pair(div, mod);
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T approximate_multiple_down(T value, T multiple)
	{
		return (value / multiple) * multiple;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T approximate_multiple_up(T value, T multiple)
	{
		return (((value - 1) / multiple) + 1) * multiple;
	}

	template <typename T, typename U, typename R = ql::superior_arithmetic_type<T, U>>
	constexpr R pow(T a, U b)
	{
		return b == U{} ? R{1} : static_cast<R>(a * ql::pow(a, b - T{1}));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T shift(T a, T b)
	{
		return b == T{} ? T{1} : static_cast<T>(a * ql::pow<T>(a, b - T{1}));
	}

	template <typename T>
	constexpr T square(T value)
	{
		return value * value;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T factorial(T a)
	{
		return a <= T{1} ? T{1} : (a == T{2} ? T{2} : static_cast<T>(a * ql::factorial(a - 1)));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T log(T a, T b)
	{
		return b < a ? T{} : T{1} + ql::log(a, static_cast<T>(b / a));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr ql::i64 log2(T a)
	{
		return a ? ql::i64{1} + ql::log2(static_cast<T>(a >> 1)) : ql::i64{-1};
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T log_approximation(T a, T b, T c = T{1})
	{
		return c > static_cast<T>(b / a) ? c : ql::log_approximation(a, b, static_cast<T>(c * a));
	}

}	 // namespace ql