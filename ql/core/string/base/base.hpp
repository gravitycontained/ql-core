#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/bit/bit.hpp>

#include <ql/core/transform/cast/cast.hpp>

#include <ql/core/maths/arithmetic/arithmetic.hpp>

#include <ql/core/string/format/format.hpp>

namespace ql
{

	enum class base_format
	{
		base36l,
		base64,
		base36u,
	};

	namespace detail
	{
		constexpr std::array<ql::u8, 64> base_64 = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
																								'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
																								'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
																								'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
		constexpr std::array<ql::u8, ql::type_configurations<ql::u8>()> base_64_inv = {
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0x3eu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0x3fu},
				ql::u8{0x34u}, ql::u8{0x35u}, ql::u8{0x36u}, ql::u8{0x37u}, ql::u8{0x38u}, ql::u8{0x39u}, ql::u8{0x3au}, ql::u8{0x3bu},
				ql::u8{0x3cu}, ql::u8{0x3du}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0x40u}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0x0u},	ql::u8{0x1u},	 ql::u8{0x2u},	ql::u8{0x3u},	 ql::u8{0x4u},	ql::u8{0x5u},	 ql::u8{0x6u},
				ql::u8{0x7u},	 ql::u8{0x8u},	ql::u8{0x9u},	 ql::u8{0xau},	ql::u8{0xbu},	 ql::u8{0xcu},	ql::u8{0xdu},	 ql::u8{0xeu},
				ql::u8{0xfu},	 ql::u8{0x10u}, ql::u8{0x11u}, ql::u8{0x12u}, ql::u8{0x13u}, ql::u8{0x14u}, ql::u8{0x15u}, ql::u8{0x16u},
				ql::u8{0x17u}, ql::u8{0x18u}, ql::u8{0x19u}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0x1au}, ql::u8{0x1bu}, ql::u8{0x1cu}, ql::u8{0x1du}, ql::u8{0x1eu}, ql::u8{0x1fu}, ql::u8{0x20u},
				ql::u8{0x21u}, ql::u8{0x22u}, ql::u8{0x23u}, ql::u8{0x24u}, ql::u8{0x25u}, ql::u8{0x26u}, ql::u8{0x27u}, ql::u8{0x28u},
				ql::u8{0x29u}, ql::u8{0x2au}, ql::u8{0x2bu}, ql::u8{0x2cu}, ql::u8{0x2du}, ql::u8{0x2eu}, ql::u8{0x2fu}, ql::u8{0x30u},
				ql::u8{0x31u}, ql::u8{0x32u}, ql::u8{0x33u}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
				ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu}, ql::u8{0xFFu},
		};
		constexpr std::array<ql::u8, 36> base_36_upper = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
																											'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
																											'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

		constexpr std::array<ql::u8, 36> base_36_lower = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',
																											'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
																											'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
		constexpr std::array<ql::u8, ql::type_configurations<ql::u8>()> base_36_inv = {
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0x0},	ql::u8{0x1},	ql::u8{0x2},	ql::u8{0x3},	ql::u8{0x4},	ql::u8{0x5},	ql::u8{0x6},	ql::u8{0x7},
				ql::u8{0x8},	ql::u8{0x9},	ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xa},	ql::u8{0xb},	ql::u8{0xc},	ql::u8{0xd},	ql::u8{0xe},	ql::u8{0xf},	ql::u8{0x10},
				ql::u8{0x11}, ql::u8{0x12}, ql::u8{0x13}, ql::u8{0x14}, ql::u8{0x15}, ql::u8{0x16}, ql::u8{0x17}, ql::u8{0x18},
				ql::u8{0x19}, ql::u8{0x1a}, ql::u8{0x1b}, ql::u8{0x1c}, ql::u8{0x1d}, ql::u8{0x1e}, ql::u8{0x1f}, ql::u8{0x20},
				ql::u8{0x21}, ql::u8{0x22}, ql::u8{0x23}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xa},	ql::u8{0xb},	ql::u8{0xc},	ql::u8{0xd},	ql::u8{0xe},	ql::u8{0xf},	ql::u8{0x10},
				ql::u8{0x11}, ql::u8{0x12}, ql::u8{0x13}, ql::u8{0x14}, ql::u8{0x15}, ql::u8{0x16}, ql::u8{0x17}, ql::u8{0x18},
				ql::u8{0x19}, ql::u8{0x1a}, ql::u8{0x1b}, ql::u8{0x1c}, ql::u8{0x1d}, ql::u8{0x1e}, ql::u8{0x1f}, ql::u8{0x20},
				ql::u8{0x21}, ql::u8{0x22}, ql::u8{0x23}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff},
				ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}, ql::u8{0xff}
		};

		constexpr std::array<bool, ql::type_configurations<ql::u8>()> special_table = {
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		};
		constexpr std::array<bool, ql::type_configurations<ql::u8>()> alpha_table = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};
		constexpr std::array<bool, ql::type_configurations<ql::u8>()> digit_table = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};
		constexpr std::array<bool, ql::type_configurations<ql::u8>()> operator_table = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
				1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};

		constexpr std::array<bool, ql::type_configurations<ql::u8>()> unary_left_operator_table = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};

		constexpr std::array<bool, ql::type_configurations<ql::u8>()> unary_right_operator_table = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};

		constexpr std::array<bool, ql::type_configurations<ql::u8>()> white_space_table = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};

		constexpr std::array<bool, ql::type_configurations<ql::u8>()> parantheses_table = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};

		constexpr std::array<bool, ql::type_configurations<ql::u8>()> arithmetic_special_table = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
				1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};

	}	 // namespace detail

	constexpr bool is_character_special(ql::char_type c)
	{
		return ql::detail::special_table[ql::size_cast(ql::u8_cast(c))];
	}

	constexpr bool is_character_digit_alpha(ql::char_type c)
	{
		return !ql::detail::special_table[ql::size_cast(ql::u8_cast(c))];
	}

	constexpr bool is_character_digit(ql::char_type c)
	{
		return ql::detail::digit_table[ql::size_cast(ql::u8_cast(c))];
	}

	constexpr bool is_character_digit_or_dot(ql::char_type c)
	{
		return c == '.' || ql::detail::digit_table[ql::size_cast(ql::u8_cast(c))];
	}

	constexpr bool is_character_alpha(ql::char_type c)
	{
		return ql::detail::alpha_table[ql::size_cast(ql::u8_cast(c))];
	}

	constexpr bool is_character_whitespace(ql::char_type c)
	{
		return ql::detail::white_space_table[ql::size_cast(ql::u8_cast(c))];
	}

	constexpr bool is_character_visible(ql::char_type c)
	{
		return (c >= 32 && c <= 126);
	}

	template <typename T>
	requires (ql::is_integer<T>())
	std::string base_string(
			T value,
			T base,
			const std::string& prefix = "",
			base_format base_format = base_format::base36l,
			bool prepend_zeroes = false,
			ql::size prepend_size = ql::size_max
	)
	{
		if (value == T{})
		{
			if (prepend_zeroes)
			{
				switch (base_format)
				{
					case base_format::base36l:
						return prefix + ql::string_repeat(ql::char_cast(ql::detail::base_36_lower[0]), ql::size_cast(ql::base_max_log(base)));
					case base_format::base36u:
						return prefix + ql::string_repeat(ql::char_cast(ql::detail::base_36_upper[0]), ql::size_cast(ql::base_max_log(base)));
					case base_format::base64:
						return prefix + ql::string_repeat(ql::char_cast(ql::detail::base_64[0]), ql::size_cast(ql::base_max_log(base)));
				}
			}
			else
			{
				switch (base_format)
				{
					case base_format::base36l:
						return prefix + ql::to_string(ql::char_cast(ql::detail::base_36_lower[0]));
					case base_format::base36u:
						return prefix + ql::to_string(ql::char_cast(ql::detail::base_36_upper[0]));
					case base_format::base64:
						return prefix + ql::to_string(ql::char_cast(ql::detail::base_64[0]));
				}
			}
		}

		std::ostringstream stream;
		std::ostringstream digits;

		if constexpr (ql::is_signed<T>())
		{
			if (value < T{})
			{
				stream << "-";
				value *= T{-1};
			}
		}
		stream << prefix;

		auto logapprox = ql::log_approximation(base, value);
		T mod;

		switch (base_format)
		{
			case base_format::base36l:
				while (logapprox)
				{
					mod = value % logapprox;
					digits << ql::char_cast(ql::detail::base_36_lower[ql::size_cast(value / logapprox)]);
					value = mod;
					logapprox /= base;
				}
				break;
			case base_format::base36u:
				while (logapprox)
				{
					mod = value % logapprox;
					digits << ql::char_cast(ql::detail::base_36_upper[ql::size_cast(value / logapprox)]);
					value = mod;
					logapprox /= base;
				}
				break;
			case base_format::base64:
				while (logapprox)
				{
					mod = value % logapprox;
					digits << ql::char_cast(ql::detail::base_64[ql::size_cast(value / logapprox)]);
					value = mod;
					logapprox /= base;
				}
				break;
		}

		auto str = digits.str();
		if (prepend_zeroes)
		{
			auto base_log = prepend_size == ql::size_max ? ql::i64_cast(ql::base_max_log(base)) : ql::i64_cast(prepend_size);
			ql::i64 left = base_log - ql::i64_cast(str.length());

			if (left > ql::i64{})
			{
				switch (base_format)
				{
					case base_format::base36l:
						stream << ql::string_repeat(ql::char_cast(ql::detail::base_36_lower[0]), ql::size_cast(left));
						break;
					case base_format::base36u:
						stream << ql::string_repeat(ql::char_cast(ql::detail::base_36_upper[0]), ql::size_cast(left));
						break;
					case base_format::base64:
						stream << ql::string_repeat(ql::char_cast(ql::detail::base_64[0]), ql::size_cast(left));
						break;
				}
			}
		}

		stream << digits.str();
		return stream.str();
	}

	template <typename T>
	requires (ql::is_integer<T>())
	char base_char(T value, T base, bool upper36 = false)
	{
		if (base <= 36)
		{
			if (upper36)
			{
				return ql::detail::base_36_upper[value];
			}
			else
			{
				return ql::detail::base_36_lower[value];
			}
		}
		else
		{
			return ql::detail::base_64[value];
		}
	}

	template <typename T>
	requires (ql::is_integer<T>())
	T from_base_char(char c, T base)
	{
		if (base <= 36)
		{
			return ql::detail::base_36_inv[c];
		}
		else
		{
			return ql::detail::base_64_inv[c];
		}
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr T from_string(const std::string_view& string)
	{
		if constexpr (ql::is_same_decayed<T, std::string>())
		{
			return string;
		}
		else if constexpr (ql::is_same_decayed<T, ql::f64>())
		{
			return std::strtod(string.data(), nullptr);
		}
		else if constexpr (ql::is_same_decayed<T, ql::f32>())
		{
			return std::strtof(string.data(), nullptr);
		}
		else if constexpr (ql::is_ql_integer<T>())
		{
			return T{string};
		}
		else
		{
			return static_cast<T>(std::atoll(string.data()));
		}
	}

	template <typename T>
	requires (ql::is_same_decayed<T, std::string>())
	constexpr T from_string(const std::string& string)
	{
		return string;
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr T from_string(const std::wstring_view& string)
	{
		if constexpr (ql::is_same_decayed<T, std::wstring>())
		{
			return string;
		}
		else if constexpr (ql::is_same_decayed<T, ql::f64>())
		{
			return std::wcstod(string.data(), nullptr);
		}
		else if constexpr (ql::is_same_decayed<T, ql::f32>())
		{
			return std::wcstof(string.data(), nullptr);
		}
		else if constexpr (ql::is_ql_integer<T>())
		{
			return T{string};
		}
		else
		{
			return static_cast<T>(std::wcstoll(string.data()));
		}
	}

	template <typename T>
	requires (ql::is_same_decayed<T, std::wstring>())
	constexpr T from_string(const std::wstring& string)
	{
		return string;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T from_base_string(const std::string_view& string, T base, base_format base_format = base_format::base36l)
	{
		bool negative = false;
		if (string.front() == '-')
		{
			negative = true;
		}

		ql::i32 stop = negative;
		if (string.length() >= 2 && string.substr(negative, 2) == "0x")
		{
			stop += 2;
		}
		T result = T{};
		T mul = T{1};
		for (ql::isize i = ql::isize_cast(string.length() - 1); i >= stop; --i)
		{
			switch (base_format)
			{
				case base_format::base36l:
				case base_format::base36u:
					result += static_cast<T>(ql::detail::base_36_inv[string[i]]) * mul;
					break;
				case base_format::base64:
					result += static_cast<T>(ql::detail::base_64_inv[string[i]]) * mul;
					break;
			}
			mul *= base;
		}
		if constexpr (ql::is_signed<T>())
		{
			if (negative)
			{
				result = -result;
			}
		}
		return result;
	}

	template <typename T>
	requires (ql::is_integer<T>())
	std::string
	base64_string(T value, const std::string& prefix = "", base_format base_format = base_format::base64, bool prepend_zeroes = false)
	{
		return ql::base_string(value, T{64}, prefix, base_format, prepend_zeroes);
	}

	QL_SOURCE std::string base64_string(const std::string_view& string);
	QL_SOURCE std::string from_base64_string(const std::string_view& string);

	template <typename T>
	requires (ql::is_integer<T>())
	std::string
	hex_string(T value, const std::string& prefix = "0x", base_format base_format = base_format::base36l, bool prepend_zeroes = false)
	{
		return ql::base_string(value, T{16}, prefix, base_format, prepend_zeroes);
	}

	QL_SOURCE std::string hex_string(const std::string_view& string);
	QL_SOURCE std::string from_hex_string(const std::string_view& string);

	QL_SOURCE std::string hex_to_base64_string(const std::string_view& string);
	QL_SOURCE std::string base64_to_hex_string(const std::string_view& string);

	template <typename T>
	requires (ql::is_integer<T>())
	std::string hex_string_full(T value, const std::string& prefix = "0x", base_format base_format = base_format::base36l)
	{
		return ql::base_string(value, T{16}, prefix, base_format, true);
	}

	template <typename T>
	requires (ql::is_integer<T>())
	std::string binary_string(T value, base_format base_format = base_format::base36l, bool prepend_zeroes = false)
	{
		return ql::base_string(value, T{2}, "", base_format, prepend_zeroes);
	}

	QL_SOURCE std::string binary_string(const std::string& string);

	template <typename T>
	requires (ql::is_integer<T>())
	std::string binary_string_full(T value, ql::size prepended_size = ql::size_max, base_format base_format = base_format::base36l)
	{
		return ql::base_string(value, T{2}, "", base_format, true, prepended_size);
	}

	QL_SOURCE std::string string_xor(std::string a, std::string b);
	QL_SOURCE std::string hex_string_xor(std::string a, std::string b);

	template <typename C>
	requires (ql::is_container<C>())
	inline std::string container_to_hex_string(const C& data, std::string_view delimiter = ", ", std::string_view brackets = "{}")
	{
		std::ostringstream str;
		str << brackets.front();
		bool start = true;
		for (const auto& e : data)
		{
			if constexpr (ql::is_container<ql::container_subtype<C>>())
			{
				if (!start)
				{
					str << delimiter;
				}
				str << container_to_string(e);
				start = false;
			}
			else
			{
				if (!start)
				{
					str << delimiter;
				}
				str << ql::hex_string_full(e);
				if constexpr (ql::is_unsigned<decltype(e)>())
				{
					str << 'u';
				}
				start = false;
			}
		}
		str << brackets.back();
		return str.str();
	}

}	 // namespace ql