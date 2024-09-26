#pragma once

#include <ql/definition/definition.hpp>
#include <utility>

namespace ql
{
  namespace detail
  {
    template <ql::size Index, ql::size Size>
    struct constexpr_index
    {
      constexpr operator ql::size()
      {
        return Index;
      }

      constexpr static ql::size size = Size;
      constexpr static ql::size i = Index;
    };
  }

  template <ql::size N, typename F>
  constexpr void constexpr_iterate(F &&function)
  {
    auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>) {
      (std::forward<F>(function)(ql::detail::constexpr_index<Ints, N>{}), ...);
    };
    unpack(std::make_index_sequence<N>());
  }
}