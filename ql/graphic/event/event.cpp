
#include <ql/graphic/event/event.hpp>

#if defined QL_GRAPHIC

#include <ql/core/string/cast/cast.hpp>

namespace ql
{
	bool ql::event::key_single_pressed(sf::Keyboard::Key key) const
	{
		return this->m_keys_single_pressed.find(key) != this->m_keys_single_pressed.cend();
	}

	bool ql::event::key_single_released(sf::Keyboard::Key key) const
	{
		return this->m_keys_single_released.find(key) != this->m_keys_single_released.cend();
	}

	bool ql::event::key_pressed(sf::Keyboard::Key key) const
	{
		return this->m_keys_pressed.find(key) != this->m_keys_pressed.cend();
	}

	bool ql::event::keys_pressed(const std::vector<sf::Keyboard::Key>& keys) const
	{
		for (auto& i : keys)
		{
			if (this->m_keys_pressed.find(i) == this->m_keys_pressed.cend())
			{
				return false;
			}
		}
		return true;
	}

	bool ql::event::key_released(sf::Keyboard::Key key) const
	{
		return this->m_keys_released.find(key) != this->m_keys_released.cend();
	}

	bool ql::event::keys_released(const std::vector<sf::Keyboard::Key>& keys) const
	{
		for (auto& i : keys)
		{
			if (this->m_keys_released.find(i) == this->m_keys_released.cend())
			{
				return false;
			}
		}
		return true;
	}

	bool ql::event::key_holding(sf::Keyboard::Key key) const
	{
		return this->m_keys_holding.find(key) != this->m_keys_holding.cend();
	}

	bool ql::event::keys_holding(const std::vector<sf::Keyboard::Key>& keys) const
	{
		for (auto& i : keys)
		{
			if (this->m_keys_holding.find(i) == this->m_keys_holding.cend())
			{
				return false;
			}
		}
		return true;
	}

	bool ql::event::mouse_button_clicked(sf::Mouse::Button button) const
	{
		if (button == sf::Mouse::Button::Left)
		{
			return this->m_left_mouse_clicked;
		}
		else if (button == sf::Mouse::Button::Middle)
		{
			return this->m_middle_mouse_clicked;
		}
		else if (button == sf::Mouse::Button::Right)
		{
			return this->m_right_mouse_clicked;
		}
		return false;
	}

	bool ql::event::mouse_button_released(sf::Mouse::Button button) const
	{
		if (button == sf::Mouse::Button::Left)
		{
			return this->m_left_mouse_released;
		}
		else if (button == sf::Mouse::Button::Middle)
		{
			return this->m_middle_mouse_released;
		}
		else if (button == sf::Mouse::Button::Right)
		{
			return this->m_right_mouse_released;
		}
		return false;
	}

	bool ql::event::mouse_button_holding(sf::Mouse::Button button) const
	{
		if (button == sf::Mouse::Button::Left)
		{
			return this->m_holding_left_mouse;
		}
		else if (button == sf::Mouse::Button::Middle)
		{
			return this->m_holding_middle_mouse;
		}
		else if (button == sf::Mouse::Button::Right)
		{
			return this->m_holding_right_mouse;
		}
		return false;
	}

	bool ql::event::mouse_button_clicked() const
	{
		return this->m_mouse_clicked;
	}

	bool ql::event::mouse_button_released() const
	{
		return this->m_mouse_released;
	}

	bool ql::event::mouse_button_holding() const
	{
		return this->m_mouse_holding;
	}

	bool ql::event::mouse_moved() const
	{
		return this->m_mouse_moved;
	}

	bool ql::event::left_mouse_clicked() const
	{
		return this->m_left_mouse_clicked;
	}

	bool ql::event::left_mouse_released() const
	{
		return this->m_left_mouse_released;
	}

	bool ql::event::right_mouse_clicked() const
	{
		return this->m_right_mouse_clicked;
	}

	bool ql::event::right_mouse_released() const
	{
		return this->m_right_mouse_released;
	}

	bool ql::event::middle_mouse_clicked() const
	{
		return this->m_middle_mouse_clicked;
	}

	bool ql::event::middle_mouse_released() const
	{
		return this->m_middle_mouse_released;
	}

	bool ql::event::scrolled_up() const
	{
		return this->m_scrolled_up;
	}

	bool ql::event::scrolled_down() const
	{
		return this->m_scrolled_down;
	}

	bool ql::event::key_pressed() const
	{
		return this->m_key_pressed;
	}

	bool ql::event::key_single_pressed() const
	{
		return this->m_key_single_pressed;
	}

	bool ql::event::key_released() const
	{
		return this->m_key_released;
	}

	bool ql::event::key_single_released() const
	{
		return this->m_key_single_released;
	}

	bool ql::event::key_holding() const
	{
		return this->m_key_holding;
	}

	bool ql::event::resized() const
	{
		return this->m_resized;
	}

	bool ql::event::window_closed() const
	{
		return this->m_window_closed;
	}

	bool ql::event::holding_left_mouse() const
	{
		return this->m_holding_left_mouse;
	}

	bool ql::event::holding_right_mouse() const
	{
		return this->m_holding_right_mouse;
	}

	bool ql::event::holding_middle_mouse() const
	{
		return this->m_holding_middle_mouse;
	}

	bool ql::event::holding_key() const
	{
		return this->m_holding_key;
	}

	bool ql::event::left_mouse_fast_clicked() const
	{
		return this->m_left_mouse_fast_click;
	}

	bool ql::event::right_mouse_fast_clicked() const
	{
		return this->m_right_mouse_fast_click;
	}

	bool ql::event::middle_mouse_fast_clicked() const
	{
		return this->m_middle_mouse_fast_click;
	}

	bool ql::event::left_mouse_double_clicked() const
	{
		return this->m_left_mouse_double_click;
	}

	bool ql::event::right_mouse_double_clicked() const
	{
		return this->m_right_mouse_double_click;
	}

	bool ql::event::middle_mouse_double_clicked() const
	{
		return this->m_middle_mouse_double_click;
	}

	ql::size ql::event::left_mouse_fast_click_count() const
	{
		if (!this->left_mouse_double_clicked())
		{
			return 0u;
		}
		return this->m_left_mouse_fast_click_ctr;
	}

	ql::size ql::event::right_mouse_fast_click_count() const
	{
		if (!this->right_mouse_double_clicked())
		{
			return 0u;
		}
		return this->m_right_mouse_fast_click_ctr;
	}

	ql::size ql::event::middle_mouse_fast_click_count() const
	{
		if (!this->middle_mouse_double_clicked())
		{
			return 0u;
		}
		return this->m_middle_mouse_fast_click_ctr;
	}

	void ql::event::reset(const sf::RenderWindow& window)
	{
		this->m_mouse_clicked = false;
		this->m_mouse_released = false;
		this->m_left_mouse_clicked = false;
		this->m_left_mouse_released = false;
		this->m_right_mouse_clicked = false;
		this->m_right_mouse_released = false;
		this->m_middle_mouse_clicked = false;
		this->m_middle_mouse_released = false;
		this->m_scrolled_up = false;
		this->m_scrolled_down = false;
		this->m_key_pressed = false;
		this->m_key_single_pressed = false;
		this->m_key_released = false;
		this->m_mouse_moved = false;
		this->m_window_closed = false;
		this->m_resized = false;
		this->m_left_mouse_double_click = false;
		this->m_right_mouse_double_click = false;
		this->m_middle_mouse_double_click = false;
		this->m_left_mouse_fast_click = false;
		this->m_right_mouse_fast_click = false;
		this->m_middle_mouse_fast_click = false;

		this->m_keys_pressed.clear();
		this->m_keys_released.clear();
		this->m_keys_single_pressed.clear();

		this->m_text_entered.clear();
		this->m_u32_text_entered.clear();

		this->m_mouse_position_screen = this->m_mouse_position = sf::Mouse::getPosition(window);
		this->m_mouse_position_desktop = sf::Mouse::getPosition();

		this->m_delta_mouse_position = this->m_mouse_position_screen - this->m_mouse_position_screen_before;
		this->m_mouse_position_screen_before = this->m_mouse_position_screen;

		// this->m_joystick_connect = false;
		// this->m_joystick_disconnect = false;
		// this->m_joystick_left_direction.clear();
		// this->m_joystick_right_direction.clear();
		// this->m_joystick_axis_holding.clear();
		// this->m_joystick_axis_pressed.clear();
		// this->m_joystick_axis_released.clear();
	}

	void ql::event::update(const sf::Event& event)
	{
		if (event.type == sf::Event::TextEntered)
		{
			this->m_u32_text_entered += event.text.unicode;
			this->m_text_entered.push_back(event.text.unicode);
			this->m_text_entered_total += (wchar_t)event.text.unicode;
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			this->m_mouse_clicked = true;
			this->m_mouse_holding = true;
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				this->m_left_mouse_click_release_clock.reset();
				this->m_left_mouse_clicked = true;
				this->m_holding_left_mouse = true;
				if (this->m_left_mouse_clock.is_running())
				{
					if (this->m_left_mouse_clock.elapsed_f() < this->m_fast_double_click_duration)
					{
						this->m_left_mouse_double_click = true;
						++this->m_left_mouse_fast_click_ctr;
						this->m_left_mouse_clock.reset();
					}
					else
					{
						this->m_left_mouse_clock.reset();
						this->m_left_mouse_fast_click_ctr = 1u;
					}
				}
				else
				{
					this->m_left_mouse_clock.reset();
					this->m_left_mouse_fast_click_ctr = 1u;
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				this->m_right_mouse_click_release_clock.reset();
				this->m_right_mouse_clicked = true;
				this->m_holding_right_mouse = true;
				if (this->m_right_mouse_clock.is_running())
				{
					if (this->m_right_mouse_clock.elapsed_f() < this->m_fast_double_click_duration)
					{
						this->m_right_mouse_double_click = true;
						++this->m_right_mouse_fast_click_ctr;
						this->m_right_mouse_clock.reset();
					}
					else
					{
						this->m_right_mouse_clock.reset();
						this->m_right_mouse_fast_click_ctr = 1u;
					}
				}
				else
				{
					this->m_right_mouse_clock.reset();
					this->m_right_mouse_fast_click_ctr = 1u;
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Middle)
			{
				this->m_middle_mouse_click_release_clock.reset();
				this->m_middle_mouse_clicked = true;
				this->m_holding_middle_mouse = true;
				if (this->m_middle_mouse_clock.is_running())
				{
					if (this->m_middle_mouse_clock.elapsed_f() < this->m_fast_double_click_duration)
					{
						this->m_middle_mouse_double_click = true;
						++this->m_middle_mouse_fast_click_ctr;
						this->m_middle_mouse_clock.reset();
					}
					else
					{
						this->m_middle_mouse_clock.reset();
						this->m_middle_mouse_fast_click_ctr = 1u;
					}
				}
				else
				{
					this->m_middle_mouse_clock.reset();
					this->m_middle_mouse_fast_click_ctr = 1u;
				}
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			this->m_mouse_released = true;
			this->m_mouse_holding = false;
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (this->m_left_mouse_click_release_clock.elapsed_f() < this->m_fast_click_duration)
				{
					this->m_left_mouse_fast_click = true;
				}
				this->m_left_mouse_released = true;
				this->m_holding_left_mouse = false;
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				if (this->m_right_mouse_click_release_clock.elapsed_f() < this->m_fast_click_duration)
				{
					this->m_right_mouse_fast_click = true;
				}
				this->m_right_mouse_released = true;
				this->m_holding_right_mouse = false;
			}
			else if (event.mouseButton.button == sf::Mouse::Middle)
			{
				if (this->m_middle_mouse_click_release_clock.elapsed_f() < this->m_fast_click_duration)
				{
					this->m_middle_mouse_fast_click = true;
				}
				this->m_middle_mouse_released = true;
				this->m_holding_middle_mouse = false;
			}
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			this->m_key_pressed = true;
			this->m_key_holding = true;
			this->m_keys_pressed.insert(event.key.code);
			if (!this->key_holding(event.key.code))
			{
				this->m_keys_single_pressed.insert(event.key.code);
				this->m_key_single_pressed = true;
			}
			this->m_keys_holding.insert(event.key.code);

			this->update_move_direction();
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			this->m_key_released = true;
			this->m_key_holding = false;
			this->m_keys_released.insert(event.key.code);
			this->m_keys_holding.erase(event.key.code);

			this->update_move_direction();
		}
		else if (event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheel.delta < 0)
			{
				this->m_scrolled_down = true;
			}
			if (event.mouseWheel.delta > 0)
			{
				this->m_scrolled_up = true;
			}
		}
		else if (event.type == sf::Event::Closed)
		{
			this->m_window_closed = true;
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			this->m_mouse_moved = true;
		}
		else if (event.type == sf::Event::Resized)
		{
			this->m_resized = true;
			this->m_resized_size = {event.size.width, event.size.height};
		}
	}

	void ql::event::update_move_direction()
	{
		ql::vec2 direction;

		this->m_moved_direction = false;

		if (this->key_holding(sf::Keyboard::W))
		{
			direction.y -= 1.f;
			this->m_moved_direction = true;
		}
		if (this->key_holding(sf::Keyboard::A))
		{
			direction.x -= 1.f;
			this->m_moved_direction = true;
		}
		if (this->key_holding(sf::Keyboard::S))
		{
			direction.y += 1.f;
			this->m_moved_direction = true;
		}
		if (this->key_holding(sf::Keyboard::D))
		{
			direction.x += 1.f;
			this->m_moved_direction = true;
		}

		this->m_move_direction = direction.normalized();
	}

	void ql::event::set_fast_click_duration(ql::f64 duration)
	{
		this->m_fast_click_duration = duration;
	}

	ql::f64 ql::event::get_fast_click_duration() const
	{
		return this->m_fast_click_duration;
	}

	void ql::event::set_fast_double_click_duration(ql::f64 duration)
	{
		this->m_fast_double_click_duration = duration;
	}

	ql::f64 ql::event::get_fast_double_click_duration() const
	{
		return this->m_fast_double_click_duration;
	}

	ql::vector2u ql::event::screen_dimension() const
	{
		return this->m_screen_dimension;
	}

	ql::time ql::event::frame_time() const
	{
		return this->m_frame_time;
	}

	ql::f64 ql::event::frame_time_f() const
	{
		return this->m_frame_time.secs_f();
	}

	ql::vector2i ql::event::resized_size() const
	{
		return this->m_resized_size;
	}

	bool ql::event::text_entered(char c) const
	{
		auto str = this->text_entered_str();
		for (auto& i : str)
		{
			if (i == c)
			{
				return true;
			}
		}
		return false;
	}

	bool ql::event::text_entered(wchar_t c) const
	{
		for (auto& i : this->m_text_entered)
		{
			if (i == c)
			{
				return true;
			}
		}
		return false;
	}

	bool ql::event::text_entered(std::string c) const
	{
		for (auto& i : c)
		{
			if (!this->text_entered(i))
			{
				return false;
			}
		}
		return true;
	}

	bool ql::event::text_entered(std::wstring c) const
	{
		for (auto& i : c)
		{
			if (!this->text_entered(i))
			{
				return false;
			}
		}
		return true;
	}

	ql::vec2 ql::event::mouse_position() const
	{
		return this->m_mouse_position;
	}

	ql::vec2 ql::event::delta_mouse_position() const
	{
		return this->m_delta_mouse_position;
	}

	ql::vector2i ql::event::mouse_position_screen() const
	{
		return this->m_mouse_position_screen;
	}

	ql::vector2i ql::event::mouse_position_desktop() const
	{
		return this->m_mouse_position_desktop;
	}

	bool ql::event::moved_direction() const
	{
		return this->m_moved_direction;
	}
	ql::vec2 ql::event::move_direction() const
	{
		return this->m_move_direction;
	}

	void ql::event::reset_delta_mouse()
	{
		this->m_mouse_position_screen_before = this->m_mouse_position_screen;
		this->m_delta_mouse_position.clear();
	}

	bool ql::event::is_text_entered() const
	{
		return !this->m_text_entered.empty();
	}

	std::wstring ql::event::text_entered() const
	{
		return this->m_text_entered;
	}

	std::u32string ql::event::u32_text_entered() const
	{
		return this->m_u32_text_entered;
	}

	std::string ql::event::text_entered_str() const
	{
		return ql::wstring_to_string(this->m_text_entered);
	}

	std::wstring ql::event::all_text_entered() const
	{
		return this->m_text_entered_total;
	}

	std::string ql::event::all_text_entered_str() const
	{
		return ql::wstring_to_string(this->m_text_entered_total);
	}

}	 // namespace ql

#endif