#pragma once

#include <tuple>

#include <ql/type-traits/container-subtype.hpp>
#include <ql/type-traits/check/is-container.hpp>
#include <ql/type-traits/check/is-tuple.hpp>
#include <ql/type-traits/compare.hpp>

#include <iostream>
#include <sstream>

namespace ql
{
  namespace impl
  {
    template <typename T>
    concept is_cout_printable_c = requires(const T t) { std::cout << t; };
    template <typename T>
    concept is_wcout_printable_c = requires(const T t) { std::wcout << t; };
    template <typename T>
    concept is_u32_printable_c = requires(
        const T t, std::basic_ostringstream<char32_t> stream) { stream << t; };

    template <typename T>
    concept is_printable_c = is_cout_printable_c<T> || is_wcout_printable_c<T>
                             || is_u32_printable_c<T>;

    template <typename T>
    constexpr bool is_printable()
    {
      if constexpr(ql::is_container<T>())
      {
        return ql::impl::is_printable<ql::container_subtype<T>>();
      }
      else if constexpr(ql::is_tuple<T>())
      {
        auto check = [&]<typename... Ts>(std::tuple<Ts...>)
        {
          constexpr auto b = (ql::impl::is_printable<Ts>() && ...);

          if constexpr(b)
          {
            return std::true_type{};
          }
          else
          {
            return std::false_type{};
          }
        };
        return decltype(check(ql::declval<T>()))::value;
      }
      else if constexpr(ql::is_pair<T>())
      {
        auto check = [&]<typename... Ts>(std::pair<Ts...>)
        {
          constexpr auto b = (ql::impl::is_printable<Ts>() && ...);
          if constexpr(b)
          {
            return std::true_type{};
          }
          else
          {
            return std::false_type{};
          }
        };
        return decltype(check(ql::declval<T>()))::value;
      }
      else
      {
        return (static_cast<bool>(ql::impl::is_printable_c<T>));
      }
    }
  }

  template <typename... Args>
  constexpr bool is_printable()
  {
    return ((ql::impl::is_printable<Args>()) && ...);
  }
}