#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>
#include <ql/core/string/cast/cast.hpp>
#include <ql/core/transform/limit.hpp>
#include <ql/core/string/to-view.hpp>

#include <vector>
#include <regex>

namespace ql
{

	template <ql::size N, typename T>
	requires (ql::is_string_view<T>())
	constexpr std::array<ql::size, N> string_split_indices_static(const T& string, ql::string_underlying_type<T> delimiter = ',')
	{
		std::array<ql::size, N> result{};
		ql::size ctr = 0u;
		for (ql::size i = 0u; i < string.size(); ++i) {
			if (string[i] == delimiter)
				result[ctr++] = i;
		}
		return result;
	}

	template <typename T>
	requires (ql::is_string_view<T>())
	std::vector<ql::string_view_to_basic_string<T>> string_split(const T& string, ql::string_underlying_type<T> by_what)
	{
		using string_type = ql::string_view_to_basic_string<T>;
		std::vector<string_type> result;

		ql::size before = 0;
		for (ql::size i = 0u; i < string.length();)
		{
			if (string[i] == by_what)
			{
				if (i - before)
					result.emplace_back(string_type{string.substr(before, i - before)});

				++i;
				while (i < string.length() && string[i] == by_what)
					++i;

				before = i;
			}
			else
				++i;
		}
		if (before != string.length())
		{
			result.emplace_back(string_type{string.substr(before)});
		}
		return result;
	}

	template <typename T>
	requires (ql::is_string_type<T>() && !ql::is_string_view<T>())
	auto string_split(const T& string, ql::string_underlying_type<T> by_what)
	{
		return ql::string_split(ql::to_string_view(string), by_what);
	}

	template <typename T>
	requires (ql::is_string_view<T>())
	std::vector<ql::string_view_to_basic_string<T>> string_split_allow_empty(const T& string, ql::string_underlying_type<T> by_what)
	{
		using string_type = ql::string_view_to_basic_string<T>;
		std::vector<string_type> result;

		ql::size before = 0;
		for (ql::size i = 0u; i < string.length();)
		{
			if (string[i] == by_what)
			{
				if (i - before)
				{
					result.emplace_back(string_type{string.substr(before, i - before)});
				}
				++i;
				while (i < string.length() && string[i] == by_what)
				{
					result.push_back(ql::to_basic_string<ql::string_underlying_type<T>>(""));
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
			result.emplace_back(string_type{string.substr(before)});
		}
		return result;
	}

	template <typename T>
	requires (ql::is_string_type<T>() && !ql::is_string_view<T>())
	auto string_split_allow_empty(const T& string, ql::string_underlying_type<T> by_what)
	{
		return ql::string_split_allow_empty(ql::to_string_view(string), by_what);
	}

	template <typename T>
	requires (ql::is_string_view<T>())
	std::vector<ql::string_view_to_basic_string<T>> string_split_every(const T& string, ql::size n)
	{
		using string_type = ql::string_view_to_basic_string<T>;
		if (string.empty())
		{
			return {};
		}
		auto size = (string.size() - 1) / n + 1;
		std::vector<string_type> result;
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

	template <typename T>
	requires (ql::is_string_type<T>() && !ql::is_string_view<T>())
	auto string_split_every(const T& string, ql::size n)
	{
		return ql::string_split_every(ql::to_string_view(string), n);
	}

	template <typename T>
	std::vector<T> string_split_numbers(const std::string& string)
	{
		std::vector<T> result;

		if constexpr (ql::is_floating_point<T>())
		{
			static std::regex reg{"[0-9.e+]+"};
			auto s = std::sregex_iterator(string.cbegin(), string.cend(), reg);
			while (s != std::sregex_iterator())
			{
				result.push_back(ql::string_cast<T>(s->str()));
				++s;
			}
		}
		else if constexpr (ql::is_integer<T>())
		{
			static std::regex reg{"[0-9]+"};
			auto s = std::sregex_iterator(string.cbegin(), string.cend(), reg);
			while (s != std::sregex_iterator())
			{
				result.push_back(ql::string_cast<T>(s->str()));
				++s;
			}
		}
		else
		{
			static_assert("string_split_numbers<T>: T is not arithmetic");
		}
		return result;
	}

	template <typename T>
	std::vector<T> string_split_numbers(const std::wstring& string)
	{
		std::vector<T> result;

		if constexpr (ql::is_floating_point<T>())
		{
			static std::wregex reg{L"[0-9.e+]+"};
			auto s = std::wsregex_iterator(string.cbegin(), string.cend(), reg);
			while (s != std::wsregex_iterator())
			{
				result.push_back(ql::string_cast<T>(s->str()));
				++s;
			}
		}
		else if constexpr (ql::is_integer<T>())
		{
			static std::wregex reg{L"[0-9]+"};
			auto s = std::wsregex_iterator(string.cbegin(), string.cend(), reg);
			while (s != std::wsregex_iterator())
			{
				result.push_back(ql::string_cast<T>(s->str()));
				++s;
			}
		}
		else
		{
			static_assert("split_numbers<T>: T is not arithmetic");
		}
		return result;
	}

	template <typename T>
	requires (ql::is_long_string_type<T>())
	std::vector<T> string_split_expression(const T& string, const T& expression)
	{
		std::vector<T> result;

		if constexpr (ql::is_wstring_type<T>())
		{
			std::wsmatch smatch;
			std::wregex reg = std::wregex{ L"[^" + expression + L"]+" };
			auto s = std::wsregex_iterator(string.cbegin(), string.cend(), reg);
			while (s != std::wsregex_iterator()) {
				result.push_back(s->str());
				++s;
			}
			return result;
		}
		else
		{
			std::smatch smatch;
			std::regex reg = std::regex{ "[^" + expression + "]+" };
			auto s = std::sregex_iterator(string.cbegin(), string.cend(), reg);
			while (s != std::sregex_iterator()) {
				result.push_back(s->str());
				++s;
			}
			return result;
		}
	}

}	 // namespace ql