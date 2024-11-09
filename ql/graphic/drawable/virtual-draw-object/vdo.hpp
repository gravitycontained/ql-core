#pragma once

#include <ql/core/core.hpp>

#ifdef QL_GRAPHIC

namespace ql
{
	struct text;

	namespace detail
	{
		QL_SOURCE extern ql::text text;
	}	 // namespace detail
}

#endif