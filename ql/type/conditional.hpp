#pragma once

#include <type_traits>

#include <ql/definition/definition.hpp>
#include <ql/type/compare/compare.hpp>
#include <ql/type/identity.hpp>

namespace ql
{

  template <class Truth, class T, typename... Args>
  struct conditional_impl;

  template <typename... Args>
  struct conditional_indirection
  {
    using type = typename conditional_impl<Args...>::type;
  };

  template <class Truth, class T, typename... Args>
  struct conditional_impl
  {
    using type = typename std::enable_if_t<
      (sizeof...(Args) == 0 && ql::is_same<Truth, ql::default_type>())
        || ql::is_truth_type<Truth>(),
      std::conditional_t<
        (sizeof...(Args) >= 2),
        std::conditional_t<ql::is_true<Truth>(),
                           std::conditional_t<ql::is_same<T, ql::error_type>(),
                                              T, ql::identity<T>>,
                           ql::conditional_indirection<Args...>>,
        std::conditional_t<
          (sizeof...(Args) == 0),
          std::conditional_t<std::is_same_v<Truth, ql::default_type>,
                             std::conditional_t<std::is_same_v<T, ql::error_type>,
                                                T, ql::identity<T>>,
                             std::enable_if<ql::is_true<Truth>(), T>>,
          std::conditional_t<ql::is_true<Truth>(),
                             std::conditional_t<std::is_same_v<T, ql::error_type>,
                                                T, ql::identity<T>>,
                             ql::empty_indirection<Args...>>>>>::type;
  };

  template <class Truth, class T, typename... Args>
  using resolved_conditional =
    typename conditional_impl<Truth, T, Args...>::type;

  template <class Truth, class T, typename... Args>
  using conditional_identity = typename std::conditional_t<
    std::is_same_v<ql::resolved_conditional<Truth, T, Args...>, ql::error_type>,
    ql::error_type, conditional_impl<Truth, T, Args...>>;

  template <class Truth, class T, typename... Args>
  using conditional = typename ql::conditional_identity<Truth, T, Args...>::type;

}