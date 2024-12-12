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
		ql_declare_interactive;

		qldev::circle circle;
		sf::CircleShape shape;
		ql::signal<ql::rgba> color;

		void init()
		{
			ql::println("circle_shape init!", ql::color::aqua, this);
			//ql::println("signal injected number: ", this->color.test.value);
			ql::effect(this->circle.position, this->circle.radius, [this]() { this->update_shape(); });

			ql::effect(this->color, [this]() { this->shape.setFillColor(this->color()); });
		}

		void update_shape()
		{
			ql::println("updating shape!");

			auto radius = this->circle.radius();
			auto position = this->circle.position();

			auto center = position + ql::vec(radius, radius);

			this->shape.setRadius(radius);
			this->shape.setPosition(center);
		}

		void draw(ql::render& draw) const
		{
			draw.draw(this->shape);
		}
	};

}	 // namespace qldev