#pragma once

#include <ql/definition/definition.hpp>
#include <ql/type/conditional.hpp>
#include <ql/type/size/size.hpp>

namespace ql
{
	template <ql::size bits>
	using ubit = conditional
	<
		ql::if_true<(bits <= ql::bits_in_type<ql::u8>())>, ql::u8,
		ql::if_true<(bits <= ql::bits_in_type<ql::u16>())>, ql::u16,
		ql::if_true<(bits <= ql::bits_in_type<ql::u32>())>, ql::u32,
		ql::if_true<(bits <= ql::bits_in_type<ql::u64>())>, ql::u64,
		ql::default_type, ql::integer<bits, false>
	>;


	template <ql::size bits>
	using ibit = conditional
	<
		ql::if_true<(bits <= ql::bits_in_type<ql::i8>())>, ql::i8,
		ql::if_true<(bits <= ql::bits_in_type<ql::i16>())>, ql::i16,
		ql::if_true<(bits <= ql::bits_in_type<ql::i32>())>, ql::i32,
		ql::if_true<(bits <= ql::bits_in_type<ql::i64>())>, ql::i64,
		ql::default_type, ql::integer<bits, true>
	>;
	
	template <ql::size bits>
	using fbit = conditional
	<
		ql::if_true<(bits == ql::bits_in_type<ql::f32>())>, ql::f32,
		ql::if_true<(bits == ql::bits_in_type<ql::f64>())>, ql::f64,
		ql::default_type, ql::floating_point<32u, bits>
	>;
}	 // namespace ql