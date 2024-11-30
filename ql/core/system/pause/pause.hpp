#pragma once

#include <ql/core/definition/definition.hpp>

namespace ql
{
	QL_SOURCE void system_pause(ql::u32 max_keyboard_latency_hz = 50'000u);
}	 // namespace ql