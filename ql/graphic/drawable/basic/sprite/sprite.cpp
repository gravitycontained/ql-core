#include <ql/graphic/drawable/basic/sprite/sprite.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/util/sprite/sprite.hpp>

namespace ql
{

	void ql::sprite::set_texture(const sf::Texture& texture)
	{
		this->m_sprite.setTexture(texture);
	}

	void ql::sprite::set_texture_rect(const sf::IntRect& rect)
	{
		this->m_sprite.setTextureRect(rect);
	}

	void ql::sprite::set_texture_rect(ql::hitbox hitbox)
	{
		sf::IntRect rect;
		rect.left = ql::i32_cast(hitbox.position.x);
		rect.top = ql::i32_cast(hitbox.position.y);
		rect.width = ql::i32_cast(hitbox.dimension.x);
		rect.height = ql::i32_cast(hitbox.dimension.y);
		this->m_sprite.setTextureRect(rect);
	}

	void ql::sprite::set_color(ql::rgba color)
	{
		this->m_sprite.setColor(color);
	}

	void ql::sprite::set_position(ql::vec2 position)
	{
		this->m_sprite.setPosition(position);
	}

	void ql::sprite::set_position_x(ql::f32 x)
	{
		auto y = this->get_position().y;
		this->m_sprite.setPosition(ql::vec(x, y));
	}

	void ql::sprite::set_position_y(ql::f32 y)
	{
		auto x = this->get_position().x;
		this->m_sprite.setPosition(ql::vec(x, y));
	}

	void ql::sprite::set_center(ql::vec2 position)
	{
		this->m_sprite.setPosition(position);
		ql::centerize_sprite(this->m_sprite);
	}

	void ql::sprite::set_scale(ql::vec2 scale)
	{
		this->m_sprite.setScale(scale);
	}

	void ql::sprite::set_scale(ql::f32 scale)
	{
		this->m_sprite.setScale(scale, scale);
	}

	void ql::sprite::set_origin(ql::vec2 origin)
	{
		this->m_sprite.setOrigin(origin);
	}

	void ql::sprite::set_rotation(ql::f32 rotation)
	{
		this->m_sprite.setRotation(rotation);
	}

	ql::rgba ql::sprite::get_color() const
	{
		return this->m_sprite.getColor();
	}

	ql::vec2 ql::sprite::get_position() const
	{
		return this->m_sprite.getPosition();
	}

	ql::vec2 ql::sprite::get_dimension() const
	{
		return ql::get_sprite_hitbox(this->m_sprite).dimension;
	}

	ql::vec2 ql::sprite::get_scale() const
	{
		return this->m_sprite.getScale();
	}

	ql::vec2 ql::sprite::get_origin() const
	{
		return this->m_sprite.getOrigin();
	}

	ql::f32 ql::sprite::get_rotation() const
	{
		return this->m_sprite.getRotation();
	}

	ql::hitbox ql::sprite::get_hitbox() const
	{
		return ql::get_sprite_hitbox(this->m_sprite);
	}

	ql::vec2 ql::sprite::get_center() const
	{
		return ql::get_sprite_center(this->m_sprite);
	}

	void ql::sprite::centerize_origin()
	{
		ql::centerize_sprite_origin(this->m_sprite);
	}

	void ql::sprite::centerize()
	{
		this->set_position(this->get_position() - this->get_dimension() / 2);
	}

	void ql::sprite::centerize_x()
	{
		auto y = this->get_position().y;
		auto x = this->get_position().x - this->get_dimension().x / 2;
		this->set_position(ql::vec(x, y));
	}

	void ql::sprite::centerize_y()
	{
		auto y = this->get_position().y - this->get_dimension().y / 2;
		auto x = this->get_position().x;
		this->set_position(ql::vec(x, y));
	}

	void ql::sprite::move(ql::vec2 delta)
	{
		this->m_sprite.move(delta);
	}

	void ql::sprite::move_scaled(ql::vec2 delta)
	{
		this->m_sprite.move(delta / this->get_scale());
	}

	void ql::sprite::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->m_sprite, states);
	}

	ql::sprite::operator sf::Sprite&()
	{
		return this->m_sprite;
	}

	ql::sprite::operator const sf::Sprite&() const
	{
		return this->m_sprite;
	}

	ql::sprite& ql::sprite::operator=(const sf::Sprite& sprite)
	{
		this->m_sprite = sprite;
		return *this;
	}
}

#endif