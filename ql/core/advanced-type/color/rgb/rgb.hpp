#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>
#include <ql/core/advanced-type/fundamental/fundamental.hpp>
#include <ql/core/transform/cast/cast.hpp>

#include <ql/core/transform/limit.hpp>

#include <ql/core/maths/arithmetic/arithmetic.hpp>

namespace ql
{

	namespace detail
	{

		template <typename T>
		struct r_impl
		{
			union
			{
				struct
				{
					T r;
				};

				std::array<T, 1> data;
			};

			constexpr r_impl() : data()
			{
				if constexpr (ql::is_floating_point<T>())
				{
					this->data.fill(T{1});
				}
				else
				{
					this->data.fill(ql::type_max<T>());
				}
			}
		};

		template <typename T>
		struct rg_impl
		{
			union
			{
				struct
				{
					T r;
					T g;
				};

				std::array<T, 2> data;
			};

			constexpr rg_impl() : data()
			{
				if constexpr (ql::is_floating_point<T>())
				{
					this->data.fill(T{1});
				}
				else
				{
					this->data.fill(ql::type_max<T>());
				}
			}
		};

		template <typename T>
		struct rgb_impl
		{
			union
			{
				struct
				{
					T r;
					T g;
					T b;
				};

				std::array<T, 3> data;
			};

			constexpr rgb_impl() : data()
			{
				if constexpr (ql::is_floating_point<T>())
				{
					this->data.fill(T{1});
				}
				else
				{
					this->data.fill(ql::type_max<T>());
				}
			}
		};

		template <typename T>
		struct rgba_impl
		{
			union
			{
				struct
				{
					T r;
					T g;
					T b;
					T a;
				};

				std::array<T, 4> data;
			};

			constexpr rgba_impl() : data()
			{
				if constexpr (ql::is_floating_point<T>())
				{
					this->data.fill(T{1});
				}
				else
				{
					this->data.fill(ql::type_max<T>());
				}
			}
		};

		template <typename T, ql::size N>
		using conditional_rgb = ql::conditional
		<
			ql::if_true<N == 1>, ql::detail::r_impl<T>,
			ql::if_true<N == 2>, ql::detail::rg_impl<T>,
			ql::if_true<N == 3>, ql::detail::rgb_impl<T>,
			ql::if_true<N == 4>, ql::detail::rgba_impl<T>
		>;
	}	 // namespace detail

	template <typename T, ql::size N>
	requires (N >= 1 && N <= 4 && ql::is_arithmetic<T>() && !(ql::is_integer<T>() && ql::is_signed<T>()))
	struct rgbN : ql::detail::conditional_rgb<T, N>
	{
		using impl_type = ql::detail::conditional_rgb<T, N>;

		using delta_type = ql::conditional<ql::if_true<is_floating_point<T>()>, T, ql::f64>;
		using visible_type = ql::conditional<ql::if_true<is_same<T, ql::u8>()>, ql::u32, ql::f64>;

		constexpr static bool has_green()
		{
			return N >= 2;
		}

		constexpr static bool has_blue()
		{
			return N >= 3;
		}

		constexpr static bool has_alpha()
		{
			return N >= 4;
		}

		constexpr static bool is_floating_point()
		{
			return ql::is_floating_point<T>();
		}

		constexpr static bool is_integer()
		{
			return ql::is_integer<T>();
		}

		constexpr static auto min_channel()
		{
			return T{0};
		}

		constexpr static auto max_channel()
		{
			if constexpr (is_floating_point())
			{
				return T{1};
			}
			else
			{
				return ql::type_max<T>();
			}
		}

		constexpr rgbN() : impl_type()
		{
		}

		template <typename U>
		constexpr rgbN(const std::initializer_list<U>& list) : impl_type()
		{
			*this = list;
		}

		template <typename Tuple>
		requires (ql::is_tuple<Tuple>())
		constexpr rgbN(const Tuple& tuple) : impl_type()
		{
			*this = tuple;
		}

		template <typename... Args>
		requires (sizeof...(Args) > 1 && sizeof...(Args) <= N)
		constexpr rgbN(Args&&... list) : impl_type()
		{
			*this = std::make_tuple(list...);
		}

		constexpr rgbN(const ql::rgbN<T, N>& other) : impl_type()
		{
			*this = other;
		}

		template <typename U, ql::size M>
		constexpr rgbN(const ql::rgbN<U, M>& other) : impl_type()
		{
			*this = other;
		}

		template <typename U, ql::size M>
		constexpr rgbN(const ql::vectorN<U, M>& other) : impl_type()
		{
			*this = other;
		}

		constexpr rgbN(rgbN<T, N> (*func)()) : impl_type()
		{
			*this = func();
		}

		constexpr ql::rgbN<T, N>& operator=(const ql::rgbN<T, N>& other)
		{
			this->data = other.data;
			return *this;
		}

		template <typename U, ql::size M>
		constexpr ql::rgbN<T, N>& operator=(const ql::rgbN<U, M>& other)
		{
			constexpr ql::f64 delta = ql::f64_cast(max_channel()) / ql::rgbN<U, M>::max_channel();

			this->clear_black();

			if constexpr (is_floating_point())
			{
				for (ql::size i = 0u; i < std::min(N, M); ++i)
				{
					this->data[i] = static_cast<T>(other[i] * delta);
				}
			}
			else
			{
				for (ql::size i = 0u; i < std::min(N, M); ++i)
				{
					this->data[i] = static_cast<T>(ql::clamp<ql::f64>(0, std::round(other[i] * delta), max_channel()));
				}
			}
			return *this;
		}

		template <typename U, ql::size M>
		constexpr ql::rgbN<T, N>& operator=(const ql::vectorN<U, M>& other)
		{
			this->clear_black();

			if constexpr (is_floating_point())
			{
				for (ql::size i = 0u; i < std::min(N, M); ++i)
				{
					this->data[i] = static_cast<T>(other[i]);
				}
			}
			else
			{
				for (ql::size i = 0u; i < std::min(N, M); ++i)
				{
					this->data[i] = static_cast<T>(ql::clamp<ql::f64>(0, std::round(other[i]), max_channel()));
				}
			}
			return *this;
		}

		template <typename U>
		constexpr ql::rgbN<T, N>& operator=(const std::initializer_list<U>& list)
		{
			this->clear_black();

			if constexpr (is_floating_point())
			{
				for (ql::size i = 0u; i < ql::min(list.size(), this->data.size()); ++i)
				{
					this->data[i] = static_cast<T>(*(list.begin() + i));
				}
			}
			else
			{
				for (ql::size i = 0u; i < ql::min(list.size(), this->data.size()); ++i)
				{
					this->data[i] = static_cast<T>(std::round(*(list.begin() + i)));
				}
			}
			return *this;
		}

		template <typename Tuple>
		requires (ql::is_tuple<Tuple>())
		constexpr ql::rgbN<T, N>& operator=(const Tuple& tuple)
		{
			this->clear_black();

			constexpr auto size = std::min(N, std::tuple_size_v<Tuple>);
			ql::constexpr_iterate<size>([&](auto i) { this->data[i] = static_cast<T>(std::get<i>(tuple)); });
			return *this;
		}

		constexpr ql::rgbN<T, N>& operator=(rgbN<T, N> (*func)())
		{
			*this = func();
			return *this;
		}

#if defined QL_GRAPHIC
		constexpr rgbN(sf::Color color)
		{
			*this = color;
		}

		constexpr ql::rgbN<T, N>& operator=(sf::Color color)
		{
			constexpr ql::f64 delta = ql::f64_cast(max_channel()) / 255;

			this->r = static_cast<T>(color.r * delta);

			if constexpr (has_green())
			{
				this->g = static_cast<T>(color.g * delta);
			}
			if constexpr (has_blue())
			{
				this->b = static_cast<T>(color.b * delta);
			}
			if constexpr (has_alpha())
			{
				this->a = static_cast<T>(color.a * delta);
			}
			return *this;
		}

		constexpr operator sf::Color() const
		{
			constexpr ql::f64 delta = 255 / ql::f64_cast(max_channel());

			if constexpr (N == 1)
			{
				return sf::Color(static_cast<sf::Uint8>(std::round(this->r * delta)), 0, 0);
			}
			else if constexpr (N == 2)
			{
				return sf::Color(
						static_cast<sf::Uint8>(std::round(this->r * delta)), static_cast<sf::Uint8>(std::round(this->g * delta)), 0
				);
			}
			else if constexpr (N == 3)
			{
				return sf::Color(
						static_cast<sf::Uint8>(std::round(this->r * delta)), static_cast<sf::Uint8>(std::round(this->g * delta)),
						static_cast<sf::Uint8>(std::round(this->b * delta))
				);
			}
			else
			{
				return sf::Color(
						static_cast<sf::Uint8>(std::round(this->r * delta)), static_cast<sf::Uint8>(std::round(this->g * delta)),
						static_cast<sf::Uint8>(std::round(this->b * delta)), static_cast<sf::Uint8>(std::round(this->a * delta))
				);
			}
		}
#endif
		constexpr void clear_black()
		{
			this->data.fill(min_channel());
			if constexpr (has_alpha())
			{
				this->data[3] = max_channel();
			}
		}

		constexpr void clear_white()
		{
			this->data.fill(max_channel());
		}

		constexpr ql::size size() const
		{
			return this->data.size();
		}

		constexpr auto& operator[](ql::size index)
		{
			return this->data[index];
		}

		constexpr const auto& operator[](ql::size index) const
		{
			return this->data[index];
		}

		constexpr auto& at(ql::size index)
		{
			return this->data[index];
		}

		constexpr const auto& at(ql::size index) const
		{
			return this->data[index];
		}

		constexpr auto begin()
		{
			return this->data.begin();
		}

		constexpr const auto begin() const
		{
			return this->data.begin();
		}

		constexpr const auto cbegin() const
		{
			return this->data.cbegin();
		}

		constexpr auto end()
		{
			return this->data.end();
		}

		constexpr const auto end() const
		{
			return this->data.end();
		}

		constexpr const auto cend() const
		{
			return this->data.cend();
		}

		constexpr auto rbegin()
		{
			return this->data.rbegin();
		}

		constexpr const auto rbegin() const
		{
			return this->data.rbegin();
		}

		constexpr const auto rcbegin() const
		{
			return this->data.crbegin();
		}

		constexpr auto rend()
		{
			return this->data.rend();
		}

		constexpr const auto rend() const
		{
			return this->data.rend();
		}

		constexpr const auto rcend() const
		{
			return this->data.crend();
		}

		constexpr auto min() const
		{
			if constexpr (N >= 4)
			{
				return *std::min_element(this->data.cbegin(), this->data.cend() - 1);
			}
			else
			{
				return *std::min_element(this->data.cbegin(), this->data.cend());
			}
		}

		constexpr auto max() const
		{
			if constexpr (N >= 4)
			{
				return *std::max_element(this->data.cbegin(), this->data.cend() - 1);
			}
			else
			{
				return *std::max_element(this->data.cbegin(), this->data.cend());
			}
		}

		constexpr auto sum() const
		{
			if constexpr (N >= 4)
			{
				return std::accumulate(this->data.cbegin(), this->data.cend() - 1, T{0});
			}
			else
			{
				return std::accumulate(this->data.cbegin(), this->data.cend(), T{0});
			}
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr ql::rgbN<T, N>& operator/=(U value)
		{
			for (auto& i : this->data)
			{
				i = static_cast<T>(i / value);
			}
			return *this;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr auto operator/(U value) const
		{
			rgbN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy /= value;
			return copy;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr ql::rgbN<T, N>& operator*=(U value)
		{
			for (auto& i : this->data)
			{
				i = static_cast<T>(i * value);
			}
			return *this;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr auto operator*(U value) const
		{
			rgbN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy *= value;
			return copy;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr ql::rgbN<T, N>& operator+=(U value)
		{
			for (auto& i : this->data)
			{
				i = static_cast<T>(i + value);
			}
			return *this;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr auto operator+(U value) const
		{
			rgbN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy += value;
			return copy;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr ql::rgbN<T, N>& operator-=(U value)
		{
			for (auto& i : this->data)
			{
				i = static_cast<T>(i - value);
			}
			return *this;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr auto operator-(U value) const
		{
			rgbN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy -= value;
			return copy;
		}

		constexpr ql::rgbN<T, N>& operator/=(const ql::rgbN<T, N>& other)
		{
			for (ql::size i = 0u; i < N; ++i)
			{
				this->data[i] /= other[i];
			}
			return *this;
		}

		template <typename U>
		constexpr ql::rgbN<T, N> operator/(const ql::rgbN<U, N>& other) const
		{
			ql::rgbN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy /= other;
			return copy;
		}

		constexpr ql::rgbN<T, N>& operator*=(const ql::rgbN<T, N>& other)
		{
			for (ql::size i = 0u; i < N; ++i)
			{
				this->data[i] *= other[i];
			}
			return *this;
		}

		template <typename U>
		constexpr ql::rgbN<T, N> operator*(const ql::rgbN<U, N>& other) const
		{
			ql::rgbN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy *= other;
			return copy;
		}

		constexpr ql::rgbN<T, N>& operator+=(const ql::rgbN<T, N>& other)
		{
			for (ql::size i = 0u; i < N; ++i)
			{
				this->data[i] += other[i];
			}
			return *this;
		}

		template <typename U>
		constexpr ql::rgbN<T, N> operator+(const ql::rgbN<U, N>& other) const
		{
			ql::rgbN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy += other;
			return copy;
		}

		constexpr ql::rgbN<T, N>& operator-=(const ql::rgbN<T, N>& other)
		{
			for (ql::size i = 0u; i < N; ++i)
			{
				this->data[i] -= other[i];
			}
			return *this;
		}

		template <typename U>
		constexpr ql::rgbN<T, N> operator-(const ql::rgbN<U, N>& other) const
		{
			ql::rgbN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy -= other;
			return copy;
		}

		template <typename U, ql::size M>
		constexpr bool operator==(const ql::rgbN<U, M>& other) const
		{
			return *this == ql::rgbN<T, N>(other);
		}

		template <typename U, ql::size M>
		constexpr bool operator!=(const ql::rgbN<U, M>& other) const
		{
			return *this != ql::rgbN<T, N>(other);
		}

		constexpr bool operator==(const ql::rgbN<T, N>& other) const
		{
			return this->data == other.data;
		}

		constexpr bool operator!=(const ql::rgbN<T, N>& other) const
		{
			return this->data != other.data;
		}

		constexpr void brighten(delta_type delta)
		{
			if constexpr (is_floating_point())
			{
				if constexpr (has_alpha())
				{
					auto acopy = this->a;
					delta = ql::clamp(delta);
					*this = white() * delta + *this * (1 - delta);
					this->a = acopy;
				}
				else
				{
					delta = ql::clamp(delta);
					*this = white() * delta + *this * (1 - delta);
				}
			}
			else
			{
				ql::rgbN<ql::f64, N> color = *this;
				color.brighten(delta);
				*this = color;
			}
		}

		constexpr ql::rgbN<T, N> brightened(delta_type delta) const
		{
			auto copy = *this;
			copy.brighten(delta);
			return copy;
		}

		constexpr void darken(delta_type delta)
		{
			if constexpr (is_floating_point())
			{
				if constexpr (has_alpha())
				{
					auto acopy = this->a;
					delta = ql::clamp(delta);
					*this = *this * (1 - delta);
					this->a = acopy;
				}
				else
				{
					delta = ql::clamp(delta);
					*this = *this * (1 - delta);
				}
			}
			else
			{
				ql::rgbN<ql::f64, N> color = *this;
				color.darken(delta);
				*this = color;
			}
		}

		constexpr ql::rgbN<T, N> darkened(delta_type delta) const
		{
			auto copy = *this;
			copy.darken(delta);
			return copy;
		}

		constexpr void light(delta_type delta)
		{
			if (delta < 0)
			{
				this->darken(-delta);
			}
			else
			{
				this->brighten(delta);
			}
		}

		constexpr ql::rgbN<T, N> lighted(delta_type delta) const
		{
			auto copy = *this;
			copy.light(delta);
			return copy;
		}

		constexpr void intensify(delta_type delta)
		{
			if constexpr (is_floating_point())
			{
				if constexpr (has_alpha())
				{
					auto acopy = this->a;
					delta = ql::clamp(delta);
					auto min = this->min();
					auto max = this->max();

					auto diff = max - min;

					auto saturated = (*this - ql::rgbN<T, N>::filled(min)) / diff;
					*this = saturated * delta + *this * (1 - delta);
					this->a = acopy;
				}
				else
				{
					delta = ql::clamp(delta);
					auto min = this->min();
					auto max = this->max();

					auto diff = max - min;

					auto saturated = (*this - ql::rgbN<T, N>::filled(min)) / diff;
					*this = saturated * delta + *this * (1 - delta);
				}
			}
			else
			{
				ql::rgbN<ql::f64, N> color = *this;
				color.intensify(delta);
				*this = color;
			}
		}

		constexpr ql::rgbN<T, N> intensified(delta_type delta) const
		{
			auto copy = *this;
			copy.intensify(delta);
			return copy;
		}

		constexpr void grayify(delta_type delta)
		{
			if constexpr (is_floating_point())
			{
				if constexpr (has_alpha())
				{
					auto acopy = this->a;
					delta = ql::clamp(delta);
					auto scale = this->sum();
					auto grayified = ql::rgbN<T, N>(scale, scale, scale) / 3.0f;
					*this = grayified * delta + *this * (1 - delta);
					this->a = acopy;
				}
				else
				{
					delta = ql::clamp(delta);
					auto scale = this->sum();
					auto grayified = ql::rgbN<T, N>(scale, scale, scale) / 3.0f;
					*this = grayified * delta + *this * (1 - delta);
				}
			}
			else
			{
				ql::rgbN<ql::f64, N> color = *this;
				color.grayify(delta);
				*this = color;
			}
		}

		constexpr ql::rgbN<T, N> grayified(delta_type delta) const
		{
			auto copy = *this;
			copy.grayify(delta);
			return copy;
		}

		constexpr void saturate(delta_type delta)
		{
			if (delta < 0)
			{
				this->grayify(-delta);
			}
			else
			{
				this->intensify(delta);
			}
		}

		constexpr ql::rgbN<T, N> saturated(delta_type delta) const
		{
			auto copy = *this;
			copy.saturate(delta);
			return copy;
		}

		constexpr void grayify_perceived(delta_type delta)
		{
			if constexpr (is_floating_point())
			{
				if constexpr (has_alpha())
				{
					auto acopy = this->a;
					delta = ql::clamp(delta);
					auto scale = this->get_perceived_brightness();
					auto grayified = ql::rgbN<ql::f64, N>(scale, scale, scale);
					*this = grayified * delta + *this * (1 - delta);
					this->a = acopy;
				}
				else
				{
					delta = ql::clamp(delta);
					auto scale = this->get_perceived_brightness();
					auto grayified = ql::rgbN<ql::f64, N>(scale, scale, scale);
					*this = grayified * delta + *this * (1 - delta);
				}
			}
			else
			{
				ql::rgbN<ql::f64, N> color = *this;
				color.grayify_perceived(delta);
				*this = color;
			}
		}

		constexpr ql::rgbN<T, N> grayified_perceived(delta_type delta) const
		{
			auto copy = *this;
			copy.grayify_perceived(delta);
			return copy;
		}

		constexpr void saturate_perceived(delta_type delta)
		{
			if (delta < 0)
			{
				this->grayify_perceived(-delta);
			}
			else
			{
				this->intensify(delta);
			}
		}

		constexpr ql::rgbN<T, N> saturated_perceived(delta_type delta) const
		{
			auto copy = *this;
			copy.saturate_perceived(delta);
			return copy;
		}

		constexpr void interpolate(const ql::rgbN<T, N>& other, delta_type delta)
		{
			*this = *this * (1.0 - delta) + (other * delta);
		}

		constexpr ql::rgbN<T, N> interpolated(const ql::rgbN<T, N>& other, delta_type delta) const
		{
			auto copy = *this;
			copy.interpolate(other, delta);
			return copy;
		}

		constexpr void invert()
		{
			for (ql::size i = 0u; i < std::min(ql::size{3}, this->size()); ++i)
			{
				this->data[i] = max_channel() - this->data[i];
			}
		}

		constexpr ql::rgbN<T, N> inverted() const
		{
			auto copy = *this;
			copy.invert();
			return copy;
		}

		constexpr auto with_alpha(T alpha) const
		{
			if constexpr (N >= 4)
			{
				auto copy = *this;
				copy.data[3] = alpha;
				return copy;
			}
			else
			{
				ql::rgbN<T, 4> copy = *this;
				return copy.with_alpha(alpha);
			}
		}

		constexpr ql::rgbN<T, N> multiplied_color(const ql::rgbN<T, N>& other) const
		{
			auto copy = *this;
			copy = copy * ql::rgbN<ql::f32, N>(other);
			return copy;
		}

		constexpr auto multiplied_alpha(T alpha) const
		{
			if constexpr (N >= 4)
			{
				auto copy = *this;
				copy.data[3] = static_cast<T>(copy.data[3] * (alpha / ql::f64_cast(max_channel())));
				return copy;
			}
			else
			{
				ql::rgbN<T, 4> copy = *this;
				return copy.multiplied_alpha(alpha);
			}
		}

		constexpr ql::f64 get_perceived_brightness() const
		{
			if constexpr (ql::is_same<T, ql::f64>() && N == 3)
			{
				return ql::vectorN<T, 3>(this->data).dot(ql::vector3d(0.2126, 0.7152, 0.0722));
			}
			else
			{
				return ql::rgbN<ql::f64, 3>(*this).get_perceived_brightness();
			}
		}

		constexpr ql::f64 get_hue() const
		requires (N >= 3)
		{
			auto min = this->min();
			auto max = this->max();
			auto diff = max - min;
			if (!diff)
			{
				return 0.0;
			}

			if (this->r == max && this->b == min)
			{
				return ((this->g - min) / ql::f64_cast(diff)) / 6.0;
			}
			else if (this->g == max && this->b == min)
			{
				return (1.0 - ((this->r - min) / ql::f64_cast(diff)) + 1.0) / 6.0;
			}
			else if (this->r == min && this->g == max)
			{
				return ((this->b - min) / ql::f64_cast(diff) + 2.0) / 6.0;
			}
			else if (this->r == min && this->b == max)
			{
				return (1.0 - ((this->g - min) / ql::f64_cast(diff)) + 3.0) / 6.0;
			}
			else if (this->g == min && this->b == max)
			{
				return ((this->r - min) / ql::f64_cast(diff) + 4.0) / 6.0;
			}
			else if (this->r == max && this->g == min)
			{
				return (1.0 - ((this->b - min) / ql::f64_cast(diff)) + 5.0) / 6.0;
			}
			return 0.0;
		}

		constexpr void set_hue(ql::f64 hue)
		requires (N >= 3)
		{
			auto min = this->min();
			auto max = this->max();
			auto diff = max - min;
			if (!diff)
			{
				return;
			}

			hue = std::fmod(ql::clamp(hue), 1.0);
			auto segment = ql::u32_cast(hue * 6.0) % 6;
			auto strength = (hue * 6.0) - segment;
			if (segment % 2 == 1u)
			{
				strength = 1.0 - strength;
			}

			T channel;
			if constexpr (is_floating_point())
			{
				channel = static_cast<T>(strength * diff) + min;
			}
			else
			{
				channel = static_cast<T>(std::round(strength * diff)) + min;
			}
			switch (segment)
			{
				case 0u:
					this->r = max;
					this->g = channel;
					this->b = min;
					break;
				case 1u:
					this->r = channel;
					this->g = max;
					this->b = min;
					break;
				case 2u:
					this->r = min;
					this->g = max;
					this->b = channel;
					break;
				case 3u:
					this->r = min;
					this->g = channel;
					this->b = max;
					break;
				case 4u:
					this->r = channel;
					this->g = min;
					this->b = max;
					break;
				case 5u:
					this->r = max;
					this->g = min;
					this->b = channel;
					break;
			}
		}

		constexpr auto with_hue(ql::f64 hue) const
		requires (N >= 3)
		{
			auto copy = *this;
			copy.set_hue(hue);
			return copy;
		}

		constexpr void add_hue(ql::f64 delta_hue)
		requires (N >= 3)
		{
			this->set_hue(std::fmod(this->get_hue() + delta_hue, 1.0));
		}

		constexpr auto with_added_hue(ql::f64 delta_hue) const
		requires (N >= 3)
		{
			auto copy = *this;
			copy.add_hue(delta_hue);
			return copy;
		}

		constexpr ql::f64 get_intensity() const
		requires (N >= 3)
		{
			auto min = this->min();
			auto max = this->max();
			auto diff = max - min;

			return ql::f64_cast(diff) / max_channel();
		}

		constexpr ql::f64 get_perceived_difference(const ql::rgbN<T, N>& other) const
		requires (N >= 3)
		{
			auto h1 = this->get_hue();
			auto h2 = other.get_hue();

			bool swapped = false;
			if (h1 >= h2)
			{
				swapped = true;
				std::swap(h1, h2);
			}

			auto delta_h1 = ql::abs(h1 - h2);
			if (h1 < 0.25 || h2 > 0.75)
			{
				auto delta_h2 = ql::abs((h1 + 1.0) - h2);
				if (delta_h2 < delta_h1)
				{
					h1 += 1.0;
				}
			}
			if (swapped)
			{
				std::swap(h1, h2);
			}
			constexpr auto weights = ql::vec(1.5, 1.0, 1.7).normalized();

			auto vec1 = ql::vec3d(h1, this->get_intensity(), this->get_perceived_brightness()) * weights;
			auto vec2 = ql::vec3d(h2, other.get_intensity(), other.get_perceived_brightness()) * weights;

			return (vec2 - vec1).length();
		}

		constexpr static auto red()
		{
			return ql::rgbN<T, N>{max_channel(), 0, 0};
		}

		constexpr static auto green()
		{
			return ql::rgbN<T, N>(0, max_channel(), 0);
		}

		constexpr static auto blue()
		{
			return ql::rgbN<T, N>(0, 0, max_channel());
		}

		constexpr static auto white()
		{
			return ql::rgbN<T, N>(max_channel(), max_channel(), max_channel());
		}

		constexpr static auto black()
		{
			return ql::rgbN<T, N>(0, 0, 0);
		}

		constexpr static auto yellow()
		{
			return ql::rgbN<T, N>(max_channel(), max_channel(), 0);
		}

		constexpr static auto cyan()
		{
			return ql::rgbN<T, N>(0, max_channel(), max_channel());
		}

		constexpr static auto magenta()
		{
			return ql::rgbN<T, N>(max_channel(), 0, max_channel());
		}

		constexpr static auto unset()
		requires (N >= 4)
		{
			return rgbN(0, 0, 0, 0);
		}

		constexpr static auto transparent()
		requires (N >= 4)
		{
			return rgbN(max_channel(), max_channel(), max_channel(), 0);
		}

		constexpr bool is_unset() const
		requires (N >= 4)
		{
			return *this == unset();
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static rgbN<T, N> filled(U value)
		{
			rgbN<T, N> result;
			result.data.fill(static_cast<T>(value));
			return result;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static rgbN<T, N> grey_shade(U value)
		{
			rgbN<T, N> result;
			result.data.fill(static_cast<T>(value));
			if constexpr (N >= 4)
			{
				result.data[3] = max_channel();
			}
			return result;
		}

		template <typename C>
		requires (ql::is_container<C>() && ql::has_size<C>() && ql::has_square_brackets_read<C>())
		[[nodiscard]] constexpr static ql::rgbN<T, N> interpolation(const C& colors, delta_type strength)
		{
			strength = ql::clamp<delta_type>(delta_type{0.0}, strength, delta_type{1.0});
			if (strength == 1.0)
			{
				return colors.back();
			}

			auto index = ql::size_cast(strength * (colors.size() - 1));
			auto left_over = static_cast<delta_type>(((colors.size() - 1) * strength) - index);

			return colors[index].interpolated(colors[index + 1], left_over);
		}

		template <typename U, ql::size M, typename C>
		requires (ql::is_container<C>() && ql::has_size<C>() && ql::has_square_brackets_read<C>())
		[[nodiscard]] constexpr static ql::rgbN<T, N> interpolation(const C& colors, delta_type strength)
		{
			return interpolation(ql::type_cast<ql::rgbN<T, N>>(colors), strength);
		}

		std::string to_string() const
		{
			bool first = true;
			std::ostringstream stream;
			stream << '(';
			for (ql::size i = 0u; i < this->data.size(); ++i)
			{
				if constexpr (N == 4)
				{
					if (i == 3 && this->data[i] == max_channel())
					{
						break;
					}
				}
				if (!first)
				{
					stream << ", ";
				}

				if constexpr (is_floating_point())
				{
					stream << ql::round(this->data[i], 2);
				}
				else
				{
					stream << static_cast<visible_type>(this->data[i]);
				}
				first = false;
			}
			stream << ')';
			return stream.str();
		}
	};

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator+(U value, const rgbN<T, N>& vec)
	{
		return vec + value;
	}

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator-(U value, const rgbN<T, N>& vec)
	{
		return rgbN<T, N>::filled(value) - vec;
	}

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator*(U value, const rgbN<T, N>& vec)
	{
		return vec * value;
	}

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator/(U value, const rgbN<T, N>& vec)
	{
		return rgbN<T, N>::filled(value) / vec;
	}

	using rgb = rgbN<ql::u8, 3>;
	using rgba = rgbN<ql::u8, 4>;
	using frgb = rgbN<ql::f32, 3>;
	using frgba = rgbN<ql::f32, 4>;

	QL_SOURCE ql::rgb get_random_color();
	QL_SOURCE ql::rgba get_random_transparency_color();
	QL_SOURCE ql::rgb get_rainbow_color(ql::f64 f);
	QL_SOURCE ql::rgb get_random_rainbow_color();

	
	constexpr auto console_colors = std::array{
		/*black,       */ ql::rgba(12, 12, 12),
		/*blue,        */ ql::rgba(0, 55, 218),
		/*green,       */ ql::rgba(19, 161, 14),
		/*aqua,        */ ql::rgba(58, 150, 221),
		/*red,         */ ql::rgba(197, 15, 31),
		/*purple,      */ ql::rgba(136, 23, 152),
		/*yellow,      */ ql::rgba(193, 156, 0),
		/*white,       */ ql::rgba(204, 204, 204),
		/*gray,        */ ql::rgba(118, 118, 118),
		/*light_blue,  */ ql::rgba(59, 120, 255),
		/*light_green, */ ql::rgba(22, 198, 12),
		/*light_aqua,  */ ql::rgba(97, 214, 214),
		/*light_red,   */ ql::rgba(231, 72, 86),
		/*light_purple,*/ ql::rgba(180, 0, 158),
		/*light_yellow,*/ ql::rgba(249, 241, 165),
		/*bright_white,*/ ql::rgba(242, 242, 242),
		/*dark_blue    */ ql::rgba(0, 15, 75),
		/*pink         */ ql::rgba(255, 166, 206),
		/*dark-gray,   */ ql::rgba(83, 83, 83),
		/*transparent, */ ql::rgba::transparent(),
		/*reset*/ ql::rgba::transparent(),
	};

	constexpr ql::rgba print_color_to_rgba(ql::print_color background)
	{
		if (background == ql::print_color::transparent)
		{
			return ql::rgba::transparent();
		}
		return ql::rgba(console_colors[ql::size_cast(background)]);
	}
}	 // namespace ql