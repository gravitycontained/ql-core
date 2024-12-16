#include <ql/graphic/drawable/basic/text/text.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/resources/resources.hpp>
#include <ql/graphic/drawable/virtual-draw-object/vdo.hpp>
#include <ql/core/system/exception/exception.hpp>

#include <cwctype>

namespace ql
{

	void ql::vtext::set_font(const std::string& font_name)
	{
		this->font_name = font_name;
	}

	void ql::vtext::set_style(ql::u32 style)
	{
		this->style = style;
	}

	void ql::vtext::set_character_size(ql::u32 character_size)
	{
		this->character_size = character_size;
	}

	void ql::vtext::set_color(ql::rgba color)
	{
		this->color = color;
	}

	void ql::vtext::set_outline_thickness(ql::f32 outline_thickness)
	{
		this->outline_thickness = outline_thickness;
	}

	void ql::vtext::set_outline_color(ql::rgba color)
	{
		this->color = color;
	}

	void ql::vtext::set_letter_spacing(ql::f32 spacing)
	{
		this->letter_spacing = spacing;
	}

	void ql::vtext::set_position(ql::vec2 position)
	{
		this->position = position;
	}

	void ql::vtext::set_string(const std::string& string)
	{
		this->string = string;
	}

	bool ql::vtext::operator==(const vtext& other) const
	{
		return this->character_size == other.character_size && this->font_name == other.font_name && this->style == other.style &&
					 this->character_size == other.character_size && this->color == other.color &&
					 this->outline_thickness == other.outline_thickness && this->outline_color == other.outline_color &&
					 this->letter_spacing == other.letter_spacing && this->position == other.position && this->string == other.string;
	}

	void ql::vtext::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::text = *this;
		ql::detail::text.draw(window, states);
	}

	const sf::Font& ql::text::get_sf_font() const
	{
		return *this->m_text.getFont();
	}

	const sf::Glyph& ql::text::get_glyph(ql::wchar_type c) const
	{
		if (this->m_font.empty())
		{
			throw ql::exception("ql::text::get_glyph : font not set");
		}
		return this->get_sf_font().getGlyph(c, this->get_character_size(), this->is_bold(), this->get_outline_thickness());
	}

	ql::hitbox ql::text::get_glyph_hitbox(ql::wchar_type c) const
	{
		auto rect = this->get_glyph(c).textureRect;
		return ql::hitbox({rect.left, rect.top}, {rect.width, rect.height});
	}

	ql::f32 ql::text::get_character_advance(ql::wchar_type current) const
	{
		return this->get_glyph(current).advance + this->get_letter_spacing_pixels();
	}

	ql::f32 ql::text::get_next_character_advance() const
	{
		auto x = this->get_standard_hitbox().dimension.x;
		auto w = this->get_wstring();
		if (w.length())
		{
			auto cw = w[w.length() - 1];
			auto special = (cw == L'\t' || cw == L'\n');
			if (!special)
			{
				auto width = this->get_letter_width(cw);
				auto advance = this->get_letter_advance(cw);
				auto spaced_advance = this->get_letter_advance_and_spacing(cw);

				ql::f32 diff = 0;
				if (!std::iswspace(cw))
				{
					diff = spaced_advance - width;
				}

				if (w.length() > 1)
				{
					auto before_left = this->get_glyph(w[w.length() - 2]).bounds.left;
					if (std::iswspace(cw))
					{
						before_left -= this->get_glyph(cw).bounds.left;
					}
					diff += before_left;
				}

				x += diff;
			}
		}
		return x;
	}

	ql::f32 ql::text::get_line_spacing_pixels() const
	{
		return this->get_sf_font().getLineSpacing(this->get_character_size()) * this->m_text.getLineSpacing();
	}

	ql::f32 ql::text::get_line_spacing() const
	{
		return this->get_line_height();
		// return this->m_text.getLineSpacing();
	}

	ql::f32 ql::text::get_letter_spacing_pixels() const
	{
		float white_width =
				this->get_sf_font().getGlyph(L' ', this->get_character_size(), this->is_bold(), this->get_outline_thickness()).advance;
		float letter_spacing = (white_width / 3.f) * (this->get_letter_spacing() - 1.f);
		return letter_spacing;
	}

	ql::f32 ql::text::get_whitespace_width() const
	{
		float white_width =
				this->get_sf_font().getGlyph(L' ', this->get_character_size(), this->is_bold(), this->get_outline_thickness()).advance;
		float letter_spacing = (white_width / 3.f) * (this->get_letter_spacing() - 1.f);
		return white_width + letter_spacing;
	}

	ql::f32 ql::text::get_italic_shear() const
	{
		return (this->get_style() == sf::Text::Style::Italic) ? (12.0f * (ql::pi_32 / 180.0f)) : 0.f;
	}

	bool ql::text::is_bold() const
	{
		return this->get_style() == sf::Text::Style::Bold;
	}

	std::string ql::text::get_font() const
	{
		return this->m_font;
	}

	ql::u32 ql::text::get_style() const
	{
		return this->m_text.getStyle();
	}

	ql::u32 ql::text::get_character_size() const
	{
		return this->m_text.getCharacterSize();
	}

	ql::rgba ql::text::get_color() const
	{
		return this->m_text.getFillColor();
	}

	ql::f32 ql::text::get_outline_thickness() const
	{
		return this->m_text.getOutlineThickness();
	}

	ql::rgba ql::text::get_outline_color() const
	{
		return this->m_text.getOutlineColor();
	}

	ql::f32 ql::text::get_letter_spacing() const
	{
		return this->m_text.getLetterSpacing();
	}

	ql::vec2 ql::text::get_position() const
	{
		return this->m_text.getPosition();
	}

	ql::vec2 ql::text::get_center() const
	{
		return this->get_standard_hitbox().get_center();
	}

	std::string ql::text::get_string() const
	{
		return this->m_text.getString().toAnsiString();
	}

	std::wstring ql::text::get_wstring() const
	{
		return this->m_text.getString().toWideString();
	}

	sf::String ql::text::get_sfstring() const
	{
		return this->m_text.getString();
	}

	void ql::text::set_font(const sf::Font& font)
	{
		this->m_font = font.getInfo().family;
		this->m_text.setFont(font);
	}

	void ql::text::set_font(const std::string& font_name)
	{
		this->m_font = font_name;
		if (this->m_font.empty())
			return;
		if (ql::find_font(font_name))
		{
			this->m_text.setFont(ql::get_font(font_name));
		}
		else
		{
			throw ql::exception("couldn't find font \"", font_name, "\"");
		}
	}

	void ql::text::set_style(ql::u32 style)
	{
		this->m_text.setStyle(style);
	}

	void ql::text::set_character_size(ql::u32 character_size)
	{
		this->m_text.setCharacterSize(character_size);
	}

	void ql::text::set_color(ql::rgba color)
	{
		this->m_text.setFillColor(color);
	}

	void ql::text::set_outline_thickness(ql::f32 outline_thickness)
	{
		this->m_text.setOutlineThickness(outline_thickness);
	}

	void ql::text::set_outline_color(ql::rgba color)
	{
		this->m_text.setOutlineColor(color);
	}

	void ql::text::set_rotation(ql::f32 angle)
	{
		this->m_text.setRotation(angle);
	}

	void ql::text::set_letter_spacing(ql::f32 spacing)
	{
		this->m_text.setLetterSpacing(spacing);
	}

	void ql::text::set_line_spacing(ql::f32 spacing)
	{
		this->m_text.setLineSpacing(spacing);
	}

	void ql::text::set_position(ql::vec2 position)
	{
		this->m_text.setPosition(position);
	}

	void ql::text::set_center(ql::vec2 position)
	{
		this->centerize();
		this->set_position(position);
	}

	void ql::text::set_string(const std::string& string)
	{
		this->m_text.setString(string);
	}

	void ql::text::set_string(const std::wstring& string)
	{
		this->m_text.setString(string);
	}

	void ql::text::set_string(const sf::String& string)
	{
		this->m_text.setString(string);
	}

	void ql::text::centerize()
	{
		auto pos = this->m_text.getPosition();
		sf::FloatRect textRect = this->m_text.getLocalBounds();
		this->m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		this->m_text.setPosition(pos);
	}

	void ql::text::centerize_x()
	{
		auto pos = this->m_text.getPosition();
		sf::FloatRect textRect = this->m_text.getLocalBounds();
		this->m_text.setOrigin(textRect.left + textRect.width / 2.0f, 0.0f);
		this->m_text.setPosition(pos);
	}

	void ql::text::centerize_y()
	{
		auto pos = this->m_text.getPosition();
		sf::FloatRect textRect = this->m_text.getLocalBounds();
		this->m_text.setOrigin(0.0f, textRect.top + textRect.height / 2.0f);
		this->m_text.setPosition(pos);
	}

	void ql::text::move(ql::vec2 delta)
	{
		this->m_text.move(delta);
	}

	ql::vec2 ql::text::find_character_position(ql::size index) const
	{
		return this->m_text.findCharacterPos(index);
	}

	ql::f32 ql::text::get_underline_baseline() const
	{
		return this->m_text.getFont()->getUnderlinePosition(this->get_character_size());
	}

	ql::f32 ql::text::get_underline_thickness() const
	{
		return this->m_text.getFont()->getUnderlineThickness(this->get_character_size());
	}

	ql::f32 ql::text::get_character_size_plus_baseline() const
	{
		return this->get_character_size() + this->get_underline_baseline();
	}

	std::vector<std::pair<ql::size, ql::hitbox>> ql::text::get_all_characters_hitbox() const
	{
		std::vector<std::pair<ql::size, ql::hitbox>> result;
		auto x = this->find_character_position(0).x;
		auto y = ql::f32_cast(this->get_character_size());
		auto string = this->get_wstring();

		wchar_t prev_char = L'\0';
		for (ql::size i = 0u; i < string.size(); ++i)
		{
			ql::vec2 pos = this->find_character_position(i);
			sf::Glyph glyph;

			auto c = string[i];
			if (c == L'\t' || c == L'\n')
			{
				glyph = this->get_glyph(L' ');
			}
			else
			{
				glyph = this->get_glyph(string[i]);
			}

			x += this->get_sf_font().getKerning(prev_char, c, this->get_character_size());
			prev_char = c;

			ql::f32 extra_width = 0.0f;
			ql::f32 extra_height = 0.0f;
			ql::vec2 shift = ql::vec(0, 0);
			bool special = false;
			switch (c)
			{
				case L'\n':
					x = this->find_character_position(0).x;
					continue;
				case L'\t':
					extra_width = this->get_whitespace_width() * 4;
					x += extra_width;
					extra_height = this->get_character_size() / 2.0f;
					shift = -ql::vec(extra_width, extra_height);
					special = true;
					continue;
				case L' ':
					extra_width = this->get_whitespace_width();
					x += extra_width;
					extra_height = this->get_character_size() / 2.0f;
					shift = -ql::vec(extra_width, extra_height);
					special = true;
					continue;
			}

			auto left = glyph.bounds.left;
			auto top = glyph.bounds.top;
			auto right = glyph.bounds.left + glyph.bounds.width;
			auto bottom = glyph.bounds.top + glyph.bounds.height;

			left = x + left - this->get_italic_shear() * bottom;
			right = x + right - this->get_italic_shear() * top;
			top = this->get_position().y + y + top;
			bottom = this->get_position().y + y + bottom;

			ql::hitbox hitbox;
			hitbox.position = ql::vec(left, top + pos.y) + shift;
			hitbox.dimension = ql::vec(right - left, bottom - top) + ql::vec(extra_width, extra_height);

			result.push_back(std::make_pair(i, hitbox));

			auto base_line = this->get_underline_baseline();
			auto base_thickness = this->get_underline_thickness();

			pos.y += this->get_character_size() + base_line + base_thickness;
			pos.x = x;
			if (!special)
			{
				x += this->get_character_advance(c);
			}
		}
		return result;
	}

	std::vector<ql::hitbox> ql::text::get_all_characters_hitbox_whitespace_included() const
	{
		std::vector<ql::hitbox> result;
		auto x = this->find_character_position(0).x;
		auto y = ql::f32_cast(this->get_character_size());
		auto string = this->get_wstring();

		wchar_t prev_char = L'\0';
		for (ql::size i = 0u; i < string.size(); ++i)
		{
			ql::vec2 pos = this->find_character_position(i);
			sf::Glyph glyph;

			auto c = string[i];
			if (c == L'\t' || c == L'\n')
			{
				glyph = this->get_glyph(L' ');
			}
			else
			{
				glyph = this->get_glyph(string[i]);
			}

			x += this->get_sf_font().getKerning(prev_char, c, this->get_character_size());
			prev_char = c;

			ql::f32 extra_width = 0.0f;
			ql::f32 extra_height = 0.0f;
			ql::vec2 shift = ql::vec(0, 0);
			bool special = false;
			switch (c)
			{
				case L'\n':
					x = this->find_character_position(0).x;
					continue;
				case L'\t':
					extra_width = this->get_whitespace_width() * 4;
					x += extra_width;
					extra_height = this->get_character_size() / 2.0f;
					shift = -ql::vec(extra_width, extra_height);
					special = true;
					break;
				case L' ':
					extra_width = this->get_whitespace_width();
					x += extra_width;
					extra_height = this->get_character_size() / 2.0f;
					shift = -ql::vec(extra_width, extra_height);
					special = true;
					break;
			}

			auto left = glyph.bounds.left;
			auto top = glyph.bounds.top;
			auto right = glyph.bounds.left + glyph.bounds.width;
			auto bottom = glyph.bounds.top + glyph.bounds.height;

			left = x + left - this->get_italic_shear() * bottom;
			right = x + right - this->get_italic_shear() * top;
			top = this->get_position().y + y + top;
			bottom = this->get_position().y + y + bottom;

			ql::hitbox hitbox;
			hitbox.position = ql::vec(left, top + pos.y) + shift;
			hitbox.dimension = ql::vec(right - left, bottom - top) + ql::vec(extra_width, extra_height);

			result.push_back(hitbox);

			auto base_line = this->get_underline_baseline();
			auto base_thickness = this->get_underline_thickness();

			pos.y += this->get_character_size() + base_line + base_thickness;
			pos.x = x;
			if (!special)
			{
				x += this->get_character_advance(c);
			}
		}
		return result;
	}

	ql::vec2 ql::text::get_starting_line_position() const
	{
		auto glyph = this->get_glyph(L'A');

		auto x = this->find_character_position(0).x;
		auto y = this->get_character_size();

		auto left = glyph.bounds.left;
		auto top = glyph.bounds.top;
		auto right = glyph.bounds.left + glyph.bounds.width;
		auto bottom = glyph.bounds.top + glyph.bounds.height;

		left = x + left - this->get_italic_shear() * bottom;
		right = x + right - this->get_italic_shear() * top;
		top = this->get_position().y + y + top;
		return ql::vec(left, top);
	}

	ql::f32 ql::text::get_line_height() const
	{
		auto glyph = this->get_glyph(L'A');

		auto y = this->get_character_size();
		auto top = glyph.bounds.top;
		auto a_top = this->get_position().y + y + top;

		glyph = this->get_glyph(L'g');

		y = this->get_character_size();
		auto bottom = glyph.bounds.top + glyph.bounds.height;
		auto g_bottom = this->get_position().y + y + bottom;

		return (g_bottom - a_top);
	}

	ql::f32 ql::text::get_delta_underline() const
	{
		auto glyph = this->get_glyph(L'x');

		auto y = this->get_character_size();
		auto bottom = glyph.bounds.top + glyph.bounds.height;
		auto x_bottom = this->get_position().y + y + bottom;

		glyph = this->get_glyph(L'g');

		y = this->get_character_size();
		bottom = glyph.bounds.top + glyph.bounds.height;
		auto g_bottom = this->get_position().y + y + bottom;

		return g_bottom - x_bottom;
	}

	ql::vec2 ql::text::get_character_dimension(wchar_t character) const
	{
		auto glyph = this->get_glyph(character);

		auto left = glyph.bounds.left;
		auto top = glyph.bounds.top;
		auto right = glyph.bounds.left + glyph.bounds.width;
		auto bottom = glyph.bounds.top + glyph.bounds.height;

		left = left - this->get_italic_shear() * bottom;
		right = right - this->get_italic_shear() * top;
		top = this->get_position().y + top;
		bottom = this->get_position().y + bottom;

		return ql::vec(right - left, bottom - top);
	}

	ql::size ql::text::get_line_number(ql::size index) const
	{
		ql::size line = 0u;
		auto str = this->get_wstring();
		for (ql::size i = 0u; i <= index && i < str.size(); ++i)
		{
			if (str[i] == L'\n')
			{
				++line;
			}
		}
		return line;
	}

	ql::hitbox ql::text::get_visible_hitbox(bool ignore_outline) const
	{
		ql::hitbox rectangle;
		auto local_bounds = this->m_text.getLocalBounds();
		auto global_bounds = this->m_text.getGlobalBounds();

		rectangle.set_position({global_bounds.left, global_bounds.top});
		rectangle.set_dimension({local_bounds.width, local_bounds.height});

		if (ignore_outline)
		{
			rectangle.position -= this->m_text.getOutlineThickness();
			rectangle.dimension -= this->m_text.getOutlineThickness() * 2;
		}
		return rectangle;
	}

	ql::hitbox ql::text::get_standard_hitbox() const
	{
		ql::hitbox rectangle;
		auto local_bounds = this->m_text.getLocalBounds();

		rectangle.set_position(this->m_text.getPosition());
		rectangle.set_dimension({local_bounds.width, local_bounds.height});

		return rectangle;
	}

	ql::vec2 ql::text::get_offset() const
	{
		auto global_bounds = this->m_text.getGlobalBounds();
		return ql::vec(global_bounds.left, global_bounds.top) - this->get_position();
	}

	ql::size ql::text::size() const
	{
		return this->m_text.getString().getSize();
	}

	std::string ql::text::string() const
	{
		return this->m_text.getString().toAnsiString();
	}

	void ql::text::clear()
	{
		sf::String s = L"";
		this->m_text.setString(s);
	}

	ql::text& ql::text::operator<<(const std::string& string)
	{
		sf::String s = this->get_sfstring();
		s += string;
		this->m_text.setString(s);
		return *this;
	}

	ql::text& ql::text::operator<<(const std::wstring& string)
	{
		sf::String s = this->get_sfstring();
		s += string;
		this->m_text.setString(s);
		return *this;
	}

	ql::text& ql::text::operator<<(const sf::String& string)
	{
		sf::String s = this->get_sfstring();
		s += string;
		this->m_text.setString(s);
		return *this;
	}

	ql::text& ql::text::operator=(const ql::vtext& text)
	{
		this->set_character_size(text.character_size);
		this->set_color(text.color);
		this->set_letter_spacing(text.letter_spacing);
		this->set_outline_color(text.outline_color);
		this->set_outline_thickness(text.outline_thickness);
		this->set_position(text.position);
		this->set_style(text.style);
		this->set_string(text.string);
		this->m_font = text.font_name;
		this->set_font(text.font_name);
		return *this;
	}

	void ql::text::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->m_text, states);
	}

	ql::f32 ql::text::get_letter_kerning(ql::wchar_type c) const
	{
		auto w = this->get_wstring();
		if (!w.length())
		{
			return 0.0f;
		}
		else
		{
			auto w = this->get_wstring();
			auto wc = w[w.length() - 1];
			return this->get_sf_font().getKerning(c, wc, this->get_character_size());
		}
	}

	ql::f32 ql::text::get_letter_advance(ql::wchar_type c) const
	{
		return this->get_sf_font().getGlyph(c, this->get_character_size(), this->is_bold(), this->get_outline_thickness()).advance;
	}

	ql::f32 ql::text::get_letter_advance_and_spacing(ql::wchar_type c) const
	{
		return this->get_letter_advance(c) + this->get_letter_spacing_pixels();
	}

	ql::f32 ql::text::get_letter_width(ql::wchar_type c) const
	{
		const auto& glyph =
				this->get_sf_font().getGlyph(c, this->get_character_size(), this->is_bold(), this->get_outline_thickness());
		return glyph.bounds.width;
	}

	void ql::text::set_scale(ql::vec2 scale)
	{
		this->m_text.setScale(scale);
	}
}	 // namespace ql

#endif