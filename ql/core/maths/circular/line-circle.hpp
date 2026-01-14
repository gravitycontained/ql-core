#pragma once

#include <ql/core/advanced-type/fundamental/vector.hpp>
#include <ql/core/advanced-type/fundamental/straight-line.hpp>
#include <ql/core/advanced-type/fundamental/circle.hpp>

namespace ql
{
	template <typename T>
	ql::vector2<T> closest_point_on_line_segment_to_circle(ql::straight_line_t<T> line_segment, ql::circle_t<T> circle)
	{
		ql::vector2<T> p1 = line_segment.a;
		ql::vector2<T> p2 = line_segment.b;

		ql::vector2<T> line_direction = p2 - p1;
		ql::vector2<T> p1_to_center = circle.position - p1;

		T denominator = line_direction.length_sq();

		if (denominator == static_cast<T>(0))
		{
			// Line segment is a single point.
			return p1;
		}

		T t = p1_to_center.dot(line_direction) / denominator;

		// !!! CRUCIAL CHANGE FOR LINE SEGMENT !!!
		// Clamp 't' to the [0, 1] range.
		// If t < 0, the closest point on the segment is p1.
		// If t > 1, the closest point on the segment is p2.
		// Otherwise, it's along the segment.
		t = std::max(static_cast<T>(0), std::min(static_cast<T>(1), t));

		ql::vector2<T> closest_point = p1 + line_direction * t;

		return closest_point;
	}

	template <typename T>
	std::pair<ql::vector2<T>, ql::f64> closest_point_on_circle_to_line_segment(ql::circle_t<T> circle, ql::straight_line_t<T> line_segment)
	{
		// 1. Find the point on the *line segment* that is closest to the circle.
		ql::vector2<T> closest_point_on_segment = closest_point_on_line_segment_to_circle(line_segment, circle);

		// The rest of the logic remains the same:
		// 2. The vector from the circle's center to this closest point on the segment.
		ql::vector2<T> center_to_segment_point_vec = circle.position - closest_point_on_segment;
		auto distance_center_to_segment = center_to_segment_point_vec.length();

		// 3. The closest point on the circle to the segment will be along the direction
		//    opposite to `center_to_segment_point_vec`, offset by the radius.

		// Handle the case where the circle's center is exactly on the segment.
		if (distance_center_to_segment == static_cast<T>(0))
		{
			// If the center is on the segment, any point on the circle is equidistant
			// to the segment (at radius distance). We'll pick one by moving along the
			// line segment's perpendicular normal from the center.
			// This normal logic for a segment can be tricky if the segment is short
			// and the circle is large. For robustness, if center is *on* the segment,
			// just pick a point on the circle by adding the radius in a default direction
			// (e.g., perpendicular to the segment's direction vector).
			ql::vector2<T> line_direction = line_segment.b - line_segment.a;
			if (line_direction.length_sq() == static_cast<T>(0)) {
				// The segment is a point. The closest circle point is just radius away in arbitrary direction
				return std::make_pair(circle.position + ql::vec<T>(circle.radius, static_cast<T>(0)), distance_center_to_segment); // e.g., to the right
			}
			ql::vector2<T> segment_normal = ql::vec<T>(-line_direction.y, line_direction.x).normal();
			return std::make_pair(circle.position + segment_normal * circle.radius, distance_center_to_segment);
		}
		else
		{
			// The direction from the circle's center to the closest point on the segment
			ql::vector2<T> direction_from_center_to_segment_point = center_to_segment_point_vec.normal();

			// The closest point on the circle is found by moving from the center
			// in the *opposite* direction of `direction_from_center_to_segment_point` by the radius.
			return std::make_pair(circle.position - (direction_from_center_to_segment_point * circle.radius), distance_center_to_segment);
		}
	}
}