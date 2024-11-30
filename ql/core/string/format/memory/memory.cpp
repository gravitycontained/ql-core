#include <ql/core/string/format/memory/memory.hpp>

#include <ql/core/string/format/precision/precision.hpp>
#include <ql/core/string/to-string.hpp>

namespace ql
{
	std::string ql::string_memory_size(ql::size bytes, bool binary)
	{
		auto converted = ql::f64_cast(bytes);

		if (binary)
		{
			constexpr auto names = std::array{"kibi", "mebi", "gibi", "tebi", "pebi", "exbi", "zebi", "yebi"};

			if (converted < 1024)
				return ql::to_string(ql::string_precision(converted, 1), " bytes");

			for (ql::size i = 0u; i < names.size(); ++i)
			{
				converted /= 1024.0;
				if (converted < 1000)
				{
					return ql::to_string(ql::string_precision(converted, 1), " ", names[i], "bytes");
				}
			}
		}
		else
		{
			constexpr auto names = std::array{"kilo", "mega", "giga", "tera", "peta", "exa", "zetta", "yotta"};

			if (converted < 1000)
				return ql::to_string(ql::string_precision(converted, 1), " bytes");

			for (ql::size i = 0u; i < names.size(); ++i)
			{
				converted /= 1000.0;
				if (converted < 1000)
				{
					return ql::to_string(ql::string_precision(converted, 1), " ", names[i], "bytes");
				}
			}
		}

		return "";
	}
}	 // namespace ql