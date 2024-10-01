#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/container/is-container.hpp>

#include <ql/core/transform/cast/cast.hpp>

namespace ql
{
	template <typename C, typename R>
	requires (ql::is_container<C>())
	void shuffle(C& container, R& engine)
	{
		for (auto i = container.size() - 1; i > 0; --i)
		{
			std::swap(container[i], container[engine.get(ql::size_cast(0ull), i)]);
		}
	}
}	 // namespace ql