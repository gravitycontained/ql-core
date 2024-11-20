#pragma once

#include <ql/core/definition/definition.hpp>

#include <optional>
#include <string>
#include <future>

namespace ql
{
	QL_SOURCE std::optional<std::string> https_get(std::string url);
	QL_SOURCE void https_get_add_request(const std::string& url, std::function<void(std::optional<std::string>)> callback);
}