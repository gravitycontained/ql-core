#pragma once
#include <ql/core/advanced-type/interactive/type.hpp>

#include <ql/graphic/interactive/create-function.hpp>

namespace ql
{
	ql_interactive_function(init_interaction, false);
	ql_interactive_function(init, false);
	ql_interactive_function(update, false);
	ql_interactive_function(update_injection, false);
	ql_interactive_function(update_phase_signal_run, false);
	ql_interactive_function(update_phase_signal_detect, false);
	ql_interactive_function(provide, false);

}	 // namespace ql
