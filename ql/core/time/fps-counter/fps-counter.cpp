#include <ql/core/time/fps-counter/fps-counter.hpp>

namespace ql
{
	ql::fps_counter::fps_counter()
	{
		this->reset();
	}

	void ql::fps_counter::set_time_period(ql::u32 time_period)
	{
		this->ema.time_period = time_period;
	}

	ql::u32 ql::fps_counter::get_time_period() const
	{
		return ql::u32_cast(this->ema.time_period);
	}

	void ql::fps_counter::reset()
	{
		this->ema.reset();
		this->ema.time_period = 100u;
		this->clock.reset();
		this->start = false;
	}

	void ql::fps_counter::measure()
	{
		if (!this->start)
		{
			this->start = true;
			this->clock.reset();
		}
		else
		{
			this->ema.add(this->clock.elapsed_f_reset());
		}
	}

	ql::u32 ql::fps_counter::get_fps_u32() const
	{
		if (!this->ema.get_average())
		{
			return 0u;
		}
		return ql::u32_cast(1.0 / this->ema.get_average());
	}

	ql::f64 ql::fps_counter::get_fps() const
	{
		if (!this->ema.get_average())
		{
			return 0.0;
		}
		return 1.0 / this->ema.get_average();
	}
}	 // namespace ql 