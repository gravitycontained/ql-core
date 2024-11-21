#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/async/async.hpp>
#include <curl/curl.h>

namespace ql
{
	// Helper function to handle the data from the GET request
	QL_SOURCE size_t write_callback(void* contents, size_t size, size_t nmemb, void* user_data);

	// Function to perform an HTTP GET request using libcurl
	QL_SOURCE ql::promise<std::string> http_get(const std::string& url);
}	 // namespace ql