#pragma once

#include <ql/type-traits/compare/compare.hpp>
#include <ql/type-traits/declval.hpp>
#include <sstream>
#include <string>

namespace ql
{

  namespace detail
  {
    template <typename T>
    constexpr auto std_basic_string(std::basic_string<T>)
    {
      return std::true_type{};
    }

    template <typename T>
    constexpr auto std_basic_string(T)
    {
      return std::false_type{};
    }

    template <typename T>
    constexpr auto std_basic_string_view(std::basic_string_view<T>)
    {
      return std::true_type{};
    }

    template <typename T>
    constexpr auto std_basic_string_view(T)
    {
      return std::false_type{};
    }
  }

  template <typename T>
  constexpr bool is_std_basic_string()
  {
    return decltype(ql::detail::std_basic_string(ql::declval<T>())){};
  }

  template <typename T>
  constexpr bool is_std_basic_string_view()
  {
    return decltype(ql::detail::std_basic_string_view(ql::declval<T>())){};
  }

  template <typename T>
  constexpr bool is_string_type()
  {
    return ql::is_std_basic_string<T>() || ql::is_std_basic_string_view<T>()
           || ql::is_any_type_decayed_equal_to<
             T, char, const char *, char *, const char[], wchar_t,
             const wchar_t *, const wchar_t[], wchar_t *, char32_t>();
  }

  template <typename T>
  constexpr bool is_standard_string_type()
  {
    return ql::is_any_type_decayed_equal_to<T, char, const char *, char *,
                                            const char[], std::string,
                                            std::string_view>();
  }

  template <typename T>
  constexpr bool is_wstring_type()
  {
    return ql::is_any_type_decayed_equal_to<T, wchar_t, const wchar_t *,
                                            wchar_t *, const wchar_t[],
                                            std::wstring, std::wstring_view>();
  }

  template <typename T>
  constexpr bool is_u32string_type()
  {
    return ql::is_any_type_decayed_equal_to<
      T, char32_t, const char32_t *, char32_t *, const char32_t[],
      std::basic_string<std::uint32_t>,
      std::basic_string_view<std::uint32_t>>();
  }

  template <typename T>
  constexpr bool is_long_string_type()
  {
    return ql::is_std_basic_string<T>() || ql::is_std_basic_string_view<T>()
           || ql::is_any_type_decayed_equal_to<T, const char *, char *,
                                               const char[], const wchar_t *,
                                               const wchar_t[], wchar_t *>();
  }

  template <typename T>
  constexpr bool is_long_standard_string_type()
  {
    return ql::is_any_type_decayed_equal_to<
      T, const char *, char *, const char[], std::string, std::string_view>();
  }

  template <typename T>
  constexpr bool is_long_wstring_type()
  {
    return ql::is_any_type_decayed_equal_to<T, const wchar_t *, wchar_t *,
                                            const wchar_t[], std::wstring,
                                            std::wstring_view>();
  }

  template <typename T>
  constexpr bool is_string_type(T value)
  {
    return is_string_type<T>();
  }

  template <typename T>
  constexpr bool is_standard_string_type(T value)
  {
    return is_standard_string_type<T>();
  }

  template <typename T>
  constexpr bool is_wstring_type(T value)
  {
    return is_wstring_type<T>();
  }

  template <typename T>
  constexpr bool is_char_type()
  {
    return ql::is_any_type_decayed_equal_to<T, char, wchar_t, char8_t, char16_t,
                                            char32_t, ql::u8, ql::i8, ql::u16,
                                            ql::i16, ql::u32, ql::i32>();
  }

  template <typename T>
  constexpr bool is_char_pointer_type()
  {
    return ql::is_any_type_equal_to<
      std::remove_const_t<T>, char *, char[], const char *, const char[],
      wchar_t *, wchar_t[], const wchar_t *, const wchar_t[], char8_t *,
      char8_t[], const char8_t *, const char8_t[], char16_t *, char16_t[],
      const char16_t *, const char16_t[], char32_t *, char32_t[],
      const char32_t *, const char32_t[]>();
  }
}