#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/conditional.hpp>

#include <ql/core/type/pointer/pointer.hpp>
#include <ql/core/type/container/is-container.hpp>
#include <ql/core/type/container/subtype.hpp>

#include <memory>

namespace ql
{
	namespace detail
	{
		template <typename T>
		struct modal_decay
		{
			using type = T;
		};

		template <typename T>
		requires (ql::is_pointer<T>())
		struct modal_decay<T>
		{
			using type = modal_decay<ql::decay<ql::remove_pointer<T>>>::type;
		};

		template <typename T>
		requires (ql::is_container<T>())
		struct modal_decay<T>
		{
			using type = modal_decay<ql::decay<ql::container_subtype<T>>>::type;
		};

		template <typename T>
		constexpr auto modal_decay_helper(T&& value)
		{
			if constexpr (ql::is_pointer<T>())
				return modal_decay_helper(*value);

			else if constexpr (ql::is_container<T>())
				return modal_decay_helper(*value.begin());

			else
				return value;
		}

	}	 // namespace detail

	template <typename T>
	using modal_decay = typename detail::modal_decay<ql::decay<T>>::type;

	//template <typename T>
	//using modal_decay = decltype(detail::modal_decay_helper(std::declval<T>()));

}	 // namespace ql