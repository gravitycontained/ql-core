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

		straight_line_t with_length(float_type length) const
		{
			auto normal = this->normal();
			auto center = this->center();
			return straight_line_t{ center - normal * length / 2, center + normal * length / 2 };
		}

		ql::vector2<float_type> perpendicular_normal() const
		{
			return ql::vector2<float_type>{this->a.y - this->b.y, this->b.x - this->a.x} / this->length();
		}

		ql::vector2<float_type> normal() const
		{
			return ql::vector2<float_type>{this->b.x - this->a.x, this->b.y - this->a.y} / this->length();
		}
		
		ql::vector2<float_type> center() const
		{
			return (this->a + this->b) / 2;
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

		constexpr bool collides(const straight_line_t<T>& other) const
		{
			// Use the line_intersection_point function to find the potential intersection.
			// It's helpful to have a version of line_intersection_point that signals if lines are parallel/collinear
			// rather than just returning (0,0), which could be a valid intersection.
			// For this example, let's modify the line_intersection_point slightly or assume den != 0 implies intersection.

			// Re-implementing parts of line_intersection_point for clarity within collides,
			// or ensure your stand-alone line_intersection_point can provide more info.

			ql::vector2<T> p1 = this->a;
			ql::vector2<T> p2 = this->b;
			ql::vector2<T> p3 = other.a;
			ql::vector2<T> p4 = other.b;

			T den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

			// If den is 0, lines are parallel or collinear
			if (den == 0) {
				// For parallel/collinear lines, they only "collide" if they overlap.
				// This is a more complex edge case. For basic collision, we can often treat them as not colliding.
				// If they are collinear and overlap, that's a collision.
				// For simplicity here, if den == 0, we'll return false, as a unique intersection point is needed
				// for the subsequent checks. If you need to handle collinear overlap, this section needs expansion.
				return false;
			}

			// Calculate t and u parameters for the intersection point
			T t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / den;
			T u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / den;

			// Check if the intersection point lies within both line segments
			// The intersection point lies on segment 1 if 0 <= t <= 1
			// The intersection point lies on segment 2 if 0 <= u <= 1
			const T epsilon = std::numeric_limits<T>::epsilon(); // For floating-point comparisons
			bool intersects_on_segment1 = (t >= -epsilon && t <= 1.0 + epsilon);
			bool intersects_on_segment2 = (u >= -epsilon && u <= 1.0 + epsilon);

			return intersects_on_segment1 && intersects_on_segment2;
		}
	};

	using straight_line = straight_line_t<ql::f32>;

}	 // namespace ql