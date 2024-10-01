#include <ql/graphic/framework.hpp>

#if defined QL_SFML

#if defined QL_GLEW
#include <ql/QGL/glew.hpp>
#include <ql/QGL/shader.hpp>
#endif

namespace ql
{
	ql::framework::framework()
	{
		this->set_title(" ");
		this->set_dimension({1280, 720});
		this->set_style(sf::Style::Default);
#if defined QL_GLEW
		this->disable_gl();
#endif
		this->created = false;
	}

	ql::framework::~framework()
	{
#if defined QL_GLEW
		if (this->created_gl)
		{
			this->destroy_gl();
		}
#endif
	}

	void ql::framework::draw_call()
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

	void ql::framework::init_back()
	{
		if (this->states.size() && !this->states.back()->is_initalized)
		{
			this->states.back()->init();
			this->states.back()->is_initalized = true;
			if (this->call_resize_call_on_init && this->states.back()->call_resize_call_on_init)
			{
				this->states.back()->call_on_resize();
			}
		}
	}

	void ql::framework::display()
	{
		this->window.display();
	}

	void ql::framework::internal_update()
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
		ql::update_tasks();
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

	bool ql::framework::game_loop_segment()
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
		if (allow_draw)
		{
			this->draw_call();
		}
		return true;
	}

	void ql::framework::game_loop()
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
	void ql::framework::enable_gl()
	{
		this->context_settings.depthBits = 24;
		this->context_settings.sRgbCapable = false;
		this->context_settings.antialiasingLevel = 12u;
		this->use_gl = true;
	}

	void ql::framework::disable_gl()
	{
		this->context_settings.depthBits = 0;
		this->context_settings.antialiasingLevel = 12u;
		this->use_gl = false;
	}

	void ql::framework::create_gl()
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

	void ql::framework::destroy_gl()
	{
		for (auto& shader : qgl::shaders)
		{
			shader.second.destroy();
		}
	}

	void ql::framework::resize_gl()
	{
		qgl::gl::viewport(0, 0, this->dimension.x, this->dimension.y);
	}
#endif
	void ql::framework::enable_vsync()
	{
		this->use_vsync = true;
		this->window.setVerticalSyncEnabled(this->use_vsync);
	}

	void ql::framework::disable_vsync()
	{
		this->use_vsync = false;
		this->window.setVerticalSyncEnabled(this->use_vsync);
	}

	bool ql::framework::is_vsync_enabled()
	{
		return this->use_vsync;
	}

	void ql::framework::set_active(bool active)
	{
		this->window.setActive(active);
	}

	void ql::framework::push_gl_states()
	{
		this->window.pushGLStates();
	}

	void ql::framework::pop_gl_states()
	{
		this->window.popGLStates();
	}

	void ql::framework::set_framerate_limit(ql::u32 value)
	{
		this->framerate_limit = value;
	}

	ql::u32 ql::framework::get_framerate_limit() const
	{
		return this->framerate_limit;
	}

	void ql::framework::disable_framerate_limit()
	{
		this->framerate_limit = 0u;
	}

	void ql::framework::enable_update_if_no_focus()
	{
		this->update_if_no_focus = true;
	}

	void ql::framework::disable_update_if_no_focus()
	{
		this->update_if_no_focus = false;
	}

	bool ql::framework::is_update_if_no_focus_enabled() const
	{
		return this->update_if_no_focus;
	}

	void ql::framework::enable_call_resize_call_on_init()
	{
		this->call_resize_call_on_init = true;
	}

	void ql::framework::disable_call_resize_call_on_init()
	{
		this->call_resize_call_on_init = false;
	}

	bool ql::framework::is_call_resize_call_on_init() const
	{
		return this->call_resize_call_on_init;
	}

	bool ql::framework::has_focus() const
	{
		return this->focus;
	}

	bool ql::framework::has_gained_focus() const
	{
		return this->gained_focus;
	}

	bool ql::framework::has_lost_focus() const
	{
		return this->lost_focus;
	}

	void ql::framework::close()
	{
		this->window.close();
	}

	ql::time ql::framework::get_no_focus_time() const
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

	ql::time ql::framework::run_time() const
	{
		return this->run_time_clock.elapsed();
	}

	ql::time ql::framework::frame_time() const
	{
		return this->frametime;
	}

	void ql::framework::add_render(const std::string& name, bool smooth)
	{
		this->render_textures[name].set_antialiasing(this->context_settings.antialiasingLevel);
		this->render_textures[name].resize(this->dimension, true);
		this->render_textures[name].set_smooth(smooth);
	}

	ql::render_texture& ql::framework::get_render(const std::string& name)
	{
		if (this->render_textures.find(name) == this->render_textures.cend())
		{
			throw std::runtime_error(ql::to_string("couldn't find render with name \"", name, "\""));
		}
		return this->render_textures[name];
	}

	const ql::render_texture& ql::framework::get_render(const std::string& name) const
	{
		if (this->render_textures.find(name) == this->render_textures.cend())
		{
			throw std::runtime_error(ql::to_string("couldn't find render with name \"", name, "\""));
		}
		return this->render_textures.at(name);
	}

	void ql::framework::play_sound(const std::string& name, ql::f32 volume, ql::f32 speed)
	{
		ql::play_sound(name, volume, speed);
	}

	void ql::framework::add_font(const std::string& name, const std::string& path)
	{
		ql::add_font(name, path);
	}

	void ql::framework::add_sound(const std::string& name, const std::string& path)
	{
		ql::add_sound(name, path);
	}

	void ql::framework::add_texture(const std::string& name, const std::string& path)
	{
		ql::add_texture(name, path);
	}

	void ql::framework::add_image(const std::string& name, const std::string& path)
	{
		ql::add_image(name, path);
	}

	void ql::framework::add_sprite(const std::string& name, const std::string& path)
	{
		ql::add_sprite(name, path);
	}

	void ql::framework::add_sprite(const std::string& name, sf::Texture& texture)
	{
		ql::add_sprite(name, texture);
	}

	void ql::framework::add_shader(const std::string& name, const std::string& path, sf::Shader::Type shader_type)
	{
		ql::add_shader(name, path, shader_type);
	}

	void ql::framework::add_shader(const std::string& name, const std::string& path)
	{
		ql::add_shader(name, path);
	}

	void ql::framework::add_text(const std::string& name)
	{
		ql::add_text(name);
	}

	void ql::framework::add_font_from_memory(const std::string& name, const std::string& memory)
	{
		ql::add_font_from_memory(name, memory);
	}

	void ql::framework::add_sound_from_memory(const std::string& name, const std::string& memory)
	{
		ql::add_sound_from_memory(name, memory);
	}

	void ql::framework::add_texture_from_memory(const std::string& name, const std::string& memory)
	{
		ql::add_texture_from_memory(name, memory);
	}

	void ql::framework::add_shader_from_memory(const std::string& name, const std::string& memory, sf::Shader::Type shader_type)
	{
		ql::add_shader_from_memory(name, memory, shader_type);
	}

	sf::Font& ql::framework::get_font(const std::string& name)
	{
		return ql::get_font(name);
	}

	sf::SoundBuffer& ql::framework::get_sound(const std::string& name)
	{
		return ql::get_sound(name);
	}

	sf::Texture& ql::framework::get_texture(const std::string& name)
	{
		return ql::get_texture(name);
	}

	sf::Sprite& ql::framework::get_sprite(const std::string& name)
	{
		return ql::get_sprite(name);
	}

	sf::Image& ql::framework::get_image(const std::string& name)
	{
		return ql::get_image(name);
	}

	sf::Shader& ql::framework::get_shader(const std::string& name)
	{
		return ql::get_shader(name);
	}

	ql::text& ql::framework::get_text(const std::string& name)
	{
		return ql::get_text(name);
	}

	const sf::Font& ql::framework::get_font(const std::string& name) const
	{
		return ql::get_font(name);
	}

	const sf::SoundBuffer& ql::framework::get_sound(const std::string& name) const
	{
		return ql::get_sound(name);
	}

	const sf::Texture& ql::framework::get_texture(const std::string& name) const
	{
		return ql::get_texture(name);
	}

	const sf::Image& ql::framework::get_image(const std::string& name) const
	{
		return ql::get_image(name);
	}

	const sf::Sprite& ql::framework::get_sprite(const std::string& name) const
	{
		return ql::get_sprite(name);
	}

	const sf::Shader& ql::framework::get_shader(const std::string& name) const
	{
		return ql::get_shader(name);
	}

	const ql::text& ql::framework::get_text(const std::string& name) const
	{
		return ql::get_text(name);
	}

	void ql::framework::create()
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

	bool ql::framework::is_open() const
	{
		return this->window.isOpen();
	}

	bool ql::framework::is_created() const
	{
		return this->created;
	}

	void ql::framework::set_info(const std::string& title, ql::vector2u dimension, ql::u32 style)
	{
		this->set_title(title);
		this->set_dimension(dimension);
		this->set_style(style);
	}

	void ql::framework::set_title(const std::string& title)
	{
		this->title = title;
		if (this->created)
		{
			this->window.setTitle(title);
		}
	}

	void ql::framework::set_dimension(ql::vector2u dimension)
	{
		this->dimension = dimension;
		this->event.m_screen_dimension = dimension;

		for (auto& i : this->states)
		{
			i->last_dimension = this->dimension;
		}
	}

	void ql::framework::set_style(ql::u32 style)
	{
		this->style = style;
	}

	void ql::framework::set_antialiasing_level(ql::u32 level)
	{
		this->context_settings.antialiasingLevel = level;
	}

	void ql::framework::hide_cursor()
	{
		this->window.setMouseCursorVisible(false);
	}

	void ql::framework::set_cursor_hand()
	{
		sf::Cursor cursor;
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->window.setMouseCursor(cursor);
	}

	void ql::framework::set_cursor_arrow()
	{
		sf::Cursor cursor;
		cursor.loadFromSystem(sf::Cursor::Arrow);
		this->window.setMouseCursor(cursor);
	}

	void ql::framework::set_window_position(ql::vector2u position)
	{
		this->window.setPosition(sf::Vector2i(position));
	}

	ql::vector2u ql::framework::get_window_position() const
	{
		return ql::vector2u(this->window.getPosition());
	}

	void ql::framework::show_cursor()
	{
		this->window.setMouseCursorVisible(true);
	}

	void ql::framework::set_cursor_position(ql::vector2i position)
	{
		sf::Mouse::setPosition(position, this->window);
		this->event.m_mouse_position_screen = position;
		this->event.m_delta_mouse_position = this->event.m_mouse_position_screen_before - this->event.m_mouse_position_screen;
		this->event.m_mouse_position_screen_before = this->event.m_mouse_position_screen;
	}

	void ql::framework::set_speed_factor(ql::f64 speed)
	{
		this->speed_factor = speed;
	}

	void ql::framework::set_icon(std::string path, std::string name)
	{
		this->add_image(name, path);
		const auto& image = this->get_image(name);
		this->window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
	}

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
			this->framework->window.clear(this->clear_color);
		}
#else
		this->framework->window.clear(this->clear_color);
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
		this->framework->draw_call();
	}

	void ql::base_state::display()
	{
		this->framework->display();
	}

	bool ql::base_state::game_loop_segment()
	{
		return this->framework->game_loop_segment();
	}

	void ql::base_state::set_antialising_level(ql::u32 antialising)
	{
		this->framework->context_settings.antialiasingLevel = antialising;
	}

	void ql::base_state::set_sRGB(bool srgb)
	{
		this->framework->context_settings.sRgbCapable = srgb;
	}

	void ql::base_state::set_depth_bits(ql::u32 depth_bits)
	{
		this->framework->context_settings.depthBits = depth_bits;
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
		this->framework->set_active(active);
	}

	void ql::base_state::push_gl_states()
	{
		this->states_pushed = true;
		this->framework->push_gl_states();
	}

	void ql::base_state::pop_gl_states()
	{
		this->states_pushed = false;
		this->framework->pop_gl_states();
	}
#if defined QL_GLEW
	void ql::base_state::enable_gl()
	{
		this->use_gl = true;

		if (!this->framework->created_gl)
		{
			this->framework->create_gl();
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
		return this->framework->create();
	}

	bool ql::base_state::is_open() const
	{
		return this->framework->is_open();
	}

	void ql::base_state::update_close_window()
	{
		if (this->event().window_closed() && this->is_allow_exit)
		{
			this->call_before_close();
			this->framework->window.close();
			this->call_on_close();
		}
	}

	void ql::base_state::hide_cursor()
	{
		this->framework->hide_cursor();
	}

	void ql::base_state::show_cursor()
	{
		this->framework->show_cursor();
	}

	void ql::base_state::set_cursor_hand()
	{
		this->framework->set_cursor_hand();
	}

	void ql::base_state::set_cursor_arrow()
	{
		this->framework->set_cursor_arrow();
	}

	void ql::base_state::set_cursor_position(ql::vector2i position)
	{
		this->framework->set_cursor_position(position);
	}

	void ql::base_state::set_window_position(ql::vector2u position)
	{
		this->framework->set_window_position(position);
	}

	ql::vector2u ql::base_state::get_window_position() const
	{
		return this->framework->get_window_position();
	}

	void ql::base_state::set_speed_factor(ql::f64 speed)
	{
		this->speed_factor = speed;
	}

	ql::vector2i ql::base_state::dimension() const
	{
		return this->framework->dimension;
	}

	ql::vec2 ql::base_state::center() const
	{
		return ql::vec2(this->framework->dimension) / 2;
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
		this->framework->add_render(name, smooth);
	}

	ql::render_texture& ql::base_state::get_render(const std::string& name)
	{
		return this->framework->get_render(name);
	}

	const ql::render_texture& ql::base_state::get_render(const std::string& name) const
	{
		return this->framework->get_render(name);
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
		return this->framework->has_focus();
	}

	bool ql::base_state::has_gained_focus() const
	{
		return this->framework->has_gained_focus();
	}

	bool ql::base_state::has_lost_focus() const
	{
		return this->framework->has_lost_focus();
	}

	void ql::base_state::close()
	{
		this->framework->close();
	}

	ql::size ql::base_state::frame_count() const
	{
		return this->frame_ctr;
	}

	ql::time ql::base_state::get_no_focus_time() const
	{
		return this->framework->get_no_focus_time();
	}

	ql::time ql::base_state::frame_time() const
	{
		return this->framework->frame_time();
	}

	ql::f64 ql::base_state::frame_time_f() const
	{
		return this->framework->frame_time().secs_f();
	}

	ql::time ql::base_state::run_time() const
	{
		return this->framework->run_time();
	}

	const ql::event_info& ql::base_state::event() const
	{
		return this->framework->event;
	}

	ql::event_info& ql::base_state::event()
	{
		return this->framework->event;
	}
}	 // namespace ql

#endif