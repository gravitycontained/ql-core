#pragma once

#include <ql/core/advanced-type/advanced-type.hpp>
#include <queue>

namespace ql
{
	struct astar_node
	{
		ql::vec2s position;
		std::shared_ptr<astar_node> parent;
		ql::size g = 0;
		ql::size h = 0;
		ql::size f = 0;

		astar_node()
		{
		}

		astar_node(ql::vec2s position, const std::shared_ptr<astar_node>& parent)
		{
			this->position = position;
			this->parent = parent;
		}

		bool operator==(const astar_node& other) const
		{
			return this->position == other.position;
		}

		bool operator<(const astar_node& other) const
		{
			return this->position.y < other.position.y || (this->position.y == other.position.y && this->position.x < other.position.x);
		}
	};

	template <bool allow_diagonal, typename T, typename F>
	requires (ql::is_callable<F>())
	std::vector<ql::vec2s> astar_solve(const std::vector<std::vector<T>>& maze, ql::vec2s start, ql::vec2s end, F valid_check)
	{
		if (maze.empty())
			return {};

		auto width = ql::signed_cast(maze[0].size());
		auto height = ql::signed_cast(maze.size());

		std::vector<std::shared_ptr<ql::astar_node>> queue;
		std::shared_ptr<ql::astar_node> starting_node = std::make_shared<ql::astar_node>(start, nullptr);
		queue.push_back(starting_node);

		constexpr auto direction = [&]()
			{
				if constexpr (allow_diagonal)
					return ql::vec_cross9;

				else
					return ql::vec_cross4;
			}();

		std::unordered_set<ql::vec2s> visited;

		while (!queue.empty())
		{
			std::shared_ptr<ql::astar_node> current_node = *queue.begin();
			ql::size current_index = 0u;
			ql::size ctr = 0u;
			for (auto& element : queue)
			{
				if (element->f < current_node->f)
				{
					current_node = element;
					current_index = ctr;
				}
				++ctr;
			}

			visited.insert(current_node->position);
			queue.erase(queue.begin() + current_index);

			if (current_node->position == end)
			{
				auto traverse = current_node;
				std::vector<ql::vec2s> path;
				while (traverse)
				{
					path.push_back(traverse->position);
					traverse = traverse->parent;
				}
				std::ranges::reverse(path);
				return path;
			}

			std::vector<std::shared_ptr<ql::astar_node>> children;
			for (auto& dir : direction)
			{
				auto check = ql::vec2is(current_node->position) + dir;

				if (check.x >= 0 && check.x < width && check.y >= 0 && check.y < height)
				{
					bool valid = false;
					if constexpr (ql::parameter_size(valid_check) == 2u)
						valid = valid_check(maze[check.y][check.x], maze[current_node->position.y][current_node->position.x]);

					else
						valid = valid_check(maze[check.y][check.x]);

					if (valid)
					{
						bool found = visited.find(check) != visited.cend();

						bool queue_found = false;
						for (auto& i : queue)
						{
							if (i->position == check)
							{
								queue_found = true;
								break;
							}
						}

						if (!found && !queue_found)
						{
							auto next = std::make_shared<ql::astar_node>(check, current_node);
							children.push_back(next);
						}
					}
				}
			}

			for (auto& child : children)
			{
				auto x = ql::signed_cast(child->position.x) - ql::signed_cast(end.x);
				auto y = ql::signed_cast(child->position.y) - ql::signed_cast(end.y);

				child->g = current_node->g + 1u;
				child->h = x * x + y * y;
				child->f = child->g + child->h;

				queue.push_back(child);
			}
		}
		return {};
	}

}	 // namespace ql