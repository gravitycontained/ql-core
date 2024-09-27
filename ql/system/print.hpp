#pragma once

#include <iostream>
#include <ql/type-traits/string/is-printable.hpp>

namespace ql
{
	template <typename T>
	requires(ql::is_printable<T>())
	void single_print(const T& value)
	{
		auto string = ql::to_string(value);

		if constexpr(ql::is_same<decltype(string), std::string>())
		{
			std::fwrite(string.data(), sizeof(string[0]) * string.size(), 1, stderr);
		}
		else if constexpr(ql::is_same<decltype(string), std::wstring>())
		{
			std::fwprintf(stderr, L"%ls", string.data());
		}
		else
		{
			static_assert(true, "Unknown string type");
		}
	}

	template <typename... Args>
	requires(ql::is_printable<Args...>())
	void print(Args&&... args)
	{
		(single_print(std::forward<Args>(args)), ...);
	}

	template <typename... Args>
	requires(ql::is_printable<Args...>())
	void println(Args&&... args)
	{
		ql::print(std::forward<Args>(args)...);
		std::fputc('\n', stderr);
	}
}	 // namespace ql