#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/color/color.hpp>
#include <ql/core/advanced-type/fundamental/vector.hpp>

#if defined QL_GRAPHIC

namespace ql
{
	struct vtext
	{
		QL_SOURCE void set_font(const std::string& font_name);
		QL_SOURCE void set_style(ql::u32 style);
		QL_SOURCE void set_character_size(ql::u32 character_size);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_outline_thickness(ql::f32 outline_thickness);
		QL_SOURCE void set_outline_color(ql::rgba color);
		QL_SOURCE void set_letter_spacing(ql::f32 spacing);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_string(const std::string& string);
		QL_SOURCE bool operator==(const vtext& other) const;

		template <typename T, typename... Args>
		requires (ql::is_printable<T, Args...>())
		void set_string(T first, Args... values)
		{
			this->set_string(ql::to_string(first, values...));
		}

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::string font_name;
		ql::u32 style = sf::Text::Style::Regular;
		ql::u32 character_size = 22u;
		ql::f32 outline_thickness = 0.0f;
		ql::rgba color = ql::rgba::white();
		ql::rgba outline_color;
		ql::f32 letter_spacing = 1.0f;
		ql::vec2 position;
		std::string string;
	};

	struct text
	{
		ql::text()
		{
		}

		ql::text(const ql::vtext& other)
		{
			*this = other;
		}


		QL_SOURCE const sf::Font& get_sf_font() const;
		QL_SOURCE const sf::Glyph& get_glyph(ql::wchar_type c) const;
		QL_SOURCE ql::hitbox get_glyph_hitbox(ql::wchar_type c) const;
		QL_SOURCE ql::f32 get_character_advance(ql::wchar_type current) const;
		QL_SOURCE ql::f32 get_next_character_advance() const;
		QL_SOURCE ql::f32 get_line_spacing_pixels() const;
		QL_SOURCE ql::f32 get_line_spacing() const;

		QL_SOURCE ql::f32 get_letter_spacing_pixels() const;
		QL_SOURCE ql::f32 get_whitespace_width() const;
		QL_SOURCE ql::f32 get_italic_shear() const;

		QL_SOURCE bool is_bold() const;
		QL_SOURCE std::string get_font() const;
		QL_SOURCE ql::u32 get_style() const;
		QL_SOURCE ql::u32 get_character_size() const;
		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE ql::rgba get_outline_color() const;
		QL_SOURCE ql::f32 get_outline_thickness() const;
		QL_SOURCE ql::f32 get_letter_spacing() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE std::string get_string() const;
		QL_SOURCE std::wstring get_wstring() const;
		QL_SOURCE sf::String get_sfstring() const;
		QL_SOURCE void set_font(const sf::Font& font);
		QL_SOURCE void set_font(const std::string& font_name);
		QL_SOURCE void set_style(ql::u32 style);
		QL_SOURCE void set_character_size(ql::u32 character_size);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_outline_color(ql::rgba color);
		QL_SOURCE void set_outline_thickness(ql::f32 outline_thickness);
		QL_SOURCE void set_rotation(ql::f32 angle);
		QL_SOURCE void set_letter_spacing(ql::f32 spacing);
		QL_SOURCE void set_line_spacing(ql::f32 spacing);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_center(ql::vec2 position);
		QL_SOURCE void set_string(const std::string& string);
		QL_SOURCE void set_string(const std::wstring& string);
		QL_SOURCE void set_string(const sf::String& string);

		template <typename T, typename... Args>
		requires (ql::is_printable<T, Args...>())
		void set_string(T first, Args... values)
		{
			this->set_string(ql::to_string(first, values...));
		}

		QL_SOURCE void centerize();
		QL_SOURCE void centerize_x();
		QL_SOURCE void centerize_y();
		QL_SOURCE void move(ql::vec2 delta);

		QL_SOURCE ql::vec2 find_character_position(ql::size index) const;
		QL_SOURCE ql::f32 get_underline_baseline() const;
		QL_SOURCE ql::f32 get_underline_thickness() const;
		QL_SOURCE ql::f32 get_character_size_plus_baseline() const;
		QL_SOURCE std::vector<std::pair<ql::size, ql::hitbox>> get_all_characters_hitbox() const;
		QL_SOURCE std::vector<ql::hitbox> get_all_characters_hitbox_whitespace_included() const;
		QL_SOURCE ql::vec2 get_starting_line_position() const;
		QL_SOURCE ql::f32 get_delta_underline() const;
		QL_SOURCE ql::f32 get_line_height() const;
		QL_SOURCE ql::vec2 get_character_dimension(wchar_t character) const;
		QL_SOURCE ql::size get_line_number(ql::size index) const;
		QL_SOURCE ql::hitbox get_visible_hitbox(bool ignore_outline = true) const;
		QL_SOURCE ql::hitbox get_standard_hitbox() const;
		QL_SOURCE ql::vec2 get_offset() const;

		QL_SOURCE ql::size size() const;
		QL_SOURCE std::string string() const;
		QL_SOURCE void clear();
		QL_SOURCE ql::text& operator<<(const std::string& string);
		QL_SOURCE ql::text& operator<<(const std::wstring& string);
		QL_SOURCE ql::text& operator<<(const sf::String& string);

		QL_SOURCE ql::text& operator=(const ql::vtext& text);

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		QL_SOURCE ql::f32 get_letter_kerning(ql::wchar_type c) const;
		QL_SOURCE ql::f32 get_letter_advance(ql::wchar_type c) const;
		QL_SOURCE ql::f32 get_letter_advance_and_spacing(ql::wchar_type c) const;
		QL_SOURCE ql::f32 get_letter_width(ql::wchar_type c) const;

		std::string m_font;
		sf::Text m_text;
	};
}

#endif