#pragma once

#include <ql/definition/definition.hpp>

#include <ql/type-traits/size/size.hpp>
#include <ql/type-traits/conditional.hpp>

namespace ql
{

#ifndef ql_NO_FLOATS
	template <ql::size exponent_bits, ql::size mantissa_bits>
	struct floating_point;
#endif

	template <typename T>
	struct is_ql_integer_impl : std::false_type
	{
	};

	template <ql::size bits, bool sign>
	struct is_ql_integer_impl<ql::integer<bits, sign>> : std::true_type
	{
	};

	template <typename T>
	constexpr bool is_ql_integer()
	{
		return is_ql_integer_impl<T>{};
	}

	template <typename T>
	struct is_ql_integer_signed_impl : std::false_type
	{
	};

	template <ql::size bits>
	struct is_ql_integer_signed_impl<ql::integer<bits, true>> : std::true_type
	{
	};

	template <typename T>
	constexpr bool is_ql_integer_signed()
	{
		return is_ql_integer_signed_impl<T>{};
	}
#ifndef ql_NO_FLOATS
	template <typename T>
	struct is_ql_floating_point_impl : std::false_type
	{
	};

	template <ql::size exponent_bits, ql::size mantissa_bits>
	struct is_ql_floating_point_impl<
			ql::floating_point<exponent_bits, mantissa_bits>> : std::true_type
	{
	};

	template <typename T>
	constexpr bool is_ql_floating_point()
	{
		return is_ql_floating_point_impl<T>{};
	}
#else

	template <typename T>
	constexpr bool is_ql_floating_point()
	{
		return false;
	}
#endif

	template <typename T>
	struct is_ql_dynamic_integer_impl : std::false_type
	{
	};

	template <ql::u32 base, bool sign>
	struct is_ql_dynamic_integer_impl<ql::dynamic_integer<base, sign>>
			: std::true_type
	{
	};

	template <typename T>
	constexpr bool is_ql_dynamic_integer()
	{
		return is_ql_dynamic_integer_impl<T>{};
	}

	template <typename T>
	constexpr bool is_ql_arithmetic()
	{
		return is_ql_dynamic_integer<T>() || is_ql_integer<T>() ||
					 is_ql_floating_point<T>();
	}

#ifdef ql_USE_INTRINSICS
	template <ql::size bits, bool sign>
	struct x64_integer;

	template <typename T>
	struct is_ql_x64_integer_impl : std::false_type
	{
	};

	template <ql::size bits, bool sign>
	struct is_ql_x64_integer_impl<ql::x64_integer<bits, sign>> : std::true_type
	{
	};

	template <typename T>
	constexpr bool is_ql_x64_integer()
	{
		return is_ql_x64_integer_impl<T>{};
	}
#endif

	template <typename T>
	struct is_ql_x64_integer_signed_impl : std::false_type
	{
	};

	template <ql::size bits>
	struct is_ql_x64_integer_signed_impl<ql::x64_integer<bits, true>>
			: std::true_type
	{
	};

	template <typename T>
	constexpr bool is_ql_x64_integer_signed()
	{
		return is_ql_x64_integer_signed_impl<T>{};
	}

	template <typename T>
	constexpr bool is_stl_arithmetic()
	{
		return std::is_arithmetic_v<T>;
	}

#ifdef QL_USE_INTRINSICS
	template <typename T>
	constexpr bool is_arithmetic()
	{
		return std::is_arithmetic_v<T> || is_ql_integer<T>() ||
					 is_ql_floating_point<T>() || is_ql_x64_integer<T>();
	}

	template <typename T>
	constexpr bool is_integer()
	{
		return std::numeric_limits<T>::is_integer || ql::is_ql_integer<T>() ||
					 is_ql_x64_integer<T>();
	}

	template <typename T>
	constexpr bool is_unsigned()
	{
		return !std::numeric_limits<T>::is_signed || !is_ql_integer_signed<T>() ||
					 !is_ql_x64_integer_signed<T>();
	}

	template <typename T>
	constexpr bool is_signed()
	{
		return std::numeric_limits<T>::is_signed || is_ql_integer_signed<T>() ||
					 is_ql_x64_integer_signed<T>();
	}
#else
	template <typename T>
	constexpr bool is_arithmetic()
	{
		return std::is_arithmetic_v<T> || is_ql_integer<T>() ||
					 is_ql_floating_point<T>();
	}

	template <typename T>
	constexpr bool is_stl_integer()
	{
		return std::numeric_limits<T>::is_integer;
	}

	template <typename T>
	constexpr bool is_integer()
	{
		return std::numeric_limits<T>::is_integer || ql::is_ql_integer<T>();
	}

	template <typename T>
	constexpr bool is_stl_floating_point()
	{
		return std::is_floating_point_v<T>;
	}

	template <typename T>
	constexpr bool is_floating_point()
	{
		return std::is_floating_point_v<T> || is_ql_floating_point<T>();
	}

	template <typename T>
	constexpr bool is_unsigned()
	{
		return !std::numeric_limits<T>::is_signed || !is_ql_integer_signed<T>();
	}

	template <typename T>
	constexpr bool is_signed()
	{
		return std::numeric_limits<T>::is_signed || is_ql_integer_signed<T>();
	}

#endif

	template <typename T>
	using signed_type = ql::conditional<
			ql::if_true<ql::is_arithmetic<ql::decay<T>>()>,
			ql::conditional<ql::if_true<ql::bits_in_type<T>() == std::size_t{8}>,
											ql::i8,
											ql::if_true<ql::bits_in_type<T>() == std::size_t{16}>,
											ql::i16,
											ql::if_true<ql::bits_in_type<T>() == std::size_t{32}>,
											ql::i32,
											ql::if_true<ql::bits_in_type<T>() == std::size_t{64}>,
											ql::i64,
											ql::default_error>,
			ql::default_error>;

	template <typename T>
	using unsigned_type = ql::conditional<
			ql::if_true<ql::is_arithmetic<ql::decay_t<T>>()>,
			ql::conditional<ql::if_true<ql::bits_in_type<T>() == std::size_t{8}>,
											ql::u8,
											ql::if_true<ql::bits_in_type<T>() == std::size_t{16}>,
											ql::u16,
											ql::if_true<ql::bits_in_type<T>() == std::size_t{32}>,
											ql::u32,
											ql::if_true<ql::bits_in_type<T>() == std::size_t{64}>,
											ql::u64,
											ql::default_error>,
			ql::default_error>;

	template <typename T>
	using int_type = ql::conditional<
			ql::if_true<ql::is_arithmetic<ql::decay<T>>()>,
			ql::conditional<ql::if_true<ql::is_integer<T>()>,
											T,
											ql::if_true<ql::bits_in_type<T>() == std::size_t{32}>,
											ql::i32,
											ql::if_true<ql::bits_in_type<T>() == std::size_t{64}>,
											ql::i64,
											ql::default_error>,
			ql::default_error>;

	template <typename T>
	using float_type = ql::conditional<
			ql::if_true<ql::is_arithmetic<ql::decay<T>>()>,
			ql::conditional<ql::if_true<ql::is_floating_point<T>()>,
											T,
											ql::if_true<ql::bits_in_type<T>() <= std::size_t{32}>,
											ql::f32,
											ql::if_true<ql::bits_in_type<T>() == std::size_t{64}>,
											ql::f64,
											ql::default_error>,
			ql::default_error>;

	constexpr bool char_is_signed()
	{
		return (CHAR_MIN != 0);
	}

	constexpr bool char_is_unsigned()
	{
		return (CHAR_MIN == 0);
	}

	constexpr bool wchar_is_signed()
	{
		return (WCHAR_MIN != 0);
	}

	constexpr bool wchar_is_unsigned()
	{
		return (WCHAR_MIN == 0);
	}

	using char_type = ql::conditional<ql::if_true<ql::char_is_signed()>,
																		ql::i8,
																		ql::if_true<ql::char_is_unsigned()>,
																		ql::u8>;

	using wchar_type = wchar_t;

}	 // namespace ql