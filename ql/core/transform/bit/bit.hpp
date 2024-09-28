#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_integer<T>())
	constexpr ql::size significant_bit(T n)
	{
		return n ? ql::size{1} + ql::significant_bit(static_cast<T>(n >> 1)) : ql::size{};
	}

	template <>
	constexpr ql::size significant_bit(ql::u8 n)
	{
		ql::u8 y = 0;

		ql::size result = 0u;
		if ((y = (n & ql::u8{0xf0u})))
		{
			result |= ql::size{0b100u};
			n = y;
		}
		if ((y = (n & ql::u8{0xccu})))
		{
			result |= ql::size{0b10u};
			n = y;
		}
		if (((n & ql::u8{0xaau})))
		{
			result |= ql::size{0b1u};
		}
		if (n)
		{
			++result;
		}
		return result;
	}

	template <>
	constexpr ql::size significant_bit(ql::u16 n)
	{
		ql::u16 y = 0;

		ql::size result = 0u;
		if ((y = (n & ql::u16{0xff00u})))
		{
			result |= ql::u16{0b1000u};
			n = y;
		}
		if ((y = (n & ql::u16{0xf0f0u})))
		{
			result |= ql::u16{0b100u};
			n = y;
		}
		if ((y = (n & ql::u16{0xccccu})))
		{
			result |= ql::u16{0b10u};
			n = y;
		}
		if (((n & ql::u16{0xaaaau})))
		{
			result |= ql::u16{0b1u};
		}
		if (n)
		{
			++result;
		}
		return result;
	}

	template <>
	constexpr ql::size significant_bit(ql::u32 n)
	{
		ql::u32 y = 0;

		ql::size result = 0u;
		if ((y = (n & 0xffff0000u)))
		{
			result |= 0b10000u;
			n = y;
		}
		if ((y = (n & 0xff00ff00u)))
		{
			result |= 0b1000u;
			n = y;
		}
		if ((y = (n & 0xf0f0f0f0u)))
		{
			result |= 0b100u;
			n = y;
		}
		if ((y = (n & 0xccccccccu)))
		{
			result |= 0b10u;
			n = y;
		}
		if (((n & 0xaaaaaaaau)))
		{
			result |= 0b1u;
		}
		if (n)
		{
			++result;
		}
		return result;
	}

	template <>
	constexpr ql::size significant_bit(ql::u64 n)
	{
		ql::u64 y = 0;

		ql::size result = 0u;
		if ((y = (n & 0xffffffff00000000ull)))
		{
			result |= 0b100000u;
			n = y;
		}
		if ((y = (n & 0xffff0000ffff0000ull)))
		{
			result |= 0b10000u;
			n = y;
		}
		if ((y = (n & 0xff00ff00ff00ff00ull)))
		{
			result |= 0b1000u;
			n = y;
		}
		if ((y = (n & 0xf0f0f0f0f0f0f0f0ull)))
		{
			result |= 0b100u;
			n = y;
		}
		if ((y = (n & 0xccccccccccccccccull)))
		{
			result |= 0b10u;
			n = y;
		}
		if (((n & 0xaaaaaaaaaaaaaaaaull)))
		{
			result |= 0b1u;
		}
		if (n)
		{
			++result;
		}
		return result;
	}

	constexpr ql::size significant_bit_ignore_last_bit(ql::u32 n)
	{
		uint32_t y = 0;

		ql::size result = 0u;
		if ((y = (n & 0x7fff0000U)))
		{
			result |= 0b10000u;
			n = y;
		}
		if ((y = (n & 0x7f00ff00U)))
		{
			result |= 0b1000u;
			n = y;
		}
		if ((y = (n & 0x70f0f0f0U)))
		{
			result |= 0b100u;
			n = y;
		}
		if ((y = (n & 0x4cccccccU)))
		{
			result |= 0b10u;
			n = y;
		}
		if (((n & 0x2aaaaaaaU)))
		{
			result |= 0b1u;
		}
		if (n)
		{
			++result;
		}
		return result;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr ql::size number_of_set_bits(T n)
	{
		return ql::number_of_set_bits(ql::u64_cast(n));
	}

	template <>
	constexpr ql::size number_of_set_bits(ql::u64 n)
	{
		n = n - ((n >> 1) & 0x5555'5555'5555'5555ull);
		n = (n & 0x3333'3333'3333'3333ull) + ((n >> 2) & 0x3333'3333'3333'3333ull);
		return (((n + (n >> 4)) & 0x0F0F'0F0F'0F0F'0F0Full) * 0x0101'0101'0101'0101ull) >> 56;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr bool get_bit(T value, ql::size position)
	{
		return ql::bool_cast(value & (T{1} << position));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr void set_bit(T& value, ql::size position, bool flag)
	{
		value = flag ? (value | (T{1} << position)) : (value & ~(T{1} << position));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T set_bit_copied(T value, ql::size position, bool flag)
	{
		return flag ? (value | (T{1} << position)) : (value & ~(T{1} << position));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr void toggle_bit(T& value, ql::size position)
	{
		value = (value & (T{1} << position)) ? (value & ~(T{1} << position)) : (value | (T{1} << position));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr void flip_bits(T& value)
	{
		value = ~value;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T flipped_bits(T value)
	{
		return ~value;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr void flip_bits_until(T& value, ql::size position)
	{
		value = (value & (~T{} << position)) | (~value & ~(~T{} << position));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T flipped_bits_until(T value, ql::size position)
	{
		return (value & (~T{} << position)) | (~value & ~(~T{} << position));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr void flip_bits_until_msb(T& value)
	{
		ql::flip_bits_until(value, ql::significant_bit(value));
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T flipped_bits_until_msb(T value)
	{
		return ql::flipped_bits_until(value, ql::significant_bit(value));
	}

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
}