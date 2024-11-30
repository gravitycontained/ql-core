#include <ql/core/time/clock/clock/clock.hpp>

namespace ql
{
	void ql::clock::reset()
	{
		this->m_begin = ql::time::clock_time();
		this->m_running = true;
		this->m_pause_sum = ql::u64{};
	}

	void ql::clock::pause()
	{
		if (this->is_running())
		{
			this->measure();
		}
		this->m_running = false;
		this->m_pause = ql::time::clock_time();
	}

	void ql::clock::reset_pause()
	{
		if (this->is_running())
		{
			this->measure();
		}
		this->m_begin = ql::time::clock_time();
		this->m_running = false;
		this->m_pause = ql::time::clock_time();
		this->m_pause_sum = ql::u64{};
	}

	ql::time ql::clock::elapsed() const
	{
		if (this->is_running())
		{
			this->measure();
		}
		return this->m_end - (this->m_begin + this->m_pause_sum);
	}

	std::string ql::clock::elapsed_str() const
	{
		return this->elapsed().string();
	}

	ql::f64 ql::clock::elapsed_f() const
	{
		return this->elapsed().secs_f();
	}

	ql::time ql::clock::elapsed_reset()
	{
		auto result = this->elapsed();
		this->reset();
		return result;
	}

	std::string ql::clock::elapsed_str_reset()
	{
		auto result = this->elapsed_str();
		this->reset();
		return result;
	}

	ql::f64 ql::clock::elapsed_f_reset()
	{
		auto result = this->elapsed_f();
		this->reset();
		return result;
	}

	void ql::clock::add(ql::f64 seconds)
	{
		this->m_begin += ql::u64_cast(seconds * ql::time::nsecs_in_sec);
	}

	void ql::clock::add(ql::time time)
	{
		this->m_begin += time;
	}

	void ql::clock::subtract(ql::f64 seconds)
	{
		this->m_begin -= ql::u64_cast(seconds * ql::time::nsecs_in_sec);
	}

	void ql::clock::subtract(ql::time time)
	{
		this->m_begin -= time;
	}

	bool ql::clock::has_elapsed(ql::f64 seconds) const
	{
		return this->elapsed_f() > seconds;
	}

	bool ql::clock::has_elapsed(ql::time duration) const
	{
		return this->elapsed() > duration;
	}

	bool ql::clock::has_elapsed_reset(ql::f64 seconds)
	{
		auto result = this->has_elapsed(seconds);
		if (result)
		{
			this->reset();
		}
		return result;
	}

	bool ql::clock::has_elapsed_reset(ql::time duration)
	{
		auto result = this->has_elapsed(duration);
		if (result)
		{
			this->reset();
		}
		return result;
	}

	void ql::clock::resume()
	{
		if (this->is_running())
		{
			return;
		}
		this->m_running = true;
		this->m_pause_sum += (ql::time::clock_time() - this->m_pause);
	}

	bool ql::clock::is_running() const
	{
		return this->m_running;
	}

	bool ql::clock::is_paused() const
	{
		return !this->m_running;
	}

	void ql::clock::measure() const
	{
		if (this->is_running())
		{
			this->m_end = ql::time::clock_time();
		}
	}

	void ql::clock::init(bool running)
	{
		this->m_begin = ql::time::clock_time();
		this->m_end = this->m_begin;
		this->m_pause_sum = ql::u64{};
		this->m_running = running;
		if (this->is_paused())
		{
			this->m_pause = this->m_begin;
		}
	}

	std::string ql::clock::to_string() const
	{
		return this->elapsed().to_string();
	}

	std::ostream& operator<<(std::ostream& os, const ql::clock& clock)
	{
		return (os << clock.elapsed().string());
	}

	std::ostream& operator<<(std::ostream& os, const ql::halted_clock& clock)
	{
		return (os << clock.elapsed().string());
	}

	ql::time get_remaining_time(ql::f64 progress, ql::clock timer)
	{
		return ql::get_remaining_time(progress, timer.elapsed());
	}

}	 // namespace ql