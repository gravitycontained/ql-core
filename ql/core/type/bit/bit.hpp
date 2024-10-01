#pragma once

#include <ql/core/type/arithmetic/is-arithmetic.hpp>
#include <ql/core/type/bit/type.hpp>
#include <ql/core/type/bit/size.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_integer<T>())
	constexpr T binary_configurations(T n)
	{
		return T{1} << n;
	}

	template <typename T>
	constexpr ql::size type_configurations()
	{
		return ql::binary_configurations<ql::size>(ql::bits_in_type<T>());
	}
}	 // namespace ql