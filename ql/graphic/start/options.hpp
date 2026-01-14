#pragma once

#include <ql/core/advanced-type/fundamental/fundamental.hpp>

namespace ql
{
	struct start_options
	{
		std::string name = "app";
		ql::vec2 dimension = { 1400u, 950u };
		ql::u32 antialiasing = 12;
		ql::u32 framerate_limit = 144u;
	};
}