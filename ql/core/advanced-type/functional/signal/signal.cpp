#include <ql/core/advanced-type/functional/signal/signal.hpp>

namespace ql
{
	namespace detail
	{
		std::unordered_set<ql::size> signal_listeners;
		ql::size signal_index = 0u;
	}	 // namespace detail

	void reset_signal_listeners()
	{
		detail::signal_listeners.clear();
	}

	void reset_signal_count()
	{
		detail::signal_index = 0u;
	}


}	 // namespace ql	