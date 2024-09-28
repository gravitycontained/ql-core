#pragma once

#include <ql/definition/definition.hpp>
#include <ql/type/tuple/type.hpp>
#include <tuple>

namespace ql
{
	template <ql::size N, typename... Ts>
	using variadic_type = ql::tuple_type<N, std::tuple<Ts...>>;

	template <ql::size N, typename... Ts>
	using variadic_type_front = ql::tuple_type_front<std::tuple<Ts...>>;

	template <typename... Ts>
	using variadic_type_back = ql::tuple_type_back<std::tuple<Ts...>>;
}