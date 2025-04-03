#pragma once

#include <ql/core/definition/definition.hpp>
#if defined QL_GRAPHIC

#include <ql/graphic/event/event.hpp>
#include <ql/graphic/drawable/drawable.hpp>
#include <ql/graphic/old-drawable/drawables.hpp>

#include <ql/core/advanced-type/advanced-type.hpp>
#include <ql/core/string/styled-string.hpp>

#include <ql/graphic/drawable/advanced/smooth-rectangle/smooth-rectangle.hpp>

namespace ql
{

	struct button;

	namespace detail
	{
		QL_SOURCE extern ql::button button;
	}

	struct vbutton
	{
		vbutton()
		{
			this->background.set_color(ql::rgba::black());
		}

		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_center(ql::vec2 center);
		QL_SOURCE void set_background_color(ql::rgba color);
		QL_SOURCE void set_hover_background_color(ql::rgba color);
		QL_SOURCE void set_text_color(ql::rgba color);
		QL_SOURCE void set_hover_text_color(ql::rgba color);
		QL_SOURCE void set_text_font(std::string font);
		QL_SOURCE void set_text_character_size(ql::u32 character_size);
		QL_SOURCE void set_text_style(ql::u32 character_style);
		QL_SOURCE void set_text(std::string text);
		QL_SOURCE void centerize_text();
		QL_SOURCE bool is_hovering() const;
		QL_SOURCE bool is_clicked() const;
		QL_SOURCE void update(const event& event);
		QL_SOURCE void set_text_alpha(ql::u8 alpha);
		QL_SOURCE void set_background_alpha(ql::u8 alpha);

		template <typename T>
		void update(const event& event)
		{
			auto pos = event.mouse_position();

			auto new_hovering = this->background.collides(pos);
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

			this->clicked = this->hovering && event.left_mouse_clicked();
		}

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE ql::vbutton& operator=(const ql::vbutton& button);

		ql::rgba text_color;
		ql::rgba hover_text_color = ql::rgba::unset();
		ql::rgba hover_background_color = ql::rgba::unset();
		ql::rgba background_color;
		ql::vtext text;
		ql::vrectangle background;
		bool hovering = false;
		bool clicked = false;
		bool outline_on_hover = true;
		bool invert_on_hover = true;
		ql::u8 text_alpha = 255;
		ql::u8 background_alpha = 255;
	};

	struct button
	{
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE ql::button& operator=(const ql::vbutton& button);

		button()
		{
			this->background.set_color(ql::rgba::black());
		}

		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_center(ql::vec2 center);
		QL_SOURCE void set_background_color(ql::rgba color);
		QL_SOURCE void set_hover_background_color(ql::rgba color);
		QL_SOURCE void set_text_color(ql::rgba color);
		QL_SOURCE void set_text_font(std::string font);
		QL_SOURCE void set_text_character_size(ql::u32 character_size);
		QL_SOURCE void set_text_style(ql::u32 character_style);
		QL_SOURCE void set_text_string(std::string text);
		QL_SOURCE void set_text_string(std::wstring text);

		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE ql::rgba get_background_color() const;
		QL_SOURCE ql::rgba get_hover_background_color() const;
		QL_SOURCE ql::rgba get_text_color() const;
		QL_SOURCE std::string get_text_font() const;
		QL_SOURCE ql::u32 get_text_character_size() const;
		QL_SOURCE ql::u32 get_text_style() const;
		QL_SOURCE std::string get_text_string() const;
		QL_SOURCE std::wstring get_text_wstring() const;
		QL_SOURCE void centerize_text();
		QL_SOURCE bool is_hovering() const;
		QL_SOURCE bool is_clicked() const;
		QL_SOURCE void update(const event& event);
		QL_SOURCE void update(const event& event, bool& hovering);

		template <typename T>
		void update(const event& event)
		{
			auto pos = event.mouse_position();

			auto new_hovering = this->background.get_hitbox().collides(pos);
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

			this->clicked = this->hovering && event.left_mouse_clicked();
		}

		bool outline_on_hover = true;
		bool invert_on_hover = true;
		ql::rgba text_color = ql::rgba::white();
		ql::rgba hover_background_color = ql::rgba::white();
		ql::rgba background_color = ql::rgba::black();
		ql::text text;
		ql::rectangle background;
		bool hovering = false;
		bool clicked = false;
	};

	struct text_field
	{
		struct line
		{
			mutable ql::text text;
			std::vector<ql::hitbox> character_hitboxes;
			std::vector<ql::hitbox> character_mouse_hitboxes;
			ql::hitbox line_hitbox;
			ql::hitbox line_mouse_hitbox;
			bool mouse_hitboxes_changed = false;
			bool layout_changed = false;
			bool hidden = false;

			QL_SOURCE void apply(ql::vtext layout);
			QL_SOURCE void calculate_hitboxes();
			QL_SOURCE void calculate_mouse_hitboxes(ql::f32 max_line_width, ql::f32 extended_line_width);
			QL_SOURCE void move(ql::vec2 delta);
			QL_SOURCE void move(ql::f32 x, ql::f32 y);
			QL_SOURCE void set_string(std::wstring text);
			QL_SOURCE std::wstring wstring() const;
			QL_SOURCE void draw(ql::render& draw) const;
		};

		text_field(bool hidden = false);

		QL_SOURCE void reset();
		QL_SOURCE void set_font(std::string font);
		QL_SOURCE void set_text_character_size(ql::u32 character_size);
		QL_SOURCE void set_text_style(ql::u32 style);
		QL_SOURCE void set_text_outline_thickness(ql::f32 outline_thickness);
		QL_SOURCE void set_text_outline_color(ql::rgba outline_color);
		QL_SOURCE void set_text_color(ql::rgba color);

		QL_SOURCE ql::hitbox get_hitbox() const;
		QL_SOURCE ql::hitbox get_background_hitbox() const;

		QL_SOURCE void set_background_color(ql::rgba color);
		QL_SOURCE void set_background_increase(ql::vec2 increase);
		QL_SOURCE void set_background_increase(ql::f32 increase);
		QL_SOURCE void set_background_outline_thickness(ql::f32 thickness);
		QL_SOURCE void set_background_outline_color(ql::rgba color);
		QL_SOURCE ql::rgba get_background_color() const;
		QL_SOURCE ql::rgba get_background_outline_color() const;
		QL_SOURCE ql::f32 get_background_outline_thickness() const;
		QL_SOURCE ql::vec2 get_background_increase() const;

		QL_SOURCE void set_minimum_dimension(ql::vec2 dimension);
		QL_SOURCE void set_minimum_width(ql::f32 width);
		QL_SOURCE void set_minimum_height(ql::f32 height);
		QL_SOURCE void set_maximum_dimension(ql::vec2 dimension);
		QL_SOURCE void set_maximum_width(ql::f32 width);
		QL_SOURCE void set_maximum_height(ql::f32 height);
		QL_SOURCE void set_fixed_dimension(ql::vec2 dimension);
		QL_SOURCE void set_fixed_width(ql::f32 width);
		QL_SOURCE void set_fixed_height(ql::f32 height);

		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_hitbox(ql::hitbox hitbox);
		QL_SOURCE void move(ql::vec2f delta);

		QL_SOURCE void set_string(std::wstring string);
		QL_SOURCE void set_string(std::string string);

		QL_SOURCE ql::f32 get_line_height() const;
		QL_SOURCE bool is_hovering() const;

		QL_SOURCE bool just_edited_text() const;
		QL_SOURCE bool just_copied_text() const;
		QL_SOURCE bool just_pasted_text() const;
		QL_SOURCE bool just_entered_text() const;
		QL_SOURCE bool just_finished_text() const;
		QL_SOURCE bool has_focus() const;

		QL_SOURCE std::wstring wstring() const;
		QL_SOURCE std::string string() const;

		QL_SOURCE std::string get_font() const;
		QL_SOURCE bool is_font_set() const;

		QL_SOURCE void new_line(ql::size y = ql::size_max);
		QL_SOURCE ql::text_field::line& get_line_at_cursor();
		QL_SOURCE const ql::text_field::line& get_line_at_cursor() const;

		QL_SOURCE std::wstring get_selection_wstring() const;
		QL_SOURCE std::string get_selection_string() const;
		QL_SOURCE void add_string_at_cursor(std::wstring string);

		QL_SOURCE void enable_focus();
		QL_SOURCE void disable_focus();

		QL_SOURCE void enable_one_line_limit();
		QL_SOURCE void set_line_limit(ql::size limit);
		QL_SOURCE void disable_one_line_limit();

		QL_SOURCE void set_string_stack_size(ql::size size);
		QL_SOURCE ql::size get_string_stack_size() const;

		QL_SOURCE bool is_dragging_selection_considering_cooldown() const;

		QL_SOURCE void delete_at_cursor();
		QL_SOURCE void delete_selection_string(bool update_cursor_position = true);
		QL_SOURCE void delete_selection_range();
		QL_SOURCE void move_cursor_up();
		QL_SOURCE void move_cursor_down();
		QL_SOURCE void move_cursor_left();
		QL_SOURCE void move_cursor_right();
		QL_SOURCE void update_cursor();
		QL_SOURCE void update_selection_rectangles();
		QL_SOURCE void update_mouse_events(const ql::event& event);

		QL_SOURCE void update(const ql::event& event);
		QL_SOURCE void draw(ql::render& draw) const;

		QL_SOURCE std::pair<ql::vector2s, ql::vector2s> get_sorted_selection_range() const;
		QL_SOURCE void internal_update() const;
		QL_SOURCE void internal_update_text() const;
		QL_SOURCE void internal_update_cursor();
		QL_SOURCE void set_cursor_dimension() const;
		QL_SOURCE void set_cursor_position();
		QL_SOURCE void make_selection_rectangles() const;
		QL_SOURCE void make_selection_rectangles(ql::size& count, ql::size y, ql::size x1, ql::size x2 = ql::size_max) const;
		QL_SOURCE void find_closest_cursor_position();
		QL_SOURCE bool just_changed() const;
		QL_SOURCE void update_all_changes();
		QL_SOURCE void set_scale(ql::vec2 scale);

		ql::vtext text_layout;
		mutable ql::hitbox hitbox;
		mutable ql::vector<line> lines;
		mutable ql::smooth_rectangle background;
		mutable ql::rectangle cursor;
		mutable std::vector<ql::rectangle> selection_rectangles;
		mutable std::wstring whole_string;

		ql::circular_array<std::pair<std::wstring, ql::vector2s>> string_stack;

		ql::vector2s cursor_position = ql::vec(0u, 0u);
		ql::vector2s selection_a = ql::vec(0u, 0u);
		ql::vector2s selection_b = ql::vec(0u, 0u);
		ql::vec2 background_increase = ql::vec(6.0f, 6.0f);
		ql::vec2 click_mouse_position = ql::vec(0, 0);
		ql::vec2 hovering_increase = ql::vec(5, 5);

		ql::small_clock selection_drag_timer;
		ql::small_clock selection_start_drag_timer;
		ql::small_clock cursor_interval_timer;
		ql::halted_clock double_click_cooldown;
		ql::f64 selection_drag_timer_duration = 0.15;
		ql::f64 selection_start_drag_timer_duration = 0.15;

		ql::rgba selection_color = ql::rgb(0, 117, 210);
		ql::rgba dragging_color = ql::rgb(200, 150, 0);

		ql::size string_stack_position = 0u;
		ql::f64 cursor_interval_duration = 1.0;
		ql::f64 cursor_blink_duration = 0.5;
		ql::f32 cursor_x_offset = 0.3f;
		ql::f32 cursor_width_percentage = 0.1f;

		ql::vec2f minimum_dimension = {0, 0};
		ql::vec2f maximum_dimension = {ql::f64_max, ql::f64_max};
		ql::vec2 scale = {1, 1};

		ql::size line_limit = ql::size_max;

		bool hovering = false;
		bool dragging = false;
		bool dragging_selection = false;
		bool dragging_selection_before = false;
		bool hidden = false;
		bool edited_text = false;
		bool copied_text = false;
		bool pasted_text = false;
		bool entered_text = false;
		bool pressed_enter_key = false;
		bool ignore_pressing_enter_key = false;
		bool focus = false;
		bool finished_text = false;
		bool control_z = false;
		bool control_y = false;
		bool changed = false;

	 private:
		mutable bool text_mouse_hitboxes_changed = false;
		mutable bool text_layout_changed = false;
		mutable bool update_required = false;
		mutable bool whole_string_changed = true;
		mutable bool cursor_position_changed = false;
	};

	template <typename T>
	class slider
	{
	 public:
		slider()
		{
			this->ptr = &this->dummy;
			this->set_colors(ql::rgba::grey_shade(50), ql::rgba::white());
		}

		slider(const slider<T>& other)
		{
			*this = other;
		}

		template <typename U>
		slider(const slider<U>& other)
		{
			*this = other;
		}

		slider<T>& operator=(const slider<T>& other)
		{
			this->background = other.background;
			this->knob = other.knob;
			this->position = other.position;
			this->knob_visible = other.knob_visible;
			this->background_visible = other.background_visible;
			this->knob_hover_effect = other.knob_hover_effect;
			this->background_hover_effect = other.background_hover_effect;
			this->knob_hover_color = other.knob_hover_color;
			this->knob_hover_outline_thickness = other.knob_hover_outline_thickness;
			this->knob_hover_outline_color = other.knob_hover_outline_color;
			this->hitbox_increase = other.hitbox_increase;
			this->background_hover_color = other.background_hover_color;
			this->background_hover_outline_thickness = other.background_hover_outline_thickness;
			this->background_hover_outline_color = other.background_hover_outline_color;
			this->start = other.start;
			this->end = other.end;
			this->dummy = other.dummy;
			this->value_before = other.value_before;
			this->background_color = other.background_color;
			this->background_outline_thickness = other.background_outline_thickness;
			this->background_outline_color = other.background_outline_color;
			this->knob_color = other.knob_color;
			this->knob_outline_thickness = other.knob_outline_thickness;
			this->knob_outline_color = other.knob_outline_color;
			this->smooth_input_key = other.smooth_input_key;
			this->smooth_input_multiply = other.smooth_input_multiply;
			this->click_knob_pos_x = other.click_knob_pos_x;
			this->click_pos_x = other.click_pos_x;
			this->range_pixel_width = other.range_pixel_width;
			this->hovering_over_background = other.hovering_over_background;
			this->click_on_background_to_skip = other.click_on_background_to_skip;
			this->input_smooth_values = other.input_smooth_values;
			this->value_changed = other.value_changed;
			this->value_modified = other.value_modified;
			this->range_set = other.range_set;
			this->allow_change = other.allow_change;
			this->allow_drag = other.allow_drag;
			this->dragging = other.dragging;
			this->released = other.released;
			this->hovering_over_knob = other.hovering_over_knob;
			this->ptr = &this->dummy;
			this->string_function = other.string_function;
			this->text = other.text;

			return *this;
		}

		template <typename U>
		slider<T>& operator=(const slider<U>& other)
		{
			this->background = other.background;
			this->knob = other.knob;
			this->position = other.position;
			this->knob_visible = other.knob_visible;
			this->background_visible = other.background_visible;
			this->knob_hover_effect = other.knob_hover_effect;
			this->background_hover_effect = other.background_hover_effect;
			this->knob_hover_color = other.knob_hover_color;
			this->knob_hover_outline_thickness = other.knob_hover_outline_thickness;
			this->knob_hover_outline_color = other.knob_hover_outline_color;
			this->hitbox_increase = other.hitbox_increase;
			this->background_hover_color = other.background_hover_color;
			this->background_hover_outline_thickness = other.background_hover_outline_thickness;
			this->background_hover_outline_color = other.background_hover_outline_color;
			this->start = static_cast<T>(other.start);
			this->end = static_cast<T>(other.end);
			this->dummy = static_cast<T>(other.dummy);
			this->value_before = static_cast<T>(other.value_before);
			this->background_color = other.background_color;
			this->background_outline_thickness = other.background_outline_thickness;
			this->background_outline_color = other.background_outline_color;
			this->knob_color = other.knob_color;
			this->knob_outline_thickness = other.knob_outline_thickness;
			this->knob_outline_color = other.knob_outline_color;
			this->smooth_input_key = other.smooth_input_key;
			this->smooth_input_multiply = other.smooth_input_multiply;
			this->click_knob_pos_x = other.click_knob_pos_x;
			this->click_pos_x = other.click_pos_x;
			this->range_pixel_width = other.range_pixel_width;
			this->hovering_over_background = other.hovering_over_background;
			this->click_on_background_to_skip = other.click_on_background_to_skip;
			this->input_smooth_values = other.input_smooth_values;
			this->value_changed = other.value_changed;
			this->value_modified = other.value_modified;
			this->range_set = other.range_set;
			this->allow_change = other.allow_change;
			this->allow_drag = other.allow_drag;
			this->dragging = other.dragging;
			this->released = other.released;
			this->hovering_over_knob = other.hovering_over_knob;
			this->ptr = &this->dummy;
			this->string_function = other.string_function;
			this->text = other.text;

			return *this;
		}

		ql::f64 get_progress() const
		{
			if (this->end == this->start)
				return 0.0;
			return ql::clamp(ql::f64_cast(*this->ptr - this->start) / ql::f64_cast(this->end - this->start));
		}

		T get_value() const
		{
			return *this->ptr;
		}

		void set_value(T value)
		{
			*this->ptr = value;
		}

		void set_pointer(T* value)
		{
			this->ptr = value;
			if (this->range_set)
			{
				*this->ptr = ql::clamp(this->start, *this->ptr, this->end);
			}
		}

		void set_knob_position()
		{
			auto progress = ql::f32_cast(this->get_progress());
			auto pos = this->knob.get_position();
			pos.x = this->position.x + this->range_pixel_width * progress;
			this->knob.set_position(pos);
		}

		std::pair<T, T> get_range() const
		{
			return std::make_pair(this->start, this->end);
		}

		void update_text_string()
		{
			if (!this->text.get_font().empty())
			{
				if (this->string_function)
				{
					this->text.set_string(ql::to_string(this->text_string, " ", this->string_function(this->get_value())));
				}
				else
				{
					this->text.set_string(ql::to_string(this->text_string, " ", this->get_value()));
				}
			}
		}

		void set_range(T start, T end)
		{
			this->start = start;
			this->end = end;
			this->range_set = true;
			this->update_text_string();
		}

		void set_range(T start, T end, T value)
		{
			this->start = start;
			this->end = end;
			this->dummy = ql::clamp(this->start, value, this->end);
			this->range_set = true;
			this->update_text_string();
		}

		template <typename P>
		requires (std::is_pointer_v<P>)
		void set_range(T start, T end, P ptr)
		{
			this->start = start;
			this->end = end;
			this->range_set = true;
			this->set_pointer(ptr);
			this->update_text_string();
		}

		ql::vec2 get_position() const
		{
			return this->position;
		}

		void set_position(ql::vec2 position)
		{
			this->position = position;
			this->background.set_position(position);

			auto y_extra = this->background.get_dimension().y - this->knob.get_dimension().y;
			this->knob.set_position(position + ql::vec2(0, y_extra / 2));
			this->set_knob_position();

			if (!this->text.get_font().empty())
			{
				this->text.set_position(this->background.get_hitbox().get_left_center());
				this->text.centerize_y();
			}
		}

		void set_center(ql::vec2 position)
		{
			this->set_position(position - this->get_dimension() / 2);
		}

		ql::vec2 get_dimension() const
		{
			return this->background.get_dimension();
		}

		ql::hitbox get_hitbox() const
		{
			return this->background.get_hitbox();
		}

		ql::vec2 get_knob_dimension() const
		{
			return this->knob.get_dimension();
		}

		ql::vec2 get_knob_position() const
		{
			return this->knob.get_position();
		}

		void set_knob_dimension(ql::vec2 dimension)
		{
			this->knob.set_dimension(dimension);
			this->range_pixel_width = this->background.get_dimension().x - this->knob.get_dimension().x;
		}

		void set_knob_width(ql::f32 width)
		{
			auto dim = this->knob.get_dimension();
			this->knob.set_dimension(ql::vec2(width, dim.y));
			this->range_pixel_width = this->background.get_dimension().x - width;
		}

		ql::f32 get_knob_width() const
		{
			return this->knob.get_dimension().x;
		}

		ql::hitbox get_knob_hitbox() const
		{
			return this->knob.get_hitbox();
		}

		void set_dimensions(ql::vec2 slider_dimension, ql::vec2 knob_dimension)
		{
			this->background.set_dimension(slider_dimension);
			this->knob.set_dimension(knob_dimension);
			this->range_pixel_width = this->background.get_dimension().x - this->knob.get_dimension().x;
		}

		void set_dimension(ql::vec2 dimension)
		{
			this->set_dimensions(dimension, sf::Vector2f(dimension.y, dimension.y));
		}

		void set_colors(ql::rgba background_color, ql::rgba knob_color)
		{
			this->background.set_color(background_color);
			this->background_color = background_color;
			this->background_hover_color = background_color;
			this->background_hover_outline_color = background_color;

			this->knob.set_color(knob_color);
			this->knob_hover_color = knob_color;
			this->knob_hover_outline_color = knob_color;
			this->knob_color = knob_color;
		}

		void set_alpha(ql::u8 alpha)
		{
			this->background.set_color(this->background.get_color().with_alpha(alpha));
			this->background_color = this->background_color.with_alpha(alpha);
			this->background_hover_color = this->background_hover_color.with_alpha(alpha);
			this->background_hover_outline_color = this->background_hover_outline_color.with_alpha(alpha);

			this->knob.set_color(this->knob.get_color().with_alpha(alpha));
			this->knob_hover_color = this->knob_hover_color.with_alpha(alpha);
			this->knob_hover_outline_color = this->knob_hover_outline_color.with_alpha(alpha);
			this->knob_color = this->knob_color.with_alpha(alpha);
		}

		bool value_has_changed() const
		{
			return this->value_changed;
		}

		bool value_was_modified() const
		{
			return this->value_modified;
		}

		bool is_dragging() const
		{
			return this->dragging;
		}

		bool was_released() const
		{
			return this->released;
		}

		void set_text_font(std::string font)
		{
			this->text.set_font(font);
		}

		void set_text_string(std::string string)
		{
			this->text_string = string;
			this->text.set_string(this->text_string);
		}

		void set_text_character_size(ql::u32 character_size)
		{
			this->text.set_character_size(character_size);
		}

		void set_text_color(ql::rgb color)
		{
			this->text.set_color(color);
		}

		void set_text_string_function(const std::function<std::string(T)>& function)
		{
			this->string_function = function;
		}

		void set_knob_color(ql::rgba color)
		{
			this->knob_color = color;
			this->knob_hover_color = color;
			this->knob_hover_outline_color = color;
			this->knob.set_color(color);
		}

		ql::rgba get_knob_color() const
		{
			return this->knob_color;
		}

		void set_knob_outline_thickness(ql::f32 thickness)
		{
			this->knob_outline_thickness = thickness;
			this->knob.set_outline_thickness(thickness);
		}

		ql::f32 get_knob_outline_thickness() const
		{
			return this->knob_outline_thickness;
		}

		void set_knob_outline_color(ql::rgba color)
		{
			this->knob_outline_color = color;
			this->knob.set_outline_color(color);
		}

		ql::rgba get_knob_outline_color() const
		{
			return this->knob_outline_color;
		}

		void set_knob_hover_color(ql::rgba color)
		{
			this->knob_hover_color = color;
		}

		ql::rgba get_knob_hover_color() const
		{
			return this->knob_hover_color;
		}

		void set_knob_hover_outline_thickness(ql::f32 thickness)
		{
			this->knob_hover_outline_thickness = thickness;
			if (this->is_hovering_over_knob())
			{
				this->knob.set_outline_thickness(thickness);
			}
		}

		ql::f32 get_knob_hover_outline_thickness() const
		{
			return this->knob_hover_outline_thickness;
		}

		void set_knob_hover_outline_color(ql::rgba color)
		{
			this->knob_hover_outline_color = color;
			if (this->is_hovering_over_knob())
			{
				this->knob.set_outline_color(color);
			}
		}

		ql::rgba get_knob_hover_outline_color() const
		{
			return this->knob_hover_outline_color;
		}

		void set_background_color(ql::rgba color)
		{
			this->background_color = color;
			this->background_hover_color = color;
			this->background_hover_outline_color = color;
			this->background.set_color(color);
		}

		ql::rgba get_background_color() const
		{
			return this->background_color;
		}

		void set_background_outline_thickness(ql::f32 thickness)
		{
			this->background_outline_thickness = thickness;
			this->background.set_outline_thickness(thickness);
		}

		ql::f32 get_background_outline_thickness() const
		{
			return this->background_outline_thickness;
		}

		void set_background_outline_color(ql::rgba color)
		{
			this->background_outline_color = color;
			this->background_outline_thickness.set_outline_color(color);
		}

		ql::rgba get_background_outline_color() const
		{
			return this->background_outline_color;
		}

		void set_background_hover_color(ql::rgba color)
		{
			this->background_hover_color = color;
			if (this->is_hovering_over_background())
			{
				this->background.set_color(color);
			}
		}

		ql::rgba get_background_hover_color() const
		{
			return this->background_hover_color;
		}

		void set_background_hover_outline_thickness(ql::f32 thickness)
		{
			this->background_hover_outline_thickness = thickness;
			if (this->is_hovering_over_background())
			{
				this->background.set_outline_thickness(thickness);
			}
		}

		ql::f32 get_background_hover_outline_thickness() const
		{
			return this->background_hover_outline_thickness;
		}

		void set_background_hover_outline_color(ql::rgba color)
		{
			this->background_hover_outline_color = color;
			if (this->is_hovering_over_background())
			{
				this->background.set_outline_color(color);
			}
		}

		ql::rgba get_background_hover_outline_color() const
		{
			return this->background_hover_outline_color;
		}

		void set_hitbox_increase(ql::f32 increase)
		{
			this->hitbox_increase = increase;
		}

		ql::f32 get_hitbox_increase() const
		{
			return this->hitbox_increase;
		}

		void enable_smooth_input()
		{
			this->input_smooth_values = true;
		}

		void enable_smooth_input(sf::Keyboard::Key key)
		{
			this->input_smooth_values = true;
			this->smooth_input_key = key;
		}

		void disable_smooth_input()
		{
			this->input_smooth_values = false;
		}

		bool is_smooth_input_enabled() const
		{
			return this->input_smooth_values;
		}

		void set_smooth_input_multiply(ql::f64 factor)
		{
			this->smooth_input_multiply = factor;
		}

		ql::f64 get_smooth_input_multiply() const
		{
			return this->smooth_input_multiply;
		}

		void allow_click_on_background_to_skip()
		{
			this->click_on_background_to_skip = true;
		}

		void disallow_click_on_background_to_skip()
		{
			this->click_on_background_to_skip = false;
		}

		void is_click_on_background_to_skip_allowed() const
		{
			return this->click_on_background_to_skip;
		}

		bool is_hovering_over_background() const
		{
			return this->hovering_over_background;
		}

		bool is_hovering_over_knob() const
		{
			return this->hovering_over_knob;
		}

		void disallow_dragging()
		{
			this->allow_drag = false;
			this->dragging = false;
		}

		void allow_dragging()
		{
			this->allow_drag = true;
		}

		bool dragging_allowed() const
		{
			return this->allow_drag;
		}

		void set_hover_increase(ql::f32 value)
		{
			this->knob_hover_outline_thickness = value;
			this->background_hover_outline_thickness = value;
		}

		void update(const ql::event& event)
		{
			auto pos = event.mouse_position();
			this->hovering_over_background = false;
			auto y_is = ql::max(this->knob.get_dimension().y, this->background.get_dimension().y);
			this->hovering_over_background = this->background.contains(
					pos, ql::vec2(this->hitbox_increase, this->hitbox_increase + (y_is - this->background.get_dimension().y) / 2)
			);

			this->value_modified = false;
			this->hovering_over_knob = this->knob.contains(pos, {this->hitbox_increase});

			if (this->background_hover_effect && this->hovering_over_background && !this->dragging)
			{
				this->background.set_color(this->background_hover_color);
				this->background.set_outline_color(this->background_hover_outline_color);
				this->background.set_outline_thickness(this->background_hover_outline_thickness);
			}
			else
			{
				this->background.set_color(this->background_color);
				this->background.set_outline_color(this->background_outline_color);
				this->background.set_outline_thickness(this->background_outline_thickness);
			}

			if (this->hovering_over_knob)
			{
				if (this->knob_hover_effect)
				{
					this->knob.set_color(this->knob_hover_color);
					this->knob.set_outline_color(this->knob_hover_outline_color);
					this->knob.set_outline_thickness(this->knob_hover_outline_thickness);
				}
				if (!this->dragging && event.left_mouse_clicked() && this->allow_drag)
				{
					this->dragging = true;
					this->click_pos_x = ql::clamp(this->position.x, ql::f32_cast(pos.x), this->position.x + this->range_pixel_width);
					this->click_knob_pos_x = pos.x - this->knob.get_position().x;
				}
			}
			else
			{
				if (this->click_on_background_to_skip && event.left_mouse_clicked() && this->allow_drag &&
						this->hovering_over_background && (this->end != this->start))
				{
					this->click_pos_x = ql::clamp(this->position.x, ql::f32_cast(pos.x), this->position.x + this->range_pixel_width);
					this->click_knob_pos_x = this->knob.get_dimension().x / 2;
					auto diff = (pos.x - this->position.x - this->click_knob_pos_x);
					auto progress = ql::clamp(diff / this->range_pixel_width);

					if constexpr (ql::is_integer<T>())
					{
						*this->ptr =
								ql::clamp(this->start, this->start + static_cast<T>((this->end - this->start) * progress + 0.5), this->end);
					}
					else
					{
						*this->ptr = ql::clamp(this->start, this->start + static_cast<T>((this->end - this->start) * progress), this->end);
					}
					if (*this->ptr != this->value_before)
					{
						this->value_modified = true;
					}
					this->dragging = true;
				}

				if (this->knob_hover_effect && !this->dragging)
				{
					this->knob.set_color(this->knob_color);
					this->knob.set_outline_color(this->knob_outline_color);
					this->knob.set_outline_thickness(this->knob_outline_thickness);
				}
			}

			if (this->input_smooth_values && event.key_single_pressed(this->smooth_input_key))
			{
				this->click_pos_x = ql::clamp(this->position.x, ql::f32_cast(pos.x), this->position.x + this->range_pixel_width);
			}

			if (!this->value_modified && this->dragging && this->allow_change && (this->end != this->start))
			{
				ql::f64 diff;
				if (this->input_smooth_values && event.key_holding(this->smooth_input_key))
				{
					diff = ((pos.x - this->click_pos_x) * this->smooth_input_multiply) +
								 (this->click_pos_x - this->position.x - this->click_knob_pos_x);
				}
				else
				{
					diff = (pos.x - this->position.x - this->click_knob_pos_x);
				}

				auto progress = ql::clamp(diff / this->range_pixel_width);

				if constexpr (ql::is_integer<T>())
				{
					*this->ptr =
							ql::clamp(this->start, this->start + static_cast<T>((this->end - this->start) * progress + 0.5), this->end);
				}
				else
				{
					*this->ptr = ql::clamp(this->start, this->start + static_cast<T>((this->end - this->start) * progress), this->end);
				}
				if (*this->ptr != this->value_before)
				{
					this->value_modified = true;
				}
			}

			this->value_changed = false;
			if (this->value_before != *this->ptr)
			{
				this->set_knob_position();
				this->value_changed = true;
			}
			this->value_before = *this->ptr;

			this->released = false;
			if (event.left_mouse_released() && this->dragging)
			{
				this->released = true;
				this->dragging = false;
			}
			if (this->value_changed)
			{
				this->update_text_string();
			}
		}

		void draw(ql::render& object) const
		{
			if (this->background_visible)
				object.draw(this->background);
			if (this->knob_visible)
				object.draw(this->knob);
			if (!this->text.get_font().empty())
				object.draw(this->text);
		}

		ql::rectangle background;
		ql::rectangle knob;

		ql::vec2 position;
		bool knob_visible = true;
		bool background_visible = true;
		bool knob_hover_effect = true;
		bool background_hover_effect = true;

		ql::rgba knob_hover_color = ql::rgba::unset();
		ql::f32 knob_hover_outline_thickness = 2.0f;
		ql::rgba knob_hover_outline_color = ql::rgba::unset();

		ql::f32 hitbox_increase = 5.0;

		ql::rgba background_hover_color = ql::rgba::unset();
		ql::f32 background_hover_outline_thickness = 2.0f;
		ql::rgba background_hover_outline_color = ql::rgba::unset();

		T start = T{0};
		T end = T{1};
		T dummy = T{1};
		T value_before = ql::type_max<T>();

		T* ptr = nullptr;

		ql::rgba background_color = ql::rgba::unset();
		ql::f32 background_outline_thickness = 0.0f;
		ql::rgba background_outline_color = ql::rgba::unset();

		ql::rgba knob_color = ql::rgba::unset();
		ql::f32 knob_outline_thickness = 0.0f;
		ql::rgba knob_outline_color = ql::rgba::unset();

		sf::Keyboard::Key smooth_input_key = sf::Keyboard::LShift;
		ql::f64 smooth_input_multiply = 0.1;

		ql::f32 click_knob_pos_x = 0.0f;
		ql::f32 click_pos_x = 0.0f;
		ql::f32 range_pixel_width = 0.0f;

		ql::text text;
		std::string text_string;
		std::function<std::string(T)> string_function;

		bool hovering_over_background = false;
		bool click_on_background_to_skip = true;
		bool input_smooth_values = true;
		bool value_changed = false;
		bool value_modified = false;
		bool range_set = false;
		bool allow_change = true;
		bool allow_drag = true;
		bool dragging = false;
		bool released = false;
		bool hovering_over_knob = false;
	};

	struct check_box
	{
		ql::rectangle background;
		ql::text text;
		bool active_value = false;
		bool value_modified = false;

		check_box()
		{
			this->background.set_dimension({30, 30});
			this->background.set_color(ql::rgb(100, 100, 100));
			this->background.set_outline_color(ql::rgb::white());
			this->background.set_outline_thickness(3.0f);
			this->text.set_color(ql::rgb::white());
			this->text.set_character_size(30);
		}

		void set_font(const std::string& font)
		{
			this->text.set_font(font);
			this->text.set_string("x");
		}

		void set_font(const sf::Font& font)
		{
			this->text.set_font(font);
			this->text.set_string("x");
		}

		void centerize_text()
		{
			this->text.set_center(this->background.get_center());
		}

		void set_dimension(ql::vec2 dimension)
		{
			this->background.set_dimension(dimension);
			this->centerize_text();
		}

		void set_character_size(ql::u32 size)
		{
			this->text.set_character_size(size);
			this->centerize_text();
		}

		void set_center(ql::vec2 position)
		{
			this->background.set_center(position);
			this->centerize_text();
		}

		void set_position(ql::vec2 position)
		{
			this->background.set_position(position);
			this->centerize_text();
		}

		void set_value(bool value)
		{
			this->active_value = value;
		}

		bool value_was_modified() const
		{
			return this->value_modified;
		}

		bool is_clicked() const
		{
			return this->value_was_modified();
		}

		bool get_value() const
		{
			return this->active_value;
		}

		void update(const ql::event& event)
		{
			this->value_modified = false;
			if (this->background.get_hitbox().collides(event.mouse_position()) && event.left_mouse_clicked())
			{
				this->active_value = !this->active_value;
				this->value_modified = true;
			}
		}

		void draw(ql::render& draw) const
		{
			draw.draw(this->background);
			if (this->active_value)
			{
				draw.draw(this->text);
			}
		}
	};

	struct color_picker
	{
		mutable ql::vertex_array gradient;
		mutable ql::vertex_array hue_slider;
		mutable ql::vertex_array gradient_cross;
		mutable ql::vertex_array transparency_slider;
		mutable ql::vertex_array transparency_checkerboard;
		mutable ql::smooth_rectangle background;
		mutable ql::smooth_rectangle hue_slider_knob;
		mutable ql::smooth_rectangle transparency_slider_knob;
		mutable ql::smooth_rectangle display_color_rectangle;
		mutable ql::circle_shape gradient_control_circle;
		mutable ql::smooth_button confirm_button;

		ql::hitbox hitbox;
		ql::f32 slider_width = 30.0f;
		ql::f32 slider_margin = 20.0f;
		ql::f32 background_increase = 40.0f;
		ql::f32 gradient_control_circle_radius = 8.0f;
		ql::f32 bottom_margin = 20.0f;
		ql::f32 bottom_height = 40.0f;
		ql::f32 hitbox_increase = 5.0f;

		ql::vec2d gradient_control;
		ql::f64 hue_control = 0.0;
		ql::f64 transparency_control = 1.0;

		ql::rgb hue_color;

		mutable ql::rgba color_result;
		mutable ql::text_field input_field;

		mutable bool internal_check = false;
		mutable bool internal_gradient_hitbox_changed = true;
		mutable bool internal_gradient_color_changed = true;
		bool visible = true;
		bool dragging_hue_slider = false;
		bool dragging_transparency_slider = false;
		bool dragging_gradient = false;
		bool color_changed = false;
		bool cross_enabled = true;
		bool focus = false;
		bool transparency_used = true;
		bool dont_update_input_text = false;

		constexpr static ql::size gradient_segments = 15u;
		constexpr static ql::size hue_slider_segments = 14u;
		constexpr static ql::vec2 transparency_checkerboard_dimension = ql::vec2{10, 10};
		constexpr static ql::rgb transparency_checkerboard_color_dark = ql::rgb::grey_shade(100);
		constexpr static ql::rgb transparency_checkerboard_color_light = ql::rgb::grey_shade(150);

		color_picker()
		{
			this->init();
		}

		QL_SOURCE void init();
		QL_SOURCE void reset();
		QL_SOURCE void update_values();

		QL_SOURCE bool color_value_changed() const;
		QL_SOURCE bool has_focus() const;
		QL_SOURCE bool is_font_set() const;

		QL_SOURCE void set_color_value(ql::rgba color);
		QL_SOURCE ql::rgba get_color_value() const;
		QL_SOURCE ql::rgb get_gradient_color_at(ql::vec2f pos) const;
		QL_SOURCE ql::hitbox get_gradient_hitbox() const;
		QL_SOURCE ql::hitbox get_hue_slider_hitbox() const;
		QL_SOURCE ql::hitbox get_transparency_slider_hitbox() const;
		QL_SOURCE ql::f64 get_hue_control_value() const;
		QL_SOURCE ql::f64 get_transparency_control_value() const;
		QL_SOURCE ql::vec2d get_gradient_control_value() const;

		QL_SOURCE void disable_transparency();
		QL_SOURCE void enable_transparency();

		QL_SOURCE void set_font(std::string font);
		QL_SOURCE void set_invisible();
		QL_SOURCE void set_visible();
		QL_SOURCE bool is_visible() const;
		QL_SOURCE bool is_dragging_hue_slider() const;
		QL_SOURCE bool is_dragging_transparency_slider() const;
		QL_SOURCE bool is_dragging_gradient() const;
		QL_SOURCE bool is_dragging() const;

		QL_SOURCE void set_input_field_width(ql::f32 width);
		QL_SOURCE void set_dimension(ql::vec2f dimension);
		QL_SOURCE void set_position(ql::vec2f position);
		QL_SOURCE void set_hitbox(ql::hitbox hitbox);
		QL_SOURCE void set_center(ql::vec2f center);
		QL_SOURCE void set_hue_wheel(ql::f64 hue);
		QL_SOURCE void set_background_color(ql::rgba color);
		QL_SOURCE void set_hue_control_color(ql::rgba color);
		QL_SOURCE void set_gradient_control_color(ql::rgba color);

		QL_SOURCE void create_gradient() const;
		QL_SOURCE void update_gradient() const;
		QL_SOURCE void create_hue_slider() const;
		QL_SOURCE void create_transparency_slider() const;
		QL_SOURCE void update_bottom_row_positions() const;
		QL_SOURCE void internal_update() const;
		QL_SOURCE void update_hue_slider_knob_position() const;
		QL_SOURCE void update_transparency_slider_knob_position() const;
		QL_SOURCE void update_gradient_control_position() const;
		QL_SOURCE void update_internal_colors();

		QL_SOURCE void update_entered_text();

		QL_SOURCE void update(const ql::event& event);
		QL_SOURCE void draw(ql::render& draw) const;
	};

	struct scroll_bar
	{
		ql::smooth_rectangle background;
		ql::smooth_rectangle knob;

		ql::hitbox hitbox;

		ql::f32 knob_progress = 0.0f;
		ql::f32 knob_range = 1.0f;
		ql::f32 visible_knob_progress = 0.0f;
		ql::size integer_step = ql::size_max;

		ql::animation background_hover_animation;
		ql::rgb background_color = ql::rgb::grey_shade(24);
		ql::rgb background_color_hover = ql::rgb::grey_shade(30);

		ql::animation hover_animation;
		ql::rgb knob_color = ql::rgb::grey_shade(141);
		ql::rgb knob_color_hover = ql::rgb::grey_shade(200);

		bool hovering = false;
		bool hovering_background = false;
		bool dragging = false;
		bool allow_dragging = true;
		bool clicked_on_background_below = false;
		bool clicked_on_background_above = false;
		bool released_dragging = false;
		bool value_changed = false;
		ql::vec2f dragging_position;

		QL_SOURCE scroll_bar();
		QL_SOURCE void set_dimension(ql::vec2f dimension);
		QL_SOURCE void set_position(ql::vec2f position);
		QL_SOURCE void set_hitbox(ql::hitbox hitbox);
		QL_SOURCE void set_visible_knob_progress(ql::f64 progress);
		QL_SOURCE void update_knob();
		QL_SOURCE void update_positions();
		QL_SOURCE ql::f32 stepped_progress() const;
		QL_SOURCE ql::f32 stepped_progress_unless_dragging() const;
		QL_SOURCE ql::f32 get_progress() const;
		QL_SOURCE ql::size get_progress_step() const;
		QL_SOURCE void set_progress_integer_step(ql::size step, ql::size knob_steps);
		QL_SOURCE void set_progress(ql::f32 progress);
		QL_SOURCE void set_knob_height(ql::f32 height);
		QL_SOURCE void set_knob_range(ql::f32 range);
		QL_SOURCE void update_hover(const ql::event& event);
		QL_SOURCE void update_background_hover(const ql::event& event);
		QL_SOURCE void update(const ql::event& event);
		QL_SOURCE void draw(ql::render& draw) const;
	};

	struct console
	{
		ql::colored_text colored_text;
		ql::styled_string<std::u32string> string;
		ql::styled_string<std::u32string> input_string;
		ql::styled_string<std::u32string> string_and_input;
		std::vector<std::wstring> input_string_split;
		std::vector<std::wstring> string_split;
		std::vector<std::wstring> string_and_input_split;
		std::vector<ql::rectangle> selection_rectangle;

		ql::vec2f selection_rectangle_start;
		ql::vec2f selection_rectangle_end;

		// ql::border_graphic shadow_border;
		ql::border_graphic scroll_bar_shadow_border;

		ql::view view;
		ql::vec2f dimension;
		ql::isize zooms = 10;
		ql::isize view_row = 0;
		ql::size visible_rows = 0u;
		ql::scroll_bar scroll_bar;
		ql::f64 cursor_interval_duration = 1.5;
		ql::rectangle cursor;
		ql::small_clock cursor_blink_timer;

		ql::animation scroll_transition_animation;
		ql::f64 scroll_transition_start = 0.0;
		ql::f64 scroll_transition_end = 0.0;
		ql::f64 scroll_bar_transition_start = 0.0;
		ql::f64 scroll_bar_transition_end = 0.0;

		ql::rgba selection_rectangle_color = ql::rgba(200, 200, 200, 140);
		ql::rgba shadow_border_color = ql::rgb(10, 10, 14);

		ql::isize visible_y_min = 0;
		ql::isize visible_y_max = 0;
		ql::size visible_buffer = 100;

		ql::size before_input_vertices_size = ql::size_max;
		ql::size before_input_outline_vertices_size = ql::size_max;
		ql::size before_input_unicode_vertices_size = ql::size_max;
		ql::size before_input_unicode_outline_vertices_size = ql::size_max;
		ql::size before_input_text_rows = 0u;
		ql::vec2f before_input_text_position = {0.f, 0.f};
		ql::vec2s cursor_position;
		ql::vec2f clicked_mouse_position;
		ql::vec2f character_size;

		std::vector<std::wstring> input_history;
		ql::size input_history_index = 0u;

		bool accept_input = false;
		bool hidden_input = false;
		bool text_entered = false;
		bool line_entered = false;
		bool text_dragging = false;
		bool allow_text_dragging = true;
		bool allow_going_up_with_cursor = false;
		bool border_texture_set = false;
		bool enter_to_continue = false;
		bool exited_enter_to_continue = false;
		bool add_new_line_on_enter = true;

		QL_SOURCE void print();

		QL_SOURCE void press_enter_to_continue_mode();
		QL_SOURCE void reset_visible_range();
		QL_SOURCE void clear();
		QL_SOURCE void init();
		QL_SOURCE void apply_font();
		QL_SOURCE void set_border_texture(const sf::Texture& texture);
		QL_SOURCE void set_font(std::string font);
		QL_SOURCE void set_unicode_font(std::string font);
		QL_SOURCE void calculate_default_character_size();
		QL_SOURCE void track_before_input_values();
		QL_SOURCE void start_accepting_input();
		QL_SOURCE void stop_accepting_input();
		QL_SOURCE void clamp_view_y(bool transition = true);
		QL_SOURCE void set_dimension(ql::vec2f dimension);
		QL_SOURCE void set_input_color(ql::color::print_color color);
		QL_SOURCE void prepare_scroll();
		QL_SOURCE void update_visible_rows_count();
		QL_SOURCE void end_animation();
		QL_SOURCE void update_string_and_input_split();
		QL_SOURCE void update_string_split();
		QL_SOURCE void update_input_string_split();
		QL_SOURCE void update_cursor_position(bool reset_timer = false);
		QL_SOURCE void update_input_text_graphics();
		QL_SOURCE void add_text_input(const std::u32string& string, bool at_end = false);
		QL_SOURCE void pop_character_at_cursor();
		QL_SOURCE void update_cursor_dimension();
		QL_SOURCE void update_text_range();
		QL_SOURCE void process_character_size();
		QL_SOURCE ql::size get_text_height() const;
		QL_SOURCE ql::size get_text_width(ql::size y) const;
		QL_SOURCE ql::size get_input_text_width(ql::size y) const;
		QL_SOURCE ql::size get_input_text_height() const;
		QL_SOURCE ql::vec2f position_to_text_position(ql::vec2f position) const;
		QL_SOURCE void clear_selection_rectangles_if_visible();
		QL_SOURCE auto get_selection_rectangle_bounds() const;
		QL_SOURCE std::wstring get_selection_rectangle_string() const;
		QL_SOURCE void make_selection_rectangles();
		QL_SOURCE void move_to_input();
		QL_SOURCE auto get_input_text() const;
		QL_SOURCE std::wstring get_last_input_line(bool consider_new_line = true) const;
		QL_SOURCE void process_text();

		template <typename T>
		requires (!ql::is_same<ql::styled_string<std::u32string>, T>())
		void add(const T& value)
		{
			ql::styled_string<std::u32string> string;
			string.clear_copy_style(this->colored_text.last_element);
			string.add(value);
			this->add(string);
		}

		QL_SOURCE void add(const ql::styled_string<std::u32string>& string);
		QL_SOURCE void create(const ql::styled_string<std::u32string>& string);
		QL_SOURCE void paste_from_clipboard();
		QL_SOURCE void update_key_input(const ql::event& event);
		QL_SOURCE void update_selection_rectangle(const ql::event& event);
		QL_SOURCE void update_cursor();
		QL_SOURCE void update(const ql::event& event);
		QL_SOURCE void draw(ql::render& draw) const;
	};
}	 // namespace ql

#endif