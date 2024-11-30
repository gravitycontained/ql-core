#include <ql/graphic/drawable/advanced/smooth-button/smooth-button.hpp>

#if defined QL_GRAPHIC

namespace ql
{
	void ql::smooth_button::enable_simple_hitbox()
	{
		this->simple_hitbox = true;
	}

	void ql::smooth_button::disable_simple_hitbox()
	{
		this->simple_hitbox = false;
	}

	void ql::smooth_button::set_hitbox_increase(ql::vec2 delta)
	{
		this->hitbox_increase = delta;
	}

	void ql::smooth_button::set_hitbox_increase(ql::f32 delta)
	{
		this->hitbox_increase = ql::vec(delta, delta);
	}

	void ql::smooth_button::set_color(ql::rgba color)
	{
		this->text.set_color(color);
		this->smooth_layout.set_color(color);
		this->rectangle.polygon.set_color(color);
	}

	void ql::smooth_button::set_dimension(ql::vec2 dimension)
	{
		this->smooth_layout.set_dimension(dimension);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_position(ql::vec2 position)
	{
		this->smooth_layout.set_position(position);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_hitbox(ql::hitbox hitbox)
	{
		this->smooth_layout.set_hitbox(hitbox);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_center(ql::vec2 center)
	{
		this->smooth_layout.set_center(center);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_slope(ql::f64 slope)
	{
		this->smooth_layout.set_slope(slope);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_background_color(ql::rgba color)
	{
		this->background_color = color;
		this->smooth_layout.set_color(color);
		this->rectangle.set_color(color);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_background_outline_thickness(ql::f32 thickness)
	{
		this->smooth_layout.set_outline_thickness(thickness);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_background_outline_color(ql::rgba color)
	{
		this->background_outline_color = color;
		this->smooth_layout.set_outline_color(color);
		this->rectangle.set_outline_color(color);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_background_slope_dimension(ql::vec2 dimension)
	{
		this->smooth_layout.set_slope_dimension(dimension);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_background_slope_point_count(ql::size point_count)
	{
		this->smooth_layout.set_slope_point_count(point_count);
		this->layout_changed = true;
	}

	void ql::smooth_button::set_text_font(const sf::Font& font)
	{
		this->text.set_font(font);
	}

	void ql::smooth_button::set_text_font(const std::string& font_name)
	{
		this->text.set_font(font_name);
	}

	void ql::smooth_button::set_text_style(ql::u32 style)
	{
		this->text.set_style(style);
	}

	void ql::smooth_button::set_text_character_size(ql::u32 character_size)
	{
		this->text.set_character_size(character_size);
	}

	void ql::smooth_button::set_text_color(ql::rgba color)
	{
		this->text_color = color;
		this->text.set_color(color);
	}

	void ql::smooth_button::set_text_outline_thickness(ql::f32 outline_thickness)
	{
		this->text.set_outline_thickness(outline_thickness);
	}

	void ql::smooth_button::set_text_outline_color(ql::rgba color)
	{
		this->text.set_outline_color(color);
	}

	void ql::smooth_button::set_text_rotation(ql::f32 angle)
	{
		this->text.set_rotation(angle);
	}

	void ql::smooth_button::set_text_letter_spacing(ql::f32 spacing)
	{
		this->text.set_letter_spacing(spacing);
	}

	void ql::smooth_button::set_text_position(ql::vec2 position)
	{
		this->text.set_position(position);
	}

	void ql::smooth_button::set_text_center(ql::vec2 position)
	{
		this->text.set_center(position);
	}

	void ql::smooth_button::set_text_string(const std::string& string)
	{
		this->text.set_string(string);
	}

	void ql::smooth_button::set_text_string(const std::wstring& string)
	{
		this->text.set_string(string);
	}

	void ql::smooth_button::centerize_text()
	{
		this->text.set_center(this->smooth_layout.get_center());
	}

	ql::vec2 ql::smooth_button::get_hitbox_increase() const
	{
		return this->hitbox_increase;
	}

	ql::vec2 ql::smooth_button::get_dimension() const
	{
		return this->smooth_layout.get_dimension();
	}

	ql::vec2 ql::smooth_button::get_position() const
	{
		return this->smooth_layout.get_position();
	}

	ql::vec2 ql::smooth_button::get_center() const
	{
		return this->smooth_layout.get_center();
	}

	ql::hitbox ql::smooth_button::get_hitbox() const
	{
		return this->smooth_layout.get_hitbox();
	}

	ql::f64 ql::smooth_button::get_slope() const
	{
		return this->smooth_layout.get_slope();
	}

	ql::rgba ql::smooth_button::get_background_color() const
	{
		return this->smooth_layout.get_color();
	}

	ql::f32 ql::smooth_button::get_background_outline_thickness() const
	{
		return this->smooth_layout.get_outline_thickness();
	}

	ql::rgba ql::smooth_button::get_background_outline_color() const
	{
		return this->smooth_layout.get_outline_color();
	}

	ql::vec2 ql::smooth_button::get_slope_dimension() const
	{
		return this->smooth_layout.get_slope_dimension();
	}

	ql::size ql::smooth_button::get_slope_point_count() const
	{
		return this->smooth_layout.get_slope_point_count();
	}

	std::string ql::smooth_button::get_text_font() const
	{
		return this->text.get_font();
	}

	ql::u32 ql::smooth_button::get_text_style() const
	{
		return this->text.get_style();
	}

	ql::u32 ql::smooth_button::get_text_character_size() const
	{
		return this->text.get_character_size();
	}

	ql::rgba ql::smooth_button::get_text_color() const
	{
		return this->text.get_color();
	}

	ql::f32 ql::smooth_button::get_text_outline_thickness() const
	{
		return this->text.get_outline_thickness();
	}

	ql::rgba ql::smooth_button::get_text_outline_color() const
	{
		return this->text.get_outline_color();
	}

	ql::f32 ql::smooth_button::get_text_letter_spacing() const
	{
		return this->text.get_letter_spacing();
	}

	ql::vec2 ql::smooth_button::get_text_position() const
	{
		return this->text.get_visible_hitbox().position;
	}

	ql::vec2 ql::smooth_button::get_text_center() const
	{
		return this->text.get_visible_hitbox().get_center();
	}

	std::string ql::smooth_button::get_text_string() const
	{
		return this->text.get_string();
	}

	std::wstring ql::smooth_button::get_text_wstring() const
	{
		return this->text.get_wstring();
	}

	bool ql::smooth_button::is_hovering() const
	{
		return this->hovering;
	}

	bool ql::smooth_button::is_clicked() const
	{
		return this->clicked;
	}

	void ql::smooth_button::update(const ql::event_manager& event)
	{
		this->create_check();
		if (this->simple_hitbox)
		{
			this->hovering = this->rectangle.get_hitbox().increased(5).collides(event.mouse_position());
		}
		else
		{
			this->hovering = this->rectangle.contains(event.mouse_position());
		}
		this->clicked = this->hovering && event.left_mouse_clicked();

		if (this->clicked)
		{
			this->clicked_once = true;
			this->click_timer.reset();
		}

		ql::rgba text_color_effect = this->text_color;
		if (this->use_basic_hover_animation)
		{
			if (this->hovering && !this->hover_before)
			{
				this->hover_animation.go_forwards();
			}
			else if (!this->hovering && this->hover_before)
			{
				this->hover_animation.go_backwards();
			}
			this->hover_before = this->hovering;

			this->hover_animation.update(event.frame_time_f());
			if (this->hover_animation.is_running())
			{
				auto progress = this->hover_animation.get_curve_progress();

				auto color = this->background_color;
				color.interpolate(this->background_color_hover, progress);
				this->smooth_layout.set_color(color);

				color = this->background_outline_color;
				color.interpolate(color.inverted(), progress);
				this->smooth_layout.set_outline_color(color);

				color = this->text_color;
				color.interpolate(this->text_color_hover, progress);

				text_color_effect = color;
				this->text.set_color(color);
				this->layout_changed = true;
			}
		}

		if (this->clicked_once && this->click_timer.elapsed_f() < 1.5)
		{
			auto progress = ql::slope_curve(this->click_timer.elapsed_f() / 1.5, 1.0);
			this->text.set_color(text_color_effect.interpolated(this->text_color_click, 1.0 - progress));
		}
	}

	void ql::smooth_button::create_check() const
	{
		if (this->layout_changed)
		{
			this->rectangle = this->smooth_layout;
			this->layout_changed = false;
		}
	}

	void ql::smooth_button::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->create_check();
		this->rectangle.draw(window, states);
		this->text.draw(window, states);
	}

}	 // namespace ql

#endif