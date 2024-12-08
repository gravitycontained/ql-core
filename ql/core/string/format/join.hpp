#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>
#include <ql/core/string/cast/cast.hpp>

namespace ql
{
	template <typename T, typename S>
	requires (ql::is_container<T>() && ql::has_push_back<T>() && ql::has_reserve<T>())
	constexpr auto string_join(const T& container, const S& delimiter)
	{
		ql::string_type<S> result;
		if (container.empty())
			return result;

		for (ql::size i = 0u; i < container.size(); ++i)
		{
			result += ql::to_string(container[i]);
			if (i != container.size() - 1)
				result += delimiter;
		}
		return result;
	}

}	 // namespace ql