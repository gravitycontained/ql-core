#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/time/clock/small-clock/small-clock.hpp>
#include <ql/core/advanced-type/container/vector.hpp>

#include <functional>

namespace ql
{
	struct queue_manager
	{
		struct task_type
		{
			std::function<void()> task;
			ql::f64 phase_offset = 0.0;
			ql::size repeat = 1u;
			ql::size last_interval = ql::size_max;
			ql::f64 duration = ql::f64_epsilon;
		};

		ql::vector<task_type> tasks;
		ql::small_clock timer;
		ql::small_clock cleanup_timer;
		ql::f64 duration = 1.0;
		ql::f64 cleanup_interval = 3.0;
		bool relative = false;

		QL_SOURCE void set_duration(ql::f64 duration);
		QL_SOURCE void set_time_relative();
		QL_SOURCE void set_time_global();
		QL_SOURCE void reset_time();
		QL_SOURCE void update();
		QL_SOURCE ql::time get_time() const;
		QL_SOURCE queue_manager& add_task(std::function<void()>&& task);
		QL_SOURCE queue_manager& with_repeat(ql::size repeat = ql::size_max);
		QL_SOURCE queue_manager& with_phase(ql::f64 phase_offset);
		QL_SOURCE queue_manager& with_phase_end();
		QL_SOURCE queue_manager& with_duration(ql::f64 duration);

	protected:
		QL_SOURCE void cleanup();
	};
}