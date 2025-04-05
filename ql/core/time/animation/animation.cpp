#include <ql/core/time/animation/animation.hpp>

#include <ql/core/transform/slope/slope.hpp>

namespace ql
{
	void ql::animation::internal_reset()
	{
		this->just_finish = false;
		this->just_finish_reverse = false;
		this->just_finish_no_reverse = false;
		this->internal_change_flag = false;
	}

	void ql::animation::reset()
	{
		this->progress = 0.0;
		this->running = false;
		this->reversed = false;
		this->internal_reset();
	}

	void ql::animation::start()
	{
		this->running = true;
	}

	void ql::animation::stop()
	{
		this->running = true;
	}

	void ql::animation::reset_and_start()
	{
		this->progress = 0.0;
		this->running = true;
		this->reversed = false;
		this->internal_reset();
	}

	void ql::animation::reset_and_start_reverse()
	{
		this->progress = 1.0;
		this->running = true;
		this->reversed = true;
		this->internal_reset();
	}

	void ql::animation::set_duration(ql::f64 duration)
	{
		this->duration = duration;
	}

	void ql::animation::update(ql::f64 frame_time)
	{
		if (this->just_finish && !this->internal_change_flag)
		{
			this->running = false;
		}
		this->internal_change_flag = false;
		this->just_finish = false;
		this->just_finish_reverse = false;
		this->just_finish_no_reverse = false;

		if (this->running)
		{
			auto before = this->progress;

			auto f = frame_time / this->duration;
			if (this->reversed)
			{
				this->progress -= f;
			}
			else
			{
				this->progress += f;
			}

			this->progress = ql::clamp(this->progress);
			if (this->progress == 1.0 && before < 1.0)
			{
				this->just_finish = this->just_finish_no_reverse = true;
			}
			else if (this->progress == 0.0 && before > 0.0)
			{
				this->just_finish = this->just_finish_reverse = true;
			}
		}

		this->progress_change_flag = (this->progress != this->progress_before);
		this->progress_before = this->progress;
	}
#if defined QL_GRAPHIC
	void ql::animation::update(const ql::event& event)
	{
		this->update(event.frame_time_f());
	}
#endif
	void ql::animation::go_forwards()
	{
		this->start();
		this->reversed = false;
		this->internal_change_flag = true;
	}

	void ql::animation::go_backwards()
	{
		this->start();
		this->reversed = true;
		this->internal_change_flag = true;
	}

	bool ql::animation::is_running() const
	{
		return this->running;
	}

	bool ql::animation::is_reversed() const
	{
		return this->reversed;
	}

	bool ql::animation::changed() const
	{
		return this->progress_change_flag;
	}

	bool ql::animation::just_finished() const
	{
		return this->just_finish;
	}

	bool ql::animation::just_finished_reverse() const
	{
		return this->just_finish_reverse;
	}

	bool ql::animation::just_finished_no_reverse() const
	{
		return this->just_finish_no_reverse;
	}

	bool ql::animation::has_progress() const
	{
		return ql::bool_cast(this->progress);
	}

	void ql::animation::set_progress(ql::f64 progress, bool backwards)
	{
		this->progress = ql::clamp(progress);
		if (backwards)
		{
			this->go_backwards();
		}
		else
		{
			this->go_forwards();
		}
	}

	ql::f64 ql::animation::get_progress() const
	{
		return this->progress;
	}

	ql::f64 ql::animation::get_curve_progress(ql::f64 curve) const
	{
		return ql::slope_curve(this->progress, curve);
	}

	ql::f64 ql::animation::get_double_curve_progress(ql::f64 curve) const
	{
		return ql::slope_double_curve(this->progress, curve);
	}

	ql::f64 ql::animation::get_s_curve_progress(ql::f64 curve) const
	{
		return ql::s_curve(this->progress, curve);
	}

}	 // names
