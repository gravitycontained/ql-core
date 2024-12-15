#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/conditional.hpp>

#include <ql/core/type/container/is-container.hpp>
#include <ql/core/type/container/subtype.hpp>

#include <memory>

namespace ql
{
	namespace detail
	{
		template <typename T>
		struct pointer_type : std::false_type
		{
			using type = T;
		};

		template <typename T>
		struct pointer_type<std::shared_ptr<T>> : std::true_type
		{
			using type = T;
		};

		template <typename T>
		struct pointer_type<std::unique_ptr<T>> : std::true_type
		{
			using type = T;
		};

		template <typename T>
		struct pointer_type<std::weak_ptr<T>> : std::true_type
		{
			using type = T;
		};

	}	 // namespace detail

	template <typename T>
	constexpr bool is_pointer()
	{
		return std::is_pointer_v<T> || detail::pointer_type<T>{};
	}

	template <typename T>
	using remove_pointer = typename detail::pointer_type<T>::type;
}	 // namespace ql