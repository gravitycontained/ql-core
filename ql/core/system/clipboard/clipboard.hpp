#pragma once

#include <ql/core/definition/definition.hpp>
#ifdef QL_INTERN_SFML_USE

#include <SFML/Graphics.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{
	namespace detail
	{
		QL_SOURCE extern sf::Clipboard clipboard;
	}

	template <typename T>
	requires (ql::is_string_type<T>())
	void copy_to_clipboard(T&& string)
	{
		detail::clipboard.setString(string);
	}

	template <typename T = std::wstring>
	requires (ql::is_string_type<T>())
	T copy_from_clipboard()
	{
		auto str = detail::clipboard.getString();
		if constexpr (ql::is_standard_string_type<T>())
		{
			return str.toAnsiString();
		}
		else
		{
			return str;
		}
	}
}	 // namespace ql

#endif