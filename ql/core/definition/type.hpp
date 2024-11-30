#pragma once

#include <type_traits>

namespace ql
{
	template <typename T, ql::size N>
	struct vectorN;

	struct empty_type
	{
	};

	struct true_type
	{
	};

	struct false_type
	{
	};

	struct default_type
	{
	};

	using error_type = std::enable_if<false, void>;
	using default_error = ql::error_type;

	template <bool condition>
	using if_true = std::conditional_t<condition, ql::true_type, ql::false_type>;

	template <typename T>
	T& singleton()
	{
		static T value;
		return value;
	}
}	 // namespace ql