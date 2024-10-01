#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/compare/compare.hpp>
#include <ql/core/type/arithmetic/is-arithmetic.hpp>
#include <ql/core/type/arithmetic/bit-count-of-max-value.hpp>

namespace ql
{
	template <class F>
	constexpr ql::size mantissa_bit_size()
	{
		if constexpr (ql::is_stl_floating_point<F>())
		{
			if constexpr (ql::is_same<F, float>())
			{
				return ql::f32_mantissa_size();
			}
			else if constexpr (ql::is_same<F, double>())
			{
				return ql::f64_mantissa_size();
			}
		}
		else if constexpr (ql::is_ql_floating_point<F>())
		{
			return F::mantissa_bit_size();
		}
		else
		{
			return 0;
		}
	}

	template <class F>
	constexpr ql::size exponent_bit_size()
	{
		if constexpr (ql::is_stl_floating_point<F>())
		{
			if constexpr (ql::is_same<F, float>())
			{
				return ql::f32_exponent_size();
			}
			else if constexpr (ql::is_same<F, double>())
			{
				return ql::f64_exponent_size();
			}
		}
		else if constexpr (ql::is_ql_floating_point<F>())
		{
			return F::exponent_bit_size();
		}
		else
		{
			return 0;
		}
	}

	template <class i1, class i2>
	using superior_floating_point = ql::conditional<
			ql::if_true<(ql::mantissa_bit_size<i2>() > ql::mantissa_bit_size<i1>())>,
			i2,
			ql::if_true<(ql::mantissa_bit_size<i1>() > ql::mantissa_bit_size<i2>())>,
			i1,
			ql::if_true<(ql::exponent_bit_size<i2>() > ql::exponent_bit_size<i1>())>,
			i2,
			i1>;

	template <class i1, class i2>
	using superior_integer = ql::conditional<ql::if_true<(i2::used_bit_size() > i1::used_bit_size())>, i2, i1>;

	template <class i1, class i2>
	using superior_dynamic_integer = ql::conditional<ql::if_true<i2::optimal_base()>, i2, i1>;

	namespace detail
	{
		// struct superior_arithmetic_type;
		template <typename T, typename U>
		using superior_arithmetic_type = typename ql::conditional<
				ql::if_true<(ql::is_floating_point<T>() && ql::is_floating_point<U>())>,
				ql::superior_floating_point<T, U>,
				ql::if_true<(ql::is_floating_point<T>())>,
				T,
				ql::if_true<(ql::is_floating_point<U>())>,
				U,
				ql::if_true<(ql::bit_count_of_max_value<T>() < ql::bit_count_of_max_value<U>())>,
				U,
				T>;

		template <typename T1>
		constexpr auto superior_arithmetic_types()
		{
			return ql::declval<T1>();
		}

		template <typename T1, typename T2>
		constexpr auto superior_arithmetic_types()
		{
			return ql::declval<superior_arithmetic_type<T1, T2>>();
		}

		template <typename T1, typename T2, typename T3, typename... Ts>
		constexpr auto superior_arithmetic_types()
		{
			return superior_arithmetic_types<
					decltype(superior_arithmetic_types<T1, T2>()), decltype(superior_arithmetic_types<T3, Ts...>())>();
		}
	}	 // namespace detail

	template <typename... Ts>
	using superior_arithmetic_type = decltype(detail::superior_arithmetic_types<Ts...>());

	template <typename T, typename U>
	using promote_superior_type_classic = ql::conditional<
			ql::if_true<(ql::bytes_in_type<T>() == 8u || ql::bytes_in_type<U>() == 8u)>,
			ql::f64,
			ql::conditional<
					ql::if_true<(ql::is_floating_point<ql::superior_arithmetic_type<T, U>>())>,
					ql::superior_arithmetic_type<T, U>,
					ql::conditional<
							ql::if_true<(ql::bit_count_of_max_value<ql::superior_arithmetic_type<T, U>>() < ql::bit_count_of_max_value<ql::i16>())>,
							std::conditional_t<ql::is_signed<ql::superior_arithmetic_type<T, U>>(), ql::i16, ql::u16>,
							ql::conditional<
									ql::if_true<
											(ql::bit_count_of_max_value<ql::superior_arithmetic_type<T, U>>() < ql::bit_count_of_max_value<ql::i32>())>,
									std::conditional_t<ql::is_signed<ql::superior_arithmetic_type<T, U>>(), ql::i32, ql::u32>,
									ql::conditional<
											ql::if_true<
													(ql::bit_count_of_max_value<ql::superior_arithmetic_type<T, U>>() < ql::bit_count_of_max_value<ql::i64>())>,
											std::conditional_t<ql::is_signed<ql::superior_arithmetic_type<T, U>>(), ql::i64, ql::u64>,
											ql::default_type,
											ql::f64>>>>>;

	template <typename T, typename U, typename R = promote_superior_type_classic<T, U>>
	constexpr R safe_addition(T a, U b)
	{
		return static_cast<R>(a) + static_cast<R>(b);
	}

	template <typename T, typename U, typename R = promote_superior_type_classic<T, U>>
	constexpr R safe_multiplication(T a, U b)
	{
		return static_cast<R>(a) * static_cast<R>(b);
	}
}	 // namespace ql