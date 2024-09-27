#pragma once

#include <utility>
#include <ql/definition/definition.hpp>
#include <ql/constexpr/index.hpp>

namespace ql
{
  template <ql::size N, typename F>
  constexpr void constexpr_iterate(F &&function)
  {
    auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>) {
      (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}), ...);
    };
    unpack(std::make_index_sequence<N>());
  }
}