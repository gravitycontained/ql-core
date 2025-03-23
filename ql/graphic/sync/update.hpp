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
					bool found_view = false;

					constexpr auto N = ql::tuple_find_index_of_type<decltype(tuple), ql::declare_unsync>();
					ql::constexpr_iterate<N>(
						[&](auto i)
						{
							auto&& tuple_element = ql::tuple_value<i>(tuple);
							if constexpr (ql::is_view<decltype(tuple_element)>())
							{
								if constexpr (ql::has_update_for_manager<decltype(tuple_element)>())
									update.update(tuple_element);

								update.event.push_view(tuple_element);
								found_view = true;
							}

							if constexpr (ql::is_or_has_sync<ql::modal_decay<decltype(tuple_element)>>() ||
														detail::has_function_update<ql::modal_decay<decltype(tuple_element)>>())
								sync_update(tuple_element, state, update);
						}
					);

					if (found_view)
						update.event.pop_view();
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
					if (!sync.declare_sync.active || !sync.declare_sync.update)
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
