#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

namespace ql
{

	template <typename C>
	requires (ql::is_container<C>())
	constexpr auto begin(C& container)
	{
		if constexpr (ql::is_read_container<C>() && ql::is_write_container<C>())
		{
			return container.begin();
		}
		else if constexpr (ql::is_read_container<C>())
		{
			return container.cbegin();
		}
		else if constexpr (ql::is_write_container<C>())
		{
			return container.begin();
		}
	}

	template <typename C>
	requires (ql::is_container<C>())
	constexpr auto cbegin(C& container)
	{
		if constexpr (ql::is_read_container<C>() && ql::is_write_container<C>())
		{
			return container.cbegin();
		}
		else if constexpr (ql::is_read_container<C>())
		{
			return container.cbegin();
		}
		else if constexpr (ql::is_write_container<C>())
		{
			return container.begin();
		}
	}

	template <typename C>
	requires (ql::is_container<C>())
	constexpr auto end(C& container)
	{
		if constexpr (ql::is_read_container<C>() && ql::is_write_container<C>())
		{
			return container.end();
		}
		else if constexpr (ql::is_read_container<C>())
		{
			return container.cend();
		}
		else if constexpr (ql::is_write_container<C>())
		{
			return container.end();
		}
	}

	template <typename C>
	requires (ql::is_container<C>())
	constexpr auto cend(C& container)
	{
		if constexpr (ql::is_read_container<C>() && ql::is_write_container<C>())
		{
			return container.cend();
		}
		else if constexpr (ql::is_read_container<C>())
		{
			return container.cend();
		}
		else if constexpr (ql::is_write_container<C>())
		{
			return container.end();
		}
	}

	template <typename C>
	requires (ql::is_container<C>() && ql::has_size<C>())
	ql::size container_size(const C& data)
	{
		if constexpr (ql::is_container<ql::container_subtype<C>>())
		{
			ql::size sum = ql::size{};
			for (const auto& e : data)
			{
				sum += container_size(e);
			}
			return sum;
		}
		else
		{
			return data.size();
		}
	}

	template <typename C>
	requires (ql::is_container<C>())
	constexpr ql::size container_depth()
	{
		return ql::is_container<C>
							 ? (ql::is_container<ql::container_subtype<C>>() ? ql::container_depth<ql::container_subtype<C>>() + ql::size{1}
																															 : ql::size{1})
							 : ql::size{};
	}

	template <typename C>
	requires (ql::is_container<C>())
	constexpr auto container_sum(const C& data)
	{
		if (data.size() == 0)
		{
			return ql::container_subtype<C>{};
		}
		auto sum = data[0];
		for (ql::u32 i = 1u; i < data.size(); ++i)
		{
			sum += data[i];
		}
		return sum;
	}

}	 // namespace ql