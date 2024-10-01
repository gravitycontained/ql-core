#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/arithmetic/is-arithmetic.hpp>
#include <ql/core/type/bit/size.hpp>

#include <limits>

namespace ql
{
	template <typename T>
	constexpr ql::size bit_count_of_max_value()
	{
		if constexpr (ql::is_ql_integer<T>())
		{
			return T::used_bit_size();
		}
		else if constexpr (ql::is_stl_integer<T>())
		{
			return std::numeric_limits<T>::digits;
		}
		else
		{
			return ql::bits_in_type<T>();
		}
	}
}	 // namespace ql