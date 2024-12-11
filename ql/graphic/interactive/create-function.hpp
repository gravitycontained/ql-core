#pragma once

#include <ql/graphic/update/update.hpp>

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

#define ql_interactive_function(function, order_top_bottom)                                                         \
                                                                                                                    \
	namespace detail                                                                                                  \
	{                                                                                                                 \
		template <typename T, typename U>                                                                               \
		concept has_##function##_c = requires(T x, U& arg) { x.##function##(arg); };                                    \
		template <typename T>                                                                                           \
		concept has_##function##_no_parameter_c = requires(T x) { x.##function##(); };                                  \
                                                                                                                    \
		template <typename T, typename... Args>                                                                         \
		constexpr bool has_function_##function##()                                                                      \
		{                                                                                                               \
			if constexpr (has_##function##_no_parameter_c<T>)                                                             \
				return true;                                                                                                \
                                                                                                                    \
			return ql::constexpr_or_chain<ql::variadic_size<Args...>()>(                                                  \
					[&](auto index) { return has_##function##_c<T, ql::variadic_type<index, Args...>>; }                      \
			);                                                                                                            \
		}                                                                                                               \
                                                                                                                    \
		template <typename T, typename... Args>                                                                         \
		constexpr void apply_##function##(T & object, Args&&... args)                                                   \
		{                                                                                                               \
			if constexpr (detail::has_function_##function##<T, Args...>())                                                \
			{                                                                                                             \
				if constexpr (has_##function##_no_parameter_c<T>)                                                           \
					object.##function##();                                                                                    \
                                                                                                                    \
				ql::constexpr_iterate<ql::variadic_size<Args...>()>(                                                        \
						[&](auto index)                                                                                         \
						{                                                                                                       \
							if constexpr (has_##function##_c<T, ql::variadic_type<index, Args...>>)                               \
								object.##function##(ql::tuple_value<index>(ql::auto_tie(std::forward<Args>(args)...)));             \
						}                                                                                                       \
				);                                                                                                          \
			}                                                                                                             \
		}                                                                                                               \
	}                                                                                                                 \
                                                                                                                    \
	template <typename T, typename... Args>                                                                           \
	requires (ql::is_or_has_interactive<T>())                                                                         \
	void interactive_##function##(T & object, Args && ... args)                                                       \
	{                                                                                                                 \
	                                                                                                                  \
	  constexpr bool order = order_top_bottom;                                                                        \
	                                                                                                                  \
		if constexpr (order)                                                                                            \
		{                                                                                                               \
			detail::apply_##function##(object, args...);                                                                  \
		}                                                                                                               \
		auto iterate = [&](auto& tuple)                                                                                 \
		{                                                                                                               \
			ql::tuple_iterate(                                                                                            \
					tuple,                                                                                                    \
					[&](auto& member)                                                                                         \
					{                                                                                                         \
						if constexpr (order && ql::is_or_has_interactive<decltype(member)>())                                   \
							interactive_##function##(member, args...);                                                            \
                                                                                                                    \
						else if constexpr (order && detail::has_function_##function##<decltype(member), Args...>())             \
							detail::apply_##function##(member, args...);                                                          \
                                                                                                                    \
						if constexpr (ql::is_container<decltype(member)>())                                                     \
						{                                                                                                       \
							if constexpr (ql::is_or_has_interactive<ql::container_subtype<decltype(member)>>())                   \
								for (auto& sub_member : member)                                                                     \
									interactive_##function##(sub_member, args...);                                                    \
                                                                                                                    \
							if constexpr (detail::has_function_##function##<ql::container_subtype<decltype(member)>, Args...>())  \
								for (auto& sub_member : member)                                                                     \
									detail::apply_##function##(sub_member, args...);                                                  \
                                                                                                                    \
						}                                                                                                       \
                                                                                                                    \
						if constexpr (!order && ql::is_or_has_interactive<decltype(member)>())                                  \
							interactive_##function##(member, args...);                                                            \
                                                                                                                    \
						else if constexpr (!order && detail::has_function_##function##<decltype(member), Args...>())            \
							detail::apply_##function##(member, args...);                                                          \
					}                                                                                                         \
			);                                                                                                            \
		};                                                                                                              \
		if constexpr (ql::has_interactive<T>())                                                                         \
		{                                                                                                               \
			auto tuple = ql::struct_to_tuple(object.interactive);                                                         \
			iterate(tuple);                                                                                               \
		}                                                                                                               \
		else if constexpr (ql::is_interactive<T>())                                                                     \
		{                                                                                                               \
			auto tuple = ql::struct_to_tuple(object);                                                                     \
			iterate(tuple);                                                                                               \
		}                                                                                                               \
		if constexpr (!order)                                                                                           \
		{                                                                                                               \
			detail::apply_##function##(object, args...);                                                                  \
		}                                                                                                               \
	}
