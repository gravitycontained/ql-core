#pragma once

#include <type_traits>

namespace ql
{
  template <typename T>
  constexpr auto declval()
  {
    using pointer = std::decay_t<T> *;
    return *(pointer{});
  }
}