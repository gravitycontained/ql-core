#pragma once

#include <ql/core/string/string.hpp>
#include <string>
#include <exception>

namespace ql
{
	struct exception : std::exception
	{
		std::string string;

		exception(const ql::exception& other) = default;

		template <typename... Args>
		exception(Args&&... args)
		{
			this->string = ql::to_string(args...);
		}

		const char* what() const override
		{
			return this->string.c_str();
		}

		std::string to_string() const
		{
			return this->string;
		}
	};
}	 // namespace qpl