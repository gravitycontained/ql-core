#pragma once

#include <ql/core/string/cast/cast.hpp>
#include <ql/core/transform/cast/cast.hpp>

#include <ql/core/system/exception/exception.hpp>

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

	wchar_t utf8_to_wchar(const std::string& utf8)
	{
		ql::size len = utf8.size();
		if (len == 0)
		{
			throw ql::exception("Empty UTF-8 string");
		}

		wchar_t wc = 0;
		if ((utf8[0] & 0x80) == 0)
		{	 // 0xxxxxxx
			wc = utf8[0];
		}
		else if ((utf8[0] & 0xE0) == 0xC0 && len >= 2)
		{	 // 110xxxxx 10xxxxxx
			wc = ((utf8[0] & 0x1F) << 6) | (utf8[1] & 0x3F);
		}
		else if ((utf8[0] & 0xF0) == 0xE0 && len >= 3)
		{	 // 1110xxxx 10xxxxxx 10xxxxxx
			wc = ((utf8[0] & 0x0F) << 12) | ((utf8[1] & 0x3F) << 6) | (utf8[2] & 0x3F);
		}
		else if ((utf8[0] & 0xF8) == 0xF0 && len >= 4)
		{	 // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
			wc = ((utf8[0] & 0x07) << 18) | ((utf8[1] & 0x3F) << 12) | ((utf8[2] & 0x3F) << 6) | (utf8[3] & 0x3F);
		}
		else
		{
			throw ql::exception("Invalid UTF-8 encoding");
		}
		return wc;
	}

	std::wstring utf8_to_wstring(const std::string& utf8_string)
	{
		std::wstring result;

		for (ql::size i = 0; i < utf8_string.size();)
		{
			char c = utf8_string[i];
			if ((c & 0x80) == 0)
			{	 // 0xxxxxxx
				result.push_back(ql::utf8_to_wchar(utf8_string.substr(i, 1)));
				++i;
			}
			else if ((c & 0xE0) == 0xC0)
			{	 // 110xxxxx 10xxxxxx
				result.push_back(ql::utf8_to_wchar(utf8_string.substr(i, 2)));
				i += 2;
			}
			else if ((c & 0xF0) == 0xE0)
			{	 // 1110xxxx 10xxxxxx 10xxxxxx
				result.push_back(ql::utf8_to_wchar(utf8_string.substr(i, 3)));
				i += 3;
			}
			else if ((c & 0xF8) == 0xF0)
			{	 // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
				result.push_back(ql::utf8_to_wchar(utf8_string.substr(i, 4)));
				i += 4;
			}
			else
			{
				throw ql::exception("Invalid UTF-8 encoding");
			}
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