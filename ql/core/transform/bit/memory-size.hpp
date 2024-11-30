#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/arithmetic/arithmetic.hpp>
#include <ql/core/transform/cast/cast.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::u64 kilobyte(T n)
	{
		return ql::u64_cast(1000ull * n);
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::u64 kibibyte(T n)
	{
		return ql::u64_cast(0x400ull * n);
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::u64 megabyte(T n)
	{
		return ql::u64_cast(1000'000ull * n);
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::u64 mebibyte(T n)
	{
		return ql::u64_cast(0x100000ull * n);
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::u64 gigabyte(T n)
	{
		return ql::u64_cast(1000'000'000ull * n);
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::u64 gebibyte(T n)
	{
		return ql::u64_cast(0x40000000ull * n);
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::u64 terabyte(T n)
	{
		return ql::u64_cast(1'000'000'000'000ull * n);
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::u64 tebibyte(T n)
	{
		return ql::u64_cast(0x10000000000ull * n);
	}
}