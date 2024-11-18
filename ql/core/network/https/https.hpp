#pragma once

#include <ql/core/definition/definition.hpp>

#include <optional>
#include <string>
#include <future>

namespace ql
{
	QL_SOURCE std::optional<std::string> https_get(std::string url);
	QL_SOURCE std::future<std::optional<std::string>> https_get_async(std::string url);
}