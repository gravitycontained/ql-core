#include <ql/graphic/drawable/advanced/polygon/polygon.hpp>
#include <ql/core/system/print/print.hpp>

#if defined QL_GRAPHIC

namespace ql
{
	sf::Vector2f ql::polygon_shape::polygon_proxy::operator=(ql::vec2 position)
	{
		this->ptr->setPoint(this->index, position);
		return this->ptr->getPoint(this->index);
	}

	ql::polygon_shape::polygon_proxy::operator ql::vec2() const
	{
		return this->ptr->getPoint(this->index);
	}

	ql::polygon_shape::const_polygon_proxy::operator ql::vec2() const
	{
		return this->ptr->getPoint(this->index);
	}

	ql::polygon_shape::polygon_proxy ql::polygon_shape::operator[](ql::size index)
	{
		ql::polygon_shape::polygon_proxy result;
		result.ptr = &this->shape;
		result.index = index;
		return result;
	}

	ql::polygon_shape::const_polygon_proxy ql::polygon_shape::operator[](ql::size index) const
	{
		ql::polygon_shape::const_polygon_proxy result;
		result.ptr = &this->shape;
		result.index = index;
		return result;
	}

	ql::polygon_shape::polygon_proxy ql::polygon_shape::front()
	{
		ql::polygon_shape::polygon_proxy result;
		result.ptr = &this->shape;
		result.index = 0u;
		return result;
	}

	ql::polygon_shape::const_polygon_proxy ql::polygon_shape::front() const
	{
		ql::polygon_shape::const_polygon_proxy result;
		result.ptr = &this->shape;
		result.index = 0u;
		return result;
	}

	ql::polygon_shape::polygon_proxy ql::polygon_shape::back()
	{
		ql::polygon_shape::polygon_proxy result;
		result.ptr = &this->shape;
		result.index = this->size() - 1;
		return result;
	}

	ql::polygon_shape::const_polygon_proxy ql::polygon_shape::back() const
	{
		ql::polygon_shape::const_polygon_proxy result;
		result.ptr = &this->shape;
		result.index = 0u;
		return result;
	}

	void ql::polygon_shape::set_outline_thickness(ql::f32 thickness)
	{
		this->shape.setOutlineThickness(thickness);
	}

	void ql::polygon_shape::set_outline_color(ql::rgba color)
	{
		this->shape.setOutlineColor(color);
	}

	void ql::polygon_shape::set_color(ql::rgba color)
	{
		this->shape.setFillColor(color);
	}

	void ql::polygon_shape::set_position(ql::vec2 position)
	{
		this->shape.setPosition(position);
	}

	ql::f32 ql::polygon_shape::get_outline_thickness() const
	{
		return this->shape.getOutlineThickness();
	}

	ql::rgba ql::polygon_shape::get_outline_color() const
	{
		return this->shape.getOutlineColor();
	}

	ql::rgba ql::polygon_shape::get_color() const
	{
		return this->shape.getFillColor();
	}

	void ql::polygon_shape::move(ql::vec2 delta)
	{
		this->shape.move(delta);
	}

	void ql::polygon_shape::set_point(ql::size index, ql::vec2 position)
	{
		this->shape.setPoint(index, position);
	}

	ql::vec2 ql::polygon_shape::get_point(ql::size index) const
	{
		return this->shape.getPoint(index);
	}

	ql::size ql::polygon_shape::size() const
	{
		return this->shape.getPointCount();
	}

	void ql::polygon_shape::resize(ql::size size)
	{
		this->shape.setPointCount(size);
	}

	void ql::polygon_shape::add(ql::vec2 point)
	{
		auto current_size = this->size();
		this->resize(current_size + 1);
		this->set_point(current_size, point);
	}

	bool ql::polygon_shape::collides(ql::vec2 point) const
	{
		double total_angle = 0.0;

		auto j = this->size() - 1;
		for (ql::size i = 0; i < this->size(); ++i)
		{
			ql::vec2 p1 = this->get_point(j);
			ql::vec2 p2 = this->get_point(i);

			// calculate the vectors from the test point to the vertices
			ql::vec2 v1 = { p1.x - point.x, p1.y - point.y };
			ql::vec2 v2 = { p2.x - point.x, p2.y - point.y };

			// calculate the angle between the two vectors
			double angle = atan2(v2.y, v2.x) - atan2(v1.y, v1.x);

			// ensure the angle is in the range [-PI, PI] to handle wrapping
			if (angle > ql::pi) angle -= 2 * ql::pi;
			if (angle < -ql::pi) angle += 2 * ql::pi;

			total_angle += angle;
			j = i;
		}

		// if the total angle is close to 2*PI (or -2*PI, etc.), the point is inside.
		// a zero total angle means the point is outside.
		return std::abs(total_angle) > ql::pi;
	}

	bool ql::polygon_shape::collides(const ql::straight_line& line) const
	{
		auto n = this->size();
		if (n < 3)
			return false; // not a valid polygon

		// STEP 1: check if the line segment intersects any edge of the polygon.
		auto j = n - 1;
		for (ql::size i = 0; i < n; ++i)
		{
			ql::straight_line edge = { this->get_point(j), this->get_point(i) };

			// Assuming line.collides(edge) correctly checks for segment-segment intersection.
			if (line.collides(edge))
				return true;

			j = i;
		}

		// STEP 2: if no edges intersect, check if the line is fully inside.
		if (this->collides(line.a))
			return true;

		// if no edges intersect and the start point is not inside, there is no collision.
		return false;
	}

	void ql::polygon_shape::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->shape, states);
	}

}	 // namespace ql

#endif