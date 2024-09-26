#pragma once

#include <ql/definition/definition.hpp>

namespace ql
{

#ifndef ql_NO_FLOATS
  template <ql::size exponent_bits, ql::size mantissa_bits>
  struct floating_point;
#endif

  template <typename T> struct is_ql_integer_impl : std::false_type
  {};

  template <ql::size bits, bool sign>
  struct is_ql_integer_impl<ql::integer<bits, sign>> : std::true_type
  {};

  template <typename T> constexpr bool is_ql_integer()
  {
    return is_ql_integer_impl<T>{};
  }

  template <typename T> struct is_ql_integer_signed_impl : std::false_type
  {};

  template <ql::size bits>
  struct is_ql_integer_signed_impl<ql::integer<bits, true>> : std::true_type
  {};

  template <typename T> constexpr bool is_ql_integer_signed()
  {
    return is_ql_integer_signed_impl<T>{};
  }
#ifndef ql_NO_FLOATS
  template <typename T> struct is_ql_floating_point_impl : std::false_type
  {};

  template <ql::size exponent_bits, ql::size mantissa_bits>
  struct is_ql_floating_point_impl<
    ql::floating_point<exponent_bits, mantissa_bits>> : std::true_type
  {};

  template <typename T> constexpr bool is_ql_floating_point()
  {
    return is_ql_floating_point_impl<T>{};
  }
#else

  template <typename T> constexpr bool is_ql_floating_point()
  {
    return false;
  }
#endif

  template <typename T> struct is_ql_dynamic_integer_impl : std::false_type
  {};

  template <ql::u32 base, bool sign>
  struct is_ql_dynamic_integer_impl<ql::dynamic_integer<base, sign>>
      : std::true_type
  {};

  template <typename T> constexpr bool is_ql_dynamic_integer()
  {
    return is_ql_dynamic_integer_impl<T>{};
  }

  template <typename T> constexpr bool is_ql_arithmetic()
  {
    return is_ql_dynamic_integer<T>() || is_ql_integer<T>()
           || is_ql_floating_point<T>();
  }

#ifdef ql_USE_INTRINSICS
  template <ql::size bits, bool sign> struct x64_integer;

  template <typename T> struct is_ql_x64_integer_impl : std::false_type
  {};

  template <ql::size bits, bool sign>
  struct is_ql_x64_integer_impl<ql::x64_integer<bits, sign>> : std::true_type
  {};

  template <typename T> constexpr bool is_ql_x64_integer()
  {
    return is_ql_x64_integer_impl<T>{};
  }
#endif

  template <typename T> struct is_ql_x64_integer_signed_impl : std::false_type
  {};

  template <ql::size bits>
  struct is_ql_x64_integer_signed_impl<ql::x64_integer<bits, true>>
      : std::true_type
  {};

  template <typename T> constexpr bool is_ql_x64_integer_signed()
  {
    return is_ql_x64_integer_signed_impl<T>{};
  }

  template <typename T> constexpr bool is_stl_arithmetic()
  {
    return std::is_arithmetic_v<T>;
  }

  template <typename T> constexpr bool is_arithmetic()
  {
    return std::is_arithmetic_v<T> || is_ql_integer<T>()
           || is_ql_floating_point<T>();
  }
}