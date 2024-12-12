#pragma once

#include <ql/graphic/interactive/create-function.hpp>
#include <ql/core/advanced-type/interactive/type.hpp>
#include <ql/graphic/interactive/definition-list.hpp>

#include <ql/graphic/update/update.hpp>

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T, typename U>
		concept has_init_c = requires(T x, U& arg) { x.init(arg); };
		template <typename T>
		concept has_init_no_parameter_c = requires(T x) { x.init(); };

		template <typename T, typename... Args>
		constexpr bool has_function_init()
		{
			if constexpr (has_init_no_parameter_c<T>)
				return true;
			return ql::constexpr_or_chain<ql::variadic_size<Args...>()>([&](auto index)
																																	{ return has_init_c<T, ql::variadic_type<index, Args...>>; });
		}

		template <typename T, typename... Args>
		constexpr void apply_init(T& object, Args&&... args)
		{
			if constexpr (detail::has_function_init<T, Args...>())
			{
				if constexpr (has_init_no_parameter_c<T>)
				{
					if constexpr (ql::is_interactive<T>())
					{
						if (!object.declare_interactive.initialized)
						{
							ql::println("initialized declare_interactive initialized");
							object.init();
							object.declare_interactive.initialized = true;
						}
					}
					else
						object.init();

					ql::constexpr_iterate<ql::variadic_size<Args...>()>(
						[&](auto index)
						{
							if constexpr (has_init_c<T, ql::variadic_type<index, Args...>>)
							{
								if constexpr (ql::is_interactive<T>())
								{
									if (!object.declare_interactive.initialized)
									{
										ql::println("initialized declare_interactive initialized");
										object.init(ql::tuple_value<index>(ql::auto_tie(std::forward<Args>(args)...)));
										object.declare_interactive.initialized = true;
									}
								}
								else
									object.init(ql::tuple_value<index>(ql::auto_tie(std::forward<Args>(args)...)));
							}
						}
					);
				}
			}
		}
	}	 // namespace detail

	template <typename T, typename... Args>
	requires (ql::is_or_has_interactive<T>())
	void interactive_init(T& object, Args&&... args)
	{
		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
					tuple,
					[&](auto& member)
					{
						if constexpr (ql::is_container<decltype(member)>())
						{
							if constexpr (ql::is_or_has_interactive<ql::container_subtype<decltype(member)>>())
								for (auto& sub_member : member)
									interactive_init(sub_member, args...);
							if constexpr (detail::has_function_init<ql::container_subtype<decltype(member)>, Args...>())
								for (auto& sub_member : member)
									detail::apply_init(sub_member, args...);
						}
						if constexpr (ql::is_or_has_interactive<decltype(member)>())
							interactive_init(member, args...);
						else if constexpr (detail::has_function_init<decltype(member), Args...>())
							detail::apply_init(member, args...);
					}
			);
		};
		if constexpr (ql::has_interactive<T>())
		{
			auto tuple = ql::struct_to_tuple(object.interactive);
			iterate(tuple);
		}
		else if constexpr (ql::is_interactive<T>())
		{
			auto tuple = ql::struct_to_tuple(object);
			iterate(tuple);
		}

		detail::apply_init(object, args...);
	}
}