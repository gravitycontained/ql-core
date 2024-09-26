#pragma once

#include <ql/type-traits/check/is-tuple.hpp>
#include <ql/type-traits/tuple/tuple-size.hpp>

namespace ql
{
  template <typename T>
  requires(ql::is_tuple<T>())
  constexpr auto tuple_to_array(T tuple)
  {
    constexpr auto size = ql::tuple_size<T>();
  }
}