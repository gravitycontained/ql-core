#include <ql/core/network/https/https.hpp>
#include <ql/core/system/system.hpp>

#include <curl/curl.h>


namespace ql
{
	ql::size write_callback(void* contents, ql::size size, ql::size nmemb, void* user_data)
	{
		ql::size total_size = size * nmemb;
		static_cast<std::string*>(user_data)->append(static_cast<char*>(contents), total_size);
		return total_size;
	}

	ql::promise<std::string> http_get(const std::string& url)
	{
		return ql::make_promise(
				[url]()
				{
					try
					{
						CURL* curl = curl_easy_init();
						if (!curl)
							throw std::runtime_error("Failed to initialize CURL");

						std::string response_data;
						curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
						curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
						curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
						curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);	 // Follow redirects

						CURLcode res = curl_easy_perform(curl);
						if (res != CURLE_OK)
						{
							curl_easy_cleanup(curl);
							throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
						}

						curl_easy_cleanup(curl);
						return response_data;
					}
					catch (const std::exception& e)
					{
						ql::println(
							ql::color::bright_yellow, "core", ql::color::bright_gray, " :: ", ql::color::bright_red, ql::to_string("http_get error: ", e.what())
						);
						return std::string();
					}
				}
		);
	}
}	 // namespace ql