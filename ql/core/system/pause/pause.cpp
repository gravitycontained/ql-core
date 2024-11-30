#include <ql/core/system/pause/pause.hpp>

#include <ql/core/system/print/print.hpp>

#include <iostream>
#include <chrono>

namespace ql
{
	void system_pause(ql::u32 max_keyboard_latency_hz)
	{
		ql::print("press enter to continue . . . ");
		if (!std::cin.good())
		{
			std::cin.clear();
		}
		auto t1 = std::chrono::high_resolution_clock::now();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		auto t2 = std::chrono::high_resolution_clock::now();

		double delta_t = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;
		if (delta_t < 1.0 / max_keyboard_latency_hz)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}