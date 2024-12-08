#include <ql/core/string/format/memory/memory.hpp>

#include <ql/core/string/format/precision/precision.hpp>
#include <ql/core/string/to-string.hpp>
#include <ql/core/transform/round.hpp>
#include <ql/core/transform/limit.hpp>

namespace ql
{
	std::string ql::string_memory_size(ql::size bytes, bool binary)
	{
		auto converted = ql::f64_cast(bytes);

		if (binary)
		{
			constexpr auto names = std::array{"kibi", "mebi", "gibi", "tebi", "pebi", "exbi", "zebi", "yebi"};

			if (converted < 1024)
				return ql::to_string(ql::round(converted, 1), " bytes");

			for (ql::size i = 0u; i < names.size(); ++i)
			{
				converted /= 1024.0;
				if (converted < 1000)
				{
					auto length = std::floor(std::log10(converted));
					auto precision = ql::size_cast(ql::clamp(ql::isize_cast(2 - length), 0ll, 3ll));
					return ql::to_string(ql::round(converted, precision), " ", names[i], "bytes");
				}
			}
		}
		else
		{
			constexpr auto names = std::array{"kilo", "mega", "giga", "tera", "peta", "exa", "zetta", "yotta"};

			if (converted < 1000)
				return ql::to_string(ql::round(converted, 1), " bytes");

			for (ql::size i = 0u; i < names.size(); ++i)
			{
				converted /= 1000.0;
				if (converted < 1000)
				{
					auto length = std::floor(std::log10(converted));
					auto precision = ql::size_cast(ql::clamp(ql::isize_cast(2 - length), 0ll, 3ll));
					return ql::to_string(ql::round(converted, precision), " ", names[i], "bytes");
				}
			}
		}

		return "";
	}
}	 // namespace ql