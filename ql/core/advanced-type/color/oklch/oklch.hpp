#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

#include <ql/core/advanced-type/color/rgb/rgb.hpp>
#include <ql/core/advanced-type/fundamental/matrix.hpp>
#include <ql/core/advanced-type/fundamental/vector.hpp>

#include <ql/core/transform/transform.hpp>

#if defined QL_SFML

#include <SFML/Graphics/Color.hpp>

#endif

namespace ql
{
	namespace detail
	{
		struct oklch_impl
		{
			union
			{
				struct
				{
					ql::f64 l;
					ql::f64 c;
					ql::f64 h;
					ql::f64 a;
				};

				std::array<ql::f64, 4> data;
			};

			constexpr oklch_impl() : data()
			{
				this->data = {0, 0, 0, 1};
			}
		};
	}

	struct oklch : detail::oklch_impl
	{
		constexpr oklch() : ql::detail::oklch_impl()
		{
		}

		constexpr oklch(ql::f64 l, ql::f64 c, ql::f64 h, ql::f64 a = 1) : ql::detail::oklch_impl()
		{
			this->l = l;
			this->c = c;
			this->h = h;
			this->a = a;
		}

		constexpr oklch(const ql::frgba& rgb) : ql::detail::oklch_impl()
		{
			this->from_oklch(rgb);
		}

		std::string to_string() const
		{
			return ql::to_string
			(
				"oklch(", ql::string_percentage_precision(this->l, 0),
				", ", ql::round(this->c, 4),
				", ", ql::round(this->h, 2),
					this->a == 1 ? "" : ql::to_string(" / ", ql::round(this->a, 2)),  ")"
			);
		}

		constexpr ql::frgba to_frgba() const
		{
			auto lab = ql::vec3d(
					{this->l, std::isnan(this->h) ? 0.0 : this->c * std::cos((this->h * ql::pi) / 180.0),
					 std::isnan(this->h) ? 0.0 : this->c * std::sin((this->h * ql::pi) / 180.0)}
			);

			constexpr auto lab_to_lms = ql::mat3d(
					{ql::vec3d(1, 0.3963377773761749, 0.2158037573099136), ql::vec3d(1, -0.1055613458156586, -0.0638541728258133),
					 ql::vec3d(1, -0.0894841775298119, -1.2914855480194092)}
			);

			auto lms = lab_to_lms * lab;
			for (auto& val : lms)
			{
				val = std::pow(val, 3);
			}

			constexpr auto lms_to_xyz = ql::mat3d(
					{ql::vec3d(1.2268798758459243, -0.5578149944602171, 0.2813910456659647),
					 ql::vec3d(-0.0405757452148008, 1.1122868032803170, -0.0717110580655164),
					 ql::vec3d(-0.0763729366746601, -0.4214933324022432, 1.5869240198367816)}
			);

			auto xyz = lms_to_xyz * lms;

			constexpr auto xyz_to_srgb = ql::mat3d(
					{ql::vec3d(3.2409699419045226, -1.537383177570094, -0.4986107602930034),
					 ql::vec3d(-0.9692436362808796, 1.8759675015077202, 0.04155505740717559),
					 ql::vec3d(0.05563007969699366, -0.20397695888897652, 1.0569715142428786)}
			);

			auto srgb = xyz_to_srgb * xyz;

			ql::vec3d rgb;
			for (int i = 0; i < 3; ++i)
			{
				rgb[i] = (std::abs(srgb[i]) > 0.0031308)
										 ? (std::copysign(1.0, srgb[i]) * (1.055 * std::pow(std::abs(srgb[i]), 1 / 2.4) - 0.055))
										 : (12.92 * srgb[i]);
			}
			return ql::vec4d(rgb[0], rgb[1], rgb[2], this->a);
		}

		constexpr void from_oklch(const ql::frgba& rgb)
		{
			auto srgb = rgb.data >> [](ql::f32 val)
			{
				return (std::abs(val) <= 0.04045) ? (val / 12.92)
																					: (std::copysign(1.0, val) * std::pow((std::abs(val) + 0.055) / 1.055, 2.4));
			};

			constexpr auto srgb_to_xyz = ql::mat3d(
					{ql::vec3d(0.41239079926595934, 0.357584339383878, 0.1804807884018343),
					 ql::vec3d(0.21263900587151027, 0.715168678767756, 0.07219231536073371),
					 ql::vec3d(0.01933081871559182, 0.11919477979462598, 0.9505321522496607)}
			);

			auto xyz = srgb_to_xyz * srgb;

			constexpr auto xyz_to_lms = ql::mat3d(
					{ql::vec3d(0.8189330101, 0.3618667424, -0.1288597137), ql::vec3d(0.0329845436, 0.9293118715, 0.0361456387),
					 ql::vec3d(0.0482003018, 0.2643662691, 0.6338517070)}
			);

			auto lms = xyz_to_lms * xyz;
			for (auto& val : lms)
			{
				val = std::cbrt(val);
			}

			constexpr auto lms_to_lab = ql::mat3d(
					{ql::vec3d(0.2104542553, 0.7936177850, -0.0040720468), ql::vec3d(1.9779984951, -2.4285922050, 0.4505937099),
					 ql::vec3d(0.0259040371, 0.7827717662, -0.8086757660)}
			);

			auto lab = lms_to_lab * lms;

			auto l = lab[0];
			auto a = lab[1];
			auto b = lab[2];

			*this = ql::oklch{
					l, ql::sqrt(a * a + b * b),
					(std::abs(a) < 0.0002 && std::abs(b) < 0.0002) ? std::numeric_limits<ql::f64>::quiet_NaN()
																												 : std::fmod(std::atan2(b, a) * 180.0 / ql::pi + 360.0, 360.0),
					rgb.a
			};
		}
		constexpr auto as_rgba() const
		{
			if (this->oklch_cache != this->data)
			{
				this->oklch_cache = {this->l, this->c, this->h, this->a};
				this->rgba_cache = this->to_frgba();
			}

			return this->rgba_cache;
		}

		constexpr operator ql::rgba() const
		{
			return this->as_rgba();
		}

		#if defined QL_SFML

		operator sf::Color() const
		{
			return this->as_rgba();
		}

		#endif

	private:
		mutable std::array<ql::f64, 4> oklch_cache;
		mutable ql::rgba rgba_cache;
	};

}	 // namespace ql