#pragma once

#include <type_traits>

#include <ql/definition/definition.hpp>

namespace ql
{
  template <class T>
  constexpr bool is_true()
  {
    return std::is_same_v<T, ql::true_type>;
  }

  template <typename T, typename U>
  constexpr bool is_same()
  {
    return std::is_same_v<T, U>;
  }

  template <typename T, typename U>
  constexpr bool is_same_decayed()
  {
    return std::is_same_v<std::decay_t<T>, std::decay_t<U>>;
  }

  template <typename T>
  struct decay_t
  {
    using type = std::decay<T>::type;
  };

  template <typename T>
  using decay = std::decay_t<T>;

  template <typename T>
  using full_decay
    = std::remove_const_t<std::remove_pointer_t<std::decay_t<T>>>;

  template <typename T, typename U>
  concept is_same_decayed_c = (ql::is_same_decayed<T, U>());

  template <typename T, typename U, typename... Args>
  constexpr bool all_equal()
  {
    return ql::is_same<T, U>() && (ql::is_same<T, Args>() && ...);
  }

  template <typename T, typename U, typename... Args>
  constexpr bool all_equal_decayed()
  {
    return ql::is_same_decayed<T, U>()
           && (ql::is_same_decayed<T, Args>() && ...);
  }

  template <class compare, class... Args>
  constexpr bool is_any_type_equal_to()
  {
    return (ql::is_same<compare, Args>() || ...);
  }

  template <class compare, class... Args>
  constexpr bool is_any_type_decayed_equal_to()
  {
    return (ql::is_same_decayed<compare, Args>() || ...);
  }

  template <class compare, class... Args>
  constexpr bool are_all_types_equal()
  {
    return (ql::is_same<compare, Args>() && ...);
  }

  template <class compare, class... Args>
  constexpr bool are_all_types_unique()
  {
    if constexpr(sizeof...(Args) == 0)
      {
        return true;
      }
    else
      {
        return (!ql::is_any_type_equal_to<compare, Args...>()
                && ql::are_all_types_unique<Args...>());
      }
  }

  template <class T>
  constexpr bool is_truth_type()
  {
    return ql::is_any_type_equal_to<T, ql::true_type, ql::false_type>();
  }
}