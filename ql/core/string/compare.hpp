#pragma once

#include <ql/core/definition/definition.hpp>

#include <string>

namespace ql
{

	constexpr bool string_equals_ignore_case(const std::string_view& a, const std::string_view& b)
	{
		if (a.size() != b.size())
		{
			return false;
		}
		for (ql::u32 i = 0u; i < a.size(); ++i)
		{
			if (std::tolower(a[i]) != std::tolower(b[i]))
			{
				return false;
			}
		}
		return true;
	}

	constexpr bool string_equals_ignore_case(const std::wstring_view& a, const std::wstring_view& b)
	{
		if (a.size() != b.size())
		{
			return false;
		}
		for (ql::u32 i = 0u; i < a.size(); ++i)
		{
			if (std::tolower(a[i]) != std::tolower(b[i]))
			{
				return false;
			}
		}
		return true;
	}

	constexpr bool string_ends_with(const std::string_view& string, const std::string_view& ending)
	{
		if (string.size() < ending.size())
		{
			return false;
		}
		return string.substr(string.size() - ending.size()) == ending;
	}
}