#pragma once
#include <ql/graphic/interactive/create-function.hpp>
#include <ql/core/advanced-type/interactive/type.hpp>
#include <ql/graphic/interactive/definition-list.hpp>

#include <ql/graphic/update/update.hpp>

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

#include <ql/graphic/state/state-manager/state-manager.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T>
		constexpr void apply_update_new(T& object, ql::state_manager& manager, bool& provided)
		{
			if constexpr (ql::is_interactive<T>())
				if (!object.declare_interactive.initialized)
				{

					if (!provided)
					{
						ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "manager.provide() called");
						manager.provide();
						provided = true;
					}

					ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "apply_update_new actually initialized the object ", ql::color::aqua, &object);
					ql::interactive_init(object);
					object.declare_interactive.initialized = true;
				}
		}
	}	 // namespace detail

	template <typename T>
	requires (ql::is_or_has_interactive<T>())
	void interactive_update_new_helper(T& object, ql::state_manager& manager, bool& provided)
	{
		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
					tuple,
					[&](auto& member)
					{
						if constexpr (ql::is_container<decltype(member)>())
						{
							if constexpr (ql::is_or_has_interactive<ql::container_subtype<decltype(member)>>())
								for (auto& sub_member : member)
									interactive_update_new_helper(sub_member, manager, provided);
						}
						if constexpr (ql::is_or_has_interactive<decltype(member)>())
							interactive_update_new_helper(member, manager, provided);
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

		detail::apply_update_new(object, manager, provided);
	}

	template <typename T>
	requires (ql::is_or_has_interactive<T>())
	void interactive_update_new(T& object, ql::state_manager& manager)
	{
		bool provided = false;
		interactive_update_new_helper(object, manager, provided);
	}
}	 // namespace ql