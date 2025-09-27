#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/time/time/time.hpp>

namespace ql
{
	class small_clock
	{
	 public:
		small_clock()
		{
			this->reset();
		}

		QL_SOURCE void reset();

		QL_SOURCE ql::time elapsed() const;
		QL_SOURCE std::string elapsed_str() const;
		QL_SOURCE ql::f64 elapsed_f() const;

		QL_SOURCE ql::time elapsed_reset();
		QL_SOURCE std::string elapsed_str_reset();
		QL_SOURCE ql::f64 elapsed_f_reset();

		QL_SOURCE void add(ql::f64 seconds);
		QL_SOURCE void add(ql::time time);
		QL_SOURCE void subtract(ql::f64 seconds);
		QL_SOURCE void subtract(ql::time time);

		QL_SOURCE bool has_elapsed(ql::f64 seconds) const;
		QL_SOURCE bool has_elapsed(ql::time duration) const;
		QL_SOURCE bool has_elapsed_reset(ql::f64 seconds);
		QL_SOURCE bool has_elapsed_reset(ql::time duration);
		QL_SOURCE ql::size has_elapsed_subtract(ql::f64 seconds);
		QL_SOURCE ql::size has_elapsed_subtract(ql::time duration);

		ql::time m_begin;
	};

}	 // namespace ql