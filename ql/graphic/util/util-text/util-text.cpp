#include <ql/graphic/util/util-text/util-text.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/drawable/basic/text/text.hpp>

namespace ql
{
	ql::hitbox ql::get_text_hitbox(const sf::Text& text, bool ignore_outline)
	{
		ql::hitbox rectangle;
		auto local_bounds = text.getLocalBounds();
		auto global_bounds = text.getGlobalBounds();

		rectangle.set_position({global_bounds.left, global_bounds.top});
		rectangle.set_dimension({local_bounds.width, local_bounds.height});

		if (ignore_outline)
		{
			rectangle.position -= text.getOutlineThickness();
			rectangle.dimension -= text.getOutlineThickness() * 2;
		}
		return rectangle;
	}

	ql::hitbox ql::get_text_hitbox(const ql::text& text, bool ignore_outline)
	{
		return text.get_visible_hitbox();
	}

	void ql::centerize_text(sf::Text& text)
	{
		auto rect = ql::get_text_hitbox(text).dimension;
		text.move(-rect / 2);
	}

	void ql::centerize_text(ql::text& text)
	{
		text.centerize();
	}

}

#endif