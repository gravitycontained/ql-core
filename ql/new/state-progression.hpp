#pragma once

#include <ql/ql.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_arithmetic<T>())
	struct state_progression
	{
		std::vector<T> states;
		ql::size current_state = 0u;
		ql::size next_state = 0u;
		ql::f64 duration = 0.2;
		ql::f64 progress = 0.0;

		void set_state(ql::size state)
		{
			if (this->next_state != state)
			{
				this->next_state = state;
				this->progress = 0.0;
			}
		}

		ql::f64 normalized_progress() const
		{
			return ql::clamp(this->progress / this->duration, 0.0, 1.0);
		}

		bool is_running() const
		{
			return this->current_state != this->next_state && this->progress < this->duration;
		}

		T get() const
		{
			auto curve = ql::slope_curve(this->normalized_progress());
			return ql::linear_interpolation(this->states[this->current_state], this->states[this->next_state], curve);
		}

		void update(ql::f64 delta_time)
		{
			if (this->current_state != this->next_state)
			{
				this->progress += delta_time;
				if (this->progress >= this->duration)
				{
					this->current_state = this->next_state;
					this->progress = 0.0;
				}
			}
		}
	};
}