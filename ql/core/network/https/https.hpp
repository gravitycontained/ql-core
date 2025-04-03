#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/async/promise.hpp>

namespace ql
{
	namespace http
	{
		// Helper function to handle the data from the GET request
		QL_SOURCE ql::size write_callback(void* contents, ql::size size, ql::size nmemb, void* user_data);

		// Function to perform an HTTP GET request using libcurl
		QL_SOURCE ql::promise<std::string> GET(const std::string& url);

		// Function to perform an HTTP POST request using libcurl
		QL_SOURCE ql::promise<std::string> POST(const std::string& url, const std::string& data);
	}
}	 // namespace ql