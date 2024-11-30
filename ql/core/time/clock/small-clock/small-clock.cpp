#include <ql/core/time/clock/small-clock/small-clock.hpp>

namespace ql
{
	void ql::small_clock::reset()
	{
		this->m_begin = ql::time::clock_time();
	}

	ql::time ql::small_clock::elapsed() const
	{
		auto time = ql::time::clock_time();
		return time - this->m_begin;
	}

	std::string ql::small_clock::elapsed_str() const
	{
		return this->elapsed().string();
	}

	ql::f64 ql::small_clock::elapsed_f() const
	{
		return this->elapsed().secs_f();
	}

	ql::time ql::small_clock::elapsed_reset()
	{
		auto result = this->elapsed();
		this->reset();
		return result;
	}

	std::string ql::small_clock::elapsed_str_reset()
	{
		auto result = this->elapsed_str();
		this->reset();
		return result;
	}

	ql::f64 ql::small_clock::elapsed_f_reset()
	{
		auto result = this->elapsed_f();
		this->reset();
		return result;
	}

	void ql::small_clock::add(ql::f64 seconds)
	{
		this->m_begin += ql::u64_cast(seconds * ql::time::nsecs_in_sec);
	}

	void ql::small_clock::add(ql::time time)
	{
		this->m_begin += time;
	}

	void ql::small_clock::subtract(ql::f64 seconds)
	{
		this->m_begin -= ql::u64_cast(seconds * ql::time::nsecs_in_sec);
	}

	void ql::small_clock::subtract(ql::time time)
	{
		this->m_begin -= time;
	}

	bool ql::small_clock::has_elapsed(ql::f64 seconds) const
	{
		return this->elapsed_f() > seconds;
	}

	bool ql::small_clock::has_elapsed(ql::time duration) const
	{
		return this->elapsed() > duration;
	}

	bool ql::small_clock::has_elapsed_reset(ql::f64 seconds)
	{
		auto result = this->has_elapsed(seconds);
		if (result)
		{
			this->reset();
		}
		return result;
	}

	bool ql::small_clock::has_elapsed_reset(ql::time duration)
	{
		auto result = this->has_elapsed(duration);
		if (result)
		{
			this->reset();
		}
		return result;
	}

}	 // namespace ql