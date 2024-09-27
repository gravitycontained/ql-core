#pragma once

#include <ql/constexpr/constexpr.hpp>
#include <ql/type-traits/tuple/is-tuple.hpp>
#include <ql/type-traits/tuple/value.hpp>

#include <array>

namespace ql
{
	template <typename T>
	requires (ql::is_tuple<T>())
	constexpr auto tuple_to_array(T tuple)
	{
		std::array<ql::tuple_type_front<T>, ql::tuple_size<T>()> result{};

		ql::constexpr_iterate<ql::tuple_size<T>()>([&](auto i) { result[i] = ql::tuple_value<i>(tuple); });

		return result;
	}
}	 // namespace ql