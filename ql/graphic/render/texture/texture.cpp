#include <ql/graphic/render/texture/texture.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/resources/resources.hpp>

namespace ql
{
	void ql::render_texture::set_antialiasing(ql::u32 antialiasing)
	{
		this->m_settings.antialiasingLevel = antialiasing;
	}

	void ql::render_texture::resize(ql::vector2i dimension, bool resize_with_window)
	{
		if (this->m_create_size.x < dimension.x || this->m_create_size.y < dimension.y)
		{
			this->m_create_size = dimension;
			this->m_texture.create(dimension.x, dimension.y, this->m_settings);
			this->m_sprite.set_texture(this->m_texture.getTexture());
		}

		sf::IntRect rect{0, 0, dimension.x, dimension.y};
		this->m_sprite.m_sprite.setTextureRect(rect);
		this->m_changed = true;
		this->m_resize_with_window = resize_with_window;
	}

	void ql::render_texture::set_smooth(bool b)
	{
		this->m_smooth = b;
		this->m_texture.setSmooth(b);
	}

	void ql::render_texture::enable_smooth()
	{
		this->set_smooth(true);
	}

	void ql::render_texture::disable_smooth()
	{
		this->set_smooth(false);
	}

	bool ql::render_texture::is_smooth() const
	{
		return this->m_smooth;
	}

	void ql::render_texture::enable_resize_with_window()
	{
		this->m_resize_with_window = true;
	}

	void ql::render_texture::disable_resize_with_window()
	{
		this->m_resize_with_window = false;
	}

	bool ql::render_texture::is_resize_with_window_enabled() const
	{
		return this->m_resize_with_window;
	}

	void ql::render_texture::enable_clear_with_window()
	{
		this->m_clear_with_window = true;
	}

	void ql::render_texture::disable_clear_with_window()
	{
		this->m_clear_with_window = false;
	}

	bool ql::render_texture::is_clear_with_window_enabled() const
	{
		return this->m_clear_with_window;
	}

	void ql::render_texture::set_color(ql::rgba color)
	{
		this->m_sprite.set_color(color);
	}

	void ql::render_texture::set_position(ql::vec2 position)
	{
		this->m_sprite.set_position(position);
	}

	void ql::render_texture::set_scale(ql::vec2 scale)
	{
		this->m_sprite.set_scale(scale);
	}

	void ql::render_texture::set_scale(ql::f32 scale)
	{
		this->m_sprite.set_scale(scale);
	}

	void ql::render_texture::set_origin(ql::vec2 origin)
	{
		this->m_sprite.set_origin(origin);
	}

	void ql::render_texture::set_rotation(ql::f32 rotation)
	{
		this->m_sprite.set_rotation(rotation);
	}

	ql::rgba ql::render_texture::get_color() const
	{
		return this->m_sprite.get_color();
	}

	ql::vec2 ql::render_texture::get_position() const
	{
		return this->m_sprite.get_position();
	}

	ql::vec2 ql::render_texture::get_scale() const
	{
		return this->m_sprite.get_scale();
	}

	ql::vec2 ql::render_texture::get_origin() const
	{
		return this->m_sprite.get_origin();
	}

	ql::f32 ql::render_texture::get_rotation() const
	{
		return this->m_sprite.get_rotation();
	}

	ql::vec2 ql::render_texture::get_dimension() const
	{
		return this->m_texture.getSize();
	}

	ql::vec2 ql::render_texture::get_center() const
	{
		return this->m_sprite.get_position() + this->get_dimension() / 2;
	}

	void ql::render_texture::move(ql::vec2 delta)
	{
		this->m_sprite.move(delta);
	}

	void ql::render_texture::move_scaled(ql::vec2 delta)
	{
		this->m_sprite.move(delta / this->get_scale());
	}

	const ql::sprite& ql::render_texture::get_sprite() const
	{
		if (this->m_changed)
		{
			this->apply();
		}
		return this->m_sprite;
	}

	void ql::render_texture::clear()
	{
		this->m_texture.clear();
	}

	void ql::render_texture::display()
	{
		this->m_texture.display();
	}

	const sf::RenderStates& ql::render_texture::get_render_states() const
	{
		return this->m_states;
	}

	const sf::Texture& ql::render_texture::get_texture() const
	{
		return this->m_texture.getTexture();
	}

	void ql::render_texture::set_shader(const std::string& name)
	{
		this->m_states.shader = &ql::get_shader(name);
	}

	void ql::render_texture::set_shader(sf::Shader& shader)
	{
		this->m_states.shader = &shader;
	}

	void ql::render_texture::unbind_shader()
	{
		this->m_states.shader = nullptr;
	}

	void ql::render_texture::apply() const
	{
		this->m_texture.display();
		this->m_changed = false;
	}
}	 // namespace ql

#endif