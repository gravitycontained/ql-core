#pragma once

#include <termcolor/termcolor.hpp>
#include <ql/core/definition/definition.hpp>

namespace ql
{
	enum class print_color : ql::u32
	{
		black = 0,
		blue = 1,
		green = 2,
		aqua = 3,
		red = 4,
		purple = 5,
		yellow = 6,
		white = 7,
		gray = 8,
		bright_blue = 9,
		bright_green = 10,
		bright_aqua = 11,
		bright_red = 12,
		bright_purple = 13,
		bright_yellow = 14,
		bright_white = 15,
		bright_gray = 16,
		reset = 17,
	};

	constexpr auto black = ql::print_color::black;
	constexpr auto red = ql::print_color::red;
	constexpr auto green = ql::print_color::green;
	constexpr auto blue = ql::print_color::blue;
	constexpr auto yellow = ql::print_color::yellow;
	constexpr auto purple = ql::print_color::purple;
	constexpr auto aqua = ql::print_color::aqua;
	constexpr auto white = ql::print_color::white;
	constexpr auto gray = ql::print_color::gray;

	constexpr auto bright_red = ql::print_color::bright_red;
	constexpr auto bright_green = ql::print_color::bright_green;
	constexpr auto bright_blue = ql::print_color::bright_blue;
	constexpr auto bright_yellow = ql::print_color::bright_yellow;
	constexpr auto bright_purple = ql::print_color::bright_purple;
	constexpr auto bright_aqua = ql::print_color::bright_aqua;
	constexpr auto bright_white = ql::print_color::bright_white;


	constexpr auto reset = ql::print_color::reset;

	constexpr auto to_termcolor(ql::print_color color)
	{
		switch (color)
		{
			case ql::print_color::blue: return termcolor::blue<char>;
			case ql::print_color::green: return termcolor::green<char>;
			case ql::print_color::aqua: return termcolor::cyan<char>;
			case ql::print_color::red: return termcolor::red<char>;
			case ql::print_color::purple: return termcolor::magenta<char>;
			case ql::print_color::yellow: return termcolor::yellow<char>;
			case ql::print_color::white: return termcolor::white<char>;
			case ql::print_color::gray: return termcolor::grey<char>;

			case ql::print_color::bright_blue: return termcolor::bright_blue<char>;
			case ql::print_color::bright_green: return termcolor::bright_green<char>;
			case ql::print_color::bright_aqua: return termcolor::bright_cyan<char>;
			case ql::print_color::bright_red: return termcolor::bright_red<char>;
			case ql::print_color::bright_purple: return termcolor::bright_magenta<char>;
			case ql::print_color::bright_yellow: return termcolor::bright_yellow<char>;
			case ql::print_color::bright_white: return termcolor::bright_white<char>;
			case ql::print_color::bright_gray: return termcolor::bright_grey<char>;

			case ql::print_color::reset: return termcolor::reset<char>;
		}
		return termcolor::reset<char>;
	}
}