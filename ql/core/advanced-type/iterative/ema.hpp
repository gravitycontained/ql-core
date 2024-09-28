#pragma once

#include <ql/core/definition/definition.hpp>

namespace ql
{
	struct exponential_moving_average
	{
		exponential_moving_average(ql::f64 time_period = 5.0)
		{
			this->time_period = time_period;
		}

		ql::f64 time_period;
		ql::size time_ctr = 0u;
		ql::f64 last_ma = 0.0;

		QL_SOURCE void reset();
		QL_SOURCE void add(ql::f64 value);
		QL_SOURCE ql::f64 get_average() const;
	};
}