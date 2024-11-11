#include <ql/graphic/old-drawable/ui-controls.hpp>

#if defined QL_GRAPHIC

#include <ql/core/definition/definition.hpp>
#include <ql/core/system/system.hpp>
#include <ql/core/transform/interpolate/interpolate.hpp>
#include <ql/core/transform/cast/cast.hpp>
#include <ql/graphic/resources/resources.hpp>

namespace ql
{
	namespace detail
	{
		ql::button ql::detail::button;
	}

	ql::vec2 ql::vbutton::get_position() const
	{
		return this->background.position;
	}

	void ql::vbutton::set_dimension(ql::vec2 dimension)
	{
		this->background.dimension = dimension;
	}

	void ql::vbutton::set_position(ql::vec2 position)
	{
		this->background.position = position;
	}

	void ql::vbutton::set_center(ql::vec2 center)
	{
		this->background.set_center(center);
	}

	void ql::vbutton::set_background_color(ql::rgba color)
	{
		this->background.set_color(color);
		this->background_color = color;
	}

	void ql::vbutton::set_hover_background_color(ql::rgba color)
	{
		this->hover_background_color = color;
	}

	void ql::vbutton::set_text_color(ql::rgba color)
	{
		this->text.set_color(color);
		this->text_color = color;
	}

	void ql::vbutton::set_hover_text_color(ql::rgba color)
	{
		this->hover_text_color = color;
	}

	void ql::vbutton::set_text_font(std::string font)
	{
		this->text.set_font(font);
	}

	void ql::vbutton::set_text_character_size(ql::u32 character_size)
	{
		this->text.set_character_size(character_size);
	}

	void ql::vbutton::set_text_style(ql::u32 character_style)
	{
		this->text.set_style(character_style);
	}

	void ql::vbutton::set_text(std::string text)
	{
		this->text.set_string(text);
	}

	void ql::vbutton::centerize_text()
	{
		this->text.set_position(this->background.get_center());
	}

	bool ql::vbutton::is_hovering() const
	{
		return this->hovering;
	}

	bool ql::vbutton::is_clicked() const
	{
		return this->clicked;
	}

	void ql::vbutton::update(const event_manager& event_manager)
	{
		auto pos = event_manager.mouse_position();

		auto new_hovering = this->background.contains(pos);
		if (new_hovering != this->hovering)
		{
			if (new_hovering)
			{
				if (this->hover_background_color.is_unset())
				{
					this->background.set_color(this->background_color.inverted());
				}
				else
				{
					this->background.set_color(this->hover_background_color);
				}
				if (this->hover_text_color.is_unset())
				{
					this->text.set_color(this->text_color.inverted());
				}
				else
				{
					this->text.set_color(this->hover_text_color);
				}
			}
			else
			{
				this->background.set_color(this->background_color);
				this->text.set_color(this->text_color);
			}
		}

		this->hovering = new_hovering;

		this->clicked = this->hovering && event_manager.left_mouse_clicked();
	}

	void ql::vbutton::set_text_alpha(ql::u8 alpha)
	{
		this->text_alpha = alpha;
	}

	void ql::vbutton::set_background_alpha(ql::u8 alpha)
	{
		this->background_alpha = alpha;
	}

	void ql::vbutton::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::button = *this;
		ql::detail::button.draw(window, states);
	}

	ql::vbutton& ql::vbutton::operator=(const ql::vbutton& button)
	{
		this->outline_on_hover = button.outline_on_hover;
		this->invert_on_hover = button.invert_on_hover;
		this->text_color = button.text_color;
		this->hover_background_color = button.hover_background_color;
		this->background_color = button.background_color;
		this->text = button.text;
		this->background = button.background;
		this->hovering = button.hovering;
		this->clicked = button.clicked;
		this->background_alpha = button.background_alpha;
		this->text_alpha = button.text_alpha;
		return *this;
	}

	void ql::button::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->background.draw(window, states);
		this->text.draw(window, states);
	}

	ql::button& ql::button::operator=(const ql::vbutton& button)
	{
		this->background = button.background;
		this->background.set_color(button.background.get_color());

		this->text = button.text;
		this->text.set_color(button.text.color);

		this->text.set_center(this->background.center());
		return *this;
	}

	void ql::button::set_dimension(ql::vec2 dimension)
	{
		this->background.set_dimension(dimension);
	}

	void ql::button::set_position(ql::vec2 position)
	{
		this->background.set_position(position);
	}

	void ql::button::set_center(ql::vec2 center)
	{
		this->background.set_center(center);
	}

	void ql::button::set_background_color(ql::rgba color)
	{
		this->background.set_color(color);
		this->background_color = color;
	}

	void ql::button::set_hover_background_color(ql::rgba color)
	{
		this->hover_background_color = color;
	}

	void ql::button::set_text_color(ql::rgba color)
	{
		this->text.set_color(color);
		this->text_color = color;
	}

	void ql::button::set_text_font(std::string font)
	{
		this->text.set_font(font);
	}

	void ql::button::set_text_character_size(ql::u32 character_size)
	{
		this->text.set_character_size(character_size);
	}

	void ql::button::set_text_style(ql::u32 character_style)
	{
		this->text.set_style(character_style);
	}

	void ql::button::set_text_string(std::string text)
	{
		this->text.set_string(text);
	}

	void ql::button::set_text_string(std::wstring text)
	{
		this->text.set_string(text);
	}

	ql::vec2 ql::button::get_dimension() const
	{
		return this->background.get_dimension();
	}

	ql::vec2 ql::button::get_position() const
	{
		return this->background.get_position();
	}

	ql::vec2 ql::button::get_center() const
	{
		return this->background.get_center();
	}

	ql::rgba ql::button::get_background_color() const
	{
		return this->background_color;
	}

	ql::rgba ql::button::get_hover_background_color() const
	{
		return this->hover_background_color;
	}

	ql::rgba ql::button::get_text_color() const
	{
		return this->text_color;
	}

	std::string ql::button::get_text_font() const
	{
		return this->text.get_font();
	}

	ql::u32 ql::button::get_text_character_size() const
	{
		return this->text.get_character_size();
	}

	ql::u32 ql::button::get_text_style() const
	{
		return this->text.get_style();
	}

	std::string ql::button::get_text_string() const
	{
		return this->text.get_string();
	}

	std::wstring ql::button::get_text_wstring() const
	{
		return this->text.get_wstring();
	}

	void ql::button::centerize_text()
	{
		this->text.set_center(this->background.center());
	}

	bool ql::button::is_hovering() const
	{
		return this->hovering;
	}

	bool ql::button::is_clicked() const
	{
		return this->clicked;
	}

	void ql::button::update(const event_manager& event_manager)
	{
		auto pos = event_manager.mouse_position();

		auto new_hovering = this->background.contains(pos);
		if (new_hovering != this->hovering)
		{
			if (this->invert_on_hover)
			{
				if (new_hovering)
				{
					this->background.set_color(this->background_color.inverted());
					this->text.set_color(this->text_color.inverted());
				}
				else
				{
					this->background.set_color(this->background_color);
					this->text.set_color(this->text_color);
				}
			}
			else
			{
				if (new_hovering)
				{
					this->background.set_color(this->hover_background_color);
				}
				else
				{
					this->background.set_color(this->background_color);
				}
			}
		}

		this->hovering = new_hovering;

		this->clicked = this->hovering && event_manager.left_mouse_clicked();
	}

	void ql::button::update(const event_manager& event_manager, bool& hovering)
	{
		this->update(event_manager);
		hovering = hovering || this->hovering;
	}

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
			this->hovering = this->rectangle.get_hitbox().increased(5).contains(event.mouse_position());
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
			auto progress = ql::curve_slope(this->click_timer.elapsed_f() / 1.5, 1.0);
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

	void ql::text_field::line::apply(ql::vtext layout)
	{
		this->text.set_font(layout.font_name);
		this->text.set_character_size(layout.character_size);
		this->text.set_color(layout.color);
		this->text.set_outline_color(layout.outline_color);
		this->text.set_outline_thickness(layout.outline_thickness);
		this->text.set_style(layout.style);
	}

	void ql::text_field::line::calculate_hitboxes()
	{
		this->character_hitboxes = this->text.get_all_characters_hitbox_whitespace_included();
		if (this->character_hitboxes.empty())
		{
			this->character_hitboxes.push_back({});

			this->character_hitboxes.back().position =
					this->text.get_starting_line_position() + ql::vec(this->text.get_character_size() / 15.0f, 0);
			this->character_hitboxes.back().dimension = this->text.get_character_dimension(L'x');
		}
		this->line_hitbox.position = this->text.get_position();
		this->line_hitbox.position.x = this->text.get_starting_line_position().x;
		this->line_hitbox.dimension.y = this->text.get_line_spacing();
		this->line_hitbox.dimension.x =
				((this->character_hitboxes.back().dimension + this->character_hitboxes.back().position) - this->line_hitbox.position).x;
	}

	void ql::text_field::line::calculate_mouse_hitboxes(ql::f32 max_line_x, ql::f32 extended_line_width)
	{
		this->character_mouse_hitboxes.resize(this->character_hitboxes.size() + 1u);

		ql::f32 y = this->text.get_starting_line_position().y - this->text.get_delta_underline();
		ql::f32 height = this->text.get_line_spacing();

		ql::f32 first_x = this->line_hitbox.dimension.x + this->line_hitbox.position.x;
		ql::f32 last_x = first_x;
		for (ql::size i = 0u; i < this->character_hitboxes.size() - 1; ++i)
		{
			ql::f32 x = this->character_hitboxes[i].get_center().x;
			ql::f32 width = this->character_hitboxes[i + 1].get_center().x - x;

			if (i == 0u)
			{
				first_x = x;
			}
			last_x = x + width;

			ql::hitbox hitbox;
			hitbox.position = ql::vec(x, y);
			hitbox.dimension = ql::vec(width, height);
			this->character_mouse_hitboxes[i + 1] = hitbox;
		}

		auto& front = this->character_mouse_hitboxes.front();
		auto& back = this->character_mouse_hitboxes.back();

		ql::hitbox hitbox;
		hitbox.position = ql::vec(this->line_hitbox.position.x, y);
		hitbox.dimension = ql::vec(first_x - this->line_hitbox.position.x, height);
		hitbox.extend_left(extended_line_width);
		front = hitbox;
		hitbox.position = ql::vec(last_x, y);
		hitbox.dimension = ql::vec(max_line_x - last_x, height);
		hitbox.extend_right(extended_line_width);
		back = hitbox;

		this->line_mouse_hitbox.position = front.position;
		this->line_mouse_hitbox.dimension = (back.position + back.dimension) - front.position;
	}

	void ql::text_field::line::move(ql::vec2 delta)
	{
		this->text.move(delta);
		this->line_hitbox.move(delta);
		this->line_mouse_hitbox.move(delta);
		for (auto& i : this->character_hitboxes)
		{
			i.move(delta);
		}
		for (auto& i : this->character_mouse_hitboxes)
		{
			i.move(delta);
		}
	}

	void ql::text_field::line::move(ql::f32 x, ql::f32 y)
	{
		this->move(ql::vec(x, y));
	}

	std::wstring ql::text_field::line::wstring() const
	{
		return this->text.get_wstring();
	}

	void ql::text_field::line::draw(ql::render& draw) const
	{
		// ql::rectangle rect;
		// for (ql::size i = 0u; i < this->character_mouse_hitboxes.size(); ++i) {
		//	ql::rgba color = ql::rgba::yellow;
		//	if (i % 2 == 0u) {
		//		color = ql::rgba::cyan;
		//	}
		//	rect.set_hitbox(this->character_mouse_hitboxes[i]);
		//	rect.set_color(color.with_alpha(50));
		//	draw.draw(rect);
		// }

		draw.draw(this->text);
	}

	ql::text_field::text_field()
	{
		this->set_dimension(ql::vec(300, 50));
		this->set_background_color(ql::rgba::grey_shade(30));
		this->set_background_outline_color(ql::rgba::grey_shade(220));
		this->set_background_outline_thickness(1.0f);
		this->reset();
	}

	void ql::text_field::reset()
	{
		this->lines.resize(1u);
		this->set_string_stack_size(10u);
		for (auto& i : this->lines)
		{
			i.layout_changed = true;
		}
	}

	void ql::text_field::set_font(std::string font)
	{
		this->text_layout.set_font(font);
		this->text_layout_changed = true;
		for (auto& line : this->lines)
		{
			line.layout_changed = true;
		}
		if (this->lines.size() == 1u)
		{
			if (this->lines.front().wstring().empty())
			{
				this->set_string(L"");
			}
		}
	}

	void ql::text_field::set_text_character_size(ql::u32 character_size)
	{
		this->text_layout.set_character_size(character_size);
		this->text_layout_changed = true;
		for (auto& line : this->lines)
		{
			line.layout_changed = true;
		}
	}

	void ql::text_field::set_text_style(ql::u32 style)
	{
		this->text_layout.set_style(style);
		this->text_layout_changed = true;
		for (auto& line : this->lines)
		{
			line.layout_changed = true;
		}
	}

	void ql::text_field::set_text_outline_thickness(ql::f32 outline_thickness)
	{
		this->text_layout.set_outline_thickness(outline_thickness);
		this->text_layout_changed = true;
		for (auto& line : this->lines)
		{
			line.layout_changed = true;
		}
	}

	void ql::text_field::set_text_outline_color(ql::rgba outline_color)
	{
		this->text_layout.set_outline_color(outline_color);
		this->text_layout_changed = true;
		for (auto& line : this->lines)
		{
			line.layout_changed = true;
		}
	}

	void ql::text_field::set_text_color(ql::rgba color)
	{
		this->text_layout.set_color(color);
		this->text_layout_changed = true;
		for (auto& line : this->lines)
		{
			line.layout_changed = true;
		}
	}

	ql::hitbox ql::text_field::get_hitbox() const
	{
		this->internal_update();
		ql::hitbox result;
		result.position = this->lines.front().line_hitbox.position;

		ql::f32 x = 0.0f;
		for (ql::size i = 0u; i < this->lines.size(); ++i)
		{
			x = ql::max(x, this->lines[i].line_hitbox.dimension.x);
		}

		auto y = (this->lines.back().line_hitbox.position.y + this->lines.back().text.get_line_height()) - result.position.y;
		result.dimension = ql::vec(x, y);
		return result;
	}

	ql::hitbox ql::text_field::get_background_hitbox() const
	{
		return this->background.get_hitbox();
	}

	void ql::text_field::set_background_increase(ql::vec2 increase)
	{
		this->background_increase = increase;
	}

	void ql::text_field::set_background_increase(ql::f32 increase)
	{
		this->background_increase = ql::vec(increase, increase);
	}

	void ql::text_field::set_background_outline_thickness(ql::f32 thickness)
	{
		this->background.set_outline_thickness(thickness);
	}

	void ql::text_field::set_background_outline_color(ql::rgba color)
	{
		this->background.set_outline_color(color);
	}

	ql::rgba ql::text_field::get_background_color() const
	{
		return this->background.get_color();
	}

	ql::rgba ql::text_field::get_background_outline_color() const
	{
		return this->background.get_outline_color();
	}

	ql::f32 ql::text_field::get_background_outline_thickness() const
	{
		return this->background.get_outline_thickness();
	}

	void ql::text_field::set_background_color(ql::rgba color)
	{
		this->background.set_color(color);
	}

	ql::vec2 ql::text_field::get_background_increase() const
	{
		return this->background_increase;
	}

	void ql::text_field::set_minimum_dimension(ql::vec2 dimension)
	{
		this->minimum_dimension = dimension;
		this->update_required = true;
	}

	void ql::text_field::set_minimum_width(ql::f32 width)
	{
		this->minimum_dimension.x = width;
		this->update_required = true;
	}

	void ql::text_field::set_minimum_height(ql::f32 height)
	{
		this->minimum_dimension.y = height;
		this->update_required = true;
	}

	void ql::text_field::set_maximum_dimension(ql::vec2 dimension)
	{
		this->maximum_dimension = dimension;
		this->update_required = true;
	}

	void ql::text_field::set_maximum_width(ql::f32 width)
	{
		this->minimum_dimension.x = width;
		this->update_required = true;
	}

	void ql::text_field::set_maximum_height(ql::f32 height)
	{
		this->minimum_dimension.y = height;
		this->update_required = true;
	}

	void ql::text_field::set_fixed_dimension(ql::vec2 dimension)
	{
		this->minimum_dimension = this->maximum_dimension = dimension;
		this->update_required = true;
	}

	void ql::text_field::set_fixed_width(ql::f32 width)
	{
		this->minimum_dimension.x = this->maximum_dimension.x = width;
		this->update_required = true;
	}

	void ql::text_field::set_fixed_height(ql::f32 height)
	{
		this->minimum_dimension.y = this->maximum_dimension.y = height;
		this->update_required = true;
	}

	void ql::text_field::set_position(ql::vec2 position)
	{
		auto delta = position - this->hitbox.position;
		this->move(delta);
	}

	void ql::text_field::set_dimension(ql::vec2 dimension)
	{
		this->hitbox.set_dimension(dimension);
		this->update_required = true;
	}

	void ql::text_field::set_hitbox(ql::hitbox hitbox)
	{
		this->set_dimension(hitbox.dimension);
		this->set_position(hitbox.position);
	}

	void ql::text_field::move(ql::vec2f delta)
	{
		this->hitbox.move(delta);

		for (auto& i : this->lines)
		{
			i.move(delta);
		}
		for (auto& i : this->selection_rectangles)
		{
			i.move(delta);
		}
		this->update_required = true;
		this->internal_update();
	}

	void ql::text_field::set_string(std::wstring string)
	{
		this->internal_update_text();

		auto split = ql::string_split_allow_empty(string, L'\n');

		ql::size size = split.size();
		if (size == 0u)
		{
			this->lines.resize(1u);
			this->lines.front().apply(this->text_layout);
			this->lines.front().text.set_string(L"");
			this->lines.front().calculate_hitboxes();
			this->lines.front().mouse_hitboxes_changed = true;
			this->text_mouse_hitboxes_changed = true;
			return;
		}
		auto size_before = this->lines.size();
		this->lines.resize(split.size());
		for (ql::size i = size_before; i < size; ++i)
		{
			this->lines[i].apply(this->text_layout);
		}

		auto pos = this->hitbox.position;
		for (ql::size i = 0u; i < size; ++i)
		{
			auto diff = pos - this->lines[i].text.get_position();
			this->lines[i].move(diff);
			this->lines[i].text.set_string(split[i]);
			this->lines[i].calculate_hitboxes();
			this->lines[i].mouse_hitboxes_changed = true;
			this->text_mouse_hitboxes_changed = true;
			pos.y += this->get_line_height();
		}
		this->whole_string_changed = true;
		this->update_required = true;
	}

	void ql::text_field::set_string(std::string string)
	{
		this->set_string(ql::string_to_wstring(string));
	}

	ql::text_field::line& ql::text_field::get_line_at_cursor()
	{
		return this->lines[this->cursor_position.y];
	}

	const ql::text_field::line& ql::text_field::get_line_at_cursor() const
	{
		return this->lines[this->cursor_position.y];
	}

	std::wstring ql::text_field::get_selection_wstring() const
	{
		auto [begin, end] = this->get_sorted_selection_range();
		if (begin == end)
		{
			return L"";
		}

		if (begin.y == end.y)
		{
			auto str = this->lines[begin.y].wstring();
			return str.substr(begin.x, end.x - begin.x);
		}
		else
		{
			std::wstring result;
			for (ql::size y = begin.y; y <= end.y; ++y)
			{
				if (y == begin.y)
				{
					result += this->lines[y].wstring().substr(begin.x);
				}
				else if (y == end.y)
				{
					result += L"\n";
					result += this->lines[y].wstring().substr(0u, end.x);
				}
				else
				{
					result += L"\n";
					result += this->lines[y].wstring();
				}
			}
			return result;
		}
	}

	std::string ql::text_field::get_selection_string() const
	{
		return ql::wstring_to_string(this->get_selection_wstring());
	}

	void ql::text_field::add_string_at_cursor(std::wstring string)
	{
		auto split = ql::string_split_allow_empty(string, L'\n');

		for (ql::size i = 0u; i < split.size(); ++i)
		{
			if (i)
			{
				this->new_line(this->cursor_position.y);
			}

			if (split[i].size() && split[i].back() == L'\r')
			{
				split[i].pop_back();
			}

			auto& line = this->get_line_at_cursor();
			auto str = line.text.get_wstring();
			std::wstring new_string;
			new_string += str.substr(0u, this->cursor_position.x);
			new_string += split[i];
			if (this->cursor_position.x < str.length())
			{
				new_string += str.substr(this->cursor_position.x);
			}
			line.text.set_string(new_string);
			line.calculate_hitboxes();
			line.mouse_hitboxes_changed = true;

			this->cursor_position.x += split[i].length();
		}

		this->whole_string_changed = true;
		this->text_mouse_hitboxes_changed = true;
		this->update_required = true;
		this->internal_update();
		this->cursor_position_changed = true;
		this->cursor_interval_timer.reset();
	}

	void ql::text_field::enable_focus()
	{
		this->focus = true;
	}

	void ql::text_field::disable_focus()
	{
		this->focus = false;
	}

	void ql::text_field::enable_one_line_limit()
	{
		this->line_limit = 1u;
	}

	void ql::text_field::set_line_limit(ql::size limit)
	{
		this->line_limit = limit;
	}

	void ql::text_field::disable_one_line_limit()
	{
		this->line_limit = ql::size_max;
	}

	void ql::text_field::set_string_stack_size(ql::size size)
	{
		this->string_stack.resize(size);
		this->string_stack.front().first = this->wstring();
		this->string_stack.front().second = this->cursor_position;
	}

	ql::size ql::text_field::get_string_stack_size() const
	{
		return this->string_stack.size();
	}

	ql::f32 ql::text_field::get_line_height() const
	{
		return this->lines.front().text.get_line_height();
	}

	bool ql::text_field::is_hovering() const
	{
		return this->hovering;
	}

	bool ql::text_field::just_edited_text() const
	{
		return this->edited_text;
	}

	bool ql::text_field::just_copied_text() const
	{
		return this->copied_text;
	}

	bool ql::text_field::just_pasted_text() const
	{
		return this->pasted_text;
	}

	bool ql::text_field::just_entered_text() const
	{
		return this->entered_text;
	}

	bool ql::text_field::just_finished_text() const
	{
		return this->finished_text;
	}

	bool ql::text_field::has_focus() const
	{
		return this->focus;
	}

	std::wstring ql::text_field::wstring() const
	{
		if (this->whole_string_changed)
		{
			this->whole_string = L"";
			for (ql::size i = 0u; i < this->lines.size(); ++i)
			{
				if (i)
				{
					this->whole_string += L"\n";
				}
				this->whole_string += this->lines[i].wstring();
			}
			this->whole_string_changed = false;
		}
		return this->whole_string;
	}

	std::string ql::text_field::string() const
	{
		return ql::wstring_to_string(this->wstring());
	}

	std::string ql::text_field::get_font() const
	{
		return this->text_layout.font_name;
	}

	bool ql::text_field::is_font_set() const
	{
		return !this->text_layout.font_name.empty();
	}

	void ql::text_field::new_line(ql::size y)
	{
		if (y == ql::size_max)
		{
			y = this->lines.size() - 1;
		}

		auto pos = this->hitbox.position;
		pos.y += this->get_line_height() * (y + 1);

		auto current_str = this->lines[y].wstring();
		this->lines[y].text.set_string(current_str.substr(0u, this->cursor_position.x));
		this->lines[y].calculate_hitboxes();

		ql::text_field::line line;
		line.apply(this->text_layout);
		line.text.set_string(current_str.substr(this->cursor_position.x));
		line.text.set_position(pos);
		line.calculate_hitboxes();
		line.mouse_hitboxes_changed = true;
		this->text_mouse_hitboxes_changed = true;
		this->whole_string_changed = true;

		this->lines.push_back({});

		for (ql::isize i = ql::signed_cast(this->lines.size()) - 1; i > ql::signed_cast(y + 1); --i)
		{
			this->lines[i] = this->lines[i - 1];

			this->lines[i].move(0.0, this->get_line_height());
		}
		this->lines[y + 1] = line;

		this->cursor_position.x = 0u;
		++this->cursor_position.y;

		this->update_required = true;
		this->internal_update();
	}

	bool ql::text_field::is_dragging_selection_considering_cooldown() const
	{
		return this->dragging_selection && this->selection_start_drag_timer.elapsed_f() > this->selection_start_drag_timer_duration;
	}

	void ql::text_field::delete_at_cursor()
	{
		auto& line = this->get_line_at_cursor();
		auto str = line.wstring();

		if (this->cursor_position.x == 0u)
		{
			if (this->cursor_position.y)
			{
				auto& line_before = this->lines[this->cursor_position.y - 1];

				auto new_cursor_x = line_before.wstring().length();

				auto new_string = line_before.wstring();
				new_string += str;

				line_before.text.set_string(new_string);
				line_before.calculate_hitboxes();
				line.mouse_hitboxes_changed = true;
				this->text_mouse_hitboxes_changed = true;
				this->whole_string_changed = true;

				for (ql::size i = this->cursor_position.y; i < this->lines.size() - 1; ++i)
				{
					this->lines[i] = this->lines[i + 1];
					this->lines[i].move(0.0, -this->get_line_height());
				}
				this->lines.pop_back();

				--this->cursor_position.y;
				this->cursor_position.x = new_cursor_x;
			}
		}
		else
		{
			std::wstring new_string;
			new_string += str.substr(0u, this->cursor_position.x - 1);
			if (this->cursor_position.x != str.length())
			{
				new_string += str.substr(this->cursor_position.x);
			}
			line.text.set_string(new_string);
			line.calculate_hitboxes();
			line.mouse_hitboxes_changed = true;
			this->text_mouse_hitboxes_changed = true;
			this->whole_string_changed = true;

			--this->cursor_position.x;
		}

		this->cursor_interval_timer.reset();
		this->update_required = true;
		this->internal_update();
	}

	void ql::text_field::delete_selection_string(bool update_cursor_position)
	{
		auto [begin, end] = this->get_sorted_selection_range();

		if (begin == end)
		{
			return;
		}

		if (begin.y == end.y)
		{
			auto& line = this->lines[begin.y];
			auto str = line.wstring();
			line.text.set_string(str.substr(0u, begin.x) + str.substr(end.x));
			line.calculate_hitboxes();
			line.calculate_mouse_hitboxes(this->hitbox.dimension.x + this->hitbox.position.x, this->background_increase.x);
		}
		else
		{
			auto& first_line = this->lines[begin.y];
			auto& last_line = this->lines[end.y];

			auto first_str = first_line.wstring().substr(0u, begin.x);
			auto last_str = last_line.wstring().substr(end.x);

			first_line.text.set_string(first_str + last_str);
			first_line.calculate_hitboxes();
			first_line.calculate_mouse_hitboxes(this->hitbox.dimension.x + this->hitbox.position.x, this->background_increase.x);

			auto remove = end.y - begin.y;
			for (ql::size i = 1u;; ++i)
			{
				auto index1 = i + begin.y;
				auto index2 = index1 + remove;
				if (index2 >= this->lines.size())
				{
					break;
				}
				this->lines[index1] = this->lines[index2];
				this->lines[index1].move(0.0, -this->get_line_height() * remove);
			}
			this->lines.resize(this->lines.size() - remove);
		}
		this->update_required = true;
		this->text_mouse_hitboxes_changed = true;
		this->whole_string_changed = true;
		this->text_layout_changed = true;

		if (update_cursor_position)
		{
			bool larger = (this->cursor_position.y > end.y || (this->cursor_position.y == end.y && this->cursor_position.x > end.x));
			bool smaller =
					(this->cursor_position.y < begin.y || (this->cursor_position.y == begin.y && this->cursor_position.x < begin.x));

			if (larger && !smaller)
			{
				auto diff = ql::vector2<ql::isize>(this->cursor_position) - ql::vector2<ql::isize>(begin);
				if (this->cursor_position.y == end.y)
				{
					this->cursor_position.x = begin.x + (this->cursor_position.x - end.x);
				}
				this->cursor_position.y -= (end.y - begin.y);
			}
			else if (!smaller && !larger)
			{
				this->cursor_position = begin;
			}
			this->cursor_position_changed = true;
		}
		this->internal_update();
		this->delete_selection_range();
		this->make_selection_rectangles();
	}

	void ql::text_field::delete_selection_range()
	{
		this->selection_a = this->selection_b = this->cursor_position;
	}

	void ql::text_field::move_cursor_up()
	{
		if (!this->cursor_position.y)
		{
			return;
		}
		--this->cursor_position.y;
		this->find_closest_cursor_position();
		this->cursor_interval_timer.reset();
	}

	void ql::text_field::move_cursor_down()
	{
		if (this->cursor_position.y == this->lines.size() - 1)
		{
			return;
		}

		++this->cursor_position.y;
		this->find_closest_cursor_position();
		this->cursor_interval_timer.reset();
	}

	void ql::text_field::move_cursor_left()
	{
		if (this->cursor_position.x == 0u)
		{
			if (this->cursor_position.y)
			{
				--this->cursor_position.y;
				this->cursor_position.x = this->get_line_at_cursor().wstring().length();
			}
		}
		else
		{
			--this->cursor_position.x;
		}

		this->cursor_interval_timer.reset();
		this->cursor_position_changed = true;
	}

	void ql::text_field::move_cursor_right()
	{
		const auto& line = this->get_line_at_cursor();
		if (this->cursor_position.x == line.wstring().length())
		{
			if (this->cursor_position.y < this->lines.size() - 1)
			{
				++this->cursor_position.y;
				this->cursor_position.x = 0u;
			}
		}
		else
		{
			++this->cursor_position.x;
		}

		this->cursor_interval_timer.reset();
		this->cursor_position_changed = true;
	}

	void ql::text_field::update_cursor()
	{
		auto elapsed = this->cursor_interval_timer.elapsed_f();
		auto delta = std::fmod(elapsed, this->cursor_interval_duration);

		ql::rgba color = ql::rgba::white();
		if (this->is_dragging_selection_considering_cooldown())
		{
			color = ql::rgb::yellow();
		}
		if (delta > this->cursor_blink_duration)
		{
			color.a = 0;
		}
		this->cursor.set_color(color);
	}

	void ql::text_field::update_selection_rectangles()
	{
		if (this->is_dragging_selection_considering_cooldown() && !this->dragging_selection_before)
		{
			ql::rgba color = this->dragging_color;
			color.a = this->selection_color.a;
			for (auto& i : this->selection_rectangles)
			{
				i.set_color(color);
			}
		}
		else if (!this->dragging_selection && this->dragging_selection_before)
		{
			ql::rgba color = this->selection_color;
			for (auto& i : this->selection_rectangles)
			{
				i.set_color(color);
			}
		}
	}

	void ql::text_field::update_mouse_events(const ql::event_manager& event)
	{
		auto max = ql::vec2::max_values(this->hovering_increase, this->background_increase);
		this->hovering = this->hitbox.increased(max).contains(event.mouse_position());

		bool selection_hovering = false;
		for (auto& i : this->selection_rectangles)
		{
			if (i.contains(event.mouse_position()))
			{
				selection_hovering = true;
				break;
			}
		}
		if (event.left_mouse_clicked() && !selection_hovering)
		{
			if (this->hovering && !this->focus)
			{
				this->cursor_interval_timer.reset();
			}
			else if (!this->hovering && this->focus)
			{
				this->delete_selection_range();
				this->make_selection_rectangles();
				selection_hovering = false;
			}
			this->focus = this->hovering;
		}

		bool delayed_click = false;
		if (selection_hovering && this->focus && event.left_mouse_fast_clicked())
		{
			bool reset = false;

			if (this->double_click_cooldown.is_running() && this->double_click_cooldown.elapsed_f() > 0.3)
			{
				reset = true;
			}
			if (reset)
			{
				this->delete_selection_range();
				this->make_selection_rectangles();
				selection_hovering = false;
				delayed_click = true;
			}
		}

		if (!this->focus)
		{
			this->dragging = false;
		}

		bool stop = false;

		if (this->hovering && (event.left_mouse_clicked() || delayed_click))
		{
			if (selection_hovering)
			{
				if (this->selection_start_drag_timer.elapsed_f() > this->selection_start_drag_timer_duration)
				{
					this->selection_drag_timer.reset();
					this->dragging_selection = true;
				}
			}
			else
			{
				for (ql::size y = 0u; !stop && y < this->lines.size(); ++y)
				{
					const auto& line = this->lines[y];
					if (line.line_mouse_hitbox.contains(event.mouse_position()))
					{
						for (ql::size x = 0u; x < line.character_mouse_hitboxes.size(); ++x)
						{
							if (line.character_mouse_hitboxes[x].contains(event.mouse_position()))
							{
								this->cursor_position = ql::vec(x, y);

								if (this->lines[y].wstring().empty())
								{
									this->cursor_position.x = 0u;
								}

								this->delete_selection_range();
								this->selection_rectangles.clear();
								this->click_mouse_position = event.mouse_position();
								this->dragging = true;
								this->cursor_interval_timer.reset();
								this->cursor_position_changed = true;
								stop = true;
								break;
							}
						}
					}
				}
			}
		}

		if (event.left_mouse_clicked())
		{
			this->selection_start_drag_timer.reset();
		}

		if ((this->dragging || this->dragging_selection) && event.mouse_moved())
		{
			bool found = false;

			auto before = this->selection_b;

			for (ql::size y = 0u; !found && y < this->lines.size(); ++y)
			{
				const auto& line = this->lines[y];
				if (line.line_mouse_hitbox.contains(event.mouse_position()))
				{
					for (ql::size x = 0u; x < line.character_mouse_hitboxes.size(); ++x)
					{
						if (line.character_mouse_hitboxes[x].contains(event.mouse_position()))
						{
							this->cursor_position = ql::vec(x, y);

							if (line.wstring().empty())
							{
								this->cursor_position.x = 0u;
							}

							if (!this->dragging_selection)
							{
								this->selection_b = this->cursor_position;
							}
							this->cursor_interval_timer.reset();
							this->cursor_position_changed = true;
							found = true;
							break;
						}
					}
				}
			}

			if (!found)
			{
				if (event.mouse_position().x > this->hitbox.get_bottom_right().x ||
						event.mouse_position().y > this->hitbox.get_bottom_right().y)
				{
					if (!this->dragging_selection)
					{
						this->selection_b.y = this->lines.size() - 1;
						this->selection_b.x = this->lines.back().wstring().length();
					}
					this->cursor_position = this->selection_b;
					this->cursor_interval_timer.reset();
					this->cursor_position_changed = true;
				}
				else if (event.mouse_position().x < this->hitbox.get_top_left().x ||
								 event.mouse_position().y < this->hitbox.get_top_left().y)
				{
					if (!this->dragging_selection)
					{
						this->selection_b = ql::vec(0u, 0u);
					}
					this->cursor_position = this->selection_b;
					this->cursor_interval_timer.reset();
					this->cursor_position_changed = true;
				}
			}

			if (this->selection_b != before)
			{
				this->make_selection_rectangles();
			}
		}

		if (event.left_mouse_released())
		{
			this->dragging = false;

			if (this->is_dragging_selection_considering_cooldown() && !selection_hovering)
			{
				auto str = this->get_selection_wstring();

				this->delete_selection_string();
				this->delete_selection_range();
				this->make_selection_rectangles();
				this->edited_text = true;
				this->update_required = true;
				this->text_mouse_hitboxes_changed = true;
				this->whole_string_changed = true;
				this->text_layout_changed = true;
				this->internal_update();
				this->add_string_at_cursor(str);
			}
			this->dragging_selection = false;
		}

		if (!this->focus)
		{
			return;
		}

		auto fast_click = event.left_mouse_fast_click_count();

		if (fast_click == 2u)
		{
			this->double_click_cooldown.reset();
			auto& line = this->get_line_at_cursor();

			if (!line.wstring().empty())
			{
				wchar_t c = line.wstring().back();
				if (this->cursor_position.x < line.wstring().length())
				{
					c = line.wstring()[this->cursor_position.x];
				}

				bool is_special = !(std::iswalpha(c) || std::iswalnum(c) || (c == L'_'));
				bool is_space = std::iswspace(c);

				ql::isize begin = this->cursor_position.x;
				ql::isize end = this->cursor_position.x;
				while (begin > 0)
				{
					auto c = line.wstring()[begin - 1];
					bool allowed;
					if (is_space)
					{
						allowed = std::iswspace(c);
					}
					else if (is_special)
					{
						allowed = !(std::iswalpha(c) || std::iswalnum(c) || (c == L'_') || std::iswspace(c));
					}
					else
					{
						allowed = std::iswalpha(c) || std::iswalnum(c) || (c == L'_');
					}

					if (!allowed)
					{
						break;
					}
					--begin;
				}
				while (end < ql::isize_cast(line.wstring().length()))
				{
					auto c = line.wstring()[end];

					bool allowed;
					if (is_space)
					{
						allowed = std::iswspace(c);
					}
					else if (is_special)
					{
						allowed = !(std::iswalpha(c) || std::iswalnum(c) || (c == L'_') || std::iswspace(c));
					}
					else
					{
						allowed = std::iswalpha(c) || std::iswalnum(c) || (c == L'_');
					}
					if (!allowed)
					{
						break;
					}
					++end;
				}

				this->selection_a.y = this->selection_b.y = this->cursor_position.y;
				this->selection_a.x = ql::size_cast(begin);
				this->selection_b.x = ql::size_cast(end);
				this->cursor_position.x = ql::size_cast(end);

				this->cursor_position_changed = true;
				this->make_selection_rectangles();
			}
		}
		else if (fast_click == 3u)
		{
			this->selection_a.y = this->selection_b.y = this->cursor_position.y;
			this->selection_a.x = 0u;
			this->selection_b.x = this->get_line_at_cursor().wstring().length();
			this->cursor_position.x = this->selection_b.x;
			if (this->selection_b.y != this->lines.size() - 1)
			{
				++this->selection_b.y;
				this->selection_b.x = 0u;
			}

			this->cursor_position_changed = true;
			this->make_selection_rectangles();
		}
	}

	void ql::text_field::update(const ql::event_manager& event)
	{
		auto cursor_before = this->cursor_position;
		auto string_before = this->wstring();

		this->update_cursor();
		this->internal_update();

		bool special_input = false;
		this->edited_text = false;
		this->copied_text = false;
		this->pasted_text = false;
		this->entered_text = false;
		this->finished_text = false;
		this->control_z = false;
		this->control_y = false;
		this->changed = false;
		this->pressed_enter_key = false;

		this->update_mouse_events(event);

		if (!this->focus)
		{
			return;
		}

		if (event.key_pressed(sf::Keyboard::Backspace))
		{
			if (this->selection_a != this->selection_b)
			{
				this->delete_selection_string();
			}
			else
			{
				this->delete_at_cursor();
			}
			special_input = true;
			this->edited_text = true;
			this->changed = true;
		}
		if (event.key_pressed(sf::Keyboard::Enter))
		{
			this->pressed_enter_key = true;

			if (!this->ignore_pressing_enter_key)
			{
				if (this->lines.size() >= this->line_limit)
				{
					this->finished_text = true;
					this->focus = false;
					this->delete_selection_range();
					this->make_selection_rectangles();
					return;
				}
				this->delete_selection_string();
				this->new_line(this->cursor_position.y);
				special_input = true;
				this->changed = true;
			}
			else
			{
				return;
			}
		}
		if (event.key_pressed(sf::Keyboard::Up))
		{
			auto before = this->cursor_position;
			this->move_cursor_up();
			special_input = true;
			if (event.key_holding(sf::Keyboard::LShift))
			{
				if (this->selection_a == this->selection_b)
				{
					this->selection_a = before;
				}
				this->selection_b = this->cursor_position;
				this->make_selection_rectangles();
			}
			else
			{
				this->delete_selection_range();
				this->make_selection_rectangles();
			}
			this->changed = true;
		}
		if (event.key_pressed(sf::Keyboard::Down))
		{
			auto before = this->cursor_position;
			this->move_cursor_down();
			special_input = true;
			if (event.key_holding(sf::Keyboard::LShift))
			{
				if (this->selection_a == this->selection_b)
				{
					this->selection_a = before;
				}
				this->selection_b = this->cursor_position;
				this->make_selection_rectangles();
			}
			else
			{
				this->delete_selection_range();
				this->make_selection_rectangles();
			}
			this->changed = true;
		}
		if (event.key_pressed(sf::Keyboard::Left))
		{
			auto before = this->cursor_position;
			this->move_cursor_left();
			special_input = true;
			if (event.key_holding(sf::Keyboard::LShift))
			{
				if (this->selection_a == this->selection_b)
				{
					this->selection_a = before;
				}
				this->selection_b = this->cursor_position;
				this->make_selection_rectangles();
			}
			else
			{
				this->delete_selection_range();
				this->make_selection_rectangles();
			}
			this->changed = true;
		}
		if (event.key_pressed(sf::Keyboard::Right))
		{
			auto before = this->cursor_position;
			this->move_cursor_right();
			special_input = true;
			if (event.key_holding(sf::Keyboard::LShift))
			{
				if (this->selection_a == this->selection_b)
				{
					this->selection_a = before;
				}
				this->selection_b = this->cursor_position;
				this->make_selection_rectangles();
			}
			else
			{
				this->delete_selection_range();
				this->make_selection_rectangles();
			}
			this->changed = true;
		}
		if (event.key_holding(sf::Keyboard::LControl))
		{
			if (event.key_pressed(sf::Keyboard::A))
			{
				this->selection_a = ql::vec(0u, 0u);
				this->selection_b = ql::vec(this->lines.back().wstring().length(), this->lines.size() - 1);

				this->cursor_position = this->selection_b;
				this->cursor_interval_timer.reset();
				this->cursor_position_changed = true;
				this->make_selection_rectangles();
				special_input = true;
				this->changed = true;
			}
			else if (event.key_pressed(sf::Keyboard::X))
			{
				auto str = this->get_selection_wstring();
				ql::copy_to_clipboard(str);
				this->delete_selection_string();
				special_input = true;
				this->edited_text = true;
				this->copied_text = true;
				this->changed = true;
			}
			else if (event.key_pressed(sf::Keyboard::C))
			{
				auto str = this->get_selection_wstring();
				ql::copy_to_clipboard(str);
				special_input = true;
				this->copied_text = true;
				this->changed = true;
			}
			else if (event.key_pressed(sf::Keyboard::V))
			{
				this->delete_selection_string();
				auto str = ql::copy_from_clipboard();
				this->add_string_at_cursor(str);
				special_input = true;

				this->update_required = true;
				this->internal_update();
				this->edited_text = true;
				this->pasted_text = true;
				this->changed = true;
			}
			else if (event.key_pressed(sf::Keyboard::Z))
			{
				if (this->string_stack.size())
				{
					auto last = 0u;
					if (this->string_stack_position != last)
					{
						--this->string_stack_position;
						this->set_string(this->string_stack[this->string_stack_position].first);
						this->cursor_position = this->string_stack[this->string_stack_position].second;

						this->cursor_position_changed = true;
						this->whole_string_changed = true;
						this->text_mouse_hitboxes_changed = true;
						this->cursor_interval_timer.reset();
						this->update_required = true;
						this->internal_update();
						this->edited_text = true;
						this->control_z = true;
						this->changed = true;
					}
				}
				special_input = true;
			}
			else if (event.key_pressed(sf::Keyboard::Y))
			{
				if (this->string_stack.size())
				{
					auto last = this->string_stack.used_size() - 1;
					if (this->string_stack.used_size() && this->string_stack_position != last)
					{
						++this->string_stack_position;
						this->set_string(this->string_stack[this->string_stack_position].first);
						this->cursor_position = this->string_stack[this->string_stack_position].second;
						this->cursor_position_changed = true;
						this->whole_string_changed = true;
						this->text_mouse_hitboxes_changed = true;
						this->cursor_interval_timer.reset();
						this->update_required = true;
						this->internal_update();
						this->edited_text = true;
						this->control_z = true;
						this->changed = true;
					}
				}
				special_input = true;
			}
			else
			{
				special_input = true;
			}
		}
		if (event.is_text_entered() && !special_input)
		{
			this->delete_selection_string();
			this->add_string_at_cursor(event.text_entered());

			this->update_required = true;
			this->internal_update();
			this->edited_text = true;
			this->entered_text = true;
			this->changed = true;
		}

		if (this->string_stack.size() && this->edited_text && (!this->control_z && !this->control_y))
		{
			auto current_str = this->wstring();
			if (string_before != current_str)
			{
				if (this->string_stack.used_size() == 0u)
				{
					this->string_stack.add(std::make_pair(string_before, cursor_before));
					this->string_stack_position = 0u;
				}
				if (this->string_stack_position != this->string_stack.used_size() - 1)
				{
					auto copy = this->string_stack;
					this->string_stack.reset();
					for (ql::size i = 0u; i <= this->string_stack_position; ++i)
					{
						this->string_stack.add(copy[i]);
					}
				}
				this->string_stack.back().second = cursor_before;

				this->string_stack.add(std::make_pair(current_str, cursor_before));
				this->string_stack_position = this->string_stack.used_size() - 1;
				this->changed = true;
			}
		}

		this->internal_update_cursor();
		this->update_selection_rectangles();

		this->dragging_selection_before = this->is_dragging_selection_considering_cooldown();
	}

	void ql::text_field::draw(ql::render& draw) const
	{
		draw.draw(this->background);
		draw.draw(this->selection_rectangles);
		draw.draw(this->lines);

		if (this->focus)
		{
			draw.draw(this->cursor);
		}
	}

	std::pair<ql::vector2s, ql::vector2s> ql::text_field::get_sorted_selection_range() const
	{
		auto begin = this->selection_a;
		auto end = this->selection_b;

		if (begin.y > end.y)
		{
			std::swap(begin, end);
		}
		else if (begin.y == end.y && begin.x > end.x)
		{
			std::swap(begin, end);
		}
		return std::make_pair(begin, end);
	}

	void ql::text_field::internal_update() const
	{
		this->internal_update_text();

		if (this->update_required)
		{
			this->update_required = false;

			auto hitbox = this->get_hitbox();

			if (hitbox.dimension.x != this->hitbox.dimension.x)
			{
				for (auto& line : this->lines)
				{
					line.mouse_hitboxes_changed = true;
				}
				this->text_mouse_hitboxes_changed = true;
			}

			hitbox.dimension.clamp(this->minimum_dimension, this->maximum_dimension);

			this->hitbox.set_dimension(hitbox.dimension);

			if (this->background_increase != ql::vec(0, 0))
			{
				hitbox.dimension.y += this->background_increase.y * 0.9f;
			}

			auto background_hitbox = hitbox.increased(this->background_increase);
			this->background.set_hitbox(background_hitbox);
			this->cursor_position_changed = true;
		}

		if (this->text_mouse_hitboxes_changed)
		{
			for (auto& i : this->lines)
			{
				if (i.mouse_hitboxes_changed)
				{
					i.calculate_mouse_hitboxes(this->hitbox.dimension.x + this->hitbox.position.x, this->background_increase.x);
					i.mouse_hitboxes_changed = false;
				}
			}
			this->text_mouse_hitboxes_changed = false;
		}
	}

	void ql::text_field::internal_update_text() const
	{
		if (this->text_layout_changed)
		{
			for (auto& i : this->lines)
			{
				if (i.layout_changed)
				{
					i.apply(this->text_layout);
					i.layout_changed = false;
				}
			}
			this->set_cursor_dimension();

			this->text_layout_changed = false;
		}
	}

	void ql::text_field::internal_update_cursor()
	{
		if (this->cursor_position_changed)
		{
			this->set_cursor_position();
			this->cursor_position_changed = false;
		}
	}

	void ql::text_field::set_cursor_dimension() const
	{
		ql::vec2 cursor_dim;
		cursor_dim.x = this->cursor_width_percentage * this->text_layout.character_size;
		cursor_dim.y = this->lines.front().text.get_line_height() + this->lines.front().text.get_delta_underline();
		this->cursor.set_dimension(cursor_dim);
	}

	void ql::text_field::set_cursor_position()
	{
		this->internal_update();

		if (this->cursor_position.y >= this->lines.size())
		{
			this->cursor_position.y = this->lines.size() - 1;
			if (this->get_line_at_cursor().wstring().empty())
			{
				this->cursor_position.x = 0u;
			}
		}

		const auto& line = this->get_line_at_cursor();
		auto hitbox_index = this->cursor_position.x;

		bool right_side = false;
		if (line.character_hitboxes.empty())
		{
			return;
		}
		if (hitbox_index >= line.character_hitboxes.size())
		{
			hitbox_index = line.character_hitboxes.size() - 1;
			if (line.wstring().empty())
			{
			}
			right_side = true;
		}
		const auto& hitbox = line.character_hitboxes[hitbox_index];

		ql::f32 x_offset;
		if (right_side)
		{
			x_offset = hitbox.dimension.x + this->cursor_x_offset;
		}
		else
		{
			x_offset = -(this->cursor_x_offset + this->cursor.get_dimension().x);
		}

		auto position = hitbox.position;
		position.y = line.text.get_starting_line_position().y - line.text.get_delta_underline();
		position.x += x_offset;

		this->cursor.set_position(position);
	}

	void ql::text_field::make_selection_rectangles() const
	{
		if (this->selection_a == this->selection_b)
		{
			this->selection_rectangles.clear();
			return;
		}
		auto [begin, end] = this->get_sorted_selection_range();

		this->selection_rectangles.clear();
		auto size = end.y - begin.y + 1;
		this->selection_rectangles.reserve(size);
		ql::size count = 0u;

		if (begin.y == end.y)
		{
			this->make_selection_rectangles(count, begin.y, begin.x, end.x);
		}
		else
		{
			for (ql::size i = 0u; i < size; ++i)
			{
				if (i == 0u)
				{
					this->make_selection_rectangles(count, i + begin.y, begin.x);
				}
				else if (i == size - 1)
				{
					this->make_selection_rectangles(count, i + begin.y, 0u, end.x);
				}
				else
				{
					this->make_selection_rectangles(count, i + begin.y, 0u);
				}
			}
		}
	}

	void ql::text_field::make_selection_rectangles(ql::size& count, ql::size y, ql::size x1, ql::size x2) const
	{
		const auto& line = this->lines[y];

		if (x2 == ql::size_max)
		{
			x2 = line.character_hitboxes.size();
		}
		if (x1 >= line.character_hitboxes.size())
		{
			auto a = line.character_hitboxes.back();
			auto length = line.line_mouse_hitbox.dimension.x + line.line_mouse_hitbox.position.x - (a.dimension.x + a.position.x) -
										this->get_background_outline_thickness();
			ql::hitbox result;
			result.position = a.position + a.dimension.just_x();
			result.dimension.x = length;

			result.position.y = line.text.get_starting_line_position().y - line.text.get_delta_underline();
			result.dimension.y = line.text.get_line_height() + line.text.get_delta_underline();

			this->selection_rectangles.push_back({});
			this->selection_rectangles.back().set_hitbox(result);
			this->selection_rectangles.back().set_color(this->selection_color);
			++count;

			return;
		}
		auto a = line.character_hitboxes[x1];

		ql::hitbox b;

		auto right_side = x2 == line.character_hitboxes.size();
		ql::f32 offset_x;
		if (right_side)
		{
			if (x2 == 0u)
			{
				b = line.character_hitboxes[x2];
			}
			else
			{
				b = line.character_hitboxes[x2 - 1];
			}
			offset_x = b.dimension.x + this->cursor_x_offset;
		}
		else
		{
			b = line.character_hitboxes[x2];
			offset_x = -(this->cursor_x_offset + this->cursor.get_dimension().x);
		}

		ql::vec2 position = a.position;
		ql::vec2 dimension = b.position - a.position + offset_x;

		position.y = line.text.get_starting_line_position().y - line.text.get_delta_underline();
		dimension.y = line.text.get_line_height() + line.text.get_delta_underline();

		this->selection_rectangles.push_back({});
		this->selection_rectangles.back().set_hitbox({position, dimension});
		this->selection_rectangles.back().set_color(this->selection_color);
		++count;
	}

	void ql::text_field::find_closest_cursor_position()
	{
		const auto& hitboxes = this->lines[this->cursor_position.y].character_hitboxes;

		bool found = false;
		ql::size new_position = 0u;
		ql::f32 diff_before = ql::f32_max;
		for (ql::size i = 0u; i < hitboxes.size(); ++i)
		{
			auto x = hitboxes[i].position.x - (this->cursor_x_offset + this->cursor.get_dimension().x);
			auto diff = ql::abs(this->cursor.get_position().x - x);

			if (diff > diff_before)
			{
				found = true;
				break;
			}
			diff_before = diff;
			new_position = i;
		}
		if (!found)
		{
			new_position = hitboxes.size();
		}
		this->cursor_position.x = new_position;
		this->cursor_position_changed = true;
	}

	bool ql::text_field::just_changed() const
	{
		return this->changed || this->pressed_enter_key;
	}

	void ql::text_field::update_all_changes()
	{
		this->text_mouse_hitboxes_changed = true;
		this->text_layout_changed = true;
		this->update_required = true;
		this->whole_string_changed = true;
		this->cursor_position_changed = true;
		this->edited_text = true;
		this->entered_text = true;
		this->changed = true;
		this->hitbox.dimension = ql::vec(ql::f32_max, ql::f32_max);
		this->internal_update();
	}

	void ql::color_picker::init()
	{
		this->set_hitbox({ql::vec(0, 0), ql::vec(460, 400)});

		this->gradient.resize(this->gradient_segments * this->gradient_segments * 4);
		this->gradient.set_primitive_type(ql::primitive_type::quads);

		this->hue_slider.resize(this->hue_slider_segments * 4);
		this->hue_slider.set_primitive_type(ql::primitive_type::quads);

		this->background.set_color(ql::rgb(50, 50, 50));
		this->background.set_slope_dimension(40);

		auto slope = 4.0f;
		this->hue_slider_knob.set_dimension(ql::vec(this->slider_width + slope * 2, 24.0f));
		this->hue_slider_knob.set_slope_dimension(slope);
		this->hue_slider_knob.set_color(ql::rgb::white().with_alpha(220));

		this->transparency_slider_knob = this->hue_slider_knob;

		this->gradient_control = {1.0, 0.0};

		this->gradient_control_circle.set_radius(this->gradient_control_circle_radius);
		this->gradient_control_circle.set_color(ql::rgba::transparent());
		this->gradient_control_circle.set_outline_color(ql::rgb::white());
		this->gradient_control_circle.set_outline_thickness(4.0f);

		this->gradient_cross.resize(4u * 4u);
		this->gradient_cross.set_primitive_type(ql::primitive_type::quads);

		this->display_color_rectangle.set_dimension({100, 40});
		this->display_color_rectangle.set_outline_thickness(4.0f);
		this->display_color_rectangle.set_outline_color(ql::rgb::white());

		this->input_field.set_background_outline_thickness(0.0f);
		this->input_field.enable_one_line_limit();
		this->set_input_field_width(200);

		this->transparency_slider.resize(4u);
		this->transparency_slider.set_primitive_type(ql::primitive_type::quads);
		this->transparency_slider[2].color = ql::rgba::transparent();
		this->transparency_slider[3].color = ql::rgba::transparent();

		this->transparency_checkerboard.set_primitive_type(ql::primitive_type::quads);

		this->confirm_button.set_dimension({100, 40});
		this->confirm_button.set_background_color(ql::rgb::grey_shade(30));
		this->confirm_button.set_text_color(ql::rgb::white());

		this->reset();
	}

	void ql::color_picker::reset()
	{
		this->gradient_control = {1, 0};
		this->hue_control = 0.0;
		this->transparency_control = 1.0;
	}

	void ql::color_picker::update_values()
	{
		this->hue_color = ql::get_rainbow_color(this->hue_control);
		this->color_result = this->get_gradient_color_at(this->gradient_control);
		this->display_color_rectangle.set_color(this->color_result);

		if (this->is_font_set())
		{
			this->input_field.set_string(this->color_result.to_string());
		}
		this->color_changed = true;
		this->internal_gradient_color_changed = true;
	}

	bool ql::color_picker::color_value_changed() const
	{
		return this->color_changed;
	}

	bool ql::color_picker::has_focus() const
	{
		return this->focus;
	}

	bool ql::color_picker::is_font_set() const
	{
		return this->input_field.is_font_set();
	}

	void ql::color_picker::set_color_value(ql::rgba color)
	{
		ql::f64 x = 0.0;
		if (color.max())
		{
			x = 1.0 - (color.min() / ql::f64_cast(color.max()));
		}
		ql::f64 y = 1.0 - color.max() / ql::f64_cast(color.max_channel());
		this->gradient_control = {x, y};
		this->hue_control = color.get_hue();

		this->update_gradient_control_position();
		this->update_hue_slider_knob_position();

		if (this->transparency_used)
		{
			this->transparency_control = color.a / 255.0;
			this->update_transparency_slider_knob_position();
		}
		this->color_changed = true;
		this->dont_update_input_text = true;

		this->update_internal_colors();
	}

	ql::rgba ql::color_picker::get_color_value() const
	{
		if (this->internal_gradient_hitbox_changed || this->internal_gradient_color_changed)
		{
			this->internal_update();
		}
		return this->color_result;
	}

	ql::rgb ql::color_picker::get_gradient_color_at(ql::vec2f pos) const
	{
		auto color = this->hue_color;
		ql::frgb result = color;
		result.interpolate(ql::rgb::white(), 1.0f - pos.x);
		result.interpolate(ql::rgb::black(), pos.y);
		return result;
	}

	ql::hitbox ql::color_picker::get_gradient_hitbox() const
	{
		auto slider_space = (this->slider_margin + this->slider_width);
		if (this->transparency_used)
		{
			slider_space *= 2;
		}
		auto hitbox = this->hitbox;
		hitbox.set_width(this->hitbox.get_width() - slider_space);
		hitbox.set_height(this->hitbox.get_height() - (this->bottom_margin + this->bottom_height));
		return hitbox;
	}

	ql::hitbox ql::color_picker::get_hue_slider_hitbox() const
	{
		auto slider_space = this->slider_width;
		if (this->transparency_used)
		{
			slider_space += (this->slider_margin + this->slider_width);
		}
		auto hitbox = this->hitbox;
		hitbox.set_width(this->slider_width);
		hitbox.set_height(this->hitbox.get_height() - (this->bottom_margin + this->bottom_height));
		hitbox.set_position(this->hitbox.position + ql::vec(this->hitbox.get_width() - slider_space, 0));
		return hitbox;
	}

	ql::hitbox ql::color_picker::get_transparency_slider_hitbox() const
	{
		auto hitbox = this->hitbox;
		hitbox.set_width(this->slider_width);
		hitbox.set_height(this->hitbox.get_height() - (this->bottom_margin + this->bottom_height));
		hitbox.set_position(this->hitbox.position + ql::vec(this->hitbox.get_width() - this->slider_width, 0));
		return hitbox;
	}

	ql::f64 ql::color_picker::get_hue_control_value() const
	{
		auto height = this->get_hue_slider_hitbox().get_height() - this->hue_slider_knob.get_dimension().y;

		auto y = this->hue_slider_knob.get_position().y - this->hitbox.position.y;
		return ql::clamp(y / height);
	}

	ql::f64 ql::color_picker::get_transparency_control_value() const
	{
		auto height = this->get_transparency_slider_hitbox().get_height() - this->transparency_slider_knob.get_dimension().y;

		auto y = this->transparency_slider_knob.get_position().y - this->hitbox.position.y;
		return 1.0 - ql::clamp(y / height);
	}

	ql::vec2d ql::color_picker::get_gradient_control_value() const
	{
		auto value = this->gradient_control_circle.get_center() - this->hitbox.position;
		return (value / this->get_gradient_hitbox().get_dimension()).clamped(0.0, 1.0);
	}

	void ql::color_picker::disable_transparency()
	{
		this->transparency_used = false;
	}

	void ql::color_picker::enable_transparency()
	{
		this->transparency_used = true;
	}

	void ql::color_picker::set_font(std::string font)
	{
		this->input_field.set_font(font);
		this->confirm_button.set_text_font(font);

		this->confirm_button.set_text_string("ok");
		this->update_values();
	}

	void ql::color_picker::set_invisible()
	{
		this->visible = false;
	}

	void ql::color_picker::set_visible()
	{
		this->visible = true;
	}

	bool ql::color_picker::is_visible() const
	{
		return this->visible;
	}

	bool ql::color_picker::is_dragging_hue_slider() const
	{
		return this->dragging_hue_slider;
	}

	bool ql::color_picker::is_dragging_gradient() const
	{
		return this->dragging_gradient;
	}

	bool ql::color_picker::is_dragging() const
	{
		return this->is_dragging_gradient() || this->is_dragging_hue_slider();
	}

	void ql::color_picker::set_input_field_width(ql::f32 width)
	{
		this->input_field.set_fixed_width(width);
	}

	void ql::color_picker::set_dimension(ql::vec2f dimension)
	{
		this->hitbox.dimension = dimension;
		this->internal_gradient_hitbox_changed = true;
	}

	void ql::color_picker::set_position(ql::vec2f position)
	{
		this->hitbox.position = position;
		this->internal_gradient_hitbox_changed = true;
	}

	void ql::color_picker::set_hitbox(ql::hitbox hitbox)
	{
		this->hitbox = hitbox;
		this->internal_gradient_hitbox_changed = true;
	}

	void ql::color_picker::set_center(ql::vec2f center)
	{
		this->hitbox.set_center(center);
		this->internal_gradient_hitbox_changed = true;
	}

	void ql::color_picker::set_hue_wheel(ql::f64 hue)
	{
		this->hue_control = hue;
		this->internal_gradient_color_changed = true;
	}

	void ql::color_picker::set_background_color(ql::rgba color)
	{
		this->background.set_color(color);
	}

	void ql::color_picker::set_hue_control_color(ql::rgba color)
	{
		this->hue_slider_knob.set_color(color);
	}

	void ql::color_picker::set_gradient_control_color(ql::rgba color)
	{
		this->gradient_control_circle.set_color(color);
	}

	void ql::color_picker::create_gradient() const
	{
		auto gradient_dimension = this->get_gradient_hitbox().dimension / this->gradient_segments;

		auto gradient_dim = ql::vec(this->gradient_segments, this->gradient_segments);
		for (ql::vec2s pos : gradient_dim.list_possibilities_range())
		{
			auto index = pos.y * this->gradient_segments + pos.x;
			for (ql::size i = 0u; i < ql::vec_square4.size(); ++i)
			{
				auto position = (pos + ql::vec_square4[i]) * gradient_dimension + this->hitbox.position;
				this->gradient[index * 4 + i].position = position;
			}
		}
	}

	void ql::color_picker::update_gradient() const
	{
		auto gradient_dim = ql::vec(this->gradient_segments, this->gradient_segments);
		for (ql::vec2s pos : gradient_dim.list_possibilities_range())
		{
			auto index = pos.y * this->gradient_segments + pos.x;
			for (ql::size i = 0u; i < ql::vec_square4.size(); ++i)
			{
				auto gradient_progress = (pos + ql::vec_square4[i]) / ql::vec2f(this->gradient_segments, this->gradient_segments);
				ql::frgb color_result = this->hue_color;
				color_result.interpolate(ql::rgb::white(), 1.0f - gradient_progress.x);
				color_result.interpolate(ql::rgb::black(), gradient_progress.y);
				this->gradient[index * 4 + i].color = color_result;
			}
		}

		this->internal_gradient_color_changed = false;
	}

	void ql::color_picker::create_hue_slider() const
	{
		auto right_side = this->get_gradient_hitbox().get_top_right();
		auto slider_height = this->get_hue_slider_hitbox().get_height() / this->hue_slider_segments;
		for (ql::size s = 0u; s < this->hue_slider_segments; ++s)
		{
			for (ql::size i = 0u; i < ql::vec_square4.size(); ++i)
			{
				auto position = (ql::vec(0, s) + ql::vec_square4[i]) * ql::vec(this->slider_width, slider_height) + right_side +
												ql::vec(this->slider_margin, 0);
				this->hue_slider[s * 4 + i].position = position;

				auto progress = ql::f64_cast(s + ql::vec_square4[i].y) / this->hue_slider_segments;
				this->hue_slider[s * 4 + i].color = ql::get_rainbow_color(progress);
			}
		}
	}

	void ql::color_picker::create_transparency_slider() const
	{
		if (this->transparency_used)
		{
			auto transparency_hitbox = this->get_transparency_slider_hitbox();
			for (ql::size i = 0u; i < ql::vec_square4.size(); ++i)
			{
				auto position = transparency_hitbox.position + transparency_hitbox.dimension * ql::vec_square4[i];
				this->transparency_slider[i].position = position;
			}
			auto checkerboard_size = ql::vec2s(transparency_hitbox.dimension / this->transparency_checkerboard_dimension);
			this->transparency_checkerboard.resize(checkerboard_size.x * checkerboard_size.y * 4u);

			for (ql::vec2s pos : checkerboard_size.list_possibilities_range())
			{
				auto index = pos.y * checkerboard_size.x + pos.x;
				for (ql::size i = 0u; i < ql::vec_square4.size(); ++i)
				{
					auto position = (pos + ql::vec_square4[i]) * this->transparency_checkerboard_dimension + transparency_hitbox.position;
					position.clamp(transparency_hitbox.get_bottom_right());
					this->transparency_checkerboard[index * 4 + i].position = position;

					ql::rgb color;
					if ((pos.x + pos.y) % 2)
					{
						color = this->transparency_checkerboard_color_dark;
					}
					else
					{
						color = this->transparency_checkerboard_color_light;
					}
					this->transparency_checkerboard[index * 4 + i].color = color;
				}
			}
		}
	}

	void ql::color_picker::update_bottom_row_positions() const
	{
		auto background_move = ql::vec(0.f, -this->background_increase / 2);

		auto h = this->display_color_rectangle.get_hitbox();
		h.set_left_center(this->hitbox.get_left_bottom().moved(
				background_move + ql::vec(this->display_color_rectangle.get_outline_thickness(), 0.0)
		));
		this->display_color_rectangle.set_hitbox(h);

		if (this->is_font_set())
		{
			h = this->input_field.get_background_hitbox();
			h.set_left_center(this->display_color_rectangle.get_hitbox().get_right_center().moved(
					this->input_field.get_background_increase() + ql::vec(this->slider_margin, 0)
			));
			this->input_field.set_hitbox(h);
		}

		h = this->confirm_button.get_hitbox();
		h.set_bottom_right(this->hitbox.get_bottom_right().moved(ql::vec(5, 0)));
		this->confirm_button.set_hitbox(h);
		this->confirm_button.centerize_text();
	}

	void ql::color_picker::internal_update() const
	{
		if (this->internal_gradient_hitbox_changed)
		{
			this->internal_gradient_hitbox_changed = false;

			this->update_gradient_control_position();
			this->update_hue_slider_knob_position();
			this->update_transparency_slider_knob_position();

			this->background.set_hitbox(this->hitbox.increased(this->background_increase));
			this->update_bottom_row_positions();

			this->create_gradient();
			this->create_hue_slider();
			this->create_transparency_slider();
		}
		if (this->internal_gradient_color_changed)
		{
			this->update_gradient();
		}
	}

	void ql::color_picker::update_hue_slider_knob_position() const
	{
		auto hitbox = this->get_hue_slider_hitbox();

		auto height = hitbox.get_height() - this->hue_slider_knob.get_dimension().y;
		auto y = height * this->hue_control;
		this->hue_slider_knob.set_position(hitbox.position + ql::vec(-this->hue_slider_knob.get_slope_dimension().x, y));
	}

	void ql::color_picker::update_transparency_slider_knob_position() const
	{
		auto hitbox = this->get_transparency_slider_hitbox();

		auto height = hitbox.get_height() - this->transparency_slider_knob.get_dimension().y;
		auto y = height * (1.0 - this->transparency_control);
		this->transparency_slider_knob.set_position(
				hitbox.position + ql::vec(-this->transparency_slider_knob.get_slope_dimension().x, y)
		);
	}

	void ql::color_picker::update_gradient_control_position() const
	{
		auto gradient_hitbox = this->get_gradient_hitbox();

		auto value = gradient_hitbox.dimension * this->gradient_control;
		auto pos = gradient_hitbox.position + value;
		this->gradient_control_circle.set_center(pos);

		if (!this->cross_enabled)
		{
			return;
		}
		ql::size cross_ctr = 0u;

		auto cross_width = 2.0f;
		auto circle_radius = this->gradient_control_circle_radius + this->gradient_control_circle.get_outline_thickness();

		for (ql::size i = 0u; i < ql::vec_square4.size(); ++i)
		{
			auto& vertex = this->gradient_cross[cross_ctr * 4 + i];
			auto cross_value = ql::vec_square4[(i + cross_ctr + 3) % ql::vec_square4.size()];

			auto start = ql::vec(0, value.y - (cross_width / 2));
			auto target_x = value.x - circle_radius;
			auto position = (start + ql::vec(target_x, cross_width) * cross_value).clamped(gradient_hitbox.dimension);
			vertex.position = gradient_hitbox.position + position;
		}
		++cross_ctr;

		for (ql::size i = 0u; i < ql::vec_square4.size(); ++i)
		{
			auto& vertex = this->gradient_cross[cross_ctr * 4 + i];
			auto cross_value = ql::vec_square4[(i + cross_ctr + 3) % ql::vec_square4.size()];

			auto start = ql::vec(value.x - (cross_width / 2), 0);
			auto target_y = value.y - circle_radius;
			auto position = (start + ql::vec(cross_width, target_y) * cross_value).clamped(gradient_hitbox.dimension);
			vertex.position = gradient_hitbox.position + position;
		}
		++cross_ctr;

		for (ql::size i = 0u; i < ql::vec_square4.size(); ++i)
		{
			auto& vertex = this->gradient_cross[cross_ctr * 4 + i];
			auto cross_value = ql::vec_square4[(i + cross_ctr + 3) % ql::vec_square4.size()];

			auto start = ql::vec(value.x + circle_radius, value.y - (cross_width / 2));
			auto target_x = gradient_hitbox.dimension.x - value.x - circle_radius;
			auto position = (start + ql::vec(target_x, cross_width) * cross_value).clamped(gradient_hitbox.dimension);
			vertex.position = gradient_hitbox.position + position;
		}
		++cross_ctr;

		for (ql::size i = 0u; i < ql::vec_square4.size(); ++i)
		{
			auto& vertex = this->gradient_cross[cross_ctr * 4 + i];
			auto cross_value = ql::vec_square4[(i + cross_ctr + 3) % ql::vec_square4.size()];

			auto start = ql::vec(value.x - (cross_width / 2), value.y + circle_radius);
			auto target_y = gradient_hitbox.dimension.y - value.y - circle_radius;
			auto position = (start + ql::vec(cross_width, target_y) * cross_value).clamped(gradient_hitbox.dimension);
			vertex.position = gradient_hitbox.position + position;
		}
		++cross_ctr;

		for (ql::size i = 0u; i < this->gradient_cross.size(); ++i)
		{
			auto vertex = i % 4;
			if (vertex == 0 || vertex == 1)
			{
				this->gradient_cross[i].color = ql::rgba::transparent();
			}
		}
	}

	void ql::color_picker::update_internal_colors()
	{
		auto gradient_color = this->get_gradient_color_at(this->gradient_control);
		this->color_result = gradient_color;

		if (this->transparency_used)
		{
			this->color_result.a = ql::u8_cast(std::round(this->transparency_control * 255));
		}
		this->display_color_rectangle.set_color(this->color_result);

		if (this->transparency_used)
		{
			this->transparency_slider[0].color = gradient_color;
			this->transparency_slider[1].color = gradient_color;
		}

		if (!this->dont_update_input_text && this->is_font_set())
		{
			this->input_field.set_string(this->color_result.to_string());
		}
	}

	void ql::color_picker::update_entered_text()
	{
		auto str = this->input_field.string();
		auto numbers = ql::string_split_numbers<ql::size>(str);
		if (!numbers.empty() && (numbers.size() == 3u || numbers.size() == 4u))
		{
			ql::rgba result;
			for (ql::size i = 0u; i < numbers.size(); ++i)
			{
				result[i] = ql::u8_cast(ql::clamp<ql::size>(0u, numbers[i], 255u));
			}
			this->set_color_value(result);
			this->dont_update_input_text = true;
		}
	}

	void ql::color_picker::update(const ql::event_manager& event)
	{
		if (!this->visible)
		{
			return;
		}

		this->focus = false;
		this->dont_update_input_text = false;

		if (this->is_font_set())
		{
			event.update(this->confirm_button);
			event.update(this->input_field);
			if (this->input_field.has_focus())
			{
				this->focus = true;
			}
			if (this->input_field.just_changed())
			{
				this->update_entered_text();
			}
		}

		this->color_changed = false;
		bool clicked_hue_slider = false;
		bool clicked_transparency_slider = false;
		bool clicked_gradient = false;
		if (this->get_gradient_hitbox().increased(this->hitbox_increase).contains(event.mouse_position()))
		{
			if (event.left_mouse_clicked())
			{
				clicked_gradient = true;
				this->dragging_gradient = true;
			}
		}
		if (this->get_hue_slider_hitbox().increased(this->hitbox_increase).contains(event.mouse_position()))
		{
			if (event.left_mouse_clicked())
			{
				clicked_hue_slider = true;
				this->dragging_hue_slider = true;
			}
		}
		if (this->transparency_used &&
				this->get_transparency_slider_hitbox().increased(this->hitbox_increase).contains(event.mouse_position()))
		{
			if (event.left_mouse_clicked())
			{
				clicked_transparency_slider = true;
				this->dragging_transparency_slider = true;
			}
		}
		if (this->dragging_gradient && (clicked_gradient || event.mouse_moved()))
		{
			this->gradient_control_circle.set_center(event.mouse_position());

			this->gradient_control = this->get_gradient_control_value();
			this->update_gradient_control_position();
			this->color_changed = true;
			this->focus = true;
		}
		if (this->dragging_hue_slider && (clicked_hue_slider || event.mouse_moved()))
		{
			auto x = this->hue_slider_knob.get_position().x;
			this->hue_slider_knob.set_position(ql::vec(x, event.mouse_position().y - this->hue_slider_knob.get_dimension().y / 2));
			this->internal_gradient_color_changed = true;

			this->hue_control = this->get_hue_control_value();
			this->hue_color = ql::get_rainbow_color(this->hue_control);
			this->update_hue_slider_knob_position();
			this->color_changed = true;
			this->focus = true;
		}
		if (this->dragging_transparency_slider && (clicked_transparency_slider || event.mouse_moved()))
		{
			auto x = this->transparency_slider_knob.get_position().x;
			this->transparency_slider_knob.set_position(
					ql::vec(x, event.mouse_position().y - this->transparency_slider_knob.get_dimension().y / 2)
			);
			this->internal_gradient_color_changed = true;

			this->transparency_control = this->get_transparency_control_value();
			this->update_transparency_slider_knob_position();
			this->color_changed = true;
			this->focus = true;
		}

		if (this->color_changed)
		{
			this->update_internal_colors();
		}

		if (event.left_mouse_released())
		{
			this->dragging_hue_slider = false;
			this->dragging_transparency_slider = false;
			this->dragging_gradient = false;
		}
	}

	void ql::color_picker::draw(ql::render& draw) const
	{
		if (!this->visible)
		{
			return;
		}
		if (this->internal_gradient_hitbox_changed || this->internal_gradient_color_changed)
		{
			this->internal_update();
		}
		draw.draw(this->background);
		draw.draw(this->gradient);
		draw.draw(this->hue_slider);
		draw.draw(this->hue_slider_knob);
		if (this->transparency_used)
		{
			draw.draw(this->transparency_checkerboard);
			draw.draw(this->transparency_slider);
			draw.draw(this->transparency_slider_knob);
		}
		draw.draw(this->gradient_control_circle);
		draw.draw(this->display_color_rectangle);
		if (this->cross_enabled)
		{
			draw.draw(this->gradient_cross);
		}
		if (this->is_font_set())
		{
			draw.draw(this->input_field);
			draw.draw(this->confirm_button);
		}
	}

	ql::scroll_bar::scroll_bar()
	{
		this->background.set_color(this->background_color);
		this->knob.set_color(this->knob_color);
		this->background.set_slope_dimension(5);
		this->knob.set_slope_dimension(5);
		this->hover_animation.set_duration(0.2);
		this->background_hover_animation.set_duration(0.2);
	}

	void ql::scroll_bar::set_dimension(ql::vec2f dimension)
	{
		this->hitbox.dimension = dimension;
		this->update_positions();
	}

	void ql::scroll_bar::set_position(ql::vec2f position)
	{
		this->hitbox.position = position;
		this->update_positions();
	}

	void ql::scroll_bar::set_hitbox(ql::hitbox hitbox)
	{
		this->hitbox = hitbox;
		this->update_positions();
	}

	void ql::scroll_bar::set_visible_knob_progress(ql::f64 progress)
	{
		this->visible_knob_progress = ql::f32_cast(progress);
		auto height = this->hitbox.get_height() - this->knob.get_dimension().y;
		this->knob.set_position(this->hitbox.position + ql::vec2f(0.0f, height * this->visible_knob_progress));
	}

	void ql::scroll_bar::update_knob()
	{
		// auto progress = this->stepped_progress();
		auto progress = this->stepped_progress_unless_dragging();
		this->knob.set_dimension(ql::vec2f(this->hitbox.get_width(), this->hitbox.get_height() * this->knob_range));
		this->set_visible_knob_progress(progress);
	}

	void ql::scroll_bar::update_positions()
	{
		this->background.set_dimension(this->hitbox.dimension);
		this->background.set_position(this->hitbox.position);
		this->update_knob();
	}

	ql::f32 ql::scroll_bar::stepped_progress() const
	{
		ql::f32 progress = this->knob_progress;
		if (this->integer_step != ql::size_max)
		{
			progress = std::round(this->knob_progress * this->integer_step) / (this->integer_step);
		}
		return progress;
	}

	ql::f32 ql::scroll_bar::stepped_progress_unless_dragging() const
	{
		if (this->dragging)
		{
			return this->knob_progress;
		}
		else
		{
			return this->stepped_progress();
		}
	}

	ql::f32 ql::scroll_bar::get_progress() const
	{
		return this->knob_progress;
	}

	ql::size ql::scroll_bar::get_progress_step() const
	{
		// return ql::size_cast(std::ceil(this->knob_progress * this->integer_step));
		return ql::size_cast(std::round(this->knob_progress * (this->integer_step)));
	}

	void ql::scroll_bar::set_progress_integer_step(ql::size step, ql::size knob_steps)
	{
		this->knob_range = ql::max(0.05f, ql::f32_cast(knob_steps) / step);
		this->integer_step = step - knob_steps;
	}

	void ql::scroll_bar::set_progress(ql::f32 progress)
	{
		this->knob_progress = ql::clamp(progress);
		this->update_knob();
	}

	void ql::scroll_bar::set_knob_height(ql::f32 height)
	{
		this->knob_range = height;
		this->update_knob();
	}

	void ql::scroll_bar::set_knob_range(ql::f32 range)
	{
		this->knob_range = range;
	}

	void ql::scroll_bar::update_hover(const ql::event_manager& event)
	{
		auto hitbox = this->knob.get_hitbox().increased(5);
		this->hovering = hitbox.contains(event.mouse_position());
		if (this->hovering && event.left_mouse_clicked() && this->allow_dragging)
		{
			this->dragging_position = event.mouse_position();
			this->dragging = true;
		}

		if (this->hovering || this->dragging)
		{
			this->hover_animation.go_forwards();
		}
		else
		{
			this->hover_animation.go_backwards();
		}
		this->hover_animation.update(event);
		if (this->hover_animation.is_running())
		{
			auto p = this->hover_animation.get_progress();
			auto curve = ql::smooth_curve(p, 1.5);
			this->knob.set_color(this->knob_color.interpolated(this->knob_color_hover, curve));
		}
	}

	void ql::scroll_bar::update_background_hover(const ql::event_manager& event)
	{
		this->hovering_background = !this->dragging && !this->hovering && this->hitbox.increased(5).contains(event.mouse_position());
		if (this->hovering_background && event.left_mouse_clicked())
		{
			if (event.mouse_position().y < this->knob.get_position().y)
			{
				this->clicked_on_background_above = true;
			}
			else
			{
				this->clicked_on_background_below = true;
			}
		}

		if (this->hovering_background)
		{
			this->background_hover_animation.go_forwards();
		}
		else
		{
			this->background_hover_animation.go_backwards();
		}
		this->background_hover_animation.update(event.frame_time_f());
		if (this->background_hover_animation.is_running())
		{
			auto p = this->background_hover_animation.get_progress();
			auto curve = ql::smooth_curve(p, 1.5);
			this->background.set_color(this->background_color.interpolated(this->background_color_hover, curve));
		}
	}

	void ql::scroll_bar::update(const ql::event_manager& event)
	{
		this->value_changed = false;
		this->released_dragging = false;
		this->clicked_on_background_above = false;
		this->clicked_on_background_below = false;
		if (this->knob_range >= 1.0f)
		{
			return;
		}

		this->update_hover(event);
		this->update_background_hover(event);

		if (this->dragging)
		{
			auto delta = event.mouse_position().y - this->dragging_position.y;

			auto height = this->hitbox.dimension.y - this->knob.get_dimension().y;
			auto percentage = delta / height;

			auto before = this->stepped_progress();
			this->knob_progress = ql::clamp(this->knob_progress + percentage);

			this->update_knob();
			if (before != this->stepped_progress())
			{
				this->value_changed = true;
			}

			this->dragging_position = event.mouse_position();
		}
		if (event.left_mouse_released())
		{
			if (this->dragging)
			{
				this->released_dragging = true;
			}
			this->dragging = false;
		}
	}

	void ql::scroll_bar::draw(ql::render& draw) const
	{
		if (this->knob_range >= 1.0f)
		{
			return;
		}
		draw.draw(this->background);
		draw.draw(this->knob);
	}

	void ql::console::print()
	{
		ql::println("string: ", this->string.string());
		ql::println("input string: ", this->input_string.string());
		ql::println("string and input: ", this->string_and_input.string());
		ql::println("string split: ", this->string_split);
		ql::println("input string split: ", this->input_string_split);
		ql::println("string and input split: ", this->string_and_input_split);
		ql::println("selection rectangle: ", this->selection_rectangle.size());
		ql::println("selection rectangle start: ", this->selection_rectangle_start);
		ql::println("selection rectangle end: ", this->selection_rectangle_end);
		ql::println("view: ", this->view.position, " ", this->view.scale);
		ql::println("dimension: ", this->dimension);
		ql::println("zooms: ", this->zooms);
		ql::println("view row: ", this->view_row);
		ql::println("visible rows: ", this->visible_rows);
		ql::println("scroll bar: ", this->scroll_bar.get_progress());
		ql::println("cursor interval duration: ", this->cursor_interval_duration);
		ql::println("cursor: ", this->cursor.get_position());
		ql::println("scroll transition start: ", this->scroll_transition_start);
		ql::println("scroll transition end: ", this->scroll_transition_end);
		ql::println("scroll bar transition start: ", this->scroll_bar_transition_start);
		ql::println("scroll bar transition end: ", this->scroll_bar_transition_end);
		ql::println("selection rectangle color: ", this->selection_rectangle_color);
		ql::println("shadow border color: ", this->shadow_border_color);
		ql::println("visible y min: ", this->visible_y_min);
		ql::println("visible y max: ", this->visible_y_max);
		ql::println("visible buffer: ", this->visible_buffer);
		ql::println("before input vertices size: ", this->before_input_vertices_size);
		ql::println("before input outline vertices size: ", this->before_input_outline_vertices_size);
		ql::println("before input unicode vertices size: ", this->before_input_unicode_vertices_size);
		ql::println("before input unicode outline vertices size: ", this->before_input_unicode_outline_vertices_size);
		ql::println("before input text rows: ", this->before_input_text_rows);
		ql::println("before input text position: ", this->before_input_text_position);
		ql::println("cursor position: ", this->cursor_position);
		ql::println("clicked mouse position: ", this->clicked_mouse_position);
		ql::println("character size: ", this->character_size);
		ql::println("input history: ", this->input_history);
		ql::println("input history index: ", this->input_history_index);
		ql::println("accept input: ", this->accept_input);
		ql::println("hidden input: ", this->hidden_input);
		ql::println("text entered: ", this->text_entered);
		ql::println("line entered: ", this->line_entered);
		ql::println("text dragging: ", this->text_dragging);
		ql::println("allow text dragging: ", this->allow_text_dragging);
		ql::println("allow going up with cursor: ", this->allow_going_up_with_cursor);
		ql::println("border texture set: ", this->border_texture_set);
	}

	void ql::console::press_enter_to_continue_mode()
	{
		this->enter_to_continue = true;
	}

	void ql::console::reset_visible_range()
	{
		this->visible_y_min = 0;
		this->visible_y_max = 0;
	}

	void ql::console::clear()
	{
		this->colored_text.clear();
		this->string.clear();
		this->input_string.clear_copy_style_self();
		this->string_and_input.clear();
		this->input_string_split.clear();
		this->string_split.clear();
		this->string_and_input_split.clear();
		this->selection_rectangle.clear();
		this->visible_y_min = 0;
		this->visible_y_max = 0;
		this->cursor_position = {0, 0};
		this->view_row = 0u;
		this->view.position.y = 0;
		this->visible_rows = 0u;

		this->process_text();
	}

	void ql::console::init()
	{
		this->scroll_transition_animation.set_duration(0.4);
		this->view.position.x = -10.0f;
		this->update_cursor_dimension();
		this->update_cursor_position();
	}

	void ql::console::apply_font()
	{
		this->init();
		this->calculate_default_character_size();
	}

	void ql::console::set_border_texture(const sf::Texture& texture)
	{
		// this->shadow_border.set_texture(texture);
		// this->shadow_border.set_color(this->shadow_border_color);
		// this->shadow_border.set_scale(0.2f);
		// this->shadow_border.clear();
		// this->shadow_border.add_top();

		this->scroll_bar_shadow_border.set_texture(texture);
		// this->scroll_bar_shadow_border.set_color(this->shadow_border_color);
		this->scroll_bar_shadow_border.set_color(ql::rgb::grey_shade(10));
		this->scroll_bar_shadow_border.set_scale(0.125f);
		this->scroll_bar_shadow_border.clear();
		this->scroll_bar_shadow_border.add_right();

		this->border_texture_set = true;
	}

	void ql::console::set_font(std::string font)
	{
		this->colored_text.set_font(ql::get_font(font));
		this->apply_font();
	}

	void ql::console::set_unicode_font(std::string font)
	{
		this->colored_text.set_unicode_font(ql::get_font(font));
		this->apply_font();
	}

	void ql::console::calculate_default_character_size()
	{
		this->character_size.y = this->colored_text.get_line_spacing_pixels();
		this->character_size.x = this->colored_text.get_white_space_width();
	}

	void ql::console::track_before_input_values()
	{
		this->before_input_vertices_size = this->colored_text.vertices.size();
		this->before_input_outline_vertices_size = this->colored_text.outline_vertices.size();
		this->before_input_unicode_vertices_size = this->colored_text.unicode_vertices.size();
		this->before_input_unicode_outline_vertices_size = this->colored_text.unicode_outline_vertices.size();
		this->before_input_text_position = this->colored_text.text_position;
		this->before_input_text_rows = this->colored_text.rows;
	}

	void ql::console::start_accepting_input()
	{
		if (this->accept_input)
		{
			return;
		}
		this->accept_input = true;
		this->track_before_input_values();
		this->cursor_position = {0, 0};
		this->update_cursor_position(true);
		this->move_to_input();
	}

	void ql::console::stop_accepting_input()
	{
		this->accept_input = false;
		this->string << this->input_string;
		this->input_string.clear_copy_style_self();
	}

	void ql::console::clamp_view_y(bool transition)
	{
		if (transition)
		{
			this->scroll_transition_start = this->view.position.y;
		}
		auto max_rows = ql::isize_cast((this->dimension.y * this->view.scale.y) / this->colored_text.get_line_spacing_pixels());
		this->view_row = ql::max(0ll, this->view_row);

		if (transition)
		{
			this->scroll_transition_end = this->view_row * this->colored_text.get_line_spacing_pixels();
			this->scroll_transition_animation.reset_and_start();
		}
	}

	void ql::console::set_dimension(ql::vec2f dimension)
	{
		this->dimension = dimension;
		auto width = 25.0f;
		auto margin = 5.0f;
		this->scroll_bar.set_position({this->dimension.x - width, margin});
		this->scroll_bar.set_dimension(ql::vec2f(width, this->dimension.y - margin * 2));
		this->update_visible_rows_count();
		this->clamp_view_y();
		this->scroll_bar.update_knob();
		this->make_selection_rectangles();

		if (this->border_texture_set)
		{
			// this->shadow_border.set_dimension(dimension);
			// this->shadow_border.clear();
			// this->shadow_border.add_top();

			this->scroll_bar_shadow_border.set_dimension(ql::vec(this->scroll_bar.hitbox.position.x, dimension.y));
			this->scroll_bar_shadow_border.clear();
			this->scroll_bar_shadow_border.add_right();
		}
		this->update_cursor_position(false);
	}

	void ql::console::set_input_color(ql::print_color color)
	{
		this->input_string << color;
	}

	void ql::console::prepare_scroll()
	{
		this->scroll_bar_transition_start = this->scroll_bar.visible_knob_progress;
		this->scroll_bar.set_progress(this->view_row / ql::f32_cast(this->colored_text.rows - this->visible_rows));
		this->scroll_bar_transition_end = this->scroll_bar.get_progress();

		this->clamp_view_y();
	}

	void ql::console::update_visible_rows_count()
	{
		this->visible_rows = ql::size_cast(std::floor(this->dimension.y / this->colored_text.get_line_spacing_pixels()));
		this->scroll_bar.set_progress_integer_step(this->colored_text.rows + 1, this->visible_rows);
	}

	void ql::console::end_animation()
	{
		this->scroll_transition_start = this->scroll_transition_end;
		this->view.position.y = ql::f32_cast(this->scroll_transition_end);
		this->scroll_bar.set_visible_knob_progress(this->scroll_bar_transition_end);
		this->scroll_transition_animation.reset();
	}

	void ql::console::update_string_and_input_split()
	{
		this->string_and_input = this->string;

		if (this->hidden_input)
		{
			auto element = this->input_string.elements.back();
			element.text = ql::to_basic_string<char32_t>(ql::to_string_repeat('*', element.text.length()));
			this->string_and_input << element.text;
		}
		else
		{
			this->string_and_input << this->input_string;
		}
		this->string_and_input_split =
				ql::string_split_allow_empty(ql::to_basic_string<wchar_t>(this->string_and_input.string()), L'\n');
	}

	void ql::console::update_string_split()
	{
		this->string_split = ql::string_split_allow_empty(ql::to_basic_string<wchar_t>(this->string.string()), L'\n');
	}

	void ql::console::update_input_string_split()
	{
		this->input_string_split = ql::string_split_allow_empty(ql::to_basic_string<wchar_t>(this->input_string.string()), L'\n');
		this->update_string_and_input_split();
	}

	void ql::console::update_cursor_position(bool reset_timer)
	{
		auto cursor_pos_with_tabs = this->cursor_position;
		if (this->cursor_position.y < this->input_string_split.size())
		{
			auto count = ql::count(this->input_string_split[this->cursor_position.y].substr(0u, this->cursor_position.x), L'\t');
			cursor_pos_with_tabs.x += count * 3u;
		}

		auto off = cursor_pos_with_tabs * this->character_size;

		this->cursor.set_position(this->before_input_text_position + off - ql::vec(0.0f, this->colored_text.character_size));
		if (reset_timer)
		{
			this->cursor_blink_timer.reset();
		}
	}

	void ql::console::update_input_text_graphics()
	{
		this->colored_text.text_position = this->before_input_text_position;

		if (this->before_input_vertices_size != ql::size_max)
		{
			this->colored_text.vertices.resize(this->before_input_vertices_size);
		}
		if (this->before_input_outline_vertices_size != ql::size_max)
		{
			this->colored_text.outline_vertices.resize(this->before_input_outline_vertices_size);
		}
		if (this->before_input_unicode_vertices_size != ql::size_max)
		{
			this->colored_text.unicode_vertices.resize(this->before_input_unicode_vertices_size);
		}
		if (this->before_input_unicode_outline_vertices_size != ql::size_max)
		{
			this->colored_text.unicode_outline_vertices.resize(this->before_input_unicode_outline_vertices_size);
		}

		this->colored_text.rows = this->before_input_text_rows;

		if (this->hidden_input)
		{
			auto element = this->input_string.elements.back();
			element.text = ql::to_basic_string<char32_t>(ql::to_string_repeat('*', element.text.length()));
			ql::styled_string<std::u32string> string;
			string.add(element);
			this->colored_text.add(string);
		}
		else
		{
			this->colored_text.add(this->input_string);
		}
		// this->reset_visible_range();
		this->update_cursor_position(false);
	}

	void ql::console::add_text_input(const std::u32string& string, bool at_end)
	{
		auto size = this->string_split.size();
		auto pos = this->cursor_position;

		if (at_end)
		{
			pos.y = this->get_input_text_height() - 1;
			pos.x = this->get_input_text_width(pos.y);

			this->cursor_position = pos;
		}

		pos.x = ql::max(0ll, ql::signed_cast(pos.x));

		auto count = ql::count(ql::to_basic_string<wchar_t>(string), L'\n');
		if (count)
		{
			auto split = ql::string_split_allow_empty(ql::to_basic_string<wchar_t>(string), L'\n');
			this->cursor_position.y += count;
			if (split.size())
			{
				this->cursor_position.x = split.back().length();
			}
			else
			{
				this->cursor_position.x = 0u;
			}
		}
		else
		{
			this->cursor_position.x += string.length();
		}
		this->input_string.add_text_at(pos, string);

		this->update_input_text_graphics();
		this->update_input_string_split();
		this->update_cursor_position(true);
	}

	void ql::console::pop_character_at_cursor()
	{
		if (this->input_string.size() && this->input_string.elements.back().text.length())
		{
			auto size = this->string_split.size();
			auto pos = this->cursor_position;
			pos.x = ql::max(0ll, ql::signed_cast(pos.x));

			if (this->cursor_position.x)
			{
				--this->cursor_position.x;
				this->update_cursor_position(true);
			}
			else if (this->cursor_position.y)
			{
				--this->cursor_position.y;
				this->cursor_position.x = this->get_input_text_width(this->cursor_position.y);
				this->update_cursor_position(true);
			}
			this->input_string.remove_character_at(pos);
			this->update_input_string_split();
			this->update_input_text_graphics();
		}
	}

	void ql::console::update_cursor_dimension()
	{
		this->cursor.set_dimension(ql::vec(3.0f, this->colored_text.get_line_spacing_pixels()));
	}

	void ql::console::update_text_range()
	{
		auto y = this->view.position.y / this->character_size.y;
		auto min_y = y;
		auto max_y = y + this->visible_rows;

		if (min_y < this->visible_y_min || max_y > this->visible_y_max)
		{
			this->visible_y_min = ql::isize_cast(min_y - visible_buffer);
			this->visible_y_max = ql::isize_cast(max_y + visible_buffer);

			auto a = this->visible_y_min * this->character_size.y;
			auto b = this->visible_y_max * this->character_size.y;

			this->colored_text.create(this->string_and_input, a, b);
		}
	}

	void ql::console::process_character_size()
	{
		this->reset_visible_range();

		if (this->accept_input)
		{
			if (this->hidden_input)
			{
				this->input_string_split = ql::string_split_allow_empty(
						ql::to_basic_string<wchar_t>(ql::to_string_repeat('*', this->input_string.string().length())), L'\n'
				);
			}
			else
			{
				this->input_string_split = ql::string_split_allow_empty(ql::to_basic_string<wchar_t>(this->input_string.string()), L'\n');
			}
		}

		auto text_pos_before = this->before_input_text_position / this->character_size;

		this->scroll_bar.set_progress(this->view_row / ql::f32_cast(this->colored_text.rows - this->visible_rows));
		this->scroll_bar.set_visible_knob_progress(this->view_row / ql::f64_cast(this->scroll_bar.integer_step));
		this->view.position.y = this->view_row * this->colored_text.get_line_spacing_pixels();
		this->calculate_default_character_size();

		auto pos = text_pos_before * this->character_size;
		pos.x = 0.f;
		this->before_input_text_position = pos;

		this->update_input_string_split();
		this->update_input_text_graphics();
		this->update_cursor_dimension();
		this->update_cursor_position(false);
		this->make_selection_rectangles();

		this->update_visible_rows_count();
		this->clamp_view_y(false);
		this->prepare_scroll();
		this->end_animation();
	}

	ql::size ql::console::get_text_height() const
	{
		return this->string_and_input_split.size();
	}

	ql::size ql::console::get_text_width(ql::size y) const
	{
		if (y >= this->string_and_input_split.size())
		{
			return 0u;
		}
		return this->string_and_input_split[y].length();
	}

	ql::size ql::console::get_input_text_width(ql::size y) const
	{
		if (y >= this->input_string_split.size())
		{
			return 0u;
		}
		return this->input_string_split[y].length();
	}

	ql::size ql::console::get_input_text_height() const
	{
		return this->input_string_split.size();
	}

	ql::vec2f ql::console::position_to_text_position(ql::vec2f position) const
	{
		return position / this->character_size;
	}

	void ql::console::clear_selection_rectangles_if_visible()
	{
		if (this->selection_rectangle.size())
		{
			this->selection_rectangle.clear();
		}
	}

	auto ql::console::get_selection_rectangle_bounds() const
	{
		auto fmin = this->selection_rectangle_start;
		auto fmax = this->selection_rectangle_end;

		fmin.y = ql::max(0.f, fmin.y);
		fmin.x = ql::max(0.f, fmin.x);
		fmax.y = ql::max(0.f, fmax.y);
		fmax.x = ql::max(0.f, fmax.x);

		if (ql::isize_cast(fmax.y) < ql::isize_cast(fmin.y))
		{
			std::swap(fmin, fmax);
		}
		else if (ql::isize_cast(fmin.y) == ql::isize_cast(fmax.y) && fmax.x < fmin.x)
		{
			std::swap(fmin, fmax);
		}

		auto min = ql::vec2is{std::round(fmin.x), fmin.y};
		auto max = ql::vec2is{
				std::round(fmax.x), ql::min(ql::size_cast(fmax.y), this->get_text_height() ? this->get_text_height() - 1 : 0ull)
		};
		return std::make_pair(min, max);
	}

	std::wstring ql::console::get_selection_rectangle_string() const
	{
		std::wstring result = L"";

		auto [min, max] = this->get_selection_rectangle_bounds();

		for (ql::isize y = min.y; y <= max.y; ++y)
		{
			if (min.y == max.y)
			{
				if (min.x <= ql::signed_cast(this->string_and_input_split[y].length()))
				{
					auto size = max.x - min.x;
					result += this->string_and_input_split[y].substr(min.x, size);
				}
			}
			else if (y == min.y)
			{
				if (min.x <= ql::signed_cast(this->string_and_input_split[y].length()))
				{
					result += this->string_and_input_split[y].substr(min.x);
				}
				result += L'\n';
			}
			else if (y == max.y)
			{
				if (max.x && max.x <= ql::signed_cast(this->string_and_input_split[y].length()))
				{
					result += this->string_and_input_split[y].substr(0u, max.x);
				}
			}
			else
			{
				if (this->string_and_input_split[y].size())
				{
					result += this->string_and_input_split[y];
				}
				result += L'\n';
			}
		}
		return result;
	}

	void ql::console::make_selection_rectangles()
	{
		auto [min, max] = this->get_selection_rectangle_bounds();

		max.y = ql::min(max.y, ql::signed_cast(this->get_text_height() - 1));

		auto size = ql::max(0ll, (max.y - min.y) + 1);
		this->selection_rectangle.resize(size);

		for (ql::isize i = min.y; i <= max.y; ++i)
		{
			auto index = i - min.y;
			auto pos = ql::vec2s(0ull, i);
			ql::size width = 0u;

			if (min.y == max.y)
			{
				auto text_width = this->get_text_width(max.y);
				min.x = ql::min(min.x, ql::signed_cast(text_width));
				max.x = ql::min(max.x, ql::signed_cast(text_width));
				pos.x = min.x;
				width = ql::size_cast((max.x - min.x) * this->colored_text.get_white_space_width());
			}
			else if (i == min.y)
			{
				auto text_width = this->get_text_width(min.y);
				min.x = ql::min(min.x, ql::signed_cast(text_width));
				pos.x = min.x;
				width = ql::size_cast(this->dimension.x - (pos.x * this->character_size.x));
			}
			else if (i == max.y)
			{
				auto text_width = this->get_text_width(max.y);
				max.x = ql::min(max.x, ql::signed_cast(text_width));
				width = ql::size_cast(max.x * this->colored_text.get_white_space_width());
			}
			else
			{
				width = ql::size_cast(this->dimension.x);
			}

			auto offset_y = this->colored_text.get_chracter_top_offset() - this->colored_text.get_character_size() / 10.f;
			this->selection_rectangle[index].set_position(pos * this->character_size + ql::vec(0.f, offset_y));
			this->selection_rectangle[index].set_dimension(ql::vec(width, this->colored_text.get_line_spacing_pixels()));
			this->selection_rectangle[index].set_color(this->selection_rectangle_color);
		}
	}

	void ql::console::move_to_input()
	{
		auto input_pos = ql::isize_cast(this->colored_text.rows - this->visible_rows) + 1;
		auto input_pos_end = ql::isize_cast(this->colored_text.rows);
		if (input_pos_end < ql::signed_cast(this->visible_rows))
		{
			input_pos_end = 0;
		}
		if (this->view_row < input_pos)
		{
			this->view_row = input_pos;
			this->prepare_scroll();
		}
		if (this->view_row > input_pos_end)
		{
			this->view_row = input_pos_end;
			this->prepare_scroll();
		}
	}

	auto ql::console::get_input_text() const
	{
		return this->input_string.string();
	}

	std::wstring ql::console::get_last_input_line(bool consider_new_line) const
	{
		if (this->input_string_split.empty())
		{
			return L"";
		}
		return this->input_string_split[this->input_string_split.size() - (consider_new_line ? 2u : 1u)];
	}

	void ql::console::process_text()
	{
		this->update_visible_rows_count();
		this->scroll_bar.set_progress(this->view_row / ql::f32_cast(this->scroll_bar.integer_step));
		this->update_cursor_position();

		auto size = this->colored_text.vertices.size() + this->colored_text.outline_vertices.size();
		this->update_string_split();
		this->update_string_and_input_split();
	}

	void ql::console::add(const ql::styled_string<std::u32string>& string)
	{
		this->colored_text.add(string);
		this->string << string;
		this->process_text();
	}

	void ql::console::create(const ql::styled_string<std::u32string>& string)
	{
		this->colored_text.clear();
		this->string.clear();
		this->add(string);
		this->update_cursor_position(true);
	}

	void ql::console::paste_from_clipboard()
	{
		this->clear_selection_rectangles_if_visible();
		this->add_text_input(ql::to_basic_string<char32_t>(ql::copy_from_clipboard()));
		this->text_entered = true;
		this->update_visible_rows_count();
		this->clear_selection_rectangles_if_visible();
	}

	void ql::console::update_key_input(const ql::event_manager& event)
	{
		this->line_entered = false;
		this->text_entered = false;
		this->exited_enter_to_continue = false;
		if (!this->accept_input)
		{
			return;
		}
		bool special_input = false;

		if (!this->enter_to_continue)
		{
			if (event.mouse_button_clicked(sf::Mouse::Middle))
			{
				this->paste_from_clipboard();
			}
			if (event.key_holding(sf::Keyboard::LControl))
			{
				special_input = true;
				if (event.key_pressed(sf::Keyboard::V))
				{
					this->paste_from_clipboard();
				}
				if (event.key_pressed(sf::Keyboard::C))
				{
					ql::copy_to_clipboard(this->get_selection_rectangle_string());
					this->clear_selection_rectangles_if_visible();
				}
				if (event.key_pressed(sf::Keyboard::A))
				{
					this->selection_rectangle_start = {0, 0};
					this->selection_rectangle_end = ql::vec2f(this->string_and_input_split.back().length(), this->get_text_height());
					this->make_selection_rectangles();
				}
			}
			if (event.key_pressed(sf::Keyboard::Backspace))
			{
				this->clear_selection_rectangles_if_visible();

				if (this->allow_going_up_with_cursor || this->cursor_position.x)
				{
					this->pop_character_at_cursor();
				}
				special_input = true;
			}

			if (event.key_pressed(sf::Keyboard::Right))
			{
				this->clear_selection_rectangles_if_visible();
				if (this->cursor_position.x < this->get_input_text_width(this->cursor_position.y))
				{
					++this->cursor_position.x;
					this->update_cursor_position(true);
				}
				else if (ql::signed_cast(this->cursor_position.y) < ql::signed_cast(this->get_input_text_height()) - 1)
				{
					++this->cursor_position.y;
					this->cursor_position.x = 0u;
					this->update_cursor_position(true);
				}
			}
			if (event.key_pressed(sf::Keyboard::Left))
			{
				this->clear_selection_rectangles_if_visible();
				if (this->cursor_position.x)
				{
					--this->cursor_position.x;
					this->update_cursor_position(true);
				}
				else if (this->allow_going_up_with_cursor && this->cursor_position.y)
				{
					--this->cursor_position.y;
					this->cursor_position.x = this->get_input_text_width(this->cursor_position.y);
					this->update_cursor_position(true);
				}
			}
			if (event.key_pressed(sf::Keyboard::Up))
			{
				this->clear_selection_rectangles_if_visible();
				if (!this->allow_going_up_with_cursor || this->get_input_text_height() <= 1u)
				{
					if (this->input_history_index)
					{
						--this->input_history_index;
					}

					if (this->input_history_index < this->input_history.size())
					{
						this->input_string.clear_last_line();
						this->update_input_text_graphics();
						this->update_input_string_split();

						this->cursor_position.x = 0u;
						const auto& history_text = this->input_history[this->input_history_index];

						this->add_text_input(ql::to_basic_string<char32_t>(history_text));
						this->cursor_position.x = history_text.length();

						this->update_input_text_graphics();
						this->update_input_string_split();
						this->update_cursor_position(true);
					}
				}
				else if (this->allow_going_up_with_cursor && this->cursor_position.y)
				{
					--this->cursor_position.y;
					this->cursor_position.x = ql::min(this->cursor_position.x, this->get_input_text_width(this->cursor_position.y));
					this->update_cursor_position(true);
				}
				special_input = true;
			}
			if (event.key_pressed(sf::Keyboard::Down))
			{
				this->clear_selection_rectangles_if_visible();
				if (!this->allow_going_up_with_cursor || this->get_input_text_height() <= 1u)
				{
					if (this->input_history.empty() || (this->input_history_index >= this->input_history.size() - 1))
					{
						this->input_string.clear_last_line();
						this->update_input_string_split();
						this->update_input_text_graphics();
						this->cursor_position.x = 0u;
						this->update_cursor_position(true);
					}
					else
					{
						++this->input_history_index;
						this->input_string.clear_last_line();
						const auto& history_text = this->input_history[this->input_history_index];
						this->add_text_input(ql::to_basic_string<char32_t>(history_text));
						this->cursor_position.x = history_text.length();
						this->update_input_text_graphics();
						this->update_input_string_split();
						this->update_cursor_position(true);
					}
				}
				else if (ql::signed_cast(this->cursor_position.y) < ql::signed_cast(this->get_input_text_height()) - 1)
				{
					++this->cursor_position.y;
					this->cursor_position.x = ql::min(this->cursor_position.x, this->get_input_text_width(this->cursor_position.y));
					this->update_cursor_position(true);
				}
				special_input = true;
			}
			if (event.key_pressed(sf::Keyboard::Escape))
			{
				special_input = true;
				this->input_string.clear_last_line();
				this->update_input_string_split();
				this->update_input_text_graphics();
				this->cursor_position.x = 0u;
				this->update_cursor_position(true);
			}
		}
		if (event.key_pressed(sf::Keyboard::Enter))
		{
			auto new_line = this->add_new_line_on_enter || event.key_holding(sf::Keyboard::LShift);
			this->add_text_input(ql::to_basic_string<char32_t>('\n'), !new_line && !this->allow_going_up_with_cursor);

			special_input = true;

			if (this->enter_to_continue)
			{
				this->enter_to_continue = false;
				this->exited_enter_to_continue = true;
			}
			this->line_entered = true;
			this->text_entered = true;

			auto last_input = this->get_last_input_line();

			if (!last_input.empty())
			{
				this->input_history.push_back(last_input);
				this->input_history_index = this->input_history.size();
			}
		}
		if (!this->enter_to_continue && event.is_text_entered() && !special_input)
		{
			this->add_text_input(event.u32_text_entered());
			this->text_entered = true;
		}
	}

	void ql::console::update_selection_rectangle(const ql::event_manager& event)
	{
		if (event.left_mouse_clicked() && this->allow_text_dragging)
		{
			this->clicked_mouse_position = event.mouse_position();
			this->text_dragging = true;

			this->selection_rectangle_start = this->position_to_text_position(event.mouse_position() + this->view.position);
		}
		if (this->text_dragging)
		{
			this->selection_rectangle_end = this->position_to_text_position(event.mouse_position() + this->view.position);

			auto zoom_factor = ql::max(1ll, 2 + this->zooms / 2);
			if (this->selection_rectangle_end.y < this->view_row)
			{
				this->view_row -= zoom_factor;
				this->view_row = ql::max(0ll, this->view_row);
				this->prepare_scroll();
			}
			if (this->selection_rectangle_end.y > ql::signed_cast(this->view_row + (this->visible_rows - 2)))
			{
				this->view_row += zoom_factor;
				this->prepare_scroll();
			}
			this->make_selection_rectangles();
		}

		if (event.left_mouse_released())
		{
			this->text_dragging = false;
		}
	}

	void ql::console::update_cursor()
	{
		auto f = this->cursor_blink_timer.elapsed_f();
		ql::f64 progress = 1.0;
		if (f > 0.5)
		{
			auto time = (f - 0.5) / this->cursor_interval_duration;
			progress = 1.0 - ql::triangle_progression(std::fmod(time, 1.0));
		}
		this->cursor.set_color(this->cursor.get_color().with_alpha(ql::u8_cast(progress * 255)));
	}

	void ql::console::update(const ql::event_manager& event)
	{
		this->scroll_bar.allow_dragging = !this->text_dragging;

		event.update(this->scroll_bar);
		this->allow_text_dragging = !(this->scroll_bar.hovering || this->scroll_bar.hovering_background);
		this->update_selection_rectangle(event);

		if (this->scroll_bar.value_changed)
		{
			this->view_row = this->scroll_bar.get_progress_step();
			this->scroll_bar_transition_start = this->scroll_bar_transition_end = this->scroll_bar.visible_knob_progress;
			this->clamp_view_y();
		}
		if (this->scroll_bar.released_dragging)
		{
			this->scroll_bar_transition_start = this->scroll_bar_transition_end = this->scroll_bar.visible_knob_progress;
			this->prepare_scroll();
		}
		if (this->scroll_bar.clicked_on_background_above)
		{
			--this->view_row;
			this->prepare_scroll();
		}
		if (this->scroll_bar.clicked_on_background_below)
		{
			++this->view_row;
			this->prepare_scroll();
		}

		if (this->visible_rows)
		{
			if (event.key_holding(sf::Keyboard::LControl))
			{
				if (event.scrolled_down())
				{
					if (this->colored_text.character_size > 2)
					{
						this->end_animation();

						this->colored_text.character_size--;
						this->process_character_size();
						++this->zooms;
					}
				}
				if (event.scrolled_up())
				{
					this->end_animation();

					this->colored_text.character_size++;
					this->process_character_size();
					--this->zooms;
				}
			}
			else
			{
				if (event.scrolled_down())
				{
					this->view_row += ql::max(1ll, (3 + this->zooms / 2));
					this->view_row = ql::min(this->view_row, ql::isize_cast(this->colored_text.rows - 3u));
					this->prepare_scroll();
				}
				if (event.scrolled_up())
				{
					this->view_row -= ql::max(1ll, (3 + this->zooms / 2));
					this->prepare_scroll();
				}
			}
		}

		if (event.key_pressed(sf::Keyboard::End))
		{
			this->move_to_input();
		}

		if (event.right_mouse_clicked())
		{
			this->paste_from_clipboard();
		}

		this->update_key_input(event);

		if (this->text_entered)
		{
			this->move_to_input();
		}
		if (this->line_entered)
		{
			this->update_visible_rows_count();
		}

		this->scroll_transition_animation.update(event);
		if (this->scroll_transition_animation.is_running())
		{
			auto p = this->scroll_transition_animation.get_progress();
			// auto curve = ql::smooth_slope(p);
			auto curve = ql::smooth_curve(p, 1.5);
			this->view.position.y =
					ql::f32_cast(ql::linear_interpolation(this->scroll_transition_start, this->scroll_transition_end, curve));

			if (!this->scroll_bar.dragging)
			{
				this->scroll_bar.set_visible_knob_progress(
						ql::linear_interpolation(this->scroll_bar_transition_start, this->scroll_bar_transition_end, curve)
				);
			}
		}
		if (this->scroll_transition_animation.just_finished())
		{
			this->scroll_transition_start = this->scroll_transition_end;
			this->scroll_bar_transition_start = this->scroll_bar_transition_end;
		}
		this->update_cursor();
		this->update_text_range();

		if (event.key_holding(sf::Keyboard::LShift) && event.holding_middle_mouse())
		{
			this->view.move(-event.delta_mouse_position());
		}
	}

	void ql::console::draw(ql::render& draw) const
	{
		auto copy = this->view;
		copy.position.y += this->colored_text.get_chracter_top_offset();
		if (this->accept_input)
		{
			draw.draw(this->cursor, copy);
		}
		draw.draw(this->colored_text, copy);
		draw.draw(this->selection_rectangle, copy);

		if (this->border_texture_set && this->scroll_bar.knob_range < 1.0f)
		{
			// if (this->view_row > 1) {
			//	draw.draw(this->shadow_border);
			// }
			draw.draw(this->scroll_bar_shadow_border);
		}
		draw.draw(this->scroll_bar);
	}

}	 // namespace ql

#endif
