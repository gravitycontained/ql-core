#pragma once

namespace ql
{
	namespace detail
	{
#if defined QL_RELEASE
		constexpr bool array_boundary_check = false;
		constexpr bool vector_boundary_check = false;
#else
		constexpr bool array_boundary_check = true;
		constexpr bool vector_boundary_check = true;
#endif

	}	 // namespace detail
}	 // namespace ql