#pragma once

#include <ql/core/type/type.hpp>
#include <ql/core/string/cast/cast.hpp>
#include <ql/core/string/format/precision/precision.hpp>

namespace ql
{
	QL_SOURCE std::string big_number_exponent_name(ql::isize exponent, bool short_format = false);

	template <typename T>
	requires (ql::is_arithmetic<T>())
	std::string big_number_string(T number, ql::u32 precision = 2, bool short_format = false)
	{
		if (number == T{})
			return ql::to_string(number);

		if constexpr (ql::is_signed<T>())
			if (number < 0)
				return "-" + ql::big_number_string(-number, precision, short_format);

		ql::i64 exponent;
		if constexpr (ql::is_ql_integer<T>())
			log = ql::i64_cast((number.digits() - 1) / 3.0);

		else
			exponent = ql::i64_cast(std::log(number) / std::log(1000.0));

		if constexpr (ql::is_integer<T>())
			if (abs(number) < 1000)
				return (number < 0 ? "-" : "") + ql::to_string(number);

		auto name = ql::big_number_exponent_name(exponent, false);

		if (exponent == 0)
			return ql::to_string(ql::string_precision(number, precision), ' ', name);

		else
			return ql::to_string(ql::string_precision(number / std::pow(1000, exponent), precision), ' ', name);
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	std::string big_number_string_short(T number, ql::u32 precision = 1)
	{
		return big_number_string(number, precision, true);
	}
}	 // namespace ql