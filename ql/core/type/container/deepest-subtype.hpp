#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/container/is-container.hpp>
#include <ql/core/type/container/subtype.hpp>

namespace ql
{
	namespace detail
	{
		template <typename C>
		auto container_deepest_subtype()
		{
			if constexpr (!ql::is_container<C>())
			{
				return ql::declval<C>();
			}
			else if constexpr (ql::is_container<ql::container_subtype<C>>())
			{
				return ql::detail::container_deepest_subtype<ql::container_subtype<C>>();
			}
			else
			{
				return ql::declval<ql::container_subtype<C>>();
			}
		}
	}	 // namespace detail

	template <typename C>
	using container_deepest_subtype = decltype(ql::detail::container_deepest_subtype<C>());

}	 // namespace ql