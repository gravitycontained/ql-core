#ifndef ql_VECTOR_HPP
#define ql_VECTOR_HPP
#pragma once

#include <ql/definition/definition.hpp>
#include <ql/maths/range.hpp>
#include <ql/transform/possibilities.hpp>
#include <ql/type-traits/type-traits.hpp>
#include <ql/transform/cast/cast.hpp>
#include <ql/type-traits/tuple/value.hpp>
#include <ql/maths/bit-rotate.hpp>
#include <ql/maths/bit-rotate.hpp>

#if defined QL_INTERN_SFML_USE
#include <SFML/Graphics.hpp>
#endif

#if defined QL_INTERN_GLM_USE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#endif

#include <array>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>

namespace ql
{

	template <typename T, ql::size N>
	struct vectorN;

	namespace detail
	{
		template <typename T, ql::size N>
		constexpr auto vectorN_signature(ql::vectorN<T, N>)
		{
			return std::true_type{};
		}

		template <typename T>
		constexpr auto vectorN_signature(T)
		{
			return std::false_type{};
		}
	}	 // namespace detail

	template <typename T>
	constexpr bool is_vectorN()
	{
		return decltype(ql::detail::vectorN_signature(std::declval<T>()))::value;
	}

	namespace impl
	{
		template <typename T, typename V>
		struct vector_impl_1
		{
			union
			{
				struct
				{
					T x;
				};

				std::array<T, 1> data;
			};

			constexpr vector_impl_1() : data()
			{
				this->data.fill(T{});
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_x(U x) const
			{
				return V(static_cast<T>(x));
			}
		};

		template <typename T, typename V>
		struct vector_impl_2
		{
			union
			{
				struct
				{
					T x;
					T y;
				};

				std::array<T, 2> data;
			};

			constexpr vector_impl_2() : data()
			{
				this->data.fill(T{});
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_x(U x) const
			{
				return V{static_cast<T>(x), this->y};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_y(U y) const
			{
				return V{this->x, static_cast<T>(y)};
			}

			constexpr V just_x() const
			{
				return V{this->x, T{0}};
			}

			constexpr V just_y() const
			{
				return V{T{0}, this->y};
			}
		};

		template <typename T, typename V>
		struct vector_impl_3
		{
			union
			{
				struct
				{
					T x;
					T y;
					T z;
				};

				std::array<T, 3> data;
			};

			constexpr vector_impl_3() : data()
			{
				this->data.fill(T{});
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_x(U x) const
			{
				return V{static_cast<T>(x), this->y, this->z};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_y(U y) const
			{
				return V{this->x, static_cast<T>(y), this->z};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_z(U z) const
			{
				return V{this->x, this->y, static_cast<T>(z)};
			}

			constexpr V just_x() const
			{
				return V{this->x, T{0}, T{0}};
			}

			constexpr V just_y() const
			{
				return V{T{0}, this->y, T{0}};
			}

			constexpr V just_z() const
			{
				return V{T{0}, T{0}, this->z};
			}
		};

		template <typename T, typename V>
		struct vector_impl_4
		{
			union
			{
				struct
				{
					T x;
					T y;
					T z;
					T w;
				};

				std::array<T, 4> data;
			};

			constexpr vector_impl_4() : data()
			{
				this->data.fill(T{});
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_x(U x) const
			{
				return V{static_cast<T>(x), this->y, this->z, this->w};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_y(U y) const
			{
				return V{this->x, static_cast<T>(y), this->z, this->w};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_z(U z) const
			{
				return V{this->x, this->y, static_cast<T>(z), this->w};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_w(U w) const
			{
				return V{this->x, this->y, this->z, static_cast<T>(w)};
			}

			constexpr V just_x() const
			{
				return V{this->x, T{0}, T{0}, T{0}};
			}

			constexpr V just_y() const
			{
				return V{T{0}, this->y, T{0}, T{0}};
			}

			constexpr V just_z() const
			{
				return V{T{0}, T{0}, this->z, T{0}};
			}

			constexpr V just_w() const
			{
				return V{T{0}, T{0}, T{0}, this->w};
			}
		};

		template <typename T, typename V>
		struct vector_impl_5
		{
			union
			{
				struct
				{
					T a;
					T b;
					T c;
					T d;
					T e;
				};

				std::array<T, 5> data;
			};

			constexpr vector_impl_5() : data()
			{
				this->data.fill(T{});
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_a(U a) const
			{
				return V{static_cast<T>(a), this->b, this->c, this->d, this->e};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_b(U b) const
			{
				return V{this->a, static_cast<T>(b), this->c, this->d, this->e};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_c(U c) const
			{
				return V{this->a, this->b, static_cast<T>(c), this->d, this->e};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_d(U d) const
			{
				return V{this->a, this->b, this->c, static_cast<T>(d), this->e};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_e(U e) const
			{
				return V{this->a, this->b, this->c, this->d, static_cast<T>(e)};
			}

			constexpr V just_a() const
			{
				return V{this->a, T{0}, T{0}, T{0}, T{0}};
			}

			constexpr V just_b() const
			{
				return V{T{0}, this->b, T{0}, T{0}, T{0}};
			}

			constexpr V just_c() const
			{
				return V{T{0}, T{0}, this->c, T{0}, T{0}};
			}

			constexpr V just_d() const
			{
				return V{T{0}, T{0}, T{0}, this->d, T{0}};
			}

			constexpr V just_e() const
			{
				return V{T{0}, T{0}, T{0}, T{0}, this->e};
			}
		};

		template <typename T, typename V>
		struct vector_impl_6
		{
			union
			{
				struct
				{
					T a;
					T b;
					T c;
					T d;
					T e;
					T f;
				};

				std::array<T, 6> data;
			};

			constexpr vector_impl_6() : data()
			{
				this->data.fill(T{});
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_a(U a) const
			{
				return V{static_cast<T>(a), this->b, this->c, this->d, this->e, this->f};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_b(U b) const
			{
				return V{this->a, static_cast<T>(b), this->c, this->d, this->e, this->f};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_c(U c) const
			{
				return V{this->a, this->b, static_cast<T>(c), this->d, this->e, this->f};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_d(U d) const
			{
				return V{this->a, this->b, this->c, static_cast<T>(d), this->e, this->f};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_e(U e) const
			{
				return V{this->a, this->b, this->c, this->d, static_cast<T>(e), this->f};
			}

			template <typename U>
			requires(ql::is_arithmetic<U>())
			constexpr V with_f(U f) const
			{
				return V{this->a, this->b, this->c, this->d, this->e, static_cast<T>(f)};
			}

			constexpr V just_a() const
			{
				return V{this->a, T{0}, T{0}, T{0}, T{0}, T{0}};
			}

			constexpr V just_b() const
			{
				return V{T{0}, this->b, T{0}, T{0}, T{0}, T{0}};
			}

			constexpr V just_c() const
			{
				return V{T{0}, T{0}, this->c, T{0}, T{0}, T{0}};
			}

			constexpr V just_d() const
			{
				return V{T{0}, T{0}, T{0}, this->d, T{0}, T{0}};
			}

			constexpr V just_e() const
			{
				return V{T{0}, T{0}, T{0}, T{0}, this->e, T{0}};
			}

			constexpr V just_f() const
			{
				return V{T{0}, T{0}, T{0}, T{0}, T{0}, this->f};
			}
		};

		template <typename T, ql::size N>
		struct vector_impl_N
		{
			std::array<T, N> data;

			constexpr vector_impl_N() : data()
			{
				this->data.fill(T{});
			}
		};
	}	 // namespace impl

	namespace detail
	{
		template <typename T, typename U>
		concept vectorN_castable = requires(T a, U b) { a = b; };

		template <typename T, ql::size N>
		using vector_impl_conditional = ql::conditional<ql::if_true<N == 0>,
																										ql::error_type,
																										ql::if_true<N == 1>,
																										impl::vector_impl_1<T, vectorN<T, N>>,
																										ql::if_true<N == 2>,
																										impl::vector_impl_2<T, vectorN<T, N>>,
																										ql::if_true<N == 3>,
																										impl::vector_impl_3<T, vectorN<T, N>>,
																										ql::if_true<N == 4>,
																										impl::vector_impl_4<T, vectorN<T, N>>,
																										ql::if_true<N == 5>,
																										impl::vector_impl_5<T, vectorN<T, N>>,
																										ql::if_true<N == 6>,
																										impl::vector_impl_6<T, vectorN<T, N>>,
																										ql::default_type,
																										impl::vector_impl_N<T, N>>;
	}	 // namespace detail

	template <typename T, ql::size N>
	struct vectorN : ql::detail::vector_impl_conditional<T, N>
	{
		using impl_type = ql::detail::vector_impl_conditional<T, N>;

		constexpr vectorN() : impl_type()
		{
			this->clear();
		}

		template <typename U>
		constexpr vectorN(const vectorN<U, N>& other) : impl_type()
		{
			*this = other;
		}

		constexpr vectorN(const vectorN<T, N>& other) : impl_type()
		{
			*this = other;
		}

		template <typename U, ql::size M>
		constexpr vectorN(const vectorN<U, M>& other) : impl_type()
		{
			*this = other;
		}

		template <typename U>
		requires(!ql::is_vectorN<U>())
		constexpr vectorN(const std::initializer_list<U>& list) : impl_type()
		{
			*this = list;
		}

		template <ql::size N, typename U>
		constexpr vectorN(const std::array<U, N>& array) : impl_type()
		{
			*this = array;
		}

		template <typename... Args>
		requires(sizeof...(Args) > 1)
		constexpr vectorN(Args&&... list) : impl_type()
		{
			*this = std::make_tuple(list...);
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr vectorN(U value) : impl_type()
		{
			*this = value;
		}

		template <typename Tuple>
		requires(ql::is_tuple<Tuple>())
		constexpr vectorN(const Tuple& tuple) : impl_type()
		{
			*this = tuple;
		}

#if defined ql_INTERN_SFML_USE
		template <typename U>
		constexpr vectorN(const sf::Vector2<U>& other) : impl_type()
		{
			*this = other;
		}

		template <typename U>
		constexpr operator sf::Vector2<U>() const
		{
			if constexpr(N == 1)
			{
				return sf::Vector2<U>(static_cast<U>(this->data[0]), U{0});
			}
			else
			{
				return sf::Vector2<U>(static_cast<U>(this->data[0]), static_cast<U>(this->data[1]));
			}
		}

		template <typename U>
		constexpr vectorN& operator=(const sf::Vector2<U>& vec)
		{
			this->x = static_cast<T>(vec.x);
			this->y = static_cast<T>(vec.y);
			if constexpr(N == 1)
			{
				this->x = static_cast<T>(vec.x);
			}
			else
			{
				this->x = static_cast<T>(vec.x);
				this->y = static_cast<T>(vec.y);
			}
			return *this;
		}
#endif

#if defined ql_INTERN_GLM_USE
		template <glm::length_t L, typename T, glm::qualifier Q = glm::defaultp>
		constexpr vectorN(const glm::vec<L, T, Q>& other) : impl_type()
		{
			*this = other;
		}

		template <glm::length_t L, typename T, glm::qualifier Q = glm::defaultp>
		constexpr operator glm::vec<L, T, Q>() const
		{
			glm::vec<L, T, Q> result;
			memcpy(&result, this, sizeof(*this));
			return result;
		}

		template <glm::length_t L, typename T, glm::qualifier Q = glm::defaultp>
		constexpr vectorN& operator=(const glm::vec<L, T, Q>& vec)
		{
			memcpy(this, &vec, sizeof(*this));
			return *this;
		}
#endif

		constexpr vectorN& operator=(const vectorN<T, N>& other)
		{
			this->data = other.data;
			return *this;
		}

		template <typename U>
		constexpr vectorN& operator=(const vectorN<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] = static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U, ql::size M>
		constexpr vectorN& operator=(const vectorN<U, M>& other)
		{
			for(ql::u32 i = 0u; i < ql::min(N, M); ++i)
			{
				this->data[i] = static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <ql::size N, typename U>
		constexpr vectorN& operator=(const std::array<U, N>& array)
		{
			if(array.empty())
			{
				this->clear();
				return *this;
			}
			for(ql::u32 i = 0u; i < ql::min(array.size(), this->data.size()); ++i)
			{
				this->data[i] = static_cast<T>(array[i]);
			}
			return *this;
		}

		template <typename Tuple>
		requires(ql::is_tuple<Tuple>())
		constexpr vectorN& operator=(const Tuple& tuple)
		{
			this->data = ql::tuple_to_array(tuple);
			return *this;
		}

		template <typename U>
		requires(!ql::is_vectorN<U>())
		constexpr vectorN& operator=(const std::initializer_list<U>& list)
		{
			if(list.size() == 0)
			{
				this->clear();
				return *this;
			}
			for(ql::size i = 0u; i < ql::min(list.size(), this->data.size()); ++i)
			{
				this->data[i] = static_cast<T>(*(list.begin() + i));
			}
			return *this;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr vectorN& operator=(U value)
		{
			this->data[0u] = value;
			for(ql::size i = 1u; i < N; ++i)
			{
				this->data[i] = T{0};
			}
			return *this;
		}

		template <typename U>
		constexpr void move(const vectorN<U, N>& delta)
		{
			*this += delta;
		}

		template <typename U, typename... Args>
		constexpr void move(U first, Args&&... list)
		{
			*this += vectorN(first, list...);
		}

		template <typename U>
		constexpr auto moved(const vectorN<U, N>& delta) const
		{
			return *this + delta;
		}

		template <typename U, typename... Args>
		constexpr auto moved(U first, Args&&... list)
		{
			return *this + vectorN(first, list...);
		}

		constexpr static vectorN values(T value)
		{
			vectorN result;
			for(auto& i : result.data)
			{
				i = value;
			}
			return result;
		}

		constexpr static vectorN zero()
		{
			return vectorN::values(0);
		}

		constexpr static vectorN one()
		{
			return vectorN::values(1);
		}

		constexpr vectorN floor() const
		{
			vectorN result = *this;
			for(auto& i : result.data)
			{
				i = std::floor(i);
			}
			return result;
		}

		constexpr vectorN ceil() const
		{
			vectorN result = *this;
			for(auto& i : result.data)
			{
				i = std::ceil(i);
			}
			return result;
		}

		constexpr vectorN round() const
		{
			vectorN result = *this;
			for(auto& i : result.data)
			{
				i = std::round(i);
			}
			return result;
		}

		constexpr void clear()
		{
			for(auto& i : this->data)
			{
				i = T{};
			}
		}

		constexpr bool empty() const
		{
			for(auto& i : this->data)
			{
				if(i != T{})
				{
					return false;
				}
			}
			return true;
		}

		constexpr T& operator[](ql::size index)
		{
			return this->data[index];
		}

		constexpr const T& operator[](ql::size index) const
		{
			return this->data[index];
		}

		constexpr T& at(ql::size index)
		{
			return this->data.at(index);
		}

		constexpr const T& at(ql::size index) const
		{
			return this->data.at(index);
		}

		constexpr T& back()
		{
			return this->data.back();
		}

		constexpr const T& back() const
		{
			return this->data.back();
		}

		constexpr T& front()
		{
			return this->data.front();
		}

		constexpr const T& front() const
		{
			return this->data.front();
		}

		constexpr auto begin()
		{
			return this->data.begin();
		}

		constexpr const auto begin() const
		{
			return this->data.cbegin();
		}

		constexpr auto cbegin()
		{
			return this->data.cbegin();
		}

		constexpr auto end()
		{
			return this->data.end();
		}

		constexpr const auto end() const
		{
			return this->data.cend();
		}

		constexpr auto cend()
		{
			return this->data.cend();
		}

		constexpr auto rbegin()
		{
			return this->data.rbegin();
		}

		constexpr const auto rbegin() const
		{
			return this->data.crbegin();
		}

		constexpr auto crbegin()
		{
			return this->data.crbegin();
		}

		constexpr auto rend()
		{
			return this->data.rend();
		}

		constexpr const auto rend() const
		{
			return this->data.crend();
		}

		constexpr auto crend()
		{
			return this->data.crend();
		}

		constexpr ql::size size() const
		{
			return N;
		}

		constexpr bool operator<(const vectorN& other) const
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if(this->data[i] < static_cast<T>(other.data[i]))
				{
					return true;
				}
				if(this->data[i] > static_cast<T>(other.data[i]))
				{
					return false;
				}
			}
			return false;
		}

		constexpr bool operator<=(const vectorN& other) const
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if(this->data[i] < static_cast<T>(other.data[i]))
				{
					return true;
				}
				if(this->data[i] > static_cast<T>(other.data[i]))
				{
					return false;
				}
			}
			return true;
		}

		constexpr bool operator>(const vectorN& other) const
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if(this->data[i] > static_cast<T>(other.data[i]))
				{
					return true;
				}
				if(this->data[i] < static_cast<T>(other.data[i]))
				{
					return false;
				}
			}
			return false;
		}

		constexpr bool operator>=(const vectorN& other) const
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if(this->data[i] > static_cast<T>(other.data[i]))
				{
					return true;
				}
				if(this->data[i] < static_cast<T>(other.data[i]))
				{
					return false;
				}
			}
			return true;
		}

		template <typename U>
		constexpr bool operator==(const vectorN<U, N>& other) const
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if(this->data[i] != static_cast<T>(other.data[i]))
				{
					return false;
				}
			}
			return true;
		}

		template <typename U>
		constexpr bool operator!=(const vectorN<U, N>& other) const
		{
			return !(*this == other);
		}

		template <typename U>
		constexpr vectorN<T, N>& operator+=(const std::initializer_list<U>& list)
		{
			vectorN<T, N> add;
			add.set(list);
			return (*this += add);
		}

		template <typename U>
		constexpr vectorN<T, N>& operator+=(const vectorN<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] += static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator+=(const std::array<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] += static_cast<T>(other[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr auto operator+(const vectorN<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy += other;
			return copy;
		}

		template <typename U>
		constexpr auto operator+(const std::array<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy += other;
			return copy;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator+=(U u)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] += static_cast<T>(u);
			}
			return *this;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr auto operator+(U u) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy += u;
			return copy;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator-=(const std::initializer_list<U>& list)
		{
			vectorN<T, N> add;
			add.set(list);
			return (*this -= add);
		}

		template <typename U>
		constexpr vectorN<T, N>& operator-=(const vectorN<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] -= static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator-=(const std::array<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] -= static_cast<T>(other[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr auto operator-(const vectorN<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy -= other;
			return copy;
		}

		template <typename U>
		constexpr auto operator-(const std::array<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy -= other;
			return copy;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator-=(U u)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] -= static_cast<T>(u);
			}
			return *this;
		}

		template <typename U>
		constexpr auto operator-(U u) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy -= u;
			return copy;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator*=(const std::initializer_list<U>& list)
		{
			vectorN<T, N> add;
			add.set(list);
			return (*this *= add);
		}

		template <typename U>
		constexpr vectorN<T, N>& operator*=(const vectorN<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] *= static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator*=(const std::array<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] *= static_cast<T>(other[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr auto operator*(const vectorN<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy *= other;
			return copy;
		}

		template <typename U>
		constexpr auto operator*(const std::array<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy *= other;
			return copy;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator*=(U u)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] *= static_cast<T>(u);
			}
			return *this;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr auto operator*(U u) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy *= u;
			return copy;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator/=(const std::initializer_list<U>& list)
		{
			vectorN<T, N> add;
			add.set(list);
			return (*this /= add);
		}

		template <typename U>
		constexpr vectorN<T, N>& operator/=(const vectorN<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] /= static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator/=(const std::array<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] /= static_cast<T>(other[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr auto operator/(const vectorN<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy /= other;
			return copy;
		}

		template <typename U>
		constexpr auto operator/(const std::array<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy /= other;
			return copy;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator/=(U u)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] /= static_cast<T>(u);
			}
			return *this;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr auto operator/(U u) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy /= u;
			return copy;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator%=(const std::initializer_list<U>& list)
		{
			vectorN<T, N> add;
			add.set(list);
			return (*this %= add);
		}

		template <typename U>
		constexpr vectorN<T, N>& operator%=(const vectorN<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] %= static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator%=(const std::array<U, N>& other)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] %= static_cast<T>(other[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr auto operator%(const vectorN<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy %= other;
			return copy;
		}

		template <typename U>
		constexpr auto operator%(const std::array<U, N>& other) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy %= other;
			return copy;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator%=(U u)
		{
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if constexpr(ql::is_floating_point<T>())
				{
					this->data[i] = std::fmod(this->data[i], static_cast<T>(u));
				}
				else
				{
					this->data[i] %= static_cast<T>(u);
				}
			}
			return *this;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr auto operator%(U u) const
		{
			vectorN<ql::superior_arithmetic_type<T, U>, N> copy = *this;
			copy %= u;
			return copy;
		}

		constexpr auto list_possibilities_range() const
		{
			return ql::list_possibilities(this->data);
		}

		template <typename T, ql::size N>
		constexpr static auto list_possibilities_range(const ql::vectorN<T, N>& range)
		{
			return range.list_possibilities_range();
		}

		template <typename T, ql::size N>
		constexpr static auto list_possibilities_range(const ql::vectorN<T, N>& min, const ql::vectorN<T, N>& max)
		{
			return ql::list_possibilities(min.data, max.data);
		}

		constexpr vectorN operator-() const
		{
			vectorN copy;
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				copy.data[i] = -this->data[i];
			}
			return copy;
		}

		constexpr vectorN operator+() const
		{
			vectorN copy;
			for(ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				copy.data[i] = +this->impl_type::data[i];
			}
			return copy;
		}

		constexpr auto reversed() const
		{
			vectorN copy;
			for(ql::size i = 0u; i < this->size(); ++i)
			{
				copy[this->size() - i - 1] = this->data[i];
			}
			return copy;
		}

		constexpr void reverse()
		{
			*this = this->reversed();
		}

		constexpr auto length() const
		{
			if(std::is_constant_evaluated())
			{
				return ql::f64_cast(ql::sqrt(this->dot(*this)));
			}
			else
			{
				return ql::f64_cast(std::sqrt(this->dot(*this)));
			}
		}

		constexpr vectorN normalized() const
		{
			if(this->length() == 0)
				return vectorN{};

			return *this / this->length();
		}

		constexpr auto angle() const
		requires(N == 2)
		{
			auto atan = ql::f64_cast(std::atan2(ql::f64_cast(this->y), -ql::f64_cast(this->x)));
			if(atan < 0)
				atan = 2 * ql::pi + atan;
			return atan;
		}

		constexpr void set_rotation(ql::f64 angle)
		requires(N == 2)
		{
			auto x = std::cos(angle);
			auto y = std::sin(angle);
			*this = vectorN(x, y) * this->length();
		}

		constexpr void set_rotation_around(vectorN center, ql::f64 angle)
		requires(N == 2)
		{
			auto x = std::cos(angle);
			auto y = std::sin(angle);
			auto diff = *this - center;
			*this = center + vectorN(x, y) * diff.length();
		}

		constexpr void rotate(ql::f64 delta_angle)
		requires(N == 2)
		{
			this->set_rotation(-this->angle() + delta_angle);
		}

		constexpr void rotate_around(vectorN center, ql::f64 delta_angle)
		requires(N == 2)
		{
			auto diff = *this - center;
			auto angle = diff.angle() + delta_angle;

			auto x = std::cos(angle);
			auto y = std::sin(angle);
			*this = center + vectorN(x, y) * diff.length();
		}

		constexpr auto rotated(ql::f64 delta_angle) const
		requires(N == 2)
		{
			auto copy = *this;
			copy.rotate(delta_angle);
			return copy;
		}

		constexpr auto rotated_around(vectorN center, ql::f64 delta_angle) const
		requires(N == 2)
		{
			auto copy = *this;
			copy.rotate_around(center, delta_angle);
			return copy;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr auto dot(const vectorN<U, N>& other) const
		{
			auto n = ql::superior_arithmetic_type<T, U>{0};
			for(ql::size i = 0u; i < N; ++i)
			{
				n += this->data[i] * other.data[i];
			}
			return n;
		}

		constexpr auto dot(const vectorN& other) const
		{
			auto n = T{0};
			for(ql::size i = 0u; i < N; ++i)
			{
				n += this->data[i] * other.data[i];
			}
			return n;
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto sum(const vectorN<T, N>& vec)
		{
			return std::accumulate(vec.begin(), vec.end(), T{0});
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto abs(const vectorN<T, N>& vec)
		{
			ql::vectorN<T, N> result = vec;
			for(auto& i : result)
			{
				i = std::abs(i);
			}
			return result;
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto sin(const vectorN<T, N>& vec)
		{
			ql::vectorN<T, N> result = vec;
			for(auto& i : result)
			{
				i = std::sin(i);
			}
			return result;
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto cos(const vectorN<T, N>& vec)
		{
			ql::vectorN<T, N> result = vec;
			for(auto& i : result)
			{
				i = std::cos(i);
			}
			return result;
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto tan(const vectorN<T, N>& vec)
		{
			ql::vectorN<T, N> result = vec;
			for(auto& i : result)
			{
				i = std::tan(i);
			}
			return result;
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto min(const vectorN<T, N>& vec)
		{
			return *std::min_element(vec.data.begin(), vec.data.end());
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto max(const vectorN<T, N>& vec)
		{
			return *std::max_element(vec.data.begin(), vec.data.end());
		}

		template <typename T, typename U, ql::size N>
		[[nodiscard]] constexpr static auto max_values(const vectorN<T, N>& a, const vectorN<U, N>& b)
		{
			using R = ql::superior_arithmetic_type<T, U>;
			vectorN<R, N> result;
			for(ql::size i = 0u; i < a.size(); ++i)
			{
				result[i] = std::max(static_cast<R>(a[i]), static_cast<R>(b[i]));
			}
			return result;
		}

		template <typename T, typename U, ql::size N>
		[[nodiscard]] constexpr static auto min_values(const vectorN<T, N>& a, const vectorN<U, N>& b)
		{
			using R = ql::superior_arithmetic_type<T, U>;
			vectorN<R, N> result;
			for(ql::size i = 0u; i < a.size(); ++i)
			{
				result[i] = std::min(static_cast<R>(a[i]), static_cast<R>(b[i]));
			}
			return result;
		}

		constexpr void clamp(T min, T max)
		{
			for(auto& i : this->data)
			{
				i = ql::clamp(min, i, max);
			}
		}

		constexpr auto clamped(T min, T max) const
		{
			ql::vectorN<T, N> result = *this;
			result.clamp(min, max);
			return result;
		}

		template <typename T, ql::size N>
		constexpr void clamp(vectorN<T, N> max)
		{
			for(ql::size i = 0u; i < this->size(); ++i)
			{
				this->data[i] = ql::clamp(T{0}, this->data[i], max[i]);
			}
		}

		template <typename T, ql::size N>
		constexpr auto clamped(vectorN<T, N> max) const
		{
			ql::vectorN<T, N> result = *this;
			result.clamp(max);
			return result;
		}

		template <typename T, ql::size N>
		constexpr void clamp(vectorN<T, N> min, vectorN<T, N> max)
		{
			for(ql::size i = 0u; i < this->size(); ++i)
			{
				this->data[i] = ql::clamp(min[i], this->data[i], max[i]);
			}
		}

		template <typename T, ql::size N>
		constexpr auto clamped(vectorN<T, N> min, vectorN<T, N> max) const
		{
			ql::vectorN<T, N> result = *this;
			result.clamp(min, max);
			return result;
		}

		constexpr auto sum() const
		{
			return ql::vectorN<T, N>::sum(*this);
		}

		constexpr auto abs() const
		{
			return ql::vectorN<T, N>::abs(*this);
		}

		constexpr ql::vectorN<T, N> sin() const
		{
			return ql::vectorN<T, N>::sin(*this);
		}

		constexpr ql::vectorN<T, N> cos() const
		{
			return ql::vectorN<T, N>::cos(*this);
		}

		constexpr ql::vectorN<T, N> tan() const
		{
			return ql::vectorN<T, N>::tan(*this);
		}

		constexpr auto min() const
		{
			return ql::vectorN<T, N>::min(*this);
		}

		constexpr auto max() const
		{
			return ql::vectorN<T, N>::max(*this);
		}

		template <typename T, typename U, ql::size N>
		[[nodiscard]] constexpr static auto dot(const vectorN<T, N>& a, const vectorN<U, N>& b)
		{
			auto n = ql::superior_arithmetic_type<T, U>{0};
			for(ql::size i = 0u; i < N; ++i)
			{
				n += a.data[i] * b.data[i];
			}
			return n;
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto normalize(const vectorN<T, N>& vec)
		{
			return vec * (1.0 / std::sqrt(vectorN<T, N>::dot(vec, vec)));
		}

		template <typename T, typename U, ql::size N>
		requires(N == 3)
		[[nodiscard]] constexpr static auto cross(const vectorN<T, N>& a, const vectorN<U, N>& b)
		{
			ql::vectorN<ql::superior_arithmetic_type<T, U>, N> result;
			result.x = a.y * b.z - b.y * a.z;
			result.y = a.z * b.x - b.z * a.x;
			result.z = a.x * b.y - b.x * a.y;
			return result;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static vectorN<T, N> filled(U value)
		{
			vectorN<T, N> result;
			result.data.fill(static_cast<T>(value));
			return result;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr void fill(U value)
		{
			this->data.fill(static_cast<T>(value));
		}

		constexpr std::string string() const
		{
			std::ostringstream stream;
			stream << '(';
			bool first = true;
			for(auto& i : this->data)
			{
				if(!first)
				{
					stream << ", ";
				}
				first = false;
				stream << i;
			}
			stream << ')';
			return stream.str();
		}

		constexpr std::string precisionString(ql::size precision) const
		{
			std::ostringstream stream;
			stream << '(';
			bool first = true;
			for(auto& i : this->data)
			{
				if(!first)
					stream << ", ";

				first = false;
				stream << std::fixed << std::setprecision(precision) << i;
			}
			stream << ')';
			return stream.str();
		}

		template <ql::size N, typename T>
		friend std::ostream& operator<<(std::ostream& os, const ql::vectorN<T, N>& vec);
	};

	template <typename T, typename U, ql::size N>
	requires(ql::is_arithmetic<U>())
	constexpr auto operator+(U value, const vectorN<T, N>& vec)
	{
		return vectorN<T, N>::filled(value) + vec;
	}

	template <typename T, typename U, ql::size N>
	requires(ql::is_arithmetic<U>())
	constexpr auto operator-(U value, const vectorN<T, N>& vec)
	{
		return vectorN<T, N>::filled(value) - vec;
	}

	template <typename T, typename U, ql::size N>
	requires(ql::is_arithmetic<U>())
	constexpr auto operator*(U value, const vectorN<T, N>& vec)
	{
		return vectorN<T, N>::filled(value) * vec;
	}

	template <typename T, typename U, ql::size N>
	requires(ql::is_arithmetic<U>())
	constexpr auto operator/(U value, const vectorN<T, N>& vec)
	{
		return vectorN<T, N>::filled(value) / vec;
	}

	template <typename T, ql::size N>
	std::ostream& operator<<(std::ostream& os, const ql::vectorN<T, N>& vec)
	{
		return os << vec.string();
	}

	template <typename T>
	requires(ql::is_vectorN<T>())
	constexpr auto list_possibilities(T value)
	{
		return ql::list_possibilities(value.data);
	}

	template <typename T>
	requires(ql::is_vectorN<T>())
	constexpr auto list_possibilities(T start, T end)
	{
		return ql::list_possibilities(start.data, end.data);
	}

	template <typename T = ql::f32>
	using vector2 = ql::vectorN<T, 2>;
	using vector2f = ql::vector2<ql::f32>;
	using vector2d = ql::vector2<ql::f64>;
	using vector2i = ql::vector2<ql::i32>;
	using vector2u = ql::vector2<ql::u32>;
	using vector2s = ql::vector2<ql::size>;
	using vector2is = ql::vector2<ql::isize>;

	template <typename T = ql::f32>
	using vector3 = ql::vectorN<T, 3>;
	using vector3f = ql::vector3<ql::f32>;
	using vector3d = ql::vector3<ql::f64>;
	using vector3i = ql::vector3<ql::i32>;
	using vector3u = ql::vector3<ql::u32>;
	using vector3s = ql::vector3<ql::size>;
	using vector3is = ql::vector3<ql::isize>;

	template <typename T = ql::f32>
	using vector4 = ql::vectorN<T, 4>;
	using vector4f = ql::vector4<ql::f32>;
	using vector4d = ql::vector4<ql::f64>;
	using vector4i = ql::vector4<ql::i32>;
	using vector4u = ql::vector4<ql::u32>;
	using vector4s = ql::vector4<ql::size>;
	using vector4is = ql::vector4<ql::isize>;

	template <typename T = ql::f32>
	using vector5 = ql::vectorN<T, 5>;
	using vector5f = ql::vector5<ql::f32>;
	using vector5d = ql::vector5<ql::f64>;
	using vector5i = ql::vector5<ql::i32>;
	using vector5u = ql::vector5<ql::u32>;
	using vector5s = ql::vector5<ql::size>;
	using vector5is = ql::vector5<ql::isize>;

	template <typename T = ql::f32>
	using vector6 = ql::vectorN<T, 6>;
	using vector6f = ql::vector6<ql::f32>;
	using vector6d = ql::vector6<ql::f64>;
	using vector6i = ql::vector6<ql::i32>;
	using vector6u = ql::vector6<ql::u32>;
	using vector6s = ql::vector6<ql::size>;
	using vector6is = ql::vector6<ql::isize>;

	using vec2 = ql::vector2f;
	using vec2f = ql::vector2f;
	using vec2d = ql::vector2d;
	using vec2i = ql::vector2i;
	using vec2u = ql::vector2u;
	using vec2s = ql::vector2s;
	using vec2is = ql::vector2is;

	using vec3 = ql::vector3f;
	using vec3f = ql::vector3f;
	using vec3d = ql::vector3d;
	using vec3i = ql::vector3i;
	using vec3u = ql::vector3u;
	using vec3s = ql::vector3s;
	using vec3is = ql::vector3is;

	using vec4 = ql::vector4f;
	using vec4f = ql::vector4f;
	using vec4d = ql::vector4d;
	using vec4i = ql::vector4i;
	using vec4u = ql::vector4u;
	using vec4s = ql::vector4s;
	using vec4is = ql::vector4is;

	using vec5 = ql::vector5f;
	using vec5f = ql::vector5f;
	using vec5d = ql::vector5d;
	using vec5i = ql::vector5i;
	using vec5u = ql::vector5u;
	using vec5s = ql::vector5s;
	using vec5is = ql::vector5is;

	using vec6 = ql::vector6f;
	using vec6f = ql::vector6f;
	using vec6d = ql::vector6d;
	using vec6i = ql::vector6i;
	using vec6u = ql::vector6u;
	using vec6s = ql::vector6s;
	using vec6is = ql::vector6is;

	template <typename T, ql::size N>
	struct texN : ql::vectorN<T, N>
	{
	};

	template <typename... Args>
	requires(ql::is_arithmetic<Args>() && ...)
	constexpr auto vec(Args... rest)
	{
		using R = ql::superior_arithmetic_type<Args...>;
		return ql::vectorN<R, sizeof...(Args)>(rest...);
	}

	template <typename... Args>
	requires(ql::is_arithmetic<Args>() && ...)
	constexpr auto tex(Args... rest)
	{
		using R = ql::superior_arithmetic_type<Args...>;
		return texN<R, sizeof...(Args)>(ql::vectorN<R, sizeof...(Args)>(rest...));
	}

	namespace detail
	{
		template <ql::size check, typename T, ql::size N>
		requires(N == check)
		constexpr auto vectorN_signature(ql::vectorN<T, N>)
		{
			return std::true_type{};
		}

		template <ql::size check, typename T>
		constexpr auto vectorN_signature(T)
		{
			return std::false_type{};
		}

		template <typename T, ql::size N>
		constexpr auto tex_signature(ql::texN<T, N>)
		{
			return std::true_type{};
		}

		template <typename T>
		constexpr auto tex_signature(T)
		{
			return std::false_type{};
		}

		template <ql::size check, typename T, ql::size N>
		requires(N == check)
		constexpr auto texN_signature(ql::texN<T, N>)
		{
			return std::true_type{};
		}

		template <ql::size check, typename T>
		constexpr auto texN_signature(T)
		{
			return std::false_type{};
		}
	}	 // namespace detail

	template <typename T, ql::size N>
	constexpr bool is_vectorN()
	{
		return decltype(detail::vectorN_signature<N>(ql::declval<T>()))::value;
	}

	template <typename T>
	constexpr bool is_tex()
	{
		return decltype(detail::tex_signature(ql::declval<T>()))::value;
	}

	template <typename T, ql::size N>
	constexpr bool is_texN()
	{
		return decltype(detail::texN_signature<N>(ql::declval<T>()))::value;
	}

	template <typename T, ql::size N>
	struct matrixN
	{
		using vec = ql::vectorN<T, N>;
		using matrix_type = std::array<vec, N>;
		matrix_type data;

		constexpr matrixN()
		{
			this->clear();
		}

		template <typename U>
		constexpr matrixN(const std::initializer_list<std::initializer_list<U>>& list) : data()
		{
			*this = list;
		}

		template <typename U, ql::size M>
		constexpr matrixN(const matrixN<U, M>& other) : data()
		{
			*this = other;
		}

		constexpr matrixN(const matrixN& other) : data()
		{
			*this = other;
		}

		template <typename... Args>
		requires(sizeof...(Args) > 1)
		constexpr matrixN(Args&&... other) : data()
		{
			auto tuple = std::make_tuple(other...);
			*this = tuple;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr matrixN(U value) : data()
		{
			*this = value;
		}

		template <typename Tuple>
		requires(ql::is_tuple<Tuple>())
		constexpr matrixN(const Tuple& tuple) : data()
		{
			*this = tuple;
		}

		template <typename U>
		constexpr matrixN& operator=(const std::initializer_list<std::initializer_list<U>>& list)
		{
			if(list.size() == 0)
			{
				this->clear();
				return *this;
			}
			for(ql::u32 i = 0u; i < ql::min(list.size(), this->data.size()); ++i)
			{
				this->data[i] = *(list.begin() + i);
			}
			return *this;
		}

		template <typename T>
		requires(ql::is_tuple<T>())
		constexpr matrixN& operator=(const T& tuple)
		{
			constexpr auto size = ql::tuple_size<T>();
			ql::constexpr_iterate<size>([](auto i) { this->data[i] = ql::tuple_value<i>(tuple); });
			return *this;
		}

		template <typename U, ql::size M>
		constexpr matrixN& operator=(const matrixN<U, M>& other)
		{
			for(ql::size i = 0u; i < ql::min(N, M); ++i)
			{
				for(ql::size j = 0u; j < ql::min(N, M); ++j)
				{
					this->data[i][j] = other.data[i][j];
				}
			}
			return *this;
		}

		constexpr matrixN& operator=(const matrixN& other)
		{
			this->data = other.data;
			return *this;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr matrixN& operator=(U value)
		{
			return *this = matrixN::filled_diagonally(value);
		}

		constexpr vec& operator[](ql::size index)
		{
			return this->data[index];
		}

		constexpr const vec& operator[](ql::size index) const
		{
			return this->data[index];
		}

		constexpr vec& at(ql::size index)
		{
			return this->data.at(index);
		}

		constexpr const vec& at(ql::size index) const
		{
			return this->data.at(index);
		}

		constexpr vec& back()
		{
			return this->data.back();
		}

		constexpr const vec& back() const
		{
			return this->data.back();
		}

		constexpr vec& front()
		{
			return this->data.front();
		}

		constexpr const vec& front() const
		{
			return this->data.front();
		}

		constexpr auto begin()
		{
			return this->data.begin();
		}

		constexpr const auto begin() const
		{
			return this->data.cbegin();
		}

		constexpr auto cbegin()
		{
			return this->data.cbegin();
		}

		constexpr auto end()
		{
			return this->data.end();
		}

		constexpr const auto end() const
		{
			return this->data.cend();
		}

		constexpr auto cend()
		{
			return this->data.cend();
		}

		constexpr auto rbegin()
		{
			return this->data.rbegin();
		}

		constexpr const auto rbegin() const
		{
			return this->data.crbegin();
		}

		constexpr auto crbegin()
		{
			return this->data.crbegin();
		}

		constexpr auto rend()
		{
			return this->data.rend();
		}

		constexpr const auto rend() const
		{
			return this->data.crend();
		}

		constexpr auto crend()
		{
			return this->data.crend();
		}

		template <typename U, ql::size M>
		constexpr matrixN& operator+=(const matrixN<U, M>& other)
		{
			for(ql::size i = 0u; i < ql::min(N, M); ++i)
			{
				for(ql::size j = 0u; j < ql::min(N, M); ++j)
				{
					this->data[i][j] += other[i][j];
				}
			}
			return *this;
		}

		constexpr matrixN& operator+=(const matrixN& other)
		{
			for(ql::size i = 0u; i < N; ++i)
			{
				this->data[i] += other[i];
			}
			return *this;
		}

		template <typename U, ql::size M>
		constexpr auto operator+(const matrixN<U, M>& other) const
		{
			matrixN<ql::superior_arithmetic_type<T, U>, ql::max(N, M)> result = *this;
			result += other;
			return result;
		}

		template <typename U, ql::size M>
		constexpr matrixN& operator-=(const matrixN<U, M>& other)
		{
			for(ql::size i = 0u; i < ql::min(N, M); ++i)
			{
				for(ql::size j = 0u; j < ql::min(N, M); ++j)
				{
					this->data[i][j] -= other[i][j];
				}
			}
			return *this;
		}

		constexpr matrixN& operator-=(const matrixN& other)
		{
			for(ql::size i = 0u; i < N; ++i)
			{
				this->data[i] -= other[i];
			}
			return *this;
		}

		template <typename U, ql::size M>
		constexpr auto operator-(const matrixN<U, M>& other) const
		{
			matrixN<ql::superior_arithmetic_type<T, U>, ql::max(N, M)> result = *this;
			result -= other;
			return result;
		}

		constexpr matrixN operator*(const matrixN& other) const
		{
			matrixN result;

			for(ql::size i = 0u; i < N; ++i)
			{
				vec sum;
				for(ql::size j = 0u; j < N; ++j)
				{
					sum += this->data[j] * other[i][j];
				}
				result[i] = sum;
			}

			return result;
		}

		constexpr ql::vectorN<T, N> operator*(const ql::vectorN<T, N>& vec) const
		{
			ql::vectorN<T, N> result;
			for(ql::size i = 0u; i < N; ++i)
			{
				for(ql::size j = 0u; j < N; ++j)
				{
					result.data[i] += this->data[j][i] * vec.data[j];
				}
			}
			return result;
		}

		template <typename U, ql::size M>
		constexpr matrixN& operator/=(const matrixN<U, M>& other)
		{
			for(ql::size i = 0u; i < ql::min(N, M); ++i)
			{
				for(ql::size j = 0u; j < ql::min(N, M); ++j)
				{
					this->data[i][j] /= other[i][j];
				}
			}
			return *this;
		}

		constexpr matrixN& operator/=(const matrixN& other)
		{
			for(ql::size i = 0u; i < N; ++i)
			{
				this->data[i] /= other[i];
			}
			return *this;
		}

		template <typename U, ql::size M>
		constexpr auto operator/(const matrixN<U, M>& other) const
		{
			matrixN<ql::superior_arithmetic_type<T, U>, ql::max(N, M)> result = *this;
			result /= other;
			return result;
		}

		constexpr matrixN operator-() const
		{
			auto copy = *this;
			for(auto& i : copy)
			{
				i = -i;
			}
			return copy;
		}

		constexpr matrixN operator+() const
		{
			auto copy = *this;
			for(auto& i : copy)
			{
				i = +i;
			}
			return copy;
		}

		constexpr bool operator==(const matrixN& other) const
		{
			for(ql::size i = 0u; i < N; ++i)
			{
				if(this->data[i] != other[i])
				{
					return false;
				}
			}
			return true;
		}

		constexpr bool operator!=(const matrixN& other) const
		{
			return !(*this == other);
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr void fill(U value)
		{
			for(auto& i : this->data)
			{
				i.fill(static_cast<T>(value));
			}
		}

		template <typename A, typename U>
		requires(N == 4)
		constexpr matrixN rotated(A angle, const ql::vector3<U>& vec) const
		{
			auto c = std::cos(angle);
			auto s = std::sin(angle);

			auto axis = vec.normalized();
			auto temp = (A{1} - c) * axis;

			matrixN rotate;
			rotate[0].x = static_cast<T>(c + temp.x * axis.x);
			rotate[0].y = static_cast<T>(temp.x * axis.y + s * axis.z);
			rotate[0].z = static_cast<T>(temp.x * axis.z - s * axis.y);

			rotate[1].x = static_cast<T>(temp.y * axis.x - s * axis.z);
			rotate[1].y = static_cast<T>(c + temp.y * axis.y);
			rotate[1].z = static_cast<T>(temp.y * axis.z + s * axis.x);

			rotate[2].x = static_cast<T>(temp.z * axis.x + s * axis.y);
			rotate[2].y = static_cast<T>(temp.z * axis.y - s * axis.x);
			rotate[2].z = static_cast<T>(c + temp.z * axis.z);

			matrixN result;
			result[0] = this->data[0] * rotate[0].x + this->data[1] * rotate[0].y + this->data[2] * rotate[0].z;
			result[1] = this->data[0] * rotate[1].x + this->data[1] * rotate[1].y + this->data[2] * rotate[1].z;
			result[2] = this->data[0] * rotate[2].x + this->data[1] * rotate[2].y + this->data[2] * rotate[2].z;
			result[3] = this->data[3];
			return result;
		}

		template <typename A, typename U>
		requires(N == 4)
		constexpr matrixN& rotate(A angle, const ql::vector3<U>& vec)
		{
			*this = this->rotated(angle, vec);
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static matrixN<T, N> filled(U value)
		{
			matrixN<T, N> result;

			for(auto& v : result)
			{
				v = vec::filled(value);
			}

			return result;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static matrixN<T, N> filled_front(U value)
		{
			matrixN<T, N> result;

			for(auto& v : result)
			{
				v = vec(value);
			}

			return result;
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static matrixN<T, N> filled_diagonally(U value)
		{
			matrixN<T, N> result;

			for(ql::size i = 0u; i < N; ++i)
			{
				result.data[i][i] = static_cast<T>(value);
			}
			return result;
		}

		template <typename A>
		requires(N == 4)
		[[nodiscard]] constexpr static matrixN rotate(const matrixN& matrix, A angle, const ql::vector3<T>& vec)
		{
			return matrix.rotated(angle, vec);
		}

		template <typename A, typename U>
		requires(N == 4)
		[[nodiscard]] constexpr static matrixN rotate(const matrixN& matrix, A angle, const ql::vector3<U>& vec)
		{
			return matrix.rotated(angle, vec);
		}

		template <typename U>
		requires(N == 4)
		[[nodiscard]] constexpr static matrixN translate(const matrixN& matrix, const ql::vector3<U>& vec)
		{
			matrixN result(matrix);
			result[3] = matrix[0] * vec.x + matrix[1] * vec.y + matrix[2] * vec.z + matrix[3];
			return result;
		}

		template <typename U, typename V, typename W>
		requires(N == 4)
		[[nodiscard]] constexpr static matrixN
		look_at(const ql::vector3<U>& eye, const ql::vector3<V>& center, const ql::vector3<W>& up)
		{
			auto f = vec::normalize(center - eye);
			auto s = vec::normalize(vec::cross(f, up));
			auto u = vec::cross(s, f);

			matrixN result(T{1});
			result[0].x = static_cast<T>(s.x);
			result[1].x = static_cast<T>(s.y);
			result[2].x = static_cast<T>(s.z);
			result[0].y = static_cast<T>(u.x);
			result[1].y = static_cast<T>(u.y);
			result[2].y = static_cast<T>(u.z);
			result[0].z = static_cast<T>(-f.x);
			result[1].z = static_cast<T>(-f.y);
			result[2].z = static_cast<T>(-f.z);
			result[3].x = static_cast<T>(-vec::dot(s, eye));
			result[3].y = static_cast<T>(-vec::dot(u, eye));
			result[3].z = static_cast<T>(vec::dot(f, eye));
			return result;
		}

		template <typename U>
		requires(N == 4)
		[[nodiscard]] constexpr static matrixN perspective(U fovy, U aspect, U zNear, U zFar)
		{
			auto tanHalfFovy = std::tan(fovy / 2.0);

			matrixN result(T{0});
			result[0].x = static_cast<T>(T{1} / (aspect * tanHalfFovy));
			result[1].y = static_cast<T>(T{1} / tanHalfFovy);
			result[2].z = static_cast<T>(-(zFar + zNear) / (zFar - zNear));
			result[2].w = -T{1};
			result[3].z = static_cast<T>((-T{2} * zFar * zNear) / (zFar - zNear));
			return result;
		}

		template <typename U>
		requires(N == 4)
		[[nodiscard]] constexpr static matrixN frustum(U left, U right, U bottom, U top, U nearVal, U farVal)
		{
			matrixN result(T{0});
			result[0][0] = (static_cast<T>(2) * nearVal) / (right - left);
			result[1][1] = (static_cast<T>(2) * nearVal) / (top - bottom);
			result[2][0] = (right + left) / (right - left);
			result[2][1] = (top + bottom) / (top - bottom);
			result[2][2] = -(farVal + nearVal) / (farVal - nearVal);
			result[2][3] = static_cast<T>(-1);
			result[3][2] = -(static_cast<T>(2) * farVal * nearVal) / (farVal - nearVal);
			return result;
		}

#if defined ql_INTERN_GLM_USE
		template <typename U>
		operator glm::mat<N, N, U>() const
		{
			using length_type = glm::mat<N, N, U>::length_type;
			glm::mat4 result;
			for(ql::size i = 0u; i < N; ++i)
			{
				for(ql::size j = 0u; j < N; ++j)
				{
					result[static_cast<length_type>(i)][static_cast<length_type>(j)] = static_cast<U>(this->data[i][j]);
				}
			}
			return result;
		}

		template <typename U>
		constexpr matrixN(const glm::mat<N, N, U>& mat)
		{
			using length_type = glm::mat<N, N, U>::length_type;
			for(ql::size i = 0u; i < N; ++i)
			{
				for(ql::size j = 0u; j < N; ++j)
				{
					this->data[i][j] = static_cast<T>(mat[static_cast<length_type>(i)][static_cast<length_type>(j)]);
				}
			}
		}
#endif

		constexpr void clear()
		{
			for(auto& i : this->data)
			{
				i.clear();
			}
		}

		constexpr std::string string() const
		{
			std::ostringstream stream;
			stream << '[';
			bool first_row = true;
			for(auto& i : this->data)
			{
				if(!first_row)
				{
					stream << ", ";
				}
				first_row = false;

				stream << i.string();
			}
			stream << ']';
			return stream.str();
		}

		template <ql::size N, typename T>
		friend std::ostream& operator<<(std::ostream& os, const ql::matrixN<T, N>& mat);
	};

	template <typename T1, typename T2>
	constexpr auto rotate(T1 angle, const ql::vectorN<T2, 3>& normal)
	{
		using superior = ql::superior_arithmetic_type<T1, T2>;
		return ql::matrixN<superior, 4>(1).rotated(angle, normal);
	}

	template <typename T1, typename T2, typename T3>
	constexpr ql::vec3 rotate(const ql::vectorN<T1, 3>& vec, T2 angle, const ql::vectorN<T3, 3>& normal)
	{
		using superior = ql::superior_arithmetic_type<T1, T2, T3>;
		return ql::matrixN<superior, 3>(ql::rotate(angle, normal)) * vec;
	}

	template <typename T1, typename T2, typename T3>
	constexpr ql::vec3 rotate_towards(const ql::vectorN<T1, 3>& vec, T2 angle, const ql::vectorN<T3, 3>& normal)
	{
		using superior = ql::superior_arithmetic_type<T1, T3>;
		auto up = ql::vectorN<superior, 3>::cross(vec, normal);
		return ql::rotate(vec, angle, up);
	}

	template <typename T1, typename T2>
	constexpr ql::vec3 rotate_x(const ql::vectorN<T1, 3>& vec, T2 angle)
	{
		return ql::rotate_towards(vec, angle, ql::vec(1, 0, 0));
	}

	template <typename T1, typename T2>
	constexpr ql::vec3 rotate_y(const ql::vectorN<T1, 3>& vec, T2 angle)
	{
		return ql::rotate_towards(vec, angle, ql::vec(0, 1, 0));
	}

	template <typename T1, typename T2>
	constexpr ql::vec3 rotate_z(const ql::vectorN<T1, 3>& vec, T2 angle)
	{
		return ql::rotate_towards(vec, angle, ql::vec(0, 0, 1));
	}

	constexpr auto vec_square4 = std::array{ql::vec(0, 0), ql::vec(1, 0), ql::vec(1, 1), ql::vec(0, 1)};
	constexpr auto vec_diagonals4 = std::array{std::array{ql::vec(-1, -1), ql::vec(1, -1), ql::vec(1, 1), ql::vec(-1, 1)}};
	constexpr auto vec_cross4 = std::array{ql::vec(1, 0), ql::vec(0, 1), ql::vec(-1, 0), ql::vec(0, -1)};
	constexpr auto vec_cross9 = std::array{ql::vec(-1, 0),	ql::vec(1, 0),	ql::vec(0, -1), ql::vec(0, 1),
																				 ql::vec(-1, -1), ql::vec(1, -1), ql::vec(1, 1),	ql::vec(-1, 1)};
	constexpr auto vec_box8 = std::array{ql::vec(0.0, 0.0), ql::vec(0.5, 0.0), ql::vec(1.0, 0.0), ql::vec(1.0, 0.5),
																			 ql::vec(1.0, 1.0), ql::vec(0.5, 1.0), ql::vec(0.0, 1.0), ql::vec(0.0, 0.5)};

	template <ql::size N, typename T>
	std::ostream& operator<<(std::ostream& os, const ql::matrixN<T, N>& mat)
	{
		return os << mat.string();
	}

	template <typename T, typename U, ql::size N>
	requires(ql::is_arithmetic<U>())
	constexpr auto operator+(U value, const matrixN<T, N>& mat)
	{
		return matrixN<T, N>::filled(value) + mat;
	}

	template <typename T, typename U, ql::size N>
	requires(ql::is_arithmetic<U>())
	constexpr auto operator-(U value, const matrixN<T, N>& mat)
	{
		return matrixN<T, N>::filled(value) - mat;
	}

	template <typename T, typename U, ql::size N>
	requires(ql::is_arithmetic<U>())
	constexpr auto operator*(U value, const matrixN<T, N>& mat)
	{
		return matrixN<T, N>::filled(value) * mat;
	}

	template <typename T, typename U, ql::size N>
	requires(ql::is_arithmetic<U>())
	constexpr auto operator/(U value, const matrixN<T, N>& mat)
	{
		return matrixN<T, N>::filled(value) / mat;
	}

	template <typename T = ql::f32>
	using matrix2 = ql::matrixN<T, 2>;
	using matrix2f = ql::matrix2<ql::f32>;
	using matrix2d = ql::matrix2<ql::f64>;

	template <typename T = ql::f32>
	using matrix3 = ql::matrixN<T, 3>;
	using matrix3f = ql::matrix3<ql::f32>;
	using matrix3d = ql::matrix3<ql::f64>;

	template <typename T = ql::f32>
	using matrix4 = ql::matrixN<T, 4>;
	using matrix4f = ql::matrix4<ql::f32>;
	using matrix4d = ql::matrix4<ql::f64>;

	template <typename T = ql::f32>
	using matrix5 = ql::matrixN<T, 5>;
	using matrix5f = ql::matrix5<ql::f32>;
	using matrix5d = ql::matrix5<ql::f64>;

	template <typename T = ql::f32>
	using matrix6 = ql::matrixN<T, 6>;
	using matrix6f = ql::matrix6<ql::f32>;
	using matrix6d = ql::matrix6<ql::f64>;

	using mat2 = ql::matrix2f;
	using mat2f = ql::matrix2f;
	using mat2d = ql::matrix2d;

	using mat3 = ql::matrix3f;
	using mat3f = ql::matrix3f;
	using mat3d = ql::matrix3d;

	using mat4 = ql::matrix4f;
	using mat4f = ql::matrix4f;
	using mat4d = ql::matrix4d;

	using mat5 = ql::matrix5f;
	using mat5f = ql::matrix5f;
	using mat5d = ql::matrix5d;

	using mat6 = ql::matrix6f;
	using mat6f = ql::matrix6f;
	using mat6d = ql::matrix6d;

	template <typename T>
	struct straight_line_t
	{
		using maths_float_type = ql::conditional<ql::if_true<ql::is_same<T, ql::f32>()>, ql::f32, ql::default_type, ql::f64>;

		constexpr straight_line_t() : a(), b()
		{
		}

		constexpr straight_line_t(ql::vector2<T> a, ql::vector2<T> b) : a(a), b(b)
		{
		}

		std::string string() const
		{
			std::ostringstream stream;
			stream << '[';
			stream << this->a.string() << ", " << this->b.string();
			stream << ']';
			return stream.str();
		}

		maths_float_type length() const
		{
			auto diff = this->b - this->a;
			return static_cast<maths_float_type>(std::sqrt(diff.x * diff.x + diff.y * diff.y));
		}

		ql::vector2<maths_float_type> normal() const
		{
			return ql::vector2<maths_float_type>{this->a.y - this->b.y, this->b.x - this->a.x} / this->length();
		}

		maths_float_type angle() const
		{
			auto atan = std::atan2(this->a.y - this->b.y, this->b.x - this->a.x);
			if(atan < 0)
				atan = static_cast<decltype(atan)>(2 * ql::pi + atan);
			return static_cast<maths_float_type>(atan);
		}

		void set_rotation_a(ql::f64 angle)
		{
			auto x = std::cos(angle);
			auto y = std::sin(angle);
			this->a = this->b + ql::vec(x, y) * this->length();
		}

		void set_rotation_b(ql::f64 angle)
		{
			auto x = std::cos(angle);
			auto y = std::sin(angle);
			this->b = this->a + ql::vec(x, y) * this->length();
		}

		constexpr bool collides(straight_line_t other) const
		{
			auto mode = [](ql::vector2<T> a, ql::vector2<T> b, ql::vector2<T> c)
			{
				auto ba = b - a;
				auto cb = c - b;
				auto x = ba.y * cb.x - ba.x * cb.y;

				if(x < T{0})
				{
					return 2u;
				}
				else if(x > T{0})
				{
					return 1u;
				}
				else
				{
					return 0u;
				}
			};
			auto collide = [](ql::vector2<T> a, ql::vector2<T> b, ql::vector2<T> c)
			{
				auto check_x = b.x <= ql::max(a.x, c.x) && b.x >= ql::min(a.x, c.x);
				auto check_y = b.y <= ql::max(a.y, c.y) && b.y >= ql::min(a.y, c.y);
				return check_x && check_y;
			};
			auto m1 = mode(this->a, this->b, other.a);
			auto m2 = mode(this->a, this->b, other.b);
			auto m3 = mode(other.a, other.b, this->a);
			auto m4 = mode(other.a, other.b, this->b);

			if(m1 != m2 && m3 != m4)
			{
				return true;
			}

			if(m1 == T{0} && collide(this->a, other.a, this->b))
			{
				return true;
			}
			if(m2 == T{0} && collide(this->a, other.b, this->b))
			{
				return true;
			}
			if(m3 == T{0} && collide(other.a, this->a, other.b))
			{
				return true;
			}
			if(m4 == T{0} && collide(other.a, this->b, other.b))
			{
				return true;
			}

			return false;
		}

		ql::vector2<T> a;
		ql::vector2<T> b;
	};

	using straight_line = straight_line_t<ql::f32>;

	enum class box_side
	{
		top_left = 0,
		top_center = 1,
		top_right = 2,
		right_top = 2,
		right_center = 3,
		right_bottom = 4,
		bottom_right = 4,
		bottom_center = 5,
		bottom_left = 6,
		left_bottom = 6,
		left_center = 7,
		left_top = 0,
		size = 8
	};

	template <typename T>
	struct hitbox_t
	{
		ql::vector2<T> dimension;
		ql::vector2<T> position;

		constexpr hitbox_t()
		{
			this->position = this->dimension = ql::vector2<T>(0, 0);
		}

		constexpr hitbox_t(ql::vector2<T> position, ql::vector2<T> dimension)
		{
			this->position = position;
			this->dimension = dimension;
		}

		constexpr void set_width(T width)
		{
			this->dimension.x = width;
		}

		constexpr void set_height(T height)
		{
			this->dimension.y = height;
		}

		constexpr void set_dimension(ql::vector2<T> dimension)
		{
			this->dimension = dimension;
		}

		constexpr void set_position(ql::vector2<T> position)
		{
			this->position = position;
		}

		constexpr void set_center(ql::vector2<T> position)
		{
			this->position = position - this->dimension / 2;
		}

		constexpr ql::vector2<T> get_center() const
		{
			return this->position + this->dimension / 2;
		}

		constexpr ql::vector2<T> get_dimension() const
		{
			return this->dimension;
		}

		constexpr ql::vector2<T> get_position() const
		{
			return this->position;
		}

		constexpr T get_width() const
		{
			return this->dimension.x;
		}

		constexpr T get_height() const
		{
			return this->dimension.y;
		}

		constexpr std::string string() const
		{
			std::ostringstream stream;
			stream << '[';
			stream << this->position.string() << ", " << this->dimension.string();
			stream << ']';
			return stream.str();
		}

		constexpr void increase(T delta)
		{
			this->position -= ql::vector2<T>(delta, delta);
			this->dimension += ql::vector2<T>(delta, delta) * 2;
		}

		constexpr void increase(ql::vector2<T> delta)
		{
			this->position -= delta;
			this->dimension += delta * 2;
		}

		constexpr void increase_x(T delta)
		{
			this->position.x -= delta;
			this->dimension.x += delta * 2;
		}

		constexpr void increase_y(T delta)
		{
			this->position.y -= delta;
			this->dimension.y += delta * 2;
		}

		constexpr ql::hitbox_t<T> increased(T delta) const
		{
			auto copy = *this;
			copy.increase(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> increased(ql::vector2<T> delta) const
		{
			auto copy = *this;
			copy.increase(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> increased_y(T delta) const
		{
			auto copy = *this;
			copy.increase_y(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> increased_x(T delta) const
		{
			auto copy = *this;
			copy.increase_x(delta);
			return copy;
		}

		constexpr void decrease(T delta)
		{
			this->position += ql::vector2<T>(delta, delta);
			this->dimension -= ql::vector2<T>(delta, delta) * 2;
		}

		constexpr void decrease(ql::vector2<T> delta)
		{
			this->position += delta;
			this->dimension -= delta * 2;
		}

		constexpr void decrease_x(T delta)
		{
			this->position.x += delta;
			this->dimension.x -= delta * 2;
		}

		constexpr void decrease_y(T delta)
		{
			this->position.y += delta;
			this->dimension.y -= delta * 2;
		}

		constexpr ql::hitbox_t<T> decreased(T delta) const
		{
			auto copy = *this;
			copy.decrease(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> decreased(ql::vector2<T> delta) const
		{
			auto copy = *this;
			copy.decrease(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> decreased_y(T delta) const
		{
			auto copy = *this;
			copy.decrease_y(delta);
			return copy;
		}

		constexpr ql::hitbox_t<T> decreased_x(T delta) const
		{
			auto copy = *this;
			copy.decrease_x(delta);
			return copy;
		}

		constexpr bool contains(ql::vector2f position) const
		{
			return (position.x > this->position.x && position.x < (this->position.x + this->dimension.x) &&
							position.y > this->position.y && position.y < (this->position.y + this->dimension.y));
		}

		template <typename U>
		constexpr bool collides(ql::straight_line_t<U> line) const
		{
			auto x1 = this->get_position().x;
			auto x2 = this->get_position().x + this->get_dimension().x;
			auto y1 = this->get_position().y;
			auto y2 = this->get_position().y + this->get_dimension().y;

			return this->collides(x1, x2, y1, y2, line);
		}

		template <typename U>
		constexpr bool collides(ql::straight_line_t<U> line, T increase) const
		{
			auto x1 = this->get_position().x - increase;
			auto x2 = this->get_position().x + this->get_dimension().x + increase;
			auto y1 = this->get_position().y - increase;
			auto y2 = this->get_position().y + this->get_dimension().y + increase;

			return this->collides(x1, x2, y1, y2, line);
		}

		template <typename U>
		constexpr bool collides(const ql::hitbox_t<U>& hitbox) const
		{
			auto a1 = this->position;
			auto a2 = this->position + this->dimension;
			auto b1 = hitbox.position;
			auto b2 = hitbox.position + hitbox.dimension;

			auto x1_inside = a1.x >= b1.x && a1.x <= b2.x;
			auto x2_inside = a2.x >= b1.x && a2.x <= b2.x;
			auto y1_inside = a1.y >= b1.y && a1.y <= b2.y;
			auto y2_inside = a2.y >= b1.y && a2.y <= b2.y;

			auto either_x_inside = x1_inside || x2_inside;
			auto either_y_inside = y1_inside || y2_inside;

			if(either_x_inside && either_y_inside)
				return true;

			auto ax_outside = a1.x < b1.x && a2.x > b2.x;
			auto ay_outside = a1.y < b1.y && a2.y > b2.y;

			if(ax_outside && ay_outside)
				return true;

			auto bx_inside = b1.x < a1.x && b2.x > a2.x;
			auto by_inside = b1.y < a1.y && b2.y > a2.y;

			if(bx_inside && by_inside)
				return true;

			if(ax_outside && either_y_inside)
				return true;
			if(ay_outside && either_x_inside)
				return true;

			return false;
		}

		template <typename U>
		constexpr bool corners_collide_with(const ql::hitbox_t<U>& hitbox) const
		{
			auto p1 = this->position;
			auto p2 = this->position + this->dimension.just_x();
			auto p3 = this->position + this->dimension.just_y();
			auto p4 = this->position + this->dimension;
			return hitbox.contains(p1) || hitbox.contains(p2) || hitbox.contains(p3) || hitbox.contains(p4);
		}

		template <typename U>
		constexpr void move(ql::vector2<U> delta)
		{
			this->position += ql::vector2<T>(delta);
		}

		template <typename U>
		requires(ql::is_arithmetic<U>())
		constexpr void move(U x, U y)
		{
			this->position += ql::vector2<T>(x, y);
		}

		template <typename U>
		constexpr void extend_left(U delta)
		{
			this->position -= ql::vector2<T>(delta, T{0});
			this->dimension += ql::vector2<T>(delta, T{0});
		}

		template <typename U>
		constexpr ql::hitbox_t<T> extended_left(U delta) const
		{
			auto copy = *this;
			copy.extend_left(delta);
			return copy;
		}

		template <typename U>
		constexpr void extend_right(U delta)
		{
			this->dimension += ql::vector2<T>(delta, T{0});
		}

		template <typename U>
		constexpr ql::hitbox_t<T> extended_right(U delta) const
		{
			auto copy = *this;
			copy.extend_right(delta);
			return copy;
		}

		template <typename U>
		constexpr void extend_up(U delta)
		{
			this->position -= ql::vector2<T>(T{0}, delta);
			this->dimension += ql::vector2<T>(T{0}, delta);
		}

		template <typename U>
		constexpr ql::hitbox_t<T> extended_up(U delta) const
		{
			auto copy = *this;
			copy.extend_up(delta);
			return copy;
		}

		template <typename U>
		constexpr void extend_down(U delta)
		{
			this->dimension += ql::vector2<T>(T{0}, delta);
		}

		template <typename U>
		constexpr ql::hitbox_t<T> extended_down(U delta) const
		{
			auto copy = *this;
			copy.extend_down(delta);
			return copy;
		}

		constexpr ql::vector2<T> get_top_left() const
		{
			return this->get_side(ql::box_side::top_left);
		}

		constexpr ql::vector2<T> get_top_center() const
		{
			return this->get_side(ql::box_side::top_center);
		}

		constexpr ql::vector2<T> get_top_right() const
		{
			return this->get_side(ql::box_side::top_right);
		}

		constexpr ql::vector2<T> get_right_top() const
		{
			return this->get_side(ql::box_side::right_top);
		}

		constexpr ql::vector2<T> get_right_center() const
		{
			return this->get_side(ql::box_side::right_center);
		}

		constexpr ql::vector2<T> get_right_bottom() const
		{
			return this->get_side(ql::box_side::right_bottom);
		}

		constexpr ql::vector2<T> get_bottom_left() const
		{
			return this->get_side(ql::box_side::bottom_left);
		}

		constexpr ql::vector2<T> get_bottom_center() const
		{
			return this->get_side(ql::box_side::bottom_center);
		}

		constexpr ql::vector2<T> get_bottom_right() const
		{
			return this->get_side(ql::box_side::bottom_right);
		}

		constexpr ql::vector2<T> get_left_top() const
		{
			return this->get_side(ql::box_side::left_top);
		}

		constexpr ql::vector2<T> get_left_center() const
		{
			return this->get_side(ql::box_side::left_center);
		}

		constexpr ql::vector2<T> get_left_bottom() const
		{
			return this->get_side(ql::box_side::left_bottom);
		}

		constexpr void set_top_left(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::top_left, position);
		}

		constexpr void set_top_center(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::top_center, position);
		}

		constexpr void set_top_right(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::top_right, position);
		}

		constexpr void set_right_top(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::right_top, position);
		}

		constexpr void set_right_center(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::right_center, position);
		}

		constexpr void set_right_bottom(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::right_bottom, position);
		}

		constexpr void set_bottom_left(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::bottom_left, position);
		}

		constexpr void set_bottom_center(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::bottom_center, position);
		}

		constexpr void set_bottom_right(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::bottom_right, position);
		}

		constexpr void set_left_top(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::left_top, position);
		}

		constexpr void set_left_center(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::left_center, position);
		}

		constexpr void set_left_bottom(ql::vector2<T> position)
		{
			this->set_side(ql::box_side::left_bottom, position);
		}

		// 4 side corners
		constexpr ql::vector2<T> get_side_corner_left(ql::size side) const
		{
			switch(side)
			{
				case 0u: return this->get_side(ql::box_side::top_left);
				case 1u: return this->get_side(ql::box_side::right_top);
				case 2u: return this->get_side(ql::box_side::bottom_left);
				case 3u: return this->get_side(ql::box_side::left_top);
			}
			return {};
		}

		// 4 side corners
		constexpr void set_side_corner_left(ql::size side, ql::vector2<T> position)
		{
			switch(side)
			{
				case 0u: this->set_side(ql::box_side::top_left, position); break;
				case 1u: this->set_side(ql::box_side::right_top, position); break;
				case 2u: this->set_side(ql::box_side::bottom_left, position); break;
				case 3u: this->set_side(ql::box_side::left_top, position); break;
			}
		}

		// 4 side corners
		constexpr void set_side_corner(ql::size side, ql::vector2<T> position)
		{
			this->set_side(side * 2, position);
		}

		// 4 side corners
		constexpr ql::vector2<T> get_side_corner(ql::size side) const
		{
			return this->get_side(side * 2);
		}

		// 4 side centers
		constexpr void set_side_center(ql::size side, ql::vector2<T> position)
		{
			this->set_side_center(side * 2 + 1, position);
		}

		// 8 sides
		constexpr ql::vector2<T> get_side(ql::size side) const
		{
			return this->position + ql::vec_box8.at(side) * this->dimension;
		}

		// 8 sides
		constexpr void set_side(ql::size side, ql::vector2<T> position)
		{
			this->set_position(position - ql::vec_box8.at(side) * this->dimension);
		}

		constexpr ql::vector2<T> get_side(ql::box_side side) const
		{
			return this->get_side(ql::size_cast(side));
		}

		constexpr void set_side(ql::box_side side, ql::vector2<T> position)
		{
			this->set_side(ql::size_cast(side), position);
		}

		template <typename U>
		bool collides(T x1, T x2, T y1, T y2, ql::straight_line_t<U> line) const
		{
			auto x_a_inside = (line.a.x > x1) && (line.a.x < x2);
			auto y_a_inside = (line.a.y > y1) && (line.a.y < y2);
			if(x_a_inside && y_a_inside)
				return true;

			auto x_b_inside = (line.b.x > x1) && (line.b.x < x2);
			auto y_b_inside = (line.b.y > y1) && (line.b.y < y2);
			if(x_b_inside && y_b_inside)
				return true;

			auto x_cross = ((line.a.x < x1) && (line.b.x > x2)) || ((line.b.x < x1) && (line.a.x > x2));
			if(x_cross && (y_a_inside && y_b_inside))
				return true;

			auto y_cross = ((line.a.y < y1) && (line.b.y > y2)) || ((line.b.y < y1) && (line.a.y > y2));
			if(y_cross && (x_a_inside && x_b_inside))
				return true;

			if(line.a.x < x1 && line.b.x < x1)
				return false;
			if(line.a.x > x2 && line.b.x > x2)
				return false;
			if(line.a.y < y1 && line.b.y < y1)
				return false;
			if(line.a.y > y2 && line.b.y > y2)
				return false;

			auto c1 = ql::vec(x1, y1);
			auto c2 = ql::vec(x2, y1);
			auto c3 = ql::vec(x1, y2);
			auto c4 = ql::vec(x2, y2);

			ql::straight_line line1(line.a, {});
			ql::straight_line line2(line.a, {});
			bool found = false;

			if(line.a.x < c1.x && line.a.y < c1.y)
			{	 // a_outside_c1
				line1.b = c3;
				line2.b = c2;
				found = true;
			}
			else if(line.a.x > c2.x && line.a.y < c2.y)
			{	 // a_outside_c2
				line1.b = c1;
				line2.b = c4;
				found = true;
			}
			else if(line.a.x < c3.x && line.a.y > c3.y)
			{	 // a_outside_c3
				line1.b = c4;
				line2.b = c1;
				found = true;
			}
			else if(line.a.x > c4.x && line.a.y > c4.y)
			{	 // a_outside_c3
				line1.b = c2;
				line2.b = c3;
				found = true;
			}
			else if(line.a.x < c1.x)
			{	 // a_left
				line1.b = c3;
				line2.b = c1;
				found = true;
			}
			else if(line.a.y < c1.y)
			{	 // a_top
				line1.b = c1;
				line2.b = c2;
				found = true;
			}
			else if(line.a.x > c2.x)
			{	 // a_right
				line1.b = c2;
				line2.b = c4;
				found = true;
			}
			else if(line.a.y > c2.y)
			{	 // a_bottom
				line1.b = c4;
				line2.b = c3;
				found = true;
			}

			if(!found)
			{
				return false;
			}
			auto line_angle = line.angle();

			auto angle1 = line1.angle();
			auto angle2 = line2.angle();

			if(angle2 < angle1)
			{
				if(line_angle < ql::pi_32)
				{
					angle1 -= ql::pi_32 * 2;
				}
				else
				{
					angle2 += ql::pi_32 * 2;
				}
			}

			return (line_angle >= angle1 && line_angle <= angle2);
		}
	};

	using hitbox = hitbox_t<ql::f32>;

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const ql::hitbox_t<T>& hitbox)
	{
		return os << hitbox.string();
	}
}	 // namespace ql

namespace std
{
	template <class T, ql::size N>
	struct std::hash<std::array<T, N>>
	{
		ql::u64 operator()(const std::array<T, N>& key) const
		{
			std::hash<T> hash;
			ql::u64 result = 9613230923329544087ull;
			for(ql::size i = 0u; i < N; ++i)
			{
				result = ql::rotate_right(result, 1) ^ hash(key[i]);
			}
			return result;
		}
	};

	template <typename T, ql::size N>
	struct hash<ql::vectorN<T, N>>
	{
		ql::u64 operator()(const ql::vectorN<T, N>& k) const
		{
			std::hash<std::array<T, N>> hash;
			return hash(k.data);
		}
	};

	template <typename T, ql::size N>
	struct hash<ql::matrixN<T, N>>
	{
		ql::u64 operator()(const ql::matrixN<T, N>& k) const
		{
			std::hash<std::array<T, N>> hash;
			return hash(k.data);
		}
	};
}	 // namespace std

#endif