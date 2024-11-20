#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/async/worker-queue.hpp>

#include <curl/curl.h>

namespace ql
{
	class curl
	{
	 protected:
		ql::worker_queue<std::function<void()>> worker_queue;

		QL_SOURCE static ql::size write_callback(void* contents, ql::size size, ql::size nmemb, void* userp);
		QL_SOURCE void make_request(const std::string& url, std::function<void(std::optional<std::string>)> callback);

	 public:
		void add_request(const std::string& url, std::function<void(std::optional<std::string>)> callback)
		{
			this->make_request(url, callback);
		}

		std::optional<std::string> get(std::string url);
	};

	namespace detail
	{
		QL_SOURCE extern ql::curl curl;
	}

}