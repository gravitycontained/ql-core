#include <ql/core/string/split/split.hpp>

#include <ql/core/transform/limit.hpp>

namespace ql
{
	std::vector<std::string> ql::string_split(const std::string_view& string, char by_what)
	{
		std::vector<std::string> result;

		ql::size before = 0;
		for (ql::size i = 0u; i < string.length();)
		{
			if (string[i] == by_what)
			{
				if (i - before)
				{
					result.emplace_back(std::string{string.substr(before, i - before)});
				}
				++i;
				while (i < string.length() && string[i] == by_what)
				{
					++i;
				}
				before = i;
			}
			else
			{
				++i;
			}
		}
		if (before != string.length())
		{
			result.emplace_back(std::string{string.substr(before)});
		}
		return result;
	}
	std::vector<std::string> ql::string_split_every(const std::string& string, ql::size n)
	{
		if (string.empty())
		{
			return {};
		}
		auto size = (string.size() - 1) / n + 1;
		std::vector<std::string> result;
		result.reserve(size);
		ql::size pos = 0;
		for (ql::u32 i = 0u;; ++i)
		{
			if (string.length() <= pos)
			{
				return result;
			}
			auto size = ql::min(string.length() - pos, n);

			std::string s;
			s.resize(size);
			memcpy(s.data(), string.data() + pos, size);
			result.push_back(s);

			pos += n;
		}
		return result;
	}

}