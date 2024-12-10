#pragma once

#include <ql/core/core.hpp>

#include <ql/graphic/event/event.hpp>

#include "polygon.hpp"

namespace qldev
{
	template <typename T>
	requires (ql::is_arithmetic<T>())
	struct rectangle_t
	{
		ql_declare_interactive;

		ql::signal<ql::vector2<T>> position = {};
		ql::signal<ql::vector2<T>> dimension = {};

		ql::signal<ql::f32> border_radius = 0.f;
		qldev::polygon_t<T> polygon;

		void init()
		{
			ql::effect(this->position, this->dimension, this->border_radius, [this]() { this->update_polygon(); });
		}

		void update_polygon()
		{
			if (this->border_radius() > 0)
			{

			}
			else
			{
				auto position = this->position();
				auto dimension = this->dimension();

				this->polygon.clear();
				this->polygon.push_back({position.x, position.y});
				this->polygon.push_back({position.x + dimension.x, position.y});
				this->polygon.push_back({position.x + dimension.x, position.y + dimension.y});
				this->polygon.push_back({position.x, position.y + dimension.y});
			}
		}
	};

	using rectangle = rectangle_t<ql::f32>;
}	 // namespace ql