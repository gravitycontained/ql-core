#pragma once

#include <ql/string/string.hpp>
#include <string>
#include <exception>

namespace ql
{
	struct exception : std::exception
	{
		std::string string;

		template <typename... Args>
		exception(Args&&... args)
		{
			this->string = ql::to_string(std::forward<Args>(args)...);
		}

		const char* what() const override
		{
			return this->string.c_str();
		}
	};
}	 // namespace qpl