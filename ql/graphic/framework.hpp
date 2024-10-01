#pragma once

#include <ql/core/definition/definition.hpp>
#if defined QL_SFML

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

#include <ql/graphic/event-info.hpp>
#include <ql/graphic/drawables.hpp>
#include <ql/graphic/resources.hpp>
#include <ql/core/advanced-type/graphic/graphic.hpp>

#include <ql/core/time/time.hpp>

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

	/*
	ql::framework framework;
	framework.set_dimension({ 1800, 720 });
	framework.set_title("x");
	framework.set_style(sf::Style::Default);
	framework.add_state<state>();
	framework.game_loop();
	*/
	struct framework
	{
		QL_SOURCE framework();
		QL_SOURCE ~framework();

		template <typename C>
		requires (std::is_base_of_v<ql::base_state, C>)
		void add_state()
		{
			this->states.push_back(std::make_unique<C>());
			this->states.back()->framework = this;

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

		QL_SOURCE void play_sound(const std::string& name, ql::f32 volume, ql::f32 speed);
		QL_SOURCE void add_font(const std::string& name, const std::string& path);
		QL_SOURCE void add_sound(const std::string& name, const std::string& path);
		QL_SOURCE void add_texture(const std::string& name, const std::string& path);
		QL_SOURCE void add_image(const std::string& name, const std::string& path);
		QL_SOURCE void add_sprite(const std::string& name, const std::string& path);
		QL_SOURCE void add_sprite(const std::string& name, sf::Texture& texture);
		QL_SOURCE void add_shader(const std::string& name, const std::string& path, sf::Shader::Type shader_type);
		QL_SOURCE void add_shader(const std::string& name, const std::string& path);
		QL_SOURCE void add_text(const std::string& name);

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
		QL_SOURCE ql::text& get_text(const std::string& name);

		QL_SOURCE const sf::Font& get_font(const std::string& name) const;
		QL_SOURCE const sf::SoundBuffer& get_sound(const std::string& name) const;
		QL_SOURCE const sf::Texture& get_texture(const std::string& name) const;
		QL_SOURCE const sf::Sprite& get_sprite(const std::string& name) const;
		QL_SOURCE const sf::Image& get_image(const std::string& name) const;
		QL_SOURCE const sf::Shader& get_shader(const std::string& name) const;
		QL_SOURCE const ql::text& get_text(const std::string& name) const;

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
		ql::event_info event;
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

	/* TO OVERLOAD:
		void init() override {

		}
		void updating() override {

		}
		void drawing() override {

		}
	*/
	struct base_state
	{
		virtual ~base_state() = default;

		virtual void init() = 0;
		virtual void updating() = 0;
		virtual void drawing() = 0;

		QL_SOURCE virtual void clear();
		QL_SOURCE virtual void call_on_resize();
		QL_SOURCE virtual void call_before_create();
		QL_SOURCE virtual void call_on_close();
		QL_SOURCE virtual void call_before_close();
		QL_SOURCE virtual void call_on_activate();

		QL_SOURCE void draw_call();
		QL_SOURCE void display();
		QL_SOURCE bool game_loop_segment();

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
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void final_draw(const T& drawable, sf::RenderStates states)
		{
			if constexpr (ql::has_view<T>())
			{
				drawable.auto_view.apply_to(states);
			}

			if constexpr (ql::is_render_texture<T>())
			{
#if defined QL_GLEW
				if (this->use_gl && !this->states_pushed)
				{
					this->push_gl_states();
					this->framework->window.draw(drawable.get_sprite(), states);
					this->pop_gl_states();
					return;
				}
#endif
				this->framework->window.draw(drawable.get_sprite(), states);
			}
			else if constexpr (std::is_base_of<sf::Drawable, T>())
			{
#if defined QL_GLEW
				if (this->use_gl && !this->states_pushed)
				{
					this->push_gl_states();
					this->framework->window.draw(drawable, states);
					this->pop_gl_states();
					return;
				}
#endif
				this->framework->window.draw(drawable, states);
			}
			else if constexpr (ql::has_draw_object<T>())
			{
				ql::draw_object draw(this->framework->window, states);
#if defined QL_GLEW
				if (this->use_gl && !this->states_pushed)
				{
					this->push_gl_states();
					drawable.draw(draw);
					this->pop_gl_states();
					return;
				}
#endif
				drawable.draw(draw);
			}
			else if constexpr (ql::has_draw_object_gl<T>())
			{
				ql::draw_object_gl draw(this->framework->window, states);
				drawable.draw(draw);
			}
			else if constexpr (ql::has_draw_sf<T>())
			{
#if defined QL_GLEW
				if (this->use_gl && !this->states_pushed)
				{
					this->push_gl_states();
					drawable.draw(this->framework->window, states);
					this->pop_gl_states();
					return;
				}
#endif
				drawable.draw(this->framework->window, states);
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw(const T& drawable, sf::RenderStates states)
		{
			if constexpr (ql::has_any_draw<T>())
			{
				if constexpr (ql::is_render_texture<T>())
				{
					this->final_draw(drawable.get_sprite(), states);
				}
				else
				{
					this->final_draw(drawable, states);
				}
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw(i);
				}
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw(const T& drawable)
		{
			if constexpr (ql::has_any_draw<T>())
			{
				if constexpr (ql::is_render_texture<T>())
				{
					this->final_draw(drawable.get_sprite(), this->render_states);
				}
				else
				{
					this->final_draw(drawable, this->render_states);
				}
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw(i);
				}
			}
		}

		template <typename T, typename V>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw(const T& drawable, ql::view_t<V> view)
		{
			this->draw(drawable, view.get_render_states());
		}

		template <typename T, typename V>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw(const T& drawable, ql::view_control_t<V> view)
		{
			if (!view.enabled)
			{
				this->draw(drawable);
				return;
			}
			if constexpr (ql::has_any_draw<T>())
			{
				sf::RenderStates states = view.get_render_states();
				this->draw(drawable, states);
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw(i, view);
				}
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw(const T& drawable, const ql::camera& camera)
		{
			if constexpr (ql::has_any_draw<T>())
			{
				sf::RenderStates states = camera.get_render_states();
				this->draw(drawable, states);
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw(i, camera);
				}
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw_into(const std::string& name, const T& drawable)
		{
			if constexpr (ql::has_any_draw<T>())
			{
				this->get_render(name).draw(drawable, this->render_states);
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw(name, i);
				}
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw_into(const std::string& name, const T& drawable, sf::RenderStates states)
		{
			if constexpr (ql::has_any_draw<T>())
			{
				this->get_render(name).draw(drawable, states);
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw_into(name, i, states);
				}
			}
		}

		template <typename T, typename V>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw_into(const std::string& name, const T& drawable, ql::view_control_t<V> view)
		{
			if (!view.enabled)
			{
				this->draw_into(name, drawable);
				return;
			}
			if constexpr (ql::has_any_draw<T>())
			{
				sf::RenderStates states = view.get_render_states();
				this->get_render(name).draw(drawable, states);
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw_into(name, i, view);
				}
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw_with_shader(const T& drawable, const std::string& name)
		{
			if constexpr (ql::has_any_draw<T>())
			{
				sf::RenderStates states = this->render_states;
				states.shader = &ql::get_shader(name);
				this->draw(drawable, states);
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw_with_shader(i, name);
				}
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw_with_shader(const T& drawable, sf::Shader& shader)
		{
			if constexpr (ql::has_any_draw<T>())
			{
				sf::RenderStates states = this->render_states;
				states.shader = &shader;
				this->draw(drawable, states);
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw_with_shader(i, shader);
				}
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw_with_shader_into(const std::string& render_name, const T& drawable, const std::string& shader_name)
		{
			if constexpr (ql::has_any_draw<T>())
			{
				sf::RenderStates states = this->render_states;
				states.shader = &ql::get_shader(shader_name);
				this->get_render(render_name).draw(drawable, states);
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw_with_shader_into(drawable, i, shader_name);
				}
			}
		}

		template <typename T>
		requires (ql::has_any_draw<T>() || (ql::is_container<T>() && ql::has_any_draw<ql::container_deepest_subtype<T>>()))
		void draw_with_shader_into(const std::string& render_name, const T& drawable, sf::Shader& shader)
		{
			if constexpr (ql::has_any_draw<T>())
			{
				sf::RenderStates states = this->render_states;
				states.shader = &shader;
				this->get_render(render_name).draw(drawable, states);
			}
			else
			{
				for (auto& i : drawable)
				{
					this->draw_with_shader_into(drawable, i, shader);
				}
			}
		}

		template <typename T, typename... Args>
		requires (
				ql::has_update<T, Args...>() || (ql::is_container<T>() && ql::has_update<ql::container_deepest_subtype<T>, Args...>())
		)
		void final_update(T& updatable, Args&&... args)
		{
			if constexpr (ql::has_view<T>())
			{
				if (updatable.auto_view.is_default_view())
				{
					updatable.update(this->event(), args...);
				}
				else
				{
					auto before = this->event().m_mouse_position;
					auto before_delta = this->event().m_delta_mouse_position;
					this->event().apply_view(updatable.auto_view);

					updatable.update(this->event(), args...);

					this->event().m_mouse_position = before;
					this->event().m_delta_mouse_position = before_delta;
				}
			}
			else
			{
				updatable.update(this->event(), args...);
			}
		}

		template <typename T, typename... Args>
		requires (
				ql::has_update<T, Args...>() || (ql::is_container<T>() && ql::has_update<ql::container_deepest_subtype<T>, Args...>())
		)
		void update(T& updatable, Args&&... args)
		{
			if constexpr (ql::has_update<T, Args...>())
			{
				this->final_update(updatable, args...);
			}
			else
			{
				for (auto& i : updatable)
				{
					this->update(i, args...);
				}
			}
		}

		template <typename T, typename V, typename... Args>
		requires (
				ql::has_update<T, Args...>() || (ql::is_container<T>() && ql::has_update<ql::container_deepest_subtype<T>, Args...>())
		)
		void update(T& updatable, const ql::view_t<V>& view, Args&&... args)
		{
			auto before = this->event().m_mouse_position;
			auto before_delta = this->event().m_delta_mouse_position;

			this->event().apply_view(view);

			if constexpr (ql::has_update<T, Args...>())
			{
				this->final_update(updatable, args...);
			}
			else
			{
				for (auto& i : updatable)
				{
					this->update(i, args...);
				}
			}
			this->event().m_mouse_position = before;
			this->event().m_delta_mouse_position = before_delta;
		}

		template <typename T, typename V, typename... Args>
		requires (
				ql::has_update<T, Args...>() || (ql::is_container<T>() && ql::has_update<ql::container_deepest_subtype<T>, Args...>())
		)
		void update(T& updatable, const ql::view_control_t<V>& view, Args&&... args)
		{
			if (!view.enabled)
			{
				this->update(updatable, args...);
				return;
			}

			auto before = this->event().m_mouse_position;
			auto before_delta = this->event().m_delta_mouse_position;

			this->event().m_mouse_position = view.transform_point(this->event().m_mouse_position);
			this->event().m_delta_mouse_position = view.transform_point_no_offset(this->event().m_delta_mouse_position);

			if constexpr (ql::has_update<T, Args...>())
			{
				this->final_update(updatable, args...);
			}
			else
			{
				for (auto& i : updatable)
				{
					this->update(i, args...);
				}
			}
			this->event().m_mouse_position = before;
			this->event().m_delta_mouse_position = before_delta;
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
		QL_SOURCE void add_text(const std::string& name);

		QL_SOURCE void add_font_from_memory(const std::string& name, const std::string& memory);
		QL_SOURCE void add_sound_from_memory(const std::string& name, const std::string& memory);
		QL_SOURCE void add_texture_from_memory(const std::string& name, const std::string& memory);
		QL_SOURCE void add_shader_from_memory(const std::string& name, const std::string& memory, sf::Shader::Type shader_type);

		QL_SOURCE sf::Font& get_font(const std::string& name);
		QL_SOURCE sf::SoundBuffer& get_sound(const std::string& name);
		QL_SOURCE sf::Texture& get_texture(const std::string& name);
		QL_SOURCE sf::Sprite& get_sprite(const std::string& name);
		QL_SOURCE sf::Shader& get_shader(const std::string& name);
		QL_SOURCE ql::text& get_text(const std::string& name);

		QL_SOURCE const sf::Font& get_font(const std::string& name) const;
		QL_SOURCE const sf::SoundBuffer& get_sound(const std::string& name) const;
		QL_SOURCE const sf::Texture& get_texture(const std::string& name) const;
		QL_SOURCE const sf::Sprite& get_sprite(const std::string& name) const;
		QL_SOURCE const sf::Shader& get_shader(const std::string& name) const;
		QL_SOURCE const ql::text& get_text(const std::string& name) const;

		QL_SOURCE void add_render(const std::string& name, bool smooth = true);
		QL_SOURCE ql::render_texture& get_render(const std::string& name);
		QL_SOURCE const ql::render_texture& get_render(const std::string& name) const;

		template <typename C>
		requires (std::is_base_of_v<ql::base_state, C>)
		void add_state()
		{
			this->framework->add_state<C>();
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
		QL_SOURCE const ql::event_info& event() const;
		QL_SOURCE ql::event_info& event();

		ql::framework* framework = nullptr;

		friend ql::framework;

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