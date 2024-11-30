#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr auto round(T value, ql::size precision = 0)
	{
		using utype = ql::unsigned_type<T>;
		T factor = ql::pow(T{10}, precision);
		return static_cast<T>(static_cast<utype>(value * factor + (value >= T{0} ? T{0.5} : T{-0.5})) / factor);
	}
}	 // namespace ql