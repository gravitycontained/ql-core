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

	void ql::curl::make_request(const std::string& url, std::function<void(std::optional<std::string>)> callback)
	{
		this->worker_queue.add_task(
				[url, callback]()
				{
					CURL* curl = curl_easy_init();
					if (curl)
					{
						std::string response;
						curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
						curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
						curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

						CURLcode res = curl_easy_perform(curl);
						if (res != CURLE_OK)
						{
							callback(std::nullopt);
						}
						else
						{
							callback(response);
						}

						curl_easy_cleanup(curl);
					}
					else
					{
						callback(std::nullopt);
					}
				}
		);
	}

	std::optional<std::string> ql::curl::get(std::string url)
	{
		std::string response;

		CURL* curl = curl_easy_init();
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->write_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);


			auto res = curl_easy_perform(curl);

			curl_easy_cleanup(curl);

			if (res != CURLE_OK)
			{
				ql::println("ql::curl_get failed: ", curl_easy_strerror(res));
				return {};
			}

			return response;
		}
		return {};
	}

	ql::curl ql::detail::curl;
}