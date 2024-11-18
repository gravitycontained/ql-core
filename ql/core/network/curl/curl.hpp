#pragma once

#include <string>
#include <ql/core/definition/definition.hpp>

#include <curl/curl.h>

#include <optional>
#include <future>

namespace ql
{
	namespace detail
	{
		QL_SOURCE ql::size write_callback(void* contents, size_t size, size_t nmemb, std::string* output);
	}

	struct curl_t
	{
		CURL* curl = nullptr;

		curl_t()
		{
			this->curl = curl_easy_init();
		}
		~curl_t()
		{
			curl_easy_cleanup(this->curl);
		}

		QL_SOURCE std::optional<std::string> get(std::string url);
		QL_SOURCE std::future<std::optional<std::string>> get_async(std::string url);
	};

	QL_SOURCE extern ql::curl_t curl;
	
}