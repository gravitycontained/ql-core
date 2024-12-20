#include <ql/graphic/sync/check-uninitialized/check-uninitialized.hpp>
#include <ql/graphic/sync/type/type.hpp>

namespace ql
{
	void sync_check_uninitialized(ql::state_manager& manager)
	{
		for (ql::size i = 0;; ++i)
		{
			if (i >= 1000)
			{
				ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_yellow,
					ql::to_string("sync check uninitialized > 1000 cycles, breaking loop");

				break;
			}

			if (ql::detail::sync_unitialized_count)
			{
				ql::println(
					ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_yellow,
					ql::color::aqua, ql::detail::sync_unitialized_count, ql::color::bright_gray, " new synchronizations"
				);
				ql::detail::sync_unitialized_count = 0u;
				manager.provide();
				manager.initialize();
			}
		}
	}
}