#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/functional/functional.hpp>

#include <future>

namespace ql
{
	template <typename T>
	class promise
	{
	 private:
		using TaskType = std::function<T()>;
		using StorageType = std::conditional_t<std::is_void_v<T>, ql::empty_type, T>;

		struct shared_state
		{
			TaskType task;
			std::mutex mutex;
			std::condition_variable cv;
			std::atomic<bool> is_ready{false};
			std::optional<StorageType> result;
			std::thread worker;

			explicit shared_state(TaskType&& task) : task(std::move(task))
			{
			}
		};

		std::shared_ptr<shared_state> state;

	 public:
		explicit promise(TaskType&& task) : state(std::make_shared<shared_state>(std::move(task)))
		{
			state->worker = std::thread(
				[state = state]()
				{
					if constexpr (std::is_void_v<T>)
					{
						state->task();
						std::lock_guard<std::mutex> lock(state->mutex);
						state->result.emplace(ql::empty_type{});
					}
					else
					{
						auto result = state->task();
						std::lock_guard<std::mutex> lock(state->mutex);
						state->result.emplace(std::move(result));
					}
					state->is_ready = true;
					state->cv.notify_all();
				}
			);
			state->worker.detach();
		}

		template <typename Func>
		auto then(Func&& continuation)
		{
			using NextType = std::invoke_result_t<Func, StorageType>;
			using CleanNextType = std::conditional_t<std::is_void_v<NextType>, ql::empty_type, NextType>;

			auto current_state = state;
			return promise<CleanNextType>(
				[continuation = std::forward<Func>(continuation), current_state]() mutable
				{
					wait(current_state);

					if constexpr (std::is_void_v<NextType>)
					{
						continuation(std::move(*current_state->result));
						return ql::empty_type{};
					}
					else
					{
						return continuation(std::move(*current_state->result));
					}
				}
			);
		}

	 private:
		static void wait(const std::shared_ptr<shared_state>& state)
		{
			if (!state->is_ready)
			{
				std::unique_lock<std::mutex> lock(state->mutex);
				state->cv.wait(lock, [state]() { return state->is_ready.load(); });
			}
		}
	};

	template <typename Func>
	auto make_promise(Func&& task)
	{
		using ResultType = std::invoke_result_t<Func>;
		return promise<ResultType>(std::forward<Func>(task));
	}

}	 // namespace ql
