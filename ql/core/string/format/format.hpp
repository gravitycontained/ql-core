#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/string/format/options.hpp>

#include <ql/core/type/type.hpp>

#include <ql/core/string/to-string.hpp>

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

	template <typename T>
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

	template <typename T>
	std::string string_repeat(T&& value, ql::size repeat)
	{
		if (repeat > ql::size_cast(1e12))
		{
			return "";
		}
		std::ostringstream stream;
		for (auto i = ql::size{}; i < repeat; ++i)
		{
			stream << value;
		}
		return stream.str();
	}

	// format is like (a, b)
	template <typename... Args>
	requires (ql::is_printable<Args...>())
	std::string to_string_format(std::string_view format, Args&&... args)
	{
		std::ostringstream stream;

		ql::size open_i = 0u;
		std::string_view open;
		std::string_view close;
		std::string_view delimiter;
		for (ql::size i = 0u; i < format.length(); ++i)
		{
			if (format[i] == 'a')
			{
				open = format.substr(0u, i);
				open_i = i;
			}
			if (format[i] == 'b')
			{
				if (i)
				{
					delimiter = format.substr(open_i + 1, i - open_i - 1);
					if (i != format.length() - 1)
					{
						close = format.substr(i + 1);
					}
				}
			}
		}

		bool first = true;
		auto add_to_stream = [&]<typename T>(T value)
		{
			if constexpr (ql::is_container<T>() && !ql::is_long_string_type<T>())
			{
				stream << open;
				bool first = true;
				for (auto& i : value)
				{
					if (!first)
					{
						stream << delimiter;
					}
					stream << ql::to_string_format(format, i);
					first = false;
				}
			}
			else if constexpr (ql::is_tuple<T>())
			{
				stream << open;
				if constexpr (ql::tuple_size<T>() > 1)
				{
					auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
					{ ((stream << ql::to_string_format(format, std::get<Ints>(value)) << delimiter), ...); };
					unpack(std::make_index_sequence<ql::tuple_size<T>() - 1>());
				}
				stream << ql::to_string_format(format, ql::tuple_value_back(value));
			}
			else
			{
				if (!first)
				{
					stream << delimiter;
				}
				else
				{
					stream << open;
				}
				first = false;
				stream << value;
			}
		};

		(add_to_stream(args), ...);
		stream << close;

		return stream.str();
	}

}	 // namespace ql