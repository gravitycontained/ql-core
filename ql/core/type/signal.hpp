#pragma once

#include <ql/core/type/declval.hpp>

namespace ql
{
	template <typename T>
	struct signal;

	namespace detail
	{

		template <typename T>
		constexpr auto signal_signature(ql::signal<T>)
		{
			return std::true_type{};
		}

		template <typename T>
		constexpr auto signal_signature(T)
		{
			return std::false_type{};
		}
	}
	template <typename T>
	constexpr bool is_signal()
	{
		return decltype(ql::detail::signal_signature(ql::declval<T>())){};
	}

	template <typename T>
	constexpr bool is_signal(T signal)
	{
		return ql::is_signal<T>();
	}
}