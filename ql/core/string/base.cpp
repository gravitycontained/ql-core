#include <ql/core/string/base.hpp>

#include <ql/core/transform/bit/bit.hpp>

#include <ql/core/transform/limit.hpp>

#include <bitset>

namespace ql
{
	std::string base64_string(const std::string_view& input)
	{
		std::string output;
		for (ql::size i = 0u; i < input.length(); i += 3u)
		{
			std::bitset<24> buffer{0};
			for (ql::size j = 0; j < 3; ++j)
			{
				buffer <<= 8;
				if (i + j < input.length())
				{
					buffer |= ql::u8_cast(input[i + j]);
				}
			}
			for (ql::size j = 0; j < 4; ++j)
			{
				if (i + j * 6 / 8 < input.length())
				{
					output += ql::detail::base_64[(buffer >> (18 - j * 6)).to_ulong() & 0x3F];
				}
			}
		}
		return output;
	}

	std::string from_base64_string(const std::string_view& input)
	{
		std::string output;
		for (ql::size i = 0; i < input.length(); i += 4)
		{
			std::bitset<24> buffer{0};

			for (ql::size j = 0; j < 4; ++j)
			{
				buffer <<= 6;
				if (i + j < input.length())
				{
					buffer |= ql::detail::base_64_inv[ql::u8_cast(input[i + j])];
				}
			}

			for (ql::size j = 0u; j < 3u; ++j)
			{
				if (i + j + 1 < input.length())
				{
					output += static_cast<char>((buffer >> (16 - j * 8)).to_ulong() & 0xFF);
				}
			}
		}

		return output;
	}

	std::string hex_string(const std::string_view& string)
	{
		std::ostringstream stream;
		for (auto& i : string)
		{
			stream << ql::string_prepended(ql::hex_string(ql::u8_cast(i), ""), "0", 2);
		}
		return stream.str();
	}

	std::string from_hex_string(const std::string_view& string)
	{
		std::ostringstream stream;
		for (ql::size i = 0u; i < string.length(); i += 2u)
		{
			stream << ql::char_cast(ql::from_base_string(string.substr(i, 2u), 16));
		}
		return stream.str();
	}

	std::string hex_to_base64_string(const std::string_view& string)
	{
		return ql::base64_string(ql::from_hex_string(string));
	}

	std::string base64_to_hex_string(const std::string_view& string)
	{
		return ql::hex_string(ql::from_base64_string(string));
	}

	std::string binary_string(const std::string& string)
	{
		std::ostringstream stream;
		for (auto& i : string)
		{
			stream << ql::string_prepended(ql::binary_string(ql::u8_cast(i)), "0", 8);
		}
		return stream.str();
	}

	std::string string_xor(std::string a, std::string b)
	{
		std::string result;
		result.resize(ql::min(a.size(), b.size()));
		for (ql::size i = 0u; i < result.length(); ++i)
		{
			result[i] = a[i] ^ b[i];
		}
		return result;
	}

	std::string hex_string_xor(std::string a, std::string b)
	{
		std::string result;
		result.resize(ql::min(a.size(), b.size()));
		for (ql::size i = 0u; i < result.length(); ++i)
		{
			auto value = ql::from_base_char(a[i], 16u) ^ ql::from_base_char(b[i], 16u);
			result[i] = ql::base_char(value, 16u);
		}
		return result;
	}
}	 // namespace ql