#include <ql/core/time/timed-task/timed-task.hpp>

namespace ql
{

	ql::clock ql::detail::signal_clock;
	ql::u64 ql::detail::signal_count;


	void ql::timed_task::update()
	{
		auto done = this->is_done();
		this->just_finish = !this->done_before && done;
		if (this->just_finish)
		{
			this->function();
		}
		this->done_before = done;
	}

	bool ql::timed_task::is_done() const
	{
		return this->clock.elapsed() > this->wait_duration;
	}

	bool ql::timed_task::is_running() const
	{
		return !this->is_done();
	}

	bool ql::timed_task::just_finished() const
	{
		return this->just_finish;
	}

	void ql::timed_task::set_wait_duration(ql::time time)
	{
		this->wait_duration = time;
	}

	void ql::timed_task::set_wait_duration(ql::f64 seconds)
	{
		this->wait_duration = ql::secs(seconds);
	}

	ql::f64 ql::timed_task::get_wait_progress() const
	{
		auto p = this->clock.elapsed_f();
		return p / this->wait_duration.secs_f();
	}

	timed_task_manager ql::detail::tasks;

	void ql::timed_task_manager::clear()
	{
		this->tasks.clear();
	}

	void ql::timed_task_manager::cleanup()
	{
		std::vector<timed_task> temp;
		temp.reserve(this->tasks.size());
		for (auto& i : this->tasks)
		{
			if (i.is_done())
			{
				this->finished_tasks.insert(i.name);
			}
			else
			{
				temp.emplace_back(i);
			}
		}
		this->tasks = temp;
	}

	bool ql::timed_task_manager::is_task_finished(const std::string& name)
	{
		return this->finished_tasks.find(name) != this->finished_tasks.cend();
	}

	bool ql::timed_task_manager::is_task_running(const std::string& name)
	{
		for (auto& i : this->tasks)
		{
			if (i.name == name)
			{
				return i.is_running();
			}
		}
		return false;
	}

	void ql::timed_task_manager::add_timed_task(ql::time time, std::function<void(void)> function, const std::string& name)
	{
		this->tasks.push_back(ql::timed_task(time, function, name));
	}

	void ql::timed_task_manager::add_timed_task(ql::f64 time, std::function<void(void)> function, const std::string& name)
	{
		this->tasks.push_back(ql::timed_task(time, function, name));
	}

	void ql::timed_task_manager::update()
	{
		bool any_done = false;
		for (auto& i : this->tasks)
		{
			i.update();
			if (i.is_done())
			{
				any_done = true;
			}
		}
		this->finished_tasks.clear();
		if (any_done)
		{
			this->cleanup();
		}
	}

	void start_timed_task(ql::time time, std::function<void(void)> function)
	{
		ql::detail::tasks.add_timed_task(time, function);
	}

	void start_timed_task(ql::time time, const std::string& name, std::function<void(void)> function)
	{
		ql::detail::tasks.add_timed_task(time, function, name);
	}

	void start_timed_task(ql::f64 time, std::function<void(void)> function)
	{
		ql::detail::tasks.add_timed_task(time, function);
	}

	void start_timed_task(ql::f64 time, const std::string& name, std::function<void(void)> function)
	{
		ql::detail::tasks.add_timed_task(time, function, name);
	}

	bool timed_task_finished(const std::string& name)
	{
		return ql::detail::tasks.is_task_finished(name);
	}

	bool timed_task_running(const std::string& name)
	{
		return ql::detail::tasks.is_task_running(name);
	}

	void clear_timed_tasks()
	{
		ql::detail::tasks.clear();
	}

	void update_tasks()
	{
		ql::detail::tasks.update();
	}

	void reset_time_signal()
	{
		ql::detail::signal_clock.reset();
	}

	bool get_time_signal(double seconds)
	{
		return (ql::detail::signal_clock.has_elapsed_reset(seconds));
	}

	bool get_time_signal(ql::time time)
	{
		return (ql::detail::signal_clock.has_elapsed_reset(time));
	}

	void reset_count_signal()
	{
		ql::detail::signal_count = ql::u64{};
	}

	bool get_count_signal(ql::u64 when)
	{
		++ql::detail::signal_count;
		if (ql::detail::signal_count >= when)
		{
			ql::detail::signal_count = ql::u64{};
			return true;
		}
		return false;
	}

}	 // namespace ql