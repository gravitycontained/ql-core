#include <ql/core/network/https/https.hpp>
#include <ql/core/network/curl/curl.hpp>

#include <ql/core/system/print/print.hpp>

namespace ql
{
	std::optional<std::string> https_get(std::string url)
	{
		return ql::detail::curl.get(url);
	}

	void https_get_add_request(const std::string& url, std::function<void(std::optional<std::string>)> callback)
	{
		ql::detail::curl.add_request(url, callback);
	}
}