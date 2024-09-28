#pragma once

#include <limits>

#include <ql/core/definition/definition.hpp>

namespace ql
{
  template <typename T>
  constexpr T type_max()
  {
    return std::numeric_limits<T>::max();
  }

  template <typename T>
  constexpr T type_min()
  {
    return std::numeric_limits<T>::min();
  }
}