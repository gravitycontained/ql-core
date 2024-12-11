#pragma once

#include <ql/core/core.hpp>
#include <ql/graphic/render/render.hpp>
#include "../shape/rectangle.hpp"

#include <ql/core/advanced-type/color/oklch/oklch.hpp>
#include "polygon.hpp"

namespace qldev
{
	struct rectangle_shape
	{
		ql_declare_interactive;

		qldev::rectangle hitbox;
		qldev::polygon_shape shape;
		ql::signal<ql::oklch> color;

		void init()
		{
			ql::effect(
					this->hitbox.position, this->hitbox.dimension, this->hitbox.border_radius, [this]() { this->update_polygon(); }
			);

			ql::effect(this->color, [this]() { this->shape.set_color(this->color()); });
		}

		void update_polygon()
		{
			//ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "update polygon: ", this->hitbox.position(), " and ", this->hitbox.dimension(), " size: ", this->hitbox.polygon.size());
			this->shape.create(this->hitbox.polygon);
		}
	};

}