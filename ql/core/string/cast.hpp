#pragma once

#include <ql/core/definition/definition.hpp>
namespace ql
{
	QL_SOURCE std::string wchar_to_utf8(wchar_t wc);
	QL_SOURCE std::string wstring_to_utf8(const std::wstring& string);
}	 // namespace ql