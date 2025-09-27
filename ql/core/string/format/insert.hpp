#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>
#include <ql/core/string/format/join.hpp>
#include <ql/core/string/split/split.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_printable<T>())
	constexpr auto string_insert(const T& string, const T& insert, ql::size count)
	{
		if (count == 0u)
			return string;

		ql::string_type<T> result;

		result.reserve(string.length() + count * insert.length());

		for (ql::size i = 0u; i < string.length(); i += count)
		{
			auto begin = i;
			auto end = ql::min(string.length(), i + count);

			result += ql::string_view<T>
			{
				string.cbegin() + begin,
				string.cbegin() + end
			};

			result += insert;
		}
		return result;
	}

}	 // namespace ql