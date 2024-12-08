#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

#include <ql/graphic/interactive/type.hpp>
#include <ql/graphic/render/render.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_or_has_interactive<T>())
	void interactive_draw(T& object, ql::render& render)
	{
		if constexpr (ql::has_draw<decltype(object)>())
			render.draw(object);

		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
				tuple,
				[&](auto& member)
					{
						if constexpr (ql::has_draw<decltype(member)>())
							render.draw(member);

					if constexpr (ql::is_or_has_interactive<decltype(member)>())
						ql::interactive_draw(member, render);
				}
			);
		};

		if constexpr (ql::has_interactive<T>())
		{
			auto tuple = ql::struct_to_tuple(object.interactive);
			iterate(tuple);
		}

		else if constexpr (ql::is_interactive<T>())
		{
			auto tuple = ql::struct_to_tuple(object);
			iterate(tuple);
		}
	}

}	 // namespace ql