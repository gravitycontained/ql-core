#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/string/type.hpp>
#include <ql/core/type/conditional.hpp>
#include <ql/core/type/recursive/recursive.hpp>
#include <ql/core/constexpr/chain.hpp>

namespace ql
{
	template <typename... Ts>
	constexpr bool recursive_any_u32string()
	{
		return ql::recursive_type_or_chain<std::tuple<Ts...>>([]<typename T>() { return ql::is_u32string_type<T>(); });
	}

	template <typename... Ts>
	constexpr bool recursive_any_wstring()
	{
		return ql::recursive_type_or_chain<std::tuple<Ts...>>([]<typename T>() { return ql::is_wstring_type<T>(); });
	}

	template <typename... Ts>
	constexpr bool recursive_any_standard_string()
	{
		return ql::recursive_type_or_chain<std::tuple<Ts...>>([]<typename T>() { return ql::is_standard_string_type<T>(); });
	}

	template <typename... Ts>
	using recursive_to_string_type = ql::conditional<
			ql::if_true<ql::recursive_any_u32string<Ts...>()>,
			std::u32string,
			ql::if_true<ql::recursive_any_wstring<Ts...>()>,
			std::wstring,
			ql::default_type,
			std::string>;
}	 // namespace ql
