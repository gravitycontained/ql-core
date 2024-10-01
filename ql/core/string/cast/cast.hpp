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
									ql::to_basic_string<char_type>(", ");
				+ql::to_basic_string<char_type>(value.second) + ql::to_basic_string<char_type>('}');
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
}	 // namespace ql