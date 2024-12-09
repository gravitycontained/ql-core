#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/signal/signal-update-manager/signal-update-manager.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/event/event.hpp>
#include <ql/graphic/render/render.hpp>
#include <ql/graphic/init/init.hpp>

namespace ql
{
	struct state_manager;

	struct update
	{
		ql::event& event;
		state_manager& state_manager;
		ql::signal_update_manager& signal_update_manager;
		ql::render& render;
		ql::init_state& init_state;
	};
}

#endif
