#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/constexpr/index.hpp>
#include <ql/core/maths/operation.hpp>

#include <ql/core/type/tuple/is-tuple.hpp>
#include <ql/core/type/tuple/type.hpp>
#include <ql/core/type/tuple/value.hpp>

#include <ql/core/type/compare/compare.hpp>

#include <functional>

namespace ql
{

	template <ql::size N, ql::operation op, typename F>
	constexpr auto constexpr_chain(F&& function)
	{
		auto unpack = [&]<ql::size... Ints>(std::index_sequence<Ints...>)
		{
			if constexpr (op == ql::operation::add)
				return (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}) + ...);

			else if constexpr (op == ql::operation::sub)
				return (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}) - ...);

			else if constexpr (op == ql::operation::mul)
				return (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}) * ...);

			else if constexpr (op == ql::operation::div)
				return (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}) / ...);

			else if constexpr (op == ql::operation::and_)
				return (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}) && ...);

			else if constexpr (op == ql::operation::or_)
				return (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}) || ...);

			else if constexpr (op == ql::operation::xor_)
				return (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}) ^ ...);

			else if constexpr (op == ql::operation::lshift)
				return (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}) << ...);

			else if constexpr (op == ql::operation::rshift)
				return (std::forward<F>(function)(ql::constexpr_index<Ints, N>{}) >> ...);
		};
		return unpack(std::make_index_sequence<N>());
	}

	template <ql::size N, typename F>
	constexpr auto constexpr_and_chain(F&& function)
	{
		return ql::constexpr_chain<N, ql::operation::and_>(std::forward<F>(function));
	}

	template <ql::size N, typename F>
	constexpr auto constexpr_or_chain(F&& function)
	{
		return ql::constexpr_chain<N, ql::operation::or_>(std::forward<F>(function));
	}

	template <typename T>
	requires (ql::is_tuple<T>())
	constexpr bool all_tuple_true(const T& tuple)
	{
		return ql::constexpr_and_chain<ql::tuple_size<T>()>(
				[&](auto i)
				{
					using type = ql::tuple_type<i, T>;
					return ql::is_same<type, ql::true_type>() || ql::tuple_value<i>(tuple);
				}
		);
	}

	template <typename T>
	requires (ql::is_tuple<T>())
	constexpr bool any_tuple_true(const T& tuple)
	{
		return ql::constexpr_or_chain<ql::tuple_size<T>()>(
				[&](auto i)
				{
					using type = ql::tuple_type<i, T>;
					return ql::is_same<type, ql::true_type>() || ql::tuple_value<i>(tuple);
				}
		);
	}
}	 // namespace ql