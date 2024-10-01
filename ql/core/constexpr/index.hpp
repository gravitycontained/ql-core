#pragma once

#include <ql/core/definition/definition.hpp>

namespace ql
{

	template <ql::size Index, ql::size Size>
	struct constexpr_index
	{
		constexpr operator ql::size()
		{
			return Index;
		}

		constexpr static ql::size size = Size;
		constexpr static ql::size i = Index;
	};
}	 // namespace ql