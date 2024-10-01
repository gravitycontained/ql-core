#include <ql/core/string/format/format.hpp>
#include <sstream>

namespace ql
{
	std::string string_to_fit(const std::string& string, char append, ql::size length)
	{
		return std::string(string.length() >= length ? 0ull : length - string.length(), append);
	}

	namespace detail
	{

		std::string string_prepended(const std::string_view& string, char prepend, ql::size length)
		{
			if (string.length() >= length)
			{
				return std::string{string};
			}
			auto result = std::string(length - string.length(), prepend);
			result += string;
			return result;
		}

		std::string string_prepended(const std::string_view& string, const std::string_view& prepend, ql::size length)
		{
			if (string.length() >= length)
			{
				return std::string{string};
			}

			auto mod = (length - string.length()) % prepend.length();
			auto div = (length - string.length()) / prepend.length();

			std::ostringstream stream;
			for (ql::u32 i = 0u; i < div; ++i)
			{
				stream << prepend;
			}
			if (mod)
			{
				stream << prepend.substr(0, mod);
			}

			stream << string;
			return stream.str();
		}

		std::string string_appended(const std::string_view& string, char append, ql::size length)
		{
			if (string.length() >= length)
			{
				return std::string{string};
			}
			auto result = std::string{string};
			result += std::string(length - string.length(), append);
			return result;
		}

		std::string string_appended(const std::string_view& string, const std::string_view& prepend, ql::size length)
		{
			if (string.length() >= length)
			{
				return std::string{string};
			}

			auto multiple = ((string.length() - 1) / prepend.length() + 1) * prepend.length();
			auto left = multiple - string.length();
			auto full = length < multiple ? 0u : ((length - multiple) / prepend.length());
			auto right = length < multiple ? 0u : (length % prepend.length());

			std::ostringstream stream;
			stream << string;

			if (left)
			{
				stream << prepend.substr(prepend.length() - left, length - string.length());
			}
			for (ql::u32 i = 0u; i < full; ++i)
			{
				stream << prepend;
			}
			if (right)
			{
				stream << prepend.substr(0, right);
			}

			return stream.str();
		}

	}	 // namespace detail
}	 // namespace ql