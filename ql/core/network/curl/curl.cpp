#include <ql/core/network/curl/curl.hpp>

#include <ql/core/system/print/print.hpp>

namespace ql
{

	namespace detail
	{
		ql::size write_callback(void* contents, ql::size size, ql::size nmemb, std::string* output)
		{
			auto totalSize = size * nmemb;
			output->append(static_cast<char*>(contents), totalSize);
			return totalSize;
		}
	}

	ql::curl_t curl;

	std::optional<std::string> ql::curl_t::get(std::string url)
	{
		std::string response;

		if (this->curl)
		{
			curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, ql::detail::write_callback);
			curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &response);


			auto res = curl_easy_perform(this->curl);

			if (res != CURLE_OK)
			{
				ql::println("ql::curl_get failed: ", curl_easy_strerror(res));
				return {};
			}

			return response;
		}
		return {};
	}

  std::future<std::optional<std::string>> ql::curl_t::get_async(std::string url)
	{
		std::promise<std::optional<std::string>> promise;

		// Spawn a new thread to handle the network operation
		std::thread(
				[this, url, promise = std::move(promise)]() mutable
				{
					std::string response;

					if (this->curl)
					{
						curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
						curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, ql::detail::write_callback);
						curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &response);

						auto res = curl_easy_perform(curl);

						if (res != CURLE_OK)
						{
							ql::println("ql::curl_get failed: ", curl_easy_strerror(res));
							promise.set_value({});
						}
						else
						{
							promise.set_value(response);
						}
					}
					else
					{
						promise.set_value({});
					}
				}
		).detach();

		return promise.get_future();
	}
}