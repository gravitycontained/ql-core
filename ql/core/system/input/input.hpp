#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/transform/cast/cast.hpp>

namespace ql
{
	template <typename T = std::string>
	T get_input()
	{
		std::string value;
		std::getline(std::cin, value);
		return ql::type_cast<T>(value);
	}

	QL_SOURCE std::string get_hidden_input(const std::string_view& replace = "*");
}