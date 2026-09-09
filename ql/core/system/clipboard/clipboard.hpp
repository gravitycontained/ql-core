#pragma once

#include <ql/core/definition/definition.hpp>
#if defined QL_GRAPHIC

#include <SFML/Graphics.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_string_type<T>())
	void copy_to_clipboard(T&& string)
	{
		sf::Clipboard::setString(string);
	}

	template <typename T = std::wstring>
	requires (ql::is_string_type<T>())
	T copy_from_clipboard()
	{
		auto str = sf::Clipboard::getString();
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