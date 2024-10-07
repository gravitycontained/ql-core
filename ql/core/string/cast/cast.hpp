#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

#include <string>
#include <string_view>

#include <locale>
#include <stdexcept>
#include <codecvt>	// Still needed for std::wstring_convert for UTF-8 to wide char

namespace ql
{
	QL_SOURCE std::string wchar_to_utf8(wchar_t wc);
	QL_SOURCE std::string wstring_to_utf8(const std::wstring& string);

	QL_SOURCE wchar_t utf8_to_wchar(const std::string& string);
	QL_SOURCE std::wstring utf8_to_wstring(const std::string& str);

	template <typename Target, typename Source>
	Target string_cast(const Source& src);

	// Specialization: std::string -> std::wstring
	template <>
	std::wstring string_cast(const std::string& src)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(src);
	}

	// Specialization: std::wstring -> std::string
	template <>
	std::string string_cast(const std::wstring& src)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(src);
	}

	// Specialization: std::string -> std::u32string
	template <>
	std::u32string string_cast(const std::string& src)
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

	// Specialization: std::u32string -> std::string
	template <>
	std::string string_cast(const std::u32string& src)
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

	// Specialization: std::wstring -> std::u32string
	template <>
	std::u32string string_cast(const std::wstring& src)
	{
		std::u32string result;
		for (wchar_t ch : src)
		{
			result.push_back(static_cast<char32_t>(ch));
		}
		return result;
	}

	// Specialization: std::u32string -> std::wstring
	template <>
	std::wstring string_cast(const std::u32string& src)
	{
		std::wstring result;
		for (char32_t ch : src)
		{
			if (ch > 0xFFFF)
				throw std::runtime_error("Cannot convert char32_t to wchar_t: out of range");
			result.push_back(static_cast<wchar_t>(ch));
		}
		return result;
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
					ql::constexpr_iterate<ql::tuple_size<T>() - 1>([&](auto index)
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
			else if constexpr (ql::is_same<T, std::wstring>() && ql::is_same<string_type, std::string>())
			{
				stream << ql::wstring_to_utf8(value);
			}
			else if constexpr (ql::is_same<T, std::string>() && ql::is_same<string_type, std::wstring>())
			{
				stream << ql::utf8_to_wstring(value);
			}
			else
			{
				//static_assert(false, __FUNCTION__ "problem");
				//assert(value);
				stream << value;
			}
		};

		(add_to_stream(args), ...);

		return stream.str();
	}

	template <typename... Ts>
	requires (ql::is_printable<Ts...>())
	auto to_u32_string(Ts&&... args)
	{
		return ql::to_basic_string<ql::u32>(args...);
	}

	QL_SOURCE std::string wstring_to_string(const std::wstring& string);
	QL_SOURCE std::wstring string_to_wstring(const std::string& string);

	template <typename T>
	T string_cast(const std::string_view& string)
	{
		if constexpr (ql::is_ql_integer<T>() || ql::is_ql_floating_point<T>())
		{
			return T(string);
		}
		else
		{
			T value;
			std::from_chars(string.data(), string.data() + string.size(), value);

			return value;
		}
	}

	template <typename T>
	T string_cast(const char* str)
	{
		return ql::string_cast<T>(std::string_view{str});
	}

	template <typename T>
	T string_cast(const std::string& string)
	{
		if constexpr (ql::is_same_decayed<T, ql::f64>())
		{
			return std::stod(string);
		}
		else if constexpr (ql::is_same_decayed<T, ql::f32>())
		{
			return std::stof(string);
		}
		else if constexpr (ql::is_same_decayed<T, ql::i8>())
		{
			return static_cast<ql::i8>(std::stoi(string));
		}
		else if constexpr (ql::is_same_decayed<T, ql::u8>())
		{
			return static_cast<ql::u8>(std::stoul(string));
		}
		else if constexpr (ql::is_same_decayed<T, ql::i16>())
		{
			return static_cast<ql::i16>(std::stoi(string));
		}
		else if constexpr (ql::is_same_decayed<T, ql::u16>())
		{
			return static_cast<ql::u16>(std::stoul(string));
		}
		else if constexpr (ql::is_same_decayed<T, ql::i32>())
		{
			return std::stoi(string);
		}
		else if constexpr (ql::is_same_decayed<T, ql::u32>())
		{
			return static_cast<ql::u32>(std::stoul(string));
		}
		else if constexpr (ql::is_same_decayed<T, ql::i64>())
		{
			return std::stoll(string);
		}
		else if constexpr (ql::is_same_decayed<T, ql::u64>())
		{
			return std::stoull(string);
		}
		else if constexpr (ql::is_same_decayed<T, std::wstring>())
		{
			return ql::string_to_wstring(string);
		}
		else if constexpr (ql::is_same_decayed<T, std::string>())
		{
			return string;
		}
	}

	template <typename T>
	T string_cast(const std::wstring& string)
	{
		if constexpr (ql::is_same_decayed<T, ql::f64>())
		{
			return std::wcstod(string.data(), nullptr);
		}
		else if constexpr (ql::is_same_decayed<T, ql::f32>())
		{
			return std::wcstof(string.data(), nullptr);
		}
		else if constexpr (ql::is_same_decayed<T, ql::i8>())
		{
			return static_cast<ql::i8>(std::wcstol(string.data(), nullptr, 10));
		}
		else if constexpr (ql::is_same_decayed<T, ql::u8>())
		{
			return static_cast<ql::u8>(std::wcstoul(string.data(), nullptr, 10));
		}
		else if constexpr (ql::is_same_decayed<T, ql::i16>())
		{
			return static_cast<ql::i16>(std::wcstol(string.data(), nullptr, 10));
		}
		else if constexpr (ql::is_same_decayed<T, ql::u16>())
		{
			return static_cast<ql::u16>(std::wcstoul(string.data(), nullptr, 10));
		}
		else if constexpr (ql::is_same_decayed<T, ql::i32>())
		{
			return static_cast<ql::i32>(std::wcstol(string.data(), nullptr, 10));
		}
		else if constexpr (ql::is_same_decayed<T, ql::u32>())
		{
			return static_cast<ql::u32>(std::wcstoul(string.data(), nullptr, 10));
		}
		else if constexpr (ql::is_same_decayed<T, ql::i64>())
		{
			return std::wcstoll(string.data(), nullptr, 10);
		}
		else if constexpr (ql::is_same_decayed<T, ql::u64>())
		{
			return std::wcstoull(string.data(), nullptr, 10);
		}
		else if constexpr (ql::is_same_decayed<T, std::wstring>())
		{
			return string;
		}
		else if constexpr (ql::is_same_decayed<T, std::string>())
		{
			return ql::wstring_to_string(string);
		}
	}

}	 // namespace ql