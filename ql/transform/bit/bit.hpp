#pragma once

#include <ql/definition/definition.hpp>
#include <ql/type/type.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_integer<T>())
	constexpr void reverse_bits(T& value)
	{
		if constexpr (ql::is_same<T, ql::u32>())
		{
			value = ((value >> 1) & 0x55555555u) | ((value & 0x55555555u) << 1);
			value = ((value >> 2) & 0x33333333u) | ((value & 0x33333333u) << 2);
			value = ((value >> 4) & 0x0f0f0f0fu) | ((value & 0x0f0f0f0fu) << 4);
			value = ((value >> 8) & 0x00ff00ffu) | ((value & 0x00ff00ffu) << 8);
			value = ((value >> 16) & 0xffffu) | ((value & 0xffffu) << 16);
			return;
		}

		ql::size count = ql::bits_in_type<T>() - 1;
		T reverse_num = value;

		reverse_num >>= 1;
		while (reverse_num)
		{
			value <<= 1;
			value |= reverse_num & 1;
			reverse_num >>= 1;
			--count;
		}
		value <<= count;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T bits_reversed(T value)
	{
		T copy;
		ql::reverse_bits(copy);
		return copy;
	}
}