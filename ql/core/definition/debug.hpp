#pragma once

namespace ql::debug {

	#ifdef QL_DEBUG_PRINT
		constexpr bool print = true;
	#else
		constexpr bool print = false;
	#endif

}	 // namespace ql::debug