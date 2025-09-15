#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/advanced-type/view/view.hpp>
#include <ql/graphic/view/view-control.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T>
		struct view_signature : std::false_type
		{
		};

		template <typename T>
		struct view_signature<ql::view_control_t<T>> : std::true_type
		{
		};

		template <typename T>
		struct view_signature<ql::view_type<T>> : std::true_type
		{
		};

		template <typename T>
		struct view_control_signature : std::false_type
		{
		};

		template <typename T>
		struct view_control_signature<ql::view_control_t<T>> : std::true_type
		{
		};
	}	 // namespace detail

	template <typename T>
	constexpr bool is_view()
	{
		return detail::view_signature<ql::decay<T>>{};
	}

	template <typename T>
	constexpr bool is_view_control()
	{
		return detail::view_control_signature<ql::decay<T>>{};
	}

	template <typename T>
	concept has_view_priority_c = requires(T x)
	{
		{
			x.view_priority
		};
		requires ql::is_view<ql::decay<decltype(T::view_priority)>>();
	};

	template <typename T>
	constexpr bool has_view_priority()
	{
		return has_view_priority_c<ql::decay<T>>;
	}
 
	template <typename T>
	concept has_modify_view_c = requires(T x) {
		{ x.modify_view(ql::view{}) } -> std::same_as<ql::view>;
	};

	template <typename T>
	constexpr bool has_modify_view()
	{
		return has_modify_view_c<ql::decay<T>>;
	}

	template <typename T>
	concept has_modify_view_no_parameter_c = requires(T x) {
		{ x.modify_view() } -> std::same_as<ql::view>;
	};

	template <typename T>
	constexpr bool has_modify_view_no_parameter()
	{
		return has_modify_view_no_parameter_c<ql::decay<T>>;
	}

	#define ql_sync_apply_default_view() ql::view modify_view() const { return ql::view{}; }

}