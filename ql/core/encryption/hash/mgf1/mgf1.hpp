#pragma once

#include <ql/core/encryption/hash/sha256/sha256.hpp>

namespace ql
{
	using hash_type = decltype(sha256_object);

	QL_SOURCE std::string mgf1(const std::string_view& seed, ql::size length, ql::hash_type hash_object);
}	 // namespace ql