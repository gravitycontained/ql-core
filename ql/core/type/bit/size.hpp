#pragma once

#include <ql/core/definition/definition.hpp>

namespace ql
{
	constexpr ql::size bits_in_byte()
	{
#ifdef CHAR_BIT
		return CHAR_BIT;
#else
		return 8u;
#endif
	}

	template <typename T>
	constexpr ql::size bits_in_type()
	{
		return sizeof(T) * bits_in_byte();
	}

	template <typename T>
	constexpr ql::size bytes_in_type()
	{
		return sizeof(T);
	}
}