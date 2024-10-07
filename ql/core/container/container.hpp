#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>
#include <ql/core/transform/limit.hpp>

#include <algorithm>
#include <span>

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

	template <typename C, typename T>
	requires (ql::is_container<C>())
	constexpr auto lower_bound(const C& container, T&& value)
	{
		return std::lower_bound(ql::cbegin(container), ql::cend(container), value);
	}

	template <typename C, typename T>
	requires (ql::is_container<C>())
	constexpr auto upper_bound(const C& container, T&& value)
	{
		return std::upper_bound(ql::cbegin(container), ql::cend(container), value);
	}

	template <typename C, typename T>
	requires (ql::is_container<C>())
	constexpr ql::size find_lower_index_sorted(const C& container, T&& value)
	{
		auto it = ql::lower_bound(container, value);
		if (*it == value)
		{
			return std::distance(ql::cbegin(container), it);
		}
		else
		{
			return ql::size_max;
		}
	}

	template <typename C, typename T>
	requires (ql::is_container<C>())
	constexpr ql::size find_upper_index_sorted(const C& container, T&& value)
	{
		auto it = ql::upper_bound(container, value);
		--it;
		if (*it == value)
		{
			return std::distance(ql::cbegin(container), it);
		}
		else
		{
			return ql::size_max;
		}
	}

	template <typename C, typename T>
	requires (ql::is_container<C>())
	constexpr ql::size find_upper_index(const C& container, T&& value)
	{
		if constexpr (ql::is_sorted_container<C>())
		{
			return ql::find_upper_index_sorted(container, value);
		}
		else
		{
			bool found = false;
			ql::size index = 0u;
			for (auto& i : container)
			{
				if (!found && i == value)
				{
					found = true;
				}
				else if (found && i != value)
				{
					return index;
				}
				++index;
			}
			return ql::size_max;
		}
	}

	template <typename C, typename T>
	requires (ql::is_container<C>() && ql::is_equal_comparable<ql::container_subtype<C>, T>())
	constexpr ql::size count_sorted(const C& container, T&& value)
	{
		auto lower_index = ql::find_lower_index_sorted(container, value);
		auto upper_index = ql::find_upper_index_sorted(container, value);
		if (lower_index == ql::size_max)
		{
			return 0u;
		}
		return (upper_index - lower_index) + 1;
	}

	template <typename C, typename T>
	requires (ql::is_container<C>() && ql::is_equal_comparable<ql::container_subtype<C>, T>())
	constexpr ql::size count(const C& container, T&& value)
	{
		if constexpr (ql::is_sorted_container<C>())
		{
			return ql::count_sorted(container, value);
		}
		else
		{
			ql::size sum = 0u;
			for (auto& i : container)
			{
				if (i == value)
				{
					++sum;
				}
			}
			return sum;
		}
	}

	template <typename C>
	std::pair<ql::container_subtype<C>, ql::container_subtype<C>> min_max(const C& data)
	{
		auto v = std::minmax_element(data.cbegin(), data.cend());
		return {*(v.first), *(v.second)};
	}

	template <typename T, typename T2>
	std::pair<std::decay_t<T>, std::decay_t<T>> min_max(const std::span<T>& data, T2 skip_size)
	{
		if (data.empty())
		{
			return std::make_pair(std::decay_t<T>{}, std::decay_t<T>{});
		}
		std::decay_t<T> min = data.front();
		std::decay_t<T> max = data.front();
		for (T2 i = 0; i < data.size(); i += skip_size)
		{
			min = ql::min(min, data[i]);
			max = ql::min(max, data[i]);
		}
		return std::make_pair(min, max);
	}

}	 // namespace ql