#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/time/clock/clock.hpp>
#include <ql/core/advanced-type/iterative/ema.hpp>

namespace ql
{
	struct fps_counter
	{
		QL_SOURCE fps_counter();

		QL_SOURCE void set_time_period(ql::u32 time_period);
		QL_SOURCE ql::u32 get_time_period() const;
		QL_SOURCE void reset();
		QL_SOURCE void measure();
		QL_SOURCE ql::u32 get_fps_u32() const;
		QL_SOURCE ql::f64 get_fps() const;

		bool start;
		ql::clock clock;
		ql::exponential_moving_average ema;
	};

}	 // namespace ql