#pragma once

#include <ql/definition/definition.hpp>
#include <ql/type/tuple/is-tuple.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_tuple<T>())
	constexpr ql::size tuple_size()
	{
		return std::tuple_size_v<T>;
	}

	template <typename T>
	requires (!ql::is_tuple<T>())
	constexpr ql::size tuple_size()
	{
		return 1;
	}


	template <typename T>
	requires (ql::is_tuple<T>())
	constexpr ql::size tuple_size(T tuple)
	{
		return ql::tuple_size<T>();
	}
}	 // namespace ql