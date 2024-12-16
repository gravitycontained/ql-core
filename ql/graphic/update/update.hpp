#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/signal/signal-update-manager/signal-update-manager.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/event/event.hpp>
#include <ql/graphic/render/render.hpp>
#include <ql/graphic/sync/update.hpp>
#include <ql/graphic/init/init.hpp>

namespace ql
{
	template <typename T, typename U>
	concept has_update_c = requires(T x, U arg) { x.update(arg); };

	template <typename T, typename U>
	constexpr bool has_update()
	{
		return has_update_c<T, U>;
	}

	struct state_manager;

	struct update_manager
	{
		ql::event& event;
		state_manager& state_manager;
		ql::signal_update_manager& signal_update_manager;
		ql::render& render;
		ql::init_state& init_state;


		template <typename T>
		requires (
			ql::has_event_update<ql::modal_decay<T>>() || ql::has_update<T, ql::update_manager>() ||
			ql::has_update<T, ql::state_manager>()
		)
		void update(T& object)
		{
			if constexpr (ql::has_event_update<ql::modal_decay<T>>())
			{
				this->event.update(object);
			}

			if constexpr (ql::has_update<T, ql::update_manager>())
			{
				object.update(*this);
			}

			if constexpr (ql::has_update<T, ql::state_manager>())
			{
				object.update(this->state_manager);
			}
		}
	};
}

#endif
