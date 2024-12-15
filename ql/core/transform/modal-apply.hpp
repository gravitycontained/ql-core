#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/container/is-container.hpp>
#include <ql/core/type/pointer/pointer.hpp>

#include <functional>

namespace ql
{
	template <typename T, typename F>
	constexpr void modal_apply(T&& value, F function)
	{
		if constexpr (ql::is_container<T>())
			for (auto& i : value)
				ql::modal_apply(std::forward<decltype(i)>(i), function);

		else if constexpr (ql::is_pointer<ql::decay<T>>())
			ql::modal_apply(*value, function);
			//if (value)
			//	ql::modal_apply(*value, function);

		else
			function(std::forward<T>(value));
	}
}