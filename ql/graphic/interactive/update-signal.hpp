#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

#include <ql/graphic/interactive/type.hpp>
#include <ql/core/advanced-type/signal/signal.hpp>

namespace ql
{
	namespace detail
	{
		template <typename C>
		concept has_update_phase_signal_c = requires(C x, ql::signal_update_manager& update) { x.update_phase_signal(update); };

		template <typename C>
		constexpr bool has_update_phase_signal()
		{
			return has_update_phase_signal_c<C>;
		}

		template <typename C>
		concept has_update_phase_signal_no_parameter_c = requires(C x) { x.update_phase_signal(); };

		template <typename C>
		constexpr bool has_update_phase_signal_no_parameter()
		{
			return has_update_phase_signal_no_parameter_c<C>;
		}
	}

	template <typename T>
	requires (ql::is_or_has_interactive<T>())
	void interactive_update_phase_signal(T& object, ql::signal_update_manager& update)
	{
		if constexpr (ql::detail::has_update_phase_signal<decltype(object)>())
			object.update_phase_signal(update);

		if constexpr (ql::detail::has_update_phase_signal_no_parameter<decltype(object)>())
			object.update_phase_signal();

		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
					tuple,
					[&](auto& member)
					{
						if constexpr (ql::detail::has_update_phase_signal<decltype(member)>())
							member.update_phase_signal(update);

						if constexpr (ql::detail::has_update_phase_signal_no_parameter<decltype(member)>())
							member.update_phase_signal();

						if constexpr (ql::is_or_has_interactive<decltype(member)>())
							ql::interactive_update_phase_signal(member, update);
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