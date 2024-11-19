#pragma once

#include <ql/core/type/type.hpp>
#include <ql/core/advanced-type/fundamental/vector.hpp>

namespace ql
{

	template <typename T>
	struct straight_line_t
	{
		ql::vector2<T> a;
		ql::vector2<T> b;

		using maths_float_type = ql::conditional<ql::if_true<ql::is_same<T, ql::f32>()>, ql::f32, ql::default_type, ql::f64>;

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

		maths_float_type length() const
		{
			auto diff = this->b - this->a;
			return static_cast<maths_float_type>(std::sqrt(diff.x * diff.x + diff.y * diff.y));
		}

		ql::vector2<maths_float_type> normal() const
		{
			return ql::vector2<maths_float_type>{this->a.y - this->b.y, this->b.x - this->a.x} / this->length();
		}

		maths_float_type angle() const
		{
			auto atan = std::atan2(this->a.y - this->b.y, this->b.x - this->a.x);
			if (atan < 0)
				atan = static_cast<decltype(atan)>(2 * ql::pi + atan);
			return static_cast<maths_float_type>(atan);
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
			{
				return true;
			}
			if (m2 == T{0} && collide(this->a, other.b, this->b))
			{
				return true;
			}
			if (m3 == T{0} && collide(other.a, this->a, other.b))
			{
				return true;
			}
			if (m4 == T{0} && collide(other.a, this->b, other.b))
			{
				return true;
			}

			return false;
		}
	};

	using straight_line = straight_line_t<ql::f32>;

}	 // namespace ql