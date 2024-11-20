#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/functional/functional.hpp>

#include <future>
#include <functional>
#include <optional>
#include <mutex>
#include <thread>
#include <type_traits>

namespace ql
{
	template <typename T>
	class promise
	{
	 private:
		std::mutex mtx;
		std::condition_variable cv;
		std::optional<T> value;
		bool resolved = false;
		std::function<void(T)> callback;

	 public:
		void set_value(const T& val)
		{
			std::unique_lock lock(mtx);
			this->value = val;
			this->resolved = true;
			this->cv.notify_all();
			if (this->callback)
			{
				this->callback(*this->value);
			}
		}

		void wait()
		{
			std::unique_lock lock(this->mtx);
			this->cv.wait(lock, [this]() { return this->resolved; });
		}

		template <typename F>
		auto then(F&& func)
		{
			std::unique_lock lock(mtx);
			using NextPromiseType = promise<typename ql::return_type<F>>;

			NextPromiseType next_promise;

			auto execute = [&next_promise, func = std::forward<F>(func)](auto&& val)
			{
				if constexpr (ql::parameter_size<F>() > 0)
				{
					if constexpr (ql::return_size<F>() > 0)
						next_promise.set_value(func(std::forward<decltype(val)>(val)));

					else
					{
						func(std::forward<decltype(val)>(val));
						next_promise.set_value(ql::empty_type{});
					}
				}
				else
				{
					if constexpr (ql::return_size<F>() > 1)
						next_promise.set_value(func());

					else
					{
						func();
						next_promise.set_value(ql::empty_type{});
					}
				}
			};

			if (resolved)
			{
				execute(*this->value);
			}
			else
			{
				callback = [execute = std::move(execute)](T val) mutable { execute(std::move(val)); };
			}

			return next_promise;
		}
	};

	template <typename F>
	requires (ql::is_callable<F>())
	auto create_promise(F&& function)
	{
		auto result = std::make_shared<promise<typename ql::return_type<F>>>();

		std::thread(
				[result, func = std::forward<F>(function)]() mutable
				{
					if constexpr (ql::return_size<F>() > 0)
						result->set_value(func());

					else
					{
						func();
						result->set_value(ql::empty_type{});
					}
				}
		).detach();

		return result;
	}

}	 // namespace ql
