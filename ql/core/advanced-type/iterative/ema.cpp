
#include <ql/core/advanced-type/iterative/ema.hpp>
#include <ql/core/transform/cast/cast.hpp>
#include <ql/core/transform/limit.hpp>

namespace ql
{
	void ql::exponential_moving_average::reset()
	{
		this->last_ma = 0.0;
		this->time_ctr = 0;
	}

	void ql::exponential_moving_average::add(ql::f64 value)
	{
		++this->time_ctr;
		this->time_ctr = ql::min(ql::size_cast(this->time_period), this->time_ctr);

		auto m = 2.0 / (1.0 + ql::f64_cast(this->time_ctr));
		this->last_ma = m * value + (1 - m) * this->last_ma;
	}

	ql::f64 ql::exponential_moving_average::get_average() const
	{
		return this->last_ma;
	}
}	 // namespace ql