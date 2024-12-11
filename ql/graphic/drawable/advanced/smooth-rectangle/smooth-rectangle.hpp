#pragma once

#include <ql/core/advanced-type/advanced-type.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/drawable/advanced/polygon/polygon.hpp>

namespace ql
{

	struct smooth_rectangle;

	struct vsmooth_rectangle
	{
		vsmooth_rectangle()
		{
			this->round_corners.fill(true);
		}

		QL_SOURCE void move(ql::vec2 delta);

		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void increase(ql::vec2 delta);
		QL_SOURCE void increase(ql::f32 delta);
		QL_SOURCE vsmooth_rectangle increased(ql::vec2 delta) const;
		QL_SOURCE vsmooth_rectangle increased(ql::f32 delta) const;

		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_hitbox(ql::hitbox hitbox);
		QL_SOURCE void set_center(ql::vec2 position);
		QL_SOURCE void set_slope(ql::f64 slope);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_outline_thickness(ql::f32 thickness);
		QL_SOURCE void set_outline_color(ql::rgba color);
		QL_SOURCE void set_slope_dimension(ql::vec2 dimension);
		QL_SOURCE void set_slope_point_count(ql::size point_count);
		QL_SOURCE void set_round_corners(ql::bitset<4u> round_corners);
		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::hitbox get_hitbox() const;
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE ql::f64 get_slope() const;
		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE ql::f32 get_outline_thickness() const;
		QL_SOURCE ql::rgba get_outline_color() const;
		QL_SOURCE ql::vec2 get_slope_dimension() const;
		QL_SOURCE ql::size get_slope_point_count() const;
		QL_SOURCE ql::bitset<4u> get_round_corners() const;
		QL_SOURCE bool contains(ql::vec2 point) const;
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		friend smooth_rectangle;

		ql::vec2 dimension;
		ql::vec2 position;
		ql::f64 slope = 2.0;
		ql::size slope_point_count = 20u;
		ql::rgba color;
		ql::rgba outline_color;
		ql::vec2 slope_dim = {10, 10};
		ql::f32 outline_thickness = 0.0f;
		ql::bitset<4u> round_corners;
	};

	struct smooth_rectangle
	{
		mutable ql::polygon_shape polygon;

		smooth_rectangle()
		{
			this->round_corners.fill(true);
		}

		smooth_rectangle(const ql::smooth_rectangle& smooth_rectangle)
		{
			*this = smooth_rectangle;
		}

		smooth_rectangle(const ql::vsmooth_rectangle& other)
		{
			*this = other;
		}

		ql::smooth_rectangle& operator=(const ql::smooth_rectangle& other)
		{
			this->dimension = other.dimension;
			this->position = other.position;
			this->slope = other.slope;
			this->slope_point_count = other.slope_point_count;
			this->slope_dim = other.slope_dim;
			this->outline_thickness = other.outline_thickness;
			this->round_corners = other.round_corners;
			this->internal_check = other.internal_check;
			this->set_color(other.get_color());
			this->set_outline_color(other.get_outline_color());
			return *this;
		}

		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_hitbox(ql::hitbox hitbox);
		QL_SOURCE void set_center(ql::vec2 position);
		QL_SOURCE void set_slope(ql::f64 slope);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_outline_thickness(ql::f32 thickness);
		QL_SOURCE void set_outline_color(ql::rgba color);
		QL_SOURCE void set_slope_dimension(ql::vec2 dimension);
		QL_SOURCE void set_slope_dimension(ql::f32 dimension);
		QL_SOURCE void set_slope_point_count(ql::size point_count);
		QL_SOURCE void set_round_corners(ql::bitset<4u> round_corners);
		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::hitbox get_hitbox() const;
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE ql::f64 get_slope() const;
		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE ql::f32 get_outline_thickness() const;
		QL_SOURCE ql::rgba get_outline_color() const;
		QL_SOURCE ql::vec2 get_slope_dimension() const;
		QL_SOURCE ql::size get_slope_point_count() const;
		QL_SOURCE ql::bitset<4u> get_round_corners() const;

		QL_SOURCE void check_create() const;
		QL_SOURCE void move(ql::vec2 delta);
		QL_SOURCE bool contains(ql::vec2 point) const;
		QL_SOURCE void create_from(const ql::vsmooth_rectangle& smooth_rectangle) const;
		QL_SOURCE ql::smooth_rectangle& operator=(const ql::vsmooth_rectangle& smooth_rectangle);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		mutable ql::vec2 dimension;
		mutable ql::vec2 position;
		ql::f64 slope = 2.0;
		ql::size slope_point_count = 20u;
		ql::vec2 slope_dim = {10, 10};
		ql::f32 outline_thickness = 0.0f;
		ql::bitset<4u> round_corners;
		mutable bool internal_check = false;
	};

}	 // namespace ql

#endif