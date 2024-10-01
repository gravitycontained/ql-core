#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/compare/compare.hpp>
#include <ql/core/string/to-string.hpp>

#include <vector>
#include <string>

namespace ql
{
	struct string_collection
	{
		std::string string;
		std::vector<std::pair<ql::size, ql::size>> sizes;
		mutable ql::size index = 0u;

		QL_SOURCE void set_string(const std::string& string);
		QL_SOURCE bool set_string_and_read(const std::string& string);
		QL_SOURCE bool read_info();
		QL_SOURCE std::string get_next_string() const;
		QL_SOURCE std::string_view get_next_string_sv() const;
		QL_SOURCE std::string get_string() const;
		QL_SOURCE std::string_view get_string_sv() const;
		QL_SOURCE std::string get_string(ql::size index) const;
		QL_SOURCE std::string_view get_string_sv(ql::size index) const;
		QL_SOURCE std::string get_finalized_string();
		QL_SOURCE std::string_view get_finalized_string_sv();
		QL_SOURCE void add_string(const std::string& string);
		QL_SOURCE void finalize();
		QL_SOURCE ql::size size() const;
		QL_SOURCE void clear();

		template <typename T>
		requires (!ql::is_same<T, std::string>())
		string_collection& operator<<(T value)
		{
			this->add_string(ql::to_string(value));
			return *this;
		}

		string_collection& operator<<(std::string value)
		{
			this->add_string(value);
			return *this;
		}
	};
}	 // namespace ql