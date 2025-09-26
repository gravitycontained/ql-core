#pragma once

#include <ql/core/time/queue/queue-manager.hpp>
#include <ql/core/system/print/print.hpp>

namespace ql
{
	// sets the default duration for tasks that do not have one explicitly set
	void ql::queue_manager::set_duration(ql::f64 duration)
	{
		this->duration = duration;
	}

	// adds a new task to the execution queue
	ql::queue_manager& ql::queue_manager::add_task(std::function<void()>&& task)
	{
		this->tasks.emplace_back(std::move(task));
		return *this;
	}

	// sets how many times the most recently added task should repeat
	// ql::size_max indicates infinite repetitions
	ql::queue_manager& ql::queue_manager::with_repeat(ql::size repeat)
	{
		auto& task = this->tasks.back();
		task.repeat = repeat;
		return *this;
	}

	// sets a phase offset (0.0 to 1.0) for the task's execution within its duration
	ql::queue_manager& ql::queue_manager::with_phase(ql::f64 phase_offset)
	{
		auto& task = this->tasks.back();
		task.phase_offset = phase_offset;
		return *this;
	}

	// convenience method to set the phase offset to the very end of the duration (1.0)
	ql::queue_manager& ql::queue_manager::with_phase_end()
	{
		auto& task = this->tasks.back();
		task.phase_offset = 1.0;
		return *this;
	}

	// sets a specific duration for the most recently added task, overriding the default
	ql::queue_manager& ql::queue_manager::with_duration(ql::f64 duration)
	{
		auto& task = this->tasks.back();
		task.duration = duration;
		return *this;
	}

	void ql::queue_manager::set_time_relative()
	{
		this->relative = true;
	}

	void ql::queue_manager::set_time_global()
	{
		this->relative = false;
	}

	void ql::queue_manager::reset_time()
	{
		this->timer.reset();
	}

	ql::time ql::queue_manager::get_time() const
	{
		if (this->relative)
			return this->timer.elapsed();

		return ql::time::clock_time();
	}
	// checks all tasks, determines which ones are due, and executes them
	void ql::queue_manager::update()
	{
		ql::vector<std::pair<ql::size, ql::f64>> due_tasks;

		// identify all tasks that are initially due to be executed
		for (ql::size i = 0u; i < this->tasks.size(); ++i)
		{
			auto& task = this->tasks[i];
			if (task.repeat == 0)
				continue;

			const auto elapsed_nsecs = ql::i64_cast(this->get_time().nsecs());
			const auto task_duration = (task.duration == ql::f64_epsilon) ? this->duration : task.duration;
			const auto delta = ql::i64_cast(task_duration * ql::time::nsecs_in_sec);

			if (delta == 0)
				continue;

			const auto offset = ql::i64_cast(task.phase_offset * delta);
			const auto [divisions, _] = ql::div_mod(elapsed_nsecs - offset, delta);

			if (divisions < 0)
				continue;

			const ql::isize last_known_interval = ql::signed_cast((task.last_interval == ql::size_max) ? 0 : task.last_interval);

			if (divisions > last_known_interval)
				due_tasks.push_back({ i, task.phase_offset });
		}

		if (due_tasks.empty())
			return;

		// sort tasks to preserve phase ordering, ensuring higher phases run first
		ql::sort(due_tasks, [](const auto& a, const auto& b)
		{
			if (a.second == b.second)
				return a.first > b.first;

			return a.second > b.second;
		});

		// this loop ensures that if tasks have missed multiple intervals, they are executed
		// one interval at a time in the correct phase order (e.g., B1, A1, B2, A2...).
		// it continues as long as any task made progress in a pass.
		bool all_caught_up = false;
		while (!all_caught_up)
		{
			all_caught_up = true;

			for (const auto& [index, _] : due_tasks)
			{
				auto& task = this->tasks[index];

				// defines and executes a single step for a task if it's pending
				const auto process_one_interval = [&](ql::queue_manager::task_type& t)
				{
					// the timer is read every time to ensure the most up-to-date state,
					// which is critical if prior tasks in the queue were time-consuming.
					const auto elapsed_nsecs = ql::i64_cast(this->get_time().nsecs());
					const auto duration = (t.duration == ql::f64_epsilon) ? this->duration : t.duration;
					const auto delta = ql::i64_cast(duration * ql::time::nsecs_in_sec);
					if (delta == 0) return;

					const auto offset = ql::i64_cast(t.phase_offset * delta);
					const auto [target_intervals, __] = ql::div_mod(elapsed_nsecs - offset, delta);

					const ql::isize last_known_interval = ql::signed_cast((task.last_interval == ql::size_max) ? 0 : task.last_interval);
					const ql::isize pending_intervals = target_intervals - last_known_interval;

					if (pending_intervals > 0 && t.repeat > 0)
					{
						t.task();

						// update the task's interval counter. the jump on the first run is intentional
						// to sync the task, preventing it from running again in the same update cycle
						// unless the timer advances enough to increment the target interval count.
						if (t.last_interval == ql::size_max)
							t.last_interval = ql::size_cast(target_intervals);

						++t.last_interval;

						if (t.repeat != ql::size_max)
							--t.repeat;

						// if the task was more than one step behind, we are not caught up.
						// a full re-scan is needed to process the next tick for all tasks in order.
						if (pending_intervals > 1)
							all_caught_up = false;
					}
				};

				process_one_interval(task);
			}
		}

		if (this->cleanup_timer.has_elapsed_reset(this->cleanup_interval))
			this->cleanup();
	}

	void ql::queue_manager::cleanup()
	{
		ql::sort(this->tasks, [](auto& a, auto& b)
			{
				return a.repeat > b.repeat;
			});

		ql::size active_count = 0u;
		for (auto it = this->tasks.crbegin(); it != this->tasks.crend(); ++it)
		{
			if (!it->repeat)
				++active_count;

			else
				break;
		}

		this->tasks.resize(this->tasks.size() - active_count);
	}
}