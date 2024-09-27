#pragma once

#include <ql/type-traits/check/is-container.hpp>
#include <ql/type-traits/declval.hpp>

namespace ql
{

  template <typename C>
    requires(ql::is_container<C>())
  using container_subtype
    = std::decay_t<decltype(*(ql::declval<C>().begin()))>;
}