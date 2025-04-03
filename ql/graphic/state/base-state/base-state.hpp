#pragma once

#include <ql/core/definition/definition.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/state/state-manager/state-manager.hpp>

#include <ql/graphic/drawable/drawable.hpp>
#include <ql/graphic/render/render.hpp>

#include <ql/graphic/init/init.hpp>

#include <ql/graphic/sync/type/type.hpp>
#include <ql/graphic/sync/list.hpp>
#include <ql/graphic/sync/provide.hpp>
#include <ql/graphic/sync/check-uninitialized/check-uninitialized.hpp>

#include <ql/graphic/update/update.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ql
{

	/* TO OVERLOAD:
		void initializing() override {

		}
		void updating() override {

		}
		void drawing() override {

		}
	*/
	struct base_state
	{
		virtual ~base_state() = default;

		virtual void call_init() = 0;
		virtual void call_check_uninitialized() = 0;
		virtual void call_provide() = 0;
		virtual void call_update() = 0;
		virtual void call_update_injection() = 0;
		virtual void call_phase_signal_run() = 0;
		virtual void call_phase_signal_detect() = 0;
		virtual void call_draw() = 0;

		QL_SOURCE virtual void init_before();
		QL_SOURCE virtual void clear();
		QL_SOURCE virtual void call_on_resize();
		QL_SOURCE virtual void call_before_create();
		QL_SOURCE virtual void call_on_close();
		QL_SOURCE virtual void call_before_close();
		QL_SOURCE virtual void call_on_activate();

		QL_SOURCE void draw_call();
		QL_SOURCE void display();

		QL_SOURCE void set_antialising_level(ql::u32 antialising);
		QL_SOURCE void set_sRGB(bool srgb);
		QL_SOURCE void set_depth_bits(ql::u32 depth_bits);
		QL_SOURCE void set_shader(const std::string& name);
		QL_SOURCE void set_shader(sf::Shader& shader);
		QL_SOURCE void unbind_shader();
		QL_SOURCE void set_active(bool active = true);
		QL_SOURCE void push_gl_states();
		QL_SOURCE void pop_gl_states();

#if defined QL_GLEW
		QL_SOURCE void enable_gl();
		QL_SOURCE void disable_gl();
#endif

		template <typename T>
		void set_view(const ql::view_control_t<T>& view)
		{
			this->render_states.transform = view.get_render_states().transform;
		}

		QL_SOURCE void reset_view();

		template <typename T>
		void sync_check_uninitialized(T& object)
		{
			ql::sync_check_uninitialized(*this->state_manager);
		}
		template <typename T>
		void sync_init(T& object)
		{
			ql::init_state init_state{this->dimension()};
			ql::sync_init(object, *this->state_manager, init_state);
			ql::sync_init(object, *this->state_manager, *this->state_manager);
			this->sync_check_uninitialized(*this->state_manager);
		}

		template <typename T>
		void sync_provide(T& object)
		{
			ql::provide(object, std::ref(this->state_manager->signal_update_manager));
			ql::provide(object, *this->state_manager);
			ql::sync_provide(object);
			this->sync_check_uninitialized(*this->state_manager);
		}

		template <typename T>
		void sync_init_before(T& object)
		{
			ql::sync_init_before(object, *this->state_manager);
			this->sync_check_uninitialized(*this->state_manager);
		}

		template <typename T>
		void sync_update(T& object)
		{
			ql::init_state init_state{ this->dimension() };
			ql::render render(this->state_manager->window, this->render_states);
			ql::update_manager update{ this->event(), *this->state_manager, this->state_manager->signal_update_manager, render, init_state };
			ql::sync_update(object, *this->state_manager, update);
			this->sync_check_uninitialized(*this->state_manager);
		}

		template <typename T>
		void sync_update_injection(T& object)
		{
			ql::sync_update_injection(object, *this->state_manager);
			this->sync_check_uninitialized(*this->state_manager);
		}

		template <typename T>
		void sync_update_phase_signal_run(T& object)
		{
			ql::sync_update_phase_signal_run(object);
			this->sync_check_uninitialized(*this->state_manager);
		}

		template <typename T>
		void sync_update_phase_signal_detect(T& object)
		{
			ql::sync_update_phase_signal_detect(object);
		}

		template <typename T>
		void sync_draw(T& object)
		{
			ql::render render(this->state_manager->window, this->render_states);
			ql::sync_draw(object, render);
		}

		QL_SOURCE void create();
		QL_SOURCE bool is_open() const;
		QL_SOURCE void update_close_window();
		QL_SOURCE void hide_cursor();
		QL_SOURCE void show_cursor();
		QL_SOURCE void set_cursor_hand();
		QL_SOURCE void set_cursor_arrow();
		QL_SOURCE void set_cursor_position(ql::vector2i position);
		QL_SOURCE void set_window_position(ql::vector2u position);
		QL_SOURCE ql::vector2u get_window_position() const;
		QL_SOURCE void set_speed_factor(ql::f64 speed);
		QL_SOURCE ql::render get_render() const;

		QL_SOURCE ql::vector2i dimension() const;
		QL_SOURCE ql::vec2 center() const;

		QL_SOURCE void play_sound(const std::string& name, ql::f32 volume = 100.0f, ql::f32 speed = 1.0f);

		QL_SOURCE void add_font(const std::string& name, const std::string& path);
		QL_SOURCE void add_sound(const std::string& name, const std::string& path);
		QL_SOURCE void add_texture(const std::string& name, const std::string& path);
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
		QL_SOURCE sf::Shader& get_shader(const std::string& name);

		QL_SOURCE const sf::Font& get_font(const std::string& name) const;
		QL_SOURCE const sf::SoundBuffer& get_sound(const std::string& name) const;
		QL_SOURCE const sf::Texture& get_texture(const std::string& name) const;
		QL_SOURCE const sf::Sprite& get_sprite(const std::string& name) const;
		QL_SOURCE const sf::Shader& get_shader(const std::string& name) const;

		QL_SOURCE void add_render(const std::string& name, bool smooth = true);
		QL_SOURCE ql::render_texture& get_render(const std::string& name);
		QL_SOURCE const ql::render_texture& get_render(const std::string& name) const;

		template <typename C>
		requires (std::is_base_of_v<ql::base_state, C>)
		void add_state()
		{
			this->state_manager->add_state<C>();
		}

		QL_SOURCE void pop_this_state();
		QL_SOURCE void allow_exit();
		QL_SOURCE void disallow_exit();
		QL_SOURCE bool is_exit_allowed() const;
		QL_SOURCE void allow_clear();
		QL_SOURCE void disallow_clear();
		QL_SOURCE bool is_clear_allowed() const;
		QL_SOURCE void allow_display();
		QL_SOURCE void disallow_display();
		QL_SOURCE bool is_display_allowed() const;
		QL_SOURCE void enable_call_resize_call_on_init();
		QL_SOURCE void disable_call_resize_call_on_init();
		QL_SOURCE bool is_call_resize_call_on_init() const;
		QL_SOURCE bool has_focus() const;
		QL_SOURCE bool has_gained_focus() const;
		QL_SOURCE bool has_lost_focus() const;
		QL_SOURCE void close();

		QL_SOURCE ql::size frame_count() const;
		QL_SOURCE ql::time get_no_focus_time() const;
		QL_SOURCE ql::time frame_time() const;
		QL_SOURCE ql::f64 frame_time_f() const;
		QL_SOURCE ql::time run_time() const;
		QL_SOURCE const ql::event& event() const;
		QL_SOURCE ql::event& event();

		ql::state_manager* state_manager = nullptr;

		friend ql::state_manager;

	 protected:
		ql::rgb clear_color = ql::rgb::black();
		sf::RenderStates render_states = sf::RenderStates::Default;
		ql::vector2i last_dimension;
		ql::f64 speed_factor = 1.0;
		ql::size frame_ctr = 0u;
		bool is_initalized = false;
		bool is_pop_this_state = false;
		bool is_allow_exit = true;
		bool is_allow_clear = true;
		bool is_allow_display = true;
		bool use_gl = false;
		bool states_pushed = false;
		bool call_resize_call_on_init = true;
	};
}	 // namespace ql

#endif