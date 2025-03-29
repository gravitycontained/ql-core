#pragma once

#include <ql/core/advanced-type/advanced-type.hpp>
#include <queue>

namespace ql
{
	struct bfs_node
	{
		ql::vec2s position;
		std::shared_ptr<bfs_node> parent;

		bfs_node()
		{
		}

		bfs_node(ql::vec2s position, const std::shared_ptr<bfs_node>& parent)
		{
			this->position = position;
			this->parent = parent;
		}

		bool operator==(const bfs_node& other) const
		{
			return this->position == other.position;
		}

		bool operator<(const bfs_node& other) const
		{
			return this->position.y < other.position.y || (this->position.y == other.position.y && this->position.x < other.position.x);
		}
	};

	template <bool allow_diagonal, typename T, typename F>
		requires (std::is_integral_v<T> && ql::is_callable<F>())
	std::vector<ql::vec2s> bfs_solve(const std::vector<std::vector<T>>& maze, ql::vec2s start, ql::vec2s end, F valid_check)
	{
		if (maze.empty())
			return {};

		auto width = ql::signed_cast(maze[0].size());
		auto height = ql::signed_cast(maze.size());

		std::queue<std::shared_ptr<ql::bfs_node>> queue;
		auto starting_node = std::make_shared<ql::bfs_node>(start, nullptr);
		queue.push(starting_node);

		std::unordered_set<ql::vec2s> visited;
		visited.insert(start);

		constexpr auto direction = [&]()
			{
				if constexpr (allow_diagonal)
					return ql::vec_cross9;

				else
					return ql::vec_cross4;
			}();

		while (!queue.empty())
		{
			std::shared_ptr<ql::bfs_node> current_node = queue.front();
			queue.pop();

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

			for (auto& dir : direction)
			{
				auto check = ql::vec2is(current_node->position) + dir;

				if (check.x >= 0 && check.x < width && check.y >= 0 && check.y < height)
				{
					bool valid = false;
					if constexpr (ql::parameter_size(valid_check) == 2u)
					{
						auto search_value = maze[check.y][check.x];
						auto previously_value = maze[current_node->position.y][current_node->position.x];
						valid = valid_check(search_value, previously_value);
					}
					else
					{
						auto search_value = maze[check.y][check.x];
						valid = valid_check(search_value);
					}
					if (valid)
					{
						bool found = visited.find(check) != visited.cend();
						if (!found)
						{
							auto next = std::make_shared<ql::bfs_node>(check, current_node);
							queue.push(next);
							visited.insert(check);
						}
					}
				}
			}
		}
		return {};
	}

}	 // namespace ql