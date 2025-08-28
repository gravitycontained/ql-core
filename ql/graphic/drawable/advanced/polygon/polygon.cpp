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
	std::optional<ql::vec2> ql::polygon_shape::collides_get_normal(const ql::straight_line& line) const
	{
		auto n = this->size();
		if (n < 3)
			return std::nullopt; // Not a valid polygon

		ql::f32 min_t = std::numeric_limits<ql::f32>::max();
		std::optional<ql::vec2> hit_normal = std::nullopt;

		auto j = n - 1;
		for (ql::size i = 0; i < n; ++i)
		{
			ql::vec2 p1 = this->get_point(j);
			ql::vec2 p2 = this->get_point(i);
			ql::straight_line edge = { p1, p2 };

			// We need a more advanced segment-segment intersection function here
			// that returns the intersection parameter 't' for the 'line' segment
			// and potentially 'u' for the 'edge' segment, and the intersection point.
			// Let's assume you have a `line.get_intersection_t(edge)` method
			// that returns std::optional<ql::f32> representing the 't' value for 'line'.
			// 't' indicates how far along 'line' the intersection occurs (0 to 1).

			// Placeholder for actual intersection logic. You'll need to implement or
			// ensure `straight_line::get_intersection_t` exists and works as described.
			// This method should return `std::nullopt` if no intersection or if it's outside
			// both segments.
			std::optional<ql::f32> current_t_opt = line.get_intersection(edge);

			if (current_t_opt)
			{
				ql::f32 current_t = *current_t_opt;

				// Check if this intersection is closer to the start of 'line'
				// and is a valid intersection along the line segment (0 <= t <= 1)
				if (current_t >= 0.0f && current_t <= 1.0f && current_t < min_t)
				{
					min_t = current_t;

					// Calculate the edge vector
					ql::vec2 edge_vec = { edge.b.x - edge.a.x, edge.b.y - edge.a.y };

					// Calculate the normal. For a 2D line (x1, y1) to (x2, y2),
					// a perpendicular vector (normal) can be (-dy, dx) or (dy, -dx).
					// To ensure it points outwards for a polygon, we need consistency.
					// For a counter-clockwise winding, (-dy, dx) often points outwards.
					ql::vec2 normal = { -edge_vec.y, edge_vec.x };

					// Normalize the normal vector
					ql::f32 length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
					if (length > 0)
					{
						normal.x /= length;
						normal.y /= length;
					}

					// We need to ensure the normal points *outwards* from the polygon.
					// One way to do this is to check the dot product with a vector
					// from the intersection point to the polygon's centroid or another internal point.
					// Alternatively, if the polygon points are consistently ordered (e.g., CCW),
					// a simple perpendicular will often be consistently inwards or outwards.

					// For now, let's assume the standard (-dy, dx) gives an outward normal for CCW polygons.
					// If your polygon vertices are ordered clockwise, you might need (dy, -dx).
					// A more robust approach might involve checking the orientation of the polygon
					// or checking the normal's direction relative to the polygon's interior.

					// A simple heuristic for outward normal (assuming CCW vertices):
					// Take a point slightly inwards from the edge (e.g., midpoint of the edge + a tiny step inwards)
					// and check its position relative to the normal.
					// For robust collision response, the normal should point from the polygon towards the line.

					hit_normal = normal;
				}
			}
			j = i;
		}

		// If no edge intersection, check if the line starts inside the polygon.
		// If it starts inside, then it might be "colliding" with the *interior*
		// of the polygon. In this case, there isn't a specific "normal" of an edge
		// that was hit. Depending on your game logic, you might return `std::nullopt`
		// or a special "interior normal" if needed (e.g., based on the closest edge).
		// For the purpose of `collides_get_normal` (edge-specific normal),
		// if no edge was hit by the line segment, `std::nullopt` is appropriate.
		// However, if your `collides` method considers the line starting inside as a collision,
		// you might need to reconsider what `collides_get_normal` means in that context.

		// For typical line-segment-polygon collision, `std::nullopt` if no edge hit is correct.
		// If `min_t` is still `max_t`, it means no intersection was found.
		if (min_t == std::numeric_limits<ql::f32>::max())
		{
			return std::nullopt;
		}

		return hit_normal;
	}

	void ql::polygon_shape::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->shape, states);
	}

}	 // namespace ql

#endif