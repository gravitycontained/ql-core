#pragma once

namespace ql
{
	template <class T, class... Ignored>
	struct identity
	{
		using type = typename T;
	};

	template <class... Args>
	struct empty_indirection
	{
		using type = typename identity<Args...>::type;
	};
}	 // namespace ql