#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/transform/modal-apply.hpp>

#include <ql/graphic/sync/type/type.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T, typename U>
		concept has_inject_c = requires(T x, U arg) { x.inject(arg); };
		template <typename T>
		concept has_inject_no_parameter_c = requires(T x) { x.inject(); };

		template <typename T, typename... Args>
		constexpr bool has_function_inject()
		{
			if constexpr (has_inject_no_parameter_c<T>)
				return true;

			return ql::constexpr_or_chain<ql::variadic_size<Args...>()>([&](auto index)
			{
				return has_inject_c<T, ql::variadic_type<index, Args...>>;
			});
		}

		template <typename T, typename... Args>
		constexpr void apply_inject(T& object, Args&&... args)
		{
			if constexpr (detail::has_function_inject<T, Args...>())
			{
				if constexpr (has_inject_no_parameter_c<T>)
					object.inject();

				ql::constexpr_iterate<ql::variadic_size<Args...>()>(
					[&](auto index)
					{
						if constexpr (has_inject_c<T, ql::variadic_type<index, Args...>>)
							object.inject(ql::tuple_value<index>(ql::auto_tie(std::forward<Args>(args)...)));
					}
				);
			}
		}
	}	 // namespace detail

	template <typename T, typename... Args>
	requires (ql::is_or_has_sync<ql::modal_decay<T>>() || detail::has_function_inject<ql::modal_decay<T>, Args...>())
	void provide_action(T& object, Args&&... args)
	{
		constexpr bool order = true;

		ql::modal_apply(
			object,
			[&](auto& check)
			{
				auto iterate = [&](auto& tuple)
				{
					constexpr auto N = ql::tuple_find_index_of_type<decltype(tuple), ql::declare_unsync>();
					ql::constexpr_iterate<N>(
						[&](auto i)
						{
							auto&& tuple_element = ql::tuple_value<i>(tuple);
							if constexpr (
								ql::is_or_has_sync<ql::modal_decay<decltype(tuple_element)>>() ||
								detail::has_function_inject<ql::modal_decay<decltype(tuple_element)>, Args...>()
							)
								ql::provide_action(tuple_element, std::forward<Args>(args)...);
						}
					);
				};

				auto check_apply_on_object = [&](auto& apply_check)
				{
					ql::modal_apply(
						check,
						[&](auto& value)
						{
							if constexpr (detail::has_function_inject<decltype(value), Args...>())
								detail::apply_inject(value, std::forward<Args>(args)...);
						}
					);
				};
				
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


	template <typename T, typename... Args>
	requires (ql::is_or_has_sync<ql::modal_decay<T>>() || ql::detail::has_function_inject<ql::modal_decay<T>, Args...>())
	void provide(T& object, Args&&... args)
	{
		ql::println("injection count: ", ql::detail::sync_injection_request_count);
		if (ql::detail::sync_injection_request_count != 0u)
		{
			ql::println(
				ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_yellow,
				ql::color::aqua, ql::detail::sync_injection_request_count, ql::color::bright_gray, " new injection requests"
			);

			ql::provide_action(object, std::forward<Args>(args)...);

			ql::println(
				ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_yellow,
				ql::color::aqua, ql::detail::sync_injection_request_count, ql::color::bright_gray, " -> post new injection requests"
			);

		}
	}
}	 // namespace ql
