#pragma once
#include <ql/core/advanced-type/interactive/type.hpp>

#include <ql/graphic/render/render.hpp>

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T>
		concept has_draw_no_parameter_c = requires(T x) { x.draw(); };

		template <typename T>
		constexpr void apply_if_draw_param(T& object, ql::render& render)
		{
			if constexpr (has_draw_no_parameter_c<T>)
				object.draw();

			if constexpr (ql::has_draw<decltype(object)>())
				render.draw(object);
		}
	}	 // namespace detail

	template <typename T>
	requires (ql::is_or_has_interactive<T>())
	void interactive_draw(T& object, ql::render& render)
	{
		detail::apply_if_draw_param(object, render);
		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
					tuple,
					[&](auto& member)
					{
						detail::apply_if_draw_param(member, render);

						if constexpr (ql::is_container<decltype(member)>())
						{
							if constexpr (ql::is_or_has_interactive<ql::container_subtype<decltype(member)>>())
								for (auto& sub_member : member)
									interactive_draw(sub_member, render);

							if constexpr (ql::has_draw<ql::container_subtype<decltype(member)>>())
								for (auto& sub_member : member)
									detail::apply_if_draw_param(sub_member, render);
						}

						if constexpr (ql::is_or_has_interactive<decltype(member)>())
							interactive_draw(member, render);
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
