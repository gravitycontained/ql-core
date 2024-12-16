#pragma once

#include <ql/graphic/sync/macro.hpp>
#include <ql/graphic/sync/type.hpp>

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T, typename U>
		concept has_init_c = requires(T x, U arg) { x.init(arg); };
		template <typename T>
		concept has_init_no_parameter_c = requires(T x) { x.init(); };

		template <typename T, typename... Args>
		constexpr bool has_function_init()
		{
			if constexpr (has_init_no_parameter_c<T>)
				return true;
			return ql::constexpr_or_chain<ql::variadic_size<Args...>()>([&](auto index)

			{
				return has_init_c<T, ql::variadic_type<index, Args...>>;
			});
		}

		template <typename T, typename... Args>
		constexpr void apply_init(T& object, Args&&... args)
		{
			if constexpr (ql::is_sync<T>())
			{
				if (!object.declare_sync.initialized)
				{
					if constexpr (detail::has_function_init<T, Args...>())
					{
						if constexpr (has_init_no_parameter_c<T>)
							object.init();

						ql::constexpr_iterate<ql::variadic_size<Args...>()>(
							[&](auto index)
							{
								if constexpr (has_init_c<T, ql::variadic_type<index, Args...>>)
									object.init(ql::tuple_value<index>(ql::auto_tie(std::forward<Args>(args)...)));
							}
						);
					}

					object.declare_sync.initialized = true;
				}
			}

			else if constexpr (detail::has_function_init<T, Args...>())
			{
				if constexpr (has_init_no_parameter_c<T>)
					object.init();

				ql::constexpr_iterate<ql::variadic_size<Args...>()>(
					[&](auto index)
					{
						if constexpr (has_init_c<T, ql::variadic_type<index, Args...>>)
							object.init(ql::tuple_value<index>(ql::auto_tie(std::forward<Args>(args)...)));
					}
				);
			}
		}
	}	 // namespace detail

	template <typename T, typename... Args>
	requires (ql::is_or_has_sync<ql::modal_decay<T>>() || detail::has_function_init<ql::modal_decay<T>, Args...>())
	void sync_init(T& object, Args&&... args)
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
								ql::is_or_has_sync<ql::modal_decay<decltype(tuple_element)>>() ||
								detail::has_function_init<ql::modal_decay<decltype(tuple_element)>, Args...>()
							)
								sync_init(tuple_element, std::forward<Args>(args)...);
						}
					);
				};

				auto check_apply_on_object = [&](auto& apply_check)
				{
					ql::modal_apply(
						apply_check,
						[&](auto& value)
						{
							if constexpr (ql::is_sync<decltype(value)>() || detail::has_function_init<decltype(value), Args...>())
								detail::apply_init(value, std::forward<Args>(args)...);
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
}	 // namespace ql