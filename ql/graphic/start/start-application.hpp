#pragma once

#include <ql/graphic/state/state.hpp>
#include <ql/graphic/sync/state.hpp>
#include <ql/graphic/start/options.hpp>

namespace ql
{
	namespace detail
	{
		template<typename T>
		struct type_state : ql::base_state
		{
			T main;
			ql_sync_state(this->main);
		};
	}

	template <class App>
	void start_application(start_options options = {})
	{
		ql::state_manager state_manager;
		state_manager.set_title(options.name);
		state_manager.set_antialiasing_level(options.antialiasing);
		state_manager.set_dimension(options.dimension);

		state_manager.add_state<ql::detail::type_state<App>>();

		if (options.framerate_limit != ql::u32_max)
			state_manager.set_framerate_limit(options.framerate_limit);

		state_manager.game_loop();
	}
}