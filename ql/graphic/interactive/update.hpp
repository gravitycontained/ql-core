#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

#include <ql/graphic/interactive/type.hpp>
#include <ql/graphic/event/event.hpp>
#include <ql/graphic/update/update.hpp>


namespace ql
{
	struct state_manager;

	namespace detail
	{
		template <typename C>
		concept has_update_full_c = requires(C x, ql::update& update) { x.update(update); };

		template <typename C>
		constexpr bool has_update_full()
		{
			return has_update_full_c<C>;
		}

		template <typename C>
		concept has_update_no_parameter_c = requires(C x) { x.update(); };

		template <typename C>
		constexpr bool has_update_no_parameter()
		{
			return has_update_no_parameter_c<C>;
		}
	}

	template <typename T>
	requires (ql::is_or_has_interactive<T>())
	void interactive_update(T& object, ql::update& update)
	{
		if constexpr (ql::has_update<decltype(object)>())
			object.update(update.event);

		if constexpr (ql::detail::has_update_full<decltype(object)>())
			object.update(update);

		if constexpr (ql::detail::has_update_no_parameter<decltype(object)>())
			object.update();

		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
					tuple,
					[&](auto& member)
					{
						if constexpr (ql::has_update<decltype(member)>())
							member.update(update.event);

						if constexpr (ql::detail::has_update_full<decltype(member)>())
							member.update(update);

						if constexpr (ql::detail::has_update_no_parameter<decltype(member)>())
							member.update();

						if constexpr (ql::is_or_has_interactive<decltype(member)>())
							ql::interactive_update(member, update);
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

}	 // namespace ql