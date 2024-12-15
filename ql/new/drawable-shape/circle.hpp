#pragma once

#include <ql/core/core.hpp>
#include <ql/graphic/render/render.hpp>
#include "../shape/circle.hpp"

#include <ql/core/advanced-type/color/oklch/oklch.hpp>
#include "polygon.hpp"

namespace qldev
{
	struct circle_shape
	{
		ql_sync;

		qldev::circle circle;
		sf::CircleShape shape;
		ql::signal<ql::rgba> color;

		void init()
		{
			ql::println(
					ql::color::bright_red, "game", ql::color::bright_gray, " :: ", ql::string_left_spaced("circle shape init ", 24), ql::color::aqua, this
			);
			//ql::println("signal injected number: ", this->color.test.value);
			ql::effect(this->circle.position, this->circle.radius, [this]() { this->update_shape(); });

			ql::effect(this->color, [this]() { this->shape.setFillColor(this->color()); });
		}

		void update_shape()
		{
			ql::println(ql::color::bright_red, "game", ql::color::bright_gray, " :: ", ql::string_left_spaced("effect updating shape ", 24));

			auto radius = this->circle.radius();
			auto position = this->circle.position();

			auto center = position + ql::vec(radius, radius);

			this->shape.setRadius(radius);
			this->shape.setPosition(center);
		}

		void draw(ql::render& render) const
		{
			render.draw(this->shape);
		}
	};

}	 // namespace qldev