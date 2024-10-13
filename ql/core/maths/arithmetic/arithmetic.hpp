#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/arithmetic/is-arithmetic.hpp>
#include <ql/core/transform/bit/bit.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::size number_of_digits(T value, T base = T{10})
	{
		return value < base ? 1 : 1 + ql::number_of_digits(value / base, base);
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr ql::size significant_digit(T n, T base = 10)
	{
		return n ? ql::size{1} + ql::significant_digit(static_cast<T>(n / base), base) : ql::size{};
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr bool is_power_of_two(T n)
	{
		return n == T{} ? false : (n == (T{1} << (ql::significant_bit(n) - 1)));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr bool base_full_bit_usage(T base)
	{
		return ql::is_power_of_two(base) ? ql::bits_in_type<T>() % (ql::significant_bit(base) - 1) == 0 : false;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T base_max_log(T base)
	{
		return ql::base_full_bit_usage(base) ? static_cast<T>(ql::bits_in_type<T>() / (ql::significant_bit(base) - 1))
																				 : ql::log<T>(base, T{1} << (ql::bits_in_type<T>() - 1));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T base_max(T base)
	{
		return ql::base_full_bit_usage(base) ? T{} : ql::pow(base, ql::base_max_log(base));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr void flip_digits(T& value, ql::u32 base = 10)
	{
		value = ql::base_max<T>(static_cast<T>(base)) - 1 - value;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T flipped_digits(T value, ql::u32 base = 10)
	{
		return ql::base_max<T>(static_cast<T>(base)) - 1 - value;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr void flip_digits_until(T& value, ql::size position, ql::u32 base = 10)
	{
		auto pow = ql::pow<ql::size>(base, position);
		value = (value + (pow - 1 - (value % pow) * 2));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T flipped_digits_until(T value, ql::size position, ql::u32 base = 10)
	{
		auto pow = ql::pow<ql::size>(base, position);
		return (value + (pow - 1 - (value % pow) * 2));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr void flip_digits_until_msd(T& value, ql::u32 base = 10)
	{
		ql::flip_digits_until(value, ql::significant_digit(value, base), base);
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T flipped_digits_until_msd(T value, ql::u32 base = 10)
	{
		return ql::flipped_digits_until(value, ql::significant_digit(value, base), base);
	}

	template <typename T1, typename T2>
	constexpr T1 loop_index(T1 n, T2 size)
	{
		if (n < 0)
		{
			n *= -1;
			n %= size;
			return static_cast<T1>(size) - n;
		}
		return n % static_cast<T1>(size);
	}

	template <typename T>
	requires (ql::is_floating_point<T>())
	constexpr T round(T value, ql::size precision)
	{
		T factor = ql::pow<T>(T{10}, precision);
		return std::round(value * factor) / factor;
	}
}	 // namespace ql