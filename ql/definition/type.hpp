#pragma once

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#include <cstdint>
#include <tuple>
#include <limits>
#include <string>

namespace ql
{
  using size = std::size_t;
  using isize = std::conditional_t<sizeof(std::size_t) == sizeof(std::int64_t),
                                   std::int64_t, std::int32_t>;

  using i8 = std::int8_t;
  using u8 = std::uint8_t;

  using i16 = std::int16_t;
  using u16 = std::uint16_t;

  using i32 = std::int32_t;
  using u32 = std::uint32_t;

  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  using itypes = std::tuple<ql::i8, ql::i16, ql::i32, ql::i64>;
  using itype_min = std::tuple_element_t<0, itypes>;
  using itype_max
    = std::tuple_element_t<std::tuple_size_v<itypes> - 1, itypes>;

  using utypes = std::tuple<ql::u8, ql::u16, ql::u32, ql::u64>;
  using utype_min = std::tuple_element_t<0, utypes>;
  using utype_max
    = std::tuple_element_t<std::tuple_size_v<utypes> - 1, utypes>;

  using f32 = float;
  using f64 = double;

  using u32_string = std::basic_string<ql::u32>;

  using ftypes = std::tuple<ql::f32, ql::f64>;
  using ftype_min = std::tuple_element_t<0, ftypes>;
  using ftype_max
    = std::tuple_element_t<std::tuple_size_v<ftypes> - 1, ftypes>;

  constexpr ql::i8 i8_min = std::numeric_limits<ql::i8>::min();
  constexpr ql::i8 i8_max = std::numeric_limits<ql::i8>::max();
  constexpr ql::u8 u8_min = std::numeric_limits<ql::u8>::min();
  constexpr ql::u8 u8_max = std::numeric_limits<ql::u8>::max();

  constexpr ql::i16 i16_min = std::numeric_limits<ql::i16>::min();
  constexpr ql::i16 i16_max = std::numeric_limits<ql::i16>::max();
  constexpr ql::u16 u16_min = std::numeric_limits<ql::u16>::min();
  constexpr ql::u16 u16_max = std::numeric_limits<ql::u16>::max();

  constexpr ql::i32 i32_min = std::numeric_limits<ql::i32>::min();
  constexpr ql::i32 i32_max = std::numeric_limits<ql::i32>::max();
  constexpr ql::u32 u32_min = std::numeric_limits<ql::u32>::min();
  constexpr ql::u32 u32_max = std::numeric_limits<ql::u32>::max();

  constexpr ql::i64 i64_min = std::numeric_limits<ql::i64>::min();
  constexpr ql::i64 i64_max = std::numeric_limits<ql::i64>::max();
  constexpr ql::u64 u64_min = std::numeric_limits<ql::u64>::min();
  constexpr ql::u64 u64_max = std::numeric_limits<ql::u64>::max();

  constexpr ql::f32 f32_min = std::numeric_limits<ql::f32>::lowest();
  constexpr ql::f32 f32_min_zero = std::numeric_limits<ql::f32>::min();
  constexpr ql::f32 f32_max = std::numeric_limits<ql::f32>::max();
  constexpr ql::f64 f64_min = std::numeric_limits<ql::f64>::lowest();
  constexpr ql::f64 f64_min_zero = std::numeric_limits<ql::f64>::min();
  constexpr ql::f64 f64_max = std::numeric_limits<ql::f64>::max();

  constexpr ql::f64 i8_min_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::i8>::min());
  constexpr ql::f64 i8_max_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::i8>::max());
  constexpr ql::f64 u8_min_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::u8>::min());
  constexpr ql::f64 u8_max_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::u8>::max());

  constexpr ql::f64 i16_min_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::i16>::min());
  constexpr ql::f64 i16_max_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::i16>::max());
  constexpr ql::f64 u16_min_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::u16>::min());
  constexpr ql::f64 u16_max_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::u16>::max());

  constexpr ql::f64 i32_min_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::i32>::min());
  constexpr ql::f64 i32_max_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::i32>::max());
  constexpr ql::f64 u32_min_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::u32>::min());
  constexpr ql::f64 u32_max_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::u32>::max());

  constexpr ql::f64 i64_min_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::i64>::min());
  constexpr ql::f64 i64_max_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::i64>::max());
  constexpr ql::f64 u64_min_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::u64>::min());
  constexpr ql::f64 u64_max_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::u64>::max());

  constexpr ql::f64 f32_min_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::f32>::min());
  constexpr ql::f64 f32_max_f64
    = static_cast<ql::f64>(std::numeric_limits<ql::f32>::max());

  constexpr ql::f32 i8_min_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::i8>::min());
  constexpr ql::f32 i8_max_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::i8>::max());
  constexpr ql::f32 u8_min_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::u8>::min());
  constexpr ql::f32 u8_max_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::u8>::max());

  constexpr ql::f32 i16_min_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::i16>::min());
  constexpr ql::f32 i16_max_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::i16>::max());
  constexpr ql::f32 u16_min_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::u16>::min());
  constexpr ql::f32 u16_max_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::u16>::max());

  constexpr ql::f32 i32_min_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::i32>::min());
  constexpr ql::f32 i32_max_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::i32>::max());
  constexpr ql::f32 u32_min_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::u32>::min());
  constexpr ql::f32 u32_max_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::u32>::max());

  constexpr ql::f32 i64_min_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::i64>::min());
  constexpr ql::f32 i64_max_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::i64>::max());
  constexpr ql::f32 u64_min_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::u64>::min());
  constexpr ql::f32 u64_max_f32
    = static_cast<ql::f32>(std::numeric_limits<ql::u64>::max());

  constexpr ql::u64 i8_min_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::i8>::min());
  constexpr ql::u64 i8_max_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::i8>::max());
  constexpr ql::u64 u8_min_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::u8>::min());
  constexpr ql::u64 u8_max_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::u8>::max());

  constexpr ql::u64 i16_min_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::i16>::min());
  constexpr ql::u64 i16_max_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::i16>::max());
  constexpr ql::u64 u16_min_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::u16>::min());
  constexpr ql::u64 u16_max_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::u16>::max());

  constexpr ql::u64 i32_min_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::i32>::min());
  constexpr ql::u64 i32_max_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::i32>::max());
  constexpr ql::u64 u32_min_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::u32>::min());
  constexpr ql::u64 u32_max_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::u32>::max());

  constexpr ql::u64 f32_min_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::f32>::min());
  constexpr ql::u64 f64_min_u64
    = static_cast<ql::u64>(std::numeric_limits<ql::f64>::min());

  constexpr ql::i64 i8_min_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::i8>::min());
  constexpr ql::i64 i8_max_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::i8>::max());
  constexpr ql::i64 u8_min_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::u8>::min());
  constexpr ql::i64 u8_max_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::u8>::max());

  constexpr ql::i64 i16_min_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::i16>::min());
  constexpr ql::i64 i16_max_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::i16>::max());
  constexpr ql::i64 u16_min_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::u16>::min());
  constexpr ql::i64 u16_max_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::u16>::max());

  constexpr ql::i64 i32_min_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::i32>::min());
  constexpr ql::i64 i32_max_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::i32>::max());
  constexpr ql::i64 u32_min_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::u32>::min());
  constexpr ql::i64 u32_max_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::u32>::max());

  constexpr ql::i64 f32_min_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::f32>::min());
  constexpr ql::i64 f64_min_i64
    = static_cast<ql::i64>(std::numeric_limits<ql::f64>::min());

  constexpr ql::u32 i8_min_u32
    = static_cast<ql::u32>(std::numeric_limits<ql::i8>::min());
  constexpr ql::u32 i8_max_u32
    = static_cast<ql::u32>(std::numeric_limits<ql::i8>::max());
  constexpr ql::u32 u8_min_u32
    = static_cast<ql::u32>(std::numeric_limits<ql::u8>::min());
  constexpr ql::u32 u8_max_u32
    = static_cast<ql::u32>(std::numeric_limits<ql::u8>::max());

  constexpr ql::u32 i16_min_u32
    = static_cast<ql::u32>(std::numeric_limits<ql::i16>::min());
  constexpr ql::u32 i16_max_u32
    = static_cast<ql::u32>(std::numeric_limits<ql::i16>::max());
  constexpr ql::u32 u16_min_u32
    = static_cast<ql::u32>(std::numeric_limits<ql::u16>::min());
  constexpr ql::u32 u16_max_u32
    = static_cast<ql::u32>(std::numeric_limits<ql::u16>::max());

  constexpr ql::i32 i8_min_i32
    = static_cast<ql::i32>(std::numeric_limits<ql::i8>::min());
  constexpr ql::i32 i8_max_i32
    = static_cast<ql::i32>(std::numeric_limits<ql::i8>::max());
  constexpr ql::i32 u8_min_i32
    = static_cast<ql::i32>(std::numeric_limits<ql::u8>::min());
  constexpr ql::i32 u8_max_i32
    = static_cast<ql::i32>(std::numeric_limits<ql::u8>::max());

  constexpr ql::i32 i16_min_i32
    = static_cast<ql::i32>(std::numeric_limits<ql::i16>::min());
  constexpr ql::i32 i16_max_i32
    = static_cast<ql::i32>(std::numeric_limits<ql::i16>::max());
  constexpr ql::i32 u16_min_i32
    = static_cast<ql::i32>(std::numeric_limits<ql::u16>::min());
  constexpr ql::i32 u16_max_i32
    = static_cast<ql::i32>(std::numeric_limits<ql::u16>::max());

  constexpr ql::u16 i8_min_u16
    = static_cast<ql::u16>(std::numeric_limits<ql::i8>::min());
  constexpr ql::u16 i8_max_u16
    = static_cast<ql::u16>(std::numeric_limits<ql::i8>::max());
  constexpr ql::u16 u8_min_u16
    = static_cast<ql::u16>(std::numeric_limits<ql::u8>::min());
  constexpr ql::u16 u8_max_u16
    = static_cast<ql::u16>(std::numeric_limits<ql::u8>::max());

  constexpr ql::i16 i8_min_i16
    = static_cast<ql::i16>(std::numeric_limits<ql::i8>::min());
  constexpr ql::i16 i8_max_i16
    = static_cast<ql::i16>(std::numeric_limits<ql::i8>::max());
  constexpr ql::i16 u8_min_i16
    = static_cast<ql::i16>(std::numeric_limits<ql::u8>::min());
  constexpr ql::i16 u8_max_i16
    = static_cast<ql::i16>(std::numeric_limits<ql::u8>::max());

  constexpr ql::size size_min = std::numeric_limits<ql::size>::min();
  constexpr ql::size size_max = std::numeric_limits<ql::size>::max();

  constexpr ql::isize isize_min = std::numeric_limits<ql::isize>::min();
  constexpr ql::isize isize_max = std::numeric_limits<ql::isize>::max();

  constexpr ql::f64 f64_epsilon = std::numeric_limits<ql::f64>::epsilon();
  constexpr ql::f64 f32_epsilon = std::numeric_limits<ql::f32>::epsilon();

  constexpr ql::size f64_digits = std::numeric_limits<ql::f64>::max_digits10;
  constexpr ql::size f32_digits = std::numeric_limits<ql::f32>::max_digits10;

  constexpr ql::f64 pi = 3.141592653589793238462;
  constexpr ql::f32 pi_32 = static_cast<ql::f32>(ql::pi);
  constexpr ql::f64 sqrt1_2 = 0.707106781186547524401;
  constexpr ql::f32 sqrt1_2_32 = static_cast<ql::f32>(ql::sqrt1_2);
  constexpr ql::f64 e = 2.718281828459045235360;
  constexpr ql::f32 e_32 = static_cast<ql::f32>(ql::e);
  constexpr ql::f64 ln2 = 0.69314718055994530941;
  constexpr ql::f32 log2_32 = static_cast<ql::f32>(ql::ln2);
  constexpr ql::f64 ln10 = 2.30258509299404568402;
  constexpr ql::f32 log10_32 = static_cast<ql::f32>(ql::ln10);

  constexpr ql::f64 f64_lower_bound10 = 9.99999999999999822;

  constexpr ql::size f32_mantissa_size()
  {
    return 23;
  }

  constexpr ql::size f32_exponent_size()
  {
    return 8;
  }

  constexpr ql::size f64_mantissa_size()
  {
    return 52;
  }

  constexpr ql::size f64_exponent_size()
  {
    return 11;
  }
}