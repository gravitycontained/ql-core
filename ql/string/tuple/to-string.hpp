#pragma once

#include <ql/type-traits/check/check.hpp>
#include <string>

namespace ql
{
  template <typename T>
    requires(ql::is_tuple<T>())
  std::string to_string(T tuple)
  {}
}