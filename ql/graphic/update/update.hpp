#pragma once

#include <ql/core/definition/definition.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/event/event.hpp>

namespace ql
{
	struct state_manager;

	struct update
	{
		std::reference_wrapper<ql::event> event;
		std::reference_wrapper<state_manager> state_manager;
	};
}

#endif
