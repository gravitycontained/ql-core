#include <ql/graphic/state/state-manager/state-manager.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/state/base-state/base-state.hpp>
#include <ql/core/advanced-type/signal/signal.hpp>

#if defined QL_GLEW
#include <ql/QGL/glew.hpp>
#include <ql/QGL/shader.hpp>
#endif

namespace ql
{
	state_manager::state_manager()
	{
		this->set_title(" ");
		this->set_dimension({1280, 720});
		this->set_style(sf::Style::Default);

		#if defined QL_GLEW
			this->disable_gl();
		#endif

		this->created = false;
	}

	state_manager::~state_manager()
	{
		#if defined QL_GLEW
			if (this->created_gl)
			{
				this->destroy_gl();
			}
		#endif
	}

	void state_manager::pop_last_state()
	{
		if (this->states.size())
		{
			this->states.back()->is_pop_this_state = true;
		}
	
	}

	void state_manager::draw_call()
	{
		if (this->states.back()->is_clear_allowed())
		{
			this->states.back()->clear();
			for (auto& i : this->render_textures)
			{
				if (i.second.is_clear_with_window_enabled())
				{
					i.second.clear();
				}
			}
		}
		this->states.back()->drawing();
		if (this->states.back()->is_display_allowed())
		{
			this->window.display();
		}
	}

	void state_manager::init_back()
	{
		if (this->states.size() && !this->states.back()->is_initalized)
		{
			this->states.back()->initializing_interaction();
			this->states.back()->initializing();
			this->states.back()->is_initalized = true;
			if (this->call_resize_call_on_init && this->states.back()->call_resize_call_on_init)
			{
				this->states.back()->call_on_resize();
			}
		}
	}

	void state_manager::display()
	{
		this->window.display();
	}

	void state_manager::internal_update()
	{
		this->frametime = this->frametime_clock.elapsed_reset();

		this->event.reset(this->window);
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			this->event.update(event);
		}
		ql::f64 f = this->frametime.nsecs() * this->speed_factor;
		if (this->states.size())
		{
			f *= this->states.back()->speed_factor;
		}
		this->event.m_frame_time = ql::time(ql::u64_cast(f));

		if (this->event.resized())
		{
			auto new_dimension = this->event.resized_size();
			sf::FloatRect view(0.0f, 0.0f, static_cast<float>(new_dimension.x), static_cast<float>(new_dimension.y));
			this->window.setView(sf::View(view));
			this->dimension = new_dimension;
			this->event.m_screen_dimension = this->dimension;

			for (auto& i : this->render_textures)
			{
				if (i.second.is_resize_with_window_enabled())
				{
					i.second.resize(new_dimension, true);
				}
			}

#if defined QL_GLEW
			if (this->use_gl && this->states.back()->use_gl)
			{
				this->resize_gl();
			}
#endif

			this->states.back()->call_on_resize();
		}

		ql::update_sounds();
		//ql::update_tasks();
		auto focus_before = this->focus;
		auto focus = this->window.hasFocus();
		this->focus = focus;
		this->lost_focus = (focus_before && !focus);
		this->gained_focus = (!focus_before && focus);
		if (this->lost_focus)
		{
			this->no_focus_timer.reset();
		}
		if (this->gained_focus)
		{
			this->no_focus_time = this->no_focus_timer.elapsed();
		}
	}

	bool state_manager::game_loop_segment()
	{
		if (!this->is_created())
		{
			this->create();
		}

		auto focus_before = this->focus;
		this->internal_update();

		if (this->state_size_before != this->states.size())
		{
			this->states.back()->call_on_activate();
			this->state_size_before = this->states.size();
		}
		
		this->signal_update_manager.clear_list();
		this->signal_update_manager.reset_active();

		if (this->update_if_no_focus || this->focus || (focus_before != this->focus))
		{
			this->states.back()->updating();
			this->states.back()->last_dimension = this->dimension;
			++this->states.back()->frame_ctr;
		}
		this->states.back()->update_close_window();

		bool allow_draw = this->states.size() == this->state_size_before;
		if (this->states.back()->is_pop_this_state)
		{
			this->states.pop_back();
			if (this->states.empty())
			{
				return false;
			}
			this->init_back();
			this->states.back()->call_on_activate();
			this->state_size_before = this->states.size();
			allow_draw = false;
			if (this->states.back()->last_dimension != this->dimension)
			{
				this->states.back()->call_on_resize();
			}
		}

		if (this->states.size())
		{
			this->states.back()->updating_phase_signal_run();
			this->states.back()->updating_phase_signal_detect();

			for (ql::size ctr = 0u; this->signal_update_manager.active; ++ctr)
			{
				if (ctr > 1000u)
				{
					ql::println(ql::color::bright_yellow, ql::to_string("updating signals > 1000 cycles, breaking loop"));
					break;
				}
				ql::println("signals cycle ", ctr, " size: ", this->signal_update_manager.next_list.size());

				this->signal_update_manager.clear_list();
				this->signal_update_manager.reset_active();

				this->states.back()->updating_phase_signal_run();
				this->states.back()->updating_phase_signal_detect();
			}

		}


		if (allow_draw)
		{
			this->draw_call();
		}
		return true;
	}

	void state_manager::game_loop()
	{
		if (this->states.empty())
		{
			return;
		}
		if (!this->is_created())
		{
			this->create();
		}

		while (this->is_open())
		{
			if (!this->game_loop_segment())
			{
				break;
			}
		}
	}

#if defined QL_GLEW
	void state_manager::enable_gl()
	{
		this->context_settings.depthBits = 24;
		this->context_settings.sRgbCapable = false;
		this->context_settings.antialiasingLevel = 12u;
		this->use_gl = true;
	}

	void state_manager::disable_gl()
	{
		this->context_settings.depthBits = 0;
		this->context_settings.antialiasingLevel = 12u;
		this->use_gl = false;
	}

	void state_manager::create_gl()
	{
		if (!this->created)
		{
			this->create();
		}
		if (this->created_gl)
		{
			return;
		}
		this->created_gl = true;
		qgl::gl::enable(GL_DEPTH_TEST);
		qgl::gl::enable(GL_CULL_FACE);

		switch (this->gl_cull_face)
		{
			case cull_face::front:
				qgl::gl::cull_face(GL_FRONT);
				break;
			case cull_face::back:
				qgl::gl::cull_face(GL_BACK);
				break;
			case cull_face::front_and_back:
				qgl::gl::cull_face(GL_FRONT_AND_BACK);
				break;
		};

		qgl::gl::front_face(GL_CW);
		qgl::gl::enable_glew_experimental();

		this->resize_gl();
	}

	void state_manager::destroy_gl()
	{
		for (auto& shader : qgl::shaders)
		{
			shader.second.destroy();
		}
	}

	void state_manager::resize_gl()
	{
		qgl::gl::viewport(0, 0, this->dimension.x, this->dimension.y);
	}
#endif
	void state_manager::enable_vsync()
	{
		this->use_vsync = true;
		this->window.setVerticalSyncEnabled(this->use_vsync);
	}

	void state_manager::disable_vsync()
	{
		this->use_vsync = false;
		this->window.setVerticalSyncEnabled(this->use_vsync);
	}

	bool state_manager::is_vsync_enabled()
	{
		return this->use_vsync;
	}

	void state_manager::set_active(bool active)
	{
		this->window.setActive(active);
	}

	void state_manager::push_gl_states()
	{
		this->window.pushGLStates();
	}

	void state_manager::pop_gl_states()
	{
		this->window.popGLStates();
	}

	void state_manager::set_framerate_limit(ql::u32 value)
	{
		this->framerate_limit = value;
	}

	ql::u32 state_manager::get_framerate_limit() const
	{
		return this->framerate_limit;
	}

	void state_manager::disable_framerate_limit()
	{
		this->framerate_limit = 0u;
	}

	void state_manager::enable_update_if_no_focus()
	{
		this->update_if_no_focus = true;
	}

	void state_manager::disable_update_if_no_focus()
	{
		this->update_if_no_focus = false;
	}

	bool state_manager::is_update_if_no_focus_enabled() const
	{
		return this->update_if_no_focus;
	}

	void state_manager::enable_call_resize_call_on_init()
	{
		this->call_resize_call_on_init = true;
	}

	void state_manager::disable_call_resize_call_on_init()
	{
		this->call_resize_call_on_init = false;
	}

	bool state_manager::is_call_resize_call_on_init() const
	{
		return this->call_resize_call_on_init;
	}

	bool state_manager::has_focus() const
	{
		return this->focus;
	}

	bool state_manager::has_gained_focus() const
	{
		return this->gained_focus;
	}

	bool state_manager::has_lost_focus() const
	{
		return this->lost_focus;
	}

	void state_manager::close()
	{
		this->window.close();
	}

	ql::time state_manager::get_no_focus_time() const
	{
		if (this->focus || this->gained_focus)
		{
			return this->no_focus_time;
		}
		else
		{
			return ql::time(0);
		}
	}

	ql::time state_manager::run_time() const
	{
		return this->run_time_clock.elapsed();
	}

	ql::time state_manager::frame_time() const
	{
		return this->frametime;
	}

	void state_manager::add_render(const std::string& name, bool smooth)
	{
		this->render_textures[name].set_antialiasing(this->context_settings.antialiasingLevel);
		this->render_textures[name].resize(this->dimension, true);
		this->render_textures[name].set_smooth(smooth);
	}

	ql::render_texture& state_manager::get_render(const std::string& name)
	{
		if (this->render_textures.find(name) == this->render_textures.cend())
		{
			throw std::runtime_error(ql::to_string("couldn't find render with name \"", name, "\""));
		}
		return this->render_textures[name];
	}

	const ql::render_texture& state_manager::get_render(const std::string& name) const
	{
		if (this->render_textures.find(name) == this->render_textures.cend())
		{
			throw std::runtime_error(ql::to_string("couldn't find render with name \"", name, "\""));
		}
		return this->render_textures.at(name);
	}

	void state_manager::play_sound(const std::string& name, ql::f32 volume, ql::f32 speed)
	{
		ql::play_sound(name, volume, speed);
	}

	void state_manager::add_font(const std::string& name, const std::string& path)
	{
		ql::add_font(name, path);
	}

	void state_manager::add_sound(const std::string& name, const std::string& path)
	{
		ql::add_sound(name, path);
	}

	void state_manager::add_texture(const std::string& name, const std::string& path)
	{
		ql::add_texture(name, path);
	}

	void state_manager::add_image(const std::string& name, const std::string& path)
	{
		ql::add_image(name, path);
	}

	void state_manager::add_sprite(const std::string& name, const std::string& path)
	{
		ql::add_sprite(name, path);
	}

	void state_manager::add_sprite(const std::string& name, sf::Texture& texture)
	{
		ql::add_sprite(name, texture);
	}

	void state_manager::add_shader(const std::string& name, const std::string& path, sf::Shader::Type shader_type)
	{
		ql::add_shader(name, path, shader_type);
	}

	void state_manager::add_shader(const std::string& name, const std::string& path)
	{
		ql::add_shader(name, path);
	}

	void state_manager::add_font_from_memory(const std::string& name, const std::string& memory)
	{
		ql::add_font_from_memory(name, memory);
	}

	void state_manager::add_sound_from_memory(const std::string& name, const std::string& memory)
	{
		ql::add_sound_from_memory(name, memory);
	}

	void state_manager::add_texture_from_memory(const std::string& name, const std::string& memory)
	{
		ql::add_texture_from_memory(name, memory);
	}

	void state_manager::add_shader_from_memory(const std::string& name, const std::string& memory, sf::Shader::Type shader_type)
	{
		ql::add_shader_from_memory(name, memory, shader_type);
	}

	sf::Font& state_manager::get_font(const std::string& name)
	{
		return ql::get_font(name);
	}

	sf::SoundBuffer& state_manager::get_sound(const std::string& name)
	{
		return ql::get_sound(name);
	}

	sf::Texture& state_manager::get_texture(const std::string& name)
	{
		return ql::get_texture(name);
	}

	sf::Sprite& state_manager::get_sprite(const std::string& name)
	{
		return ql::get_sprite(name);
	}

	sf::Image& state_manager::get_image(const std::string& name)
	{
		return ql::get_image(name);
	}

	sf::Shader& state_manager::get_shader(const std::string& name)
	{
		return ql::get_shader(name);
	}

	const sf::Font& state_manager::get_font(const std::string& name) const
	{
		return ql::get_font(name);
	}

	const sf::SoundBuffer& state_manager::get_sound(const std::string& name) const
	{
		return ql::get_sound(name);
	}

	const sf::Texture& state_manager::get_texture(const std::string& name) const
	{
		return ql::get_texture(name);
	}

	const sf::Image& state_manager::get_image(const std::string& name) const
	{
		return ql::get_image(name);
	}

	const sf::Sprite& state_manager::get_sprite(const std::string& name) const
	{
		return ql::get_sprite(name);
	}

	const sf::Shader& state_manager::get_shader(const std::string& name) const
	{
		return ql::get_shader(name);
	}

	void state_manager::create()
	{
		if (!this->is_created())
		{
			sf::String s = this->title.c_str();

			this->event.m_screen_dimension = this->dimension;
			this->window.create(sf::VideoMode({this->dimension.x, this->dimension.y}), s, this->style, this->context_settings);
			this->window.setFramerateLimit(this->framerate_limit);
			this->created = true;

#if defined QL_GLEW
			if (this->use_gl)
			{
				this->create_gl();
			}
#endif

			if (this->states.size())
			{
				this->init_back();
			}
		}
	}

	bool state_manager::is_open() const
	{
		return this->window.isOpen();
	}

	bool state_manager::is_created() const
	{
		return this->created;
	}

	void state_manager::set_info(const std::string& title, ql::vector2u dimension, ql::u32 style)
	{
		this->set_title(title);
		this->set_dimension(dimension);
		this->set_style(style);
	}

	void state_manager::set_title(const std::string& title)
	{
		this->title = title;
		if (this->created)
		{
			this->window.setTitle(title);
		}
	}

	void state_manager::set_dimension(ql::vector2u dimension)
	{
		this->dimension = dimension;
		this->event.m_screen_dimension = dimension;

		for (auto& i : this->states)
		{
			i->last_dimension = this->dimension;
		}
	}

	void state_manager::set_style(ql::u32 style)
	{
		this->style = style;
	}

	void state_manager::set_antialiasing_level(ql::u32 level)
	{
		this->context_settings.antialiasingLevel = level;
	}

	void state_manager::hide_cursor()
	{
		this->window.setMouseCursorVisible(false);
	}

	void state_manager::set_cursor_hand()
	{
		sf::Cursor cursor;
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->window.setMouseCursor(cursor);
	}

	void state_manager::set_cursor_arrow()
	{
		sf::Cursor cursor;
		cursor.loadFromSystem(sf::Cursor::Arrow);
		this->window.setMouseCursor(cursor);
	}

	void state_manager::set_window_position(ql::vector2u position)
	{
		this->window.setPosition(sf::Vector2i(position));
	}

	ql::vector2u state_manager::get_window_position() const
	{
		return ql::vector2u(this->window.getPosition());
	}

	void state_manager::show_cursor()
	{
		this->window.setMouseCursorVisible(true);
	}

	void state_manager::set_cursor_position(ql::vector2i position)
	{
		sf::Mouse::setPosition(position, this->window);
		this->event.m_mouse_position_screen = position;
		this->event.m_delta_mouse_position = this->event.m_mouse_position_screen_before - this->event.m_mouse_position_screen;
		this->event.m_mouse_position_screen_before = this->event.m_mouse_position_screen;
	}

	void state_manager::set_speed_factor(ql::f64 speed)
	{
		this->speed_factor = speed;
	}

	void state_manager::set_icon(std::string path, std::string name)
	{
		this->add_image(name, path);
		const auto& image = this->get_image(name);
		this->window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	}

}	 // namespace ql

#endif