#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/bit/size.hpp>

#include <ql/core/transform/limit.hpp>

namespace ql
{
	template <typename R, typename T>
	requires (ql::bytes_in_type<T>() == ql::bytes_in_type<R>())
	constexpr inline R reinterpret_memory(const T& source)
	{
		R destination;
		memcpy(&destination, &source, ql::bytes_in_type<T>());
		return destination;
	}

	template <typename C>
	requires (ql::has_data<C>() && ql::has_size<C>())
	constexpr inline void container_memory_to_string(const C& data, std::string& destination)
	{
		destination.resize(data.size() * sizeof(ql::container_subtype<C>));
		memcpy(destination.data(), data.data(), destination.size());
	}

	template <typename C>
	requires (ql::is_container<C>())
	constexpr void container_memory_to_wstring(const C& data, std::wstring& destination)
	{
		destination.resize(data.size() * sizeof(ql::container_subtype<C>));
		memcpy(destination.data(), data.data(), destination.size() * (sizeof(wchar_t) / sizeof(char)));
	}

	template <typename C>
	requires (ql::is_container<C>())
	constexpr inline C string_to_container_memory(const std::string& data)
	{
		C result;
		if (data.empty())
		{
			return result;
		}
		result.resize((data.size() - 1) / ql::bytes_in_type<ql::container_subtype<C>>() + 1);
		memcpy(result.data(), data.data(), data.size());
		return result;
	}

	template <typename C>
	inline std::string memory_to_string(const C& data)
	{
		std::string result;
		result.resize(sizeof(C));
		memcpy(result.data(), &data, result.size());
		return result;
	}

	template <typename C>
	constexpr inline std::string stack_memory_to_string(const C& data)
	{
		return ql::memory_to_string(data);
	}

	template <typename C>
	requires (ql::has_data<C>() && ql::has_size<C>())
	constexpr inline std::string heap_memory_to_string(const C& data)
	{
		return ql::container_memory_to_string(data);
	}

	template <typename C>
	inline void string_to_memory(const std::string& data, C& destination)
	{
		memcpy(&destination, data.data(), ql::min(sizeof(C), data.size()));
	}

	template <typename C>
	inline void string_to_stack_memory(const std::string& data, C& destination)
	{
		ql::string_to_memory(data, destination);
	}

	template <typename C>
	requires (ql::has_data<C>() && ql::has_size<C>())
	constexpr inline void string_to_container_memory(const std::string_view& data, C& destination)
	{
		if (data.empty())
		{
			return;
		}
		if constexpr (ql::has_resize<C>())
		{
			destination.resize((data.size() - 1) / sizeof(ql::container_subtype<C>) + 1);
		}
		memcpy(destination.data(), data.data(), data.size());
	}

	template <typename C>
	requires (ql::has_data<C>() && ql::has_size<C>())
	constexpr inline void string_to_heap_memory(const std::string_view& data, C& destination)
	{
		ql::string_to_container_memory(data, destination);
	}

	template <typename C>
	requires (ql::has_data<C>() && ql::has_resize<C>())
	constexpr inline void string_to_heap_memory(const std::string& data, C& destination)
	{
		ql::string_to_container_memory(data, destination);
	}
}	 // namespace ql