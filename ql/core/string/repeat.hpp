#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/transform/cast/cast.hpp>

namespace ql
{
	template <typename T>
	std::string to_string_repeat(T&& value, ql::size repeat)
	{
		if (repeat > ql::size_cast(1e12))
		{
			return "";
		}
		std::ostringstream stream;
		for (auto i = ql::size{}; i < repeat; ++i)
		{
			stream << value;
		}
		return stream.str();
	}
}	 // namespace ql