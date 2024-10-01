#pragma once

#include <ql/core/definition/definition.hpp>

namespace ql
{
	enum class format_options : ql::u8
	{
		none = 0x0,
		comma_separated = 0b1,
		container_newline = 0b10,
	};
}	 // namespace ql