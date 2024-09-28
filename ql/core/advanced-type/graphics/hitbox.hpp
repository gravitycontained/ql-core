#pragma once

#include <ql/core/advanced-type/fundamental/vector.hpp>
#include <ql/core/advanced-type/graphics/straight-line.hpp>

namespace ql
{
	
	enum class box_side
	{
		top_left = 0,
		top_center = 1,
		top_right = 2,
		right_top = 2,
		right_center = 3,
		right_bottom = 4,
		bottom_right = 4,
		bottom_center = 5,
		bottom_left = 6,
		left_bottom = 6,
		left_center = 7,
		left_top = 0,
		size = 8
	};

	template <typename T>
	struct hitbox_t
	{
		ql::vector2<T> dimension;
		ql::vector2<T> position;

		constexpr hitbox_t()
		{
			this->position = this->dimension = ql::vector2<T>(0, 0);
		}

		constexpr hitbox_t(ql::vector2<T> position, ql::vector2<T> dimension)
		{
			this->position = position;
			this->dimension = dimension;
		}

		constexpr void set_width(T width)
		{
			this->dimension.x = width;
		}

		constexpr void set_height(T height)
		{
			this->dimension.y = height;
		}

		constexpr void set_dimension(ql::vector2<T> dimension)
		{
			this->dimension = dimension;
		}

		constexpr void set_position(ql::vector2<T> position)
		{
			this->position = position;
		}

		constexpr void set_center(ql::vector2<T> position)
		{
			this->position = position - this->dimension / 2;
		}

		constexpr ql::vector2<T> get_center() const
		{
			return this->position + this->dimension / 2;
		}

		constexpr ql::vector2<T> get_dimension() const
		{
			return this->dimension;
		}

		constexpr ql::vector2<T> get_position() const
		{
			return this->position;
		}

		constexpr T get_width() const
		{
			return this->dimension.x;
		}

		constexpr T get_height() const
		{
			return this->dimension.y;
		}

		constexpr std::string to_string() const
		{
			return ql::to_string(std::array{this->position, this->dimension});
		}

		constexpr void increase(T delta)
		{
			this->position -= ql::vector2<T>(delta, delta);
			this->dimension += ql::vector2<T>(delta, delta) * 2;
		}

		constexpr void increase(ql::vector2<T> delta)
		{
			this->position -= delta;
			this->dimension += delta * 2;
		}

		constexpr void increase_x(T delta)
		{
			this->position.x -= delta;
			this->dimension.x += delta * 2;
		}

		constexpr void increase_y(T delta)
		{
			this->position.y -= delta;
			this->dimension.y += delta * 2;
		}

		constexpr ql::hitbox_t<T> increased(T delta) const
		{
			auto copy = *this;
			copy.increase(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> increased(ql::vector2<T> delta) const
		{
			auto copy = *this;
			copy.increase(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> increased_y(T delta) const
		{
			auto copy = *this;
			copy.increase_y(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> increased_x(T delta) const
		{
			auto copy = *this;
			copy.increase_x(delta);
			return copy;
		}

		constexpr void decrease(T delta)
		{
			this->position += ql::vector2<T>(delta, delta);
			this->dimension -= ql::vector2<T>(delta, delta) * 2;
		}

		constexpr void decrease(ql::vector2<T> delta)
		{
			this->position += delta;
			this->dimension -= delta * 2;
		}

		constexpr void decrease_x(T delta)
		{
			this->position.x += delta;
			this->dimension.x -= delta * 2;
		}

		constexpr void decrease_y(T delta)
		{
			this->position.y += delta;
			this->dimension.y -= delta * 2;
		}

		constexpr ql::hitbox_t<T> decreased(T delta) const
		{
			auto copy = *this;
			copy.decrease(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> decreased(ql::vector2<T> delta) const
		{
			auto copy = *this;
			copy.decrease(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> decreased_y(T delta) const
		{
			auto copy = *this;
			copy.decrease_y(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> decreased_x(T delta) const
		{
			auto copy = *this;
			copy.decrease_x(delta);
			return copy;
		}

		constexpr bool contains(ql::vector2f position) const
		{
			return (position.x > this->position.x && position.x < (this->position.x + this->dimension.x) &&
							position.y > this->position.y && position.y < (this->position.y + this->dimension.y));
		}

		template <typename U>
		constexpr bool collides(ql::straight_line_t<U> line) const
		{
			auto x1 = this->get_position().x;
			auto x2 = this->get_position().x + this->get_dimension().x;
			auto y1 = this->get_position().y;
			auto y2 = this->get_position().y + this->get_dimension().y;

			return this->collides(x1, x2, y1, y2, line);
		}

		template <typename U>
		constexpr bool collides(ql::straight_line_t<U> line, T increase) const
		{
			auto x1 = this->get_position().x - increase;
			auto x2 = this->get_position().x + this->get_dimension().x + increase;
			auto y1 = this->get_position().y - increase;
			auto y2 = this->get_position().y + this->get_dimension().y + increase;

			return this->collides(x1, x2, y1, y2, line);
		}

		template <typename U>
		constexpr bool collides(const ql::hitbox_t<U>& hitbox) const
		{
			auto a1 = this->position;
			auto a2 = this->position + this->dimension;
			auto b1 = hitbox.position;
			auto b2 = hitbox.position + hitbox.dimension;

			auto x1_inside = a1.x >= b1.x && a1.x <= b2.x;
			auto x2_inside = a2.x >= b1.x && a2.x <= b2.x;
			auto y1_inside = a1.y >= b1.y && a1.y <= b2.y;
			auto y2_inside = a2.y >= b1.y && a2.y <= b2.y;

			auto either_x_inside = x1_inside || x2_inside;
			auto either_y_inside = y1_inside || y2_inside;

			if (either_x_inside && either_y_inside)
				return true;

			auto ax_outside = a1.x < b1.x && a2.x > b2.x;
			auto ay_outside = a1.y < b1.y && a2.y > b2.y;

			if (ax_outside && ay_outside)
				return true;

			auto bx_inside = b1.x < a1.x && b2.x > a2.x;
			auto by_inside = b1.y < a1.y && b2.y > a2.y;

			if (bx_inside && by_inside)
				return true;

			if (ax_outside && either_y_inside)
				return true;
			if (ay_outside && either_x_inside)
				return true;

			return false;
		}

		template <typename U>
		constexpr bool corners_collide_with(const ql::hitbox_t<U>& hitbox) const
		{
			auto p1 = this->position;
			auto p2 = this->position + this->dimension.just_x();
			auto p3 = this->position + this->dimension.just_y();
			auto p4 = this->position + this->dimension;
			return hitbox.contains(p1) || hitbox.contains(p2) || hitbox.contains(p3) || hitbox.contains(p4);
		}

		template <typename U>
		constexpr void move(ql::vector2<U> delta)
		{
			this->position += ql::vector2<T>(delta);
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr void move(U x, U y)
		{
			this->position += ql::vector2<T>(x, y);
		}

		template <typename U>
		constexpr void extend_left(U delta)
		{
			this->position -= ql::vector2<T>(delta, T{0});
			this->dimension += ql::vector2<T>(delta, T{0});
		}

		template <typename U>
		constexpr ql::hitbox_t<T> extended_left(U delta) const
		{
			auto copy = *this;
			copy.extend_left(delta);
			return copy;
		}

		template <typename U>
		constexpr void extend_right(U delta)
		{
			this->dimension += ql::vector2<T>(delta, T{0});
		}

		template <typename U>
		constexpr ql::hitbox_t<T> extended_right(U delta) const
		{
			auto copy = *this;
			copy.extend_right(delta);
			return copy;
		}

		template <typename U>
		constexpr void extend_up(U delta)
		{
			this->position -= ql::vector2<T>(T{0}, delta);
			this->dimension += ql::vector2<T>(T{0}, delta);
		}

		template <typename U>
		constexpr ql::hitbox_t<T> extended_up(U delta) const
		{
			auto copy = *this;
			copy.extend_up(delta);
			return copy;
		}

		template <typename U>
		constexpr void extend_down(U delta)
		{
			this->dimension += ql::vector2<T>(T{0}, delta);
		}

		template <typename U>
		constexpr ql::hitbox_t<T> extended_down(U delta) const
		{
			auto copy = *this;
			copy.extend_down(delta);
			return copy;
		}

		constexpr ql::vector2<T> get_top_left() const
		{
			return this->get_side(ql::box_side::top_left);
		}

		constexpr ql::vector2<T> get_top_center() const
		{
			return this->get_side(ql::box_side::top_center);
		}

		constexpr ql::vector2<T> get_top_right() const
		{
			return this->get_side(ql::box_side::top_right);
		}

		constexpr ql::vector2<T> get_right_top() const
		{
			return this->get_side(ql::box_side::right_top);
		}

		constexpr ql::vector2<T> get_right_center() const
		{
			return this->get_side(ql::box_side::right_center);
		}

		constexpr ql::vector2<T> get_right_bottom() const
		{
			return this->get_side(ql::box_side::right_bottom);
		}

		constexpr ql::vector2<T> get_bottom_left() const
		{
			return this->get_side(ql::box_side::bottom_left);
		}

		constexpr ql::vector2<T> get_bottom_center() const
		{
			return this->get_side(ql::box_side::bottom_center);
		}

		constexpr ql::vector2<T> get_bottom_right() const
		{
			return this->get_side(ql::box_side::bottom_right);
		}

		constexpr ql::vector2<T> get_left_top() const
		{
			return this->get_side(ql::box_side::left_top);
		}

		constexpr ql::vector2<T> get_left_center() const
		{
			return this->get_side(ql::box_side::left_center);
		}

		constexpr ql::vector2<T> get_left_bottom() const
		{
			return this->get_side(ql::box_side::left_bottom);
		}

		constexpr void set_top_left(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::top_left, position);
		}

		constexpr void set_top_center(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::top_center, position);
		}

		constexpr void set_top_right(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::top_right, position);
		}

		constexpr void set_right_top(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::right_top, position);
		}

		constexpr void set_right_center(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::right_center, position);
		}

		constexpr void set_right_bottom(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::right_bottom, position);
		}

		constexpr void set_bottom_left(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::bottom_left, position);
		}

		constexpr void set_bottom_center(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::bottom_center, position);
		}

		constexpr void set_bottom_right(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::bottom_right, position);
		}

		constexpr void set_left_top(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::left_top, position);
		}

		constexpr void set_left_center(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::left_center, position);
		}

		constexpr void set_left_bottom(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::left_bottom, position);
		}

		// 4 side corners
		constexpr ql::vector2<T> get_side_corner_left(ql::size side) const
		{
			switch (side)
			{
				case 0u: return this->get_side(ql::box_side::top_left);
				case 1u: return this->get_side(ql::box_side::right_top);
				case 2u: return this->get_side(ql::box_side::bottom_left);
				case 3u: return this->get_side(ql::box_side::left_top);
			}
			return {};
		}

		// 4 side corners
		constexpr void set_side_corner_left(ql::size side, ql::vector2<T> position)
		{
			switch (side)
			{
				case 0u: this->set_side(ql::box_side::top_left, position); break;
				case 1u: this->set_side(ql::box_side::right_top, position); break;
				case 2u: this->set_side(ql::box_side::bottom_left, position); break;
				case 3u: this->set_side(ql::box_side::left_top, position); break;
			}
		}

		// 4 side corners
		constexpr void set_side_corner(ql::size side, ql::vector2<T> position)
		{
			this->set_side(side * 2, position);
		}

		// 4 side corners
		constexpr ql::vector2<T> get_side_corner(ql::size side) const
		{
			return this->get_side(side * 2);
		}

		// 4 side centers
		constexpr void set_side_center(ql::size side, ql::vector2<T> position)
		{
			this->set_side_center(side * 2 + 1, position);
		}

		// 8 sides
		constexpr ql::vector2<T> get_side(ql::size side) const
		{
			return this->position + ql::vec_box8.at(side) * this->dimension;
		}

		// 8 sides
		constexpr void set_side(ql::size side, ql::vector2<T> position)
		{
			this->set_position(position - ql::vec_box8.at(side) * this->dimension);
		}

		constexpr ql::vector2<T> get_side(ql::box_side side) const
		{
			return this->get_side(ql::size_cast(side));
		}

		constexpr void set_side(ql::box_side side, ql::vector2<T> position)
		{
			this->set_side(ql::size_cast(side), position);
		}

		template <typename U>
		bool collides(T x1, T x2, T y1, T y2, ql::straight_line_t<U> line) const
		{
			auto x_a_inside = (line.a.x > x1) && (line.a.x < x2);
			auto y_a_inside = (line.a.y > y1) && (line.a.y < y2);
			if (x_a_inside && y_a_inside)
				return true;

			auto x_b_inside = (line.b.x > x1) && (line.b.x < x2);
			auto y_b_inside = (line.b.y > y1) && (line.b.y < y2);
			if (x_b_inside && y_b_inside)
				return true;

			auto x_cross = ((line.a.x < x1) && (line.b.x > x2)) || ((line.b.x < x1) && (line.a.x > x2));
			if (x_cross && (y_a_inside && y_b_inside))
				return true;

			auto y_cross = ((line.a.y < y1) && (line.b.y > y2)) || ((line.b.y < y1) && (line.a.y > y2));
			if (y_cross && (x_a_inside && x_b_inside))
				return true;

			if (line.a.x < x1 && line.b.x < x1)
				return false;
			if (line.a.x > x2 && line.b.x > x2)
				return false;
			if (line.a.y < y1 && line.b.y < y1)
				return false;
			if (line.a.y > y2 && line.b.y > y2)
				return false;

			auto c1 = ql::vec(x1, y1);
			auto c2 = ql::vec(x2, y1);
			auto c3 = ql::vec(x1, y2);
			auto c4 = ql::vec(x2, y2);

			ql::straight_line line1(line.a, {});
			ql::straight_line line2(line.a, {});
			bool found = false;

			if (line.a.x < c1.x && line.a.y < c1.y)
			{	 // a_outside_c1
				line1.b = c3;
				line2.b = c2;
				found = true;
			}
			else if (line.a.x > c2.x && line.a.y < c2.y)
			{	 // a_outside_c2
				line1.b = c1;
				line2.b = c4;
				found = true;
			}
			else if (line.a.x < c3.x && line.a.y > c3.y)
			{	 // a_outside_c3
				line1.b = c4;
				line2.b = c1;
				found = true;
			}
			else if (line.a.x > c4.x && line.a.y > c4.y)
			{	 // a_outside_c3
				line1.b = c2;
				line2.b = c3;
				found = true;
			}
			else if (line.a.x < c1.x)
			{	 // a_left
				line1.b = c3;
				line2.b = c1;
				found = true;
			}
			else if (line.a.y < c1.y)
			{	 // a_top
				line1.b = c1;
				line2.b = c2;
				found = true;
			}
			else if (line.a.x > c2.x)
			{	 // a_right
				line1.b = c2;
				line2.b = c4;
				found = true;
			}
			else if (line.a.y > c2.y)
			{	 // a_bottom
				line1.b = c4;
				line2.b = c3;
				found = true;
			}

			if (!found)
			{
				return false;
			}
			auto line_angle = line.angle();

			auto angle1 = line1.angle();
			auto angle2 = line2.angle();

			if (angle2 < angle1)
			{
				if (line_angle < ql::pi_32)
				{
					angle1 -= ql::pi_32 * 2;
				}
				else
				{
					angle2 += ql::pi_32 * 2;
				}
			}

			return (line_angle >= angle1 && line_angle <= angle2);
		}
	};

	using hitbox = hitbox_t<ql::f32>;
}