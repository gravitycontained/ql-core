#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/transform/cast/cast.hpp>
#include <ql/core/transform/limit.hpp>

namespace ql
{
	template <typename T = ql::f64>
	struct exponential_moving_average
	{
		exponential_moving_average(ql::f64 time_period = 5.0)
		{
			this->time_period = time_period;
		}

		ql::f64 time_period;
		ql::size time_ctr = 0u;
		T last_ma = 0.0;

		void reset()
		{
			this->last_ma = T{};
			this->time_ctr = 0;
		}

		void add(T value)
		{
			++this->time_ctr;
			this->time_ctr = ql::min(ql::size_cast(this->time_period), this->time_ctr);

			auto m = 2.0 / (1.0 + ql::f64_cast(this->time_ctr));
			this->last_ma = m * value + (1 - m) * this->last_ma;
		}

		T get_average() const
		{
			return this->last_ma;
		}
	};
}	 // namespace ql