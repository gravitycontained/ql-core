
#pragma once

#include <ql/definition/definition.hpp>
#include <ql/constexpr/index.hpp>

namespace ql
{

  template <ql::size N, typename F>
  constexpr auto constexpr_apply(F &&function)
  {
    auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
    {
      return std::make_tuple(std::forward<F>(function)(
          ql::constexpr_index<Ints, N> {})...);
    };
    return unpack(std::make_index_sequence<N>());
  }
}