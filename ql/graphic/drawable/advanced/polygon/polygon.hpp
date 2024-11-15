#pragma once

#include <ql/core/core.hpp>

#if defined QL_GRAPHIC

namespace ql
{
	struct polygon
	{
		struct polygon_proxy
		{
			sf::ConvexShape* ptr;
			ql::size index;

			QL_SOURCE sf::Vector2f operator=(ql::vec2 position);
			QL_SOURCE operator ql::vec2() const;
		};

		struct const_polygon_proxy
		{
			const sf::ConvexShape* ptr;
			ql::size index;

			QL_SOURCE operator ql::vec2() const;
		};

		sf::ConvexShape shape;

		QL_SOURCE polygon_proxy operator[](ql::size index);
		QL_SOURCE const_polygon_proxy operator[](ql::size index) const;
		QL_SOURCE polygon_proxy front();
		QL_SOURCE const_polygon_proxy front() const;
		QL_SOURCE polygon_proxy back();
		QL_SOURCE const_polygon_proxy back() const;
		QL_SOURCE ql::size size() const;

		QL_SOURCE void set_outline_thickness(ql::f32 thickness);
		QL_SOURCE void set_outline_color(ql::rgba color);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_position(ql::vec2 position);

		QL_SOURCE ql::f32 get_outline_thickness() const;
		QL_SOURCE ql::rgba get_outline_color() const;
		QL_SOURCE ql::rgba get_color() const;

		QL_SOURCE void move(ql::vec2 delta);
		QL_SOURCE void set_point(ql::size index, ql::vec2 position);
		QL_SOURCE ql::vec2 get_point(ql::size index) const;
		QL_SOURCE void resize(ql::size size);
		QL_SOURCE void add(ql::vec2 point);

		QL_SOURCE bool contains(ql::vec2 point, ql::size increment = 1u) const;

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
	};

}	 // namespace ql

#endif