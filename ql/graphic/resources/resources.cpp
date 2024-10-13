#include <ql/graphic/resources.hpp>
#include <ql/core/system/exception/exception.hpp>

#if defined QL_GRAPHIC

namespace ql
{

	void ql::load_font(sf::Font& font, const std::string& path)
	{
		if (!font.loadFromFile(path))
		{
			throw ql::exception("load font: couldn't find / load \"", path, "\"");
		}
	}

	void ql::load_texture(sf::Texture& texture, const std::string& path, bool set_smooth)
	{
		if (!texture.loadFromFile(path))
		{
			throw ql::exception("load texture: couldn't find / load \"", path, "\"");
		}
		texture.setSmooth(set_smooth);
	}

	void ql::load_image(sf::Image& image, const std::string& path)
	{
		if (!image.loadFromFile(path))
		{
			throw ql::exception("load image: couldn't find / load \"", path, "\"");
		}
	}

	void ql::load_sound(sf::SoundBuffer& sound, const std::string& path)
	{
		if (!sound.loadFromFile(path))
		{
			throw ql::exception("load sound: couldn't find / load \"", path, "\"");
		}
	}

	void ql::load_shader(sf::Shader& shader, const std::string& path, sf::Shader::Type shader_type)
	{
		if (!shader.loadFromFile(path, shader_type))
		{
			throw ql::exception("load shader: couldn't find / load \"", path, "\"");
		}
	}

	void ql::load_shader(sf::Shader& shader, const std::string& path)
	{
		auto split = ql::string_split(path, '.');
		if (split.size())
		{
			auto back = split.back();
			if (ql::string_equals_ignore_case(back, "frag"))
			{
				ql::load_shader(shader, path, sf::Shader::Type::Fragment);
			}
			else if (ql::string_equals_ignore_case(back, "fragment"))
			{
				ql::load_shader(shader, path, sf::Shader::Type::Fragment);
			}
			else if (ql::string_equals_ignore_case(back, "vert"))
			{
				ql::load_shader(shader, path, sf::Shader::Type::Vertex);
			}
			else if (ql::string_equals_ignore_case(back, "vertex"))
			{
				ql::load_shader(shader, path, sf::Shader::Type::Vertex);
			}
			else if (ql::string_equals_ignore_case(back, "geom"))
			{
				ql::load_shader(shader, path, sf::Shader::Type::Geometry);
			}
			else if (ql::string_equals_ignore_case(back, "geometry"))
			{
				ql::load_shader(shader, path, sf::Shader::Type::Geometry);
			}
			else
			{
				throw ql::exception("load shader: can't identify what the shader type for \".", back, "\" is");
			}
		}
	}

	void ql::load_font_from_memory(sf::Font& font, const std::string& memory)
	{
		if (!font.loadFromMemory(memory.data(), memory.size()))
		{
			throw ql::exception("load font: couldn't load from memory");
		}
	}

	void ql::load_texture_from_memory(sf::Texture& texture, const std::string& memory, bool set_smooth)
	{
		if (!texture.loadFromMemory(memory.data(), memory.size()))
		{
			throw ql::exception("load texture: couldn't load from memory");
		}
		texture.setSmooth(set_smooth);
	}

	void ql::load_sound_from_memory(sf::SoundBuffer& sound, const std::string& memory)
	{
		if (!sound.loadFromMemory(memory.data(), memory.size()))
		{
			throw ql::exception("load sound: couldn't load from memory");
		}
	}

	void ql::load_shader_from_memory(sf::Shader& shader, const std::string& memory, sf::Shader::Type shader_type)
	{
		if (!shader.loadFromMemory(memory, shader_type))
		{
			throw ql::exception("load shader: couldn't load from memory");
		}
	}

	void ql::resources::play_sound(const std::string& name, ql::f32 volume, ql::f32 speed)
	{
		if (!this->find_sound(name))
		{
			throw ql::exception(ql::to_string("play_sound: couldn't find \"", name, "\"").c_str());
		}
		this->active_sounds.push_back(sf::Sound{});
		this->active_sounds.back().setBuffer(this->sounds[name]);
		this->active_sounds.back().setVolume(volume);
		this->active_sounds.back().setPitch(speed);
		this->active_sounds.back().play();
	}

	void ql::resources::update_sounds()
	{
		std::vector<std::list<sf::Sound>::iterator> remove;

		for (auto it = this->active_sounds.begin(); it != this->active_sounds.end(); ++it)
		{
			if (it->getStatus() == sf::SoundSource::Status::Stopped)
			{
				remove.push_back(it);
			}
		}
		for (auto& i : remove)
		{
			this->active_sounds.erase(i);
		}
	}

	void ql::resources::add_font(const std::string& name, const std::string& path)
	{
		ql::load_font(this->fonts[name], path);
	}

	void ql::resources::add_sound(const std::string& name, const std::string& path)
	{
		ql::load_sound(this->sounds[name], path);
	}

	void ql::resources::add_texture(const std::string& name, const std::string& path)
	{
		ql::load_texture(this->textures[name], path);
	}

	void ql::resources::add_image(const std::string& name, const std::string& path)
	{
		ql::load_image(this->images[name], path);
	}

	void ql::resources::add_shader(const std::string& name, const std::string& path, sf::Shader::Type shader_type)
	{
		ql::load_shader(this->shaders[name], path, shader_type);
	}

	void ql::resources::add_shader(const std::string& name, const std::string& path)
	{
		ql::load_shader(this->shaders[name], path);
	}

	void ql::resources::add_sprite(const std::string& name, const std::string& path)
	{
		if (this->textures.find(name) == this->textures.cend())
		{
			this->add_texture(name, path);
		}
		ql::load_texture(this->textures[name], path);
	}

	void ql::resources::add_sprite(const std::string& name, sf::Texture& texture)
	{
		this->sprites[name].setTexture(texture);
	}

	void ql::resources::add_font_from_memory(const std::string& name, const std::string& memory)
	{
		ql::load_font_from_memory(this->fonts[name], memory);
	}

	void ql::resources::add_sound_from_memory(const std::string& name, const std::string& memory)
	{
		ql::load_sound_from_memory(this->sounds[name], memory);
	}

	void ql::resources::add_texture_from_memory(const std::string& name, const std::string& memory)
	{
		ql::load_texture_from_memory(this->textures[name], memory);
	}

	void ql::resources::add_shader_from_memory(const std::string& name, const std::string& memory, sf::Shader::Type shader_type)
	{
		ql::load_shader_from_memory(this->shaders[name], memory, shader_type);
	}

	bool ql::resources::find_font(const std::string& name) const
	{
		return this->fonts.find(name) != this->fonts.cend();
	}

	bool ql::resources::find_sound(const std::string& name) const
	{
		return this->sounds.find(name) != this->sounds.cend();
	}

	bool ql::resources::find_texture(const std::string& name) const
	{
		return this->textures.find(name) != this->textures.cend();
	}

	bool ql::resources::find_image(const std::string& name) const
	{
		return this->images.find(name) != this->images.cend();
	}

	bool ql::resources::find_sprite(const std::string& name) const
	{
		return this->sprites.find(name) != this->sprites.cend();
	}

	bool ql::resources::find_shader(const std::string& name) const
	{
		return this->shaders.find(name) != this->shaders.cend();
	}

	sf::Font& ql::resources::get_font(const std::string& name)
	{
		if (this->fonts.find(name) == this->fonts.cend())
		{
			throw ql::exception("couldn't find font with name \"", name, "\"");
		}
		return this->fonts[name];
	}

	sf::SoundBuffer& ql::resources::get_sound(const std::string& name)
	{
		if (this->sounds.find(name) == this->sounds.cend())
		{
			throw ql::exception("couldn't find sound with name \"", name, "\"");
		}
		return this->sounds[name];
	}

	sf::Texture& ql::resources::get_texture(const std::string& name)
	{
		if (this->textures.find(name) == this->textures.cend())
		{
			throw ql::exception("couldn't find texture with name \"", name, "\"");
		}
		return this->textures[name];
	}

	sf::Image& ql::resources::get_image(const std::string& name)
	{
		if (this->images.find(name) == this->images.cend())
		{
			throw ql::exception("couldn't find image with name \"", name, "\"");
		}
		return this->images[name];
	}

	sf::Sprite& ql::resources::get_sprite(const std::string& name)
	{
		if (this->sprites.find(name) == this->sprites.cend())
		{
			throw ql::exception("couldn't find sprite with name \"", name, "\"");
		}
		return this->sprites[name];
	}

	sf::Shader& ql::resources::get_shader(const std::string& name)
	{
		if (this->shaders.find(name) == this->shaders.cend())
		{
			throw ql::exception("couldn't find shader with name \"", name, "\"");
		}
		return this->shaders[name];
	}

	const sf::Font& ql::resources::get_font(const std::string& name) const
	{
		if (this->fonts.find(name) == this->fonts.cend())
		{
			throw ql::exception("couldn't find font with name \"", name, "\"");
		}
		return this->fonts.at(name);
	}

	const sf::SoundBuffer& ql::resources::get_sound(const std::string& name) const
	{
		if (this->sounds.find(name) == this->sounds.cend())
		{
			throw ql::exception("couldn't find sound with name \"", name, "\"");
		}
		return this->sounds.at(name);
	}

	const sf::Texture& ql::resources::get_texture(const std::string& name) const
	{
		if (this->textures.find(name) == this->textures.cend())
		{
			throw ql::exception("couldn't find texture with name \"", name, "\"");
		}
		return this->textures.at(name);
	}

	const sf::Image& ql::resources::get_image(const std::string& name) const
	{
		if (this->images.find(name) == this->images.cend())
		{
			throw ql::exception("couldn't find image with name \"", name, "\"");
		}
		return this->images.at(name);
	}

	const sf::Sprite& ql::resources::get_sprite(const std::string& name) const
	{
		if (this->sprites.find(name) == this->sprites.cend())
		{
			throw ql::exception("couldn't find sprite with name \"", name, "\"");
		}
		return this->sprites.at(name);
	}

	const sf::Shader& ql::resources::get_shader(const std::string& name) const
	{
		if (this->shaders.find(name) == this->shaders.cend())
		{
			throw ql::exception("couldn't find shader with name \"", name, "\"");
		}
		return this->shaders.at(name);
	}

	ql::resources ql::detail::resources;

	void ql::play_sound(const std::string& name, ql::f32 volume, ql::f32 speed)
	{
		ql::detail::resources.play_sound(name, volume, speed);
	}

	void ql::update_sounds()
	{
		ql::detail::resources.update_sounds();
	}

	void ql::add_font(const std::string& name, const std::string& path)
	{
		ql::detail::resources.add_font(name, path);
	}

	void ql::add_sound(const std::string& name, const std::string& path)
	{
		ql::detail::resources.add_sound(name, path);
	}

	void ql::add_texture(const std::string& name, const std::string& path)
	{
		ql::detail::resources.add_texture(name, path);
	}

	void ql::add_sprite(const std::string& name, const std::string& path)
	{
		ql::detail::resources.add_sprite(name, path);
	}

	void ql::add_sprite(const std::string& name, sf::Texture& texture)
	{
		ql::detail::resources.add_sprite(name, texture);
	}

	void ql::add_image(const std::string& name, const std::string& path)
	{
		ql::detail::resources.add_image(name, path);
	}

	void ql::add_shader(const std::string& name, const std::string& path, sf::Shader::Type shader_type)
	{
		ql::detail::resources.add_shader(name, path, shader_type);
	}

	void ql::add_shader(const std::string& name, const std::string& path)
	{
		ql::detail::resources.add_shader(name, path);
	}

	void ql::add_font_from_memory(const std::string& name, const std::string& memory)
	{
		ql::detail::resources.add_font_from_memory(name, memory);
	}

	void ql::add_sound_from_memory(const std::string& name, const std::string& memory)
	{
		ql::detail::resources.add_sound_from_memory(name, memory);
	}

	void ql::add_texture_from_memory(const std::string& name, const std::string& memory)
	{
		ql::detail::resources.add_texture_from_memory(name, memory);
	}

	void ql::add_shader_from_memory(const std::string& name, const std::string& memory, sf::Shader::Type shader_type)
	{
		ql::detail::resources.add_shader_from_memory(name, memory, shader_type);
	}

	sf::Font& ql::get_font(const std::string& name)
	{
		return ql::detail::resources.get_font(name);
	}

	sf::SoundBuffer& ql::get_sound(const std::string& name)
	{
		return ql::detail::resources.get_sound(name);
	}

	sf::Texture& ql::get_texture(const std::string& name)
	{
		return ql::detail::resources.get_texture(name);
	}

	sf::Image& ql::get_image(const std::string& name)
	{
		return ql::detail::resources.get_image(name);
	}

	sf::Sprite& ql::get_sprite(const std::string& name)
	{
		return ql::detail::resources.get_sprite(name);
	}

	sf::Shader& ql::get_shader(const std::string& name)
	{
		return ql::detail::resources.get_shader(name);
	}

	bool ql::find_font(const std::string& name)
	{
		return ql::detail::resources.find_font(name);
	}

	bool ql::find_sound(const std::string& name)
	{
		return ql::detail::resources.find_sound(name);
	}

	bool ql::find_texture(const std::string& name)
	{
		return ql::detail::resources.find_texture(name);
	}

	bool ql::find_image(const std::string& name)
	{
		return ql::detail::resources.find_texture(name);
	}

	bool ql::find_sprite(const std::string& name)
	{
		return ql::detail::resources.find_sprite(name);
	}

	bool ql::find_shader(const std::string& name)
	{
		return ql::detail::resources.find_shader(name);
	}
}	 // namespace ql
#endif