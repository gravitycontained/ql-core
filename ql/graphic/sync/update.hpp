#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>
#include <ql/graphic/sync/type.hpp>
#include <ql/graphic/sync/macro.hpp>

#include <ql/graphic/update/update.hpp>

namespace ql
{
	struct sync_update_info
	{
		bool needs_provide_and_initialize = false;
	}; 

	namespace detail
	{
		template <typename T, typename U>
		concept has_update_c = requires(T x, U arg) { x.update(arg); };

		template <typename T, typename U>
		constexpr bool has_update()
		{
			return has_update_c<T, U>;
		}

		template <typename T>
		concept has_update_no_parameter_c = requires(T x) { x.update(); };


		template <typename T>
		constexpr bool has_update_for_manager()
		{
			return (
				ql::has_event_update<ql::modal_decay<T>>() || ql::has_update<T, ql::update_manager>() ||
				ql::has_update<T, ql::state_manager>()
			);
		}

		template <typename T, typename... Args>
		constexpr bool has_function_update()
		{
			if constexpr (has_update_no_parameter_c<T>)
				return true;
			return ql::constexpr_or_chain<ql::variadic_size<Args...>()>(
				[&](auto index)
				{ return has_update_c<ql::variadic_type<index, Args...>, T>; }
			);
		}

		template <typename T, typename... Args>
		constexpr void apply_update(T& object, Args&&... args)
		{
			if constexpr (detail::has_function_update<T, Args...>())
			{
				if constexpr (has_update_no_parameter_c<T>)
					object.update();
				ql::constexpr_iterate<ql::variadic_size<Args...>()>(
					[&](auto index)
					{
						using check_type = ql::variadic_type<index, Args...>;
						if constexpr (has_update_for_manager<T>())
							ql::tuple_value<index>(ql::auto_tie(std::forward<Args>(args)...)).update(object);
					}
				);
			}
		}
	}	 // namespace detail

	template <typename T, typename... Args>
	requires (ql::is_or_has_sync<ql::modal_decay<T>>() || detail::has_function_update<ql::modal_decay<T>, Args...>())
	void sync_update_helper(T& object, sync_update_info& info, Args&&... args)
	{
		ql::modal_apply(
			object,
			[&](auto& check)
			{
				constexpr bool order = true;
				auto iterate = [&](auto& tuple)
				{
					constexpr auto N = ql::tuple_find_index_of_type<decltype(tuple), ql::declare_unsync>();
					ql::constexpr_iterate<N>(
						[&](auto i)
						{
							auto&& tuple_element = ql::tuple_value<i>(tuple);
							if constexpr (ql::is_or_has_sync<ql::modal_decay<decltype(tuple_element)>>() ||
														detail::has_function_update<ql::modal_decay<decltype(tuple_element)>, Args...>())
								sync_update_helper(tuple_element, info, std::forward<Args>(args)...);
						}
					);
				};
				auto check_apply_on_object = [&](auto& apply_check)
				{
					ql::modal_apply(
						apply_check,
						[&](auto& value)
						{
							if constexpr (ql::is_sync<decltype(value)>())
							{
								if (!value.declare_sync.initialized)
								{
									info.needs_provide_and_initialize = true;
									ql::println(
										ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_gray,
										ql::string_left_spaced("uninitialized object ", 24), ql::color::aqua, &value, " ", ql::color::bright_blue, ql::type_name<decltype(value)>()
									);
								}
							}
							if constexpr (detail::has_function_update<decltype(value), Args...>())
								detail::apply_update(value, std::forward<Args>(args)...);
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

	template <typename T, typename ... Args>
	requires (ql::is_or_has_sync<T>())
	void sync_update(T& object, ql::state_manager& manager, Args&&... args)
	{
		sync_update_info info;
		sync_update_helper(object, info, std::forward<Args>(args)...);

		if (info.needs_provide_and_initialize)
		{
			manager.last_state_provide();
			manager.last_state_initialize();
		}
	}
}	 // namespace ql
