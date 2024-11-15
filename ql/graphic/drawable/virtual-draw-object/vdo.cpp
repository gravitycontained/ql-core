#include <ql/graphic/drawable/virtual-draw-object/vdo.hpp>

#ifdef QL_GRAPHIC

#include <ql/graphic/drawable/basic/text/text.hpp>
#include <ql/graphic/drawable/advanced/smooth-rectangle/smooth-rectangle.hpp>

namespace ql
{
	namespace detail
	{
		ql::text ql::detail::text;
		ql::smooth_rectangle ql::detail::smooth_rectangle;
	}	 // namespace detail

}

#endif