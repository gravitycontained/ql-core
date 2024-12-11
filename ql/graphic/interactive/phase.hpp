#pragma once

#define ql_add_phase(function)                                           \
	namespace detail                                                       \
	{                                                                      \
		template <typename C>                                                \
		concept has_##function##_c = requires(C x) { x.##function##(); };    \
                                                                         \
		template <typename T>                                                \
		constexpr void apply_if_##function##(T & object)                     \
		{                                                                    \
			if constexpr (detail::has_##function##_c<T>)                       \
				object.##function##();                                           \
		}                                                                    \
	}                                                                      \
                                                                         \
	template <typename T>                                                  \
	requires (ql::is_or_has_interactive<T>())                              \
	void interactive_##function##(T & object)                              \
	{                                                                      \
		detail::apply_if_##function##(object);                               \
		auto iterate = [&](auto& tuple)                                      \
		{                                                                    \
			ql::tuple_iterate(                                                 \
					tuple,                                                         \
					[&](auto& member)                                              \
					{                                                              \
						detail::apply_if_##function##(member);                       \
                                                                         \
						if constexpr (ql::is_or_has_interactive<decltype(member)>()) \
							interactive_##function##(member);                          \
					}                                                              \
			);                                                                 \
		};                                                                   \
		if constexpr (ql::has_interactive<T>())                              \
		{                                                                    \
			auto tuple = ql::struct_to_tuple(object.interactive);              \
			iterate(tuple);                                                    \
		}                                                                    \
		else if constexpr (ql::is_interactive<T>())                          \
		{                                                                    \
			auto tuple = ql::struct_to_tuple(object);                          \
			iterate(tuple);                                                    \
		}                                                                    \
	}                                                                      