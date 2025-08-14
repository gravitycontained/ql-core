#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/string/to-string.hpp>
#include <ql/core/type/type.hpp>

#include <iomanip>

namespace ql
{
	template <typename T>
	requires (ql::is_printable<T>())
	std::string string_precision(const T& value, ql::size precision)
	{
		std::ostringstream stream;
		stream << std::fixed << std::setprecision(precision) << ql::f64_cast(value);
		return stream.str();
	}

	template <typename T>
	requires (ql::is_printable<T>())
	std::string string_percentage_precision(const T& value, ql::size precision)
	{
		return ql::to_string(ql::string_precision(value * 100, precision), '%');
	}
	template <typename T>
	requires (ql::is_printable<T>())
	std::string string_percentage(const T& value)
	{
		return ql::string_percentage_precision(value, 2);
	}

}	 // namespace ql