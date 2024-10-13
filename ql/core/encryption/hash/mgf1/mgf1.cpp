#include <ql/core/encryption/hash/mgf1/mgf1.hpp>

#include <ql/core/string/to-string.hpp>

namespace ql
{

	std::string mgf1(const std::string_view& seed, ql::size length, ql::hash_type hash_object)
	{
		if (length == 0u)
		{
			return "";
		}
		std::string result = "";
		auto blocks = ((length - 1) / (hash_object.second / 4u) + 1);
		for (ql::size i = 0u; i < blocks; ++i)
		{
			auto input = ql::to_string(seed, i);
			result += hash_object.first(input);
		}
		result.resize(length);
		return result;
	}

}	 // namespace ql