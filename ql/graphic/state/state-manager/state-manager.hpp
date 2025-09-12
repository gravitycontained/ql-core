
#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/signal/signal-update-manager/signal-update-manager.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/drawable/drawable.hpp>

#include <ql/graphic/render/render.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ql/graphic/event/event.hpp>
#include <ql/graphic/resources/resources.hpp>

namespace ql
{

	template <typename T>
	struct view_control_t;

	enum class cull_face : ql::u8
	{
		back,
		front,
		front_and_back,
	};

	struct base_state;

	struct state_manager
	{
		QL_SOURCE state_manager();
		QL_SOURCE ~state_manager();

		template <typename C>
		requires (std::is_base_of_v<ql::base_state, C>)
		void add_state()
		{
			this->states.push_back(std::make_unique<C>());
			this->states.back()->state_manager = this;

#if defined QL_GLEW
			this->states.back()->use_gl = this->use_gl;
#endif

			this->states.back()->call_before_create();

			if (this->states.back()->is_pop_this_state)
			{
				this->states.pop_back();
				if (this->states.empty())
				{
					return;
				}
			}
			this->states.back()->last_dimension = this->dimension;
			if (this->is_created())
			{
				this->init_back();
			}
		}

		template <typename C>
		requires (std::is_base_of_v<ql::base_state, C>)
		void add_state(C& state)
		{
			this->states.push_back(std::make_unique<C>(state));
			this->states.back()->framework = this;
			this->states.back()->call_before_create();
			this->states.back()->last_dimension = this->dimension;
			if (this->is_created())
			{
				this->init_back();
			}
		}

		QL_SOURCE void pop_last_state();

		QL_SOURCE void draw_call();
		QL_SOURCE void init_back();

		QL_SOURCE void display();
		QL_SOURCE void internal_update();
		QL_SOURCE bool game_loop_segment();
		QL_SOURCE void game_loop();

#if defined QL_GLEW
		QL_SOURCE void enable_gl();
		QL_SOURCE void disable_gl();
		QL_SOURCE void create_gl();
		QL_SOURCE void destroy_gl();
		QL_SOURCE void resize_gl();
#endif
		QL_SOURCE void enable_vsync();
		QL_SOURCE void disable_vsync();
		QL_SOURCE bool is_vsync_enabled();

		QL_SOURCE void set_active(bool active = true);
		QL_SOURCE void push_gl_states();
		QL_SOURCE void pop_gl_states();

		QL_SOURCE void set_framerate_limit(ql::u32 value);
		QL_SOURCE ql::u32 get_framerate_limit() const;
		QL_SOURCE void disable_framerate_limit();
		QL_SOURCE void enable_update_if_no_focus();
		QL_SOURCE void disable_update_if_no_focus();
		QL_SOURCE bool is_update_if_no_focus_enabled() const;
		QL_SOURCE void enable_call_resize_call_on_init();
		QL_SOURCE void disable_call_resize_call_on_init();
		QL_SOURCE bool is_call_resize_call_on_init() const;
		QL_SOURCE bool has_focus() const;
		QL_SOURCE bool has_gained_focus() const;
		QL_SOURCE bool has_lost_focus() const;
		QL_SOURCE void close();
		QL_SOURCE ql::time get_no_focus_time() const;
		QL_SOURCE ql::time run_time() const;
		QL_SOURCE ql::time frame_time() const;
		QL_SOURCE void add_render(const std::string& name, bool smooth);
		QL_SOURCE ql::render_texture& get_render(const std::string& name);
		QL_SOURCE const ql::render_texture& get_render(const std::string& name) const;

		QL_SOURCE void provide();
		QL_SOURCE void initialize();
		QL_SOURCE void update_injection();
		QL_SOURCE void check_uninitialized();

		QL_SOURCE void play_sound(const std::string& name, ql::f32 volume, ql::f32 speed);
		QL_SOURCE void add_font(const std::string& name, const std::string& path);
		QL_SOURCE void add_sound(const std::string& name, const std::string& path);
		QL_SOURCE void add_texture(const std::string& name, const std::string& path, bool set_smooth = false);
		QL_SOURCE void add_image(const std::string& name, const std::string& path);
		QL_SOURCE void add_sprite(const std::string& name, const std::string& path);
		QL_SOURCE void add_sprite(const std::string& name, sf::Texture& texture);
		QL_SOURCE void add_shader(const std::string& name, const std::string& path, sf::Shader::Type shader_type);
		QL_SOURCE void add_shader(const std::string& name, const std::string& path);

		QL_SOURCE void add_font_from_memory(const std::string& name, const std::string& memory);
		QL_SOURCE void add_sound_from_memory(const std::string& name, const std::string& memory);
		QL_SOURCE void add_texture_from_memory(const std::string& name, const std::string& memory);
		QL_SOURCE void add_shader_from_memory(const std::string& name, const std::string& memory, sf::Shader::Type shader_type);

		QL_SOURCE sf::Font& get_font(const std::string& name);
		QL_SOURCE sf::SoundBuffer& get_sound(const std::string& name);
		QL_SOURCE sf::Texture& get_texture(const std::string& name);
		QL_SOURCE sf::Sprite& get_sprite(const std::string& name);
		QL_SOURCE sf::Image& get_image(const std::string& name);
		QL_SOURCE sf::Shader& get_shader(const std::string& name);

		QL_SOURCE const sf::Font& get_font(const std::string& name) const;
		QL_SOURCE const sf::SoundBuffer& get_sound(const std::string& name) const;
		QL_SOURCE const sf::Texture& get_texture(const std::string& name) const;
		QL_SOURCE const sf::Sprite& get_sprite(const std::string& name) const;
		QL_SOURCE const sf::Image& get_image(const std::string& name) const;
		QL_SOURCE const sf::Shader& get_shader(const std::string& name) const;

		QL_SOURCE void create();
		QL_SOURCE bool is_open() const;
		QL_SOURCE bool is_created() const;
		QL_SOURCE void set_info(const std::string& title, ql::vector2u dimension, ql::u32 style);
		QL_SOURCE void set_title(const std::string& title);
		QL_SOURCE void set_dimension(ql::vector2u dimension);
		QL_SOURCE void set_style(ql::u32 style);
		QL_SOURCE void set_antialiasing_level(ql::u32 level);
		QL_SOURCE void hide_cursor();
		QL_SOURCE void set_cursor_hand();
		QL_SOURCE void set_cursor_arrow();
		QL_SOURCE void set_window_position(ql::vector2u position);
		QL_SOURCE ql::vector2u get_window_position() const;
		QL_SOURCE void show_cursor();
		QL_SOURCE void set_cursor_position(ql::vector2i position);
		QL_SOURCE void set_speed_factor(ql::f64 speed);
		QL_SOURCE void set_icon(std::string path, std::string name = "icon");

		std::vector<std::unique_ptr<ql::base_state>> states;
		ql::event event;
		ql::signal_update_manager signal_update_manager;

		sf::RenderWindow window;
		std::unordered_map<std::string, ql::render_texture> render_textures;
		sf::ContextSettings context_settings;
		std::string title;
		ql::vector2u dimension;
		ql::small_clock run_time_clock;
		ql::small_clock frametime_clock;
		ql::small_clock no_focus_timer;
		ql::time frametime;
		ql::time no_focus_time;
		ql::size state_size_before = 0u;
		ql::u32 framerate_limit = 144u;
		ql::u32 style = sf::Style::Default;
		ql::f64 speed_factor = 1.0;
		ql::size frame_ctr = 0u;
		cull_face gl_cull_face = cull_face::back;
		bool created = false;
		bool created_gl = false;
		bool update_if_no_focus = true;
		bool focus = true;
		bool lost_focus = false;
		bool gained_focus = false;
		bool use_gl = false;
		bool use_vsync = false;
		bool call_resize_call_on_init = true;
	};


	namespace detail
	{
		QL_SOURCE extern ql::state_manager* state_manager;

		QL_SOURCE void register_state_manager(ql::state_manager& state_manager);
	}

}	 // namespace ql

#endif