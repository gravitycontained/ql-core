#pragma once
#include <ql/graphic/sync/type/type.hpp>
#include <ql/graphic/sync/draw.hpp>
#include <ql/graphic/sync/init.hpp>
#include <ql/graphic/sync/update.hpp>

#include <ql/graphic/sync/macro.hpp>
#include <functional>

namespace ql
{
	ql_sync_function(init_before, true);
	ql_sync_function(update_injection, false);
	ql_sync_function(update_phase_signal_run, false);
	ql_sync_function(update_phase_signal_detect, false);
	ql_sync_function(provide, false);

}	 // namespace ql
