#include <ql/graphic/drawable/advanced/smooth-rectangle/smooth-rectangle.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/drawable/virtual-draw-object/vdo.hpp>

namespace ql
{
	void ql::vsmooth_rectangle::move(ql::vec2 delta)
	{
		this->position.move(delta);
	}

	void ql::vsmooth_rectangle::set_dimension(ql::vec2 dimension)
	{
		this->dimension = dimension;
	}

	void ql::vsmooth_rectangle::increase(ql::vec2 delta)
	{
		this->dimension += delta * 2;
		this->position -= delta;
	}

	void ql::vsmooth_rectangle::increase(ql::f32 delta)
	{
		this->increase(ql::vec(delta, delta));
	}

	vsmooth_rectangle ql::vsmooth_rectangle::increased(ql::vec2 delta) const
	{
		auto copy = *this;
		copy.increase(delta);
		return copy;
	}

	vsmooth_rectangle ql::vsmooth_rectangle::increased(ql::f32 delta) const
	{
		auto copy = *this;
		copy.increase(delta);
		return copy;
	}

	void ql::vsmooth_rectangle::set_position(ql::vec2 position)
	{
		this->position = position;
	}

	void ql::vsmooth_rectangle::set_hitbox(ql::hitbox hitbox)
	{
		this->position = hitbox.position;
		this->dimension = hitbox.dimension;
	}

	void ql::vsmooth_rectangle::set_center(ql::vec2 position)
	{
		this->position = position - this->dimension / 2;
	}

	void ql::vsmooth_rectangle::set_slope(ql::f64 slope)
	{
		this->slope = slope;
	}

	void ql::vsmooth_rectangle::set_color(ql::rgba color)
	{
		this->color = color;
	}

	void ql::vsmooth_rectangle::set_outline_color(ql::rgba color)
	{
		this->outline_color = color;
	}

	void ql::vsmooth_rectangle::set_outline_thickness(ql::f32 thickness)
	{
		this->outline_thickness = thickness;
	}

	void ql::vsmooth_rectangle::set_slope_dimension(ql::vec2 dimension)
	{
		this->slope_dim = dimension;
	}

	void ql::vsmooth_rectangle::set_slope_point_count(ql::size point_count)
	{
		this->slope_point_count = point_count;
	}

	void ql::vsmooth_rectangle::set_round_corners(ql::bitset<4u> round_corners)
	{
		this->round_corners = round_corners;
	}

	ql::vec2 ql::vsmooth_rectangle::get_dimension() const
	{
		return this->dimension;
	}

	ql::vec2 ql::vsmooth_rectangle::get_position() const
	{
		return this->position;
	}

	ql::hitbox ql::vsmooth_rectangle::get_hitbox() const
	{
		return ql::hitbox(this->get_position(), this->get_dimension());
	}

	ql::vec2 ql::vsmooth_rectangle::get_center() const
	{
		return this->position + this->dimension / 2;
	}

	ql::f64 ql::vsmooth_rectangle::get_slope() const
	{
		return this->slope;
	}

	ql::rgba ql::vsmooth_rectangle::get_color() const
	{
		return this->color;
	}

	ql::rgba ql::vsmooth_rectangle::get_outline_color() const
	{
		return this->outline_color;
	}

	ql::f32 ql::vsmooth_rectangle::get_outline_thickness() const
	{
		return this->outline_thickness;
	}

	ql::vec2 ql::vsmooth_rectangle::get_slope_dimension() const
	{
		return this->slope_dim;
	}

	ql::size ql::vsmooth_rectangle::get_slope_point_count() const
	{
		return this->slope_point_count;
	}

	ql::bitset<4u> ql::vsmooth_rectangle::get_round_corners() const
	{
		return this->round_corners;
	}

	bool ql::vsmooth_rectangle::contains(ql::vec2 point) const
	{
		ql::detail::smooth_rectangle = *this;
		return ql::detail::smooth_rectangle.contains(point);
	}

	void ql::vsmooth_rectangle::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::smooth_rectangle = *this;
		ql::detail::smooth_rectangle.draw(window, states);
	}

	void ql::smooth_rectangle::set_position(ql::vec2 position)
	{
		this->position = position;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_dimension(ql::vec2 dimension)
	{
		this->dimension = dimension;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_hitbox(ql::hitbox hitbox)
	{
		this->position = hitbox.position;
		this->dimension = hitbox.dimension;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_center(ql::vec2 position)
	{
		this->position = position - this->dimension / 2;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_slope(ql::f64 slope)
	{
		this->slope = slope;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_color(ql::rgba color)
	{
		this->polygon.set_color(color);
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_outline_color(ql::rgba color)
	{
		this->polygon.set_outline_color(color);
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_outline_thickness(ql::f32 thickness)
	{
		this->outline_thickness = thickness;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_slope_dimension(ql::vec2 dimension)
	{
		this->slope_dim = dimension;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_slope_dimension(ql::f32 dimension)
	{
		this->set_slope_dimension(ql::vec(dimension, dimension));
	}

	void ql::smooth_rectangle::set_slope_point_count(ql::size point_count)
	{
		this->slope_point_count = point_count;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_round_corners(ql::bitset<4u> round_corners)
	{
		this->round_corners = round_corners;
	}

	ql::vec2 ql::smooth_rectangle::get_dimension() const
	{
		return this->dimension;
	}

	ql::vec2 ql::smooth_rectangle::get_position() const
	{
		return this->position;
	}

	ql::hitbox ql::smooth_rectangle::get_hitbox() const
	{
		return ql::hitbox(this->position, this->dimension);
	}

	ql::vec2 ql::smooth_rectangle::get_center() const
	{
		return this->position + this->dimension / 2;
	}

	ql::f64 ql::smooth_rectangle::get_slope() const
	{
		return this->slope;
	}

	ql::rgba ql::smooth_rectangle::get_color() const
	{
		return this->polygon.get_color();
	}

	ql::rgba ql::smooth_rectangle::get_outline_color() const
	{
		return this->polygon.get_outline_color();
	}

	ql::f32 ql::smooth_rectangle::get_outline_thickness() const
	{
		return this->outline_thickness;
	}

	ql::vec2 ql::smooth_rectangle::get_slope_dimension() const
	{
		return this->slope_dim;
	}

	ql::size ql::smooth_rectangle::get_slope_point_count() const
	{
		return this->slope_point_count;
	}

	ql::bitset<4u> ql::smooth_rectangle::get_round_corners() const
	{
		return this->round_corners;
	}

	void ql::smooth_rectangle::move(ql::vec2 delta)
	{
		this->check_create();
		this->position.move(delta);
		this->internal_check = true;
	}

	bool ql::smooth_rectangle::contains(ql::vec2 point) const
	{
		this->check_create();
		return this->polygon.collides(point);
	}

	void ql::smooth_rectangle::check_create() const
	{
		if (this->internal_check)
		{
			ql::vsmooth_rectangle rect;
			rect.set_dimension(this->dimension);
			rect.set_position(this->position);
			rect.set_slope(this->slope);
			rect.set_slope_point_count(this->slope_point_count);
			rect.set_color(this->get_color());
			rect.set_outline_color(this->get_outline_color());
			rect.set_slope_dimension(this->slope_dim);
			rect.set_outline_thickness(this->outline_thickness);
			rect.set_round_corners(this->get_round_corners());

			this->create_from(rect);
		}
	}

	void ql::smooth_rectangle::create_from(const ql::vsmooth_rectangle& smooth_rectangle) const
	{
		this->position = smooth_rectangle.get_position();
		this->dimension = smooth_rectangle.get_dimension();

		this->polygon.set_color(smooth_rectangle.color);
		this->polygon.set_outline_color(smooth_rectangle.outline_color);
		this->polygon.set_outline_thickness(smooth_rectangle.outline_thickness);
		this->polygon.shape.setFillColor(smooth_rectangle.color);
		this->polygon.shape.setOutlineColor(smooth_rectangle.outline_color);

		auto active_corners = smooth_rectangle.round_corners.number_of_set_bits();
		auto size = smooth_rectangle.slope_point_count;
		this->polygon.resize(active_corners * size + (4 - active_corners));

		auto position = smooth_rectangle.position;
		auto dimension = smooth_rectangle.slope_dim;
		auto rect_dimension = smooth_rectangle.dimension;
		auto slope_exponent = std::pow(smooth_rectangle.slope, 1.0);

		ql::u32 ctr = 0u;

		if (smooth_rectangle.round_corners[0u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::slope_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(progress, -value) * dimension;
				auto pos = position + ql::vec(0, dimension.y) + curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position;
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		if (smooth_rectangle.round_corners[1u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(1 - ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::slope_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(progress, value) * dimension;
				auto pos = position + ql::vec(rect_dimension.x, dimension.y) - curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position + rect_dimension.just_x();
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		if (smooth_rectangle.round_corners[2u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::slope_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(-progress, value) * dimension;
				auto pos = position + ql::vec(rect_dimension.x, rect_dimension.y - dimension.y) + curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position + rect_dimension;
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		if (smooth_rectangle.round_corners[3u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(1 - ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::slope_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(progress, value) * dimension;
				auto pos = position + ql::vec(0, rect_dimension.y - dimension.y) + curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position + rect_dimension.just_y();
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		this->internal_check = false;
	}

	ql::smooth_rectangle& ql::smooth_rectangle::operator=(const ql::vsmooth_rectangle& smooth_rectangle)
	{
		this->create_from(smooth_rectangle);
		return *this;
	}

	void ql::smooth_rectangle::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->check_create();
		this->polygon.draw(window, states);
	}

}	 // namespace ql

#endif