#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/advanced-type/color/color.hpp>

#include <ql/core/string/cast/cast.hpp>

#include <ql/core/container/container.hpp>

namespace ql
{

	namespace style
	{
		struct color
		{
			ql::rgba value;

			constexpr color(ql::rgb color) : value(color)
			{
			}

			constexpr color(ql::print_color color)
			{
				this->value = ql::print_color_to_rgba(color);
			}
		};

		struct style
		{
			ql::u32 value;

			constexpr style(ql::u32 style) : value(style)
			{
			}
		};

		struct outline_thickness
		{
			ql::f32 value;

			constexpr outline_thickness(ql::f32 thickness) : value(thickness)
			{
			}
		};

		struct background_color
		{
			ql::rgba value;

			constexpr background_color(ql::rgb color) : value(color)
			{
			}
		};

		struct outline_color
		{
			ql::rgba value;

			constexpr outline_color(ql::rgb color) : value(color)
			{
			}
		};

		struct keep
		{
		};

		struct pop
		{
		};
	}	 // namespace style

	template <typename T>
	struct styled_string
	{
		struct element
		{
			T text{};
			ql::rgba color = ql::rgba(204, 204, 204);
			ql::rgba background_color = ql::rgba::transparent;
			ql::rgba outline_color = ql::rgba::black();
			ql::f32 outline_thickness = 0.0f;
			ql::u32 style = 0u;
			bool keep = false;

			bool operator==(const element& other) const
			{
				return this->color == other.color && this->background_color == other.background_color && this->style == other.style &&
							 this->outline_thickness == other.outline_thickness &&
							 ((this->outline_thickness == 0.0f && other.outline_thickness == 0.0f) ||
								(this->outline_color == other.outline_color));
			}

			bool is_default() const
			{
				return *this == element{};
			}

			void copy_style(const element& other)
			{
				this->color = other.color;
				this->background_color = other.background_color;
				this->outline_color = other.outline_color;
				this->outline_thickness = other.outline_thickness;
				this->style = other.style;
			}
		};

		std::vector<element> elements;
		bool always_keep_styles = true;

		styled_string()
		{
			this->clear();
		}

		void clear_copy_style(const styled_string<T>& other)
		{
			this->elements.resize(1u);
			this->elements[0u].copy_style(other.elements.back());
		}

		void clear_copy_style_self()
		{
			auto copy = this->elements.back();
			this->elements.resize(1u);
			this->elements[0u].text.clear();
			this->elements[0u].copy_style(copy);
		}

		void clear_copy_style(const styled_string<T>::element& other)
		{
			this->elements.resize(1u);
			this->elements[0u].text.clear();
			this->elements[0u].copy_style(other);
		}

		void clear()
		{
			this->elements.clear();
			this->always_keep_styles = true;
			this->elements.push_back({});
		}

		ql::size size() const
		{
			return this->elements.size();
		}

		constexpr auto& operator[](ql::size index)
		{
			return this->elements[index];
		}

		constexpr const auto& operator[](ql::size index) const
		{
			return this->elements[index];
		}

		constexpr auto& at(ql::size index)
		{
			return this->elements.at(index);
		}

		constexpr const auto& at(ql::size index) const
		{
			return this->elements.at(index);
		}

		constexpr void resize(ql::size size)
		{
			this->elements.resize(size);
		}

		constexpr void reserve(ql::size size)
		{
			this->elements.reserve(size);
		}

		constexpr auto begin()
		{
			return this->elements.begin();
		}

		constexpr const auto begin() const
		{
			return this->elements.begin();
		}

		constexpr const auto cbegin() const
		{
			return this->elements.cbegin();
		}

		constexpr auto end()
		{
			return this->elements.end();
		}

		constexpr const auto end() const
		{
			return this->elements.end();
		}

		constexpr const auto cend() const
		{
			return this->elements.cend();
		}

		constexpr auto rbegin()
		{
			return this->elements.rbegin();
		}

		constexpr const auto rbegin() const
		{
			return this->elements.rbegin();
		}

		constexpr const auto rcbegin() const
		{
			return this->elements.crbegin();
		}

		constexpr auto rend()
		{
			return this->elements.rend();
		}

		constexpr const auto rend() const
		{
			return this->elements.rend();
		}

		constexpr const auto rcend() const
		{
			return this->elements.crend();
		}

		void prepare_next_style()
		{
			this->elements.push_back({});
			if (this->elements.back().keep || this->always_keep_styles)
			{
				this->elements.back().copy_style(this->elements[this->elements.size() - 2]);
			}
		}

		void add(const style::keep& keep)
		{
			this->elements.back().keep = true;
		}

		void add(const style::pop& push)
		{
			this->elements.pop_back();
			if (this->elements.empty())
			{
				this->elements.push_back({});
			}
		}

		void add(const ql::print_color& color)
		{
			this->add(style::color(color));
		}

		void add(const ql::rgba& color)
		{
			this->add(style::color(color));
		}

		void add(const ql::rgb& color)
		{
			this->add(style::color(color));
		}

		void add(const ql::style::color& color)
		{
			if (this->elements.back().color == color.value)
			{
				return;
			}
			this->prepare_next_style();
			this->elements.back().color = color.value;
		}

		void add(const ql::style::background_color& background_color)
		{
			if (this->elements.back().background_color == background_color.value)
			{
				return;
			}
			if (this->elements.back().background_color.a == 0 && background_color.value.a == 0)
			{
				return;
			}
			this->prepare_next_style();
			this->elements.back().background_color = background_color.value;
		}

		void add(const ql::style::outline_color& outline_color)
		{
			if (this->elements.back().outline_color == outline_color.value)
			{
				return;
			}
			this->prepare_next_style();
			this->elements.back().outline_color = outline_color.value;
		}

		void add(const ql::style::outline_thickness& thickness)
		{
			if (this->elements.back().outline_thickness == thickness.value)
			{
				return;
			}
			this->prepare_next_style();
			this->elements.back().outline_thickness = thickness.value;
		}

		void add(const ql::style::style& style)
		{
			if (this->elements.back().style == style.value)
			{
				return;
			}
			this->prepare_next_style();
			this->elements.back().style = style.value;
		}

		void add(const element& element)
		{
			if (this->elements.back() == element)
			{
				this->elements.back().text += element.text;
			}
			else
			{
				this->elements.push_back(element);
			}
		}

		template <typename S>
		requires (ql::is_string_type<S>())
		void add(const S& string)
		{
			if (!this->always_keep_styles && !this->elements.back().is_default())
			{
				this->elements.push_back({});
			}
			this->elements.back().text += ql::to_basic_string<typename T::value_type>(string);
		}

		//template <typename T>
		//void add(const T& other)
		//{
		//	static_assert(ql::is_string_type<T>(), "T must be a string type");
		//}

		void remove_character_at(ql::vec2s pos)
		{
			ql::size y = 0u;

			for (ql::size i = 0u; i < this->elements.size(); ++i)
			{
				auto& element = this->elements[i];
				if (element.text.empty() && i != this->elements.size() - 1)
				{
					continue;
				}
				auto element_string = ql::to_basic_string<wchar_t>(element.text);
				auto new_lines = ql::count(element_string, L'\n');
				auto new_y = y + new_lines;

				if (pos.y >= y && pos.y <= new_y)
				{
					auto off = pos.y - y;

					ql::size size = 0u;
					auto split = ql::string_split_allow_empty(element_string, L'\n');
					for (ql::size i = 0u; i < off; ++i)
					{
						size += split[i].length() + 1;
					}
					size += pos.x;

					if (!size)
					{
						return;
					}
					auto result = element.text.substr(0u, size - 1);
					if (element.text.length() > size)
					{
						result += element.text.substr(size);
					}
					element.text = result;
					return;
				}

				y = new_y;
			}
		}

		void clear_last_line()
		{
			auto& text = this->elements.back().text;
			auto ctr = ql::signed_cast(text.length()) - 1;
			while (ctr >= 0 && text[ctr] != U'\n')
			{
				--ctr;
			}
			text.resize(ctr + 1);
		}

		void add_text_at(ql::vec2s pos, const T& string)
		{
			ql::size y = 0u;
			for (ql::size i = 0u; i < this->elements.size(); ++i)
			{
				auto& element = this->elements[i];
				if (element.text.empty() && i != this->elements.size() - 1)
				{
					continue;
				}
				auto element_string = ql::to_basic_string<wchar_t>(element.text);
				auto new_lines = ql::count(element_string, L'\n');
				auto new_y = y + new_lines;

				if (pos.y >= y && pos.y <= new_y)
				{
					auto off = pos.y - y;

					ql::size size = 0u;
					auto split = ql::string_split_allow_empty(element_string, L'\n');
					for (ql::size i = 0u; i < off; ++i)
					{
						size += split[i].length() + 1;
					}
					size += pos.x;

					auto result = element.text.substr(0u, size) + string;
					if (size && element.text.length() >= size)
					{
						result += element.text.substr(size);
					}
					element.text = result;
					return;
				}

				y = new_y;
			}
		}

		void add(const styled_string& styled_string)
		{
			for (auto& i : styled_string)
			{
				this->add(i);
			}
		}

		template <typename T>
		styled_string& operator<<(T value)
		{
			this->add(value);
			return *this;
		}

		bool empty() const
		{
			return this->elements.empty();
		}

		auto string() const
		{
			T result{};
			for (auto& i : this->elements)
			{
				result += i.text;
			}
			return result;
		}
	};

	template <typename T, typename... Args>
	ql::styled_string<T> to_styled_string(Args... args)
	{
		ql::styled_string<T> result;
		((result << args), ...);
		return result;
	}

	template <typename T, typename... Args>
	ql::styled_string<T> to_styled_stringln(Args... args)
	{
		return ql::to_styled_string(args..., '\n');
	}

}	 // namespace ql