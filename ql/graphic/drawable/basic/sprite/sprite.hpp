#pragma once

#include <ql/core/advanced-type/advanced-type.hpp>

#if defined QL_GRAPHIC

namespace ql
{
	struct sprite
	{
		sf::Sprite m_sprite;

		sprite()
		{
		}

		sprite(const ql::sprite& sprite)
		{
			*this = sprite;
		}

		sprite(const sf::Sprite& sprite)
		{
			*this = sprite;
		}

		QL_SOURCE void set_texture(const sf::Texture& texture);
		QL_SOURCE void set_texture_rect(const sf::IntRect& rect);
		QL_SOURCE void set_texture_rect(ql::hitbox hitbox);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_position_x(ql::f32 x);
		QL_SOURCE void set_position_y(ql::f32 y);
		QL_SOURCE void set_center(ql::vec2 position);
		QL_SOURCE void set_scale(ql::vec2 scale);
		QL_SOURCE void set_scale(ql::f32 scale);
		QL_SOURCE void set_origin(ql::vec2 origin);
		QL_SOURCE void set_rotation(ql::f32 rotation);

		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_scale() const;
		QL_SOURCE ql::vec2 get_origin() const;
		QL_SOURCE ql::f32 get_rotation() const;
		QL_SOURCE ql::hitbox get_hitbox() const;
		QL_SOURCE ql::vec2 get_center() const;

		QL_SOURCE void centerize_origin();
		QL_SOURCE void centerize();
		QL_SOURCE void centerize_x();
		QL_SOURCE void centerize_y();
		QL_SOURCE void move(ql::vec2 delta);
		QL_SOURCE void move_scaled(ql::vec2 delta);

		QL_SOURCE operator sf::Sprite&();
		QL_SOURCE operator const sf::Sprite&() const;
		QL_SOURCE ql::sprite& operator=(const sf::Sprite& sprite);

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
	};

}

#endif