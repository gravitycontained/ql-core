#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

#include <ql/graphic/interactive/type.hpp>

namespace ql
{

	template <typename C>
	concept has_post_update_c = requires(C x) { x.post_update(); };

	template <typename C>
	constexpr bool has_post_update()
	{
		return has_post_update_c<C>;
	}

	template <typename T>
	requires (ql::is_or_has_interactive<T>())
	void interactive_post_update(T& object)
	{
		if constexpr (ql::has_post_update<decltype(object)>())
			object.post_update();

		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
					tuple,
					[&](auto& member)
					{
						if constexpr (ql::has_post_update<decltype(member)>())
							member.post_update();

						if constexpr (ql::is_or_has_interactive<decltype(member)>())
							ql::interactive_post_update(member);
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