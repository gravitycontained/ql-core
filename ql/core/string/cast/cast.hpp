#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

#include <string>
#include <codecvt>
#include <string_view>

namespace ql
{
	QL_SOURCE std::string wchar_to_utf8(wchar_t wc);
	QL_SOURCE std::string wstring_to_utf8(const std::wstring& string);

	QL_SOURCE wchar_t utf8_to_wchar(const std::string& string);
	QL_SOURCE std::wstring utf8_to_wstring(const std::string& str);

	template <typename Target, typename Source>
	Target string_cast(const Source& src)
	{
		// Convert std::string -> std::wstring
		if constexpr (std::is_same_v<Target, std::wstring> && std::is_same_v<Source, std::string>)
		{
#pragma warning(push)
#pragma warning(disable : 4996)
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			auto result = converter.from_bytes(src);
			#pragma warning(pop)
			return result;
		}
		// Convert std::wstring -> std::string
		else if constexpr (std::is_same_v<Target, std::string> && std::is_same_v<Source, std::wstring>)
		{
#pragma warning(push)
#pragma warning(disable : 4996)
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			auto result = converter.to_bytes(src);
#pragma warning(pop)
			return result;
		}
		// Convert std::string -> std::u32string (UTF-8 to UTF-32)
		else if constexpr (std::is_same_v<Target, std::u32string> && std::is_same_v<Source, std::string>)
		{
			std::u32string result;
			char32_t ch32;
			size_t i = 0;

			while (i < src.size())
			{
				unsigned char ch = static_cast<unsigned char>(src[i]);
				if (ch < 0x80)
				{
					ch32 = ch;
					++i;
				}
				else if (ch < 0xE0)
				{
					if (i + 1 >= src.size())
						throw std::runtime_error("Invalid UTF-8 sequence");
					ch32 = ((ch & 0x1F) << 6) | (static_cast<unsigned char>(src[i + 1]) & 0x3F);
					i += 2;
				}
				else if (ch < 0xF0)
				{
					if (i + 2 >= src.size())
						throw std::runtime_error("Invalid UTF-8 sequence");
					ch32 = ((ch & 0x0F) << 12) | ((static_cast<unsigned char>(src[i + 1]) & 0x3F) << 6) |
								 (static_cast<unsigned char>(src[i + 2]) & 0x3F);
					i += 3;
				}
				else
				{
					if (i + 3 >= src.size())
						throw std::runtime_error("Invalid UTF-8 sequence");
					ch32 = ((ch & 0x07) << 18) | ((static_cast<unsigned char>(src[i + 1]) & 0x3F) << 12) |
								 ((static_cast<unsigned char>(src[i + 2]) & 0x3F) << 6) | (static_cast<unsigned char>(src[i + 3]) & 0x3F);
					i += 4;
				}
				result.push_back(ch32);
			}
			return result;
		}
		// Convert std::u32string -> std::string (UTF-32 to UTF-8)
		else if constexpr (std::is_same_v<Target, std::string> && std::is_same_v<Source, std::u32string>)
		{
			std::string result;
			for (char32_t ch : src)
			{
				if (ch < 0x80)
				{
					result.push_back(static_cast<char>(ch));
				}
				else if (ch < 0x800)
				{
					result.push_back(static_cast<char>((ch >> 6) | 0xC0));
					result.push_back(static_cast<char>((ch & 0x3F) | 0x80));
				}
				else if (ch < 0x10000)
				{
					result.push_back(static_cast<char>((ch >> 12) | 0xE0));
					result.push_back(static_cast<char>(((ch >> 6) & 0x3F) | 0x80));
					result.push_back(static_cast<char>((ch & 0x3F) | 0x80));
				}
				else
				{
					result.push_back(static_cast<char>((ch >> 18) | 0xF0));
					result.push_back(static_cast<char>(((ch >> 12) & 0x3F) | 0x80));
					result.push_back(static_cast<char>(((ch >> 6) & 0x3F) | 0x80));
					result.push_back(static_cast<char>((ch & 0x3F) | 0x80));
				}
			}
			return result;
		}
		// Convert std::u32string -> std::wstring (via std::string)
		else if constexpr (std::is_same_v<Target, std::wstring> && std::is_same_v<Source, std::u32string>)
		{
			std::string temp = string_cast<std::string>(src);	 // u32 -> string
			return string_cast<std::wstring>(temp);						 // string -> wstring
		}
		// Convert std::wstring -> std::u32string (direct cast per character)
		else if constexpr (std::is_same_v<Target, std::u32string> && std::is_same_v<Source, std::wstring>)
		{
			std::u32string result;
			for (wchar_t ch : src)
			{
				result.push_back(static_cast<char32_t>(ch));
			}
			return result;
		}
		// Otherwise, if types are not supported, throw an error
		else
		{
			throw std::runtime_error("Unsupported conversion between types");
		}
	}

	template <typename char_type, typename... Ts>
	requires (!ql::is_long_string_type<char_type>() && ql::is_printable<Ts...>())
	std::basic_string<char_type> to_basic_string(Ts&&... args)
	{
		using string_type = std::basic_string<char_type>;
		if constexpr (ql::variadic_size<Ts...>() == 1u && ql::is_same<ql::variadic_type_front<Ts...>, string_type>())
		{
			return ql::variadic_value_front(std::forward<Ts...>(args...));
		}

		std::basic_ostringstream<char_type> stream;

		auto add_to_stream = [&]<typename T>(T value)
		{
			if constexpr (ql::has_to_string<T>())
			{
				stream << ql::to_basic_string<char_type>(value.to_string());
			}
			else if constexpr (ql::is_container<T>() && !ql::is_long_string_type<T>())
			{
				stream << ql::to_basic_string<char_type>('{');
				bool first = true;
				for (auto& i : value)
				{
					if (!first)
					{
						stream << ql::to_basic_string<char_type>(", ");
					}
					stream << ql::to_basic_string<char_type>(i);
					first = false;
				}
				stream << ql::to_basic_string<char_type>('}');
			}
			else if constexpr (ql::is_tuple<T>())
			{
				stream << ql::to_basic_string<char_type>('{');
				if constexpr (ql::tuple_size<T>() > 1)
				{
					ql::constexpr_iterate<ql::tuple_size<T>() - 1>(
							[&](auto index)
							{ stream << ql::to_basic_string<char_type>(ql::tuple_value<index>(value)) << ql::to_basic_string<char_type>(", "); }
					);
				}
				stream << ql::to_basic_string<char_type>(ql::tuple_value_back(value)) + ql::to_basic_string<char_type>('}');
			}
			else if constexpr (ql::is_char_type<T>())
			{
				stream << value;
			}
			else if constexpr (ql::is_char_pointer_type<T>())
			{
				std::basic_string<ql::full_decay<T>> string = value;
				string_type convert(string.begin(), string.end());
				stream << convert;
			}
			else if constexpr (ql::is_same<T, string_type>())
			{
				string_type convert(value.begin(), value.end());
				stream << convert;
			}
			else if constexpr (ql::is_same<T, string_type>())
			{
				stream << value;
			}
			else if constexpr (ql::is_same<T, std::string>() || ql::is_same<T, std::wstring>() || ql::is_same<T, std::u32string>())
			{
				stream << ql::string_cast<string_type>(value);
			}
			else
			{
				// static_assert(false, __FUNCTION__ "problem");
				// assert(value);
				stream << value;
			}
		};

		(add_to_stream(args), ...);

		return stream.str();
	}

	QL_SOURCE std::string wstring_to_string(const std::wstring& string);
	QL_SOURCE std::wstring string_to_wstring(const std::string& string);

}	 // namespace ql
