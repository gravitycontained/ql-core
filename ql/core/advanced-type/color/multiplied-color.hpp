#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/color/rgb.hpp>

namespace ql
{
	namespace detail
	{
		template <typename C>
		concept has_set_color_c = requires(C& x) { x.set_color(ql::rgba{}); };
		template <typename C>
		concept has_set_outline_color_c = requires(C& x) { x.set_outline_color(ql::rgba{}); };

		struct outline_extension
		{
			ql::rgba original_outline_color = ql::rgba::black();
		};

		template <typename T>
		using color_extension_inheritance =
				ql::conditional<ql::if_true<has_set_outline_color_c<T>>, outline_extension, ql::empty_type>;
	}	 // namespace detail

	template <typename T>
	requires detail::has_set_color_c<T>
	struct multiplied_color_extension : T, detail::color_extension_inheritance<T>
	{
		ql::rgba original_color = ql::rgba::white();
		ql::rgba multiplied_color = ql::rgba::white();

		multiplied_color_extension()
		{
		}

		multiplied_color_extension(const multiplied_color_extension& other) = default;
		multiplied_color_extension& operator=(const multiplied_color_extension& value) = default;

		template <typename U>
		multiplied_color_extension(const U& value) : T(value)
		{
		}

		template <typename U>
		multiplied_color_extension(U&& value) : T(std::move(value))
		{
		}

		void set_color(ql::rgba color)
		{
			this->original_color = color;
			T::set_color(this->original_color.multiplied_color(this->multiplied_color));
		}

		void set_outline_color(ql::rgba color)
		requires detail::has_set_outline_color_c<T>
		{
			this->original_outline_color = color;
			T::set_outline_color(this->original_outline_color.multiplied_color(this->multiplied_color));
		}

		void set_multiplied_color(ql::rgba color)
		{
			this->multiplied_color = color;
			T::set_color(this->original_color.multiplied_color(this->multiplied_color));
			if constexpr (detail::has_set_outline_color_c<T>)
			{
				T::set_outline_color(this->original_outline_color.multiplied_color(this->multiplied_color));
			}
		}

		void set_multiplied_alpha(ql::u8 alpha)
		{
			this->set_multiplied_color(this->multiplied_color.with_alpha(alpha));
		}
	};

}	 // namespace ql