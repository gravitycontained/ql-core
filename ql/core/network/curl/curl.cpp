#include <ql/core/network/curl/curl.hpp>

#include <ql/core/system/print/print.hpp>

namespace ql
{
	ql::size ql::curl::write_callback(void* contents, ql::size size, ql::size nmemb, void* output)
	{
		ql::size total_size = size * nmemb;
		std::string* content = static_cast<std::string*>(output);
		content->append(static_cast<char*>(contents), total_size);
		return total_size;
	}

	// Synchronous get method
	std::optional<std::string> ql::curl::get(std::string url)
	{
		std::string response;

		CURL* curl = curl_easy_init();
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			CURLcode res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);

			if (res != CURLE_OK)
			{
				ql::println("ql::curl_get failed: ", curl_easy_strerror(res));
				return std::nullopt;
			}

			return response;
		}

		return std::nullopt;
	}

	// Asynchronous get method
	ql::promise<std::optional<std::string>> ql::curl::get_async(std::string url)
	{
		ql::promise<std::optional<std::string>> result_promise;

		// Add the task to the worker queue for asynchronous execution
		this->worker_queue.add_task(
				[url, &result_promise]()
				{
					CURL* curl = curl_easy_init();
					if (curl)
					{
						std::string response;
						curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
						curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
						curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

						CURLcode res = curl_easy_perform(curl);
						curl_easy_cleanup(curl);

						if (res != CURLE_OK)
						{
							ql::println("ql::curl_get_async failed: ", curl_easy_strerror(res));
							result_promise.set_value(std::nullopt);
						}
						else
						{
							result_promise.set_value(response);
						}
					}
					else
					{
						result_promise.set_value(std::nullopt);
					}
				}
		);

		return result_promise;
	}

	// Asynchronous get method
	std::shared_ptr<ql::promise<std::optional<std::string>>> ql::curl::get_async_ptr(std::string url)
	{
		auto result_promise = std::make_shared<ql::promise<std::optional<std::string>>>();

		// Add the task to the worker queue for asynchronous execution
		this->worker_queue.add_task(
				[url, result_promise]()
				{
					CURL* curl = curl_easy_init();
					if (curl)
					{
						std::string response;
						curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
						curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
						curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

						CURLcode res = curl_easy_perform(curl);
						curl_easy_cleanup(curl);

						if (res != CURLE_OK)
						{
							ql::println("ql::curl_get_async failed: ", curl_easy_strerror(res));
							result_promise->set_value(std::nullopt);
						}
						else
						{
							result_promise->set_value(response);
						}
					}
					else
					{
						result_promise->set_value(std::nullopt);
					}
				}
		);

		return result_promise;
	}

	ql::curl ql::detail::curl;
}	 // namespace ql
