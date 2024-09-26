#pragma once

#include <ql/definition/definition.hpp>
#include <tuple>

namespace ql
{
  template <typename... Ts>
  constexpr ql::size variadic_size()
  {
    return std::tuple_size_v<std::tuple<Ts...>>;
  }

  template <typename... Ts>
  constexpr ql::size variadic_size(Ts &&...args)
  {
    return ql::variadic_size<Ts...>();
  }
}