#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/declval.hpp>
#include <ql/core/type/conditional.hpp>
#include <ql/core/type/tuple/is-tuple.hpp>

#include <ql/core/functional/auto-tie.hpp>

namespace ql
{
	template <typename T>
	using as_tuple_type = ql::conditional<ql::if_true<ql::is_tuple<T>()>, T, std::tuple<T>>;

	template <typename... T>
	constexpr auto concat_tuple(T&&... t)
	{
		auto to_tuple = [](auto&& value)
		{
			if constexpr (ql::is_tuple<decltype(value)>())
				return std::forward<decltype(value)>(value);
			else
				return ql::auto_tie(std::forward<decltype(value)>(value));
		};

		return std::tuple_cat(to_tuple(std::forward<T>(t))...);
	}

	template <typename... T>
	using concat_tuple_type = decltype(concat_tuple(ql::declval_fully_qualified<T>()...));

}