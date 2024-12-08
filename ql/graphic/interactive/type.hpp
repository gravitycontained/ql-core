#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/serialize/serialize.hpp>

namespace ql
{
	struct declare_interactive
	{
	};

	template <typename C>
	concept has_interactive_c = requires(C x) { ql::struct_member_size<decltype(x.interactive)>(); };

	template <typename C>
	constexpr bool has_interactive()
	{
		return has_interactive_c<C>;
	}

	template <typename C>
	concept is_interactive_c = requires(C x) {
		{ x.declare_interactive };
	};

	template <typename C>
	constexpr bool is_interactive()
	{
		return is_interactive_c<C>;
	}

	template <typename C>
	constexpr bool is_or_has_interactive()
	{
		return is_interactive<C>() || has_interactive<C>();
	}

}	 // namespace ql