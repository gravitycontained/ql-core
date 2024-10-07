#pragma once

#include <string>
#include <ql/core/type/string/is-printable.hpp>
#include <ql/core/type/tuple/tuple.hpp>
#include <ql/core/type/variadic/type.hpp>
#include <ql/core/type/variadic/value.hpp>
#include <ql/core/string/format/options.hpp>
#include <ql/core/constexpr/iterate.hpp>
#include <ql/core/string/cast/cast.hpp>

namespace ql
{
	template <typename... Args>
	requires (ql::is_printable<Args>() && ...)
	std::string to_string2(Args&&... args)
	{
		if constexpr (sizeof...(Args) == 1u && ql::is_same<ql::variadic_type<0u, Args...>, std::string>())
		{
			return ql::variadic_value<0u>(std::forward<Args>(args)...);
		}

		std::ostringstream stream;

		auto add_to_stream = [&]<typename T>(T value)
		{
			if constexpr (ql::has_to_string<T>())
			{
				stream << value.to_string();
			}
			else if constexpr (ql::is_container<T>() && !ql::is_long_string_type<T>())
			{
				stream << '[';
				bool first = true;
				for (auto& i : value)
				{
					if (!first)
					{
						stream << ", ";
					}
					stream << ql::to_string2(std::forward<decltype(i)>(i));
					first = false;
				}
				stream << ']';
			}
			else if constexpr (ql::is_tuple<T>())
			{
				stream << '{';
				if constexpr (ql::tuple_size<T>() > 1)
				{
					ql::constexpr_iterate<ql::tuple_size<T>() - 1>([&](auto index)
																												 { stream << ql::to_string2(ql::tuple_value<index>(value)) << ", "; });
				}
				stream << ql::to_string2(ql::tuple_value_back(value)) << '}';
			}
			else
			{
				stream << value;
			}
		};

		(add_to_stream(args), ...);

		return stream.str();
	}

		template <typename... Ts>
	requires (ql::is_printable<Ts>() && ...)
	auto to_string(Ts&&... args)
	{
		using string_type = ql::recursive_to_string_type<Ts...>;
		using string_underlying = ql::string_underlying_type<string_type>;
		return ql::to_basic_string<string_underlying>(std::forward<Ts>(args)...);
	}

}	 // namespace ql