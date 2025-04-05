#pragma once

#include <ql/core/type/type.hpp>
#include <ql/graphic/sync/type/type.hpp>
#include <ql/graphic/sync/check-uninitialized/check-uninitialized.hpp>

#include <ql/graphic/update/update.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T>
		concept has_update_no_parameter_c = requires(T x) { x.update(); };

		template <typename T, typename... Args>
		constexpr bool has_function_update()
		{
			return has_update_no_parameter_c<T> || ql::has_update_for_manager<T>();
		}

		template <typename T>
		constexpr void apply_update(T& object, ql::update_manager& update)
		{
			if constexpr (has_update_no_parameter_c<T>)
				object.update();

				if constexpr (!ql::is_view<T>() && ql::has_update_for_manager<T>())
					update.update(object);
		}
	}	 // namespace detail

	template <typename T>
	requires (ql::is_or_has_sync<ql::modal_decay<T>>() || detail::has_function_update<ql::modal_decay<T>>())
	void sync_update(T& object, ql::state_manager& state, ql::update_manager& update)
	{
		ql::modal_apply(
			object,
			[&](auto& check)
			{
				constexpr bool order = true;
				auto iterate = [&](auto& tuple)
				{
					ql::size view_found_ctr = 0;

					ql::constexpr_iterate<ql::tuple_size<decltype(tuple)>()>(
						[&](auto i)
						{
							auto&& tuple_element = ql::tuple_value<i>(tuple);
							using U = decltype(tuple_element);

							if constexpr (ql::has_view_priority<U>())
							{
								update.event.push_view(tuple_element.view_priority);
								++view_found_ctr;
							}

							if constexpr (ql::is_view<U>())
							{
								if constexpr (ql::has_update_for_manager<U>())
									update.update(tuple_element);

								update.event.push_view(tuple_element);
								++view_found_ctr;
							}

							if constexpr (ql::has_modify_view<U>())
								if (update.event.m_views.size())
								{
									auto new_view = tuple_element.modify_view(update.event.m_views.back());
									update.event.push_view(new_view);
								}

							if constexpr (ql::has_modify_view_no_parameter<U>())
									update.event.push_view(tuple_element.modify_view());

							if constexpr (ql::is_or_has_sync<ql::modal_decay<U>>() || detail::has_function_update<ql::modal_decay<U>>())
								sync_update(tuple_element, state, update);

							if constexpr (ql::has_modify_view<U>() || ql::has_modify_view_no_parameter<U>())
								if (update.event.m_views.size())
									update.event.pop_view();
						}
					);

					if (view_found_ctr)
						update.event.pop_view(view_found_ctr);
				};
				auto check_apply_on_object = [&](auto& apply_check)
				{
					ql::modal_apply(
						apply_check,
						[&](auto& value)
						{
							if constexpr (detail::has_function_update<decltype(value)>())
								detail::apply_update(value, update);

							ql::sync_check_uninitialized(state);
						}
					);
				};

				if constexpr (ql::is_or_has_sync<decltype(check)>())
				{
					auto&& sync = ql::sync_resolve(check);
					if (!sync.sync_options.active || !sync.sync_options.update)
						return;
				}

				if constexpr (order)
					check_apply_on_object(check);

				ql::sync_modal_apply(check, [&](auto&& value)
				{
					auto tuple = ql::struct_to_tuple(value);
					iterate(tuple);
				});

				if constexpr (!order)
					check_apply_on_object(check);
			}
		);
	}
}	 // namespace ql
