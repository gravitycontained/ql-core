#pragma once

#include <ql/core/core.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/render/render.hpp>

namespace ql
{
	enum class interaction_state : ql::u8
	{
		inactive = 0,
		hover = 1,
		active = 2
	};
	struct rectangle_shape
	{
		ql::hitbox hitbox;
		ql::rgba background_color;

		mutable bool changed = false;
		mutable sf::RectangleShape shape;

		void set_hitbox(ql::hitbox hitbox)
		{
			this->changed = true;
			this->hitbox = hitbox;
		}

		ql::hitbox get_hitbox() const
		{
			return this->hitbox;
		}

		void set_background_color(ql::rgba color)
		{
			this->changed = true;
			this->background_color = color;
		}

		ql::rgba get_background_color() const
		{
			return this->background_color;
		}

		void update_shape() const
		{
			if (this->changed)
			{
				this->shape.setSize(this->hitbox.dimension);
				this->shape.setPosition(this->hitbox.position);
				this->shape.setFillColor(this->background_color);
				this->changed = false;
			}
		}

		void draw(ql::render& render) const
		{
			this->update_shape();
			render.draw(this->shape);
		}
	};

	template <typename T>
	concept has_hitbox = requires(T a) {
		a.set_hitbox(ql::hitbox());
		{ a.get_hitbox() } -> std::same_as<ql::hitbox>;
	};

	constexpr auto test = has_hitbox<ql::rectangle_shape>;
}	 // namespace ql

#endif