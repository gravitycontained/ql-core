#pragma once

#include <ql/core/core.hpp>

#if defined QL_GRAPHIC

#include <SFML/Graphics.hpp>

namespace ql
{
	struct text;

	QL_SOURCE ql::hitbox get_text_hitbox(const sf::Text& text, bool ignore_outline = true);
	QL_SOURCE ql::hitbox get_text_hitbox(const ql::text& text, bool ignore_outline = true);
	QL_SOURCE void centerize_text(sf::Text& text);
	QL_SOURCE void centerize_text(ql::text& text);
}

#endif