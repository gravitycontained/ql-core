#include <ql/core/string/format/big-number/big-number.hpp>

namespace ql
{
	std::string ql::big_number_exponent_name(ql::isize exponent, bool short_format)
	{
		if (exponent < 0)
			return "/ " + big_number_exponent_name(exponent * -1, false);

		// a master lambda to encapsulate the entire logic, capturing the format choice.
		auto generate_name = [short_format](ql::isize exp) -> std::string
			{
				if (exp == 0)
					return short_format ? "" : "One";

				// if the exponent isn't a multiple of 3, find the nearest lower multiple.
				if (exp % 3 != 0)
					exp = (exp / 3) * 3;

				if (exp == 3)
					return short_format ? "k" : "Thousand";

				// the naming convention is based on n, where exponent = 3 * (n + 1)
				ql::size n = (exp / 3) - 1;

				// handle the first 9 -illions (Million to Nonillion) via direct lookup.
				if (n >= 1 && n <= 9)
				{
					constexpr std::array<std::string, 10> base_names_long = {
						"", "Million", "Billion", "Trillion", "Quadrillion", "Quintillion", "Sextillion", "Septillion", "Octillion", "Nonillion"
					};
					constexpr std::array<std::string, 10> base_names_short = { "", "M", "B", "T", "Qd", "Qn", "Sx", "Sp", "Oc", "No" };

					return short_format ? base_names_short[n] : base_names_long[n];
				}
				else if (n == 0)	// should not be reached due to exp==3 check, but for safety
					return "";

				// for n >= 10, we generate the name programmatically.
				// a recursive lambda is used to build the name prefix for any n.
				std::function<std::string(ql::size)> build_prefix;

				build_prefix = [&](ql::size num) -> std::string
					{
						if (num == 0)
							return "";

						// for n >= 1000, we use a recursive structure with "milli" as a joiner.
						// example: n=1234 -> (prefix for 1) + milli + (prefix for 234) -> Unmilli...
						if (num >= 1000)
						{
							std::string high_part = (num / 1000 == 1 && short_format == false) ? "un" : build_prefix(num / 1000);
							std::string low_part = build_prefix(num % 1000);
							return high_part + (short_format ? "Mi" : "milli") + low_part;
						}

						// define the Latin prefixes for units, tens, and hundreds.
						constexpr std::array<std::string, 10> units_long = { "",			"un",	 "duo",		 "tre",	 "quattuor",
																																"quin", "sex", "septem", "octo", "novem" };
						constexpr std::array<std::string, 10> tens_long = {
							"", "deci", "viginti", "triginti", "quadraginti", "quinquaginti", "sexaginti", "septuaginti", "octoginti", "nonaginti"
						};
						constexpr std::array<std::string, 10> hundreds_long = { "",					"centi",		"ducenti",		 "trecenti",	 "quadringenti",
																																	 "quingenti", "sescenti", "septingenti", "octingenti", "noningenti" };

						constexpr std::array<std::string, 10> units_short = { "", "U", "D", "T", "Qd", "Qn", "Sx", "Sp", "Oc", "No" };
						constexpr std::array<std::string, 10> tens_short = { "", "De", "Vt", "Tg", "qg", "Qg", "Sg", "Spg", "Ocg", "Nog" };
						constexpr std::array<std::string, 10> hundreds_short = { "", "C", "DC", "TC", "QdC", "QnC", "SxC", "SpC", "OcC", "NoC" };

						// Select vectors based on format
						const auto& units = short_format ? units_short : units_long;
						const auto& tens = short_format ? tens_short : tens_long;
						const auto& hundreds = short_format ? hundreds_short : hundreds_long;

						// decompose n into hundreds, tens, and units.
						auto h = (num / 100) % 10;
						auto t = (num / 10) % 10;
						auto u = num % 10;

						auto p_u = units[u];
						auto p_t = tens[t];
						auto p_h = hundreds[h];

						// lambda to apply combination rules for proper Latin grammar.
						auto apply_combo_rules = [&](std::string& unit, const std::string& ten_hundred)
							{
								if (short_format)
									return;	 // rules are for long format only

								if ((unit == "tre") && (ten_hundred.rfind("genti", 0) == 0 || ten_hundred.rfind("ginti", 0) == 0))
									unit = "tres";
								if ((unit == "septem" || unit == "novem") && (ten_hundred.rfind("deci", 0) == 0))
									unit.pop_back();	// septem/novem -> septen/noven
							};

						apply_combo_rules(p_u, p_t + p_h);

						// combine prefixes in the correct order: units, then tens, then hundreds.
						return p_u + p_t + p_h;
					};

				std::string prefix = build_prefix(n);

				// final assembly of the name.
				if (short_format)
					return prefix;

				else
				{
					// for long format, append "illion", handling vowel cleanup.
					if (prefix.back() == 'i')
						prefix.pop_back();

					return prefix + "illion";
				}
			};

		auto result = generate_name(exponent);
		if (!result.empty())
			result[0] = std::toupper(result[0]);

		return result;
	}
}