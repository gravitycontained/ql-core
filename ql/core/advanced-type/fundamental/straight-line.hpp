#pragma once

#include <ql/core/type/type.hpp>
#include <ql/core/advanced-type/fundamental/vector.hpp>

#include <optional>

namespace ql
{
	template <typename T>
	struct straight_line_t
	{
		ql::vector2<T> a;
		ql::vector2<T> b;

		using float_type = ql::conditional<ql::if_true<ql::is_same<T, ql::f32>()>, ql::f32, ql::default_type, ql::f64>;

		constexpr straight_line_t() : a(), b()
		{
		}

		constexpr straight_line_t(ql::vector2<T> a, ql::vector2<T> b) : a(a), b(b)
		{
		}

		std::string to_string() const
		{
			return ql::to_string(std::array{this->a, this->b});
		}

		float_type length() const
		{
			auto diff = this->b - this->a;
			return static_cast<float_type>(std::sqrt(diff.x * diff.x + diff.y * diff.y));
		}

		ql::vector2<float_type> normal() const
		{
			return ql::vector2<float_type>{this->a.y - this->b.y, this->b.x - this->a.x} / this->length();
		}

		float_type angle() const
		{
			auto atan = std::atan2(this->a.y - this->b.y, this->b.x - this->a.x);
			if (atan < 0)
				atan = static_cast<decltype(atan)>(2 * ql::pi + atan);
			return static_cast<float_type>(atan);
		}

		void set_rotation_a(ql::f64 angle)
		{
			auto x = std::cos(angle);
			auto y = std::sin(angle);
			this->a = this->b + ql::vec(x, y) * this->length();
		}

		void set_rotation_b(ql::f64 angle)
		{
			auto x = std::cos(angle);
			auto y = std::sin(angle);
			this->b = this->a + ql::vec(x, y) * this->length();
		}

		constexpr std::optional<ql::f32> get_intersection(straight_line_t other) const
		{
			// Line 1 (this): P + t * R
			// P = this->a
			// R = this->b - this->a

			// Line 2 (other): Q + u * S
			// Q = other.a
			// S = other.b - other.a

			auto p = this->a;
			auto r = this->b - this->a;

			auto q = other.a;
			auto s = other.b - other.a;

			auto r_cross_s = ql::vec2::cross_product(r, s);
			auto q_minus_p_cross_r = ql::vec2::cross_product(q - p, r);
			auto q_minus_p_cross_s = ql::vec2::cross_product(q - p, s);

			// If r x s == 0, lines are parallel or collinear
			if (std::abs(r_cross_s) < 1e-6) // Use a small epsilon for float comparison
			{
				// If (q - p) x r == 0, lines are collinear.
				if (std::abs(q_minus_p_cross_r) < 1e-6)
				{
					// Lines are collinear. Check for overlap.
					// This is the "overlap" case handled by your `collides` method,
					// but for `get_intersection` returning a single `t`, it's ambiguous.
					// A common approach is to return nullopt for collinear overlapping segments
					// unless a specific convention is defined (e.g., return t for first point of overlap).
					// For simplicity, we'll just return nullopt if parallel or collinear for get_intersection.
					// Your `collides` method already handles the 'collide' check for collinear.
					return std::nullopt;
				}
				// Parallel and non-collinear means no intersection.
				return std::nullopt;
			}

			// Calculate t and u
			T t_val = q_minus_p_cross_s / r_cross_s;
			T u_val = q_minus_p_cross_r / r_cross_s;

			// Check if the intersection point lies on both segments (0 <= t <= 1 and 0 <= u <= 1)
			// Use a small epsilon for boundary checks to account for floating point inaccuracies.
			const T epsilon = static_cast<T>(1e-6);

			if (t_val >= -epsilon && t_val <= 1.0f + epsilon &&
				u_val >= -epsilon && u_val <= 1.0f + epsilon)
			{
				// Return the 't' parameter for the current line segment (this).
				// Clamp t_val to [0, 1] if it's slightly outside due to epsilon
				return static_cast<ql::f32>(std::clamp(t_val, static_cast<T>(0.0), static_cast<T>(1.0)));
			}

			return std::nullopt; // No intersection within segments
		}


		constexpr bool collides(straight_line_t other) const
		{
			auto mode = [](ql::vector2<T> a, ql::vector2<T> b, ql::vector2<T> c)
			{
				auto ba = b - a;
				auto cb = c - b;
				auto x = ba.y * cb.x - ba.x * cb.y;

				if (x < T{0})
				{
					return 2u;
				}
				else if (x > T{0})
				{
					return 1u;
				}
				else
				{
					return 0u;
				}
			};
			auto collide = [](ql::vector2<T> a, ql::vector2<T> b, ql::vector2<T> c)
			{
				auto check_x = b.x <= ql::max(a.x, c.x) && b.x >= ql::min(a.x, c.x);
				auto check_y = b.y <= ql::max(a.y, c.y) && b.y >= ql::min(a.y, c.y);
				return check_x && check_y;
			};
			auto m1 = mode(this->a, this->b, other.a);
			auto m2 = mode(this->a, this->b, other.b);
			auto m3 = mode(other.a, other.b, this->a);
			auto m4 = mode(other.a, other.b, this->b);

			if (m1 != m2 && m3 != m4)
			{
				return true;
			}

			if (m1 == T{0} && collide(this->a, other.a, this->b))
				return true;

			if (m2 == T{0} && collide(this->a, other.b, this->b))
				return true;

			if (m3 == T{0} && collide(other.a, this->a, other.b))
				return true;

			if (m4 == T{0} && collide(other.a, this->b, other.b))
				return true;

			return false;
		}
	};

	using straight_line = straight_line_t<ql::f32>;

}	 // namespace ql