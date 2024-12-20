#pragma once

#include <string>

namespace ql
{

	template <typename T>
	std::string type_name()
	{
		auto result = std::string(typeid(T).name());

		auto searches = std::vector<std::string>{"class ", "struct ", "__cdecl ", "__ptr64 ", "enum "};

		for (auto search : searches)
		{
			auto position = result.find(search);
			if (position != std::string::npos)
			{
				result.erase(position, search.size());
			}
		}

		return result;
	}

	template <typename T>
	std::string type_name(T value)
	{
		return ql::type_name(value);
	}
}	 // namespace ql