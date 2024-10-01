#pragma once

#include <type_traits>

namespace ql
{
	template <typename T>
	concept lvalue = std::is_lvalue_reference_v<T>;

	template <typename T>
	concept rvalue = std::is_rvalue_reference_v<T>;

	template <typename T>
	concept no_reference = !std::is_lvalue_reference_v<T> && !std::is_rvalue_reference_v<T>;

}	 // namespace ql