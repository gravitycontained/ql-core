#include <ql/core/async/interval/interval.hpp>
#include <ql/core/time/clock/small-clock/small-clock.hpp>
#include <ql/core/async/promise.hpp>

namespace ql
{
	std::shared_ptr<ql::subject> create_interval(ql::f64 time)
	{
		std::shared_ptr<ql::subject> signal = std::make_shared<ql::subject>();

		ql::make_promise(
				[=, &signal]()
				{
					ql::small_clock clock;
					while (signal.use_count() > 0)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(1));

						if (clock.has_elapsed_reset(time))
							signal->emit();
					}
				}
		);

		return signal;
	}
}