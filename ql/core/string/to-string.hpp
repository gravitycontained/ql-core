#pragma once

#include <string>
#include <ql/core/type/string/is-printable.hpp>
#include <ql/core/type/tuple/tuple.hpp>
#include <ql/core/type/variadic/type.hpp>
#include <ql/core/type/variadic/value.hpp>
#include <ql/core/string/format/options.hpp>
#include <ql/core/functional/functional.hpp>

namespace ql
{
	template <typename... Args>
	requires (ql::is_printable<Args>() && ...)
	std::string to_string(Args&&... args)
	{
		std::ostringstream stream;

		ql::recursive_value_apply(
				[&]<typename T>(T value, ql::iterate_info info)
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
							stream << ql::to_string(i);
							first = false;
						}
						stream << ']';
					}
					else if constexpr (ql::is_tuple<T>())
					{
						stream << '{';
						if constexpr (ql::tuple_size<T>() > 1)
						{
							auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
							{ ((stream << ql::to_string(ql::tuple_value<Ints>(value)) << ", "), ...); };
							unpack(std::make_index_sequence<ql::tuple_size<T>() - 1>());
						}
						stream << ql::to_string(ql::tuple_value_back(value)) << '}';
					}
					else if constexpr (ql::is_pair<T>())
					{
						stream << '{' << ql::to_string(value.first) << ", " << ql::to_string(value.second) << '}';
					}
					else
					{
						stream << value;
					}
				},
				std::forward<Args>(args)...
		);

		return stream.str();
	}

}	 // namespace ql