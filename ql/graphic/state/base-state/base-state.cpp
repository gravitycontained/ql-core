#include <ql/graphic/state/base-state/base-state.hpp>

#if defined QL_SFML

#include <ql/graphic/resources.hpp>
#include <ql/graphic/view-control.hpp>

namespace ql
{

	void ql::base_state::clear()
	{
#if defined QL_GLEW
		if (this->use_gl)
		{
			auto c = ql::frgba(this->clear_color);
			qgl::gl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			qgl::gl::clear_color(c.r, c.g, c.b, c.a);
		}
		else
		{
			this->state_manager->window.clear(this->clear_color);
		}
#else
		this->state_manager->window.clear(this->clear_color);
#endif
	}

	void ql::base_state::call_on_resize()
	{
	}

	void ql::base_state::call_before_create()
	{
	}

	void ql::base_state::call_on_close()
	{
	}

	void ql::base_state::call_before_close()
	{
	}

	void ql::base_state::call_on_activate()
	{
	}

	void ql::base_state::draw_call()
	{
		this->state_manager->draw_call();
	}

	void ql::base_state::display()
	{
		this->state_manager->display();
	}

	bool ql::base_state::game_loop_segment()
	{
		return this->state_manager->game_loop_segment();
	}

	void ql::base_state::set_antialising_level(ql::u32 antialising)
	{
		this->state_manager->context_settings.antialiasingLevel = antialising;
	}

	void ql::base_state::set_sRGB(bool srgb)
	{
		this->state_manager->context_settings.sRgbCapable = srgb;
	}

	void ql::base_state::set_depth_bits(ql::u32 depth_bits)
	{
		this->state_manager->context_settings.depthBits = depth_bits;
	}

	void ql::base_state::set_shader(const std::string& name)
	{
		this->render_states.shader = &ql::get_shader(name);
	}

	void ql::base_state::set_shader(sf::Shader& shader)
	{
		this->render_states.shader = &shader;
	}

	void ql::base_state::unbind_shader()
	{
		this->render_states.shader = nullptr;
	}

	void ql::base_state::set_active(bool active)
	{
		this->state_manager->set_active(active);
	}

	void ql::base_state::push_gl_states()
	{
		this->states_pushed = true;
		this->state_manager->push_gl_states();
	}

	void ql::base_state::pop_gl_states()
	{
		this->states_pushed = false;
		this->state_manager->pop_gl_states();
	}
#if defined QL_GLEW
	void ql::base_state::enable_gl()
	{
		this->use_gl = true;

		if (!this->state_manager->created_gl)
		{
			this->state_manager->create_gl();
		}
	}

	void ql::base_state::disable_gl()
	{
		this->use_gl = false;
	}
#endif

	void ql::base_state::reset_view()
	{
		this->render_states = sf::RenderStates::Default;
	}

	void ql::base_state::create()
	{
		return this->state_manager->create();
	}

	bool ql::base_state::is_open() const
	{
		return this->state_manager->is_open();
	}

	void ql::base_state::update_close_window()
	{
		if (this->event().window_closed() && this->is_allow_exit)
		{
			this->call_before_close();
			this->state_manager->window.close();
			this->call_on_close();
		}
	}

	void ql::base_state::hide_cursor()
	{
		this->state_manager->hide_cursor();
	}

	void ql::base_state::show_cursor()
	{
		this->state_manager->show_cursor();
	}

	void ql::base_state::set_cursor_hand()
	{
		this->state_manager->set_cursor_hand();
	}

	void ql::base_state::set_cursor_arrow()
	{
		this->state_manager->set_cursor_arrow();
	}

	void ql::base_state::set_cursor_position(ql::vector2i position)
	{
		this->state_manager->set_cursor_position(position);
	}

	void ql::base_state::set_window_position(ql::vector2u position)
	{
		this->state_manager->set_window_position(position);
	}

	ql::vector2u ql::base_state::get_window_position() const
	{
		return this->state_manager->get_window_position();
	}

	void ql::base_state::set_speed_factor(ql::f64 speed)
	{
		this->speed_factor = speed;
	}

	ql::vector2i ql::base_state::dimension() const
	{
		return this->state_manager->dimension;
	}

	ql::vec2 ql::base_state::center() const
	{
		return ql::vec2(this->state_manager->dimension) / 2;
	}

	void ql::base_state::play_sound(const std::string& name, ql::f32 volume, ql::f32 speed)
	{
		ql::play_sound(name, volume, speed);
	}

	void ql::base_state::add_font(const std::string& name, const std::string& path)
	{
		ql::add_font(name, path);
	}

	void ql::base_state::add_sound(const std::string& name, const std::string& path)
	{
		ql::add_sound(name, path);
	}

	void ql::base_state::add_texture(const std::string& name, const std::string& path)
	{
		ql::add_texture(name, path);
	}

	void ql::base_state::add_sprite(const std::string& name, const std::string& path)
	{
		ql::add_sprite(name, path);
	}

	void ql::base_state::add_sprite(const std::string& name, sf::Texture& texture)
	{
		ql::add_sprite(name, texture);
	}

	void ql::base_state::add_shader(const std::string& name, const std::string& path, sf::Shader::Type shader_type)
	{
		ql::add_shader(name, path, shader_type);
	}

	void ql::base_state::add_shader(const std::string& name, const std::string& path)
	{
		ql::add_shader(name, path);
	}

	void ql::base_state::add_text(const std::string& name)
	{
		ql::add_text(name);
	}

	void ql::base_state::add_font_from_memory(const std::string& name, const std::string& memory)
	{
		ql::add_font_from_memory(name, memory);
	}

	void ql::base_state::add_sound_from_memory(const std::string& name, const std::string& memory)
	{
		ql::add_sound_from_memory(name, memory);
	}

	void ql::base_state::add_texture_from_memory(const std::string& name, const std::string& memory)
	{
		ql::add_texture_from_memory(name, memory);
	}

	void ql::base_state::add_shader_from_memory(const std::string& name, const std::string& memory, sf::Shader::Type shader_type)
	{
		ql::add_shader_from_memory(name, memory, shader_type);
	}

	sf::Font& ql::base_state::get_font(const std::string& name)
	{
		return ql::get_font(name);
	}

	sf::SoundBuffer& ql::base_state::get_sound(const std::string& name)
	{
		return ql::get_sound(name);
	}

	sf::Texture& ql::base_state::get_texture(const std::string& name)
	{
		return ql::get_texture(name);
	}

	sf::Sprite& ql::base_state::get_sprite(const std::string& name)
	{
		return ql::get_sprite(name);
	}

	sf::Shader& ql::base_state::get_shader(const std::string& name)
	{
		return ql::get_shader(name);
	}

	ql::text& ql::base_state::get_text(const std::string& name)
	{
		return ql::get_text(name);
	}

	const sf::Font& ql::base_state::get_font(const std::string& name) const
	{
		return ql::get_font(name);
	}

	const sf::SoundBuffer& ql::base_state::get_sound(const std::string& name) const
	{
		return ql::get_sound(name);
	}

	const sf::Texture& ql::base_state::get_texture(const std::string& name) const
	{
		return ql::get_texture(name);
	}

	const sf::Sprite& ql::base_state::get_sprite(const std::string& name) const
	{
		return ql::get_sprite(name);
	}

	const sf::Shader& ql::base_state::get_shader(const std::string& name) const
	{
		return ql::get_shader(name);
	}

	const ql::text& ql::base_state::get_text(const std::string& name) const
	{
		return ql::get_text(name);
	}

	void ql::base_state::add_render(const std::string& name, bool smooth)
	{
		this->state_manager->add_render(name, smooth);
	}

	ql::render_texture& ql::base_state::get_render(const std::string& name)
	{
		return this->state_manager->get_render(name);
	}

	const ql::render_texture& ql::base_state::get_render(const std::string& name) const
	{
		return this->state_manager->get_render(name);
	}

	void ql::base_state::pop_this_state()
	{
		this->is_pop_this_state = true;
	}

	void ql::base_state::allow_exit()
	{
		this->is_allow_exit = true;
	}

	void ql::base_state::disallow_exit()
	{
		this->is_allow_exit = false;
	}

	bool ql::base_state::is_exit_allowed() const
	{
		return this->is_allow_exit;
	}

	void ql::base_state::allow_clear()
	{
		this->is_allow_clear = true;
	}

	void ql::base_state::disallow_clear()
	{
		this->is_allow_clear = false;
	}

	bool ql::base_state::is_clear_allowed() const
	{
		return this->is_allow_clear;
	}

	void ql::base_state::allow_display()
	{
		this->is_allow_display = true;
	}

	void ql::base_state::disallow_display()
	{
		this->is_allow_display = false;
	}

	bool ql::base_state::is_display_allowed() const
	{
		return this->is_allow_display;
	}

	void ql::base_state::enable_call_resize_call_on_init()
	{
		this->call_resize_call_on_init = true;
	}

	void ql::base_state::disable_call_resize_call_on_init()
	{
		this->call_resize_call_on_init = false;
	}

	bool ql::base_state::is_call_resize_call_on_init() const
	{
		return this->call_resize_call_on_init;
	}

	bool ql::base_state::has_focus() const
	{
		return this->state_manager->has_focus();
	}

	bool ql::base_state::has_gained_focus() const
	{
		return this->state_manager->has_gained_focus();
	}

	bool ql::base_state::has_lost_focus() const
	{
		return this->state_manager->has_lost_focus();
	}

	void ql::base_state::close()
	{
		this->state_manager->close();
	}

	ql::size ql::base_state::frame_count() const
	{
		return this->frame_ctr;
	}

	ql::time ql::base_state::get_no_focus_time() const
	{
		return this->state_manager->get_no_focus_time();
	}

	ql::time ql::base_state::frame_time() const
	{
		return this->state_manager->frame_time();
	}

	ql::f64 ql::base_state::frame_time_f() const
	{
		return this->state_manager->frame_time().secs_f();
	}

	ql::time ql::base_state::run_time() const
	{
		return this->state_manager->run_time();
	}

	const ql::event_info& ql::base_state::event() const
	{
		return this->state_manager->event;
	}

	ql::event_info& ql::base_state::event()
	{
		return this->state_manager->event;
	}
}	 // namespace ql

#endif