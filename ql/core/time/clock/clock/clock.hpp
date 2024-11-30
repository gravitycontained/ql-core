#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/time/time/time.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{
	class clock
	{
		ql::time m_pause;
		ql::time m_pause_sum;
		ql::time m_begin;
		mutable ql::time m_end;
		bool m_running;

	 public:
		clock(bool running = true)
		{
			this->init(running);
		}

		QL_SOURCE void reset();
		QL_SOURCE void pause();
		QL_SOURCE void reset_pause();
		QL_SOURCE void resume();
		QL_SOURCE bool is_running() const;
		QL_SOURCE bool is_paused() const;

		QL_SOURCE ql::time elapsed() const;
		QL_SOURCE std::string elapsed_str() const;
		QL_SOURCE ql::f64 elapsed_f() const;

		QL_SOURCE ql::time elapsed_reset();
		QL_SOURCE std::string elapsed_str_reset();
		QL_SOURCE ql::f64 elapsed_f_reset();

		QL_SOURCE void add(ql::f64 seconds);
		QL_SOURCE void add(ql::time time);
		QL_SOURCE void subtract(ql::f64 seconds);
		QL_SOURCE void subtract(ql::time time);

		QL_SOURCE bool has_elapsed(ql::f64 seconds) const;
		QL_SOURCE bool has_elapsed(ql::time duration) const;
		QL_SOURCE bool has_elapsed_reset(ql::f64 seconds);
		QL_SOURCE bool has_elapsed_reset(ql::time duration);

		QL_SOURCE void measure() const;
		QL_SOURCE void init(bool running);

		QL_SOURCE std::string to_string() const;
	};

	class halted_clock : public ql::clock
	{
	 public:
		halted_clock() : ql::clock(false) {}
	};

	QL_SOURCE ql::time get_remaining_time(ql::f64 progress, ql::clock timer);

	template <typename T, typename U>
	requires (ql::is_integer<T>() && ql::is_integer<U>())
	ql::time get_remaining_time(T start, U end, ql::clock timer)
	{
		return ql::get_remaining_time(ql::f64_cast(start) / end, timer.elapsed());
	}

}	 // namespace ql