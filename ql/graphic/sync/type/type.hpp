#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/serialize/serialize.hpp>
#include <ql/core/advanced-type/container/bitset.hpp>
#include <ql/core/transform/modal-apply.hpp>

namespace ql
{
	namespace detail
	{
		QL_SOURCE extern ql::size sync_unitialized_count;
	}
	struct declare_sync
	{
		bool initialized = false;
		bool draw = true;
		bool update = true;
		bool active = true;

		declare_sync()
		{
			++detail::sync_unitialized_count;
		}
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
	concept has_sync_extension_c = requires(C x) { ql::struct_member_size<decltype(x.sync_extension)>(); };

	template <typename C>
	constexpr bool has_sync_extension()
	{
		return has_sync_extension_c<C>;
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
		return is_sync<C>() || has_sync<C>() || has_sync_extension<C>();
	}


	template <typename T, typename F>
	constexpr void sync_modal_apply(T&& value, F function)
	{
		if constexpr (ql::is_sync<ql::modal_decay<decltype(value)>>())
			ql::modal_apply(std::forward<decltype(value)>(value), function);

		if constexpr (ql::has_sync<ql::modal_decay<decltype(value)>>())
			ql::modal_apply(std::forward<decltype(value.sync)>(value.sync), function);

		if constexpr (ql::has_sync_extension<ql::modal_decay<decltype(value)>>())
			ql::modal_apply(std::forward<decltype(value.sync_extension)>(value.sync_extension), function);
	}

	template <bool order, typename T, typename F>
	constexpr void sync_apply_soft(T&& value, F function)
	{
		if constexpr (order)
		{
			function(std::forward<decltype(value)>(value));

			if constexpr (ql::has_sync<decltype(value)>())
				function(std::forward<decltype(value.sync)>(value.sync));

			if constexpr (ql::has_sync_extension<decltype(value)>())
				function(std::forward<decltype(value.sync_extension)>(value.sync_extension));
		}
		else
		{
			if constexpr (ql::has_sync_extension<decltype(value)>())
				function(std::forward<decltype(value.sync_extension)>(value.sync_extension));

			if constexpr (ql::has_sync<decltype(value)>())
				function(std::forward<decltype(value.sync)>(value.sync));

			function(std::forward<decltype(value)>(value));
		}
	}

	template <typename T>
	requires (ql::is_or_has_sync<T>())
	constexpr auto&& sync_resolve(T&& value)
	{
		if constexpr (ql::is_sync<decltype(value)>())
			return std::forward<decltype(value)>(value);

		else if constexpr (ql::has_sync<decltype(value)>())
			return std::forward<decltype(value.sync)>(value.sync);

		else
			return std::forward<decltype(value.sync_extension)>(value.sync_extension);
	}

	template <typename T>
	requires (ql::is_or_has_sync<T>())
	constexpr auto&& sync_resolve_backwards(T&& value)
	{
		if constexpr (ql::has_sync_extension<decltype(value)>())
			return std::forward<decltype(value.sync_extension)>(value.sync_extension);

		else if constexpr (ql::has_sync<decltype(value)>())
			return std::forward<decltype(value.sync)>(value.sync);

		else
			return std::forward<decltype(value)>(value);
	}

}	 // namespace ql

#define ql_sync ql::declare_sync declare_sync;
#define ql_unsync ql::declare_unsync declare_unsync;

#define ql_sync_within(...) \
  struct \
  { \
    ql::declare_sync declare_sync; \
    __VA_ARGS__ \
  } sync;

#define ql_sync_extension_within(...) \
  struct \
  { \
    ql::declare_sync declare_sync; \
    __VA_ARGS__ \
  } sync_extension;
