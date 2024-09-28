#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/bit/size.hpp>

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
}	 // namespace ql