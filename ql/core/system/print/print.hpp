#pragma once

#include <iostream>

#include <ql/core/string/string.hpp>
#include <ql/core/type/string/string.hpp>
#include <ql/core/advanced-type/color/print-color.hpp>

#include <ql/core/definition/definition.hpp>

namespace ql
{
	namespace detail
	{
		QL_SOURCE extern bool printed_color;
	}

	template <typename T>
	requires (ql::is_printable<T>())
	void single_print(const T& value)
	{
		if constexpr (ql::is_same<T, ql::print_color>())
		{
			ql::detail::printed_color = true;
			std::cout << ql::to_termcolor(value);
			return;
		}
		else
		{
			auto string = ql::to_string(value);

			if constexpr (ql::is_same<decltype(string), std::string>())
			{
				std::fwrite(string.data(), sizeof(string[0]) * string.size(), 1, stderr);
			}
			else if constexpr (ql::is_same<decltype(string), std::wstring>())
			{
				std::fwprintf(stderr, L"%ls", string.data());
			}
			else
			{
				static_assert(true, "Unknown string type");
			}

			if (ql::detail::printed_color)
			{
				ql::single_print(ql::reset);
				ql::detail::printed_color = false;
			}
		}
	}

	template <typename... Args>
	requires (ql::is_printable<Args...>())
	void print(Args&&... args)
	{
		(ql::single_print(std::forward<Args>(args)), ...);
	}

	template <typename... Args>
	requires (ql::is_printable<Args...>())
	void println(Args&&... args)
	{
		ql::print(std::forward<Args>(args)...);
		std::fputc('\n', stderr);
	}
}	 // namespace ql