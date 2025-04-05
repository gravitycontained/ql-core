#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/transform/interpolate/interpolate.hpp>

#ifdef QL_GRAPHIC
#include <ql/graphic/event/event.hpp>
#endif


namespace ql
{
	struct animation
	{
		ql::f64 duration = 1.0;
		ql::f64 progress = 0.0;
		ql::f64 progress_before = ql::f64_max;
		bool reversed = false;
		bool running = false;
		bool just_finish = false;
		bool just_finish_reverse = false;
		bool just_finish_no_reverse = false;
		bool internal_change_flag = false;
		bool progress_change_flag = true;

		QL_SOURCE void internal_reset();
		QL_SOURCE void reset();
		QL_SOURCE void start();
		QL_SOURCE void stop();
		QL_SOURCE void reset_and_start();
		QL_SOURCE void reset_and_start_reverse();
		QL_SOURCE void set_duration(ql::f64 duration);
		QL_SOURCE void update(ql::f64 frame_time);

#if defined QL_GRAPHIC
		QL_SOURCE void update(const ql::event& event);
#endif

		QL_SOURCE bool is_running() const;
		QL_SOURCE bool is_reversed() const;
		QL_SOURCE bool changed() const;
		QL_SOURCE void go_forwards();
		QL_SOURCE void go_backwards();
		QL_SOURCE bool just_finished() const;
		QL_SOURCE bool just_finished_reverse() const;
		QL_SOURCE bool just_finished_no_reverse() const;
		QL_SOURCE bool has_progress() const;
		QL_SOURCE void set_progress(ql::f64 progress, bool backwards = false);
		QL_SOURCE ql::f64 get_progress() const;
		QL_SOURCE ql::f64 get_curve_progress(ql::f64 curve = 1.5) const;
		QL_SOURCE ql::f64 get_double_curve_progress(ql::f64 curve = 1.5) const;
		QL_SOURCE ql::f64 get_s_curve_progress(ql::f64 curve = 2) const;
	};

	template <typename T>
	struct value_animation : animation
	{
		T begin;
		T end;
		double curve = 1.5;
		bool use_double_curve = true;

		void set_begin(T value)
		{
			this->begin = value;
		}

		void set_end(T value)
		{
			this->end = value;
		}

		void set_range(T begin, T end)
		{
			this->begin = begin;
			this->end = end;
		}

		void set_curve(ql::f64 curve)
		{
			this->curve = curve;
		}

		void enable_double_curve()
		{
			this->use_double_curve = true;
		}

		void disable_double_curve()
		{
			this->use_double_curve = false;
		}

		ql::f64 get_resulting_progress() const
		{
			if (this->use_double_curve)
			{
				return this->get_double_curve_progress(this->curve);
			}
			else
			{
				return this->get_curve_progress(this->curve);
			}
		}

		T get() const
		{
			auto p = this->get_resulting_progress();
			return ql::linear_interpolation(this->begin, this->end, p);
		}

		T get(T begin) const
		{
			auto p = this->get_resulting_progress();
			return ql::linear_interpolation(begin, this->end, p);
		}

		T get(T begin, T end) const
		{
			auto p = this->get_resulting_progress();
			return ql::linear_interpolation(begin, end, p);
		}
	};

}	 // namespace ql