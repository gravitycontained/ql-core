#pragma once

#include <string>

namespace ql
{

	template <typename T>
	std::string type_name()
	{
		return std::string(typeid(T).name());
	}

	template <typename T>
	std::string type_name(T value)
	{
		return ql::type_name(value);
	}
}