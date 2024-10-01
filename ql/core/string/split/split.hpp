#pragma once

#include <ql/core/definition/definition.hpp>

#include <vector>

namespace ql
{
	QL_SOURCE std::vector<std::string> string_split(const std::string_view& string, char by_what);
	QL_SOURCE std::vector<std::string> string_split_allow_empty(const std::string_view& string, char by_what);
	QL_SOURCE std::vector<std::string> string_split_every(const std::string& string, ql::size n);
}	 // namespace ql