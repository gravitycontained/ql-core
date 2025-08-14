#pragma once

#include <ql/core/type/type.hpp>
#include <ql/core/string/cast/cast.hpp>
#include <ql/core/string/format/precision/precision.hpp>

namespace ql
{
	template <typename T>
	requires (ql::is_arithmetic<T>())
	std::string big_number_string(T number, ql::u32 precision = 2)
	{
		if (number == T{})
			return ql::to_string(number);

		if constexpr (ql::is_signed<T>())
			if (number < 0)
				return "-" + ql::big_number_string(-number, precision);

		ql::i64 log;
		if constexpr (ql::is_ql_integer<T>())
			log = ql::i64_cast((number.digits() - 1) / 3.0);

		else
			log = ql::i64_cast(std::log(number) / std::log(1000.0));

		std::string name;
		bool negative = false;

		if (log < 0)
		{
			log *= -1;
			negative = true;
		}

		const static std::array<std::string, 10> p_ones = {"", "un", "dou", "tre", "quat", "quin", "sex", "sept", "oct", "non"};
		const static std::array<std::string, 10> p_tens = {"dec",		"vig",		 "trig",	"quadrag", "quinquag",
																											 "sexag", "septuag", "octog", "nonag"};

		if (log >= 1 && log <= 100)
		{
			switch (log)
			{
				case 1:
					name = "k";
					break;
				case 2:
					name = "mln";
					break;
				case 3:
					name = "bln";
					break;
				case 4:
					name = "trn";
					break;
				case 5:
					name = "quad";
					break;
				case 6:
					name = "quint";
					break;
				case 7:
					name = "sext";
					break;
				case 8:
					name = "sept";
					break;
				case 9:
					name = "oct";
					break;
				case 10:
					name = "non";
					break;
				default:
					name = ql::to_string(p_ones[(log - 1) % 10], p_tens[((log - 1) / 10) - 1]);
			}
		}
		if constexpr (ql::is_integer<T>())
			if (number < 1000)
				return ql::to_string(number);

		if (log == 0)
			return ql::to_string(ql::string_precision(precision, ql::size_cast(number)), name);

		if (negative)
			return ql::to_string(ql::string_precision(precision, ql::size_cast(number * std::pow(1000, log))), " 1/", name);

		else
			return ql::to_string(ql::string_precision(precision, ql::size_cast(number / std::pow(1000, log))), name);
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	std::string big_number_string_short(T number, ql::u32 precision = 1)
	{
		if (number == T{})
		{
			return ql::to_string(number);
		}
		if constexpr (ql::is_signed<T>())
		{
			if (number < 0)
			{
				return "-" + ql::big_number_string(-number, precision);
			}
		}
		ql::i64 log;
		if constexpr (ql::is_ql_integer<T>())
		{
			log = (number.digits() - 1) / 3.0;
		}
		else
		{
			log = static_cast<ql::i64>(std::log(number) / std::log(1000.0));
		}
		std::string name;
		bool negative = false;

		if (log < 0)
		{
			log *= -1;
			negative = true;
		}

		const static std::array<std::string, 10> p_ones = {"", "Un", "Dou", "Tre", "Qa", "Qi", "Sx", "Sp", "Oc", "No"};
		const static std::array<std::string, 10> p_tens = {"Dec", "Vig", "Tri", "Qa", "Qi", "Sx", "Sp", "Oc", "No"};

		if (log >= 1 && log <= 100)
		{
			switch (log)
			{
				case 1:
					name = "K";
					break;
				case 2:
					name = "M";
					break;
				case 3:
					name = "B";
					break;
				case 4:
					name = "T";
					break;
				case 5:
					name = "Qa";
					break;
				case 6:
					name = "Qi";
					break;
				case 7:
					name = "Sx";
					break;
				case 8:
					name = "Sp";
					break;
				case 9:
					name = "Oc";
					break;
				case 10:
					name = "No";
					break;
				default:
					name = ql::to_string(p_ones[(log - 1) % 10], p_tens[((log - 1) / 10) - 1]);
			}
		}
		if constexpr (ql::is_integer<T>())
		{
			if (number < 1000)
			{
				return ql::to_string(number);
			}
		}
		if (log == 0)
		{
			return ql::to_string(ql::string_precision(precision, ql::size_cast(number)), name);
		}
		if (negative)
		{
			ql::f64 pow;
			if constexpr (ql::is_ql_integer<T>())
			{
				T x = 1000;
				pow = x.pow(log);
			}
			else
			{
				pow = std::pow(1000, log);
			}
			return ql::to_string(ql::string_precision(precision, ql::size_cast(number * pow)), " 1/", name);
		}
		else
		{
			ql::f64 pow;
			if constexpr (ql::is_ql_integer<T>())
			{
				T x = 1000;
				pow = x.pow(log);
			}
			else
			{
				pow = std::pow(1000, log);
			}

			return ql::to_string(ql::string_precision(precision, ql::size_cast(number / pow)), name);
		}
	}
}	 // namespace ql