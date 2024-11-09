#include <ql/graphic/util/util-sprite/util-sprite.hpp>

#if defined QL_GRAPHIC

namespace ql
{

	ql::hitbox ql::get_sprite_hitbox(const sf::Sprite& sprite)
	{
		ql::hitbox rectangle;
		auto local_bounds = sprite.getLocalBounds();
		auto global_bounds = sprite.getGlobalBounds();

		rectangle.set_position({global_bounds.left, global_bounds.top});
		rectangle.set_dimension(ql::vec(local_bounds.width, local_bounds.height) * ql::vec2(sprite.getScale()));

		return rectangle;
	}

	ql::vec2 ql::get_sprite_center(const sf::Sprite& sprite)
	{
		auto hitbox = ql::get_sprite_hitbox(sprite);
		return hitbox.position + hitbox.dimension / 2;
	}

	void ql::centerize_sprite_origin(sf::Sprite& sprite)
	{
		auto local_bounds = sprite.getLocalBounds();
		auto dim = ql::vec(local_bounds.width, local_bounds.height);
		sprite.setOrigin(dim / 2);
	}

	void ql::centerize_sprite(sf::Sprite& sprite)
	{
		auto hitbox = ql::get_sprite_hitbox(sprite);
		sprite.setPosition(hitbox.position - hitbox.dimension / 2);
	}
}

#endif