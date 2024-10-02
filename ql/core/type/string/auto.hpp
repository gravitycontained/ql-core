#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/string/type.hpp>
#include <ql/core/type/conditional.hpp>

namespace ql
{

	template <typename T>
	using auto_string_type = ql::conditional<
			ql::if_true<ql::is_wstring_type<T>()>,
			std::wstring,
			ql::if_true<ql::is_standard_string_type<T>()>,
			std::string,
			ql::default_type,
			std::u32string>;
}