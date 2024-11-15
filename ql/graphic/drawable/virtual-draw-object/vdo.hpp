#pragma once

#include <ql/core/core.hpp>

#ifdef QL_GRAPHIC

namespace ql
{
	struct text;
	struct smooth_rectangle;

	namespace detail
	{
		QL_SOURCE extern ql::text text;
		QL_SOURCE extern ql::smooth_rectangle smooth_rectangle;
	}	 // namespace detail
}

#endif