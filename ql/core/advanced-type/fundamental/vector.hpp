#pragma once

#include <ql/core/constexpr/constexpr.hpp>

#include <ql/core/definition/definition.hpp>

#include <ql/core/transform/bit/bit.hpp>

#include <ql/core/string/to-string.hpp>

#include <ql/core/type/tuple/value.hpp>
#include <ql/core/type/tuple/is-tuple.hpp>

#include <ql/core/transform/cast/cast.hpp>
#include <ql/core/transform/limit.hpp>
#include <ql/core/transform/possibilities.hpp>

#include <iomanip>
#include <numeric>

#if defined QL_INTERN_SFML_USE
#include <SFML/Graphics.hpp>
#endif

#if defined QL_INTERN_GLM_USE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#endif

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
			requires (ql::is_arithmetic<U>())
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
			requires (ql::is_arithmetic<U>())
			constexpr V with_x(U x) const
			{
				return V{static_cast<T>(x), this->y};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
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
			requires (ql::is_arithmetic<U>())
			constexpr V with_x(U x) const
			{
				return V{static_cast<T>(x), this->y, this->z};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_y(U y) const
			{
				return V{this->x, static_cast<T>(y), this->z};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
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
			requires (ql::is_arithmetic<U>())
			constexpr V with_x(U x) const
			{
				return V{static_cast<T>(x), this->y, this->z, this->w};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_y(U y) const
			{
				return V{this->x, static_cast<T>(y), this->z, this->w};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_z(U z) const
			{
				return V{this->x, this->y, static_cast<T>(z), this->w};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
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
			requires (ql::is_arithmetic<U>())
			constexpr V with_a(U a) const
			{
				return V{static_cast<T>(a), this->b, this->c, this->d, this->e};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_b(U b) const
			{
				return V{this->a, static_cast<T>(b), this->c, this->d, this->e};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_c(U c) const
			{
				return V{this->a, this->b, static_cast<T>(c), this->d, this->e};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_d(U d) const
			{
				return V{this->a, this->b, this->c, static_cast<T>(d), this->e};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
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
			requires (ql::is_arithmetic<U>())
			constexpr V with_a(U a) const
			{
				return V{static_cast<T>(a), this->b, this->c, this->d, this->e, this->f};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_b(U b) const
			{
				return V{this->a, static_cast<T>(b), this->c, this->d, this->e, this->f};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_c(U c) const
			{
				return V{this->a, this->b, static_cast<T>(c), this->d, this->e, this->f};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_d(U d) const
			{
				return V{this->a, this->b, this->c, static_cast<T>(d), this->e, this->f};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
			constexpr V with_e(U e) const
			{
				return V{this->a, this->b, this->c, this->d, static_cast<T>(e), this->f};
			}

			template <typename U>
			requires (ql::is_arithmetic<U>())
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
		requires (!ql::is_vectorN<U>())
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
		requires (sizeof...(Args) > 1)
		constexpr vectorN(Args&&... list) : impl_type()
		{
			*this = ql::tuple_to_array(std::make_tuple(std::forward<Args>(list)...));
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr vectorN(U value) : impl_type()
		{
			*this = value;
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
			if constexpr (N == 1)
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
			if constexpr (N == 1)
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
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] = static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U, ql::size M>
		constexpr vectorN& operator=(const vectorN<U, M>& other)
		{
			for (ql::u32 i = 0u; i < ql::min(N, M); ++i)
			{
				this->data[i] = static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <ql::size N, typename U>
		constexpr vectorN& operator=(const std::array<U, N>& array)
		{
			if (array.empty())
			{
				this->clear();
				return *this;
			}
			for (ql::u32 i = 0u; i < ql::min(array.size(), this->data.size()); ++i)
			{
				this->data[i] = static_cast<T>(array[i]);
			}
			return *this;
		}

		template <typename U>
		requires (!ql::is_vectorN<U>())
		constexpr vectorN& operator=(const std::initializer_list<U>& list)
		{
			if (list.size() == 0)
			{
				this->clear();
				return *this;
			}
			for (ql::size i = 0u; i < ql::min(list.size(), this->data.size()); ++i)
			{
				this->data[i] = static_cast<T>(*(list.begin() + i));
			}
			return *this;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr vectorN& operator=(U value)
		{
			this->data[0u] = value;
			for (ql::size i = 1u; i < N; ++i)
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
			for (auto& i : result.data)
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
			for (auto& i : result.data)
			{
				i = std::floor(i);
			}
			return result;
		}

		constexpr vectorN ceil() const
		{
			vectorN result = *this;
			for (auto& i : result.data)
			{
				i = std::ceil(i);
			}
			return result;
		}

		constexpr vectorN round() const
		{
			vectorN result = *this;
			for (auto& i : result.data)
			{
				i = std::round(i);
			}
			return result;
		}

		constexpr void clear()
		{
			for (auto& i : this->data)
			{
				i = T{};
			}
		}

		constexpr bool empty() const
		{
			for (auto& i : this->data)
			{
				if (i != T{})
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
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if (this->data[i] < static_cast<T>(other.data[i]))
				{
					return true;
				}
				if (this->data[i] > static_cast<T>(other.data[i]))
				{
					return false;
				}
			}
			return false;
		}

		constexpr bool operator<=(const vectorN& other) const
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if (this->data[i] < static_cast<T>(other.data[i]))
				{
					return true;
				}
				if (this->data[i] > static_cast<T>(other.data[i]))
				{
					return false;
				}
			}
			return true;
		}

		constexpr bool operator>(const vectorN& other) const
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if (this->data[i] > static_cast<T>(other.data[i]))
				{
					return true;
				}
				if (this->data[i] < static_cast<T>(other.data[i]))
				{
					return false;
				}
			}
			return false;
		}

		constexpr bool operator>=(const vectorN& other) const
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if (this->data[i] > static_cast<T>(other.data[i]))
				{
					return true;
				}
				if (this->data[i] < static_cast<T>(other.data[i]))
				{
					return false;
				}
			}
			return true;
		}

		template <typename U>
		constexpr bool operator==(const vectorN<U, N>& other) const
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if (this->data[i] != static_cast<T>(other.data[i]))
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
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] += static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator+=(const std::array<U, N>& other)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
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
		requires (ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator+=(U u)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] += static_cast<T>(u);
			}
			return *this;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
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
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] -= static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator-=(const std::array<U, N>& other)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
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
		requires (ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator-=(U u)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
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
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] *= static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator*=(const std::array<U, N>& other)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
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
		requires (ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator*=(U u)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] *= static_cast<T>(u);
			}
			return *this;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
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
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] /= static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator/=(const std::array<U, N>& other)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
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
		requires (ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator/=(U u)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] /= static_cast<T>(u);
			}
			return *this;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
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
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				this->data[i] %= static_cast<T>(other.data[i]);
			}
			return *this;
		}

		template <typename U>
		constexpr vectorN<T, N>& operator%=(const std::array<U, N>& other)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
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
		requires (ql::is_arithmetic<U>())
		constexpr vectorN<T, N>& operator%=(U u)
		{
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				if constexpr (ql::is_floating_point<T>())
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
		requires (ql::is_arithmetic<U>())
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
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				copy.data[i] = -this->data[i];
			}
			return copy;
		}

		constexpr vectorN operator+() const
		{
			vectorN copy;
			for (ql::u32 i = 0u; i < this->data.size(); ++i)
			{
				copy.data[i] = +this->impl_type::data[i];
			}
			return copy;
		}

		constexpr auto reversed() const
		{
			vectorN copy;
			for (ql::size i = 0u; i < this->size(); ++i)
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
			if (std::is_constant_evaluated())
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
			if (this->length() == 0)
				return vectorN{};

			return *this / this->length();
		}

		constexpr auto angle() const
		requires (N == 2)
		{
			auto atan = ql::f64_cast(std::atan2(ql::f64_cast(this->y), -ql::f64_cast(this->x)));
			if (atan < 0)
				atan = 2 * ql::pi + atan;
			return atan;
		}

		constexpr void set_rotation(ql::f64 angle)
		requires (N == 2)
		{
			auto x = std::cos(angle);
			auto y = std::sin(angle);
			*this = vectorN(x, y) * this->length();
		}

		constexpr void set_rotation_around(vectorN center, ql::f64 angle)
		requires (N == 2)
		{
			auto x = std::cos(angle);
			auto y = std::sin(angle);
			auto diff = *this - center;
			*this = center + vectorN(x, y) * diff.length();
		}

		constexpr void rotate(ql::f64 delta_angle)
		requires (N == 2)
		{
			this->set_rotation(-this->angle() + delta_angle);
		}

		constexpr void rotate_around(vectorN center, ql::f64 delta_angle)
		requires (N == 2)
		{
			auto diff = *this - center;
			auto angle = diff.angle() + delta_angle;

			auto x = std::cos(angle);
			auto y = std::sin(angle);
			*this = center + vectorN(x, y) * diff.length();
		}

		constexpr auto rotated(ql::f64 delta_angle) const
		requires (N == 2)
		{
			auto copy = *this;
			copy.rotate(delta_angle);
			return copy;
		}

		constexpr auto rotated_around(vectorN center, ql::f64 delta_angle) const
		requires (N == 2)
		{
			auto copy = *this;
			copy.rotate_around(center, delta_angle);
			return copy;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr auto dot(const vectorN<U, N>& other) const
		{
			auto n = ql::superior_arithmetic_type<T, U>{0};
			for (ql::size i = 0u; i < N; ++i)
			{
				n += this->data[i] * other.data[i];
			}
			return n;
		}

		constexpr auto dot(const vectorN& other) const
		{
			auto n = T{0};
			for (ql::size i = 0u; i < N; ++i)
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
			for (auto& i : result)
			{
				i = std::abs(i);
			}
			return result;
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto sin(const vectorN<T, N>& vec)
		{
			ql::vectorN<T, N> result = vec;
			for (auto& i : result)
			{
				i = std::sin(i);
			}
			return result;
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto cos(const vectorN<T, N>& vec)
		{
			ql::vectorN<T, N> result = vec;
			for (auto& i : result)
			{
				i = std::cos(i);
			}
			return result;
		}

		template <typename T, ql::size N>
		[[nodiscard]] constexpr static auto tan(const vectorN<T, N>& vec)
		{
			ql::vectorN<T, N> result = vec;
			for (auto& i : result)
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
			for (ql::size i = 0u; i < a.size(); ++i)
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
			for (ql::size i = 0u; i < a.size(); ++i)
			{
				result[i] = std::min(static_cast<R>(a[i]), static_cast<R>(b[i]));
			}
			return result;
		}

		constexpr void clamp(T min, T max)
		{
			for (auto& i : this->data)
			{
				i = ql::clamp(i, min, max);
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
			for (ql::size i = 0u; i < this->size(); ++i)
			{
				this->data[i] = ql::clamp(this->data[i], T{0}, max[i]);
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
			for (ql::size i = 0u; i < this->size(); ++i)
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
			for (ql::size i = 0u; i < N; ++i)
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
		requires (N == 3)
		[[nodiscard]] constexpr static auto cross(const vectorN<T, N>& a, const vectorN<U, N>& b)
		{
			ql::vectorN<ql::superior_arithmetic_type<T, U>, N> result;
			result.x = a.y * b.z - b.y * a.z;
			result.y = a.z * b.x - b.z * a.x;
			result.z = a.x * b.y - b.x * a.y;
			return result;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static vectorN<T, N> filled(U value)
		{
			vectorN<T, N> result;
			result.data.fill(static_cast<T>(value));
			return result;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr void fill(U value)
		{
			this->data.fill(static_cast<T>(value));
		}

		constexpr std::string to_string() const
		{
			std::ostringstream stream;
			stream << '(';
			bool first = true;
			for (auto& i : this->data)
			{
				if (!first)
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
			for (auto& i : this->data)
			{
				if (!first)
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
	requires (ql::is_arithmetic<U>())
	constexpr auto operator+(U value, const vectorN<T, N>& vec)
	{
		return vectorN<T, N>::filled(value) + vec;
	}

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator-(U value, const vectorN<T, N>& vec)
	{
		return vectorN<T, N>::filled(value) - vec;
	}

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator*(U value, const vectorN<T, N>& vec)
	{
		return vectorN<T, N>::filled(value) * vec;
	}

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator/(U value, const vectorN<T, N>& vec)
	{
		return vectorN<T, N>::filled(value) / vec;
	}

	template <typename T, ql::size N>
	std::ostream& operator<<(std::ostream& os, const ql::vectorN<T, N>& vec)
	{
		return os << vec.to_string();
	}

	template <typename T>
	requires (ql::is_vectorN<T>())
	constexpr auto list_possibilities(T value)
	{
		return ql::list_possibilities(value.data);
	}

	template <typename T>
	requires (ql::is_vectorN<T>())
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
	requires (ql::is_arithmetic<Args>() && ...)
	constexpr auto vec(Args... rest)
	{
		using R = ql::superior_arithmetic_type<Args...>;
		return ql::vectorN<R, sizeof...(Args)>(rest...);
	}

	template <typename... Args>
	requires (ql::is_arithmetic<Args>() && ...)
	constexpr auto tex(Args... rest)
	{
		using R = ql::superior_arithmetic_type<Args...>;
		return texN<R, sizeof...(Args)>(ql::vectorN<R, sizeof...(Args)>(rest...));
	}

	namespace detail
	{
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
		requires (N == check)
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

	constexpr auto vec_square4 = std::array{ql::vec(0, 0), ql::vec(1, 0), ql::vec(1, 1), ql::vec(0, 1)};
	constexpr auto vec_diagonals4 = std::array{std::array{ql::vec(-1, -1), ql::vec(1, -1), ql::vec(1, 1), ql::vec(-1, 1)}};
	constexpr auto vec_cross4 = std::array{ql::vec(1, 0), ql::vec(0, 1), ql::vec(-1, 0), ql::vec(0, -1)};
	constexpr auto vec_cross9 = std::array{ql::vec(-1, 0),	ql::vec(1, 0),	ql::vec(0, -1), ql::vec(0, 1),
																				 ql::vec(-1, -1), ql::vec(1, -1), ql::vec(1, 1),	ql::vec(-1, 1)};
	constexpr auto vec_box8 = std::array{ql::vec(0.0, 0.0), ql::vec(0.5, 0.0), ql::vec(1.0, 0.0), ql::vec(1.0, 0.5),
																			 ql::vec(1.0, 1.0), ql::vec(0.5, 1.0), ql::vec(0.0, 1.0), ql::vec(0.0, 0.5)};

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
			for (ql::size i = 0u; i < N; ++i)
			{
				result = ql::bit_rotate_right(result, 1) ^ hash(key[i]);
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
}	 // namespace std