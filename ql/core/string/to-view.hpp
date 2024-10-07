#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_long_string_type<T>() && !ql::is_string_view<T>())
	constexpr auto to_string_view(const T& str)
	{
		if constexpr (ql::has_data<T>() && ql::has_size<T>())
		{
			return ql::string_view<T>{str.data(), str.size()};
		}
		else
		{
			return ql::string_view<T>{str};
		}
	}
}	 // namespace ql