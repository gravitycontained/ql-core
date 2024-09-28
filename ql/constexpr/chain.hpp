#pragma once

#include <ql/definition/definition.hpp>
#include <ql/constexpr/index.hpp>
#include <ql/maths/operation.hpp>

#include <ql/type/tuple/is-tuple.hpp>
#include <ql/type/tuple/type.hpp>
#include <ql/type/tuple/value.hpp>

#include <ql/type/compare/compare.hpp>

#include <functional>

namespace ql
{

	template <ql::operation op, ql::size N, typename F>
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
		return constexpr_chain<ql::operation::and_, N>(std::forward<F>(function));
	}

	template <ql::size N, typename F>
	constexpr auto constexpr_or_chain(F&& function)
	{
		return constexpr_chain<ql::operation::or_, N>(std::forward<F>(function));
	}

	template <typename T>
	requires (ql::is_tuple<T>())
	constexpr bool all_true(const T& tuple)
	{
		return ql::constexpr_and_chain<ql::tuple_size<T>()>(
				[&](auto i)
				{
					using type = ql::tuple_type<i, T>;
					return ql::is_same<type, ql::true_type>() || ql::tuple_value<i>(tuple);
				});
	}
}	 // namespace ql