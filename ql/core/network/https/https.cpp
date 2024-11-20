#include <ql/core/network/https/https.hpp>
#include <ql/core/network/curl/curl.hpp>

#include <ql/core/system/print/print.hpp>

namespace ql
{
	std::optional<std::string> https_get(std::string url)
	{
		return ql::detail::curl.get(url);
	}

	ql::promise<std::optional<std::string>> https_get_async(const std::string& url)
	{
		return ql::detail::curl.get_async(url);
	}

	std::shared_ptr<ql::promise<std::optional<std::string>>> https_get_async_ptr(const std::string& url)
	{
		return ql::detail::curl.get_async_ptr(url);
	}
}