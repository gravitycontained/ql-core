
#pragma once

#include <ql/definition/definition.hpp>
#include <ql/type-traits/arithmetic/is-arithmetic.hpp>
#include <ql/type-traits/size/size.hpp>

namespace ql
{
	template <typename T>
	constexpr T bit_rotate_left(T val, ql::size rotation)
	{
		return (rotation >= ql::bits_in_type<T>() ? ql::bit_rotate_left(val, rotation % ql::bits_in_type<T>())
																							: ((val >> (ql::bits_in_type<T>() - rotation)) | (val << rotation)));
	}

	template <typename T>
	constexpr T bit_rotate_right(T val, ql::size rotation)
	{
		return (rotation >= ql::bits_in_type<T>()) ? ql::bit_rotate_right(val, rotation % ql::bits_in_type<T>())
																							 : ((val >> rotation) | (val << (ql::bits_in_type<T>() - rotation)));
	}
}	 // namespace ql