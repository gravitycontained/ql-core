#pragma once

#include <tuple>

#include <ql/constexpr/constexpr.hpp>

namespace ql
{
  template <typename... Args>
  constexpr auto to_tuple(Args &&...args)
  {
    return std::make_tuple(std::forward<Args>(args)...);
  }

  template <typename T, ql::size N>
  constexpr auto array_to_tuple(const std::array<T, N> &array)
  {
    return ql::constexpr_iterate<N>([])
  }
}