#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/functional/functional.hpp>
#include <ql/core/constexpr/chain.hpp>
#include <ql/core/maths/operation.hpp>

namespace ql
{
	template <typename T, ql::operation op, typename F>
	constexpr auto recursive_type_chain(F&& function)
	{
		if constexpr (ql::is_container<T>())
		{
			return ql::recursive_type_chain<ql::container_subtype<T>, op>(std::forward<F>(function));
		}
		else if constexpr (ql::is_tuple<T>())
		{
			constexpr auto size = ql::tuple_size<T>();
			return ql::constexpr_chain<size, op>(
					[&](auto i) { return ql::recursive_type_chain<ql::tuple_type<i, T>, op>(std::forward<F>(function)); }
			);
		}
		else
		{
			return std::forward<F>(function).template operator()<T>();
		}
	}

	template <typename T, typename F>
	constexpr auto recursive_type_and_chain(F&& function)
	{
		return ql::recursive_type_chain<T, ql::operation::and_>(std::forward<F>(function));
	}

	template <typename T, typename F>
	constexpr auto recursive_type_or_chain(F&& function)
	{
		return ql::recursive_type_chain<T, ql::operation::or_>(std::forward<F>(function));
	}
}	 // namespace ql