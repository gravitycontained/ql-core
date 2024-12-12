#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/color/color.hpp>
#include <ql/core/advanced-type/fundamental/vector.hpp>
#include <ql/core/time/time.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/drawable/basic/text/text.hpp>
#include <ql/graphic/drawable/advanced/smooth-rectangle/smooth-rectangle.hpp>

#include <SFML/Graphics.hpp>

namespace ql
{
	struct smooth_button
	{
		ql::text text;
		ql::vsmooth_rectangle smooth_layout;
		mutable ql::smooth_rectangle rectangle;
		ql::vec2 hitbox_increase;
		ql::animation hover_animation;
		ql::rgba background_color = ql::rgba(70, 70, 70);
		ql::rgba background_outline_color = ql::rgba::black();
		ql::rgba text_color = ql::rgba(220, 220, 220);
		ql::rgba background_color_hover = ql::rgba(10, 10, 10);
		ql::rgba text_color_hover = ql::rgba::white();
		ql::rgba text_color_click = ql::rgba(100, 255, 100);
		ql::small_clock click_timer;
		mutable bool layout_changed = false;
		bool simple_hitbox = false;
		bool hovering = false;
		bool clicked = false;
		bool clicked_once = false;
		bool use_basic_hover_animation = true;
		bool hover_before = false;

		smooth_button()
		{
			this->set_background_color(ql::rgba::black());
			this->hover_animation.set_duration(0.1);
			this->enable_simple_hitbox();
		}

		QL_SOURCE void enable_simple_hitbox();
		QL_SOURCE void disable_simple_hitbox();
		QL_SOURCE void set_hitbox_increase(ql::vec2 delta);
		QL_SOURCE void set_hitbox_increase(ql::f32 delta);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_hitbox(ql::hitbox hitbox);
		QL_SOURCE void set_center(ql::vec2 position);
		QL_SOURCE void set_slope(ql::f64 slope);
		QL_SOURCE void set_background_color(ql::rgba color);
		QL_SOURCE void set_background_outline_thickness(ql::f32 thickness);
		QL_SOURCE void set_background_outline_color(ql::rgba color);
		QL_SOURCE void set_background_slope_dimension(ql::vec2 dimension);
		QL_SOURCE void set_background_slope_point_count(ql::size point_count);
		QL_SOURCE void set_text_font(const sf::Font& font);
		QL_SOURCE void set_text_font(const std::string& font_name);
		QL_SOURCE void set_text_style(ql::u32 style);
		QL_SOURCE void set_text_character_size(ql::u32 character_size);
		QL_SOURCE void set_text_color(ql::rgba color);
		QL_SOURCE void set_text_outline_thickness(ql::f32 outline_thickness);
		QL_SOURCE void set_text_outline_color(ql::rgba color);
		QL_SOURCE void set_text_rotation(ql::f32 angle);
		QL_SOURCE void set_text_letter_spacing(ql::f32 spacing);
		QL_SOURCE void set_text_position(ql::vec2 position);
		QL_SOURCE void set_text_center(ql::vec2 position);
		QL_SOURCE void set_text_string(const std::string& string);
		QL_SOURCE void set_text_string(const std::wstring& string);
		QL_SOURCE void centerize_text();

		QL_SOURCE ql::vec2 get_hitbox_increase() const;
		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE ql::hitbox get_hitbox() const;
		QL_SOURCE ql::f64 get_slope() const;
		QL_SOURCE ql::rgba get_background_color() const;
		QL_SOURCE ql::f32 get_background_outline_thickness() const;
		QL_SOURCE ql::rgba get_background_outline_color() const;
		QL_SOURCE ql::vec2 get_slope_dimension() const;
		QL_SOURCE ql::size get_slope_point_count() const;
		QL_SOURCE std::string get_text_font() const;
		QL_SOURCE ql::u32 get_text_style() const;
		QL_SOURCE ql::u32 get_text_character_size() const;
		QL_SOURCE ql::rgba get_text_color() const;
		QL_SOURCE ql::f32 get_text_outline_thickness() const;
		QL_SOURCE ql::rgba get_text_outline_color() const;
		QL_SOURCE ql::f32 get_text_letter_spacing() const;
		QL_SOURCE ql::vec2 get_text_position() const;
		QL_SOURCE ql::vec2 get_text_center() const;
		QL_SOURCE std::string get_text_string() const;
		QL_SOURCE std::wstring get_text_wstring() const;
		QL_SOURCE bool is_hovering() const;
		QL_SOURCE bool is_clicked() const;

		QL_SOURCE void update(const ql::event& event);

		QL_SOURCE void create_check() const;
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
	};

}	 // namespace ql

#endif