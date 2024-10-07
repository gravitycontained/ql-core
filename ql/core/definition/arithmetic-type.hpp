#pragma once

#include <cstdint>
#include <tuple>
#include <limits>
#include <string>

namespace ql
{
	using size = std::size_t;
	using isize = std::conditional_t<sizeof(std::size_t) == 8u, std::int64_t, std::int32_t>;

	using i8 = std::int8_t;
	using u8 = std::uint8_t;

	using i16 = std::int16_t;
	using u16 = std::uint16_t;

	using i32 = std::int32_t;
	using u32 = std::uint32_t;

	template <ql::u32 base, bool sign>
	struct dynamic_integer;
	template <ql::size bits, bool sign>
	struct integer;
	template <ql::size bits, bool sign>
	struct x64_integer;
	template <typename E>
	struct big_float_t;

#ifndef ql_NO_FLOATS
	template <ql::size exponent_bits, ql::size mantissa_bits>
	struct floating_point;
#endif

	using ii32 = ql::integer<32, 1>;
	using uu32 = ql::integer<32, 0>;

	using i64 = std::int64_t;
	using u64 = std::uint64_t;

	using ii64 = ql::integer<64, 1>;
	using uu64 = ql::integer<64, 0>;

	using i96 = ql::integer<96, 1>;
	using u96 = ql::integer<96, 1>;

	using i128 = ql::integer<128, 1>;
	using u128 = ql::integer<128, 0>;

	using i160 = ql::integer<160, 1>;
	using u160 = ql::integer<160, 0>;

	using i192 = ql::integer<192, 1>;
	using u192 = ql::integer<192, 0>;

	using i256 = ql::integer<256, 1>;
	using u256 = ql::integer<256, 0>;

	using i320 = ql::integer<320, 1>;
	using u320 = ql::integer<320, 0>;

	using i512 = ql::integer<512, 1>;
	using u512 = ql::integer<512, 0>;

	using i640 = ql::integer<640, 1>;
	using u640 = ql::integer<640, 0>;

	using i768 = ql::integer<768, 1>;
	using u768 = ql::integer<768, 0>;

	using i1024 = ql::integer<1024, 1>;
	using u1024 = ql::integer<1024, 0>;

	using i2048 = ql::integer<2048, 1>;
	using u2048 = ql::integer<2048, 0>;

	using i4096 = ql::integer<4096, 1>;
	using u4096 = ql::integer<4096, 0>;

	using i8192 = ql::integer<8192, 1>;
	using u8192 = ql::integer<8192, 0>;

	using i10240 = ql::integer<10240, 1>;
	using u10240 = ql::integer<10240, 0>;

	using i20480 = ql::integer<20480, 1>;
	using u20480 = ql::integer<20480, 0>;

	using i32768 = ql::integer<32768, 1>;
	using u32768 = ql::integer<32768, 0>;

	using i65536 = ql::integer<65536, 1>;
	using u65536 = ql::integer<65536, 0>;

	using i102400 = ql::integer<102400, 1>;
	using u102400 = ql::integer<102400, 0>;

	using i204800 = ql::integer<204800, 1>;
	using u204800 = ql::integer<204800, 0>;

	using ux128 = ql::x64_integer<128, 0>;
	using ix128 = ql::x64_integer<128, 1>;

	using ux192 = ql::x64_integer<192, 0>;
	using ix192 = ql::x64_integer<192, 1>;

	using ux256 = ql::x64_integer<256, 0>;
	using ix256 = ql::x64_integer<256, 1>;

	using ux320 = ql::x64_integer<320, 0>;
	using ix320 = ql::x64_integer<320, 1>;

	using ux512 = ql::x64_integer<512, 0>;
	using ix512 = ql::x64_integer<512, 1>;

	using ux768 = ql::x64_integer<768, 0>;
	using ix768 = ql::x64_integer<768, 1>;

	using ux1024 = ql::x64_integer<1024, 0>;
	using ix1024 = ql::x64_integer<1024, 1>;

	using ux2048 = ql::x64_integer<2048, 0>;
	using ix2048 = ql::x64_integer<2048, 1>;

	using ux4096 = ql::x64_integer<4096, 0>;
	using ix4096 = ql::x64_integer<4096, 1>;

	using ux8192 = ql::x64_integer<8192, 0>;
	using ix8192 = ql::x64_integer<8192, 1>;

	using ix10240 = ql::x64_integer<10240, 1>;
	using ux10240 = ql::x64_integer<10240, 0>;

	using ix20480 = ql::x64_integer<20480, 1>;
	using ux20480 = ql::x64_integer<20480, 0>;

	using ix32768 = ql::x64_integer<65536, 1>;
	using ux32768 = ql::x64_integer<65536, 0>;

	using ix65536 = ql::x64_integer<65536, 1>;
	using ux65536 = ql::x64_integer<65536, 0>;

	using ix102400 = ql::x64_integer<102400, 1>;
	using ux102400 = ql::x64_integer<102400, 0>;

	using ix204800 = ql::x64_integer<204800, 1>;
	using ux204800 = ql::x64_integer<204800, 0>;

	template <ql::u32 base>
	using ubase = ql::dynamic_integer<base, 0>;
	template <ql::u32 base>
	using ibase = ql::dynamic_integer<base, 1>;

	using u = ql::dynamic_integer<10u, 0>;
	using i = ql::dynamic_integer<10u, 1>;

	using ub = ql::dynamic_integer<2u, 0>;
	using ib = ql::dynamic_integer<2u, 1>;

	using uh = ql::dynamic_integer<16u, 0>;
	using ih = ql::dynamic_integer<16u, 1>;

	using itypes = std::tuple<ql::i8, ql::i16, ql::i32, ql::i64>;
	using itype_min = std::tuple_element_t<0, itypes>;
	using itype_max = std::tuple_element_t<std::tuple_size_v<itypes> - 1, itypes>;

	using utypes = std::tuple<ql::u8, ql::u16, ql::u32, ql::u64>;
	using utype_min = std::tuple_element_t<0, utypes>;
	using utype_max = std::tuple_element_t<std::tuple_size_v<utypes> - 1, utypes>;

	using f32 = float;
	using f64 = double;

#ifndef ql_NO_FLOATS
	using ff32 = ql::floating_point<32u, 32u>;
	using ff64 = ql::floating_point<32u, 64u>;
	using f128 = ql::floating_point<32u, 128u>;
	using f256 = ql::floating_point<32u, 256u>;
	using f512 = ql::floating_point<32u, 512u>;
	using f768 = ql::floating_point<32u, 768u>;
	using f1024 = ql::floating_point<32u, 1024u>;
	using f2048 = ql::floating_point<32u, 2048u>;
	using f2560 = ql::floating_point<32u, 2560u>;
	using f4096 = ql::floating_point<32u, 4096u>;
	using f5120 = ql::floating_point<32u, 5120u>;
	using f8192 = ql::floating_point<32u, 8192u>;
	using f10240 = ql::floating_point<32u, 10240u>;
	using f16384 = ql::floating_point<32u, 16384u>;
	using f32768 = ql::floating_point<32u, 32768u>;
#endif

	using xf32 = ql::big_float_t<ql::i32>;
	using xf64 = ql::big_float_t<ql::i64>;
	using xf128 = ql::big_float_t<ql::i128>;
	using xf192 = ql::big_float_t<ql::i192>;
	using xf256 = ql::big_float_t<ql::i256>;

	using ftypes = std::tuple<ql::f32, ql::f64>;
	using ftype_min = std::tuple_element_t<0, ftypes>;
	using ftype_max = std::tuple_element_t<std::tuple_size_v<ftypes> - 1, ftypes>;

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

	constexpr ql::f64 i8_min_f64 = static_cast<ql::f64>(std::numeric_limits<ql::i8>::min());
	constexpr ql::f64 i8_max_f64 = static_cast<ql::f64>(std::numeric_limits<ql::i8>::max());
	constexpr ql::f64 u8_min_f64 = static_cast<ql::f64>(std::numeric_limits<ql::u8>::min());
	constexpr ql::f64 u8_max_f64 = static_cast<ql::f64>(std::numeric_limits<ql::u8>::max());

	constexpr ql::f64 i16_min_f64 = static_cast<ql::f64>(std::numeric_limits<ql::i16>::min());
	constexpr ql::f64 i16_max_f64 = static_cast<ql::f64>(std::numeric_limits<ql::i16>::max());
	constexpr ql::f64 u16_min_f64 = static_cast<ql::f64>(std::numeric_limits<ql::u16>::min());
	constexpr ql::f64 u16_max_f64 = static_cast<ql::f64>(std::numeric_limits<ql::u16>::max());

	constexpr ql::f64 i32_min_f64 = static_cast<ql::f64>(std::numeric_limits<ql::i32>::min());
	constexpr ql::f64 i32_max_f64 = static_cast<ql::f64>(std::numeric_limits<ql::i32>::max());
	constexpr ql::f64 u32_min_f64 = static_cast<ql::f64>(std::numeric_limits<ql::u32>::min());
	constexpr ql::f64 u32_max_f64 = static_cast<ql::f64>(std::numeric_limits<ql::u32>::max());

	constexpr ql::f64 i64_min_f64 = static_cast<ql::f64>(std::numeric_limits<ql::i64>::min());
	constexpr ql::f64 i64_max_f64 = static_cast<ql::f64>(std::numeric_limits<ql::i64>::max());
	constexpr ql::f64 u64_min_f64 = static_cast<ql::f64>(std::numeric_limits<ql::u64>::min());
	constexpr ql::f64 u64_max_f64 = static_cast<ql::f64>(std::numeric_limits<ql::u64>::max());

	constexpr ql::f64 f32_min_f64 = static_cast<ql::f64>(std::numeric_limits<ql::f32>::min());
	constexpr ql::f64 f32_max_f64 = static_cast<ql::f64>(std::numeric_limits<ql::f32>::max());

	constexpr ql::f32 i8_min_f32 = static_cast<ql::f32>(std::numeric_limits<ql::i8>::min());
	constexpr ql::f32 i8_max_f32 = static_cast<ql::f32>(std::numeric_limits<ql::i8>::max());
	constexpr ql::f32 u8_min_f32 = static_cast<ql::f32>(std::numeric_limits<ql::u8>::min());
	constexpr ql::f32 u8_max_f32 = static_cast<ql::f32>(std::numeric_limits<ql::u8>::max());

	constexpr ql::f32 i16_min_f32 = static_cast<ql::f32>(std::numeric_limits<ql::i16>::min());
	constexpr ql::f32 i16_max_f32 = static_cast<ql::f32>(std::numeric_limits<ql::i16>::max());
	constexpr ql::f32 u16_min_f32 = static_cast<ql::f32>(std::numeric_limits<ql::u16>::min());
	constexpr ql::f32 u16_max_f32 = static_cast<ql::f32>(std::numeric_limits<ql::u16>::max());

	constexpr ql::f32 i32_min_f32 = static_cast<ql::f32>(std::numeric_limits<ql::i32>::min());
	constexpr ql::f32 i32_max_f32 = static_cast<ql::f32>(std::numeric_limits<ql::i32>::max());
	constexpr ql::f32 u32_min_f32 = static_cast<ql::f32>(std::numeric_limits<ql::u32>::min());
	constexpr ql::f32 u32_max_f32 = static_cast<ql::f32>(std::numeric_limits<ql::u32>::max());

	constexpr ql::f32 i64_min_f32 = static_cast<ql::f32>(std::numeric_limits<ql::i64>::min());
	constexpr ql::f32 i64_max_f32 = static_cast<ql::f32>(std::numeric_limits<ql::i64>::max());
	constexpr ql::f32 u64_min_f32 = static_cast<ql::f32>(std::numeric_limits<ql::u64>::min());
	constexpr ql::f32 u64_max_f32 = static_cast<ql::f32>(std::numeric_limits<ql::u64>::max());

	constexpr ql::u64 i8_min_u64 = static_cast<ql::u64>(std::numeric_limits<ql::i8>::min());
	constexpr ql::u64 i8_max_u64 = static_cast<ql::u64>(std::numeric_limits<ql::i8>::max());
	constexpr ql::u64 u8_min_u64 = static_cast<ql::u64>(std::numeric_limits<ql::u8>::min());
	constexpr ql::u64 u8_max_u64 = static_cast<ql::u64>(std::numeric_limits<ql::u8>::max());

	constexpr ql::u64 i16_min_u64 = static_cast<ql::u64>(std::numeric_limits<ql::i16>::min());
	constexpr ql::u64 i16_max_u64 = static_cast<ql::u64>(std::numeric_limits<ql::i16>::max());
	constexpr ql::u64 u16_min_u64 = static_cast<ql::u64>(std::numeric_limits<ql::u16>::min());
	constexpr ql::u64 u16_max_u64 = static_cast<ql::u64>(std::numeric_limits<ql::u16>::max());

	constexpr ql::u64 i32_min_u64 = static_cast<ql::u64>(std::numeric_limits<ql::i32>::min());
	constexpr ql::u64 i32_max_u64 = static_cast<ql::u64>(std::numeric_limits<ql::i32>::max());
	constexpr ql::u64 u32_min_u64 = static_cast<ql::u64>(std::numeric_limits<ql::u32>::min());
	constexpr ql::u64 u32_max_u64 = static_cast<ql::u64>(std::numeric_limits<ql::u32>::max());

	constexpr ql::u64 f32_min_u64 = static_cast<ql::u64>(std::numeric_limits<ql::f32>::min());
	constexpr ql::u64 f64_min_u64 = static_cast<ql::u64>(std::numeric_limits<ql::f64>::min());

	constexpr ql::i64 i8_min_i64 = static_cast<ql::i64>(std::numeric_limits<ql::i8>::min());
	constexpr ql::i64 i8_max_i64 = static_cast<ql::i64>(std::numeric_limits<ql::i8>::max());
	constexpr ql::i64 u8_min_i64 = static_cast<ql::i64>(std::numeric_limits<ql::u8>::min());
	constexpr ql::i64 u8_max_i64 = static_cast<ql::i64>(std::numeric_limits<ql::u8>::max());

	constexpr ql::i64 i16_min_i64 = static_cast<ql::i64>(std::numeric_limits<ql::i16>::min());
	constexpr ql::i64 i16_max_i64 = static_cast<ql::i64>(std::numeric_limits<ql::i16>::max());
	constexpr ql::i64 u16_min_i64 = static_cast<ql::i64>(std::numeric_limits<ql::u16>::min());
	constexpr ql::i64 u16_max_i64 = static_cast<ql::i64>(std::numeric_limits<ql::u16>::max());

	constexpr ql::i64 i32_min_i64 = static_cast<ql::i64>(std::numeric_limits<ql::i32>::min());
	constexpr ql::i64 i32_max_i64 = static_cast<ql::i64>(std::numeric_limits<ql::i32>::max());
	constexpr ql::i64 u32_min_i64 = static_cast<ql::i64>(std::numeric_limits<ql::u32>::min());
	constexpr ql::i64 u32_max_i64 = static_cast<ql::i64>(std::numeric_limits<ql::u32>::max());

	constexpr ql::i64 f32_min_i64 = static_cast<ql::i64>(std::numeric_limits<ql::f32>::min());
	constexpr ql::i64 f64_min_i64 = static_cast<ql::i64>(std::numeric_limits<ql::f64>::min());

	constexpr ql::u32 i8_min_u32 = static_cast<ql::u32>(std::numeric_limits<ql::i8>::min());
	constexpr ql::u32 i8_max_u32 = static_cast<ql::u32>(std::numeric_limits<ql::i8>::max());
	constexpr ql::u32 u8_min_u32 = static_cast<ql::u32>(std::numeric_limits<ql::u8>::min());
	constexpr ql::u32 u8_max_u32 = static_cast<ql::u32>(std::numeric_limits<ql::u8>::max());

	constexpr ql::u32 i16_min_u32 = static_cast<ql::u32>(std::numeric_limits<ql::i16>::min());
	constexpr ql::u32 i16_max_u32 = static_cast<ql::u32>(std::numeric_limits<ql::i16>::max());
	constexpr ql::u32 u16_min_u32 = static_cast<ql::u32>(std::numeric_limits<ql::u16>::min());
	constexpr ql::u32 u16_max_u32 = static_cast<ql::u32>(std::numeric_limits<ql::u16>::max());

	constexpr ql::i32 i8_min_i32 = static_cast<ql::i32>(std::numeric_limits<ql::i8>::min());
	constexpr ql::i32 i8_max_i32 = static_cast<ql::i32>(std::numeric_limits<ql::i8>::max());
	constexpr ql::i32 u8_min_i32 = static_cast<ql::i32>(std::numeric_limits<ql::u8>::min());
	constexpr ql::i32 u8_max_i32 = static_cast<ql::i32>(std::numeric_limits<ql::u8>::max());

	constexpr ql::i32 i16_min_i32 = static_cast<ql::i32>(std::numeric_limits<ql::i16>::min());
	constexpr ql::i32 i16_max_i32 = static_cast<ql::i32>(std::numeric_limits<ql::i16>::max());
	constexpr ql::i32 u16_min_i32 = static_cast<ql::i32>(std::numeric_limits<ql::u16>::min());
	constexpr ql::i32 u16_max_i32 = static_cast<ql::i32>(std::numeric_limits<ql::u16>::max());

	constexpr ql::u16 i8_min_u16 = static_cast<ql::u16>(std::numeric_limits<ql::i8>::min());
	constexpr ql::u16 i8_max_u16 = static_cast<ql::u16>(std::numeric_limits<ql::i8>::max());
	constexpr ql::u16 u8_min_u16 = static_cast<ql::u16>(std::numeric_limits<ql::u8>::min());
	constexpr ql::u16 u8_max_u16 = static_cast<ql::u16>(std::numeric_limits<ql::u8>::max());

	constexpr ql::i16 i8_min_i16 = static_cast<ql::i16>(std::numeric_limits<ql::i8>::min());
	constexpr ql::i16 i8_max_i16 = static_cast<ql::i16>(std::numeric_limits<ql::i8>::max());
	constexpr ql::i16 u8_min_i16 = static_cast<ql::i16>(std::numeric_limits<ql::u8>::min());
	constexpr ql::i16 u8_max_i16 = static_cast<ql::i16>(std::numeric_limits<ql::u8>::max());

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
}	 // namespace ql