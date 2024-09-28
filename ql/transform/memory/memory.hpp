#pragma once

#include <ql/definition/definition.hpp>
#include <ql/type/size/size.hpp>

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
}	 // namespace ql