#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/async/worker-queue.hpp>
#include <ql/core/async/promise.hpp>

#include <curl/curl.h>

namespace ql
{
	class curl
	{
	 protected:
		ql::worker_queue<std::function<void()>> worker_queue;

		QL_SOURCE static ql::size write_callback(void* contents, ql::size size, ql::size nmemb, void* userp);

	 public:
		std::optional<std::string> get(std::string url);										 // Synchronous method
		ql::promise<std::optional<std::string>> get_async(std::string url);	 // Asynchronous method
		std::shared_ptr<ql::promise<std::optional<std::string>>> get_async_ptr(std::string url);	 // Asynchronous method
	};

	namespace detail
	{
		QL_SOURCE extern ql::curl curl;
	}
}	 // namespace ql
