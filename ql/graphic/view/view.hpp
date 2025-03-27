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
	}	 // namespace detail

	template <typename T>
	constexpr bool is_view()
	{
		return detail::view_signature<ql::decay<T>>{};
	}

	template <typename T>
	concept has_view_priority_c = requires(T x) {
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
}