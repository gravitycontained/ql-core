#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/signal/signal.hpp>

namespace ql
{
	QL_SOURCE std::shared_ptr<ql::subject> create_interval(ql::f64 time);
}