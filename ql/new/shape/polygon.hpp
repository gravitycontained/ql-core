#pragma once

#include <ql/core/core.hpp>

#include "straight-line.hpp"

namespace qldev
{
	template <typename T>
	requires (ql::is_arithmetic<T>())
	struct polygon_t : public std::vector<ql::vector2<T>>
	{
		bool collides(ql::vec2 point, ql::size index_increment = 1ull) const
		{
			bool flag = false;

			qldev::straight_line compare;
			compare.a = {0, 0};
			compare.b = point;

			auto j = this->size() - 1;
			for (ql::size i = 0u; i < this->size(); i += index_increment)
			{
				ql::straight_line edge_line;
				edge_line.a = this->get_point(i);
				edge_line.b = this->get_point(j);
				if (compare.collides(edge_line))
				{
					flag = !flag;
				}
				j = i;
			}
			return flag;
		}
	};
}