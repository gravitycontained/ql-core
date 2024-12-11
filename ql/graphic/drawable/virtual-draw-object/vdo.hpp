#pragma once

#include <ql/graphic/drawable/basic/text/text.hpp>
#include <ql/graphic/drawable/advanced/smooth-rectangle/smooth-rectangle.hpp>

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