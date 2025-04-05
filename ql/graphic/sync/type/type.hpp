#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/serialize/serialize.hpp>
#include <ql/core/advanced-type/container/bitset.hpp>
#include <ql/core/transform/modal-apply.hpp>

namespace ql
{
	namespace detail
	{
		QL_SOURCE extern ql::size sync_initialization_request_count;
		QL_SOURCE extern ql::size sync_injection_request_count;
	}
	struct sync_options
	{
		bool initialized = false;
		bool draw = true;
		bool update = true;
		bool active = true;

		sync_options()
		{
			++detail::sync_initialization_request_count;
		}
	};

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
		{ x.sync_options };
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
	constexpr void sync_apply(T&& value, F function)
	{
		if constexpr (ql::is_sync<ql::modal_decay<decltype(value)>>())
			function(std::forward<decltype(value)>(value));

		if constexpr (ql::has_sync<ql::modal_decay<decltype(value)>>())
			function(std::forward<decltype(value.sync)>(value.sync));

		if constexpr (ql::has_sync_extension<ql::modal_decay<decltype(value)>>())
			function(std::forward<decltype(value.sync_extension)>(value.sync_extension));
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

}	 // namespace ql

#define ql_sync() ql::sync_options sync_options;

#define ql_sync_within(...) \
  struct \
  { \
    ql::sync_options sync_options; \
    __VA_ARGS__ \
  } sync;

#define ql_sync_extension_within(...) \
  struct \
  { \
    ql::sync_options sync_options; \
    __VA_ARGS__ \
  } sync_extension;
