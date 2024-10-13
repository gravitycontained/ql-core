#include <ql/core/advanced-type/color/rgb/rgb.hpp>

#include <ql/core/random/random.hpp>

namespace ql
{
	ql::rgb get_random_color()
	{
		auto value = ql::random((1u - 24) - 1);
		auto r = (value & 0xFF0000u) >> 16;
		auto g = (value & 0x00FF00u) >> 8;
		auto b = (value & 0x0000FFu);
		return ql::rgb(r, g, b);
	}

	ql::rgba get_random_transparency_color()
	{
		auto u32 = ql::random(ql::u32_max);
		ql::rgba result;
		memcpy(&result, &u32, sizeof(u32));
		return result;
	}

	ql::rgb get_rainbow_color(ql::f64 f)
	{
		constexpr auto rainbow = std::array{ql::rgb::red(),	 ql::rgb::yellow(),	 ql::rgb::green(), ql::rgb::cyan(),
																				ql::rgb::blue(), ql::rgb::magenta(), ql::rgb::red()};
		return ql::rgb::interpolation(rainbow, f);
	}

	ql::rgb get_random_rainbow_color()
	{
		return ql::get_rainbow_color(ql::random(0.0, 1.0));
	}
}	 // namespace ql