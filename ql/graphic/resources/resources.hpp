#pragma once

#include <ql/core/definition/definition.hpp>

#if defined QL_GRAPHIC

#include <unordered_map>
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ql
{
	QL_SOURCE void load_font(sf::Font& Font, const std::string& path);
	QL_SOURCE void load_texture(sf::Texture& texture, const std::string& path, bool set_smooth = false);
	QL_SOURCE void load_image(sf::Image& image, const std::string& path);
	QL_SOURCE void load_sound(sf::SoundBuffer& sound, const std::string& path);
	QL_SOURCE void load_shader(sf::Shader& shader, const std::string& path, sf::Shader::Type shader_type);
	QL_SOURCE void load_shader(sf::Shader& shader, const std::string& path);

	QL_SOURCE void load_font_from_memory(sf::Font& Font, const std::string& memory);
	QL_SOURCE void load_texture_from_memory(sf::Texture& texture, const std::string& memory, bool set_smooth = false);
	QL_SOURCE void load_sound_from_memory(sf::SoundBuffer& sound, const std::string& memory);
	QL_SOURCE void load_shader_from_memory(sf::Shader& shader, const std::string& memory, sf::Shader::Type shader_type);

	struct resources
	{
		QL_SOURCE void play_sound(const std::string& name, ql::f32 volume = 100.0f, ql::f32 speed = 1.0f);
		QL_SOURCE void update_sounds();

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

		QL_SOURCE bool find_font(const std::string& name) const;
		QL_SOURCE bool find_sound(const std::string& name) const;
		QL_SOURCE bool find_texture(const std::string& name) const;
		QL_SOURCE bool find_sprite(const std::string& name) const;
		QL_SOURCE bool find_shader(const std::string& name) const;
		QL_SOURCE bool find_image(const std::string& name) const;

		QL_SOURCE sf::Font& get_font(const std::string& name);
		QL_SOURCE sf::SoundBuffer& get_sound(const std::string& name);
		QL_SOURCE sf::Texture& get_texture(const std::string& name);
		QL_SOURCE sf::Sprite& get_sprite(const std::string& name);
		QL_SOURCE sf::Shader& get_shader(const std::string& name);
		QL_SOURCE sf::Image& get_image(const std::string& name);

		QL_SOURCE const sf::Font& get_font(const std::string& name) const;
		QL_SOURCE const sf::SoundBuffer& get_sound(const std::string& name) const;
		QL_SOURCE const sf::Texture& get_texture(const std::string& name) const;
		QL_SOURCE const sf::Sprite& get_sprite(const std::string& name) const;
		QL_SOURCE const sf::Shader& get_shader(const std::string& name) const;
		QL_SOURCE const sf::Image& get_image(const std::string& name) const;

		std::unordered_map<std::string, sf::Font> fonts;
		std::unordered_map<std::string, sf::SoundBuffer> sounds;
		std::unordered_map<std::string, sf::Texture> textures;
		std::unordered_map<std::string, sf::Sprite> sprites;
		std::unordered_map<std::string, sf::Shader> shaders;
		std::unordered_map<std::string, sf::Image> images;
		std::list<sf::Sound> active_sounds;
	};

	namespace detail
	{
		QL_SOURCE extern ql::resources resources;
	}

	QL_SOURCE void play_sound(const std::string& name, ql::f32 volume = 100.0f, ql::f32 speed = 1.0f);
	QL_SOURCE void update_sounds();

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
	QL_SOURCE sf::Image& get_image(const std::string& name);
	QL_SOURCE sf::Sprite& get_sprite(const std::string& name);
	QL_SOURCE sf::Shader& get_shader(const std::string& name);

	QL_SOURCE bool find_font(const std::string& name);
	QL_SOURCE bool find_sound(const std::string& name);
	QL_SOURCE bool find_texture(const std::string& name);
	QL_SOURCE bool find_image(const std::string& name);
	QL_SOURCE bool find_sprite(const std::string& name);
	QL_SOURCE bool find_shader(const std::string& name);
};	// namespace ql

#endif