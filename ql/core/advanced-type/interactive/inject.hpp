#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>
#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/serialize/serialize.hpp>

#include <ql/core/advanced-type/interactive/type.hpp>

namespace ql
{

	namespace detail
	{
		template <typename T, typename I>
		concept has_inject_c = requires(T x, I injectable) { x.inject(injectable); };

		template <typename T, typename I>
		constexpr bool has_inject()
		{
			if constexpr (detail::has_inject_c<T, I&>)
				return true;

			if constexpr (ql::is_struct_to_tuple_convertible<T>())
			{
				using update_tuple = decltype(ql::struct_to_tuple(ql::declval_fully_qualified<I&>()));
				using tuple = ql::concat_tuple_type<I&, update_tuple>;
				return ql::constexpr_or_chain<ql::tuple_size<tuple>()>([](auto index)
																															 { return detail::has_inject_c<T, ql::tuple_type<index, tuple>>; });
			}

			return false;
		}

		template <typename T, typename I>
		constexpr void apply_if_inject_param(T& object, I& injectable)
		{
			if constexpr (detail::has_inject<T, I>())
			{
				if constexpr (detail::has_inject_c<T, I&>)
					object.inject(injectable);

				if constexpr (ql::is_struct_to_tuple_convertible<T>())
				{
					auto&& tuple = ql::struct_to_tuple(injectable);

					ql::tuple_iterate(
						tuple,
						[&](auto& member)
						{
							if constexpr (detail::has_inject_c<decltype(object), decltype(member)>)
								object.inject(member);
						}
					);
				}
			}
		}
	};	// namespace detail

	template <typename T, typename I>
	requires (ql::is_or_has_interactive<T>())
	void interactive_inject(T& object, I& injectable)
	{
		detail::apply_if_inject_param(object, injectable);
		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
					tuple,
					[&](auto& member)
					{
						detail::apply_if_inject_param(member, injectable);
						if constexpr (ql::is_or_has_interactive<decltype(member)>())
							interactive_inject(member, injectable);
					}
			);
		};
		if constexpr (ql::has_interactive<T>())
		{
			auto tuple = ql::struct_to_tuple(object.interactive);
			iterate(tuple);
		}
		else if constexpr (ql::is_interactive<T>())
		{
			auto tuple = ql::struct_to_tuple(object);
			iterate(tuple);
		}
	};

	template <typename T>
	struct inject
	{
		T* value = nullptr;
	};
}