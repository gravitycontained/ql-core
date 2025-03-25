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
	void provide(T& object, Args&&... args)
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
								provide(tuple_element, std::forward<Args>(args)...);
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
				if constexpr (ql::debug::print)
					ql::println(
						ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_yellow, "provide on ",
						ql::color::aqua, ql::type_name<decltype(check)>(), ql::color::bright_gray, " ", ql::color::bright_blue, &check
					);
				
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
