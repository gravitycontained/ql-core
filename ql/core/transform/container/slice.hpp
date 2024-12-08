#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_container<T>() && ql::has_push_back<T>() && ql::has_reserve<T>())
	constexpr auto slice(const T& container, ql::size start, ql::size end = ql::size_max)
	{
		if (end == ql::size_max)
			end = container.size();

		T result;
		if (container.empty())
		{
			return result;
		}

		if (start >= container.size())
		{
			return result;
		}

		if (end >= container.size())
		{
			end = container.size();
		}

		result.reserve(end - start);
		for (ql::size i = start; i < end; ++i)
		{
			result.push_back(container[i]);
		}
		return result;
	}

	template <typename T>
	requires (ql::is_container<T>() && ql::has_push_back<T>() && ql::has_reserve<T>())
	constexpr auto slice_back(const T& container, ql::size rest)
	{
		return slice(container, 0, container.size() - rest);
	}
}