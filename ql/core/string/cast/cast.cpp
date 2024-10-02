#pragma once

#include <ql/core/string/cast/cast.hpp>
#include <ql/core/transform/cast/cast.hpp>

namespace ql
{
	std::string ql::wchar_to_utf8(wchar_t wc)
	{
		std::string result;
		if (wc < 0x80)
		{
			result.push_back(ql::char_cast(wc));
		}
		else if (wc < 0x800)
		{
			result.push_back(ql::char_cast(0xC0 | wc >> 6));
			result.push_back(ql::char_cast(0x80 | (wc & 0x3F)));
		}
		else if (wc < 0x10000)
		{
			result.push_back(ql::char_cast(0xE0 | wc >> 12));
			result.push_back(ql::char_cast(0x80 | ((wc >> 6) & 0x3F)));
			result.push_back(ql::char_cast(0x80 | (wc & 0x3F)));
		}
		else
		{
			result.push_back(ql::char_cast(0xF0 | wc >> 18));
			result.push_back(ql::char_cast(0x80 | ((wc >> 12) & 0x3F)));
			result.push_back(ql::char_cast(0x80 | ((wc >> 6) & 0x3F)));
			result.push_back(ql::char_cast(0x80 | (wc & 0x3F)));
		}
		return result;
	}

	std::string ql::wstring_to_utf8(const std::wstring& string)
	{
		std::string result = "";
		for (auto& i : string)
		{
			result += ql::wchar_to_utf8(i);
		}
		return result;
	}

	
	std::string wstring_to_string(const std::wstring& string)
	{
		return ql::to_basic_string<char>(string);
	}

	std::wstring string_to_wstring(const std::string& string)
	{
		return ql::to_basic_string<wchar_t>(string);
	}
}	 // namespace ql