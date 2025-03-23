#pragma once

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

#define ql_sync_function(function, order_top_bottom)																																																																			\
																																																																																													\
namespace detail																																																																																					\
{																																																																																													\
	template <typename T, typename U>																																																																												\
	concept has_##function##_c = requires(T x, U arg) { x.##function##(arg); };																																																							\
	template <typename T>																																																																																		\
	concept has_##function##_no_parameter_c = requires(T x) { x.##function##(); };																																																					\
																																																																																													\
	template <typename T, typename... Args>																																																																									\
	constexpr bool has_function_##function##()																																																																							\
	{																																																																																												\
		if constexpr (has_##function##_no_parameter_c<T>)																																																																			\
			return true;																																																																																				\
																																																																																													\
		return ql::constexpr_or_chain<ql::variadic_size<Args...>()>(																																																													\
			[&](auto index) {																																																																																		\
				return has_##function##_c<ql::variadic_type<index, Args...>, T> ||																																																								\
							 has_##function##_c<T, ql::variadic_type<index, Args...>>;																																																									\
			}																																																																																										\
		);																																																																																										\
	}																																																																																												\
																																																																																													\
	template <typename T, typename... Args>																																																																									\
	constexpr void apply_##function##(T& object, Args&&... args)																																																														\
	{																																																																																												\
		if constexpr (detail::has_function_##function##<T, Args...>())																																																												\
		{																																																																																											\
			if constexpr (has_##function##_no_parameter_c<T>)																																																																		\
				object.##function##();																																																																														\
																																																																																													\
			ql::constexpr_iterate<ql::variadic_size<Args...>()>(																																																																\
				[&](auto index)																																																																																		\
				{																																																																																									\
					if constexpr (has_##function##_c<ql::variadic_type<index, Args...>, T>)																																																					\
						ql::tuple_value<index>(ql::auto_tie(std::forward<Args>(args)...)).##function##(object);																																												\
																																																																																													\
					else if constexpr (has_##function##_c<T, ql::variadic_type<index, Args...>>)																																																		\
						object.##function##(ql::tuple_value<index>(ql::auto_tie(std::forward<Args>(args)...)));																																												\
				}																																																																																									\
			);																																																																																									\
		}																																																																																											\
	}																																																																																												\
}																																																																																													\
																																																																																													\
template <typename T, typename... Args>																																																																										\
requires (ql::is_or_has_sync<ql::modal_decay<T>>() || detail::has_function_##function##<ql::modal_decay<T>, Args...>())																																		\
void sync_##function##(T& object, Args&&... args)																																																																					\
{																																																																																													\
	ql::modal_apply(																																																																																				\
		object,																																																																																								\
		[&](auto& check)																																																																																			\
		{																																																																																											\
			constexpr bool order = order_top_bottom;																																																																						\
			auto iterate = [&](auto& tuple)																																																																											\
			{																																																																																										\
				constexpr auto N = ql::tuple_find_index_of_type<decltype(tuple), ql::declare_unsync>();																																														\
				ql::constexpr_iterate<N>(																																																																													\
					[&](auto i)																																																																																			\
					{																																																																																								\
						auto&& tuple_element = ql::tuple_value<i>(tuple);																																																															\
																																																																																													\
						if constexpr (ql::is_or_has_sync<ql::modal_decay<decltype(tuple_element)>>() || detail::has_function_##function##<ql::modal_decay<decltype(tuple_element)>, Args...>())				\
							sync_##function##(tuple_element, std::forward<Args>(args)...);																																																							\
					}																																																																																								\
				);																																																																																								\
			};																																																																																									\
																																																																																													\
			auto check_apply_on_object = [&](auto& apply_check)																																																																	\
			{																																																																																										\
				ql::modal_apply(																																																																																	\
					apply_check,																																																																																		\
					[&](auto& value)																																																																																\
					{																																																																																								\
						if constexpr (detail::has_function_##function##<decltype(value), Args...>())																																																	\
							detail::apply_##function##(value, std::forward<Args>(args)...);																																																							\
					}																																																																																								\
				);																																																																																								\
			};																																																																																									\
																																																																																													\
			if constexpr (order)																																																																																\
				ql::sync_apply_soft<true>(check, [&](auto&& value)																																																																\
				{																																																																																									\
					check_apply_on_object(value);																																																																										\
				});																																																																																								\
																																																																																													\
			ql::sync_modal_apply(check, [&](auto&& value)																																																																							\
			{																																																																																										\
				auto tuple = ql::struct_to_tuple(value);																																																																					\
				iterate(tuple);																																																																																		\
			});																																																																																									\
																																																																																													\
			if constexpr (!order)																																																																																\
				ql::sync_apply_soft<false>(check, [&](auto&& value)																																																																\
				{																																																																																									\
					check_apply_on_object(value);																																																																										\
				});																																																																																								\
		}																																																																																											\
	);																																																																																											\
}																																																																																													\
