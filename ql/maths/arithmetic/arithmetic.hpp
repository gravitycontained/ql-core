#pragma once

#include <ql/type/arithmetic/arithmetic.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::size number_of_digits(T value, T base = T{10})
	{
		return value < base ? 1 : 1 + ql::number_of_digits(value / base, base);
	}
}	 // namespace ql