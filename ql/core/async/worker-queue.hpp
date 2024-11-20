#pragma once

#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

namespace ql
{
	template <typename Task>
	class worker_queue
	{
	 protected:
		std::condition_variable cv;
		std::queue<Task> tasks;
		std::atomic<bool> running;
		std::thread worker_thread;

		void process_tasks()
		{
			while (this->running)
			{
				Task task;
				{
					std::unique_lock<std::mutex> lock(this->mutex);
					this->cv.wait(lock, [&]() { return !this->tasks.empty() || !this->running; });

					if (!this->running && this->tasks.empty())
						return;

					task = std::move(this->tasks.front());
					this->tasks.pop();
				}

				if (task)
					task();
			}
		}

	 public:
		std::mutex mutex;

		worker_queue() : running(true), worker_thread(&worker_queue::process_tasks, this)
		{
		}

		~worker_queue()
		{
			{
				std::lock_guard<std::mutex> lock(this->mutex);
				this->running = false;
				this->cv.notify_all();
			}
			if (this->worker_thread.joinable())
			{
				this->worker_thread.join();
			}
		}

		void add_task(Task task)
		{
			{
				std::lock_guard<std::mutex> lock(this->mutex);
				this->tasks.push(std::move(task));
			}
			this->cv.notify_one();
		}
	};

}