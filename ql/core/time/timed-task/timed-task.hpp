#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/time/clock/clock.hpp>

#include <functional>

namespace ql
{
	namespace detail
	{
		QL_SOURCE extern ql::clock signal_clock;
		QL_SOURCE extern ql::u64 signal_count;
	}

	struct timed_task
	{
		ql::small_clock clock;
		ql::time wait_duration;
		std::function<void(void)> function;
		std::string name = "";
		bool done_before = false;
		bool just_finish = false;

		timed_task()
		{
		}

		timed_task(ql::time wait_duration, std::function<void(void)> function, const std::string& name = "")
		{
			this->wait_duration = wait_duration;
			this->function = function;
			this->name = name;
		}

		timed_task(ql::f64 wait_duration, std::function<void(void)> function, const std::string& name = "")
		{
			this->wait_duration = ql::secs(wait_duration);
			this->function = function;
			this->name = name;
		}

		QL_SOURCE void update();
		QL_SOURCE bool is_done() const;
		QL_SOURCE bool is_running() const;
		QL_SOURCE bool just_finished() const;
		QL_SOURCE void set_wait_duration(ql::time time);
		QL_SOURCE void set_wait_duration(ql::f64 seconds);
		QL_SOURCE ql::f64 get_wait_progress() const;
	};

	struct timed_task_manager
	{
		std::vector<timed_task> tasks;
		std::set<std::string> finished_tasks;

		QL_SOURCE void clear();
		QL_SOURCE void cleanup();
		QL_SOURCE bool is_task_finished(const std::string& name);
		QL_SOURCE bool is_task_running(const std::string& name);
		QL_SOURCE void add_timed_task(ql::time time, std::function<void(void)> function, const std::string& name = "");
		QL_SOURCE void add_timed_task(ql::f64 time, std::function<void(void)> function, const std::string& name = "");
		QL_SOURCE void update();
	};

	namespace detail
	{
		QL_SOURCE extern ql::timed_task_manager tasks;
	}

	QL_SOURCE void start_timed_task(ql::time time, const std::string& name, std::function<void(void)> function);
	QL_SOURCE void start_timed_task(ql::time time, std::function<void(void)> function);
	QL_SOURCE void start_timed_task(ql::f64 time, const std::string& name, std::function<void(void)> function);
	QL_SOURCE void start_timed_task(ql::f64 time, std::function<void(void)> function);
	QL_SOURCE bool timed_task_finished(const std::string& name = "");
	QL_SOURCE bool timed_task_running(const std::string& name = "");
	QL_SOURCE void clear_timed_tasks();
	QL_SOURCE void update_tasks();

	QL_SOURCE void reset_time_signal();
	QL_SOURCE bool get_time_signal(double seconds);
	QL_SOURCE bool get_time_signal(ql::time time);

	QL_SOURCE void reset_count_signal();
	QL_SOURCE bool get_count_signal(ql::u64 when);
}	 // namespace ql