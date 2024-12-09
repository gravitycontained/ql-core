#include <ql/core/advanced-type/signal/signal-update-manager/signal-update-manager.hpp>

namespace ql
{
	void ql::signal_update_manager::clear_list()
	{
		this->next_list.clear();
	}

	void ql::signal_update_manager::reset_active()
	{
		this->active = false;
	}

	ql::size ql::signal_update_manager::advance_count()
	{
		return this->count++;
	}

	bool ql::signal_update_manager::cycle_allowed_store(ql::size index)
	{
		if (this->next_list.find(index) == this->next_list.cend())
		{
			this->next_list.insert(index);
			this->active = true;
			return true;
		}
		return false;
	}

}	 // namespace ql	