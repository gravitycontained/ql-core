#pragma once

#include <ql/core/definition/definition.hpp>

#include <unordered_set>

namespace ql
{
	struct signal_update_manager
	{
		std::unordered_set<ql::size> next_list;
		ql::size count = 0u;
		bool active = false;

		QL_SOURCE void clear_list();
		QL_SOURCE void reset_active();
		QL_SOURCE ql::size advance_count();
		QL_SOURCE bool cycle_allowed_store(ql::size index);
	};
}