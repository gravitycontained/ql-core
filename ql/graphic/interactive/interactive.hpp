#pragma once
// #include <ql/graphic/interactive/draw.hpp>
// #include <ql/graphic/interactive/init.hpp>
// #include <ql/graphic/interactive/update-signal.hpp>
// #include <ql/graphic/interactive/update.hpp>
#include <ql/graphic/interactive/type.hpp>

#include <ql/graphic/update/update.hpp>

#include <ql/core/constexpr/constexpr.hpp>
#include <ql/core/type/type.hpp>

#define ql_state_interactive(param)               				 \
	void initializing_interaction() override        				 \
	{                                               				 \
		this->interactive_init_interaction(param);             \
	}                                               				 \
	void initializing() override                    				 \
	{                                               				 \
		this->interactive_init(param);                				 \
	}                                               				 \
                                                  				 \
	void updating() override                        				 \
	{                                               				 \
		this->interactive_update(param);              				 \
	}                                               				 \
                                                  				 \
	void updating_phase_signal_run() override           		 \
	{                                               				 \
		this->interactive_update_phase_signal_run(param); 		 \
	}                                               				 \
                                                  				 \
	void updating_phase_signal_detect() override           	 \
	{                                                   		 \
		this->interactive_update_phase_signal_detect(param); 	 \
	}                                               				 \
                                                  				 \
	void drawing() override                         				 \
	{                                               				 \
		this->interactive_draw(param);                				 \
	}																												 \

#define ql_declare_interactive ql::declare_interactive declare_interactive;

#define ql_detail_phase(function)                                                                     \
	namespace detail                                                                                    \
	{                                                                                                   \
		template <typename C, typename T>                                                                 \
		concept has_##function##_c = requires(C x, T update) { x.##function##(update); };                 \
                                                                                                      \
		template <typename C>                                                                             \
		concept has_##function##_no_parameter_c = requires(C x) { x.##function##(); };                    \
                                                                                                      \
		template <typename T>                                                                             \
		constexpr bool has_##function##_update()                                                          \
		{                                                                                                 \
			if constexpr (has_##function##_no_parameter_c<T>)                                               \
				return true;                                                                                  \
                                                                                                      \
			using update_tuple = decltype(ql::struct_to_tuple(ql::declval_fully_qualified<ql::update&>())); \
			using tuple = ql::concat_tuple_type<ql::update&, update_tuple>;                                 \
			return ql::constexpr_or_chain<ql::tuple_size<tuple>()>(                                         \
					[](auto index)                                                                              \
					{                                                                                           \
						return detail::has_##function##_c<T, ql::tuple_type<index, tuple>> ||                     \
									 detail::has_##function##_c<ql::tuple_type<index, tuple>, T>;                       \
					}                                                                                           \
			);                                                                                              \
		}                                                                                                 \
                                                                                                      \
		template <typename T>                                                                             \
		constexpr void apply_if_##function##_param(T& object, ql::update& update)                         \
		{                                                                                                 \
			if constexpr (detail::has_##function##_update<T>())                                             \
			{                                                                                               \
				if constexpr (detail::has_##function##_no_parameter_c<T>)                                     \
					object.##function##();                                                                      \
                                                                                                      \
				if constexpr (detail::has_##function##_c<T, ql::update&>)                                     \
					object.##function##(update);                                                                \
                                                                                                      \
				auto&& tuple = ql::struct_to_tuple(update);                                                   \
                                                                                                      \
				ql::tuple_iterate(                                                                            \
						tuple,                                                                                    \
						[&](auto& member)                                                                         \
						{                                                                                         \
							if constexpr (detail::has_##function##_c<decltype(member), decltype(object)>)           \
								member.##function##(object);                                                          \
                                                                                                      \
							if constexpr (detail::has_##function##_c<decltype(object), decltype(member)>)           \
								object.##function##(member);                                                          \
						}                                                                                         \
				);                                                                                            \
			}                                                                                               \
		}                                                                                                 \
	}

#define ql_create_phase(function)                                        \
	template <typename T>                                                  \
	requires (ql::is_or_has_interactive<T>())                              \
	void interactive_##function(T& object, ql::update& update)             \
	{                                                                      \
		detail::apply_if_##function##_param(object, update);                 \
                                                                         \
		auto iterate = [&](auto& tuple)                                      \
		{                                                                    \
			ql::tuple_iterate(                                                 \
					tuple,                                                         \
					[&](auto& member)                                              \
					{                                                              \
						detail::apply_if_##function##_param(member, update);         \
                                                                         \
						if constexpr (ql::is_or_has_interactive<decltype(member)>()) \
							interactive_##function(member, update);                    \
					}                                                              \
			);                                                                 \
		};                                                                   \
                                                                         \
		if constexpr (ql::has_interactive<T>())                              \
		{                                                                    \
			auto tuple = ql::struct_to_tuple(object.interactive);              \
			iterate(tuple);                                                    \
		}                                                                    \
                                                                         \
		else if constexpr (ql::is_interactive<T>())                          \
		{                                                                    \
			auto tuple = ql::struct_to_tuple(object);                          \
			iterate(tuple);                                                    \
		}                                                                    \
	}

#define ql_create_phase_bottom_up(function)                              \
	template <typename T>                                                  \
	requires (ql::is_or_has_interactive<T>())                              \
	void interactive_##function(T& object, ql::update& update)             \
	{                                                                      \
		auto iterate = [&](auto& tuple)                                      \
		{                                                                    \
			ql::tuple_iterate(                                                 \
					tuple,                                                         \
					[&](auto& member)                                              \
					{                                                              \
						if constexpr (ql::is_or_has_interactive<decltype(member)>()) \
							interactive_##function(member, update);                    \
                                                                         \
						detail::apply_if_##function##_param(member, update);         \
					}                                                              \
			);                                                                 \
		};                                                                   \
                                                                         \
		if constexpr (ql::has_interactive<T>())                              \
		{                                                                    \
			auto tuple = ql::struct_to_tuple(object.interactive);              \
			iterate(tuple);                                                    \
		}                                                                    \
                                                                         \
		else if constexpr (ql::is_interactive<T>())                          \
		{                                                                    \
			auto tuple = ql::struct_to_tuple(object);                          \
			iterate(tuple);                                                    \
		}                                                                    \
                                                                         \
		detail::apply_if_##function##_param(object, update);                 \
	}

#define ql_add_interactive_phase(function) \
	ql_detail_phase(function);               \
	ql_create_phase(function);

#define ql_add_interactive_bottom_phase(function) \
	ql_detail_phase(function);                      \
	ql_create_phase_bottom_up(function);

namespace ql
{
	ql_add_interactive_bottom_phase(init_interaction);
	ql_add_interactive_bottom_phase(init);
	ql_add_interactive_phase(update);
	ql_add_interactive_phase(update_phase_signal_run);
	ql_add_interactive_phase(update_phase_signal_detect);

	//ql_add_interactive_phase(draw);

	namespace detail
	{
		template <typename C, typename T>
		concept has_draw_c = requires(C x, T update) { x.draw(update); };
		template <typename C>
		concept has_draw_no_parameter_c = requires(C x) { x.draw(); };

		template <typename T>
		constexpr bool has_draw_update()
		{
			if constexpr (has_draw_no_parameter_c<T>)
				return true;
			using update_tuple = decltype(ql::struct_to_tuple(ql::declval_fully_qualified<ql::update&>()));
			using tuple = ql::concat_tuple_type<ql::update&, update_tuple>;
			return ql::constexpr_or_chain<ql::tuple_size<tuple>()>(
					[](auto index)
					{ return detail::has_draw_c<ql::tuple_type<index, tuple>, T>; }
			);
		}

		template <typename T>
		constexpr void apply_if_draw_param(T& object, ql::update& update)
		{
			if constexpr (detail::has_draw_update<T>())
			{
				if constexpr (detail::has_draw_no_parameter_c<T>)
					object.draw();

				if constexpr (ql::has_draw<decltype(object)>())
					update.render.draw(object);
			}
		}
	};	// namespace detail

	template <typename T>
	requires (ql::is_or_has_interactive<T>())
	void interactive_draw(T& object, ql::update& update)
	{
		detail::apply_if_draw_param(object, update);
		auto iterate = [&](auto& tuple)
		{
			ql::tuple_iterate(
					tuple,
					[&](auto& member)
					{
						detail::apply_if_draw_param(member, update);
						if constexpr (ql::is_or_has_interactive<decltype(member)>())
							interactive_draw(member, update);
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
}	 // namespace ql


