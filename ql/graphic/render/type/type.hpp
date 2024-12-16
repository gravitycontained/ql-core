#pragma once

#include <ql/core/definition/definition.hpp>

#if defined QL_GRAPHIC

#include <ql/core/type/type.hpp>
#include <SFML/Graphics.hpp>

namespace ql
{
	template <bool opengl>
	struct render_type
	{
		render_type(sf::RenderWindow& window, sf::RenderStates states = sf::RenderStates::Default)
		{
			this->window = &window;
			this->texture = nullptr;
			this->states = states;
		}

		render_type(sf::RenderTexture& texture, sf::RenderStates states = sf::RenderStates::Default)
		{
			this->texture = &texture;
			this->window = nullptr;
			this->states = states;
		}

		template <typename T>
		requires (ql::has_draw<ql::modal_decay<T>>())
		void draw(const T& object)
		{
			ql::modal_apply(object,
				[this](const auto& value)
				{
					using U = decltype(value);
					if constexpr (ql::has_draw<U>())
					{
						if constexpr (ql::is_view<T>())
						{
							auto before = this->states;

							value.draw(*this);

							this->states = before;
						}
						else if constexpr (ql::is_render_texture<U>())
						{
							if (this->window)
							{
								this->window->draw(value.get_sprite(), this->states);
							}
							else if (this->texture)
							{
								this->texture->draw(value.get_sprite(), this->states);
							}
						}
						else if constexpr (std::is_base_of<sf::Drawable, U>())
						{
							if (this->window)
							{
								this->window->draw(value, this->states);
							}
							else if (this->texture)
							{
								this->texture->draw(value, this->states);
							}
						}
						else if constexpr (ql::has_render<U>())
						{
							value.draw(*this);
						}
						else if constexpr (ql::has_render_gl<U>())
						{
							value.draw(*this);
						}
						else if constexpr (ql::has_draw_sf_reverse<U>())
						{
							if (this->window)
							{
								this->window->draw(value, this->states);
							}
							else if (this->texture)
							{
								this->texture->draw(value, this->states);
							}
						}
						else if constexpr (ql::has_draw_sf<U>())
						{
							if (this->window)
							{
								value.draw(*this->window, this->states);
							}
							else if (this->texture)
							{
								value.draw(*this->texture, this->states);
							}
						}
					}
				}
			);
		}

		template <typename T, typename U>
		requires (ql::has_draw<T>() || ql::is_container<T>())
		void draw(const T& object, const ql::view_type<U>& view)
		{
			auto copy = this->states;
			view.apply_to(this->states);
			this->draw(object);
			this->states = copy;
		}

		template <typename T>
		requires (ql::has_draw<T>() || ql::is_container<T>())
		void draw(const T& object, sf::RenderStates states)
		{
			if constexpr (ql::has_view<T>())
			{
				object.auto_view.apply_to(states);
			}
			if constexpr (ql::has_draw<T>())
			{
				if constexpr (ql::is_render_texture<T>())
				{
					if (this->window)
					{
						this->window->draw(object.get_sprite(), states);
					}
					else if (this->texture)
					{
						this->texture->draw(object.get_sprite(), states);
					}
				}
				else if constexpr (std::is_base_of<sf::Drawable, T>())
				{
					if (this->window)
					{
						this->window->draw(object, states);
					}
					else if (this->texture)
					{
						this->texture->draw(object, states);
					}
				}
				else if constexpr (ql::has_render<T>())
				{
					auto copy = this->states;
					this->states = states;
					object.draw(*this);
					this->states = copy;
				}
				else if constexpr (ql::has_draw_sf<T>())
				{
					if (this->window)
					{
						object.draw(*this->window, states);
					}
					else if (this->texture)
					{
						object.draw(*this->texture, states);
					}
				}
			}
			else
			{
				for (auto& i : object)
				{
					this->draw(i, states);
				}
			}
		}

		sf::RenderWindow* window;
		sf::RenderTexture* texture;
		sf::RenderStates states;
	};

	using render = render_type<false>;
	using render_gl = render_type<true>;
}	 // namespace ql

#endif