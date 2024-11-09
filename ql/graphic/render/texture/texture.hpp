#pragma once

#include <ql/core/core.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/drawable/basic/sprite/sprite.hpp>

namespace ql
{
	struct render_texture
	{
		QL_SOURCE void set_antialiasing(ql::u32 antialiasing);
		QL_SOURCE void resize(ql::vector2i dimension, bool resize_with_window = false);
		QL_SOURCE void set_smooth(bool smooth);
		QL_SOURCE void enable_smooth();
		QL_SOURCE void disable_smooth();
		QL_SOURCE bool is_smooth() const;
		QL_SOURCE void enable_resize_with_window();
		QL_SOURCE void disable_resize_with_window();
		QL_SOURCE bool is_resize_with_window_enabled() const;

		QL_SOURCE void enable_clear_with_window();
		QL_SOURCE void disable_clear_with_window();
		QL_SOURCE bool is_clear_with_window_enabled() const;

		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_scale(ql::vec2 scale);
		QL_SOURCE void set_scale(ql::f32 scale);
		QL_SOURCE void set_origin(ql::vec2 origin);
		QL_SOURCE void set_rotation(ql::f32 rotation);

		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::vec2 get_scale() const;
		QL_SOURCE ql::vec2 get_origin() const;
		QL_SOURCE ql::f32 get_rotation() const;
		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_center() const;

		QL_SOURCE void move(ql::vec2 delta);
		QL_SOURCE void move_scaled(ql::vec2 delta);

		QL_SOURCE const ql::sprite& get_sprite() const;
		QL_SOURCE void clear();
		QL_SOURCE void display();

		QL_SOURCE const sf::RenderStates& get_render_states() const;
		QL_SOURCE const sf::Texture& get_texture() const;

		QL_SOURCE void set_shader(const std::string& name);
		QL_SOURCE void set_shader(sf::Shader& shader);
		QL_SOURCE void unbind_shader();

		template <typename T>
		requires (ql::has_any_draw<T>())
		void draw(const T& object)
		{
			if constexpr (ql::is_render_texture<T>())
			{
				this->m_texture.draw(object.get_sprite(), this->m_states);
				this->m_changed = true;
			}
			else if constexpr (std::is_base_of<sf::Drawable, T>())
			{
				this->m_texture.draw(object, this->m_states);
				this->m_changed = true;
			}
			else if constexpr (ql::has_render<T>())
			{
				render draw(this->m_texture, this->m_states);
				object.draw(draw);
				this->m_changed = true;
			}
			else if constexpr (ql::has_draw_sf<T>())
			{
				object.draw(this->m_texture, this->m_states);
				this->m_changed = true;
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>())
		void draw(const T& object, sf::RenderStates states)
		{
			if constexpr (ql::is_render_texture<T>())
			{
				this->m_texture.draw(object.get_sprite(), states);
				this->m_changed = true;
			}
			else if constexpr (std::is_base_of<sf::Drawable, T>())
			{
				this->m_texture.draw(object, states);
				this->m_changed = true;
			}
			else if constexpr (ql::has_render<T>())
			{
				render draw(this->m_texture, states);
				object.draw(draw);
				this->m_changed = true;
			}
			else if constexpr (ql::has_draw_sf<T>())
			{
				object.draw(this->m_texture, states);
				this->m_changed = true;
			}
		}

		QL_SOURCE void apply() const;

		mutable sf::RenderTexture m_texture;
		mutable ql::sprite m_sprite;
		mutable bool m_changed = false;
		ql::vector2i m_create_size;
		bool m_smooth = false;
		bool m_resize_with_window = true;
		bool m_clear_with_window = true;
		sf::RenderStates m_states;
		sf::ContextSettings m_settings;
	};

}

#endif