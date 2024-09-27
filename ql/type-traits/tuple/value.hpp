#pragma once

#include <ql/type-traits/tuple/size.hpp>
#include <ql/type-traits/tuple/type.hpp>
#include <ql/type-traits/expression.hpp>

namespace ql
{
	template <ql::size N, typename T>
	requires(ql::is_tuple<T>() && ql::lvalue<ql::tuple_type<N, T>>)
	constexpr auto& tuple_value(T&& tuple)
	{
		return std::get<N>(std::forward<T>(tuple));
	}

	template <ql::size N, typename T>
	requires(ql::is_tuple<T>() && ql::rvalue<ql::tuple_type<N, T>>)
	constexpr auto&& tuple_value(T&& tuple)
	{
		return std::get<N>(std::forward<T>(tuple));
	}

	template <ql::size N, typename T>
	requires(ql::is_tuple<T>() && ql::no_reference<ql::tuple_type<N, T>>)
	constexpr auto tuple_value(T tuple)
	{
		return std::get<N>(std::forward<T>(tuple));
	}

	template <typename T>
	requires(ql::is_tuple<T>() && ql::lvalue<ql::tuple_type<0, T>>)
	constexpr auto& tuple_value_front(T&& tuple)
	{
		return ql::tuple_value<0u>(std::forward<T>(tuple));
	}

	template <typename T>
	requires(ql::is_tuple<T>() && ql::rvalue<ql::tuple_type<0, T>>)
	constexpr auto&& tuple_value_front(T&& tuple)
	{
		return ql::tuple_value<0u>(std::forward<T>(tuple));
	}

	template <typename T>
	requires(ql::is_tuple<T>() && ql::no_reference<ql::tuple_type<0, T>>)
	constexpr auto tuple_value_front(T tuple)
	{
		return ql::tuple_value<0u>(std::forward<T>(tuple));
	}

	template <typename T>
	requires(ql::is_tuple<T>() &&
					 ql::lvalue<ql::tuple_type<ql::tuple_size<T>() - 1, T>>)
	constexpr auto& tuple_value_back(T&& tuple)
	{
		return ql::tuple_value<ql::tuple_size<T>() - 1>(std::forward<T>(tuple));
	}

	template <typename T>
	requires(ql::is_tuple<T>() &&
					 ql::rvalue<ql::tuple_type<ql::tuple_size<T>() - 1, T>>)
	constexpr auto&& tuple_value_back(T&& tuple)
	{
		return ql::tuple_value<ql::tuple_size<T>() - 1>(std::forward<T>(tuple));
	}

	template <typename T>
	requires(ql::is_tuple<T>() &&
					 ql::no_reference<ql::tuple_type<ql::tuple_size<T>() - 1, T>>)
	constexpr auto tuple_value_back(T tuple)
	{
		return ql::tuple_value<ql::tuple_size<T>() - 1>(std::forward<T>(tuple));
	}
}	 // namespace ql