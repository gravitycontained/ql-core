#pragma once

#include <ql/definition/definition.hpp>
#include <ql/type-traits/check/is-tuple.hpp>
#include <tuple>

namespace ql
{
  template <ql::size N, typename T>
    requires(ql::is_tuple<T>())
  using tuple_type = std::tuple_element_t<N, T>;
}