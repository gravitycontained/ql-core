#pragma once

#include <ql/core/definition/definition.hpp>

#if defined QL_GRAPHIC

#include <SFML/Graphics.hpp>

#include <ql/core/advanced-type/view/view.hpp>
#include <ql/core/time/clock/clock.hpp>

#include <set>

namespace ql
{
	struct event;

	template <typename C, typename... Args>
	concept has_update_c = requires(C x, const event& event, Args... args) { x.update(event, args...); };

	template <typename C, typename... Args>
	constexpr bool has_update()
	{
		return has_update_c<C, Args...>;
	}

	struct event
	{
		QL_SOURCE bool key_single_pressed(sf::Keyboard::Key key) const;
		QL_SOURCE bool key_single_released(sf::Keyboard::Key key) const;
		QL_SOURCE bool key_pressed(sf::Keyboard::Key key) const;
		QL_SOURCE bool key_released(sf::Keyboard::Key key) const;
		QL_SOURCE bool key_holding(sf::Keyboard::Key key) const;
		QL_SOURCE bool keys_pressed(const std::vector<sf::Keyboard::Key>& keys) const;
		QL_SOURCE bool keys_released(const std::vector<sf::Keyboard::Key>& keys) const;
		QL_SOURCE bool keys_holding(const std::vector<sf::Keyboard::Key>& keys) const;

		QL_SOURCE bool mouse_button_clicked(sf::Mouse::Button button) const;
		QL_SOURCE bool mouse_button_released(sf::Mouse::Button button) const;
		QL_SOURCE bool mouse_button_holding(sf::Mouse::Button button) const;

		QL_SOURCE bool mouse_button_clicked() const;
		QL_SOURCE bool mouse_button_released() const;
		QL_SOURCE bool mouse_button_holding() const;

		QL_SOURCE bool mouse_moved() const;
		QL_SOURCE bool left_mouse_clicked() const;
		QL_SOURCE bool left_mouse_released() const;
		QL_SOURCE bool right_mouse_clicked() const;
		QL_SOURCE bool right_mouse_released() const;
		QL_SOURCE bool middle_mouse_clicked() const;
		QL_SOURCE bool middle_mouse_released() const;
		QL_SOURCE bool scrolled_up() const;
		QL_SOURCE bool scrolled_down() const;
		QL_SOURCE bool key_pressed() const;
		QL_SOURCE bool key_single_pressed() const;
		QL_SOURCE bool key_released() const;
		QL_SOURCE bool key_single_released() const;
		QL_SOURCE bool key_holding() const;

		QL_SOURCE bool resized() const;
		QL_SOURCE bool window_closed() const;

		QL_SOURCE bool holding_left_mouse() const;
		QL_SOURCE bool holding_right_mouse() const;
		QL_SOURCE bool holding_middle_mouse() const;
		QL_SOURCE bool holding_key() const;

		QL_SOURCE bool left_mouse_fast_clicked() const;
		QL_SOURCE bool right_mouse_fast_clicked() const;
		QL_SOURCE bool middle_mouse_fast_clicked() const;

		QL_SOURCE bool left_mouse_double_clicked() const;
		QL_SOURCE bool right_mouse_double_clicked() const;
		QL_SOURCE bool middle_mouse_double_clicked() const;
		QL_SOURCE ql::size left_mouse_fast_click_count() const;
		QL_SOURCE ql::size right_mouse_fast_click_count() const;
		QL_SOURCE ql::size middle_mouse_fast_click_count() const;

		QL_SOURCE void reset(const sf::RenderWindow& window);
		QL_SOURCE void update(const sf::Event& event);
		QL_SOURCE void update_move_direction();

		QL_SOURCE void set_fast_click_duration(ql::f64 duration);
		QL_SOURCE ql::f64 get_fast_click_duration() const;
		QL_SOURCE void set_fast_double_click_duration(ql::f64 duration);
		QL_SOURCE ql::f64 get_fast_double_click_duration() const;

		QL_SOURCE ql::vector2u screen_dimension() const;
		QL_SOURCE ql::time frame_time() const;
		QL_SOURCE ql::f64 frame_time_f() const;
		QL_SOURCE ql::vector2i resized_size() const;
		QL_SOURCE ql::vec2 mouse_position() const;
		QL_SOURCE ql::vec2 delta_mouse_position() const;
		QL_SOURCE ql::vector2i mouse_position_screen() const;
		QL_SOURCE ql::vector2i mouse_position_desktop() const;

		QL_SOURCE bool moved_direction() const;
		QL_SOURCE ql::vec2 move_direction() const;

		QL_SOURCE void reset_delta_mouse();

		template <typename T>
		void apply_view(const ql::view_type<T>& view) const
		{
			this->m_mouse_position = view.transform_point(this->m_mouse_position);
			this->m_delta_mouse_position = view.transform_point_no_offset(this->m_delta_mouse_position);
		}

		QL_SOURCE bool text_entered(char c) const;
		QL_SOURCE bool text_entered(wchar_t c) const;
		QL_SOURCE bool text_entered(std::string c) const;
		QL_SOURCE bool text_entered(std::wstring c) const;

		QL_SOURCE bool is_text_entered() const;
		QL_SOURCE std::wstring text_entered() const;
		QL_SOURCE std::u32string u32_text_entered() const;
		QL_SOURCE std::string text_entered_str() const;
		QL_SOURCE std::wstring all_text_entered() const;
		QL_SOURCE std::string all_text_entered_str() const;

		template <typename T, typename... Args>
		requires (
				ql::has_update<T, Args...>() || (ql::is_container<T>() && ql::has_update<ql::container_deepest_subtype<T>, Args...>())
		)
		void update(T& updatable, Args&&... args) const
		{
			if constexpr (ql::has_update<T, Args...>())
			{
				if constexpr (ql::has_view<T>())
				{
					if (updatable.auto_view.is_default_view())
					{
						updatable.update(*this, args...);
					}
					else
					{
						auto before = this->m_mouse_position;
						auto before_delta = this->m_delta_mouse_position;
						this->apply_view(updatable.auto_view);

						updatable.update(*this, args...);

						this->m_mouse_position = before;
						this->m_delta_mouse_position = before_delta;
					}
				}
				else
				{
					updatable.update(*this, args...);
				}
			}
			else
			{
				for (auto& i : updatable)
				{
					this->update(i, args...);
				}
			}
		}

		bool m_mouse_clicked = false;
		bool m_mouse_released = false;
		bool m_mouse_holding = false;
		bool m_left_mouse_clicked = false;
		bool m_left_mouse_released = false;
		bool m_right_mouse_clicked = false;
		bool m_right_mouse_released = false;
		bool m_middle_mouse_clicked = false;
		bool m_middle_mouse_released = false;
		bool m_scrolled_up = false;
		bool m_scrolled_down = false;
		bool m_key_pressed = false;
		bool m_key_single_pressed = false;
		bool m_key_released = false;
		bool m_key_single_released = false;
		bool m_key_holding = false;
		bool m_mouse_moved = false;
		bool m_window_closed = false;
		bool m_resized = false;

		bool m_holding_left_mouse = false;
		bool m_holding_right_mouse = false;
		bool m_holding_middle_mouse = false;
		bool m_holding_key = false;
		bool m_left_mouse_double_click = false;
		bool m_right_mouse_double_click = false;
		bool m_middle_mouse_double_click = false;
		bool m_left_mouse_fast_click = false;
		bool m_right_mouse_fast_click = false;
		bool m_middle_mouse_fast_click = false;

		std::wstring m_text_entered;
		std::u32string m_u32_text_entered;
		std::wstring m_text_entered_total;

		bool m_moved_direction = false;
		ql::vec2 m_move_direction;
		ql::vector2i m_resized_size;
		mutable ql::vec2 m_mouse_position;
		mutable ql::vec2 m_delta_mouse_position;
		ql::vector2i m_mouse_position_screen;
		ql::vector2i m_mouse_position_screen_before;
		ql::vector2i m_mouse_position_desktop;
		std::set<sf::Keyboard::Key> m_keys_pressed;
		std::set<sf::Keyboard::Key> m_keys_released;
		std::set<sf::Keyboard::Key> m_keys_single_pressed;
		std::set<sf::Keyboard::Key> m_keys_single_released;
		std::set<sf::Keyboard::Key> m_keys_holding;

		ql::time m_frame_time = 0;
		ql::vector2u m_screen_dimension = ql::vec(0u, 0u);

		ql::small_clock m_left_mouse_click_release_clock;
		ql::small_clock m_right_mouse_click_release_clock;
		ql::small_clock m_middle_mouse_click_release_clock;

		ql::halted_clock m_left_mouse_clock;
		ql::halted_clock m_right_mouse_clock;
		ql::halted_clock m_middle_mouse_clock;
		ql::size m_left_mouse_fast_click_ctr = 1u;
		ql::size m_right_mouse_fast_click_ctr = 1u;
		ql::size m_middle_mouse_fast_click_ctr = 1u;

		ql::f64 m_fast_double_click_duration = 0.2;
		ql::f64 m_fast_click_duration = 0.15;

		// bool m_joystick_connect;
		// bool m_joystick_disconnect;
		// ql::vec2 m_joystick_left_direction;
		// ql::vec2 m_joystick_right_direction;
		// std::unordered_set<sf::Joystick::Axis> m_joystick_axis_pressed;
		// std::unordered_set<sf::Joystick::Axis> m_joystick_axis_released;
		// std::unordered_set<sf::Joystick::Axis> m_joystick_axis_holding;
	};

}	 // namespace ql

#endif