#pragma once

#include <string>

namespace ql
{
	template <typename T>
	concept has_to_string_c = requires(const T t) {
		{ t.to_string() } -> std::convertible_to<std::string>;
	};

	template <typename T>
	constexpr auto has_to_string()
	{
		return ql::has_to_string_c<T>;
	}
}	 // namespace ql