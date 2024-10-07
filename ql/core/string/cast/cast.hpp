#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

#include <string>
#include <string_view>

namespace ql
{
	QL_SOURCE std::string wchar_to_utf8(wchar_t wc);
	QL_SOURCE std::string wstring_to_utf8(const std::wstring& string);

	QL_SOURCE wchar_t utf8_to_wchar(const std::string& string);
	QL_SOURCE std::wstring utf8_to_wstring(const std::string& str);


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