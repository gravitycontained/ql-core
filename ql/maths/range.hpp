#pragma once

namespace ql
{
  template <typename T>
  constexpr T min(T a, T b)
  {
    return (a < b ? a : b);
  }

  template <typename T, typename... Args>
  constexpr T min(T a, T b, Args... rest)
  {
    return ql::min(ql::min(a, b), rest...);
  }

  template <typename T>
  constexpr T max(T a, T b)
  {
    return (a > b ? a : b);
  }

  template <typename T, typename... Args>
  constexpr T max(T a, T b, Args... rest)
  {
    return ql::max(ql::max(a, b), rest...);
  }

  template <typename T>
  constexpr T clamp(T min, T value, T max)
  {
    return ql::min(max, ql::max(min, value));
  }
}