#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/tuple/is-tuple.hpp>
#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/maths/operation.hpp>

namespace ql
{
	template <typename T, typename U>
	requires (ql::is_tuple<T>())
	constexpr ql::size tuple_find_index_of_type()
	{
		constexpr auto result = ql::constexpr_chain<ql::tuple_size<T>(), ql::operation::add>(
			[&](auto index)
			{
				if constexpr (ql::is_same_decayed<ql::tuple_type<index, T>, U>())
					return index + 1;

				else
					return 0u;
			}
		);

		if constexpr (result == 0u)
			return ql::tuple_size<T>();

		else
			return result - 1;
	}

}