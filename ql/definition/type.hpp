#pragma once

#include <type_traits>

namespace ql
{
  struct empty_type
  {};

  struct true_type
  {};

  struct false_type
  {};

  struct default_type
  {};

  using error_type = std::enable_if<false, void>;
  using default_error = error_type;

  template<bool condition>
	using if_true = std::conditional_t<condition, true_type, false_type>;
}