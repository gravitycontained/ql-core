#pragma once

#include <ql/core/core.hpp>

#if defined QL_GRAPHIC

#include <SFML/Graphics.hpp>

namespace ql
{
	QL_SOURCE ql::hitbox get_sprite_hitbox(const sf::Sprite& sprite);
	QL_SOURCE ql::vec2 get_sprite_center(const sf::Sprite& sprite);

	QL_SOURCE void centerize_sprite_origin(sf::Sprite& sprite);
	QL_SOURCE void centerize_sprite(sf::Sprite& sprite);
}

#endif