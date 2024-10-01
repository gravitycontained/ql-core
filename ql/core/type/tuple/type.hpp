#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/tuple/is-tuple.hpp>
#include <ql/core/type/tuple/size.hpp>
#include <tuple>

namespace ql
{
	template <ql::size N, typename T>
	requires (ql::is_tuple<T>())
	using tuple_type = std::tuple_element_t<N, T>;

	template <typename T>
	requires (ql::is_tuple<T>())
	using tuple_type_front = tuple_type<0, T>;

	template <typename T>
	requires (ql::is_tuple<T>())
	using tuple_type_back = tuple_type<ql::tuple_size<T>() - 1, T>;

}	 // namespace ql