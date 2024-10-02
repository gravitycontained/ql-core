#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/tuple/is-tuple.hpp>
#include <ql/core/type/tuple/size.hpp>
#include <ql/core/type/compare/compare.hpp>
#include <tuple>

namespace ql
{
	template <ql::size N, typename T>
	requires (ql::is_tuple<T>())
	using tuple_type = std::tuple_element_t<N, ql::full_decay<T>>;

	template <typename T>
	requires (ql::is_tuple<T>())
	using tuple_type_front = ql::tuple_type<0, T>;

	template <typename T>
	requires (ql::is_tuple<T>())
	using tuple_type_back = ql::tuple_type<ql::tuple_size<T>() - 1, T>;

}	 // namespace ql