#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/advanced-type/interactive/type.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T, typename U>
		concept has_inject_c = requires(T x, U& arg) { x.inject(arg); };
		template <typename T>
		concept has_inject_no_parameter_c = requires(T x) { x.inject(); };

		template <typename T, typename... Args>
		constexpr bool has_function_inject()
		{
			if constexpr (has_inject_no_parameter_c<T>)
				return true;
			return ql::constexpr_or_chain<ql::variadic_size<Args...>()>([&](auto index)
																																	{ return has_inject_c<T, ql::variadic_type<index, Args...>>; });
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
	requires (ql::is_or_has_interactive<T>())
	void provide(T& object, Args&&... args)
	{
		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
					tuple,
					[&](auto& member)
					{
						if constexpr (ql::is_or_has_interactive<decltype(member)>())
						{
							detail::apply_inject(member, args...);
							provide(member, args...);
						}

						else if constexpr (detail::has_function_inject<decltype(member), Args...>())
							detail::apply_inject(member, args...);

						if constexpr (ql::is_container<decltype(member)>())
						{
							if constexpr (ql::is_or_has_interactive<ql::container_subtype<decltype(member)>>())
								for (auto& sub_member : member)
								{
									detail::apply_inject(sub_member, args...);
									provide(sub_member, args...);
								}
						}
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
	}
}