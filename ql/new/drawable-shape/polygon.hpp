#pragma once

#include <ql/core/core.hpp>
#include <ql/graphic/render/render.hpp>
#include "../shape/polygon.hpp"

namespace qldev
{
	struct polygon_shape
	{
		sf::ConvexShape shape;
		
		template <typename T>
		void create(const qldev::polygon_t<T>& points)
		{
			this->shape.setPointCount(points.size());
			for (ql::size i = 0u; i < points.size(); i++)
			{
				this->shape.setPoint(i, {points[i].x, points[i].y});
			}
		}

		void set_color(const ql::rgba& color)
		{
			this->shape.setFillColor(color);
		}

		void draw(ql::render& render) const
		{
			render.draw(this->shape);
		}
	};
}