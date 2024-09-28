#pragma once

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/tuple/is-tuple.hpp>
#include <ql/core/type/tuple/value.hpp>

#include <array>

namespace ql
{
	template <typename T, ql::size N>
	constexpr auto array_to_tuple(const std::array<T, N>& array)
	{
		return ql::constexpr_apply<N>([&](auto i) { return array[i]; });
	}
}	 // namespace ql

constexpr auto test = ql::array_to_tuple(std::array{1, 2, 3});