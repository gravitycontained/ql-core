#include <ql/core/time/benchmark/benchmark.hpp>

#include <ql/core/system/print/print.hpp>

namespace ql
{
	std::unordered_map<std::string, std::unordered_map<std::string, ql::halted_clock>> ql::detail::sub_benchmark_clocks;
	std::unordered_map<std::string, ql::halted_clock> ql::detail::benchmark_clocks;
	std::string ql::detail::last_benchmark_name;
	std::string ql::detail::last_sub_benchmark_name;

	void begin_benchmark_end_previous(const std::string& name)
	{
		ql::end_benchmark();
		ql::begin_benchmark(name);
	}

	void begin_benchmark_end_previous(const std::string& sub, const std::string& name)
	{
		ql::end_benchmark();
		ql::begin_benchmark(sub, name);
	}

	ql::halted_clock ql::get_benchmark(const std::string& name)
	{
		return ql::detail::benchmark_clocks[name];
	}

	void begin_benchmark(const std::string& name)
	{
		ql::detail::last_benchmark_name = name;
		ql::detail::benchmark_clocks[name].resume();
	}

	void begin_benchmark(const std::string& sub, const std::string& name)
	{
		ql::detail::last_benchmark_name = name;
		ql::detail::last_sub_benchmark_name = sub;
		ql::detail::sub_benchmark_clocks[sub][name].resume();
	}

	void end_benchmark(const std::string& name)
	{
		ql::detail::benchmark_clocks[name].pause();
	}

	void end_benchmark()
	{
		if (!ql::detail::last_sub_benchmark_name.empty())
		{
			ql::detail::sub_benchmark_clocks[ql::detail::last_sub_benchmark_name][ql::detail::last_benchmark_name].pause();
			ql::detail::last_sub_benchmark_name.clear();
			ql::detail::last_benchmark_name.clear();
		}
		else if (!ql::detail::last_benchmark_name.empty())
		{
			ql::detail::benchmark_clocks[ql::detail::last_benchmark_name].pause();
			ql::detail::last_benchmark_name.clear();
		}
	}

	void begin_benchmark_segments()
	{
		ql::detail::benchmark_clocks.clear();
	}

	void clear_benchmark()
	{
		ql::detail::benchmark_clocks.clear();
	}

	void reset_benchmark()
	{
		ql::clear_benchmark();
	}

	void print_benchmark()
	{
		ql::time sum = 0;

		ql::size length_max = 0u;
		std::vector<std::pair<std::string, double>> sorted;
		for (auto& i : ql::detail::benchmark_clocks)
		{
			length_max = ql::max(length_max, i.first.length());
			sum += i.second.elapsed();
			sorted.emplace_back(std::make_pair(i.first, i.second.elapsed_f()));
		}
		std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

		for (auto i : ql::detail::benchmark_clocks)
		{
			if (i.first == sorted.front().first && sorted.size() >= 2u)
			{
				ql::print(ql::color::bright_green);
			}
			else if (i.first == sorted.back().first && sorted.size() >= 3u)
			{
				ql::print(ql::color::bright_red);
			}
			auto f = i.second.elapsed().nsecs_f() / sum.nsecs_f();

			auto precision = ql::size{3};
			auto percentage_string = ql::string_percentage_precision(f, precision);
			percentage_string = ql::string_prepended(percentage_string, ' ', precision + 4);
			ql::print(ql::to_string(
					ql::string_right_spaced(i.first, length_max + 1), " - ", ql::string_left_spaced(percentage_string, 10),
					" time usage : ", i.second.elapsed().string()
			));

			if (i.first != sorted.back().first && sorted.size() >= 2u)
			{
				auto p = ql::size_cast(sorted.back().second / i.second.elapsed_f());
				ql::print(" [ ", ql::string_precision(3, p), "x ]");
			}
			ql::println();
		}

		for (auto& sub : ql::detail::sub_benchmark_clocks)
		{
			ql::println();
			sum = 0;
			length_max = 0u;
			sorted.clear();
			for (auto& i : sub.second)
			{
				length_max = ql::max(length_max, i.first.length());
				sum += i.second.elapsed();
				sorted.emplace_back(std::make_pair(i.first, i.second.elapsed_f()));
			}
			std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

			for (auto& i : sub.second)
			{
				if (i.first == sorted.front().first && sorted.size() >= 2u)
				{
					ql::print(ql::color::bright_green);
				}
				else if (i.first == sorted.back().first && sorted.size() >= 3u)
				{
					ql::print(ql::color::bright_red);
				}

				auto f = i.second.elapsed().nsecs_f() / sum.nsecs_f();
				if (i.first != sorted.back().first && sorted.size() >= 2u)
				{
					auto p = ql::size_cast(sorted.back().second / i.second.elapsed_f());
					ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::to_string(
							sub.first, ": ", ql::string_left_spaced(i.first, length_max + 1), " - ",
							ql::string_left_spaced(ql::string_precision(f * 100, 7), 14),
							"% time usage : ", i.second.elapsed().string(), " [ ", ql::string_precision(p, 3), "x ]"
					));
				}
				else
				{
					ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::to_string(
							sub.first, ": ", ql::string_left_spaced(i.first, length_max + 1), " - ",
							ql::string_left_spaced(ql::string_precision(f * 100, 7), 14),
							"% time usage : ", i.second.elapsed().string()
					));
				}
			}
		}
	}

	void print_benchmark(const std::string& name)
	{
		ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", name, " took ", ql::detail::benchmark_clocks[name].elapsed_reset().string());
	}
}	 // namespace ql
