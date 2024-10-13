#pragma once

#include <ql/core/definition/definition.hpp>

#if defined QL_GRAPHIC

#include <ql/core/type/compare/compare.hpp>
#include <SFML/Graphics.hpp>

namespace ql
{
	template <bool opengl>
	struct render_type;
	using render = render_type<false>;
	using render_gl = render_type<true>;

	struct render_texture;

	template <typename C>
	concept is_render_texture_c = ql::is_same_decayed<C, ql::render_texture>();

	template <typename C>
	constexpr bool is_render_texture()
	{
		return is_render_texture_c<C>;
	}

	namespace detail
	{
		template <typename C>
		concept has_render_c = requires(const C x, render_type<false>& object) { x.draw(object); };
		template <typename C>
		concept has_render_gl_c = requires(const C x, render_type<true>& object) { x.draw(object); };
	}	 // namespace detail

	template <typename C>
	constexpr bool has_render()
	{
		return detail::has_render_c<C>;
	}

	template <typename C>
	constexpr bool has_render_gl()
	{
		return detail::has_render_gl_c<C>;
	}

	template <typename C>
	concept has_draw_sf_c = requires(const C x, sf::RenderTarget& render, sf::RenderStates states) { x.draw(render, states); };

	template <typename C>
	constexpr bool has_draw_sf()
	{
		return has_draw_sf_c<C>;
	}

	template <typename C>
	concept has_any_draw_c = ql::is_render_texture_c<C> || ql::has_draw_sf_c<C> || ql::has_render<C>() ||
													 ql::has_render_gl<C>() || std::is_base_of_v<sf::Drawable, C>;

	template <typename C>
	constexpr bool has_any_draw()
	{
		return has_any_draw_c<C>;
	}
}

#endif