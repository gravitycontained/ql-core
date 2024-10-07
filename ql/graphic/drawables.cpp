#include <ql/graphic/drawables.hpp>

#if defined QL_SFML

#include <ql/graphic/resources.hpp>

namespace ql
{

	ql::hitbox ql::get_text_hitbox(const sf::Text& text, bool ignore_outline)
	{
		ql::hitbox rectangle;
		auto local_bounds = text.getLocalBounds();
		auto global_bounds = text.getGlobalBounds();

		rectangle.set_position({global_bounds.left, global_bounds.top});
		rectangle.set_dimension({local_bounds.width, local_bounds.height});

		if (ignore_outline)
		{
			rectangle.position -= text.getOutlineThickness();
			rectangle.dimension -= text.getOutlineThickness() * 2;
		}
		return rectangle;
	}

	ql::hitbox ql::get_text_hitbox(const ql::text& text, bool ignore_outline)
	{
		return text.get_visible_hitbox();
	}

	void ql::centerize_text(sf::Text& text)
	{
		auto rect = ql::get_text_hitbox(text).dimension;
		text.move(-rect / 2);
	}

	void ql::centerize_text(ql::text& text)
	{
		text.centerize();
	}

	ql::hitbox ql::get_sprite_hitbox(const sf::Sprite& sprite)
	{
		ql::hitbox rectangle;
		auto local_bounds = sprite.getLocalBounds();
		auto global_bounds = sprite.getGlobalBounds();

		rectangle.set_position({global_bounds.left, global_bounds.top});
		rectangle.set_dimension(ql::vec(local_bounds.width, local_bounds.height) * ql::vec2(sprite.getScale()));

		return rectangle;
	}

	ql::vec2 ql::get_sprite_center(const sf::Sprite& sprite)
	{
		auto hitbox = ql::get_sprite_hitbox(sprite);
		return hitbox.position + hitbox.dimension / 2;
	}

	void ql::centerize_sprite_origin(sf::Sprite& sprite)
	{
		auto local_bounds = sprite.getLocalBounds();
		auto dim = ql::vec(local_bounds.width, local_bounds.height);
		sprite.setOrigin(dim / 2);
	}

	void ql::centerize_sprite(sf::Sprite& sprite)
	{
		auto hitbox = ql::get_sprite_hitbox(sprite);
		sprite.setPosition(hitbox.position - hitbox.dimension / 2);
	}

	namespace detail
	{
		ql::text ql::detail::text;
		ql::rectangle ql::detail::rectangle;
		ql::rectangles ql::detail::rectangles;
		ql::smooth_rectangle ql::detail::smooth_rectangle;
		ql::smooth_corner ql::detail::smooth_corner;
		ql::point ql::detail::point;
		ql::points ql::detail::points;
		ql::circle ql::detail::circle;
		ql::circles ql::detail::circles;
		ql::line ql::detail::line;
		ql::lines ql::detail::lines;
		ql::thick_line ql::detail::thick_line;
		ql::thick_lines ql::detail::thick_lines;
		ql::graph ql::detail::graph;
	}	 // namespace detail

	void ql::vertex::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(reinterpret_cast<const sf::Vertex*>(this), 1, sf::PrimitiveType::Points, states);
	}

	void ql::vertex_array::set_primitive_type(ql::primitive_type primitive_type)
	{
		this->primitive_type = primitive_type;
	}

	void ql::vertex_array::set_primitive_type(sf::PrimitiveType primitive_type)
	{
		this->primitive_type = static_cast<ql::primitive_type>(primitive_type);
	}

	void ql::vertex_array::set_color(ql::rgba color)
	{
		for (auto& i : this->vertices)
		{
			i.color = color;
		}
	}

	void ql::vertex_array::move(ql::vec2 delta)
	{
		for (auto& i : this->vertices)
		{
			i.position += delta;
		}
	}

	ql::size ql::vertex_array::size() const
	{
		return this->vertices.size();
	}

	bool ql::vertex_array::empty() const
	{
		return this->vertices.empty();
	}

	void ql::vertex_array::resize(ql::size new_size)
	{
		this->vertices.resize(new_size);
	}

	void ql::vertex_array::reserve(ql::size new_size)
	{
		this->vertices.reserve(new_size);
	}

	void ql::vertex_array::add(const ql::vertex& vertex)
	{
		this->vertices.push_back(vertex);
	}

	void ql::vertex_array::clear()
	{
		this->vertices.clear();
	}

	ql::vertex& ql::vertex_array::operator[](ql::size index)
	{
		return this->vertices[index];
	}

	const ql::vertex& ql::vertex_array::operator[](ql::size index) const
	{
		return this->vertices[index];
	}

	ql::vertex& ql::vertex_array::front()
	{
		return this->vertices.front();
	}

	const ql::vertex& ql::vertex_array::front() const
	{
		return this->vertices.front();
	}

	ql::vertex& ql::vertex_array::back()
	{
		return this->vertices.back();
	}

	const ql::vertex& ql::vertex_array::back() const
	{
		return this->vertices.back();
	}

	std::vector<ql::vertex>::iterator ql::vertex_array::begin()
	{
		return this->vertices.begin();
	}

	std::vector<ql::vertex>::const_iterator ql::vertex_array::begin() const
	{
		return this->vertices.begin();
	}

	std::vector<ql::vertex>::const_iterator ql::vertex_array::cbegin() const
	{
		return this->vertices.cbegin();
	}

	std::vector<ql::vertex>::iterator ql::vertex_array::end()
	{
		return this->vertices.end();
	}

	std::vector<ql::vertex>::const_iterator ql::vertex_array::end() const
	{
		return this->vertices.end();
	}

	std::vector<ql::vertex>::const_iterator ql::vertex_array::cend() const
	{
		return this->vertices.cend();
	}

	void ql::vertex_array::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(
				reinterpret_cast<const sf::Vertex*>(this->vertices.data()), this->size(),
				static_cast<sf::PrimitiveType>(this->primitive_type), states
		);
	}

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

	void ql::vrectangle::set_dimension(ql::vec2 dimension)
	{
		this->dimension = dimension;
	}

	void ql::vrectangle::set_position(ql::vec2 position)
	{
		this->position = position;
	}

	void ql::vrectangle::set_center(ql::vec2 position)
	{
		this->position = position - this->dimension / 2;
	}

	void ql::vrectangle::set_hitbox(const ql::hitbox& hitbox)
	{
		this->set_position(hitbox.position);
		this->set_dimension(hitbox.dimension);
	}

	void ql::vrectangle::set_color(ql::rgba color)
	{
		this->color = color;
	}

	void ql::vrectangle::set_outline_thickness(ql::f32 outline_thickness)
	{
		this->outline_thickness = outline_thickness;
	}

	void ql::vrectangle::set_outline_color(ql::rgba outline_color)
	{
		this->outline_color = outline_color;
	}

	ql::vec2 ql::vrectangle::get_dimension() const
	{
		return this->dimension;
	}

	ql::vec2 ql::vrectangle::get_position() const
	{
		return this->position;
	}

	ql::vec2 ql::vrectangle::get_center() const
	{
		return this->position + (this->dimension / 2);
	}

	ql::hitbox ql::vrectangle::get_hitbox() const
	{
		return ql::hitbox(this->position, this->dimension);
	}

	ql::rgba ql::vrectangle::get_color() const
	{
		return this->color;
	}

	ql::f32 ql::vrectangle::get_outline_thickness() const
	{
		return this->outline_thickness;
	}

	ql::rgba ql::vrectangle::get_outline_color() const
	{
		return this->color;
	}

	void ql::vrectangle::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::rectangle = *this;
		ql::detail::rectangle.draw(window, states);
	}

	std::string ql::vrectangle::string() const
	{
		return ql::to_string('[', this->position, ", ", this->dimension, ']');
	}

	void ql::vrectangle::increase(ql::f32 delta)
	{
		this->position -= ql::vec2(delta, delta);
		this->dimension += ql::vec2(delta, delta) * 2;
	}

	ql::vrectangle ql::vrectangle::increased(ql::f32 delta) const
	{
		auto copy = *this;
		copy.increase(delta);
		return copy;
	}

	bool ql::vrectangle::contains(ql::vec2 position) const
	{
		return (
				position.x > this->position.x && position.x < (this->position.x + this->dimension.x) && position.y > this->position.y &&
				position.y < (this->position.y + this->dimension.y)
		);
	}

	bool ql::vrectangle::contains(ql::vec2 position, ql::f32 hitbox_increase) const
	{
		return (
				position.x > (this->position.x - hitbox_increase) &&
				position.x < (this->position.x + this->dimension.x + hitbox_increase) &&
				position.y > (this->position.y - hitbox_increase) && position.y < (this->position.y + this->dimension.y + hitbox_increase)
		);
	}

	bool ql::vrectangle::collides(ql::straight_line line) const
	{
		return this->get_hitbox().collides(line);
	}

	bool ql::vrectangle::collides(ql::straight_line line, ql::f32 hitbox_increase) const
	{
		return this->get_hitbox().collides(line, hitbox_increase);
	}

	void ql::rectangle::set_dimension(ql::vec2 dimension)
	{
		this->m_rect.setSize(dimension);
	}

	void ql::rectangle::set_position(ql::vec2 position)
	{
		this->m_rect.setPosition(position);
	}

	void ql::rectangle::set_center(ql::vec2 position)
	{
		this->m_rect.setPosition(position - this->get_dimension() / 2);
	}

	void ql::rectangle::set_hitbox(const ql::hitbox& hitbox)
	{
		this->set_position(hitbox.position);
		this->set_dimension(hitbox.dimension);
	}

	void ql::rectangle::set_outline_thickness(ql::f32 outline_thickness)
	{
		this->m_rect.setOutlineThickness(outline_thickness);
	}

	void ql::rectangle::set_color(ql::rgba color)
	{
		this->m_rect.setFillColor(color);
	}

	void ql::rectangle::set_outline_color(ql::rgba color)
	{
		this->m_rect.setOutlineColor(color);
	}

	void ql::rectangle::increase(ql::f64 delta)
	{
		this->set_position(this->get_position() - ql::vec2(delta, delta));
		this->set_dimension(this->get_dimension() + ql::vec2(delta, delta) * 2);
	}

	bool ql::rectangle::contains(ql::vec2 position) const
	{
		auto pos = this->get_position();
		auto dim = this->get_dimension();
		return (position.x > pos.x && position.x < (pos.x + dim.x) && position.y > pos.y && position.y < (pos.y + dim.y));
	}

	bool ql::rectangle::contains(ql::vec2 position, ql::f32 hitbox_increase) const
	{
		auto pos = this->get_position() - hitbox_increase;
		auto dim = this->get_dimension() + hitbox_increase * 2;
		return (position.x > pos.x && position.x < (pos.x + dim.x) && position.y > pos.y && position.y < (pos.y + dim.y));
	}

	bool ql::rectangle::contains(ql::vec2 position, ql::vec2 hitbox_increase) const
	{
		auto pos = this->get_position() - hitbox_increase;
		auto dim = this->get_dimension() + hitbox_increase * 2;
		return (position.x > pos.x && position.x < (pos.x + dim.x) && position.y > pos.y && position.y < (pos.y + dim.y));
	}

	bool ql::rectangle::collides(ql::straight_line line) const
	{
		return this->get_hitbox().collides(line);
	}

	bool ql::rectangle::collides(ql::straight_line line, ql::f32 hitbox_increase) const
	{
		return this->get_hitbox().collides(line, hitbox_increase);
	}

	void ql::rectangle::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->m_rect, states);
	}

	void ql::va_rectangle::move(ql::vec2 delta)
	{
		this->hitbox.move(delta);
		this->apply_hitbox();
	}

	void ql::va_rectangle::set_color(ql::rgba color)
	{
		for (auto& i : this->va)
		{
			i.color = color;
		}
	}

	void ql::va_rectangle::set_position(ql::vec2 position)
	{
		this->hitbox.position = position;
		this->apply_hitbox();
	}

	void ql::va_rectangle::set_dimension(ql::vec2 dimension)
	{
		this->hitbox.dimension = dimension;
		this->apply_hitbox();
	}

	void ql::va_rectangle::set_hitbox(const ql::hitbox& hitbox)
	{
		this->hitbox = hitbox;
		this->apply_hitbox();
	}

	ql::vertex& ql::va_rectangle::top_left()
	{
		return this->va[0];
	}

	ql::vertex& ql::va_rectangle::top_right()
	{
		return this->va[1];
	}

	ql::vertex& ql::va_rectangle::bottom_left()
	{
		return this->va[3];
	}

	ql::vertex& ql::va_rectangle::bottom_right()
	{
		return this->va[2];
	}

	const ql::vertex& ql::va_rectangle::top_left() const
	{
		return this->va[0];
	}

	const ql::vertex& ql::va_rectangle::top_right() const
	{
		return this->va[1];
	}

	const ql::vertex& ql::va_rectangle::bottom_left() const
	{
		return this->va[3];
	}

	const ql::vertex& ql::va_rectangle::bottom_right() const
	{
		return this->va[2];
	}

	ql::vec2 ql::va_rectangle::get_position() const
	{
		return this->hitbox.position;
	}

	ql::vec2 ql::va_rectangle::get_dimension() const
	{
		return this->hitbox.dimension;
	}

	ql::hitbox ql::va_rectangle::get_hitbox() const
	{
		return this->hitbox;
	}

	void ql::va_rectangle::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->va.draw(window, states);
	}

	void ql::va_rectangle::apply_hitbox()
	{
		this->va[0].position = this->hitbox.position;
		this->va[1].position = this->hitbox.position + ql::vec(this->hitbox.dimension.x, 0);
		this->va[2].position = this->hitbox.position + this->hitbox.dimension;
		this->va[3].position = this->hitbox.position + ql::vec(0, this->hitbox.dimension.y);
	}

	ql::rgba ql::rectangle::get_color() const
	{
		return this->m_rect.getFillColor();
	}

	ql::rgba ql::rectangle::get_outline_color() const
	{
		return this->m_rect.getOutlineColor();
	}

	ql::vec2 ql::rectangle::get_position() const
	{
		return this->m_rect.getPosition();
	}

	ql::vec2 ql::rectangle::get_dimension() const
	{
		return this->m_rect.getSize();
	}

	ql::vec2 ql::rectangle::get_center() const
	{
		return this->get_position() + this->get_dimension() / 2;
	}

	ql::f32 ql::rectangle::get_outline_thickness() const
	{
		return this->m_rect.getOutlineThickness();
	}

	ql::hitbox ql::rectangle::get_hitbox() const
	{
		ql::hitbox result;
		result.position = this->get_position();
		result.dimension = this->get_dimension();
		return result;
	}

	ql::vlines ql::rectangle::as_lines() const
	{
		ql::vlines lines;

		lines.add_point(this->get_position());
		lines.add_point(this->get_position() + this->get_dimension().just_x());
		lines.add_point(this->get_position() + this->get_dimension());
		lines.add_point(this->get_position() + this->get_dimension().just_y());
		return lines;
	}

	ql::vlines ql::rectangle::as_lines_completed() const
	{
		ql::vlines lines;

		lines.add_point(this->get_position());
		lines.add_point(this->get_position() + this->get_dimension().just_x());
		lines.add_point(this->get_position() + this->get_dimension());
		lines.add_point(this->get_position() + this->get_dimension().just_y());
		lines.complete();
		return lines;
	}

	ql::vec2 ql::rectangle::center() const
	{
		return this->get_position() + (this->get_dimension() / 2);
	}

	void ql::rectangle::move(ql::vec2 delta)
	{
		this->m_rect.move(delta);
	}

	ql::rectangle& ql::rectangle::operator=(const ql::vrectangle& rectangle)
	{
		this->set_color(rectangle.color);
		this->set_position(rectangle.position);
		this->set_dimension(rectangle.dimension);
		this->set_outline_color(rectangle.outline_color);
		this->set_outline_thickness(rectangle.outline_thickness);
		return *this;
	}

	ql::size ql::vrectangles::size() const
	{
		return this->rectangles.size();
	}

	void ql::vrectangles::resize(ql::size new_size)
	{
		this->rectangles.resize(new_size);
	}

	void ql::vrectangles::reserve(ql::size new_size)
	{
		this->rectangles.reserve(new_size);
	}

	void ql::vrectangles::clear()
	{
		this->rectangles.clear();
	}

	void ql::vrectangles::add(const ql::vrectangle& rect)
	{
		this->rectangles.push_back(rect);
	}

	ql::vrectangle& ql::vrectangles::operator[](ql::size index)
	{
		return this->rectangles[index];
	}

	const ql::vrectangle& ql::vrectangles::operator[](ql::size index) const
	{
		return this->rectangles[index];
	}

	ql::vrectangle& ql::vrectangles::front()
	{
		return this->rectangles.front();
	}

	const ql::vrectangle& ql::vrectangles::front() const
	{
		return this->rectangles.front();
	}

	ql::vrectangle& ql::vrectangles::back()
	{
		return this->rectangles.back();
	}

	const ql::vrectangle& ql::vrectangles::back() const
	{
		return this->rectangles.back();
	}

	std::vector<ql::vrectangle>::iterator ql::vrectangles::begin()
	{
		return this->rectangles.begin();
	}

	std::vector<ql::vrectangle>::const_iterator ql::vrectangles::begin() const
	{
		return this->rectangles.begin();
	}

	std::vector<ql::vrectangle>::const_iterator ql::vrectangles::cbegin() const
	{
		return this->rectangles.cbegin();
	}

	std::vector<ql::vrectangle>::iterator ql::vrectangles::end()
	{
		return this->rectangles.end();
	}

	std::vector<ql::vrectangle>::const_iterator ql::vrectangles::end() const
	{
		return this->rectangles.end();
	}

	std::vector<ql::vrectangle>::const_iterator ql::vrectangles::cend() const
	{
		return this->rectangles.cend();
	}

	void ql::vrectangles::add_rectangle(vrectangle rectangle)
	{
		this->rectangles.push_back(rectangle);
	}

	void ql::vrectangles::add_rectangle(ql::vec2 position, ql::vec2 dimension)
	{
		this->rectangles.push_back(ql::vrectangle(position, dimension));
	}

	void ql::vrectangles::add_rectangle(ql::vec2 position, ql::vec2 dimension, ql::rgba color)
	{
		this->rectangles.push_back(ql::vrectangle(position, dimension, color));
	}

	ql::vrectangles& ql::vrectangles::operator=(const ql::vrectangles& rectangles)
	{
		this->rectangles = rectangles.rectangles;
		return *this;
	}

	void ql::vrectangles::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::rectangles = *this;
		ql::detail::rectangles.draw(window, states);
	}

	ql::size ql::rectangles::size() const
	{
		return this->rectangles_.size();
	}

	void ql::rectangles::resize(ql::size new_size)
	{
		this->rectangles_.resize(new_size);
	}

	void ql::rectangles::reserve(ql::size new_size)
	{
		this->rectangles_.reserve(new_size);
	}

	void ql::rectangles::clear()
	{
		this->rectangles_.clear();
	}

	void ql::rectangles::add(const ql::rectangle& rect)
	{
		this->rectangles_.push_back(rect);
	}

	ql::rectangle& ql::rectangles::operator[](ql::size index)
	{
		return this->rectangles_[index];
	}

	const ql::rectangle& ql::rectangles::operator[](ql::size index) const
	{
		return this->rectangles_[index];
	}

	ql::rectangle& ql::rectangles::front()
	{
		return this->rectangles_.front();
	}

	const ql::rectangle& ql::rectangles::front() const
	{
		return this->rectangles_.front();
	}

	ql::rectangle& ql::rectangles::back()
	{
		return this->rectangles_.back();
	}

	const ql::rectangle& ql::rectangles::back() const
	{
		return this->rectangles_.back();
	}

	std::vector<ql::rectangle>::iterator ql::rectangles::begin()
	{
		return this->rectangles_.begin();
	}

	std::vector<ql::rectangle>::const_iterator ql::rectangles::begin() const
	{
		return this->rectangles_.begin();
	}

	std::vector<ql::rectangle>::const_iterator ql::rectangles::cbegin() const
	{
		return this->rectangles_.cbegin();
	}

	std::vector<ql::rectangle>::iterator ql::rectangles::end()
	{
		return this->rectangles_.end();
	}

	std::vector<ql::rectangle>::const_iterator ql::rectangles::end() const
	{
		return this->rectangles_.end();
	}

	std::vector<ql::rectangle>::const_iterator ql::rectangles::cend() const
	{
		return this->rectangles_.cend();
	}

	ql::rectangles& ql::rectangles::operator=(const ql::vrectangles& rectangles)
	{
		this->rectangles_.resize(rectangles.size());
		for (ql::u32 i = 0u; i < this->rectangles_.size(); ++i)
		{
			this->rectangles_[i] = rectangles[i];
		}
		return *this;
	}

	void ql::rectangles::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		for (auto& i : this->rectangles_)
		{
			i.draw(window, states);
		}
	}

	sf::Vector2f ql::polygon::polygon_proxy::operator=(ql::vec2 position)
	{
		this->ptr->setPoint(this->index, position);
		return this->ptr->getPoint(this->index);
	}

	ql::polygon::polygon_proxy::operator ql::vec2() const
	{
		return this->ptr->getPoint(this->index);
	}

	ql::polygon::const_polygon_proxy::operator ql::vec2() const
	{
		return this->ptr->getPoint(this->index);
	}

	ql::polygon::polygon_proxy ql::polygon::operator[](ql::size index)
	{
		ql::polygon::polygon_proxy result;
		result.ptr = &this->shape;
		result.index = index;
		return result;
	}

	ql::polygon::const_polygon_proxy ql::polygon::operator[](ql::size index) const
	{
		ql::polygon::const_polygon_proxy result;
		result.ptr = &this->shape;
		result.index = index;
		return result;
	}

	ql::polygon::polygon_proxy ql::polygon::front()
	{
		ql::polygon::polygon_proxy result;
		result.ptr = &this->shape;
		result.index = 0u;
		return result;
	}

	ql::polygon::const_polygon_proxy ql::polygon::front() const
	{
		ql::polygon::const_polygon_proxy result;
		result.ptr = &this->shape;
		result.index = 0u;
		return result;
	}

	ql::polygon::polygon_proxy ql::polygon::back()
	{
		ql::polygon::polygon_proxy result;
		result.ptr = &this->shape;
		result.index = this->size() - 1;
		return result;
	}

	ql::polygon::const_polygon_proxy ql::polygon::back() const
	{
		ql::polygon::const_polygon_proxy result;
		result.ptr = &this->shape;
		result.index = 0u;
		return result;
	}

	void ql::polygon::set_outline_thickness(ql::f32 thickness)
	{
		this->shape.setOutlineThickness(thickness);
	}

	void ql::polygon::set_outline_color(ql::rgba color)
	{
		this->shape.setOutlineColor(color);
	}

	void ql::polygon::set_color(ql::rgba color)
	{
		this->shape.setFillColor(color);
	}

	void ql::polygon::set_position(ql::vec2 position)
	{
		this->shape.setPosition(position);
	}

	ql::f32 ql::polygon::get_outline_thickness() const
	{
		return this->shape.getOutlineThickness();
	}

	ql::rgba ql::polygon::get_outline_color() const
	{
		return this->shape.getOutlineColor();
	}

	ql::rgba ql::polygon::get_color() const
	{
		return this->shape.getFillColor();
	}

	void ql::polygon::move(ql::vec2 delta)
	{
		this->shape.move(delta);
	}

	void ql::polygon::set_point(ql::size index, ql::vec2 position)
	{
		this->shape.setPoint(index, position);
	}

	ql::vec2 ql::polygon::get_point(ql::size index) const
	{
		return this->shape.getPoint(index);
	}

	ql::size ql::polygon::size() const
	{
		return this->shape.getPointCount();
	}

	void ql::polygon::resize(ql::size size)
	{
		this->shape.setPointCount(size);
	}

	bool ql::polygon::contains(ql::vec2 point, ql::size increment) const
	{
		bool flag = false;

		ql::straight_line compare;
		compare.a = {0, 0};
		compare.b = point;

		auto j = this->size() - 1;
		for (ql::size i = 0u; i < this->size(); i += increment)
		{
			ql::straight_line edge_line;
			edge_line.a = this->get_point(i);
			edge_line.b = this->get_point(j);
			if (compare.collides(edge_line))
			{
				flag = !flag;
			}
			j = i;
		}
		return flag;
	}

	void ql::polygon::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->shape, states);
	}

	void ql::vsmooth_rectangle::move(ql::vec2 delta)
	{
		this->position.move(delta);
	}

	void ql::vsmooth_rectangle::set_dimension(ql::vec2 dimension)
	{
		this->dimension = dimension;
	}

	void ql::vsmooth_rectangle::increase(ql::vec2 delta)
	{
		this->dimension += delta * 2;
		this->position -= delta;
	}

	void ql::vsmooth_rectangle::increase(ql::f32 delta)
	{
		this->increase(ql::vec(delta, delta));
	}

	vsmooth_rectangle ql::vsmooth_rectangle::increased(ql::vec2 delta) const
	{
		auto copy = *this;
		copy.increase(delta);
		return copy;
	}

	vsmooth_rectangle ql::vsmooth_rectangle::increased(ql::f32 delta) const
	{
		auto copy = *this;
		copy.increase(delta);
		return copy;
	}

	void ql::vsmooth_rectangle::set_position(ql::vec2 position)
	{
		this->position = position;
	}

	void ql::vsmooth_rectangle::set_hitbox(ql::hitbox hitbox)
	{
		this->position = hitbox.position;
		this->dimension = hitbox.dimension;
	}

	void ql::vsmooth_rectangle::set_center(ql::vec2 position)
	{
		this->position = position - this->dimension / 2;
	}

	void ql::vsmooth_rectangle::set_slope(ql::f64 slope)
	{
		this->slope = slope;
	}

	void ql::vsmooth_rectangle::set_color(ql::rgba color)
	{
		this->color = color;
	}

	void ql::vsmooth_rectangle::set_outline_color(ql::rgba color)
	{
		this->outline_color = color;
	}

	void ql::vsmooth_rectangle::set_outline_thickness(ql::f32 thickness)
	{
		this->outline_thickness = thickness;
	}

	void ql::vsmooth_rectangle::set_slope_dimension(ql::vec2 dimension)
	{
		this->slope_dim = dimension;
	}

	void ql::vsmooth_rectangle::set_slope_point_count(ql::size point_count)
	{
		this->slope_point_count = point_count;
	}

	void ql::vsmooth_rectangle::set_round_corners(ql::bitset<4u> round_corners)
	{
		this->round_corners = round_corners;
	}

	ql::vec2 ql::vsmooth_rectangle::get_dimension() const
	{
		return this->dimension;
	}

	ql::vec2 ql::vsmooth_rectangle::get_position() const
	{
		return this->position;
	}

	ql::hitbox ql::vsmooth_rectangle::get_hitbox() const
	{
		return ql::hitbox(this->get_position(), this->get_dimension());
	}

	ql::vec2 ql::vsmooth_rectangle::get_center() const
	{
		return this->position + this->dimension / 2;
	}

	ql::f64 ql::vsmooth_rectangle::get_slope() const
	{
		return this->slope;
	}

	ql::rgba ql::vsmooth_rectangle::get_color() const
	{
		return this->color;
	}

	ql::rgba ql::vsmooth_rectangle::get_outline_color() const
	{
		return this->outline_color;
	}

	ql::f32 ql::vsmooth_rectangle::get_outline_thickness() const
	{
		return this->outline_thickness;
	}

	ql::vec2 ql::vsmooth_rectangle::get_slope_dimension() const
	{
		return this->slope_dim;
	}

	ql::size ql::vsmooth_rectangle::get_slope_point_count() const
	{
		return this->slope_point_count;
	}

	ql::bitset<4u> ql::vsmooth_rectangle::get_round_corners() const
	{
		return this->round_corners;
	}

	bool ql::vsmooth_rectangle::contains(ql::vec2 point) const
	{
		ql::detail::smooth_rectangle = *this;
		return ql::detail::smooth_rectangle.contains(point);
	}

	void ql::vsmooth_rectangle::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::smooth_rectangle = *this;
		ql::detail::smooth_rectangle.draw(window, states);
	}

	void ql::smooth_rectangle::set_position(ql::vec2 position)
	{
		this->position = position;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_dimension(ql::vec2 dimension)
	{
		this->dimension = dimension;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_hitbox(ql::hitbox hitbox)
	{
		this->position = hitbox.position;
		this->dimension = hitbox.dimension;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_center(ql::vec2 position)
	{
		this->position = position - this->dimension / 2;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_slope(ql::f64 slope)
	{
		this->slope = slope;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_color(ql::rgba color)
	{
		this->polygon.set_color(color);
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_outline_color(ql::rgba color)
	{
		this->polygon.set_outline_color(color);
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_outline_thickness(ql::f32 thickness)
	{
		this->outline_thickness = thickness;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_slope_dimension(ql::vec2 dimension)
	{
		this->slope_dim = dimension;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_slope_dimension(ql::f32 dimension)
	{
		this->set_slope_dimension(ql::vec(dimension, dimension));
	}

	void ql::smooth_rectangle::set_slope_point_count(ql::size point_count)
	{
		this->slope_point_count = point_count;
		this->internal_check = true;
	}

	void ql::smooth_rectangle::set_round_corners(ql::bitset<4u> round_corners)
	{
		this->round_corners = round_corners;
	}

	ql::vec2 ql::smooth_rectangle::get_dimension() const
	{
		return this->dimension;
	}

	ql::vec2 ql::smooth_rectangle::get_position() const
	{
		return this->position;
	}

	ql::hitbox ql::smooth_rectangle::get_hitbox() const
	{
		return ql::hitbox(this->position, this->dimension);
	}

	ql::vec2 ql::smooth_rectangle::get_center() const
	{
		return this->position + this->dimension / 2;
	}

	ql::f64 ql::smooth_rectangle::get_slope() const
	{
		return this->slope;
	}

	ql::rgba ql::smooth_rectangle::get_color() const
	{
		return this->polygon.get_color();
	}

	ql::rgba ql::smooth_rectangle::get_outline_color() const
	{
		return this->polygon.get_outline_color();
	}

	ql::f32 ql::smooth_rectangle::get_outline_thickness() const
	{
		return this->outline_thickness;
	}

	ql::vec2 ql::smooth_rectangle::get_slope_dimension() const
	{
		return this->slope_dim;
	}

	ql::size ql::smooth_rectangle::get_slope_point_count() const
	{
		return this->slope_point_count;
	}

	ql::bitset<4u> ql::smooth_rectangle::get_round_corners() const
	{
		return this->round_corners;
	}

	void ql::smooth_rectangle::move(ql::vec2 delta)
	{
		this->check_create();
		this->position.move(delta);
		this->internal_check = true;
	}

	bool ql::smooth_rectangle::contains(ql::vec2 point) const
	{
		this->check_create();
		return this->polygon.contains(point);
	}

	void ql::smooth_rectangle::check_create() const
	{
		if (this->internal_check)
		{
			ql::vsmooth_rectangle rect;
			rect.set_dimension(this->dimension);
			rect.set_position(this->position);
			rect.set_slope(this->slope);
			rect.set_slope_point_count(this->slope_point_count);
			rect.set_color(this->get_color());
			rect.set_outline_color(this->get_outline_color());
			rect.set_slope_dimension(this->slope_dim);
			rect.set_outline_thickness(this->outline_thickness);
			rect.set_round_corners(this->get_round_corners());

			*this = rect;
		}
	}

	ql::smooth_rectangle& ql::smooth_rectangle::operator=(const ql::vsmooth_rectangle& smooth_rectangle)
	{
		this->position = smooth_rectangle.get_position();
		this->dimension = smooth_rectangle.get_dimension();

		this->polygon.set_color(smooth_rectangle.color);
		this->polygon.set_outline_color(smooth_rectangle.outline_color);
		this->polygon.set_outline_thickness(smooth_rectangle.outline_thickness);
		this->polygon.shape.setFillColor(smooth_rectangle.color);
		this->polygon.shape.setOutlineColor(smooth_rectangle.outline_color);

		auto active_corners = smooth_rectangle.round_corners.number_of_set_bits();
		auto size = smooth_rectangle.slope_point_count;
		this->polygon.resize(active_corners * size + (4 - active_corners));

		auto position = smooth_rectangle.position;
		auto dimension = smooth_rectangle.slope_dim;
		auto rect_dimension = smooth_rectangle.dimension;
		auto slope_exponent = std::pow(smooth_rectangle.slope, 1.0);

		ql::u32 ctr = 0u;

		if (smooth_rectangle.round_corners[0u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::smooth_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(progress, -value) * dimension;
				auto pos = position + ql::vec(0, dimension.y) + curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position;
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		if (smooth_rectangle.round_corners[1u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(1 - ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::smooth_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(progress, value) * dimension;
				auto pos = position + ql::vec(rect_dimension.x, dimension.y) - curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position + rect_dimension.just_x();
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		if (smooth_rectangle.round_corners[2u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::smooth_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(-progress, value) * dimension;
				auto pos = position + ql::vec(rect_dimension.x, rect_dimension.y - dimension.y) + curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position + rect_dimension;
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		if (smooth_rectangle.round_corners[3u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(1 - ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::smooth_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(progress, value) * dimension;
				auto pos = position + ql::vec(0, rect_dimension.y - dimension.y) + curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position + rect_dimension.just_y();
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		this->internal_check = false;
		return *this;
	}

	const ql::smooth_rectangle& ql::smooth_rectangle::operator=(const ql::vsmooth_rectangle& smooth_rectangle) const
	{
		this->position = smooth_rectangle.get_position();
		this->dimension = smooth_rectangle.get_dimension();

		this->polygon.set_color(smooth_rectangle.color);
		this->polygon.set_outline_color(smooth_rectangle.outline_color);
		this->polygon.set_outline_thickness(smooth_rectangle.outline_thickness);
		this->polygon.shape.setFillColor(smooth_rectangle.color);
		this->polygon.shape.setOutlineColor(smooth_rectangle.outline_color);

		auto active_corners = smooth_rectangle.round_corners.number_of_set_bits();
		auto size = smooth_rectangle.slope_point_count;
		this->polygon.resize(active_corners * size + (4 - active_corners));

		auto position = smooth_rectangle.position;
		auto dimension = smooth_rectangle.slope_dim;
		auto rect_dimension = smooth_rectangle.dimension;
		auto slope_exponent = std::pow(smooth_rectangle.slope, 1.0);

		ql::u32 ctr = 0u;

		if (smooth_rectangle.round_corners[0u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::smooth_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(progress, -value) * dimension;
				auto pos = position + ql::vec(0, dimension.y) + curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position;
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		if (smooth_rectangle.round_corners[1u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(1 - ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::smooth_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(progress, value) * dimension;
				auto pos = position + ql::vec(rect_dimension.x, dimension.y) - curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position + rect_dimension.just_x();
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		if (smooth_rectangle.round_corners[2u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::smooth_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(-progress, value) * dimension;
				auto pos = position + ql::vec(rect_dimension.x, rect_dimension.y - dimension.y) + curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position + rect_dimension;
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		if (smooth_rectangle.round_corners[3u])
		{
			for (ql::u32 i = 0u; i < size; ++i)
			{
				auto progress = std::pow(1 - ql::f64_cast(i) / (size - 1), slope_exponent);
				auto value = ql::smooth_curve(progress, smooth_rectangle.slope);
				auto curve_pos = ql::vec(progress, value) * dimension;
				auto pos = position + ql::vec(0, rect_dimension.y - dimension.y) + curve_pos;
				this->polygon.set_point(ctr, pos);
				++ctr;
			}
		}
		else
		{
			auto pos = position + rect_dimension.just_y();
			this->polygon.set_point(ctr, pos);
			++ctr;
		}
		this->internal_check = false;
		return *this;
	}

	void ql::smooth_rectangle::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->check_create();
		this->polygon.draw(window, states);
	}

	void ql::vsmooth_corner::invert()
	{
		this->slope = 1.0 / this->slope;
	}

	void ql::vsmooth_corner::move(ql::vec2 delta)
	{
		this->position.move(delta);
	}

	void ql::vsmooth_corner::set_rotation(ql::f64 rotation)
	{
		this->rotation = rotation;
	}

	void ql::vsmooth_corner::set_dimension(ql::vec2 dimension)
	{
		this->dimension = dimension;
	}

	void ql::vsmooth_corner::set_position(ql::vec2 position)
	{
		this->position = position;
	}

	void ql::vsmooth_corner::set_hitbox(ql::hitbox hitbox)
	{
		this->position = hitbox.position;
		this->dimension = hitbox.dimension;
	}

	void ql::vsmooth_corner::set_center(ql::vec2 position)
	{
		this->position = position - this->dimension / 2;
	}

	void ql::vsmooth_corner::set_slope(ql::f64 slope)
	{
		this->slope = slope;
	}

	void ql::vsmooth_corner::set_color(ql::rgba color)
	{
		this->color = color;
	}

	void ql::vsmooth_corner::set_slope_point_count(ql::size point_count)
	{
		this->slope_point_count = point_count;
	}

	ql::f64 ql::vsmooth_corner::get_rotation() const
	{
		return this->rotation;
	}

	ql::vec2 ql::vsmooth_corner::get_dimension() const
	{
		return this->dimension;
	}

	ql::vec2 ql::vsmooth_corner::get_position() const
	{
		return this->position;
	}

	ql::hitbox ql::vsmooth_corner::get_hitbox() const
	{
		return ql::hitbox(this->get_position(), this->get_dimension());
	}

	ql::vec2 ql::vsmooth_corner::get_center() const
	{
		return this->position + this->dimension / 2;
	}

	ql::f64 ql::vsmooth_corner::get_slope() const
	{
		return this->slope;
	}

	ql::rgba ql::vsmooth_corner::get_color() const
	{
		return this->color;
	}

	ql::size ql::vsmooth_corner::get_slope_point_count() const
	{
		return this->slope_point_count;
	}

	void ql::vsmooth_corner::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::smooth_corner = *this;
		ql::detail::smooth_corner.draw(window, states);
	}

	void ql::smooth_corner::invert()
	{
		this->slope = 1.0 / this->slope;
	}

	void ql::smooth_corner::set_rotation(ql::f64 rotation)
	{
		this->rotation = rotation;
		this->internal_check = true;
	}

	void ql::smooth_corner::set_position(ql::vec2 position)
	{
		this->position = position;
		this->internal_check = true;
	}

	void ql::smooth_corner::set_dimension(ql::vec2 dimension)
	{
		this->dimension = dimension;
		this->internal_check = true;
	}

	void ql::smooth_corner::set_hitbox(ql::hitbox hitbox)
	{
		this->position = hitbox.position;
		this->dimension = hitbox.dimension;
		this->internal_check = true;
	}

	void ql::smooth_corner::set_center(ql::vec2 position)
	{
		this->position = position - this->dimension / 2;
		this->internal_check = true;
	}

	void ql::smooth_corner::set_slope(ql::f64 slope)
	{
		this->slope = slope;
		this->internal_check = true;
	}

	void ql::smooth_corner::set_color(ql::rgba color)
	{
		this->color = color;
		this->internal_check = true;
	}

	void ql::smooth_corner::set_slope_point_count(ql::size point_count)
	{
		this->slope_point_count = point_count;
		this->internal_check = true;
	}

	ql::f64 ql::smooth_corner::get_rotation() const
	{
		return this->rotation;
	}

	ql::vec2 ql::smooth_corner::get_dimension() const
	{
		return this->dimension;
	}

	ql::vec2 ql::smooth_corner::get_position() const
	{
		return this->position;
	}

	ql::hitbox ql::smooth_corner::get_hitbox() const
	{
		return ql::hitbox(this->position, this->dimension);
	}

	ql::vec2 ql::smooth_corner::get_center() const
	{
		return this->position + this->dimension / 2;
	}

	ql::f64 ql::smooth_corner::get_slope() const
	{
		return this->slope;
	}

	ql::rgba ql::smooth_corner::get_color() const
	{
		return this->color;
	}

	ql::size ql::smooth_corner::get_slope_point_count() const
	{
		return this->slope_point_count;
	}

	void ql::smooth_corner::move(ql::vec2 delta)
	{
		this->check_create();
		this->position.move(delta);
		this->internal_check = true;
	}

	void ql::smooth_corner::check_create() const
	{
		if (this->internal_check)
		{
			ql::vsmooth_corner corner;
			corner.set_dimension(this->dimension);
			corner.set_position(this->position);
			corner.set_slope(this->slope);
			corner.set_slope_point_count(this->slope_point_count);
			corner.set_color(this->get_color());
			corner.set_rotation(this->rotation);

			*this = corner;
		}
	}

	const ql::smooth_corner& ql::smooth_corner::operator=(const ql::vsmooth_corner& smooth_corner) const
	{
		this->position = smooth_corner.get_position();
		this->dimension = smooth_corner.get_dimension();
		auto size = smooth_corner.slope_point_count;
		this->polygon.resize(size + 1);

		auto offset = smooth_corner.position;
		auto dimension = smooth_corner.dimension;

		auto center = smooth_corner.get_center();

		ql::u32 ctr = 0u;
		this->polygon[ctr].position = smooth_corner.get_hitbox().get_bottom_right().rotated_around(center, smooth_corner.rotation);
		this->polygon[ctr].color = smooth_corner.get_color();
		++ctr;

		auto slope_exponent = std::pow(smooth_corner.slope, 1.0);

		for (ql::u32 i = 0u; i < size; ++i)
		{
			auto progress = std::pow(ql::f64_cast(i) / (size - 1), slope_exponent);
			auto value = ql::smooth_curve(progress, smooth_corner.slope);
			auto curve_pos = ql::vec(progress, 1.0 - value);

			auto pos = offset + curve_pos * dimension;
			this->polygon[ctr].position = pos.rotated_around(center, smooth_corner.rotation);
			this->polygon[ctr].color = smooth_corner.get_color();
			++ctr;
		}
		this->internal_check = false;
		return *this;
	}

	void ql::smooth_corner::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->check_create();
		this->polygon.draw(window, states);
	}

	vpoint& ql::vpoint::operator=(ql::vec2 position)
	{
		this->position = position;
		return *this;
	}

	bool ql::vpoint::operator==(const vpoint& other) const
	{
		return this->position == other.position && this->color == other.color;
	}

	bool ql::vpoint::operator!=(const vpoint& other) const
	{
		return !(*this == other);
	}

	void ql::vpoint::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::point = *this;
		ql::detail::point.draw(window, states);
	}

	ql::line& ql::line::operator=(const ql::vline& line)
	{
		this->vertices[0].position = line.a.position;
		this->vertices[0].color = line.a.color;
		this->vertices[1].position = line.b.position;
		this->vertices[1].color = line.b.color;
		return *this;
	}

	ql::line& ql::line::operator=(const ql::straight_line& line)
	{
		this->vertices[0].position = line.a;
		this->vertices[1].position = line.b;
		return *this;
	}

	void ql::line::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->vertices.data(), this->vertices.size(), sf::PrimitiveType::Lines, states);
	}

	ql::point& ql::point::operator=(const ql::vpoint& point)
	{
		this->vertex.position = point.position;
		this->vertex.color = point.color;
		return *this;
	}

	void ql::point::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->vertex.draw(window, states);
	}

	ql::size ql::vpoints::size() const
	{
		return this->points.size();
	}

	void ql::vpoints::resize(ql::size new_size)
	{
		this->points.resize(new_size);
	}

	void ql::vpoints::reserve(ql::size new_size)
	{
		this->points.reserve(new_size);
	}

	ql::vpoint& ql::vpoints::operator[](ql::size index)
	{
		return this->points[index];
	}

	const ql::vpoint& ql::vpoints::operator[](ql::size index) const
	{
		return this->points[index];
	}

	ql::vpoint& ql::vpoints::front()
	{
		return this->points.front();
	}

	const ql::vpoint& ql::vpoints::front() const
	{
		return this->points.front();
	}

	ql::vpoint& ql::vpoints::back()
	{
		return this->points.back();
	}

	const ql::vpoint& ql::vpoints::back() const
	{
		return this->points.back();
	}

	std::vector<ql::vpoint>::iterator ql::vpoints::begin()
	{
		return this->points.begin();
	}

	std::vector<ql::vpoint>::const_iterator ql::vpoints::begin() const
	{
		return this->points.begin();
	}

	std::vector<ql::vpoint>::const_iterator ql::vpoints::cbegin() const
	{
		return this->points.cbegin();
	}

	std::vector<ql::vpoint>::iterator ql::vpoints::end()
	{
		return this->points.end();
	}

	std::vector<ql::vpoint>::const_iterator ql::vpoints::end() const
	{
		return this->points.end();
	}

	std::vector<ql::vpoint>::const_iterator ql::vpoints::cend() const
	{
		return this->points.cend();
	}

	void ql::vpoints::add_point(ql::vpoint point)
	{
		this->points.push_back(point);
	}

	void ql::vpoints::add_point(ql::vec2 position, ql::rgba color)
	{
		this->points.push_back(ql::vpoint(position, color));
	}

	ql::vlines ql::vpoints::as_lines() const
	{
		ql::vlines result;
		result.points = this->points;
		result.complete();
		return result;
	}

	void ql::vpoints::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::points = *this;
		ql::detail::points.draw(window, states);
	}

	void ql::vpoints::clear()
	{
		this->points.clear();
	}

	void ql::points::resize(ql::size new_size)
	{
		this->vertices.resize(new_size);
	}

	void ql::points::reserve(ql::size new_size)
	{
		this->vertices.reserve(new_size);
	}

	ql::vertex& ql::points::operator[](ql::size index)
	{
		return this->vertices[index];
	}

	const ql::vertex& ql::points::operator[](ql::size index) const
	{
		return this->vertices[index];
	}

	ql::vertex& ql::points::front()
	{
		return this->vertices[0u];
	}

	const ql::vertex& ql::points::front() const
	{
		return this->vertices[0u];
	}

	ql::vertex& ql::points::back()
	{
		return this->vertices[this->size() - 1];
	}

	const ql::vertex& ql::points::back() const
	{
		return this->vertices[this->size() - 1];
	}

	ql::vlines ql::points::as_lines() const
	{
		ql::vlines result;

		result.points.resize(this->vertices.size());
		for (ql::u32 i = 0u; i < result.points.size(); ++i)
		{
			result.points[i].position = this->vertices[i].position;
			result.points[i].color = this->vertices[i].color;
		}

		result.complete();
		return result;
	}

	ql::points& ql::points::operator=(const ql::vpoints& points)
	{
		this->vertices.resize(points.points.size());
		for (ql::u32 i = 0u; i < points.points.size(); ++i)
		{
			this->vertices[i].color = points.points[i].color;
			this->vertices[i].position = points.points[i].position;
		}
		return *this;
	}

	void ql::points::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->vertices.draw(window, states);
	}

	void ql::points::clear()
	{
		this->vertices.clear();
	}

	ql::size ql::points::size() const
	{
		return this->vertices.size();
	}

	bool ql::vcircle::contains(ql::vec2 position) const
	{
		return (this->get_center() - position).length() < this->radius;
	}

	void ql::vcircle::set_position(ql::vec2 position)
	{
		this->point.position = position;
	}

	void ql::vcircle::set_radius(ql::f32 radius)
	{
		this->radius = radius;
	}

	void ql::vcircle::set_color(ql::rgba color)
	{
		this->point.color = color;
	}

	void ql::vcircle::set_center(ql::vec2 center)
	{
		this->point.position = center - ql::vec2{this->radius, this->radius};
	}

	void ql::vcircle::set_outline_thickness(ql::f32 outline_thickness)
	{
		this->outline_thickness = outline_thickness;
	}

	void ql::vcircle::set_outline_color(ql::rgba outline_color)
	{
		this->outline_color = outline_color;
	}

	ql::vec2 ql::vcircle::get_center() const
	{
		return this->point.position + ql::vec2{this->radius, this->radius};
	}

	void ql::vcircle::centerize()
	{
		this->point.position -= ql::vec2{this->radius, this->radius};
	}

	void ql::vcircle::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::circle = *this;
		ql::detail::circle.draw(window, states);
	}

	void ql::circle::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->circle_shape, states);
	}

	ql::circle& ql::circle::operator=(const ql::vcircle& circle)
	{
		this->circle_shape.setPosition(circle.point.position);
		this->circle_shape.setRadius(circle.radius);
		this->circle_shape.setFillColor(circle.point.color);
		this->circle_shape.setOutlineThickness(circle.outline_thickness);
		this->circle_shape.setOutlineColor(circle.outline_color);
		return *this;
	}

	ql::circle& ql::circle::operator=(const ql::circle& circle)
	{
		this->circle_shape.setPosition(circle.circle_shape.getPosition());
		this->circle_shape.setRadius(circle.circle_shape.getRadius());
		this->circle_shape.setFillColor(circle.circle_shape.getFillColor());
		this->circle_shape.setOrigin(circle.circle_shape.getOrigin());
		return *this;
	}

	bool ql::circle::contains(ql::vec2 position) const
	{
		return (this->get_center() - position).length() < this->get_radius();
	}

	void ql::circle::centerize_origin()
	{
		this->circle_shape.setOrigin(ql::vec(this->get_radius(), this->get_radius()));
	}

	void ql::circle::set_radius(ql::f32 radius)
	{
		this->circle_shape.setRadius(radius);
	}

	ql::f32 ql::circle::get_radius() const
	{
		return this->circle_shape.getRadius();
	}

	void ql::circle::set_position(ql::vec2 position)
	{
		this->circle_shape.setPosition(position);
	}

	void ql::circle::set_center(ql::vec2 center)
	{
		this->set_position(center - ql::vec2{this->get_radius(), this->get_radius()});
	}

	ql::vec2 ql::circle::get_center() const
	{
		return this->get_position() + ql::vec2{this->get_radius(), this->get_radius()};
	}

	ql::vec2 ql::circle::get_position() const
	{
		return this->circle_shape.getPosition();
	}

	void ql::circle::set_color(ql::rgba color)
	{
		this->circle_shape.setFillColor(color);
	}

	ql::rgba ql::circle::get_color() const
	{
		return this->circle_shape.getFillColor();
	}

	void ql::circle::set_outline_thickness(ql::f32 outline_thickness)
	{
		this->circle_shape.setOutlineThickness(outline_thickness);
	}

	ql::f32 ql::circle::get_outline_thickness() const
	{
		return this->circle_shape.getOutlineThickness();
	}

	void ql::circle::set_outline_color(ql::rgba outline_color)
	{
		this->circle_shape.setOutlineColor(outline_color);
	}

	ql::rgba ql::circle::get_outline_color() const
	{
		return this->circle_shape.getOutlineColor();
	}

	void ql::circle::set_point_count(ql::size count)
	{
		this->circle_shape.setPointCount(count);
	}

	ql::size ql::circle::get_point_count() const
	{
		return this->circle_shape.getPointCount();
	}

	void ql::vcircles::resize(ql::size new_size)
	{
		this->circles.resize(new_size);
	}

	void ql::vcircles::reserve(ql::size new_size)
	{
		this->circles.reserve(new_size);
	}

	ql::vcircle& ql::vcircles::operator[](ql::size index)
	{
		return this->circles[index];
	}

	const ql::vcircle& ql::vcircles::operator[](ql::size index) const
	{
		return this->circles[index];
	}

	ql::vcircle& ql::vcircles::front()
	{
		return this->circles.front();
	}

	const ql::vcircle& ql::vcircles::front() const
	{
		return this->circles.front();
	}

	ql::vcircle& ql::vcircles::back()
	{
		return this->circles.back();
	}

	const ql::vcircle& ql::vcircles::back() const
	{
		return this->circles.back();
	}

	void ql::vcircles::add_circle(ql::vcircle circle)
	{
		this->circles.push_back(circle);
	}

	void ql::vcircles::add_circle(ql::vpoint point, ql::f32 radius, ql::rgba color)
	{
		this->circles.push_back(ql::vcircle(point.position, radius, color));
	}

	void ql::vcircles::add_circle(ql::vec2 position, ql::f32 radius, ql::rgba color)
	{
		this->circles.push_back(ql::vcircle(position, radius, color));
	}

	ql::size ql::vcircles::size() const
	{
		return this->circles.size();
	}

	void ql::vcircles::clear()
	{
		this->circles.clear();
	}

	void ql::vcircles::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::circles = *this;
		ql::detail::circles.draw(window, states);
	}

	void ql::circles::resize(ql::size new_size)
	{
		this->circles_.resize(new_size);
	}

	void ql::circles::reserve(ql::size new_size)
	{
		this->circles_.reserve(new_size);
	}

	ql::circle& ql::circles::operator[](ql::size index)
	{
		return this->circles_[index];
	}

	const ql::circle& ql::circles::operator[](ql::size index) const
	{
		return this->circles_[index];
	}

	ql::circle& ql::circles::front()
	{
		return this->circles_.front();
	}

	const ql::circle& ql::circles::front() const
	{
		return this->circles_.front();
	}

	ql::circle& ql::circles::back()
	{
		return this->circles_.back();
	}

	const ql::circle& ql::circles::back() const
	{
		return this->circles_.back();
	}

	void ql::circles::add_circle(const ql::vcircle& circle)
	{
		this->circles_.push_back(circle);
	}

	void ql::circles::add_circle(const ql::circle& circle)
	{
		this->circles_.push_back(circle);
	}

	void ql::circles::add_circle(ql::vpoint point, ql::f32 radius, ql::rgba color)
	{
		this->circles_.push_back(ql::vcircle(point.position, radius, color));
	}

	void ql::circles::add_circle(ql::vec2 position, ql::f32 radius, ql::rgba color)
	{
		this->circles_.push_back(ql::vcircle(position, radius, color));
	}

	void ql::circles::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		for (auto& i : this->circles_)
		{
			i.draw(window, states);
		}
	}

	ql::circles& ql::circles::operator=(const ql::vcircles& circles)
	{
		this->circles_.resize(circles.size());
		for (ql::u32 i = 0u; i < circles.size(); ++i)
		{
			this->circles_[i] = circles.circles[i];
		}
		return *this;
	}

	ql::circles& ql::circles::operator=(const ql::circles& circles)
	{
		this->circles_ = circles.circles_;
		return *this;
	}

	void ql::circles::clear()
	{
		this->circles_.clear();
	}

	ql::size ql::circles::size() const
	{
		return this->circles_.size();
	}

	void ql::vline::set_a(ql::vpoint point)
	{
		this->a = point.position;
	}

	void ql::vline::set_a(ql::vec2 position)
	{
		this->a = position;
	}

	void ql::vline::set_b(ql::vpoint point)
	{
		this->b = point.position;
	}

	void ql::vline::set_b(ql::vec2 position)
	{
		this->b = position;
	}

	void ql::vline::set_color(ql::rgba color)
	{
		this->a.color = this->b.color = color;
	}

	void ql::vline::set_a_color(ql::rgba color)
	{
		this->a.color = color;
	}

	void ql::vline::set_b_color(ql::rgba color)
	{
		this->b.color = color;
	}

	ql::f32 ql::vline::length() const
	{
		auto diff = this->b.position - this->a.position;
		return std::sqrt(diff.x * diff.x + diff.y * diff.y);
	}

	ql::vec2 ql::vline::normal() const
	{
		return ql::vec2{this->a.position.y - this->b.position.y, this->b.position.x - this->a.position.x} / this->length();
	}

	ql::vline& ql::vline::rotate_around_a(ql::f64 degree)
	{
		return *this;
	}

	ql::vline& ql::vline::rotate_around_b(ql::f64 degree)
	{
		// a / sin(a) = b / sin(b) = c / sin(c)

		//(x, y) +
		return *this;
	}

	ql::vline::operator ql::straight_line() const
	{
		return ql::straight_line(this->a.position, this->b.position);
	}

	void ql::vline::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::line = *this;
		ql::detail::line.draw(window, states);
	}

	void ql::line::set_a(ql::vpoint point)
	{
		this->vertices[0].position = point.position;
	}

	void ql::line::set_a(ql::vec2 position)
	{
		this->vertices[0].position = position;
	}

	void ql::line::set_b(ql::vpoint point)
	{
		this->vertices[1].position = point.position;
	}

	void ql::line::set_b(ql::vec2 position)
	{
		this->vertices[1].position = position;
	}

	void ql::line::set_color(ql::rgba color)
	{
		this->vertices[0].color = this->vertices[1].color = color;
	}

	void ql::line::set_a_color(ql::rgba color)
	{
		this->vertices[0].color = color;
	}

	void ql::line::set_b_color(ql::rgba color)
	{
		this->vertices[1].color = color;
	}

	ql::vpoint ql::line::get_a() const
	{
		return ql::vpoint(this->vertices[0].position, this->vertices[0].color);
	}

	ql::vpoint ql::line::get_b() const
	{
		return ql::vpoint(this->vertices[1].position, this->vertices[1].color);
	}

	ql::vec2 ql::line::normal() const
	{
		return ql::vec2{
							 this->vertices[0].position.y - this->vertices[1].position.y,
							 this->vertices[1].position.x - this->vertices[0].position.x
					 } /
					 this->length();
	}

	ql::f32 ql::line::length() const
	{
		ql::vec2 diff = this->vertices[0].position - this->vertices[1].position;
		return std::sqrt(diff.x * diff.x + diff.y * diff.y);
	}

	ql::line::operator ql::straight_line() const
	{
		return ql::straight_line(this->vertices[0].position, this->vertices[1].position);
	}

	void ql::vlines::resize(ql::size new_size)
	{
		this->points.resize(new_size);
	}

	void ql::vlines::reserve(ql::size new_size)
	{
		this->points.reserve(new_size);
	}

	ql::vpoint& ql::vlines::operator[](ql::size index)
	{
		return this->points[index];
	}

	const ql::vpoint& ql::vlines::operator[](ql::size index) const
	{
		return this->points[index];
	}

	ql::vpoint& ql::vlines::front()
	{
		return this->points.front();
	}

	const ql::vpoint& ql::vlines::front() const
	{
		return this->points.front();
	}

	ql::vpoint& ql::vlines::back()
	{
		return this->points.back();
	}

	const ql::vpoint& ql::vlines::back() const
	{
		return this->points.back();
	}

	void ql::vlines::clear()
	{
		this->points.clear();
	}

	ql::size ql::vlines::size() const
	{
		return this->points.size();
	}

	void ql::vlines::add_point(ql::vpoint point)
	{
		this->points.push_back(point);
	}

	void ql::vlines::add_point(ql::vec2 position, ql::rgba color)
	{
		this->points.push_back(ql::vpoint{position, color});
	}

	void ql::vlines::complete()
	{
		this->add_point(this->points[0]);
	}

	void ql::vlines::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::lines = *this;
		ql::detail::lines.draw(window, states);
	}

	void ql::lines::resize(ql::size new_size)
	{
		this->vertices.resize(new_size);
	}

	void ql::lines::reserve(ql::size new_size)
	{
		this->vertices.reserve(new_size);
	}

	ql::vertex& ql::lines::operator[](ql::size index)
	{
		return this->vertices[index];
	}

	const ql::vertex& ql::lines::operator[](ql::size index) const
	{
		return this->vertices[index];
	}

	ql::vertex& ql::lines::front()
	{
		return this->vertices[0u];
	}

	const ql::vertex& ql::lines::front() const
	{
		return this->vertices[0u];
	}

	ql::vertex& ql::lines::back()
	{
		return this->vertices[this->size() - 1u];
	}

	const ql::vertex& ql::lines::back() const
	{
		return this->vertices[this->size() - 1u];
	}

	void ql::lines::complete()
	{
		this->add_point(this->vertices[0].position, this->vertices[0].color);
	}

	ql::lines& ql::lines::operator=(const ql::vlines& lines)
	{
		this->vertices.resize(lines.size());
		for (ql::u32 i = 0u; i < lines.points.size(); ++i)
		{
			this->vertices[i] = ql::vertex(lines.points[i].position, lines.points[i].color);
		}
		return *this;
	}

	void ql::lines::clear()
	{
		this->vertices.clear();
	}

	ql::size ql::lines::size() const
	{
		return this->vertices.size();
	}

	void ql::lines::add_point(ql::vpoint point)
	{
		this->vertices.add(ql::vertex(point.position, point.color));
	}

	void ql::lines::add_point(ql::vec2 position, ql::rgba color)
	{
		this->vertices.add(ql::vertex(position, color));
	}

	void ql::lines::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->vertices.draw(window, states);
	}

	void ql::vthick_line::set_a(ql::vpoint point)
	{
		this->a = point.position;
	}

	void ql::vthick_line::set_a(ql::vec2 position)
	{
		this->a = position;
	}

	void ql::vthick_line::set_b(ql::vpoint point)
	{
		this->b = point.position;
	}

	void ql::vthick_line::set_b(ql::vec2 position)
	{
		this->b = position;
	}

	void ql::vthick_line::set_color(ql::rgba color)
	{
		this->a.color = this->b.color = color;
	}

	void ql::vthick_line::set_a_color(ql::rgba color)
	{
		this->a.color = color;
	}

	void ql::vthick_line::set_b_color(ql::rgba color)
	{
		this->b.color = color;
	}

	ql::f32 ql::vthick_line::length() const
	{
		auto diff = this->b.position - this->a.position;
		return std::sqrt(diff.x * diff.x + diff.y * diff.y);
	}

	ql::vpoints ql::vthick_line::as_points() const
	{
		ql::vpoints result(4);
		auto normal = this->normal();

		result.points[0].position = this->a.position - normal * this->thickness;
		result.points[1].position = this->a.position + normal * this->thickness;
		result.points[2].position = this->b.position + normal * this->thickness;
		result.points[3].position = this->b.position - normal * this->thickness;

		return result;
	}

	ql::vec2 ql::vthick_line::normal() const
	{
		return ql::vec2{this->a.position.y - this->b.position.y, this->b.position.x - this->a.position.x} / this->length();
	}

	void ql::vthick_line::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::thick_line = *this;
		ql::detail::thick_line.draw(window, states);
	}

	void ql::thick_line::set_a(ql::vpoint point)
	{
		this->vertices[0].position = this->vertices[1].position = point.position;
		this->vertices[0].color = this->vertices[1].color = point.color;
	}

	void ql::thick_line::set_a(ql::vec2 position)
	{
		this->vertices[0].position = this->vertices[1].position = position;
	}

	void ql::thick_line::extend_a(ql::f32 delta)
	{
		auto direction =
				ql::vec2{
						this->vertices[2].position.y - this->vertices[0].position.y,
						this->vertices[2].position.x - this->vertices[0].position.x
				} /
				this->length();
		this->vertices[0].position -= sf::Vector2f(direction * delta);
		this->vertices[1].position -= sf::Vector2f(direction * delta);
	}

	void ql::thick_line::set_b(ql::vpoint point)
	{
		this->vertices[2].position = this->vertices[3].position = point.position;
		this->vertices[2].color = this->vertices[3].color = point.color;
	}

	void ql::thick_line::set_b(ql::vec2 position)
	{
		this->vertices[2].position = this->vertices[3].position = position;
	}

	void ql::thick_line::extend_b(ql::f32 delta)
	{
		auto direction =
				ql::vec2{
						this->vertices[2].position.y - this->vertices[0].position.y,
						this->vertices[2].position.x - this->vertices[0].position.x
				} /
				this->length();
		this->vertices[2].position += sf::Vector2f(direction * delta);
		this->vertices[3].position += sf::Vector2f(direction * delta);
	}

	void ql::thick_line::set_color(ql::rgba color)
	{
		this->vertices[0].color = this->vertices[1].color = this->vertices[2].color = this->vertices[3].color = color;
	}

	void ql::thick_line::set_a_color(ql::rgba color)
	{
		this->vertices[0].color = this->vertices[1].color = color;
	}

	void ql::thick_line::set_b_color(ql::rgba color)
	{
		this->vertices[2].color = this->vertices[3].color = color;
	}

	void ql::thick_line::set_thickness(ql::f32 thickness)
	{
		auto normal = this->normal();

		ql::vec2 a_pos = this->vertices[0].position;
		ql::vec2 b_pos = this->vertices[2].position;

		this->vertices[0].position = a_pos - normal * thickness;
		this->vertices[1].position = a_pos + normal * thickness;
		this->vertices[2].position = b_pos + normal * thickness;
		this->vertices[3].position = b_pos - normal * thickness;
	}

	void ql::thick_line::move(ql::vec2 delta)
	{
		this->vertices[0].position += sf::Vector2f(delta);
		this->vertices[1].position += sf::Vector2f(delta);
		this->vertices[2].position += sf::Vector2f(delta);
		this->vertices[3].position += sf::Vector2f(delta);
	}

	ql::f32 ql::thick_line::length() const
	{
		auto diff = this->vertices[0].position - this->vertices[2].position;
		return std::sqrt(diff.x * diff.x + diff.y * diff.y);
	}

	ql::vpoints ql::thick_line::as_points() const
	{
		ql::vpoints result(4);
		auto normal = this->normal();

		result.points[0].position = this->vertices[0].position;
		result.points[1].position = this->vertices[1].position;
		result.points[2].position = this->vertices[2].position;
		result.points[3].position = this->vertices[3].position;

		return result;
	}

	ql::vec2 ql::thick_line::normal() const
	{
		return ql::vec2{
							 this->vertices[0].position.y - this->vertices[2].position.y,
							 this->vertices[2].position.x - this->vertices[0].position.x
					 } /
					 this->length();
	}

	ql::thick_line& ql::thick_line::operator=(const ql::vthick_line& line)
	{
		auto normal = line.normal();

		this->vertices[0].position = line.a.position - normal * line.thickness;
		this->vertices[0].color = line.a.color;
		this->vertices[1].position = line.a.position + normal * line.thickness;
		this->vertices[1].color = line.a.color;
		this->vertices[2].position = line.b.position + normal * line.thickness;
		this->vertices[2].color = line.b.color;
		this->vertices[3].position = line.b.position - normal * line.thickness;
		this->vertices[3].color = line.b.color;
		return *this;
	}

	void ql::thick_line::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->vertices.data(), this->vertices.size(), sf::PrimitiveType::Quads, states);
	}

	void ql::vthick_lines::resize(ql::size new_size)
	{
		this->points.resize(new_size);
	}

	void ql::vthick_lines::reserve(ql::size new_size)
	{
		this->points.reserve(new_size);
	}

	ql::vpoint& ql::vthick_lines::operator[](ql::size index)
	{
		return this->points[index];
	}

	const ql::vpoint& ql::vthick_lines::operator[](ql::size index) const
	{
		return this->points[index];
	}

	ql::vpoint& ql::vthick_lines::front()
	{
		return this->points.front();
	}

	const ql::vpoint& ql::vthick_lines::front() const
	{
		return this->points.front();
	}

	ql::vpoint& ql::vthick_lines::back()
	{
		return this->points.back();
	}

	const ql::vpoint& ql::vthick_lines::back() const
	{
		return this->points.back();
	}

	void ql::vthick_lines::add_thick_line(ql::vpoint point)
	{
		this->points.add_point(point);
	}

	void ql::vthick_lines::add_thick_line(ql::vec2 position, ql::rgba color)
	{
		this->points.add_point(position, color);
	}

	void ql::vthick_lines::set_thickness(ql::f32 thickness)
	{
		this->thickness = thickness;
	}

	void ql::vthick_lines::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::thick_lines = *this;
		ql::detail::thick_lines.draw(window, states);
	}

	void ql::vthick_lines::clear()
	{
		this->points.clear();
	}

	ql::size ql::vthick_lines::size() const
	{
		return this->points.size();
	}

	void ql::thick_lines::resize(ql::size new_size)
	{
		this->vertices.resize(new_size);
	}

	void ql::thick_lines::reserve(ql::size new_size)
	{
		this->vertices.reserve(new_size);
	}

	ql::vertex& ql::thick_lines::operator[](ql::size index)
	{
		return this->vertices[index];
	}

	const ql::vertex& ql::thick_lines::operator[](ql::size index) const
	{
		return this->vertices[index];
	}

	ql::vertex& ql::thick_lines::front()
	{
		return this->vertices[0u];
	}

	const ql::vertex& ql::thick_lines::front() const
	{
		return this->vertices[0u];
	}

	ql::vertex& ql::thick_lines::back()
	{
		return this->vertices[this->size() - 1u];
	}

	const ql::vertex& ql::thick_lines::back() const
	{
		return this->vertices[this->size() - 1u];
	}

	void ql::thick_lines::add_thick_line(ql::vpoint point, ql::f32 thickness)
	{
		this->add_thick_line(point.position, point.color, thickness);
	}

	void ql::thick_lines::add_thick_line(ql::vec2 position, ql::rgba color, ql::f32 thickness)
	{
		auto last_point = position;
		auto last_color = color;
		auto last_thickness = thickness;
		if (this->vertices.size())
		{
			last_point =
					(this->vertices[this->vertices.size() - 1].position + this->vertices[this->vertices.size() - 2].position) / 2.0f;

			last_color.r = ql::u8_cast(
					(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.r) +
					 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.r)) /
					2
			);
			last_color.g = ql::u8_cast(
					(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.g) +
					 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.g)) /
					2
			);
			last_color.b = ql::u8_cast(
					(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.b) +
					 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.b)) /
					2
			);
			last_color.a = ql::u8_cast(
					(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.a) +
					 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.a)) /
					2
			);

			ql::vline line;
			line.set_a(this->vertices[this->vertices.size() - 1].position);
			line.set_b(this->vertices[this->vertices.size() - 2].position);
			last_thickness = line.length() / 2;
		}

		ql::vline line;
		line.set_b(last_point);
		line.set_a(position);

		auto normal = line.normal();
		if (position == last_point)
		{
			normal.x = 1.0;
			normal.y = 0.0;
		}

		if (this->vertices.size() > 4u)
		{
			this->vertices.resize(this->vertices.size() + 8);
			this->vertices[this->vertices.size() - 8] = this->vertices[this->vertices.size() - 10];
			this->vertices[this->vertices.size() - 7] = this->vertices[this->vertices.size() - 9];
			this->vertices[this->vertices.size() - 6].position = last_point + normal * last_thickness;
			this->vertices[this->vertices.size() - 6].color = last_color;
			this->vertices[this->vertices.size() - 5].position = last_point - normal * last_thickness;
			this->vertices[this->vertices.size() - 5].color = last_color;

			this->vertices[this->vertices.size() - 4] = this->vertices[this->vertices.size() - 6];
			this->vertices[this->vertices.size() - 3] = this->vertices[this->vertices.size() - 5];
			this->vertices[this->vertices.size() - 2].position = position - normal * thickness;
			this->vertices[this->vertices.size() - 2].color = color;
			this->vertices[this->vertices.size() - 1].position = position + normal * thickness;
			this->vertices[this->vertices.size() - 1].color = color;
		}
		else
		{
			this->vertices.resize(this->vertices.size() + 4);
			this->vertices[this->vertices.size() - 4].position = last_point + normal * last_thickness;
			this->vertices[this->vertices.size() - 4].color = last_color;
			this->vertices[this->vertices.size() - 3].position = last_point - normal * last_thickness;
			this->vertices[this->vertices.size() - 3].color = last_color;
			this->vertices[this->vertices.size() - 2].position = position - normal * thickness;
			this->vertices[this->vertices.size() - 2].color = color;
			this->vertices[this->vertices.size() - 1].position = position + normal * thickness;
			this->vertices[this->vertices.size() - 1].color = color;
		}
	}

	void ql::thick_lines::complete()
	{
		if (this->empty())
		{
			return;
		}
		ql::vec2 first_point;
		ql::rgba first_color;
		ql::f32 first_thickness = 0.0f;

		if (this->vertices.size())
		{
			first_point = (this->vertices[0].position + this->vertices[1].position) / 2.0f;

			first_color.r = ql::u8_cast((ql::u32_cast(this->vertices[0].color.r) + ql::u32_cast(this->vertices[1].color.r)) / 2);
			first_color.g = ql::u8_cast((ql::u32_cast(this->vertices[0].color.g) + ql::u32_cast(this->vertices[1].color.g)) / 2);
			first_color.b = ql::u8_cast((ql::u32_cast(this->vertices[0].color.b) + ql::u32_cast(this->vertices[1].color.b)) / 2);
			first_color.a = ql::u8_cast((ql::u32_cast(this->vertices[0].color.a) + ql::u32_cast(this->vertices[1].color.a)) / 2);

			ql::vline line;
			line.set_a(this->vertices[0].position);
			line.set_b(this->vertices[1].position);
			first_thickness = line.length() / 2;
		}

		auto last_point = first_point;
		auto last_color = first_color;
		auto last_thickness = first_thickness;
		if (this->vertices.size() > 4)
		{
			last_point =
					(this->vertices[this->vertices.size() - 1].position + this->vertices[this->vertices.size() - 2].position) / 2.0f;

			last_color.r = ql::u8_cast(
					(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.r) +
					 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.r)) /
					2
			);
			last_color.g = ql::u8_cast(
					(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.g) +
					 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.g)) /
					2
			);
			last_color.b = ql::u8_cast(
					(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.b) +
					 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.b)) /
					2
			);
			last_color.a = ql::u8_cast(
					(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.a) +
					 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.a)) /
					2
			);

			ql::vline line;
			line.set_a(this->vertices[this->vertices.size() - 1].position);
			line.set_b(this->vertices[this->vertices.size() - 2].position);
			last_thickness = line.length() / 2;
		}

		ql::vline line;
		line.set_b(last_point);
		line.set_a(first_point);

		auto normal = line.normal();
		if (first_point == last_point)
		{
			normal.x = 1.0;
			normal.y = 0.0;
		}

		this->vertices.resize(this->vertices.size() + 8);

		this->vertices[this->vertices.size() - 8] = this->vertices[this->vertices.size() - 10];
		this->vertices[this->vertices.size() - 7] = this->vertices[this->vertices.size() - 9];
		this->vertices[this->vertices.size() - 6].position = last_point + normal * last_thickness;
		this->vertices[this->vertices.size() - 6].color = last_color;
		this->vertices[this->vertices.size() - 5].position = last_point - normal * last_thickness;
		this->vertices[this->vertices.size() - 5].color = last_color;

		this->vertices[this->vertices.size() - 4].position = last_point + normal * last_thickness;
		this->vertices[this->vertices.size() - 4].color = last_color;
		this->vertices[this->vertices.size() - 3].position = last_point - normal * last_thickness;
		this->vertices[this->vertices.size() - 3].color = last_color;
		this->vertices[this->vertices.size() - 2].position = first_point - normal * first_thickness;
		this->vertices[this->vertices.size() - 2].color = first_color;
		this->vertices[this->vertices.size() - 1].position = first_point + normal * first_thickness;
		this->vertices[this->vertices.size() - 1].color = first_color;

		auto mid_point = (this->vertices[8].position + this->vertices[9].position) / 2.0f;

		ql::rgba mid_color;
		mid_color.r = ql::u8_cast((ql::u32_cast(this->vertices[8].color.r) + ql::u32_cast(this->vertices[9].color.r)) / 2);
		mid_color.g = ql::u8_cast((ql::u32_cast(this->vertices[8].color.g) + ql::u32_cast(this->vertices[9].color.g)) / 2);
		mid_color.b = ql::u8_cast((ql::u32_cast(this->vertices[8].color.b) + ql::u32_cast(this->vertices[9].color.b)) / 2);
		mid_color.a = ql::u8_cast((ql::u32_cast(this->vertices[8].color.a) + ql::u32_cast(this->vertices[9].color.a)) / 2);

		line.set_a(this->vertices[8].position);
		line.set_b(this->vertices[9].position);
		auto mid_thickness = line.length() / 2;

		last_point = (this->vertices[this->vertices.size() - 1].position + this->vertices[this->vertices.size() - 2].position) / 2.0f;

		last_color.r = ql::u8_cast(
				(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.r) +
				 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.r)) /
				2
		);
		last_color.g = ql::u8_cast(
				(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.g) +
				 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.g)) /
				2
		);
		last_color.b = ql::u8_cast(
				(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.b) +
				 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.b)) /
				2
		);
		last_color.a = ql::u8_cast(
				(ql::u32_cast(this->vertices[this->vertices.size() - 1].color.a) +
				 ql::u32_cast(this->vertices[this->vertices.size() - 2].color.a)) /
				2
		);

		line.set_a(this->vertices[this->vertices.size() - 1].position);
		line.set_b(this->vertices[this->vertices.size() - 2].position);
		last_thickness = line.length() / 2;

		line.set_b(last_point);
		line.set_a(mid_point);

		normal = line.normal();
		if (mid_point == last_point)
		{
			normal.x = 1.0;
			normal.y = 0.0;
		}

		this->vertices.resize(this->vertices.size() + 4);
		this->vertices[this->vertices.size() - 4] = this->vertices[this->vertices.size() - 6];
		this->vertices[this->vertices.size() - 3] = this->vertices[this->vertices.size() - 5];
		this->vertices[this->vertices.size() - 2].position = last_point + normal * last_thickness;
		this->vertices[this->vertices.size() - 2].color = last_color;
		this->vertices[this->vertices.size() - 1].position = last_point - normal * last_thickness;
		this->vertices[this->vertices.size() - 1].color = last_color;
	}

	ql::thick_lines& ql::thick_lines::operator=(const ql::vthick_lines& lines)
	{
		this->vertices.clear();
		for (auto& p : lines.points.points)
		{
			this->add_thick_line(p.position + lines.position, p.color, lines.thickness);
		}
		return *this;
	}

	void ql::thick_lines::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->vertices.draw(window, states);
	}

	void ql::thick_lines::clear()
	{
		this->vertices.clear();
	}

	ql::size ql::thick_lines::size() const
	{
		return this->vertices.size();
	}

	bool ql::thick_lines::empty() const
	{
		return this->vertices.empty();
	}

	void ql::sprite::set_texture(const sf::Texture& texture)
	{
		this->m_sprite.setTexture(texture);
	}

	void ql::sprite::set_texture_rect(const sf::IntRect& rect)
	{
		this->m_sprite.setTextureRect(rect);
	}

	void ql::sprite::set_texture_rect(ql::hitbox hitbox)
	{
		sf::IntRect rect;
		rect.left = ql::i32_cast(hitbox.position.x);
		rect.top = ql::i32_cast(hitbox.position.y);
		rect.width = ql::i32_cast(hitbox.dimension.x);
		rect.height = ql::i32_cast(hitbox.dimension.y);
		this->m_sprite.setTextureRect(rect);
	}

	void ql::sprite::set_color(ql::rgba color)
	{
		this->m_sprite.setColor(color);
	}

	void ql::sprite::set_position(ql::vec2 position)
	{
		this->m_sprite.setPosition(position);
	}

	void ql::sprite::set_position_x(ql::f32 x)
	{
		auto y = this->get_position().y;
		this->m_sprite.setPosition(ql::vec(x, y));
	}

	void ql::sprite::set_position_y(ql::f32 y)
	{
		auto x = this->get_position().x;
		this->m_sprite.setPosition(ql::vec(x, y));
	}

	void ql::sprite::set_center(ql::vec2 position)
	{
		this->m_sprite.setPosition(position);
		ql::centerize_sprite(this->m_sprite);
	}

	void ql::sprite::set_scale(ql::vec2 scale)
	{
		this->m_sprite.setScale(scale);
	}

	void ql::sprite::set_scale(ql::f32 scale)
	{
		this->m_sprite.setScale(scale, scale);
	}

	void ql::sprite::set_origin(ql::vec2 origin)
	{
		this->m_sprite.setOrigin(origin);
	}

	void ql::sprite::set_rotation(ql::f32 rotation)
	{
		this->m_sprite.setRotation(rotation);
	}

	ql::rgba ql::sprite::get_color() const
	{
		return this->m_sprite.getColor();
	}

	ql::vec2 ql::sprite::get_position() const
	{
		return this->m_sprite.getPosition();
	}

	ql::vec2 ql::sprite::get_dimension() const
	{
		return ql::get_sprite_hitbox(this->m_sprite).dimension;
	}

	ql::vec2 ql::sprite::get_scale() const
	{
		return this->m_sprite.getScale();
	}

	ql::vec2 ql::sprite::get_origin() const
	{
		return this->m_sprite.getOrigin();
	}

	ql::f32 ql::sprite::get_rotation() const
	{
		return this->m_sprite.getRotation();
	}

	ql::hitbox ql::sprite::get_hitbox() const
	{
		return ql::get_sprite_hitbox(this->m_sprite);
	}

	ql::vec2 ql::sprite::get_center() const
	{
		return ql::get_sprite_center(this->m_sprite);
	}

	void ql::sprite::centerize_origin()
	{
		ql::centerize_sprite_origin(this->m_sprite);
	}

	void ql::sprite::centerize()
	{
		this->set_position(this->get_position() - this->get_dimension() / 2);
	}

	void ql::sprite::centerize_x()
	{
		auto y = this->get_position().y;
		auto x = this->get_position().x - this->get_dimension().x / 2;
		this->set_position(ql::vec(x, y));
	}

	void ql::sprite::centerize_y()
	{
		auto y = this->get_position().y - this->get_dimension().y / 2;
		auto x = this->get_position().x;
		this->set_position(ql::vec(x, y));
	}

	void ql::sprite::move(ql::vec2 delta)
	{
		this->m_sprite.move(delta);
	}

	void ql::sprite::move_scaled(ql::vec2 delta)
	{
		this->m_sprite.move(delta / this->get_scale());
	}

	void ql::sprite::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->m_sprite, states);
	}

	ql::sprite::operator sf::Sprite&()
	{
		return this->m_sprite;
	}

	ql::sprite::operator const sf::Sprite&() const
	{
		return this->m_sprite;
	}

	ql::sprite& ql::sprite::operator=(const sf::Sprite& sprite)
	{
		this->m_sprite = sprite;
		return *this;
	}

	ql::transition_overlay::transition_overlay()
	{
		this->overlay.set_color(ql::rgba::black());
		this->set_duration(0.3);
	}

	void ql::transition_overlay::set_color(ql::rgba color)
	{
		this->overlay.set_color(color);
	}

	void ql::transition_overlay::set_slope(ql::f64 slope)
	{
		this->slope = slope;
	}

	void ql::transition_overlay::set_dimension(ql::vec2 dimension)
	{
		this->overlay.set_dimension(dimension);
	}

	void ql::transition_overlay::set_duration(ql::f64 duration)
	{
		this->animation.set_duration(duration);
	}

	void ql::transition_overlay::make_disappear()
	{
		this->animation.reset_and_start();
	}

	void ql::transition_overlay::make_appear()
	{
		this->animation.reset_and_start_reverse();
	}

	void ql::transition_overlay::update(const ql::event_info& event)
	{
		this->animation.update(event.frame_time_f());
		if (this->animation.is_running())
		{
			auto p = this->animation.get_curve_progress(this->slope);
			auto a = ql::u8_cast(255 * p);
			this->overlay.set_multiplied_alpha(a);
		}
	}

	bool ql::transition_overlay::just_finished_disappearing() const
	{
		return this->animation.just_finished_no_reverse();
	}

	bool ql::transition_overlay::just_finished_appearing() const
	{
		return this->animation.just_finished_reverse();
	}

	void ql::transition_overlay::draw(ql::draw_object& draw) const
	{
		draw.draw(this->overlay);
	}

	void ql::render_texture::set_antialiasing(ql::u32 antialiasing)
	{
		this->m_settings.antialiasingLevel = antialiasing;
	}

	void ql::render_texture::resize(ql::vector2i dimension, bool resize_with_window)
	{
		// if (this->m_texture) {
		//	this->m_texture.get_deleter();
		// }
		// this->m_texture = std::make_unique<sf::RenderTexture>();
		// if (this->m_texture) {
		//	this->m_texture->~RenderTexture();
		//	delete this->m_texture;
		// }
		// this->m_texture = new sf::RenderTexture;
		if (this->m_create_size.x < dimension.x || this->m_create_size.y < dimension.y)
		{
			this->m_create_size = dimension;
			this->m_texture.create(dimension.x, dimension.y, this->m_settings);
			this->m_sprite.set_texture(this->m_texture.getTexture());
		}

		sf::IntRect rect{0, 0, dimension.x, dimension.y};
		this->m_sprite.m_sprite.setTextureRect(rect);
		this->m_changed = true;
		this->m_resize_with_window = resize_with_window;
	}

	void ql::render_texture::set_smooth(bool b)
	{
		this->m_smooth = b;
		this->m_texture.setSmooth(b);
	}

	void ql::render_texture::enable_smooth()
	{
		this->set_smooth(true);
	}

	void ql::render_texture::disable_smooth()
	{
		this->set_smooth(false);
	}

	bool ql::render_texture::is_smooth() const
	{
		return this->m_smooth;
	}

	void ql::render_texture::enable_resize_with_window()
	{
		this->m_resize_with_window = true;
	}

	void ql::render_texture::disable_resize_with_window()
	{
		this->m_resize_with_window = false;
	}

	bool ql::render_texture::is_resize_with_window_enabled() const
	{
		return this->m_resize_with_window;
	}

	void ql::render_texture::enable_clear_with_window()
	{
		this->m_clear_with_window = true;
	}

	void ql::render_texture::disable_clear_with_window()
	{
		this->m_clear_with_window = false;
	}

	bool ql::render_texture::is_clear_with_window_enabled() const
	{
		return this->m_clear_with_window;
	}

	void ql::render_texture::set_color(ql::rgba color)
	{
		this->m_sprite.set_color(color);
	}

	void ql::render_texture::set_position(ql::vec2 position)
	{
		this->m_sprite.set_position(position);
	}

	void ql::render_texture::set_scale(ql::vec2 scale)
	{
		this->m_sprite.set_scale(scale);
	}

	void ql::render_texture::set_scale(ql::f32 scale)
	{
		this->m_sprite.set_scale(scale);
	}

	void ql::render_texture::set_origin(ql::vec2 origin)
	{
		this->m_sprite.set_origin(origin);
	}

	void ql::render_texture::set_rotation(ql::f32 rotation)
	{
		this->m_sprite.set_rotation(rotation);
	}

	ql::rgba ql::render_texture::get_color() const
	{
		return this->m_sprite.get_color();
	}

	ql::vec2 ql::render_texture::get_position() const
	{
		return this->m_sprite.get_position();
	}

	ql::vec2 ql::render_texture::get_scale() const
	{
		return this->m_sprite.get_scale();
	}

	ql::vec2 ql::render_texture::get_origin() const
	{
		return this->m_sprite.get_origin();
	}

	ql::f32 ql::render_texture::get_rotation() const
	{
		return this->m_sprite.get_rotation();
	}

	ql::vec2 ql::render_texture::get_dimension() const
	{
		return this->m_texture.getSize();
	}

	ql::vec2 ql::render_texture::get_center() const
	{
		return this->m_sprite.get_position() + this->get_dimension() / 2;
	}

	void ql::render_texture::move(ql::vec2 delta)
	{
		this->m_sprite.move(delta);
	}

	void ql::render_texture::move_scaled(ql::vec2 delta)
	{
		this->m_sprite.move(delta / this->get_scale());
	}

	const ql::sprite& ql::render_texture::get_sprite() const
	{
		if (this->m_changed)
		{
			this->apply();
		}
		return this->m_sprite;
	}

	void ql::render_texture::clear()
	{
		this->m_texture.clear();
	}

	void ql::render_texture::display()
	{
		this->m_texture.display();
	}

	const sf::RenderStates& ql::render_texture::get_render_states() const
	{
		return this->m_states;
	}

	const sf::Texture& ql::render_texture::get_texture() const
	{
		return this->m_texture.getTexture();
	}

	void ql::render_texture::set_shader(const std::string& name)
	{
		this->m_states.shader = &ql::get_shader(name);
	}

	void ql::render_texture::set_shader(sf::Shader& shader)
	{
		this->m_states.shader = &shader;
	}

	void ql::render_texture::unbind_shader()
	{
		this->m_states.shader = nullptr;
	}

	void ql::render_texture::apply() const
	{
		this->m_texture.display();
		this->m_changed = false;
	}

	void ql::pixel_image::set_array_dimension(ql::vector2u dimension)
	{
		this->positions_set = this->array_dimension == dimension;
		this->array_dimension = dimension;
		this->vertices.resize((this->array_dimension.x - 1) * (this->array_dimension.y - 1) * 4);

		this->create_positions();
	}

	void ql::pixel_image::set_pixel_dimension(ql::vec2 dimension)
	{
		this->positions_set = this->pixel_dimension == dimension;
		this->pixel_dimension = dimension;
		this->create_positions();
	}

	void ql::pixel_image::set_position(ql::vec2 position)
	{
		this->positions_set = this->position == position;
		this->position = position;
		this->create_positions();
	}

	void ql::pixel_image::create_positions()
	{
		if (!this->positions_set)
		{
			this->positions_set = true;

			if (this->vertices.size())
			{
				for (ql::u32 y = 0u; y < this->array_dimension.y - 1; ++y)
				{
					for (ql::u32 x = 0u; x < this->array_dimension.x - 1; ++x)
					{
						auto index = (y * (this->array_dimension.x - 1) + x);

						this->vertices[index * 4 + 0].position = (this->position + this->pixel_dimension * ql::vec2(x, y));
						this->vertices[index * 4 + 1].position = (this->position + this->pixel_dimension * ql::vec2(x, y + 1.0f));
						this->vertices[index * 4 + 2].position = (this->position + this->pixel_dimension * ql::vec2(x + 1.0f, y + 1.0f));
						this->vertices[index * 4 + 3].position = (this->position + this->pixel_dimension * ql::vec2(x + 1.0f, y));
					}
				}
			}
		}
	}

	void ql::pixel_image::set(ql::size x, ql::size y, ql::rgba color)
	{
		auto index = (y * this->array_dimension.y + x);

		auto above_index = ((ql::signed_cast(y) - 1) * (ql::signed_cast(this->array_dimension.x) - 1) + ql::signed_cast(x)) * 4;
		if (above_index - 2 >= 0 && above_index - 2 < ql::signed_cast(this->vertices.size()))
		{
			this->vertices[above_index - 2].color = color;
		}
		if (above_index + 1 >= 0 && above_index + 1 < ql::signed_cast(this->vertices.size()))
		{
			this->vertices[above_index + 1].color = color;
		}
		auto below_index = ((ql::signed_cast(y)) * (ql::signed_cast(this->array_dimension.x) - 1) + ql::signed_cast(x)) * 4;
		if (below_index >= 0 && below_index < ql::signed_cast(this->vertices.size()))
		{
			this->vertices[below_index].color = color;
		}
		if (below_index - 1 >= 0 && below_index - 1 < ql::signed_cast(this->vertices.size()))
		{
			this->vertices[below_index - 1].color = color;
		}
	}

	void ql::pixel_image::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->vertices.draw(window, states);
	}

	ql::endl_type endl;

	void ql::tile_map::set_texture_ptr(const sf::Texture& texture, ql::vector2u texture_tile_dimension)
	{
		this->texture_ptr = &texture;
		this->texture_tile_dimension = texture_tile_dimension;
		this->position_tile_dimension = this->texture_tile_dimension;
		this->texture_ptr_set = true;
	}

	void ql::tile_map::set_texture_ptr(const sf::Texture& texture, ql::u32 texture_tile_width)
	{
		this->set_texture_ptr(texture, ql::vec(texture_tile_width, texture_tile_width));
	}

	void ql::tile_map::set_position(ql::vec2 position)
	{
		this->position = position;
	}

	void ql::tile_map::create(const std::vector<std::pair<ql::u32, ql::u32>>& indices, ql::size width, ql::rgba color)
	{
		if (!this->texture_ptr_set)
		{
			throw ql::exception("tile_map::create: texture_ptr not set");
			return;
		}

		this->chunks.clear();
		this->color = color;
		auto chunk_width = (width - 1) / this->max_chunk_size.x + 1;
		auto chunk_height = (indices.size() / width - 1) / this->max_chunk_size.y + 1;
		auto chunk_dim = chunk_width * chunk_height;

		this->chunk_width_count = chunk_width;
		this->chunks.resize(chunk_dim);
		for (auto& chunk : this->chunks)
		{
			chunk.setPrimitiveType(sf::Quads);
			chunk.resize(this->max_chunk_size.y * this->max_chunk_size.x * 4);
		}

		auto texture_row_tile_count = texture_ptr->getSize().x / this->texture_tile_dimension.x;

		if (color == ql::rgba::white())
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto [y, x] = ql::div_mod(i, width);
				auto tile = indices[i];
				auto tile_x = (tile.first % texture_row_tile_count);
				auto tile_y = (tile.first / texture_row_tile_count);

				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;

				auto& chunk = this->chunks[chunk_x + chunk_y * chunk_width];

				auto chunk_index =
						((i % width) % this->max_chunk_size.x) + ((i / width) % this->max_chunk_size.y) * this->max_chunk_size.x;

				chunk[chunk_index * 4 + 0].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 1].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 2].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 3].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

				auto tex_0 = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_1 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_2 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				auto tex_3 = ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);

				if (tile.second == 0b000)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_0;
					chunk[chunk_index * 4 + 1].texCoords = tex_1;
					chunk[chunk_index * 4 + 2].texCoords = tex_2;
					chunk[chunk_index * 4 + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b001)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_1;
					chunk[chunk_index * 4 + 1].texCoords = tex_0;
					chunk[chunk_index * 4 + 2].texCoords = tex_3;
					chunk[chunk_index * 4 + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b010)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_3;
					chunk[chunk_index * 4 + 1].texCoords = tex_2;
					chunk[chunk_index * 4 + 2].texCoords = tex_1;
					chunk[chunk_index * 4 + 3].texCoords = tex_0;
				}
				else if (tile.second == 0b011)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_2;
					chunk[chunk_index * 4 + 1].texCoords = tex_3;
					chunk[chunk_index * 4 + 2].texCoords = tex_0;
					chunk[chunk_index * 4 + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b100)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_3;
					chunk[chunk_index * 4 + 1].texCoords = tex_0;
					chunk[chunk_index * 4 + 2].texCoords = tex_1;
					chunk[chunk_index * 4 + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b101)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_2;
					chunk[chunk_index * 4 + 1].texCoords = tex_1;
					chunk[chunk_index * 4 + 2].texCoords = tex_0;
					chunk[chunk_index * 4 + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b110)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_0;
					chunk[chunk_index * 4 + 1].texCoords = tex_3;
					chunk[chunk_index * 4 + 2].texCoords = tex_2;
					chunk[chunk_index * 4 + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b111)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_1;
					chunk[chunk_index * 4 + 1].texCoords = tex_2;
					chunk[chunk_index * 4 + 2].texCoords = tex_3;
					chunk[chunk_index * 4 + 3].texCoords = tex_0;
				}
			}
		}
		else
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto [y, x] = ql::div_mod(i, width);
				auto tile = indices[i];
				auto tile_x = (tile.first % texture_row_tile_count);
				auto tile_y = (tile.first / texture_row_tile_count);

				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;

				auto& chunk = this->chunks[chunk_x + chunk_y * chunk_width];

				auto chunk_index =
						((i % width) % this->max_chunk_size.x) + ((i / width) % this->max_chunk_size.y) * this->max_chunk_size.x;

				chunk[chunk_index * 4 + 0].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 1].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 2].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 3].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

				chunk[chunk_index * 4 + 0].color = color;
				chunk[chunk_index * 4 + 1].color = color;
				chunk[chunk_index * 4 + 2].color = color;
				chunk[chunk_index * 4 + 3].color = color;

				auto tex_0 = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_1 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_2 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				auto tex_3 = ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);

				if (tile.second == 0b000)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_0;
					chunk[chunk_index * 4 + 1].texCoords = tex_1;
					chunk[chunk_index * 4 + 2].texCoords = tex_2;
					chunk[chunk_index * 4 + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b001)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_1;
					chunk[chunk_index * 4 + 1].texCoords = tex_0;
					chunk[chunk_index * 4 + 2].texCoords = tex_3;
					chunk[chunk_index * 4 + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b010)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_3;
					chunk[chunk_index * 4 + 1].texCoords = tex_2;
					chunk[chunk_index * 4 + 2].texCoords = tex_1;
					chunk[chunk_index * 4 + 3].texCoords = tex_0;
				}
				else if (tile.second == 0b011)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_2;
					chunk[chunk_index * 4 + 1].texCoords = tex_3;
					chunk[chunk_index * 4 + 2].texCoords = tex_0;
					chunk[chunk_index * 4 + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b100)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_3;
					chunk[chunk_index * 4 + 1].texCoords = tex_0;
					chunk[chunk_index * 4 + 2].texCoords = tex_1;
					chunk[chunk_index * 4 + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b101)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_2;
					chunk[chunk_index * 4 + 1].texCoords = tex_1;
					chunk[chunk_index * 4 + 2].texCoords = tex_0;
					chunk[chunk_index * 4 + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b110)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_0;
					chunk[chunk_index * 4 + 1].texCoords = tex_3;
					chunk[chunk_index * 4 + 2].texCoords = tex_2;
					chunk[chunk_index * 4 + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b111)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_1;
					chunk[chunk_index * 4 + 1].texCoords = tex_2;
					chunk[chunk_index * 4 + 2].texCoords = tex_3;
					chunk[chunk_index * 4 + 3].texCoords = tex_0;
				}
			}
		}
	}

	void ql::tile_map::create(const std::vector<std::pair<ql::u32, ql::u32>>& indices, ql::size width)
	{
		this->create(indices, width, ql::rgba::white());
	}

	void ql::tile_map::create(const std::vector<std::pair<ql::u32, ql::f32>>& indices, ql::size width, ql::rgba color)
	{
		if (!this->texture_ptr_set)
		{
			throw ql::exception("tile_map::create: texture_ptr not set");
			return;
		}

		this->chunks.clear();
		this->color = color;
		auto chunk_width = (width - 1) / this->max_chunk_size.x + 1;
		auto chunk_height = (indices.size() / width - 1) / this->max_chunk_size.y + 1;
		auto chunk_dim = chunk_width * chunk_height;

		this->chunk_width_count = chunk_width;
		this->chunks.resize(chunk_dim);
		for (auto& chunk : this->chunks)
		{
			chunk.setPrimitiveType(sf::Quads);
			chunk.resize(this->max_chunk_size.y * this->max_chunk_size.x * 4);
		}

		auto texture_row_tile_count = texture_ptr->getSize().x / this->texture_tile_dimension.x;

		if (color == ql::rgba::white())
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto [y, x] = ql::div_mod(i, width);
				auto tile = indices[i];
				auto tile_x = (tile.first % texture_row_tile_count);
				auto tile_y = (tile.first / texture_row_tile_count);

				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;

				auto& chunk = this->chunks[chunk_x + chunk_y * chunk_width];

				auto chunk_index =
						((i % width) % this->max_chunk_size.x) + ((i / width) % this->max_chunk_size.y) * this->max_chunk_size.x;

				auto middle = ql::vec2(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y) +
											this->position_tile_dimension / 2;

				auto diagonal = std::sqrt(std::pow(this->position_tile_dimension.x, 2) + std::pow(this->position_tile_dimension.y, 2));
				auto angle = tile.second + (ql::pi * 1.25);
				auto pos_1 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 0.0)), std::sin(angle + (ql::pi * 0.0))) * diagonal / 2;
				auto pos_2 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 0.5)), std::sin(angle + (ql::pi * 0.5))) * diagonal / 2;
				auto pos_3 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 1.0)), std::sin(angle + (ql::pi * 1.0))) * diagonal / 2;
				auto pos_4 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 1.5)), std::sin(angle + (ql::pi * 1.5))) * diagonal / 2;

				chunk[chunk_index * 4 + 0].position = pos_1;
				chunk[chunk_index * 4 + 1].position = pos_2;
				chunk[chunk_index * 4 + 2].position = pos_3;
				chunk[chunk_index * 4 + 3].position = pos_4;

				auto tex_0 = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_1 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_2 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				auto tex_3 = ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);

				chunk[chunk_index * 4 + 0].texCoords = tex_0;
				chunk[chunk_index * 4 + 1].texCoords = tex_1;
				chunk[chunk_index * 4 + 2].texCoords = tex_2;
				chunk[chunk_index * 4 + 3].texCoords = tex_3;
			}
		}
		else
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto [y, x] = ql::div_mod(i, width);
				auto tile = indices[i];
				auto tile_x = (tile.first % texture_row_tile_count);
				auto tile_y = (tile.first / texture_row_tile_count);

				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;

				auto& chunk = this->chunks[chunk_x + chunk_y * chunk_width];

				auto chunk_index =
						((i % width) % this->max_chunk_size.x) + ((i / width) % this->max_chunk_size.y) * this->max_chunk_size.x;

				auto middle = ql::vec2(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y) +
											this->position_tile_dimension / 2;

				auto diagonal = std::sqrt(std::pow(this->position_tile_dimension.x, 2) + std::pow(this->position_tile_dimension.y, 2));
				auto angle = tile.second + (ql::pi * 1.25);
				auto pos_1 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 0.0)), std::sin(angle + (ql::pi * 0.0))) * diagonal / 2;
				auto pos_2 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 0.5)), std::sin(angle + (ql::pi * 0.5))) * diagonal / 2;
				auto pos_3 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 1.0)), std::sin(angle + (ql::pi * 1.0))) * diagonal / 2;
				auto pos_4 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 1.5)), std::sin(angle + (ql::pi * 1.5))) * diagonal / 2;

				chunk[chunk_index * 4 + 0].position = pos_1;
				chunk[chunk_index * 4 + 1].position = pos_2;
				chunk[chunk_index * 4 + 2].position = pos_3;
				chunk[chunk_index * 4 + 3].position = pos_4;

				chunk[chunk_index * 4 + 0].color = color;
				chunk[chunk_index * 4 + 1].color = color;
				chunk[chunk_index * 4 + 2].color = color;
				chunk[chunk_index * 4 + 3].color = color;

				auto tex_0 = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_1 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_2 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				auto tex_3 = ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);

				if (tile.second == 0b000)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_0;
					chunk[chunk_index * 4 + 1].texCoords = tex_1;
					chunk[chunk_index * 4 + 2].texCoords = tex_2;
					chunk[chunk_index * 4 + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b001)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_1;
					chunk[chunk_index * 4 + 1].texCoords = tex_0;
					chunk[chunk_index * 4 + 2].texCoords = tex_3;
					chunk[chunk_index * 4 + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b010)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_3;
					chunk[chunk_index * 4 + 1].texCoords = tex_2;
					chunk[chunk_index * 4 + 2].texCoords = tex_1;
					chunk[chunk_index * 4 + 3].texCoords = tex_0;
				}
				else if (tile.second == 0b011)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_2;
					chunk[chunk_index * 4 + 1].texCoords = tex_3;
					chunk[chunk_index * 4 + 2].texCoords = tex_0;
					chunk[chunk_index * 4 + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b100)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_3;
					chunk[chunk_index * 4 + 1].texCoords = tex_0;
					chunk[chunk_index * 4 + 2].texCoords = tex_1;
					chunk[chunk_index * 4 + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b101)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_2;
					chunk[chunk_index * 4 + 1].texCoords = tex_1;
					chunk[chunk_index * 4 + 2].texCoords = tex_0;
					chunk[chunk_index * 4 + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b110)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_0;
					chunk[chunk_index * 4 + 1].texCoords = tex_3;
					chunk[chunk_index * 4 + 2].texCoords = tex_2;
					chunk[chunk_index * 4 + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b111)
				{
					chunk[chunk_index * 4 + 0].texCoords = tex_1;
					chunk[chunk_index * 4 + 1].texCoords = tex_2;
					chunk[chunk_index * 4 + 2].texCoords = tex_3;
					chunk[chunk_index * 4 + 3].texCoords = tex_0;
				}
			}
		}
	}

	void ql::tile_map::create(const std::vector<std::pair<ql::u32, ql::f32>>& indices, ql::size width)
	{
		this->create(indices, width, ql::rgba::white());
	}

	void ql::tile_map::create(const std::vector<ql::u32>& indices, ql::size width, ql::rgba color)
	{
		if (!this->texture_ptr_set)
		{
			throw ql::exception("tile_map::create: texture_ptr not set");
			return;
		}

		this->chunks.clear();
		this->color = color;

		auto chunk_width = (width - 1) / this->max_chunk_size.x + 1;
		auto chunk_height = (indices.size() / width - 1) / this->max_chunk_size.y + 1;
		auto chunk_dim = chunk_width * chunk_height;
		this->chunk_width_count = chunk_width;
		this->chunks.resize(chunk_dim);
		for (auto& chunk : this->chunks)
		{
			chunk.setPrimitiveType(sf::Quads);
			chunk.resize(this->max_chunk_size.y * this->max_chunk_size.x * 4);
		}

		auto texture_row_tile_count = texture_ptr->getSize().x / this->texture_tile_dimension.x;

		if (color == ql::rgba::white())
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto [y, x] = ql::div_mod(i, width);
				auto index = indices[i];
				auto tile_x = (index % texture_row_tile_count);
				auto tile_y = (index / texture_row_tile_count);

				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;

				auto& chunk = this->chunks[chunk_x + chunk_y * chunk_width];

				auto chunk_index =
						((i % width) % this->max_chunk_size.x) + ((i / width) % this->max_chunk_size.y) * this->max_chunk_size.x;

				chunk[chunk_index * 4 + 0].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 1].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 2].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 3].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

				chunk[chunk_index * 4 + 0].texCoords =
						ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				chunk[chunk_index * 4 + 1].texCoords =
						ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				chunk[chunk_index * 4 + 2].texCoords =
						ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				chunk[chunk_index * 4 + 3].texCoords =
						ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
			}
		}
		else
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto [y, x] = ql::div_mod(i, width);
				auto index = indices[i];
				auto tile_x = (index % texture_row_tile_count);
				auto tile_y = (index / texture_row_tile_count);

				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;

				auto& chunk = this->chunks[chunk_x + chunk_y * chunk_width];

				auto chunk_index =
						((i % width) % this->max_chunk_size.x) + ((i / width) % this->max_chunk_size.y) * this->max_chunk_size.x;

				chunk[chunk_index * 4 + 0].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 1].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 2].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
				chunk[chunk_index * 4 + 3].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

				chunk[chunk_index * 4 + 0].color = color;
				chunk[chunk_index * 4 + 1].color = color;
				chunk[chunk_index * 4 + 2].color = color;
				chunk[chunk_index * 4 + 3].color = color;

				chunk[chunk_index * 4 + 0].texCoords =
						ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				chunk[chunk_index * 4 + 1].texCoords =
						ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				chunk[chunk_index * 4 + 2].texCoords =
						ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				chunk[chunk_index * 4 + 3].texCoords =
						ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
			}
		}
	}

	void ql::tile_map::create(const std::vector<ql::u32>& indices, ql::size width)
	{
		this->create(indices, width, ql::rgba::white());
	}

	void ql::tile_map::create_skip_empty(
			const std::vector<std::pair<ql::u32, ql::u32>>& indices,
			ql::size width,
			ql::rgba color,
			ql::u32 skip_index
	)
	{
		if (!this->texture_ptr_set)
		{
			throw ql::exception("tile_map::create: texture_ptr not set");
			return;
		}

		this->chunks.clear();
		this->color = color;
		auto texture_row_tile_count = texture_ptr->getSize().x / this->texture_tile_dimension.x;

		auto chunk_width = (width - 1) / this->max_chunk_size.x + 1;
		auto chunk_height = (indices.size() / width - 1) / this->max_chunk_size.y + 1;
		auto chunk_dim = chunk_width * chunk_height;

		this->chunk_width_count = chunk_width;
		this->chunks.resize(chunk_dim);
		for (auto& chunk : this->chunks)
		{
			chunk.setPrimitiveType(sf::Quads);
		}

		if (color == ql::rgba::white())
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto tile = indices[i];
				if (tile.first == skip_index)
				{
					continue;
				}

				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;
				auto chunk_index = chunk_x + chunk_y * chunk_width;

				auto& chunk = this->chunks[chunk_index];

				auto ctr = chunk.getVertexCount();
				chunk.resize(ctr + 4);

				auto [y, x] = ql::div_mod(i, width);
				auto tile_x = (tile.first % texture_row_tile_count);
				auto tile_y = (tile.first / texture_row_tile_count);

				auto pos_0 = this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				auto pos_1 =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				auto pos_2 =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
				auto pos_3 =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

				chunk[ctr + 0].position = pos_0;
				chunk[ctr + 1].position = pos_1;
				chunk[ctr + 2].position = pos_2;
				chunk[ctr + 3].position = pos_3;

				auto tex_0 = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_1 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_2 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				auto tex_3 = ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);

				if (tile.second == 0b000)
				{
					chunk[ctr + 0].texCoords = tex_0;
					chunk[ctr + 1].texCoords = tex_1;
					chunk[ctr + 2].texCoords = tex_2;
					chunk[ctr + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b001)
				{
					chunk[ctr + 0].texCoords = tex_1;
					chunk[ctr + 1].texCoords = tex_0;
					chunk[ctr + 2].texCoords = tex_3;
					chunk[ctr + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b010)
				{
					chunk[ctr + 0].texCoords = tex_3;
					chunk[ctr + 1].texCoords = tex_2;
					chunk[ctr + 2].texCoords = tex_1;
					chunk[ctr + 3].texCoords = tex_0;
				}
				else if (tile.second == 0b011)
				{
					chunk[ctr + 0].texCoords = tex_2;
					chunk[ctr + 1].texCoords = tex_3;
					chunk[ctr + 2].texCoords = tex_0;
					chunk[ctr + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b100)
				{
					chunk[ctr + 0].texCoords = tex_3;
					chunk[ctr + 1].texCoords = tex_0;
					chunk[ctr + 2].texCoords = tex_1;
					chunk[ctr + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b101)
				{
					chunk[ctr + 0].texCoords = tex_2;
					chunk[ctr + 1].texCoords = tex_1;
					chunk[ctr + 2].texCoords = tex_0;
					chunk[ctr + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b110)
				{
					chunk[ctr + 0].texCoords = tex_0;
					chunk[ctr + 1].texCoords = tex_3;
					chunk[ctr + 2].texCoords = tex_2;
					chunk[ctr + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b111)
				{
					chunk[ctr + 0].texCoords = tex_1;
					chunk[ctr + 1].texCoords = tex_2;
					chunk[ctr + 2].texCoords = tex_3;
					chunk[ctr + 3].texCoords = tex_0;
				}
			}
		}
		else
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto tile = indices[i];
				if (tile.first == skip_index)
				{
					continue;
				}
				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;
				auto chunk_index = chunk_x + chunk_y * chunk_width;

				auto& chunk = this->chunks[chunk_index];
				auto ctr = chunk.getVertexCount();
				chunk.resize(ctr + 4);

				auto [y, x] = ql::div_mod(i, width);
				auto tile_x = (tile.first % texture_row_tile_count);
				auto tile_y = (tile.first / texture_row_tile_count);

				auto pos_0 = this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				auto pos_1 =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				auto pos_2 =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
				auto pos_3 =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

				chunk[ctr + 0].position = pos_0;
				chunk[ctr + 1].position = pos_1;
				chunk[ctr + 2].position = pos_2;
				chunk[ctr + 3].position = pos_3;

				chunk[ctr + 0].color = color;
				chunk[ctr + 1].color = color;
				chunk[ctr + 2].color = color;
				chunk[ctr + 3].color = color;

				auto tex_0 = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_1 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_2 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				auto tex_3 = ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);

				if (tile.second == 0b000)
				{
					chunk[ctr + 0].texCoords = tex_0;
					chunk[ctr + 1].texCoords = tex_1;
					chunk[ctr + 2].texCoords = tex_2;
					chunk[ctr + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b001)
				{
					chunk[ctr + 0].texCoords = tex_1;
					chunk[ctr + 1].texCoords = tex_0;
					chunk[ctr + 2].texCoords = tex_3;
					chunk[ctr + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b010)
				{
					chunk[ctr + 0].texCoords = tex_3;
					chunk[ctr + 1].texCoords = tex_2;
					chunk[ctr + 2].texCoords = tex_1;
					chunk[ctr + 3].texCoords = tex_0;
				}
				else if (tile.second == 0b011)
				{
					chunk[ctr + 0].texCoords = tex_2;
					chunk[ctr + 1].texCoords = tex_3;
					chunk[ctr + 2].texCoords = tex_0;
					chunk[ctr + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b100)
				{
					chunk[ctr + 0].texCoords = tex_3;
					chunk[ctr + 1].texCoords = tex_0;
					chunk[ctr + 2].texCoords = tex_1;
					chunk[ctr + 3].texCoords = tex_2;
				}
				else if (tile.second == 0b101)
				{
					chunk[ctr + 0].texCoords = tex_2;
					chunk[ctr + 1].texCoords = tex_1;
					chunk[ctr + 2].texCoords = tex_0;
					chunk[ctr + 3].texCoords = tex_3;
				}
				else if (tile.second == 0b110)
				{
					chunk[ctr + 0].texCoords = tex_0;
					chunk[ctr + 1].texCoords = tex_3;
					chunk[ctr + 2].texCoords = tex_2;
					chunk[ctr + 3].texCoords = tex_1;
				}
				else if (tile.second == 0b111)
				{
					chunk[ctr + 0].texCoords = tex_1;
					chunk[ctr + 1].texCoords = tex_2;
					chunk[ctr + 2].texCoords = tex_3;
					chunk[ctr + 3].texCoords = tex_0;
				}
			}
		}
	}

	void
	ql::tile_map::create_skip_empty(const std::vector<std::pair<ql::u32, ql::u32>>& indices, ql::size width, ql::u32 skip_index)
	{
		this->create_skip_empty(indices, width, ql::rgba::white(), skip_index);
	}

	void ql::tile_map::create_skip_empty(
			const std::vector<std::pair<ql::u32, ql::f32>>& indices,
			ql::size width,
			ql::rgba color,
			ql::u32 skip_index
	)
	{
		if (!this->texture_ptr_set)
		{
			throw ql::exception("tile_map::create: texture_ptr not set");
			return;
		}

		this->chunks.clear();
		this->color = color;
		auto texture_row_tile_count = texture_ptr->getSize().x / this->texture_tile_dimension.x;

		auto chunk_width = (width - 1) / this->max_chunk_size.x + 1;
		auto chunk_height = (indices.size() / width - 1) / this->max_chunk_size.y + 1;
		auto chunk_dim = chunk_width * chunk_height;

		this->chunk_width_count = chunk_width;
		this->chunks.resize(chunk_dim);
		for (auto& chunk : this->chunks)
		{
			chunk.setPrimitiveType(sf::Quads);
		}

		auto diagonal = std::sqrt(std::pow(this->texture_tile_dimension.x, 2) + std::pow(this->texture_tile_dimension.y, 2));

		if (color == ql::rgba::white())
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto tile = indices[i];
				if (tile.first == skip_index)
				{
					continue;
				}

				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;
				auto chunk_index = chunk_x + chunk_y * chunk_width;

				auto& chunk = this->chunks[chunk_index];

				auto ctr = chunk.getVertexCount();
				chunk.resize(ctr + 4);

				auto [y, x] = ql::div_mod(i, width);
				auto tile_x = (tile.first % texture_row_tile_count);
				auto tile_y = (tile.first / texture_row_tile_count);

				auto middle = ql::vec2(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y) +
											this->position_tile_dimension / 2;

				auto angle = ((tile.second / 180) * ql::pi) + (ql::pi * 1.25);
				auto pos_1 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 0.0)), std::sin(angle + (ql::pi * 0.0))) * diagonal / 2;
				auto pos_2 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 0.5)), std::sin(angle + (ql::pi * 0.5))) * diagonal / 2;
				auto pos_3 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 1.0)), std::sin(angle + (ql::pi * 1.0))) * diagonal / 2;
				auto pos_4 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 1.5)), std::sin(angle + (ql::pi * 1.5))) * diagonal / 2;

				chunk[ctr + 0].position = pos_1;
				chunk[ctr + 1].position = pos_2;
				chunk[ctr + 2].position = pos_3;
				chunk[ctr + 3].position = pos_4;

				auto tex_0 = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_1 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_2 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				auto tex_3 = ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);

				chunk[ctr + 0].texCoords = tex_0;
				chunk[ctr + 1].texCoords = tex_1;
				chunk[ctr + 2].texCoords = tex_2;
				chunk[ctr + 3].texCoords = tex_3;
			}
		}
		else
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto tile = indices[i];
				if (tile.first == skip_index)
				{
					continue;
				}
				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;
				auto chunk_index = chunk_x + chunk_y * chunk_width;

				auto& chunk = this->chunks[chunk_index];
				auto ctr = chunk.getVertexCount();
				chunk.resize(ctr + 4);

				auto [y, x] = ql::div_mod(i, width);
				auto tile_x = (tile.first % texture_row_tile_count);
				auto tile_y = (tile.first / texture_row_tile_count);

				auto middle = ql::vec2(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y) +
											this->position_tile_dimension / 2;

				auto angle = tile.second + (ql::pi * 1.25);
				auto pos_1 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 0.0)), std::sin(angle + (ql::pi * 0.0))) * diagonal / 2;
				auto pos_2 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 0.5)), std::sin(angle + (ql::pi * 0.5))) * diagonal / 2;
				auto pos_3 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 1.0)), std::sin(angle + (ql::pi * 1.0))) * diagonal / 2;
				auto pos_4 =
						this->position + middle + ql::vec2(std::cos(angle + (ql::pi * 1.5)), std::sin(angle + (ql::pi * 1.5))) * diagonal / 2;

				chunk[ctr + 0].position = pos_1;
				chunk[ctr + 1].position = pos_2;
				chunk[ctr + 2].position = pos_3;
				chunk[ctr + 3].position = pos_4;

				chunk[ctr + 0].color = color;
				chunk[ctr + 1].color = color;
				chunk[ctr + 2].color = color;
				chunk[ctr + 3].color = color;

				auto tex_0 = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_1 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				auto tex_2 = ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				auto tex_3 = ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);

				chunk[ctr + 0].texCoords = tex_0;
				chunk[ctr + 1].texCoords = tex_1;
				chunk[ctr + 2].texCoords = tex_2;
				chunk[ctr + 3].texCoords = tex_3;
			}
		}
	}

	void
	ql::tile_map::create_skip_empty(const std::vector<std::pair<ql::u32, ql::f32>>& indices, ql::size width, ql::u32 skip_index)
	{
		this->create_skip_empty(indices, width, ql::rgba::white(), skip_index);
	}

	void ql::tile_map::create_skip_empty(const std::vector<ql::u32>& indices, ql::size width, ql::rgba color, ql::u32 skip_index)
	{
		if (!this->texture_ptr_set)
		{
			throw ql::exception("tile_map::create: texture_ptr not set");
			return;
		}

		this->chunks.clear();
		this->color = color;

		auto chunk_width = (width - 1) / this->max_chunk_size.x + 1;
		auto chunk_height = (indices.size() / width - 1) / this->max_chunk_size.y + 1;
		auto chunk_dim = chunk_width * chunk_height;

		this->chunk_width_count = chunk_width;
		this->chunks.resize(chunk_dim);
		for (auto& chunk : this->chunks)
		{
			chunk.setPrimitiveType(sf::Quads);
		}

		auto texture_row_tile_count = texture_ptr->getSize().x / this->texture_tile_dimension.x;

		ql::u32 ctr = 0;
		if (color == ql::rgba::white())
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto index = indices[i];
				if (index == skip_index)
				{
					continue;
				}
				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;
				auto chunk_index = chunk_x + chunk_y * chunk_width;

				auto& chunk = this->chunks[chunk_index];
				auto ctr = chunk.getVertexCount();
				chunk.resize(ctr + 4);

				auto [y, x] = ql::div_mod(i, width);

				auto tile_x = (index % texture_row_tile_count);
				auto tile_y = (index / texture_row_tile_count);

				chunk[ctr + 0].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[ctr + 1].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[ctr + 2].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
				chunk[ctr + 3].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

				chunk[ctr + 0].texCoords = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				chunk[ctr + 1].texCoords =
						ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				chunk[ctr + 2].texCoords =
						ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				chunk[ctr + 3].texCoords =
						ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
			}
		}
		else
		{
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto index = indices[i];
				if (index == skip_index)
				{
					continue;
				}

				auto chunk_x = (i % width) / this->max_chunk_size.x;
				auto chunk_y = (i / width) / this->max_chunk_size.y;
				auto chunk_index = chunk_x + chunk_y * chunk_width;

				auto& chunk = this->chunks[chunk_index];
				auto ctr = chunk.getVertexCount();
				chunk.resize(ctr + 4);

				auto [y, x] = ql::div_mod(i, width);
				auto tile_x = (index % texture_row_tile_count);
				auto tile_y = (index / texture_row_tile_count);

				chunk[ctr + 0].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[ctr + 1].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
				chunk[ctr + 2].position =
						this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
				chunk[ctr + 3].position =
						this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

				chunk[ctr + 0].color = color;
				chunk[ctr + 1].color = color;
				chunk[ctr + 2].color = color;
				chunk[ctr + 3].color = color;

				chunk[ctr + 0].texCoords = ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				chunk[ctr + 1].texCoords =
						ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
				chunk[ctr + 2].texCoords =
						ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				chunk[ctr + 3].texCoords =
						ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
			}
		}
	}

	void ql::tile_map::create_skip_empty(const std::vector<ql::u32>& indices, ql::size width, ql::u32 skip_index)
	{
		this->create_skip_empty(indices, width, ql::rgba::white(), skip_index);
	}

	void ql::tile_map::set_color(ql::rgba color)
	{
		this->color = color;
		for (auto& v : this->chunks)
		{
			for (ql::u32 i = 0u; i < v.getVertexCount(); ++i)
			{
				v[i].color = color;
			}
		}
	}

	void ql::tile_map::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		states.texture = this->texture_ptr;

		for (ql::u32 i = 0u; i < this->chunks.size(); ++i)
		{
			auto x = i % this->chunk_width_count;
			auto y = i / this->chunk_width_count;

			auto rx = ql::f32_cast(x * this->max_chunk_size.x * this->texture_tile_dimension.x);
			auto ry = ql::f32_cast(y * this->max_chunk_size.y * this->texture_tile_dimension.y);
			auto rw = ql::f32_cast(this->max_chunk_size.x * this->texture_tile_dimension.x);
			auto rh = ql::f32_cast(this->max_chunk_size.y * this->texture_tile_dimension.y);

			auto rect = states.transform.transformRect(sf::FloatRect(rx, ry, rw, rh));
			auto fov = sf::FloatRect(0.f, 0.f, ql::f32_cast(window.getSize().x), ql::f32_cast(window.getSize().y));

			if (rect.intersects(fov))
			{
				window.draw(this->chunks[i], states);
			}
		}
	}

	ql::size ql::tile_map::size() const
	{
		ql::size count = 0u;
		for (auto& i : this->chunks)
		{
			count += i.getVertexCount() / 4;
		}
		return count;
	}

	ql::size ql::tile_map::chunk_count() const
	{
		return this->chunks.size();
	}

	void ql::tile_map::set_chunk_dimension(ql::u32 x, ql::u32 y)
	{
		this->max_chunk_size = ql::vector2u(x, y);
	}

	void ql::tile_map::clear()
	{
		this->chunks.clear();
	}

	void ql::small_tile_map::set_texture(const sf::Texture& texture, ql::u32 texture_tile_width)
	{
		this->texture_ptr = &texture;
		this->texture_tile_dimension = ql::vec(texture_tile_width, texture_tile_width);
	}

	void ql::small_tile_map::set_position(ql::vec2 position)
	{
		this->position = position;
	}

	void ql::small_tile_map::set_scale(ql::vec2 scale)
	{
		this->scale = scale;
	}

	void ql::small_tile_map::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		if (this->vertices.size())
		{
			states.transform.translate(this->position);
			states.texture = this->texture_ptr;
			this->vertices.draw(window, states);
		}
	}

	void ql::vgraph::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		ql::detail::graph = *this;
		ql::detail::graph.draw(window, states);
	}

	ql::vgraph::data_point_info& ql::vgraph::data_point_info::operator=(const ql::vgraph::data_point_info& other)
	{
		this->data = other.data;
		this->color = other.color;
		this->thickness = other.thickness;
		this->circle = other.circle;
		this->text = other.text;
		return *this;
	}

	ql::vgraph::data_point_info ql::vgraph::data_point_info::operator*(ql::f64 n) const
	{
		auto copy = *this;
		copy.color *= n;
		copy.thickness *= n;
		copy.data *= n;
		return copy;
	}

	ql::vgraph::data_point_info ql::vgraph::data_point_info::operator*(ql::vgraph::data_point_info other) const
	{
		auto copy = *this;
		copy.color *= other.color;
		copy.thickness *= other.thickness;
		copy.data *= other.data;

		return copy;
	}

	ql::vgraph::data_point_info ql::vgraph::data_point_info::operator-(ql::vgraph::data_point_info other) const
	{
		auto copy = *this;
		copy.color -= other.color;
		copy.thickness -= other.thickness;
		copy.data -= other.data;
		return copy;
	}

	ql::vgraph::data_point_info ql::vgraph::data_point_info::operator+(ql::vgraph::data_point_info other) const
	{
		auto copy = *this;
		copy.color += other.color;
		copy.thickness += other.thickness;
		copy.data += other.data;
		return copy;
	}

	bool ql::vgraph::data_point_info::operator<(ql::vgraph::data_point_info other) const
	{
		return this->data < other.data;
	}

	bool ql::vgraph::data_point_info::operator>(ql::vgraph::data_point_info other) const
	{
		return this->data > other.data;
	}

	ql::vgraph::data_point& ql::vgraph::data_point::operator=(const ql::vgraph::data_point& other)
	{
		this->data = other.data;
		this->color = other.color;
		this->thickness = other.thickness;
		return *this;
	}

	ql::vgraph::data_point ql::vgraph::data_point::operator*(ql::f64 n) const
	{
		auto copy = *this;
		copy.color *= n;
		copy.thickness *= n;
		copy.data *= n;
		return copy;
	}

	ql::vgraph::data_point ql::vgraph::data_point::operator*(ql::vgraph::data_point other) const
	{
		auto copy = *this;
		copy.color *= other.color;
		copy.thickness *= other.thickness;
		copy.data *= other.data;
		return copy;
	}

	ql::vgraph::data_point ql::vgraph::data_point::operator-(ql::vgraph::data_point other) const
	{
		auto copy = *this;
		copy.color -= other.color;
		copy.thickness -= other.thickness;
		copy.data -= other.data;
		return copy;
	}

	ql::vgraph::data_point ql::vgraph::data_point::operator+(ql::vgraph::data_point other) const
	{
		auto copy = *this;
		copy.color += other.color;
		copy.thickness += other.thickness;
		copy.data += other.data;
		return copy;
	}

	bool ql::vgraph::data_point::operator<(ql::vgraph::data_point other) const
	{
		return this->data < other.data;
	}

	bool ql::vgraph::data_point::operator>(ql::vgraph::data_point other) const
	{
		return this->data > other.data;
	}

	ql::vgraph::data_point_simple& ql::vgraph::data_point_simple::operator=(const ql::vgraph::data_point_simple& other)
	{
		this->data = other.data;
		return *this;
	}

	ql::vgraph::data_point_simple ql::vgraph::data_point_simple::operator*(ql::f64 n) const
	{
		auto copy = *this;
		copy.data *= n;
		return copy;
	}

	ql::vgraph::data_point_simple ql::vgraph::data_point_simple::operator*(ql::vgraph::data_point_simple other) const
	{
		auto copy = *this;
		copy.data *= other.data;
		return copy;
	}

	ql::vgraph::data_point_simple ql::vgraph::data_point_simple::operator-(ql::vgraph::data_point_simple other) const
	{
		auto copy = *this;
		copy.data -= other.data;
		return copy;
	}

	ql::vgraph::data_point_simple ql::vgraph::data_point_simple::operator+(ql::vgraph::data_point_simple other) const
	{
		auto copy = *this;
		copy.data += other.data;
		return copy;
	}

	bool ql::vgraph::data_point_simple::operator<(ql::vgraph::data_point_simple other) const
	{
		return this->data < other.data;
	}

	bool ql::vgraph::data_point_simple::operator>(ql::vgraph::data_point_simple other) const
	{
		return this->data > other.data;
	}

	void ql::vgraph::info_graph::set_font(const std::string& font)
	{
		this->text.font_name = font;
	}

	void ql::vgraph::info_graph::set_text_color(ql::rgba text_color)
	{
		this->text.set_color(text_color);
	}

	void ql::vgraph::info_graph::set_text_character_size(ql::u32 character_size)
	{
		this->text.character_size = character_size;
	}

	void ql::vgraph::info_graph::set_text_style(ql::u32 text_style)
	{
		this->text.style = text_style;
	}

	void ql::vgraph::info_graph::set_text_outline_thickness(ql::f32 thickness)
	{
		this->text.outline_thickness = thickness;
	}

	void ql::vgraph::info_graph::set_text_outline_color(ql::rgba color)
	{
		this->text.outline_color = color;
	}

	ql::f64 ql::vgraph::info_graph::get_percentage_height_at(ql::size index) const
	{
		auto [low, high] = this->get_low_high();

		return (this->data[index].data - low.data) / (high.data - low.data);
	}

	void ql::vgraph::info_graph::add_data(ql::f64 data)
	{
		this->add_data(data, this->color, this->thickness);
	}

	void ql::vgraph::info_graph::add_data(ql::f64 data, ql::rgba color)
	{
		this->add_data(data, color, this->thickness);
	}

	void ql::vgraph::info_graph::add_data(ql::f64 data, ql::rgba color, ql::f64 thickness)
	{
		this->data.push_back({});
		this->data.back().data = data;
		this->data.back().color = color;
		this->data.back().thickness = thickness;
	}

	void ql::vgraph::info_graph::add_data(ql::f64 data, std::string string)
	{
		this->add_data(data, this->color, this->thickness);
		this->data.back().text = this->text;
		this->data.back().text.set_string(string);
	}

	void ql::vgraph::info_graph::add_data(ql::f64 data, std::string string, ql::rgba color)
	{
		this->add_data(data, this->color, this->thickness);
		this->data.back().text = this->text;
		this->data.back().text.set_string(string);
		this->data.back().text.set_color(color);
	}

	std::pair<ql::vgraph::data_point_info, ql::vgraph::data_point_info> ql::vgraph::info_graph::get_low_high() const
	{
		return ql::min_max(this->data);
	}

	ql::size ql::vgraph::info_graph::size() const
	{
		return this->data.size();
	}

	void ql::vgraph::info_graph::clear()
	{
		return this->data.clear();
	}

	ql::vgraph::data_point_info& ql::vgraph::info_graph::operator[](ql::size index)
	{
		return this->data[index];
	}

	const ql::vgraph::data_point_info& ql::vgraph::info_graph::operator[](ql::size index) const
	{
		return this->data[index];
	}

	ql::vgraph::data_point_info& ql::vgraph::info_graph::back()
	{
		return this->data.back();
	}

	const ql::vgraph::data_point_info& ql::vgraph::info_graph::back() const
	{
		return this->data.back();
	}

	ql::vgraph::data_point_info& ql::vgraph::info_graph::front()
	{
		return this->data.front();
	}

	const ql::vgraph::data_point_info& ql::vgraph::info_graph::front() const
	{
		return this->data.front();
	}

	std::vector<ql::vgraph::data_point_info>::iterator ql::vgraph::info_graph::begin()
	{
		return this->data.begin();
	}

	std::vector<ql::vgraph::data_point_info>::const_iterator ql::vgraph::info_graph::begin() const
	{
		return this->data.begin();
	}

	std::vector<ql::vgraph::data_point_info>::const_iterator ql::vgraph::info_graph::cbegin()
	{
		return this->data.cbegin();
	}

	std::vector<ql::vgraph::data_point_info>::iterator ql::vgraph::info_graph::end()
	{
		return this->data.end();
	}

	std::vector<ql::vgraph::data_point_info>::const_iterator ql::vgraph::info_graph::end() const
	{
		return this->data.end();
	}

	std::vector<ql::vgraph::data_point_info>::const_iterator ql::vgraph::info_graph::cend()
	{
		return this->data.cend();
	}

	ql::f64 ql::vgraph::standard_graph::get_percentage_height_at(ql::size index) const
	{
		auto [low, high] = this->get_low_high();

		return (this->data[index].data - low.data) / (high.data - low.data);
	}

	void ql::vgraph::standard_graph::add_data(ql::f64 data)
	{
		this->add_data(data, this->color, this->thickness);
	}

	void ql::vgraph::standard_graph::add_data(ql::f64 data, ql::rgba color)
	{
		this->add_data(data, color, this->thickness);
	}

	void ql::vgraph::standard_graph::add_data(ql::f64 data, ql::rgba color, ql::f64 thickness)
	{
		this->data.push_back({});
		this->data.back().data = data;
		this->data.back().color = color;
		this->data.back().thickness = thickness;
	}

	std::pair<ql::vgraph::data_point, ql::vgraph::data_point> ql::vgraph::standard_graph::get_low_high() const
	{
		return ql::min_max(this->data);
	}

	ql::size ql::vgraph::standard_graph::size() const
	{
		return this->data.size();
	}

	void ql::vgraph::standard_graph::clear()
	{
		return this->data.clear();
	}

	ql::vgraph::data_point& ql::vgraph::standard_graph::operator[](ql::size index)
	{
		return this->data[index];
	}

	const ql::vgraph::data_point& ql::vgraph::standard_graph::operator[](ql::size index) const
	{
		return this->data[index];
	}

	ql::vgraph::data_point& ql::vgraph::standard_graph::back()
	{
		return this->data.back();
	}

	const ql::vgraph::data_point& ql::vgraph::standard_graph::back() const
	{
		return this->data.back();
	}

	ql::vgraph::data_point& ql::vgraph::standard_graph::front()
	{
		return this->data.front();
	}

	const ql::vgraph::data_point& ql::vgraph::standard_graph::front() const
	{
		return this->data.front();
	}

	std::vector<ql::vgraph::data_point>::iterator ql::vgraph::standard_graph::begin()
	{
		return this->data.begin();
	}

	std::vector<ql::vgraph::data_point>::const_iterator ql::vgraph::standard_graph::begin() const
	{
		return this->data.begin();
	}

	std::vector<ql::vgraph::data_point>::const_iterator ql::vgraph::standard_graph::cbegin()
	{
		return this->data.cbegin();
	}

	std::vector<ql::vgraph::data_point>::iterator ql::vgraph::standard_graph::end()
	{
		return this->data.end();
	}

	std::vector<ql::vgraph::data_point>::const_iterator ql::vgraph::standard_graph::end() const
	{
		return this->data.end();
	}

	std::vector<ql::vgraph::data_point>::const_iterator ql::vgraph::standard_graph::cend()
	{
		return this->data.cend();
	}

	ql::f64 ql::vgraph::simple_graph::get_percentage_height_at(ql::size index) const
	{
		auto [low, high] = this->get_low_high();

		return (this->data[index].data - low.data) / (high.data - low.data);
	}

	void ql::vgraph::simple_graph::add_data(ql::f64 data)
	{
		this->data.push_back(data);
	}

	std::pair<ql::vgraph::data_point_simple, ql::vgraph::data_point_simple> ql::vgraph::simple_graph::get_low_high() const
	{
		return ql::min_max(this->data);
	}

	ql::size ql::vgraph::simple_graph::size() const
	{
		return this->data.size();
	}

	void ql::vgraph::simple_graph::clear()
	{
		return this->data.clear();
	}

	ql::vgraph::data_point_simple& ql::vgraph::simple_graph::operator[](ql::size index)
	{
		return this->data[index];
	}

	const ql::vgraph::data_point_simple& ql::vgraph::simple_graph::operator[](ql::size index) const
	{
		return this->data[index];
	}

	ql::vgraph::data_point_simple& ql::vgraph::simple_graph::back()
	{
		return this->data.back();
	}

	const ql::vgraph::data_point_simple& ql::vgraph::simple_graph::back() const
	{
		return this->data.back();
	}

	ql::vgraph::data_point_simple& ql::vgraph::simple_graph::front()
	{
		return this->data.front();
	}

	const ql::vgraph::data_point_simple& ql::vgraph::simple_graph::front() const
	{
		return this->data.front();
	}

	std::vector<ql::vgraph::data_point_simple>::iterator ql::vgraph::simple_graph::begin()
	{
		return this->data.begin();
	}

	std::vector<ql::vgraph::data_point_simple>::const_iterator ql::vgraph::simple_graph::begin() const
	{
		return this->data.begin();
	}

	std::vector<ql::vgraph::data_point_simple>::const_iterator ql::vgraph::simple_graph::cbegin()
	{
		return this->data.cbegin();
	}

	std::vector<ql::vgraph::data_point_simple>::iterator ql::vgraph::simple_graph::end()
	{
		return this->data.end();
	}

	std::vector<ql::vgraph::data_point_simple>::const_iterator ql::vgraph::simple_graph::end() const
	{
		return this->data.end();
	}

	std::vector<ql::vgraph::data_point_simple>::const_iterator ql::vgraph::simple_graph::cend()
	{
		return this->data.cend();
	}

	void ql::vgraph::clear_data()
	{
		this->simple_graphs.clear();
		this->standard_graphs.clear();
		this->info_graphs.clear();
		this->index_start = 0u;
		this->index_end = ql::size_max;
	}

	bool ql::vgraph::empty() const
	{
		return this->simple_graphs.empty() && this->standard_graphs.empty() && this->info_graphs.empty();
	}

	bool ql::vgraph::changed() const
	{
		return (this->visible_index_range_before != this->visible_index_range());
	}

	void ql::vgraph::update_change() const
	{
		if (!this->changed())
		{
			return;
		}
		this->check_x_axis();
		auto x = this->get_low_high();
		this->low_high_graph = {x.first, x.second};

		this->visible_index_range_before = this->visible_index_range();
	}

	void ql::vgraph::check_x_axis() const
	{
		while (this->visible_element_size() / this->x_axis_line_frequency < this->desired_x_axis_lines / 2)
		{
			this->x_axis_line_frequency /= 2;
			if (!this->x_axis_line_frequency)
			{
				this->x_axis_line_frequency = 1u;
				break;
			}
		}
		while (this->visible_element_size() / this->x_axis_line_frequency > this->desired_x_axis_lines * 2)
		{
			this->x_axis_line_frequency *= 2;
		}

		this->index_skip_size = this->x_axis_line_frequency / this->desired_visible_size;
		if (!this->index_skip_size)
		{
			this->index_skip_size = 1u;
		}
	}

	void ql::vgraph::enable_track_new_entries()
	{
		this->display_last_n_entries = this->visible_element_size();
		this->index_start = 0u;
		this->index_end = ql::size_max;
		this->enable_last_n_when_dragging_right_lock = false;
	}

	void ql::vgraph::disable_track_new_entries()
	{
		auto size = this->visible_element_size();
		this->index_end = this->graph_element_size();
		this->index_start = ql::u32_cast(ql::max(ql::i32_cast(0), ql::i32_cast(this->index_end) - ql::i32_cast(size)));
	}

	void ql::vgraph::enable_axis_info()
	{
		this->use_x_axis = true;
		this->use_y_axis = true;
	}

	void ql::vgraph::update(const event_info& event_info)
	{
		if (this->empty())
		{
			return;
		}
		if (event_info.left_mouse_clicked())
		{
			ql::vrectangle rect(this->position, this->true_graph_dimension());
			rect.position.x += ql::f32_cast(this->y_axis_text_space);

			if (rect.contains(event_info.mouse_position()))
			{
				this->drag = true;
				this->click_position = event_info.mouse_position();
			}
		}

		this->mouse_position = event_info.mouse_position();
		if (event_info.mouse_moved())
		{
			if (this->drag && this->allow_dragging)
			{
				auto diff = this->click_position - event_info.mouse_position();

				auto size = this->visible_element_size();
				auto index_f = (diff.x / this->true_graph_width()) * size;
				auto index_delta = ql::i64_cast(index_f);

				if (index_delta)
				{
					this->click_position = event_info.mouse_position();
					this->click_position.x += ql::f32_cast(((index_f - index_delta) / size) * this->true_graph_width());

					this->index_start = ql::size_cast(ql::max(ql::i64_cast(0), ql::i64_cast(this->visible_index_start()) + index_delta));
					this->index_end = this->index_start + size;
					auto over = ql::i64_cast(this->index_end) - ql::i64_cast(this->graph_element_size());

					if (this->index_end >= this->graph_element_size())
					{
						this->index_end = this->graph_element_size();
						this->index_start = ql::size_cast(this->index_start - over);

						this->enable_last_n_when_dragging_right_lock = true;
					}
				}
				if (this->enable_last_n_when_dragging_right_lock)
				{
					this->enable_track_new_entries();
				}
			}
		}

		if (this->display_closest_graph_at_cursor && this->visible_element_size())
		{
			ql::vgraph::interpolation_type interpolation = ql::vgraph::interpolation_type::unset;

			auto visible_size = this->visible_element_size() - 1;
			auto offset = this->position.x + this->y_axis_text_space;
			auto progress = (event_info.mouse_position().x - offset) / this->true_graph_width();
			auto index = visible_size * progress;
			auto int_index = ql::size_cast(index);
			auto left_over = index - int_index;
			auto [low, high] = this->get_low_high();

			auto y_range = (high - low);
			if (high == ql::f64_min && low == ql::f64_max)
			{
				y_range = 0.0;
			}
			auto low_padded = low - y_range * this->y_axis_padding;
			auto high_padded = high + y_range * this->y_axis_padding;

			this->closest_graph_at_cursor = "";
			if (index >= 0 && index <= visible_size)
			{
				ql::f64 min_distance = ql::f64_max;

				for (auto& g : this->info_graphs)
				{
					interpolation = interpolation;
					if (interpolation == ql::vgraph::interpolation_type::unset)
					{
						interpolation = this->interpolation;
					}

					ql::f64 value = 0.0;
					if (left_over == 0.0)
					{
						value = g.second.data[this->visible_index_start() + int_index].data;
					}
					else if (interpolation == ql::vgraph::interpolation_type::cubic)
					{
						value = ql::cubic_interpolation(
								g.second.data[this->visible_index_start() + int_index].data,
								g.second.data[this->visible_index_start() + int_index + this->index_skip_size].data, left_over
						);
					}
					else if (interpolation == ql::vgraph::interpolation_type::linear)
					{
						value = ql::linear_interpolation(
								g.second.data[this->visible_index_start() + int_index].data,
								g.second.data[this->visible_index_start() + int_index + this->index_skip_size].data, left_over
						);
					}

					auto y_progress = (value - low_padded) / (high_padded - low_padded);
					y_progress = ql::clamp((1.0 - y_progress) * (1.0 - this->height_delta) + (this->height_delta) / 2);
					auto pos_y = this->position.y + this->dimension.y * y_progress;

					auto distance = ql::abs(pos_y - event_info.mouse_position().y);

					if (min_distance > distance && distance < this->closest_graph_at_cursor_distance)
					{
						min_distance = distance;
						this->closest_graph_at_cursor = g.first;
						this->closest_graph_at_cursor_value = value;
						this->closest_graph_at_cursor_color = g.second.color;
						this->closest_graph_at_cursor_index = ql::u32_cast(this->visible_index_start() + index + 0.5);
						if (this->closest_graph_at_cursor_color.is_unset())
						{
							this->closest_graph_at_cursor_color = this->color;
						}
					}
				}
				for (auto& g : this->standard_graphs)
				{
					interpolation = interpolation;
					if (interpolation == ql::vgraph::interpolation_type::unset)
					{
						interpolation = this->interpolation;
					}

					ql::f64 value = 0.0;
					if (left_over == 0.0)
					{
						value = g.second.data[this->visible_index_start() + int_index].data;
					}
					else if (interpolation == ql::vgraph::interpolation_type::cubic)
					{
						value = ql::cubic_interpolation(
								g.second.data[this->visible_index_start() + int_index].data,
								g.second.data[this->visible_index_start() + int_index + this->index_skip_size].data, left_over
						);
					}
					else if (interpolation == ql::vgraph::interpolation_type::linear)
					{
						value = ql::linear_interpolation(
								g.second.data[this->visible_index_start() + int_index].data,
								g.second.data[this->visible_index_start() + int_index + this->index_skip_size].data, left_over
						);
					}

					auto y_progress = (value - low_padded) / (high_padded - low_padded);
					y_progress = ql::clamp((1.0 - y_progress) * (1.0 - this->height_delta) + (this->height_delta) / 2);
					auto pos_y = this->position.y + this->dimension.y * y_progress;

					auto distance = ql::abs(pos_y - event_info.mouse_position().y);

					if (min_distance > distance && distance < this->closest_graph_at_cursor_distance)
					{
						min_distance = distance;
						this->closest_graph_at_cursor = g.first;
						this->closest_graph_at_cursor_value = value;
						this->closest_graph_at_cursor_color = g.second.color;
						this->closest_graph_at_cursor_index = ql::u32_cast(this->visible_index_start() + index + 0.5);
						if (this->closest_graph_at_cursor_color.is_unset())
						{
							this->closest_graph_at_cursor_color = this->color;
						}
					}
				}
				for (auto& g : this->simple_graphs)
				{
					interpolation = interpolation;
					if (interpolation == ql::vgraph::interpolation_type::unset)
					{
						interpolation = this->interpolation;
					}

					ql::f64 value = 0.0;
					if (left_over == 0.0)
					{
						value = g.second.data[this->visible_index_start() + int_index].data;
					}
					else if (interpolation == ql::vgraph::interpolation_type::cubic)
					{
						value = ql::cubic_interpolation(
								g.second.data[this->visible_index_start() + int_index].data,
								g.second.data[this->visible_index_start() + int_index + this->index_skip_size].data, left_over
						);
					}
					else if (interpolation == ql::vgraph::interpolation_type::linear)
					{
						value = ql::linear_interpolation(
								g.second.data[this->visible_index_start() + int_index].data,
								g.second.data[this->visible_index_start() + int_index + this->index_skip_size].data, left_over
						);
					}

					auto y_progress = (value - low_padded) / (high_padded - low_padded);
					y_progress = ql::clamp((1.0 - y_progress) * (1.0 - this->height_delta) + (this->height_delta) / 2);
					auto pos_y = this->position.y + this->dimension.y * y_progress;

					auto distance = ql::abs(pos_y - event_info.mouse_position().y);

					if (min_distance > distance && distance < this->closest_graph_at_cursor_distance)
					{
						min_distance = distance;
						this->closest_graph_at_cursor = g.first;
						this->closest_graph_at_cursor_value = value;
						this->closest_graph_at_cursor_color = g.second.color;
						this->closest_graph_at_cursor_index = ql::u32_cast(this->visible_index_start() + index + 0.5);
						if (this->closest_graph_at_cursor_color.is_unset())
						{
							this->closest_graph_at_cursor_color = this->color;
						}
					}
				}
			}
		}
		if (event_info.left_mouse_released())
		{
			this->drag = false;
			this->enable_last_n_when_dragging_right_lock = false;
		}
		if (event_info.scrolled_up())
		{
			ql::vrectangle rect(this->position, this->true_graph_dimension());
			rect.position.x += ql::f32_cast(this->y_axis_text_space);

			if (rect.contains(event_info.mouse_position()))
			{
				auto progress = (event_info.mouse_position().x - rect.position.x) / rect.dimension.x;
				auto change = this->visible_element_size();
				auto start = ql::i64_cast(this->visible_index_start());
				auto end = ql::i64_cast(this->visible_index_end());

				change = ql::size_cast(ql::f64_cast(change) * (this->zoom_factor - 1));

				if (change < 5)
				{
					change = 0;
				}

				start += ql::i64_cast(change * progress);
				end -= ql::i64_cast(change * (1 - progress));

				if (start >= ql::signed_cast(this->graph_element_size()))
				{
					start = ql::i64_cast(this->graph_element_size()) - 1;
				}
				if (end < 0)
				{
					end = 0;
				}

				this->index_start = ql::u32_cast(start);
				this->index_end = ql::u32_cast(end);
				this->check_x_axis();
			}
		}
		if (event_info.scrolled_down())
		{
			ql::vrectangle rect(this->position, this->true_graph_dimension());
			rect.position.x += ql::f32_cast(this->y_axis_text_space);

			if (rect.contains(event_info.mouse_position()))
			{
				auto progress = (event_info.mouse_position().x - rect.position.x) / rect.dimension.x;
				auto change = this->visible_element_size();
				auto start = ql::i64_cast(this->visible_index_start());
				auto end = ql::i64_cast(this->visible_index_end());

				change = ql::size_cast(ql::f64_cast(change) * (this->zoom_factor - 1));
				if (change == 0)
				{
					change = 1;
				}

				start -= ql::i64_cast(change * progress);
				end += ql::i64_cast(change * (1 - progress));

				if (end >= ql::signed_cast(this->graph_element_size()))
				{
					end = ql::i64_cast(this->graph_element_size());
				}
				if (start < 0)
				{
					start = 0;
				}
				this->index_start = ql::size_cast(start);
				this->index_end = ql::size_cast(end);

				this->check_x_axis();
			}
		}
	}

	void ql::vgraph::copy_visible_range(const vgraph& other)
	{
		this->visible_index_range_before = this->visible_index_range();
		this->index_start = other.index_start;
		this->index_end = other.index_end;
		this->index_skip_size = other.index_skip_size;
		this->display_last_n_entries = other.display_last_n_entries;
	}

	void ql::vgraph::set_visible_range(ql::size begin, ql::size end)
	{
		this->visible_index_range_before = this->visible_index_range();
		this->index_start = begin;
		this->index_end = end;
		this->check_x_axis();
		this->display_last_n_entries = 0u;
	}

	void ql::vgraph::set_visible_range_max()
	{
		this->index_start = 0u;
		this->index_end = ql::size_max;
	}

	void ql::vgraph::set_font(std::string name)
	{
		this->font = name;
		this->enable_axis_info();
	}

	std::string ql::vgraph::get_font() const
	{
		return this->font;
	}

	void ql::vgraph::set_dimension(ql::vec2 dimension)
	{
		this->dimension = dimension;
	}

	void ql::vgraph::set_position(ql::vec2 position)
	{
		this->position = position;
	}

	ql::f64 ql::vgraph::true_graph_width() const
	{
		return this->dimension.x - this->y_axis_text_space;
	}

	ql::f64 ql::vgraph::true_graph_height() const
	{
		return this->dimension.y - this->x_axis_text_space;
	}

	ql::vec2 ql::vgraph::true_graph_dimension() const
	{
		return ql::vec2(this->true_graph_width(), this->true_graph_height());
	}

	std::pair<ql::f64, ql::f64> ql::vgraph::get_low_high() const
	{
		ql::f64 low, high;
		low = ql::f64_max;
		high = ql::f64_min;

		ql::size interpolation_steps = ql::size{};
		ql::vgraph::interpolation_type interpolation = ql::vgraph::interpolation_type::unset;

		for (auto& g : this->info_graphs)
		{
			ql::f64 min, max;

			interpolation_steps = g.second.interpolation_steps;
			if (interpolation_steps == ql::size_max)
			{
				interpolation_steps = this->interpolation_steps;
			}

			interpolation = g.second.interpolation;
			if (interpolation == ql::vgraph::interpolation_type::unset)
			{
				interpolation = this->interpolation;
			}

			if (interpolation == ql::vgraph::interpolation_type::cubic)
			{
				auto span = this->get_info_graph_span(g.first);

				auto result = ql::cubic_container_interpolation_min_max(
						span, interpolation_steps, 0, this->index_skip_size, ql::vgraph::data_point_info{ql::f64_max},
						ql::vgraph::data_point_info{ql::f64_min}
				);

				std::tie(min, max) = std::make_pair(result.first.data, result.second.data);
			}
			else
			{
				auto span = this->get_info_graph_span(g.first);

				auto result = ql::min_max(span, this->index_skip_size);

				std::tie(min, max) = std::make_pair(result.first.data, result.second.data);
			}

			low = ql::min(min, low);
			high = ql::max(max, high);
		}
		for (auto& g : this->standard_graphs)
		{
			ql::f64 min, max;

			interpolation_steps = g.second.interpolation_steps;
			if (interpolation_steps == ql::size_max)
			{
				interpolation_steps = this->interpolation_steps;
			}

			interpolation = g.second.interpolation;
			if (interpolation == ql::vgraph::interpolation_type::unset)
			{
				interpolation = this->interpolation;
			}

			if (interpolation == ql::vgraph::interpolation_type::cubic)
			{
				auto span = this->get_standard_graph_span(g.first);

				auto result = ql::cubic_container_interpolation_min_max(
						span, interpolation_steps, 0, this->index_skip_size, ql::vgraph::data_point{ql::f64_max},
						ql::vgraph::data_point{ql::f64_min}
				);

				std::tie(min, max) = std::make_pair(result.first.data, result.second.data);
			}
			else
			{
				auto span = this->get_standard_graph_span(g.first);

				auto result = ql::min_max(span, this->index_skip_size);

				std::tie(min, max) = std::make_pair(result.first.data, result.second.data);
			}

			low = ql::min(min, low);
			high = ql::max(max, high);
		}
		for (auto& g : this->simple_graphs)
		{
			ql::f64 min, max;

			interpolation_steps = g.second.interpolation_steps;
			if (interpolation_steps == ql::size_max)
			{
				interpolation_steps = this->interpolation_steps;
			}

			interpolation = g.second.interpolation;
			if (interpolation == ql::vgraph::interpolation_type::unset)
			{
				interpolation = this->interpolation;
			}

			if (interpolation == ql::vgraph::interpolation_type::cubic)
			{
				auto span = this->get_simple_graph_span(g.first);

				auto result = ql::cubic_container_interpolation_min_max(
						span, interpolation_steps, 0, this->index_skip_size, ql::vgraph::data_point_simple{ql::f64_max},
						ql::vgraph::data_point_simple{ql::f64_min}
				);

				std::tie(min, max) = std::make_pair(result.first.data, result.second.data);
			}
			else
			{
				auto span = this->get_simple_graph_span(g.first);

				auto result = ql::min_max(span, this->index_skip_size);

				std::tie(min, max) = std::make_pair(result.first.data, result.second.data);
			}

			low = ql::min(min, low);
			high = ql::max(max, high);
		}

		low = ql::clamp(this->min_min_value, low, this->min_max_value);
		high = ql::clamp(this->max_min_value, high, this->max_max_value);

		if (this->y_axis_start_at_0)
		{
			if (low < 0 && high < 0)
			{
				high = 0;
			}
			if (low > 0 && high > 0)
			{
				low = 0;
			}
		}
		if (low == high)
		{
			low -= 1;
			high += 1;
		}

		return std::make_pair(low, high);
	}

	ql::size ql::vgraph::total_graph_size() const
	{
		return this->standard_graphs.size() + this->info_graphs.size() + this->simple_graphs.size();
	}

	ql::size ql::vgraph::graph_element_size() const
	{
		ql::size result = ql::size_max;
		for (auto& i : this->info_graphs)
		{
			if (result == ql::size_max)
			{
				result = i.second.size();
			}
			else
			{
				if (result != i.second.size())
				{
					throw std::exception(ql::to_string("ql::vgraph: graphs have different element sizes (", i.first, ")").c_str());
				}
			}
		}
		for (auto& i : this->standard_graphs)
		{
			if (result == ql::size_max)
			{
				result = i.second.size();
			}
			else
			{
				if (result != i.second.size())
				{
					throw std::exception(ql::to_string("ql::vgraph: graphs have different element sizes (", i.first, ")").c_str());
				}
			}
		}
		for (auto& i : this->simple_graphs)
		{
			if (result == ql::size_max)
			{
				result = i.second.size();
			}
			else
			{
				if (result != i.second.size())
				{
					throw std::exception(ql::to_string("ql::vgraph: graphs have different element sizes (", i.first, ")").c_str());
				}
			}
		}
		if (result == ql::size_max)
		{
			return ql::size{0u};
		}
		return result;
	}

	ql::size ql::vgraph::visible_element_size() const
	{
		if (this->is_range_enabled())
		{
			return (this->index_end - this->index_start);
		}
		else if (this->display_last_n_entries)
		{
			auto size = this->graph_element_size();
			return ql::min(size, this->display_last_n_entries);
		}
		else
		{
			return this->graph_element_size();
		}
	}

	ql::size ql::vgraph::visible_index_start() const
	{
		if (this->is_range_enabled())
		{
			return this->index_start;
		}
		else if (this->display_last_n_entries)
		{
			auto size = this->graph_element_size();
			if (size >= this->display_last_n_entries)
			{
				return size - this->display_last_n_entries;
			}
		}
		return 0u;
	}

	ql::size ql::vgraph::visible_index_end() const
	{
		if (this->is_range_enabled())
		{
			return this->index_end;
		}
		else if (this->display_last_n_entries)
		{
			auto size = this->visible_element_size();
			return this->visible_index_start() + size;
		}
		return this->visible_element_size();
	}

	std::pair<ql::size, ql::size> ql::vgraph::visible_index_range() const
	{
		return std::make_pair(this->visible_index_start(), this->visible_index_end());
	}

	bool ql::vgraph::is_range_enabled() const
	{
		return !(this->index_start == 0u && this->index_end == ql::size_max);
	}

	void ql::vgraph::add_info_graph(std::string name)
	{
		if (this->info_graphs.find(name) == this->info_graphs.cend())
		{
			this->info_graphs[name];
		}
	}

	ql::vgraph::info_graph& ql::vgraph::get_info_graph(std::string name)
	{
		return this->info_graphs[name];
	}

	const ql::vgraph::info_graph& ql::vgraph::get_info_graph(std::string name) const
	{
		return this->info_graphs.at(name);
	}

	std::span<const ql::vgraph::data_point_info> ql::vgraph::get_info_graph_span(std::string name) const
	{
		auto start = this->visible_index_start();
		auto end = this->visible_index_end();

		auto begin = this->get_info_graph(name).data.begin();
		return std::span(begin + start, begin + end);
	}

	void ql::vgraph::add_standard_graph(std::string name)
	{
		if (this->standard_graphs.find(name) == this->standard_graphs.cend())
		{
			this->standard_graphs[name];
		}
	}

	ql::vgraph::standard_graph& ql::vgraph::get_standard_graph(std::string name)
	{
		return this->standard_graphs[name];
	}

	const ql::vgraph::standard_graph& ql::vgraph::get_standard_graph(std::string name) const
	{
		return this->standard_graphs.at(name);
	}

	std::span<const ql::vgraph::data_point> ql::vgraph::get_standard_graph_span(std::string name) const
	{
		auto start = this->visible_index_start();
		auto end = this->visible_index_end();

		auto begin = this->get_standard_graph(name).data.begin();
		return std::span(begin + start, begin + end);
	}

	void ql::vgraph::add_simple_graph(std::string name)
	{
		if (this->simple_graphs.find(name) == this->simple_graphs.cend())
		{
			this->simple_graphs[name];
		}
	}

	ql::vgraph::simple_graph& ql::vgraph::get_simple_graph(std::string name)
	{
		return this->simple_graphs[name];
	}

	const ql::vgraph::simple_graph& ql::vgraph::get_simple_graph(std::string name) const
	{
		return this->simple_graphs.at(name);
	}

	std::span<const ql::vgraph::data_point_simple> ql::vgraph::get_simple_graph_span(std::string name) const
	{
		auto start = this->visible_index_start();
		auto end = this->visible_index_end();

		auto begin = this->get_simple_graph(name).data.begin();
		return std::span(begin + start, begin + end);
	}

	void ql::vgraph::add_y_axis_line(ql::f64 value)
	{
		this->add_y_axis_line(value, ql::rgba::red(), this->axis_thickness / 2);
	}

	void ql::vgraph::add_y_axis_line(ql::f64 value, ql::rgba color, ql::f64 thickness, bool foreground)
	{
		this->y_axis_highlighted_lines[value].color = color;
		this->y_axis_highlighted_lines[value].thickness = thickness;
		this->y_axis_highlighted_lines[value].foreground = foreground;
	}

	ql::vgraph::highlighted_line& ql::vgraph::get_y_axis_line(ql::f64 value)
	{
		if (this->y_axis_highlighted_lines.find(value) == this->y_axis_highlighted_lines.cend())
		{
			this->y_axis_highlighted_lines[value].color = ql::rgba::red();
			this->y_axis_highlighted_lines[value].thickness = this->axis_thickness;
		}
		return this->y_axis_highlighted_lines[value];
	}

	const ql::vgraph::highlighted_line& ql::vgraph::get_y_axis_line(ql::f64 value) const
	{
		return this->y_axis_highlighted_lines.at(value);
	}

	ql::graph& ql::graph::operator=(const ql::vgraph& graph)
	{
		if (graph.empty() || graph.graph_element_size() == 0u)
		{
			return *this;
		}
		graph.update_change();

		std::string used_font = graph.font;

		if (used_font.empty())
		{
			used_font = graph.y_axis_text.font_name;
		}
		if (used_font.empty())
		{
			used_font = graph.x_axis_text.font_name;
		}

		this->lines.resize(graph.total_graph_size());
		this->circle_texts.resize(graph.info_graphs.size());
		this->circles.resize(graph.info_graphs.size());

		ql::size interpolation_steps;
		ql::vgraph::interpolation_type interpolation = ql::vgraph::interpolation_type::unset;

		for (auto& g : graph.info_graphs)
		{
			interpolation_steps = g.second.interpolation_steps;
			if (interpolation_steps == ql::size_max)
			{
				interpolation_steps = graph.interpolation_steps;
			}
		}
		for (auto& g : graph.standard_graphs)
		{
			interpolation_steps = g.second.interpolation_steps;
			if (interpolation_steps == ql::size_max)
			{
				interpolation_steps = graph.interpolation_steps;
			}

			interpolation = g.second.interpolation;
			if (interpolation == ql::vgraph::interpolation_type::unset)
			{
				interpolation = graph.interpolation;
			}
		}
		for (auto& g : graph.simple_graphs)
		{
			interpolation_steps = g.second.interpolation_steps;
			if (interpolation_steps == ql::size_max)
			{
				interpolation_steps = graph.interpolation_steps;
			}

			interpolation = g.second.interpolation;
			if (interpolation == ql::vgraph::interpolation_type::unset)
			{
				interpolation = graph.interpolation;
			}
		}

		ql::f64 low, high;
		std::tie(low, high) = graph.get_low_high();

		auto y_range = (high - low);
		if (high == ql::f64_min && low == ql::f64_max)
		{
			y_range = 0.0;
		}
		auto low_padded = low - y_range * graph.y_axis_padding;
		auto high_padded = high + y_range * graph.y_axis_padding;

		ql::u32 u = 0u;
		for (auto& g : graph.info_graphs)
		{
			std::vector<ql::vgraph::data_point_info> interpolated_data;

			auto span = graph.get_info_graph_span(g.first);

			if (interpolation == ql::vgraph::interpolation_type::cubic)
			{
				interpolated_data = ql::cubic_container_interpolation(span, interpolation_steps, graph.index_skip_size);
			}
			else if (interpolation == ql::vgraph::interpolation_type::linear)
			{
				interpolated_data = ql::linear_container_interpolation(span, interpolation_steps, graph.index_skip_size);
			}

			bool use_interpolated_thickness = false;
			bool use_interpolated_color = false;

			this->circles[u].clear();
			this->circle_texts[u].clear();

			for (ql::u32 i = 0u; i < span.size(); ++i)
			{
				if (!use_interpolated_thickness && span[i].thickness != ql::f64_min)
				{
					use_interpolated_thickness = true;
				}

				if (!use_interpolated_color && span[i].color != ql::frgba::unset())
				{
					use_interpolated_color = true;
				}

				if (!use_interpolated_thickness && !use_interpolated_color)
				{
					break;
				}
			}

			ql::f64 using_thickness = g.second.thickness;
			if (using_thickness == ql::f64_min)
			{
				using_thickness = graph.thickness;
			}

			if (graph.display_closest_graph_at_cursor && !graph.closest_graph_at_cursor.empty() &&
					graph.closest_graph_at_cursor == g.first && graph.closest_graph_at_cursor_color == g.second.color)
			{
				using_thickness *= graph.closest_graph_at_cursor_multiply_thickness;
			}
			ql::frgba using_color = g.second.color;
			if (using_color == ql::frgba::unset())
			{
				using_color = graph.color;
			}

			this->lines[u].clear();
			for (ql::u32 i = 0u; i < interpolated_data.size(); ++i)
			{
				ql::vec2 position;
				position.x = ql::f32_cast(
						graph.position.x +
						(graph.dimension.x - graph.y_axis_text_space) * (i / static_cast<double>(interpolated_data.size() - 1)) +
						graph.y_axis_text_space
				);

				auto y_progress = (interpolated_data[i].data - low_padded) / (high_padded - low_padded);
				y_progress = ql::clamp((1.0 - y_progress) * (1.0 - graph.height_delta) + (graph.height_delta) / 2);
				position.y = ql::f32_cast(graph.position.y + graph.dimension.y * y_progress);

				auto color = use_interpolated_color ? interpolated_data[i].color : using_color;
				auto thickness = ql::f32_cast(use_interpolated_thickness ? interpolated_data[i].thickness : using_thickness);
				this->lines[u].add_thick_line(position, color, thickness);

				if (g.second.only_draw_if_close && graph.index_skip_size == 1)
				{
					if (interpolated_data[i].circle.radius > 0.0)
					{
						// graph.data[i].circle.point.position = position;

						this->circles[u].add_circle(position, interpolated_data[i].circle.radius, interpolated_data[i].circle.point.color);
					}

					if (!interpolated_data[i].text.string.empty())
					{
						this->circle_texts[u].push_back(interpolated_data[i].text);
						if (interpolated_data[i].text.font_name.empty())
						{
							this->circle_texts[u].back().set_font(used_font);
						}
						else
						{
							if (used_font.empty())
							{
								used_font = interpolated_data[i].text.font_name;
							}
							this->circle_texts[u].back().set_font(interpolated_data[i].text.font_name);
						}
						this->circle_texts[u].back().set_position(position);
						this->circle_texts[u].back().centerize();
					}
				}
			}

			++u;
		}
		for (auto& g : graph.standard_graphs)
		{
			std::vector<ql::vgraph::data_point> interpolated_data;

			auto span = graph.get_standard_graph_span(g.first);

			if (interpolation == ql::vgraph::interpolation_type::cubic)
			{
				interpolated_data = ql::cubic_container_interpolation(span, interpolation_steps, graph.index_skip_size);
			}
			else if (interpolation == ql::vgraph::interpolation_type::linear)
			{
				interpolated_data = ql::linear_container_interpolation(span, interpolation_steps, graph.index_skip_size);
			}

			bool use_interpolated_thickness = false;
			bool use_interpolated_color = false;

			for (ql::u32 i = 0u; i < span.size(); ++i)
			{
				if (!use_interpolated_thickness && span[i].thickness != ql::f64_min)
				{
					use_interpolated_thickness = true;
				}

				if (!use_interpolated_color && span[i].color != ql::frgba::unset())
				{
					use_interpolated_color = true;
				}

				if (!use_interpolated_thickness && !use_interpolated_color)
				{
					break;
				}
			}

			ql::f64 using_thickness = g.second.thickness;
			if (using_thickness == ql::f64_min)
			{
				using_thickness = graph.thickness;
			}

			if (graph.display_closest_graph_at_cursor && !graph.closest_graph_at_cursor.empty() &&
					graph.closest_graph_at_cursor == g.first && graph.closest_graph_at_cursor_color == g.second.color)
			{
				using_thickness *= graph.closest_graph_at_cursor_multiply_thickness;
			}

			ql::frgba using_color = g.second.color;
			if (using_color == ql::frgba::unset())
			{
				using_color = graph.color;
			}

			this->lines[u].clear();
			for (ql::u32 i = 0u; i < interpolated_data.size(); ++i)
			{
				ql::vec2 position;
				position.x = ql::f32_cast(
						graph.position.x +
						(graph.dimension.x - graph.y_axis_text_space) * (i / static_cast<double>(interpolated_data.size() - 1)) +
						graph.y_axis_text_space
				);

				auto y_progress = (interpolated_data[i].data - low_padded) / (high_padded - low_padded);
				y_progress = ql::clamp((1.0 - y_progress) * (1.0 - graph.height_delta) + (graph.height_delta) / 2);
				position.y = ql::f32_cast(graph.position.y + graph.dimension.y * y_progress);

				auto color = use_interpolated_color ? interpolated_data[i].color : using_color;
				auto thickness = ql::f32_cast(use_interpolated_thickness ? interpolated_data[i].thickness : using_thickness);
				this->lines[u].add_thick_line(position, color, thickness);
			}

			++u;
		}
		for (auto& g : graph.simple_graphs)
		{
			std::vector<ql::vgraph::data_point_simple> interpolated_data;

			auto span = graph.get_simple_graph_span(g.first);

			if (interpolation == ql::vgraph::interpolation_type::cubic)
			{
				interpolated_data = ql::cubic_container_interpolation(span, interpolation_steps, graph.index_skip_size);
			}
			else if (interpolation == ql::vgraph::interpolation_type::linear)
			{
				interpolated_data = ql::linear_container_interpolation(span, interpolation_steps, graph.index_skip_size);
			}

			ql::f64 using_thickness = g.second.thickness;
			if (using_thickness == ql::f64_min)
			{
				using_thickness = graph.thickness;
			}

			if (graph.display_closest_graph_at_cursor && !graph.closest_graph_at_cursor.empty() &&
					graph.closest_graph_at_cursor == g.first && graph.closest_graph_at_cursor_color == g.second.color)
			{
				using_thickness *= graph.closest_graph_at_cursor_multiply_thickness;
			}

			ql::frgba using_color = g.second.color;
			if (using_color == ql::frgba::unset())
			{
				using_color = graph.color;
			}

			this->lines[u].clear();

			for (ql::u32 i = 0u; i < interpolated_data.size(); ++i)
			{
				ql::vec2 position;
				position.x = ql::f32_cast(
						graph.position.x +
						(graph.dimension.x - graph.y_axis_text_space) * (i / static_cast<double>(interpolated_data.size() - 1)) +
						graph.y_axis_text_space
				);

				auto y_progress = (interpolated_data[i].data - low_padded) / (high_padded - low_padded);
				y_progress = ql::clamp((1.0 - y_progress) * (1.0 - graph.height_delta) + (graph.height_delta) / 2);
				position.y = ql::f32_cast(graph.position.y + graph.dimension.y * y_progress);

				auto color = using_color;
				auto thickness = ql::f32_cast(using_thickness);
				this->lines[u].add_thick_line(position, color, thickness);
			}

			++u;
		}

		if (u)
		{
			ql::rgba use_color = graph.axis_color;

			if (graph.use_y_axis)
			{
				auto exponent = static_cast<ql::i64>(std::log10(y_range)) - 1;
				auto multiply = std::pow(10, -exponent);
				y_range *= multiply;

				ql::f64 y_delta = 0.0;
				ql::f64 y_start = 0.0;
				ql::f64 y_end = 0.0;
				ql::u32 y_steps = 0;

				if (!used_font.empty() && y_range != 0)
				{
					y_delta = ql::i64_cast(y_range) / (multiply * graph.desired_y_axis_lines);

					y_start = ql::i64_cast(low_padded / y_delta + 1) * y_delta;
					y_end = ql::i64_cast(high_padded / y_delta) * y_delta;
					y_steps = ql::u32_cast(ql::i64_cast((y_end - y_start) / y_delta) + 2);
				}

				this->y_lines.resize(y_steps);
				this->y_lines_foreground.clear();
				this->y_texts.resize(y_steps);

				for (auto& y : graph.y_axis_highlighted_lines)
				{
					if (y.first >= low_padded && y.first <= high_padded)
					{
						auto y_position = y.first;
						auto y_progress = ((y_position)-low_padded) / (high_padded - low_padded);
						y_progress = (1.0 - y_progress) * (1.0 - graph.height_delta) + (graph.height_delta) / 2;

						ql::vec2 position;
						position.x = graph.position.x;
						position.y = ql::f32_cast(graph.position.y + graph.true_graph_height() * y_progress + graph.x_axis_text_space);

						auto a = position;
						auto b = a;
						b.x += graph.dimension.x;

						if (y.second.foreground)
						{
							this->y_lines_foreground.resize(this->y_lines_foreground.size() + 1);
							this->y_lines_foreground.back().clear();
							this->y_lines_foreground.back().add_thick_line(a, y.second.color, ql::f32_cast(y.second.thickness));
							this->y_lines_foreground.back().add_thick_line(b, y.second.color, ql::f32_cast(y.second.thickness));
						}
						else
						{
							this->y_lines.resize(this->y_lines.size() + 1);
							this->y_lines.back().clear();
							this->y_lines.back().add_thick_line(a, y.second.color, ql::f32_cast(y.second.thickness));
							this->y_lines.back().add_thick_line(b, y.second.color, ql::f32_cast(y.second.thickness));
						}
					}
				}
				for (ql::u32 i = 0u; i < y_steps; ++i)
				{
					auto y_position = y_start + y_delta * i;
					auto y_progress = ((y_position)-low_padded) / (high_padded - low_padded);
					y_progress = (1.0 - y_progress) * (1.0 - graph.height_delta) + (graph.height_delta) / 2;
					ql::vec2 position;
					position.x = graph.position.x;
					position.y = ql::f32_cast(graph.position.y + graph.true_graph_height() * y_progress + graph.x_axis_text_space);

					this->y_texts[i] = graph.y_axis_text;
					if (this->y_texts[i].get_font().empty())
					{
						this->y_texts[i].set_font(used_font);
					}
					if (use_color.is_unset())
					{
						if (!graph.y_axis_color.is_unset())
						{
							use_color = graph.y_axis_color;
							this->y_texts[i].set_color(use_color);
						}
					}
					else
					{
						this->y_texts[i].set_color(use_color);
					}
					if (graph.y_axis_text_left)
					{
						if (graph.y_axis_string_function)
						{
							this->y_texts[i].set_string(graph.y_axis_string_function(y_position));
						}
						else if (graph.y_axis_text_percent)
						{
							this->y_texts[i].set_string(
									graph.y_axis_text.string + ql::string_precision(graph.y_axis_text_precision, ql::size_cast(y_position * 100)) +
									"%"
							);
						}
						else if (graph.y_axis_text_integer)
						{
							this->y_texts[i].set_string(graph.y_axis_text.string + ql::to_string(ql::i64_cast(y_position)));
						}
						else
						{
							this->y_texts[i].set_string(
									graph.y_axis_text.string + ql::string_precision(graph.y_axis_text_precision, ql::size_cast(y_position))
							);
						}
					}
					else
					{
						if (graph.y_axis_string_function)
						{
							this->y_texts[i].set_string(graph.y_axis_string_function(y_position));
						}
						else if (graph.y_axis_text_percent)
						{
							this->y_texts[i].set_string(
									ql::string_precision(graph.y_axis_text_precision, ql::size_cast(y_position * 100)) + "%" +
									graph.y_axis_text.string
							);
						}
						else if (graph.y_axis_text_integer)
						{
							this->y_texts[i].set_string(ql::to_string(ql::i64_cast(y_position)));
						}
						else
						{
							this->y_texts[i].set_string(
									ql::string_precision(graph.y_axis_text_precision, ql::size_cast(y_position)) + graph.y_axis_text.string
							);
						}
					}
					this->y_texts[i].set_position(position);
					this->y_texts[i].centerize_y();

					auto a = position;
					auto b = a;
					b.x += graph.dimension.x;

					this->y_lines[i].clear();
					this->y_lines[i].add_thick_line(a, graph.axis_line_color, ql::f32_cast(graph.axis_thickness));
					this->y_lines[i].add_thick_line(b, graph.axis_line_color, ql::f32_cast(graph.axis_thickness));
				}
			}
			else
			{
				this->y_lines.clear();
				this->y_texts.clear();
			}

			if (graph.use_x_axis)
			{
				auto index_mod = graph.x_axis_line_frequency - (graph.visible_index_start() % graph.x_axis_line_frequency) - 1;
				auto x_size = graph.visible_element_size() / graph.x_axis_line_frequency + 1;
				this->x_lines.resize(x_size);
				this->x_texts.resize(x_size);

				for (ql::u32 i = 0u; i < x_size; ++i)
				{
					auto progress =
							(((i * graph.x_axis_line_frequency) + index_mod)) / static_cast<double>(graph.visible_element_size() - 1);
					auto multiple = ql::approximate_multiple_up(graph.visible_index_start(), graph.x_axis_line_frequency);
					if (graph.visible_index_start() == 0u)
					{
						multiple = ql::u32_cast(graph.x_axis_line_frequency);
					}
					ql::size index = multiple + ql::size_cast(i * graph.x_axis_line_frequency);

					ql::vec2 position;
					position.x = ql::f32_cast(graph.position.x + (graph.true_graph_width()) * progress + graph.y_axis_text_space);
					position.y = graph.position.y + graph.dimension.y;

					this->x_texts[i] = graph.x_axis_text;
					if (this->x_texts[i].get_font().empty())
					{
						this->x_texts[i].set_font(used_font);
					}

					if (use_color.is_unset())
					{
						if (!graph.x_axis_color.is_unset())
						{
							use_color = graph.x_axis_color;
							this->x_texts[i].set_color(use_color);
						}
					}
					else
					{
						this->x_texts[i].set_color(use_color);
					}
					this->x_texts[i].set_string(graph.x_axis_text.string + graph.x_axis_string_function(index));
					this->x_texts[i].set_position(position.moved(0, -ql::signed_cast(graph.x_axis_text.character_size)));
					this->x_texts[i].centerize_x();

					auto a = position;
					a.y -= ql::f32_cast(graph.x_axis_text_space);
					auto b = a;
					b.y = graph.position.y;

					this->x_lines[i].clear();
					this->x_lines[i].add_thick_line(a, graph.axis_line_color, ql::f32_cast(graph.axis_thickness));
					this->x_lines[i].add_thick_line(b, graph.axis_line_color, ql::f32_cast(graph.axis_thickness));
				}
			}
			else
			{
				this->x_lines.clear();
				this->x_texts.clear();
			}
		}

		this->cursor_graph_text.set_color(ql::rgba::unset());
		if (graph.display_closest_graph_at_cursor && !graph.closest_graph_at_cursor.empty())
		{
			this->cursor_graph_text = graph.closest_graph_at_cursor_text;
			if (this->cursor_graph_text.get_font().empty())
			{
				this->cursor_graph_text.set_font(used_font);
			}
			if (graph.closest_graph_at_cursor_string_function)
			{
				this->cursor_graph_text.set_string(graph.closest_graph_at_cursor_string_function(
						graph.closest_graph_at_cursor, graph.closest_graph_at_cursor_value, graph.closest_graph_at_cursor_index
				));
			}
			else
			{
				if (graph.y_axis_cursor_string_function)
				{
					this->cursor_graph_text.set_string(ql::to_string(
							graph.closest_graph_at_cursor, " : ", graph.y_axis_cursor_string_function(graph.closest_graph_at_cursor_value)
					));
				}
				else
				{
					if (graph.y_axis_string_function)
					{
						this->cursor_graph_text.set_string(ql::to_string(
								graph.closest_graph_at_cursor, " : ", graph.y_axis_string_function(graph.closest_graph_at_cursor_value)
						));
					}
					else
					{
						this->cursor_graph_text.set_string(
								ql::to_string(graph.closest_graph_at_cursor, " = ", graph.closest_graph_at_cursor_value)
						);
					}
				}
			}
			this->cursor_graph_text.set_color(graph.closest_graph_at_cursor_color.with_alpha(255));
			this->cursor_graph_text.set_position(graph.mouse_position);

			auto hitbox = this->cursor_graph_text.get_visible_hitbox();
			this->cursor_graph_text.move(ql::vec2{15, -hitbox.dimension.y - 15});
			hitbox = this->cursor_graph_text.get_visible_hitbox();
			auto diff = (hitbox.position.x + hitbox.dimension.x) - (graph.position.x + graph.dimension.x) + 15;
			if (diff > 0)
			{
				this->cursor_graph_text.move(ql::vec2{-diff, 0});
				hitbox = this->cursor_graph_text.get_visible_hitbox();
			}

			this->cursor_graph_background = graph.closest_graph_at_cursor_background;
			if (graph.closest_graph_at_cursor_background_is_graph_background)
			{
				this->cursor_graph_background.set_color(graph.background_color.with_alpha(255));
			}
			this->cursor_graph_background.set_dimension(hitbox.dimension + 5);
			this->cursor_graph_background.set_center(hitbox.get_center());
			this->cursor_graph_background.set_outline_color(graph.closest_graph_at_cursor_color.with_alpha(255));
		}

		this->background.set_position(graph.position);
		this->background.set_dimension(graph.dimension);
		this->background.set_color(graph.background_color);
		return *this;
	}

	void ql::graph::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		this->background.draw(window, states);

		for (ql::u32 i = 0u; i < this->y_lines.size(); ++i)
		{
			this->y_lines[i].draw(window, states);
		}
		for (ql::u32 i = 0u; i < this->x_lines.size(); ++i)
		{
			this->x_lines[i].draw(window, states);
		}
		for (ql::u32 i = 0u; i < this->y_texts.size(); ++i)
		{
			this->y_texts[i].draw(window, states);
		}
		for (ql::u32 i = 0u; i < this->x_texts.size(); ++i)
		{
			this->x_texts[i].draw(window, states);
		}
		for (ql::u32 i = 0u; i < this->lines.size(); ++i)
		{
			this->lines[i].draw(window, states);
		}
		for (ql::u32 i = 0u; i < this->circles.size(); ++i)
		{
			this->circles[i].draw(window, states);
			for (auto& i : this->circle_texts[i])
			{
				i.draw(window, states);
			}
		}
		for (ql::u32 i = 0u; i < this->y_lines_foreground.size(); ++i)
		{
			this->y_lines_foreground[i].draw(window, states);
		}
		if (!this->cursor_graph_text.get_color().is_unset())
		{
			this->cursor_graph_background.draw(window, states);
			this->cursor_graph_text.draw(window, states);
		}
	}

	void ql::border_graphic::set_dimension(ql::vec2 dimension)
	{
		this->dimension = dimension;
	}

	void ql::border_graphic::set_position(ql::vec2 position)
	{
		this->position = position;
	}

	void ql::border_graphic::increase(ql::vec2 delta)
	{
		this->position -= delta;
		this->dimension += delta * 2;
	}

	void ql::border_graphic::set_color(ql::rgba color)
	{
		this->color = color;
	}

	void ql::border_graphic::set_scale(ql::vec2 scale)
	{
		this->scale = scale;
	}

	void ql::border_graphic::set_scale(ql::f32 scale)
	{
		this->scale = ql::vec(scale, scale);
	}

	void ql::border_graphic::set_texture(const sf::Texture& texture)
	{
		this->texture = &texture;
		this->texture_dimension = texture.getSize();
	}

	void ql::border_graphic::check_texture()
	{
		if (!this->texture)
		{
			throw ql::exception("ql::border_graphic : texture was not set.");
		}
	}

	void ql::border_graphic::update_dimensions(ql::vec2 position, ql::vec2 dimension)
	{
		this->dimension = dimension;
		this->position = position;
		this->sprites.clear();
	}

	void ql::border_graphic::move(ql::vec2 delta)
	{
		this->position += delta;
		for (auto& i : this->sprites)
		{
			i.move(delta);
		}
	}

	void ql::border_graphic::clear()
	{
		this->sprites.clear();
		this->position = ql::vec(0, 0);
	}

	void ql::border_graphic::add_top(ql::f32 correction_gap)
	{
		this->check_texture();

		auto x_size = ql::u32_cast(this->dimension.x / ((this->texture_dimension.x - 1) * this->scale.x) + 1);

		auto ctr = this->sprites.size();
		this->sprites.resize(ctr + x_size);

		auto pos = this->position;
		for (ql::u32 i = 0u; i < x_size; ++i)
		{
			this->sprites[ctr].set_texture(*this->texture);
			this->sprites[ctr].set_rotation(270.f);
			this->sprites[ctr].set_position(pos + ql::vec2(0, this->texture_dimension.x * (this->scale.x)));
			this->sprites[ctr].set_scale(this->scale);
			this->sprites[ctr].set_color(this->color);

			if (i == x_size - 1)
			{
				auto leftover = std::fmod(this->dimension.x, this->texture_dimension.x * this->scale.y) / this->scale.y;
				ql::hitbox hitbox;
				hitbox.dimension = {this->texture_dimension.x, leftover};
				this->sprites[ctr].set_texture_rect(hitbox);
			}

			pos.x += this->texture_dimension.x * this->scale.y + correction_gap;
			++ctr;
		}
	}

	void ql::border_graphic::add_bottom(ql::f32 correction_gap)
	{
		this->check_texture();

		auto x_size = ql::u32_cast(this->dimension.x / ((this->texture_dimension.x - 1) * this->scale.x) + 1);

		auto ctr = this->sprites.size();
		this->sprites.resize(ctr + x_size);

		auto pos = this->position + ql::vec2(0, this->dimension.y - this->texture_dimension.x);
		for (ql::u32 i = 0u; i < x_size; ++i)
		{
			this->sprites[ctr].set_texture(*this->texture);
			this->sprites[ctr].set_rotation(90.f);
			this->sprites[ctr].set_position(
					pos + ql::vec2(this->texture_dimension.x * this->scale.y, this->texture_dimension.x * (1 - this->scale.x))
			);
			this->sprites[ctr].set_scale(this->scale);
			this->sprites[ctr].set_color(this->color);

			if (i == x_size - 1)
			{
				auto leftover = std::fmod(this->dimension.x, this->texture_dimension.x * this->scale.y);
				ql::hitbox hitbox;
				hitbox.dimension = {this->texture_dimension.x, leftover / this->scale.y};

				this->sprites[ctr].move(ql::vec(-(this->texture_dimension.x * this->scale.y - leftover), 0));
				this->sprites[ctr].set_texture_rect(hitbox);
			}

			pos.x += this->texture_dimension.x * this->scale.y + correction_gap;
			++ctr;
		}
	}

	void ql::border_graphic::add_left(ql::f32 correction_gap)
	{
		this->check_texture();

		auto y_size = ql::u32_cast(this->dimension.y / ((this->texture_dimension.x - 1) * this->scale.y) + 1);

		auto ctr = this->sprites.size();
		this->sprites.resize(ctr + y_size);

		auto pos = this->position;
		for (ql::u32 i = 0u; i < y_size; ++i)
		{
			this->sprites[ctr].set_texture(*this->texture);
			this->sprites[ctr].set_rotation(180.f);
			this->sprites[ctr].set_position(
					pos + ql::vec2(this->texture_dimension.x * this->scale.x, this->texture_dimension.x * this->scale.y)
			);
			this->sprites[ctr].set_scale(this->scale);
			this->sprites[ctr].set_color(this->color);

			if (i == y_size - 1)
			{
				auto leftover = std::fmod(this->dimension.y, this->texture_dimension.y * this->scale.x);
				ql::hitbox hitbox;
				hitbox.dimension = {this->texture_dimension.x, leftover / this->scale.x};
				this->sprites[ctr].move(ql::vec(0, -(this->texture_dimension.y * this->scale.x - leftover)));
				this->sprites[ctr].set_texture_rect(hitbox);
			}

			pos.y += this->texture_dimension.x * this->scale.x + correction_gap;
			++ctr;
		}
	}

	void ql::border_graphic::add_right(ql::f32 correction_gap)
	{
		this->check_texture();

		auto y_size = ql::u32_cast(this->dimension.y / ((this->texture_dimension.x - 1) * this->scale.y) + 1);

		auto ctr = this->sprites.size();
		this->sprites.resize(ctr + y_size);

		auto pos = this->position + ql::vec2(this->dimension.x - this->texture_dimension.x, 0);
		for (ql::u32 i = 0u; i < y_size; ++i)
		{
			this->sprites[ctr].set_texture(*this->texture);
			this->sprites[ctr].set_position(pos + ql::vec2(this->texture_dimension.x * (1 - this->scale.y), 0));
			this->sprites[ctr].set_rotation(0.f);
			this->sprites[ctr].set_scale(this->scale);
			this->sprites[ctr].set_color(this->color);

			if (i == y_size - 1)
			{
				auto leftover = std::fmod(this->dimension.y, this->texture_dimension.y * this->scale.x);
				ql::hitbox hitbox;
				hitbox.dimension = {this->texture_dimension.x, leftover / this->scale.x};
				this->sprites[ctr].set_texture_rect(hitbox);
			}

			pos.y += this->texture_dimension.x * this->scale.x + correction_gap;
			++ctr;
		}
	}

	void ql::border_graphic::add_all_sides(ql::f32 correction_gap)
	{
		this->add_top(correction_gap);
		this->add_left(correction_gap);
		this->add_right(correction_gap);
		this->add_bottom(correction_gap);
	}

	void ql::border_graphic::draw(ql::draw_object& object) const
	{
		object.draw(this->sprites);
	}

	namespace
	{
		void add_line(
				ql::vertex_array& vertices,
				ql::f32 line_length,
				ql::f32 lineTop,
				const ql::rgba& color,
				ql::f32 offset,
				ql::f32 thickness,
				ql::f32 outline_thickness = 0
		)
		{
			ql::f32 top = std::floor(lineTop + offset - (thickness / 2) + 0.5f);
			ql::f32 bottom = top + std::floor(thickness + 0.5f);

			vertices.add(ql::vertex(ql::vec2f(-outline_thickness, top - outline_thickness), color, ql::vec2f(1, 1)));
			vertices.add(ql::vertex(ql::vec2f(line_length + outline_thickness, top - outline_thickness), color, ql::vec2f(1, 1)));
			vertices.add(ql::vertex(ql::vec2f(-outline_thickness, bottom + outline_thickness), color, ql::vec2f(1, 1)));
			vertices.add(ql::vertex(ql::vec2f(-outline_thickness, bottom + outline_thickness), color, ql::vec2f(1, 1)));
			vertices.add(ql::vertex(ql::vec2f(line_length + outline_thickness, top - outline_thickness), color, ql::vec2f(1, 1)));
			vertices.add(ql::vertex(ql::vec2f(line_length + outline_thickness, bottom + outline_thickness), color, ql::vec2f(1, 1)));
		}

		glyph_quad get_glyph_quad(const sf::Glyph& glyph, ql::f32 italic_shear)
		{
			ql::f32 padding = 1.0;

			ql::f32 left = glyph.bounds.left - padding;
			ql::f32 top = glyph.bounds.top - padding;
			ql::f32 right = glyph.bounds.left + glyph.bounds.width + padding;
			ql::f32 bottom = glyph.bounds.top + glyph.bounds.height + padding;

			ql::f32 u1 = ql::f32_cast(glyph.textureRect.left) - padding;
			ql::f32 v1 = ql::f32_cast(glyph.textureRect.top) - padding;
			ql::f32 u2 = ql::f32_cast(glyph.textureRect.left + glyph.textureRect.width) + padding;
			ql::f32 v2 = ql::f32_cast(glyph.textureRect.top + glyph.textureRect.height) + padding;

			ql::size ctr = 0u;
			glyph_quad result;
			result[0u] = glyph_quad_vertex{ql::vec2f(left - italic_shear * top, top), ql::vec2f(u1, v1)};
			result[1u] = glyph_quad_vertex{ql::vec2f(right - italic_shear * top, top), ql::vec2f(u2, v1)};
			result[2u] = glyph_quad_vertex{ql::vec2f(left - italic_shear * bottom, bottom), ql::vec2f(u1, v2)};
			result[3u] = glyph_quad_vertex{ql::vec2f(left - italic_shear * bottom, bottom), ql::vec2f(u1, v2)};
			result[4u] = glyph_quad_vertex{ql::vec2f(right - italic_shear * top, top), ql::vec2f(u2, v1)};
			result[5u] = glyph_quad_vertex{ql::vec2f(right - italic_shear * bottom, bottom), ql::vec2f(u2, v2)};
			return result;
		}

		// Add a glyph quad to the vertex array
		void add_glyph_quad(
				ql::vertex_array& vertices,
				ql::vec2f position,
				const ql::rgba& color,
				const sf::Glyph& glyph,
				ql::f32 italic_shear
		)
		{
			auto quad = get_glyph_quad(glyph, italic_shear);

			for (auto& i : quad)
			{
				ql::vertex vertex;
				vertex.position = i.position + position;
				vertex.tex_coords = i.tex_coord;
				vertex.color = color;
				vertices.add(vertex);
			}
		}

		void add_background_quad(ql::vertex_array& vertices, ql::hitbox hitbox, const ql::rgba& color)
		{
			std::vector<ql::vec2> positions;
			positions.push_back(hitbox.get_side_corner(0u));
			positions.push_back(hitbox.get_side_corner(1u));
			positions.push_back(hitbox.get_side_corner(3u));
			positions.push_back(hitbox.get_side_corner(1u));
			positions.push_back(hitbox.get_side_corner(2u));
			positions.push_back(hitbox.get_side_corner(3u));

			for (auto& pos : positions)
			{
				ql::vertex vertex;
				vertex.position = pos;
				vertex.color = color;
				vertices.add(vertex);
			}
		}
	}	 // namespace

	ql::colored_text::colored_text()
	{
		this->clear();
	}

	ql::colored_text::colored_text(const ql::colored_text&) = default;
	ql::colored_text& ql::colored_text::operator=(const ql::colored_text&) = default;
	ql::colored_text::colored_text(ql::colored_text&&) noexcept = default;
	ql::colored_text& ql::colored_text::operator=(ql::colored_text&&) noexcept = default;

	void ql::colored_text::set_font(const sf::Font& font)
	{
		this->font = &font;
	}

	void ql::colored_text::set_unicode_font(const sf::Font& font)
	{
		this->unicode_font = &font;
	}

	void ql::colored_text::set_character_size(ql::u32 size)
	{
		this->character_size = size;
	}

	void ql::colored_text::set_letter_spacing(ql::f32 spacingFactor)
	{
		this->letter_spacing_factor = spacingFactor;
	}

	void ql::colored_text::set_line_spacing(ql::f32 spacingFactor)
	{
		this->line_spacing_factor = spacingFactor;
	}

	void ql::colored_text::set_style(ql::u32 style)
	{
		this->style = style;
	}

	ql::u32 ql::colored_text::get_character_size() const
	{
		return this->character_size;
	}

	ql::f32 ql::colored_text::get_line_spacing() const
	{
		return this->line_spacing_factor;
	}

	ql::f32 ql::colored_text::get_line_spacing_pixels() const
	{
		return this->font->getLineSpacing(this->character_size) * this->line_spacing_factor;
	}

	ql::f32 ql::colored_text::get_outline_thickness() const
	{
		return this->outline_thickness;
	}

	ql::f32 ql::colored_text::get_white_space_width() const
	{
		auto whitespace_width = this->font->getGlyph(U' ', this->character_size, false).advance;
		auto letter_spacing = (whitespace_width / 3.f) * (this->letter_spacing_factor - 1.f);
		return whitespace_width + letter_spacing;
	}

	ql::f32 ql::colored_text::get_underline_position() const
	{
		return this->font->getUnderlinePosition(this->character_size);
	}

	ql::f32 ql::colored_text::get_chracter_top_offset() const
	{
		return this->character_size + this->font->getGlyph(U'A', this->character_size, false).bounds.top;
	}

	const sf::Glyph& ql::colored_text::get_glyph(ql::u32 character, ql::u32 character_size, bool is_bold, ql::f32 outline_thickness)
	{
		return this->font->getGlyph(character, character_size, is_bold, outline_thickness);
	}

	const sf::Glyph&
	ql::colored_text::get_unicode_glyph(ql::u32 character, ql::u32 character_size, bool is_bold, ql::f32 outline_thickness)
	{
		return this->unicode_font->getGlyph(character, character_size, is_bold, outline_thickness);
	}

	ql::u32 ql::colored_text::get_style() const
	{
		return this->style;
	}

	void ql::colored_text::clear()
	{
		this->vertices.clear();
		this->outline_vertices.clear();
		this->unicode_vertices.clear();
		this->unicode_outline_vertices.clear();
		this->text_position.x = 0.f;
		this->text_position.y = 0.f;
		this->rows = 0u;
	}

	void ql::colored_text::pop_last_character()
	{
		if (this->last_element.style & sf::Text::Style::Bold)
		{
			this->outline_vertices.resize(ql::max(0ll, ql::signed_cast(this->outline_vertices.size()) - 6));
		}
		this->vertices.resize(ql::max(0ll, ql::signed_cast(this->vertices.size()) - 6));
	}

	void ql::colored_text::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (this->font)
		{
			sf::RenderStates new_states{states};

			new_states.texture = &this->font->getTexture(this->character_size);

			if (this->outline_vertices.size())
			{
				this->outline_vertices.draw(target, new_states);
			}

			this->vertices.draw(target, new_states);
		}
		if (this->unicode_font)
		{
			sf::RenderStates new_states{states};

			new_states.texture = &this->unicode_font->getTexture(this->character_size);

			if (this->unicode_outline_vertices.size())
			{
				this->unicode_outline_vertices.draw(target, new_states);
			}

			this->unicode_vertices.draw(target, new_states);
		}
	}

	void ql::colored_text::create(const ql::styled_string<ql::u32_string>& string, ql::f32 visible_y_min, ql::f32 visible_y_max)
	{
		this->clear();
		this->add(string, visible_y_min, visible_y_max);
	}

	void ql::colored_text::add(const ql::styled_string<ql::u32_string>& string, ql::f32 visible_y_min, ql::f32 visible_y_max)
	{
		if (!this->font)
		{
			ql::println(" ql::colored_text::add : no font set!");
			return;
		}

		this->hitbox = ql::hitbox{};

		if (string.empty())
		{
			return;
		}
		auto underline_offset = this->font->getUnderlinePosition(this->character_size);
		auto underline_thickness = this->font->getUnderlineThickness(this->character_size);

		auto line_spacing = this->get_line_spacing_pixels();

		if (this->text_position.y == 0.f)
		{
			this->text_position.y = this->font->getLineSpacing(this->character_size);
		}

		auto minX = ql::f32_cast(this->character_size);
		auto minY = 0.f;
		auto maxX = 0.f;
		auto maxY = 0.f;
		ql::u32 previous = 0;

		auto Xglyph = this->get_glyph(L'x', this->character_size, false);
		auto delta_underline = Xglyph.bounds.top + Xglyph.bounds.height;

		this->last_element.copy_style(string.elements.back());
		for (auto& element : string)
		{
			bool is_bold = element.style & sf::Text::Style::Bold;
			bool is_underlined = element.style & sf::Text::Style::Underlined;
			bool is_strike_through = element.style & sf::Text::Style::StrikeThrough;
			auto italic_shear = (element.style & sf::Text::Style::Italic) ? 0.2094395102393f : 0.f;

			const auto& default_glyph = this->get_glyph(U'x', this->character_size, is_bold);
			sf::FloatRect default_bounds = default_glyph.bounds;

			sf::Glyph default_unicode_glyph;
			if (this->unicode_font)
			{
				default_unicode_glyph = this->get_unicode_glyph(U'x', this->character_size, is_bold);
			}

			auto unreadable_glyph_texture = this->get_glyph(63744u, this->character_size, is_bold).textureRect;

			auto strike_through_offset = default_bounds.top + default_bounds.height / 2.f;
			auto whitespace_width = this->font->getGlyph(U' ', this->character_size, is_bold).advance;
			auto letter_spacing = (whitespace_width / 3.f) * (this->letter_spacing_factor - 1.f);
			whitespace_width += letter_spacing;

			for (ql::size i = 0u; i < element.text.length(); ++i)
			{
				ql::u32 c = element.text[i];

				if (c == U'\r')
				{
					continue;
				}

				sf::Glyph character_glyph;
				character_glyph = this->get_glyph(c, this->character_size, is_bold);
				auto glyph_bounds = character_glyph.textureRect;

				bool is_unicode_character = false;
				if (this->unicode_font && glyph_bounds.left == unreadable_glyph_texture.left &&
						glyph_bounds.top == unreadable_glyph_texture.top && glyph_bounds.width == unreadable_glyph_texture.width &&
						glyph_bounds.height == unreadable_glyph_texture.height)
				{
					character_glyph = this->get_unicode_glyph(c, this->character_size, is_bold);

					auto factor = character_glyph.advance / default_unicode_glyph.advance;
					if (factor >= 1.5)
					{
						character_glyph.advance = default_glyph.advance * 2u;
					}
					else
					{
						character_glyph.advance = default_glyph.advance;
					}

					is_unicode_character = true;
				}

				ql::f32 left = character_glyph.bounds.left;
				ql::f32 top = character_glyph.bounds.top;
				ql::f32 right = character_glyph.bounds.left + character_glyph.bounds.width;
				ql::f32 bottom = character_glyph.bounds.top + character_glyph.bounds.height;

				minX = std::min(minX, this->text_position.x + left - italic_shear * bottom);
				maxX = std::max(maxX, this->text_position.x + right - italic_shear * top);
				minY = std::min(minY, this->text_position.y + top);
				maxY = std::max(maxY, this->text_position.y + bottom);

				if (element.background_color.a)
				{
					ql::hitbox background_hitbox;
					background_hitbox.position.x = this->text_position.x;
					background_hitbox.position.y =
							this->text_position.y - this->character_size + underline_offset - this->character_size / 10.f;

					background_hitbox.dimension = ql::vec2(character_glyph.advance + letter_spacing, line_spacing);

					add_background_quad(this->vertices, background_hitbox, element.background_color);
				}

				this->text_position.x += this->font->getKerning(previous, c, this->character_size);
				if (is_underlined && (c == U'\n' && previous != U'\n'))
				{
					add_line(
							this->vertices, this->text_position.x, this->text_position.y, element.color, underline_offset, underline_thickness
					);

					if (element.outline_thickness != 0)
					{
						add_line(
								this->outline_vertices, this->text_position.x, this->text_position.y, element.outline_color, underline_offset,
								underline_thickness, element.outline_thickness
						);
					}
				}
				if (is_strike_through && (c == U'\n' && previous != U'\n'))
				{
					add_line(
							this->vertices, this->text_position.x, this->text_position.y, element.color, strike_through_offset,
							underline_thickness
					);

					if (element.outline_thickness != 0)
					{
						add_line(
								this->outline_vertices, this->text_position.x, this->text_position.y, element.outline_color,
								strike_through_offset, underline_thickness, element.outline_thickness
						);
					}
				}

				previous = c;

				if ((c == U' ') || (c == U'\n') || (c == U'\t'))
				{
					minX = std::min(minX, this->text_position.x);
					minY = std::min(minY, this->text_position.y);

					switch (c)
					{
						case U' ':
							this->text_position.x += whitespace_width;
							break;
						case U'\t':
							this->text_position.x += whitespace_width * 4;
							break;
						case U'\n':
							this->text_position.y += line_spacing;
							this->text_position.x = 0;
							++this->rows;
							break;
					}

					maxX = std::max(maxX, this->text_position.x);
					maxY = std::max(maxY, this->text_position.y);
					continue;
				}

				bool in_range =
						(this->text_position.y - line_spacing) > visible_y_min && (text_position.y + line_spacing) < visible_y_max;

				if (in_range && element.outline_thickness != 0)
				{
					sf::Glyph glyph;
					// if (this->unicode_font && ql::unicode_character_length(c) == 2u)
					if (this->unicode_font)
					{
						glyph = this->get_unicode_glyph(c, this->character_size, is_bold, element.outline_thickness);
						if (in_range)
						{
							add_glyph_quad(this->unicode_outline_vertices, this->text_position, element.outline_color, glyph, italic_shear);
						}
					}
					else
					{
						glyph = this->get_glyph(c, this->character_size, is_bold, element.outline_thickness);
						if (in_range)
						{
							add_glyph_quad(this->outline_vertices, this->text_position, element.outline_color, glyph, italic_shear);
						}
					}
				}

				if (in_range)
				{
					if (is_unicode_character)
					{
						add_glyph_quad(this->unicode_vertices, this->text_position, element.color, character_glyph, italic_shear);
					}
					else
					{
						add_glyph_quad(this->vertices, this->text_position, element.color, character_glyph, italic_shear);
					}
				}

				this->text_position.x += character_glyph.advance + letter_spacing;
			}
		}

		this->hitbox.position.x = minX;
		this->hitbox.position.y = 0;
		this->hitbox.dimension.x = maxX - minX;
		this->hitbox.dimension.y = maxY - minY;
	}

	std::unordered_map<std::string, ql::text> ql::detail::texts;

	ql::text& ql::get_text(const std::string& name)
	{
		if (ql::detail::texts.find(name) == ql::detail::texts.cend())
		{
			ql::add_text();
		}
		return ql::detail::texts[name];
	}

	void ql::add_text(const std::string& name)
	{
		if (ql::detail::texts.find(name) == ql::detail::texts.cend())
		{
			if (ql::detail::texts.size())
			{
				ql::detail::texts[name] = ql::detail::texts.begin()->second;
			}
			else if (ql::detail::resources.fonts.size())
			{
				ql::detail::texts[name].set_font(ql::detail::resources.fonts.begin()->first);
			}
		}
	}
}	 // namespace ql
#endif
