#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{
	QL_SOURCE std::string wchar_to_utf8(wchar_t wc);
	QL_SOURCE std::string wstring_to_utf8(const std::wstring& string);

	template <typename char_type, typename... Args>
	requires (!ql::is_long_string_type<char_type>() && ql::is_printable<Args...>())
	std::basic_string<char_type> to_basic_string(Args&&... args)
	{
		if constexpr (sizeof...(Args) == 1u && ql::is_same<ql::tuple_type<0u, std::tuple<Args...>>, std::basic_string<char_type>>())
		{
			return ql::variadic_value<0u>(args...);
		}

		std::basic_string<char_type> result;
		auto add_to_stream = [&]<typename T>(T value)
		{
			if constexpr (ql::is_container<T>() && !ql::is_long_string_type<T>())
			{
				result += ql::to_basic_string<char_type>('{');
				bool first = true;
				for (auto& i : value)
				{
					if (!first)
					{
						result += ql::to_basic_string<char_type>(", ");
					}
					result += ql::to_basic_string<char_type>(i);
					first = false;
				}
				result += ql::to_basic_string<char_type>('}');
			}
			else if constexpr (ql::is_tuple<T>())
			{
				result += ql::to_basic_string<char_type>('{');
				if constexpr (ql::tuple_size<T>() > 1)
				{
					auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
					{ ((result += ql::to_basic_string<char_type>(std::get<Ints>(value)) + ql::to_basic_string<char_type>(", ")), ...); };
					unpack(std::make_index_sequence<ql::tuple_size<T>() - 1>());
				}
				result += ql::to_basic_string<char_type>(ql::tuple_value_back(value)) + ql::to_basic_string<char_type>('}');
			}
			else if constexpr (ql::is_pair<T>())
			{
				result += ql::to_basic_string<char_type>('{') + ql::to_basic_string<char_type>(value.first) +
									ql::to_basic_string<char_type>(", ") + ql::to_basic_string<char_type>(value.second) +
									ql::to_basic_string<char_type>('}');
			}
			else if constexpr (ql::is_char_type<T>())
			{
				result += static_cast<char32_t>(value);
			}
			else if constexpr (ql::is_char_pointer_type<T>())
			{
				std::basic_string<ql::full_decay<T>> string = value;
				std::basic_string<char_type> convert(string.begin(), string.end());
				result += convert;
			}
			else
			{
				std::basic_string<char_type> convert(value.begin(), value.end());
				result += convert;
			}
		};

		(add_to_stream(args), ...);

		return result;
	}

	template <typename... Args>
	requires (ql::is_printable<Args...>())
	auto to_u32_string(Args&&... args)
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