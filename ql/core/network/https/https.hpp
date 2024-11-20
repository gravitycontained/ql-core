#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/async/promise.hpp>

#include <optional>
#include <string>
#include <future>

namespace ql
{
	QL_SOURCE std::optional<std::string> https_get(std::string url);
	QL_SOURCE ql::promise<std::optional<std::string>> https_get_async(const std::string& url);
	QL_SOURCE std::shared_ptr<ql::promise<std::optional<std::string>>> https_get_async_ptr(const std::string& url);
}