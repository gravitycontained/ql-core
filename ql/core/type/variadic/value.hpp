#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/variadic/type.hpp>
#include <ql/core/type/variadic/size.hpp>

#include <ql/core/type/tuple/auto-tie.hpp>
#include <ql/core/type/tuple/value.hpp>

#include <ql/core/type/expression.hpp>

namespace ql
{

	template <ql::size N, typename... Args>
	requires (ql::lvalue<ql::variadic_type<N, Args...>>)
	constexpr auto& variadic_value(Args&&... args)
	{
		return ql::tuple_value<N>(ql::auto_tie(std::forward<Args>(args)...));
	}

	template <ql::size N, typename... Args>
	requires (ql::rvalue<ql::variadic_type<N, Args...>>)
	constexpr auto&& variadic_value(Args&&... args)
	{
		return ql::tuple_value<N>(ql::auto_tie(std::forward<Args>(args)...));
	}

	template <ql::size N, typename... Args>
	requires (ql::no_reference<ql::variadic_type<N, Args...>>)
	constexpr auto variadic_value(Args... args)
	{
		return ql::tuple_value<N>(ql::auto_tie(std::forward<Args>(args)...));
	}

	template <typename... Args>
	requires (ql::lvalue<ql::variadic_type<0, Args...>>)
	constexpr auto& variadic_value_front(Args&&... args)
	{
		return ql::variadic_value<0u>(std::forward<Args>(args)...);
	}

	template <typename... Args>
	requires (ql::rvalue<ql::variadic_type<0, Args...>>)
	constexpr auto&& variadic_value_front(Args&&... args)
	{
		return ql::variadic_value<0u>(std::forward(args...));
	}

	template <typename... Args>
	requires (ql::no_reference<ql::variadic_type<0, Args...>>)
	constexpr auto variadic_value_front(Args... args)
	{
		return ql::variadic_value<0u>(std::forward<Args>(args)...);
	}

	template <typename... Args>
	requires (ql::lvalue<ql::variadic_type<ql::variadic_size<Args...>() - 1, Args...>>)
	constexpr auto& variadic_value_back(Args&&... args)
	{
		return ql::variadic_value<ql::variadic_size<Args...>() - 1>(std::forward<Args>(args)...);
	}

	template <typename... Args>
	requires (ql::rvalue<ql::variadic_type<ql::variadic_size<Args...>() - 1, Args...>>)
	constexpr auto&& variadic_value_back(Args&&... args)
	{
		return ql::variadic_value<ql::variadic_size<Args...>() - 1>(std::forward(args...));
	}

	template <typename... Args>
	requires (ql::no_reference<ql::variadic_type<ql::variadic_size<Args...>() - 1, Args...>>)
	constexpr auto variadic_value_back(Args... args)
	{
		return ql::variadic_value<ql::variadic_size<Args...>() - 1>(std::forward<Args>(args)...);
	}
}	 // namespace ql