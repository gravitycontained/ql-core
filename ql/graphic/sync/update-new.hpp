#pragma once
#include <ql/graphic/sync/macro.hpp>
#include <ql/graphic/sync/type.hpp>
#include <ql/graphic/sync/list.hpp>

#include <ql/graphic/update/update.hpp>

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

#include <ql/graphic/state/state-manager/state-manager.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T>
		constexpr void apply_update_new(T& object, ql::state_manager& manager, bool& provided)
		{
			if constexpr (ql::is_sync<T>())
				if (!object.declare_sync.initialized)
				{
					if (!provided)
					{
						ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ql::to_string(":: ", "calling update injection"));
						manager.last_state_update_injection();
						provided = true;
					}
					
					ql::println(
						ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_gray,
						ql::string_left_spaced("uninitialized object ", 24), ql::color::aqua, &object, " ", ql::color::bright_blue, ql::type_name<decltype(object)>()
					);
					manager.last_state_initialize();
				}
		}
	}	 // namespace detail

	template <typename T>
	requires (ql::is_or_has_sync<ql::modal_decay<T>>())
	void sync_update_new_helper(T& object, ql::state_manager& manager, bool& provided)
	{
		ql::modal_apply(
			object,
			[&](auto& check)
			{
				constexpr bool order = false;
				auto iterate = [&](auto& tuple)
					{
						constexpr auto N = ql::tuple_find_index_of_type<decltype(tuple), ql::declare_unsync>();
						ql::constexpr_iterate<N>(
							[&](auto i)
							{
								auto&& tuple_element = ql::tuple_value<i>(tuple);

								if constexpr (
									ql::is_or_has_sync<ql::modal_decay<decltype(tuple_element)>>()
									)
									sync_update_new_helper(tuple_element, manager, provided);
							}
						);
					};

				auto check_apply_on_object = [&](auto& check)
					{
						ql::modal_apply(
							check,
							[&](auto& value)
							{
								detail::apply_update_new(value, manager, provided);
							}
						);
					};

				if constexpr (order)
				{
					check_apply_on_object(check);

					if constexpr (ql::has_sync<decltype(check)>())
						check_apply_on_object(check.sync);
				}


				if constexpr (ql::has_sync<decltype(check)>())
				{
					auto tuple = ql::struct_to_tuple(check.sync);
					iterate(tuple);
				}
				else if constexpr (ql::is_sync<decltype(check)>())
				{
					auto tuple = ql::struct_to_tuple(check);
					iterate(tuple);
				}


				if constexpr (!order)
				{
					if constexpr (ql::has_sync<decltype(check)>())
						check_apply_on_object(check.sync);

					check_apply_on_object(check);
				}
			}
		);
	}

	template <typename T>
	requires (ql::is_or_has_sync<T>())
	void sync_update_new(T& object, ql::state_manager& manager)
	{
		bool provided = false;
		sync_update_new_helper(object, manager, provided);
	}
}	 // namespace ql