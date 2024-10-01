#pragma once

#include <tuple>

#include <ql/core/constexpr/constexpr.hpp>

namespace ql
{
	template <typename... Args>
	constexpr auto to_tuple(Args&&... args)
	{
		return std::make_tuple(std::forward<Args>(args)...);
	}
}	 // namespace ql
