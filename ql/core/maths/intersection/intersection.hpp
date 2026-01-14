#pragma once

#include <ql/core/advanced-type/fundamental/vector.hpp>
#include <ql/core/advanced-type/fundamental/straight-line.hpp>

namespace ql
{
	template <typename T>
	constexpr ql::vector2<T> line_intersection_point(ql::straight_line_t<T> a, ql::straight_line_t<T>  b)
	{
		// line a points
		ql::vector2<T> p1 = a.a;
		ql::vector2<T> p2 = a.b;

		// line b points
		ql::vector2<T> p3 = b.a;
		ql::vector2<T> p4 = b.b;

		// calculate slopes and intercepts
		auto den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

		// if den is 0, lines are parallel or collinear
		if (den == 0)
			return ql::vec(0, 0);

		auto t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / den;

		ql::vector2<T> intersection_point;
		intersection_point.x = p1.x + t * (p2.x - p1.x);
		intersection_point.y = p1.y + t * (p2.y - p1.y);

		return intersection_point;
	}

	template <typename T>
	std::pair<ql::vector2<T>, ql::vector2<T>> line_bounce_point(ql::vector2<T> line_start, ql::vector2<T> line_end_target, ql::straight_line_t<T> reflector)
	{
		ql::straight_line_t<T> incident_line;
		incident_line.a = line_start;
		incident_line.b = line_end_target;

		// 1. find the intersection point of incident_line and line b
		ql::vector2<T> collision_point = line_intersection_point(incident_line, reflector);

		// 2. calculate the incident vector (direction of the incoming ray)
		ql::vector2<T> incident_vector = (line_end_target - line_start).normal();

		// 3. get the normal of line b
		ql::vector2<T> normal_b = reflector.perpendicular_normal();

		// 4. calculate the reflected vector
		// the reflection formula is: R = I - 2 * (I . N) * N
		// where I is the incident vector, N is the normal vector
		T dot_product = incident_vector.dot(normal_b);
		ql::vector2<T> reflected_vector = incident_vector - (normal_b * (static_cast<T>(2) * dot_product));
		reflected_vector = reflected_vector.normal();

		// 5. determine the final reflection point along the reflected ray
		// we want the new point to be at the same distance from collision_point as line_end_target was from collision_point
		auto distance_from_collision = (line_end_target - collision_point).length();

		// the final reflection point is collision_point + reflected_vector * distance
		ql::vector2<T> final_reflection_point = collision_point + (reflected_vector * distance_from_collision);

		return std::make_pair(final_reflection_point, reflected_vector);
	}

}