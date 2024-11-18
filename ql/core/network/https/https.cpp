#include <ql/core/network/https/https.hpp>
#include <ql/core/network/curl/curl.hpp>

#include <ql/core/system/print/print.hpp>

namespace ql
{
	std::optional<std::string> https_get(std::string url)
	{
		return ql::curl.get(url);
	}
	std::future<std::optional<std::string>> https_get_async(std::string url)
	{
		return ql::curl.get_async(url);
	}
}