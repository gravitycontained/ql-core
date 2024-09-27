#pragma once

#include <string>

#include <ql/type-traits/string/is-printable.hpp>
#include <ql/type-traits/tuple/tuple.hpp>
#include <ql/type-traits/variadic/type.hpp>
#include <ql/type-traits/variadic/value.hpp>

namespace ql
{
	template <typename... Args>
	requires(ql::is_printable<Args...>())
	std::string to_string(Args&&... args)
	{
		if constexpr(sizeof...(Args) == 1u &&
								 ql::is_same<ql::variadic_type<0u, Args...>, std::string>())
		{
			return ql::variadic_value<0u>(std::forward<Args>(args)...);
		}

		std::ostringstream stream;
		auto add_to_stream = [&]<typename T>(T value)
		{
			if constexpr(ql::is_container<T>() && !ql::is_long_string_type<T>())
			{
				stream << '[';
				bool first = true;
				for(auto& i : value)
				{
					if(!first)
					{
						stream << ", ";
					}
					stream << ql::to_string(i);
					first = false;
				}
				stream << ']';
			}
			else if constexpr(ql::is_tuple<T>())
			{
				stream << '{';
				if constexpr(ql::tuple_size<T>() > 1)
				{
					auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
					{ ((stream << ql::to_string(std::get<Ints>(value)) << ", "), ...); };
					unpack(std::make_index_sequence<ql::tuple_size<T>() - 1>());
				}
				stream << ql::to_string(ql::tuple_value_back(value)) << '}';
			}
			else if constexpr(ql::is_pair<T>())
			{
				stream << '{' << ql::to_string(value.first) << ", "
							 << ql::to_string(value.second) << '}';
			}
			else
			{
				stream << value;
			}
		};

		(add_to_stream(args), ...);

		return stream.str();
	}

}	 // namespace ql