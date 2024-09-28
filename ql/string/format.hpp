#pragma once


#include <ql/definition/definition.hpp>

#include <ql/type/type.hpp>

#include <ql/string/to-string.hpp>

#include <string>
#include <iomanip>

namespace ql
{
	QL_SOURCE std::string string_to_fit(const std::string& string, char append, ql::size length);

	namespace detail
	{
		QL_SOURCE std::string string_prepended(const std::string_view& string, char append, ql::size length);
		QL_SOURCE std::string string_prepended(const std::string_view& string, const std::string_view& prepend, ql::size length);

		QL_SOURCE std::string string_appended(const std::string_view& string, char append, ql::size length);
		QL_SOURCE std::string string_appended(const std::string_view& string, const std::string_view& append, ql::size length);
	}	 // namespace detail

	template<typename T>
	requires (ql::is_printable<T>())
	std::string string_prepended(const T& value, auto prepend, ql::size length)
	{
		return ql::detail::string_prepended(ql::to_string(value), prepend, length);
	}

	template <typename T>
	requires (ql::is_printable<T>())
	std::string string_appended(const T& value, auto append, ql::size length)
	{
		return ql::detail::string_appended(ql::to_string(value), append, length);
	}

	template <typename T>
	requires (ql::is_printable<T>())
	std::string string_left_spaced(const T& value, ql::size length)
	{
		return ql::string_appended(value, ' ', length);
	}

	template <typename T>
	requires (ql::is_printable<T>())
	std::string string_right_spaced(const T& value, ql::size length)
	{
		return ql::string_prepended(value, ' ', length);
	}

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
}	 // namespace ql