#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/constexpr/constexpr.hpp>

#include <ql/graphic/interactive/type.hpp>
#include <ql/graphic/init/init.hpp>

namespace ql
{

	template <typename C>
	concept has_init_c = requires(C x, ql::init_state& state) { x.init(state); };

	template <typename C>
	constexpr bool has_init()
	{
		return has_init_c<C>;
	}

	namespace detail
	{
		template <typename C>
		concept has_init_no_parameter_c = requires(C x) { x.init(); };

		template <typename C>
		constexpr bool has_init_no_parameter()
		{
			return has_init_no_parameter_c<C>;
		}
	}

	template <typename T>
	requires (ql::is_or_has_interactive<T>())
	void interactive_init(T& object, const ql::init_state& state)
	{
		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
				tuple,
				[&](auto& member)
				{
					if constexpr (ql::is_or_has_interactive<decltype(member)>())
						ql::interactive_init(member, state);

					if constexpr (ql::has_init<decltype(member)>())
						member.init(state);

					else if constexpr (ql::detail::has_init_no_parameter<decltype(member)>())
						member.init();
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

		if constexpr (ql::has_init<decltype(object)>())
			object.init(state);

		else if constexpr (ql::detail::has_init_no_parameter<decltype(object)>())
			object.init();

	}

}	 // namespace ql