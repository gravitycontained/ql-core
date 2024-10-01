#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/container/is-container.hpp>
#include <ql/core/type/container/subtype.hpp>
#include <ql/core/container/container.hpp>

namespace ql
{
	template <typename C>
	requires (ql::is_container<C>())
	constexpr void fill_zeroes(C& container)
	{
		if constexpr (ql::is_container<ql::container_subtype<C>>())
		{
			for (auto& i : container)
			{
				ql::fill_zeroes(i);
			}
		}
		else
		{
			if constexpr (ql::is_contiguous_container<C>() && ql::has_size<C>())
			{
				memset(container.data(), 0, container.size() * ql::bytes_in_type<ql::container_subtype<C>>());
			}
			else
			{
				std::fill(ql::begin(container), ql::end(container), ql::container_subtype<C>{0});
			}
		}
	}

	template <typename C>
	requires (ql::is_container<C>())
	constexpr C filled_zeroes(const C& container)
	{
		auto result = container;
		ql::fill_zeroes(result);
		return result;
	}

	template <typename C, typename T>
	requires (ql::is_container<C>())
	constexpr void fill(C& container, T&& value)
	{
		if (!value)
		{
			ql::fill_zeroes(container);
		}
		if constexpr (ql::is_container<ql::container_subtype<C>>())
		{
			for (auto& i : container)
			{
				ql::fill(i, value);
			}
		}
		else
		{
			std::fill(ql::begin(container), ql::end(container), ql::type_cast<ql::container_subtype<C>>(value));
		}
	}
}	 // namespace ql