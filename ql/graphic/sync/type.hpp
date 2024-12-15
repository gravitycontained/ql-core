#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/serialize/serialize.hpp>

namespace ql
{
	struct declare_sync
	{
		bool initialized = false;
	};

	struct declare_unsync{};

	template <typename C>
	concept has_sync_c = requires(C x) { ql::struct_member_size<decltype(x.sync)>(); };

	template <typename C>
	constexpr bool has_sync()
	{
		return has_sync_c<C>;
	}

	template <typename C>
	concept is_sync_c = requires(C x) {
		{ x.declare_sync };
	};

	template <typename C>
	constexpr bool is_sync()
	{
		return is_sync_c<C>;
	}

	template <typename C>
	constexpr bool is_or_has_sync()
	{
		return is_sync<C>() || has_sync<C>();
	}

}	 // namespace ql

#define ql_sync ql::declare_sync declare_sync;
#define ql_unsync ql::declare_unsync declare_unsync;