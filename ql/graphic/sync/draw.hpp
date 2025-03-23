#pragma once

#include <ql/graphic/sync/type/type.hpp>
#include <ql/core/system/print/print.hpp>
#include <ql/graphic/view/view.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T>
		concept has_draw_no_parameter_c = requires(T x) { x.draw(); };

		template <typename T>
		constexpr bool has_sync_draw()
		{
			return detail::has_draw_no_parameter_c<T> || ql::has_draw<T>();
		};

		template <typename T>
		constexpr void apply_draw(const T& object, ql::render& render)
		{
			if constexpr (has_draw_no_parameter_c<T>)
				object.draw();

			if constexpr (ql::has_draw<decltype(object)>())
				render.draw(object);
		}
	}	 // namespace detail

	template <typename T>
	requires (ql::is_or_has_sync<ql::modal_decay<T>>() || detail::has_sync_draw<ql::modal_decay<T>>())
	void sync_draw(T& object, ql::render& render)
	{
		ql::modal_apply(
			object,
			[&](auto& check)
			{
				constexpr bool order = true;

				auto iterate = [&](auto& tuple)
				{
					bool found_view = false;

					constexpr auto N = ql::tuple_find_index_of_type<decltype(tuple), ql::declare_unsync>();
					ql::constexpr_iterate<N>(
						[&](auto i)
						{
							auto&& tuple_element = ql::tuple_value<i>(tuple);

							if constexpr (ql::is_view<decltype(tuple_element)>())
							{
								render.push_view(tuple_element);
								found_view = true;
							}

							if constexpr (ql::is_or_has_sync<ql::modal_decay<decltype(tuple_element)>>() ||
								detail::has_sync_draw<ql::modal_decay<decltype(tuple_element)>>()
							)
								sync_draw(tuple_element, render);
						}
					);

					if (found_view)
						render.pop_view();
				};

				auto check_apply_on_object = [&](auto& apply_check)
				{
					ql::modal_apply(
						apply_check,
						[&](auto& value)
						{
							if constexpr (detail::has_sync_draw<decltype(value)>())
								detail::apply_draw(value, render);
						}
					);
				};

				if constexpr (ql::is_or_has_sync<decltype(check)>())
				{
					auto&& sync = ql::sync_resolve(check);
					if (!sync.declare_sync.active || !sync.declare_sync.draw)
						return;
				}

				if constexpr (order)
					ql::sync_apply_soft<true>(check, [&](auto&& value)
					{
						check_apply_on_object(value);
					});

				ql::sync_modal_apply(check, [&](auto&& value)
				{
					auto tuple = ql::struct_to_tuple(value);
					iterate(tuple);
				});

				if constexpr (!order)
					ql::sync_apply_soft<false>(check, [&](auto&& value)
					{
						check_apply_on_object(value);
					});
			}
		);
	}

}	 // namespace ql
