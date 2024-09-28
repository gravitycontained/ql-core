#pragma once

#include <tuple>
#include <ql/core/type/declval.hpp>

namespace ql
{
  namespace impl
  {
    template <typename... Ts>
    constexpr auto tuple_signature(std::tuple<Ts...>)
    {
      return std::true_type{};
    }

    template <typename T>
    constexpr auto tuple_signature(T)
    {
      return std::false_type{};
    }

    template <typename... Ts>
    constexpr auto pair_signature(std::pair<Ts...>)
    {
      return std::true_type{};
    }

    template <typename T>
    constexpr auto pair_signature(T)
    {
      return std::false_type{};
    }
  }

  template <typename T>
  constexpr bool is_tuple()
  {
    return decltype(ql::impl::tuple_signature(ql::declval<T>())){};
  }

  template <typename T>
  constexpr bool is_tuple(T tuple)
  {
    return ql::is_tuple<T>();
  }

  template <typename T>
  constexpr bool is_pair()
  {
    return decltype(ql::impl::pair_signature(ql::declval<T>())){};
  }

  template <typename T>
  constexpr bool is_is_pair(T tuple)
  {
    return ql::is_is_pair<T>();
  }
}