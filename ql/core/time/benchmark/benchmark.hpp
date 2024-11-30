#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/time/time/time.hpp>
#include <ql/core/time/clock/clock.hpp>
#include <unordered_map>

namespace ql
{
	namespace detail
	{
		QL_SOURCE extern std::unordered_map<std::string, std::unordered_map<std::string, ql::halted_clock>> sub_benchmark_clocks;
		QL_SOURCE extern std::unordered_map<std::string, ql::halted_clock> benchmark_clocks;
		QL_SOURCE extern std::string last_benchmark_name;
		QL_SOURCE extern std::string last_sub_benchmark_name;
	}	 // namespace detail

	QL_SOURCE void begin_benchmark_end_previous(const std::string& name);
	QL_SOURCE void begin_benchmark_end_previous(const std::string& sub, const std::string& name);
	QL_SOURCE ql::halted_clock get_benchmark(const std::string& name = "");
	QL_SOURCE void begin_benchmark(const std::string& name = "");
	QL_SOURCE void begin_benchmark(const std::string& sub, const std::string& name);
	QL_SOURCE void end_benchmark();
	QL_SOURCE void end_benchmark(const std::string& name);

	template <typename F>
	void benchmark(std::string name, F&& function)
	{
		ql::begin_benchmark(name);
		std::invoke(function);
		ql::end_benchmark(name);
	}

	QL_SOURCE void clear_benchmark();
	QL_SOURCE void reset_benchmark();
	QL_SOURCE void begin_benchmark_segments();
	QL_SOURCE void print_benchmark();
	QL_SOURCE void print_benchmark(const std::string& name);
}	 // namespace ql