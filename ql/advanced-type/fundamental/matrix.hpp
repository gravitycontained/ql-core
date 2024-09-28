#pragma once

#include <ql/definition/definition.hpp>
#include <ql/advanced-type/fundamental/vector.hpp>
#include <ql/type/type.hpp>

namespace ql
{

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
		requires (sizeof...(Args) > 1)
		constexpr matrixN(Args&&... other) : data()
		{
			auto tuple = std::make_tuple(other...);
			*this = tuple;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		constexpr matrixN(U value) : data()
		{
			*this = value;
		}

		template <typename Tuple>
		requires (ql::is_tuple<Tuple>())
		constexpr matrixN(const Tuple& tuple) : data()
		{
			*this = tuple;
		}

		template <typename U>
		constexpr matrixN& operator=(const std::initializer_list<std::initializer_list<U>>& list)
		{
			if (list.size() == 0)
			{
				this->clear();
				return *this;
			}
			for (ql::u32 i = 0u; i < ql::min(list.size(), this->data.size()); ++i)
			{
				this->data[i] = *(list.begin() + i);
			}
			return *this;
		}

		template <typename T>
		requires (ql::is_tuple<T>())
		constexpr matrixN& operator=(const T& tuple)
		{
			constexpr auto size = ql::tuple_size<T>();
			ql::constexpr_iterate<size>([&](auto i) { this->data[i] = ql::tuple_value<i>(tuple); });
			return *this;
		}

		template <typename U, ql::size M>
		constexpr matrixN& operator=(const matrixN<U, M>& other)
		{
			for (ql::size i = 0u; i < ql::min(N, M); ++i)
			{
				for (ql::size j = 0u; j < ql::min(N, M); ++j)
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
		requires (ql::is_arithmetic<U>())
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
			for (ql::size i = 0u; i < ql::min(N, M); ++i)
			{
				for (ql::size j = 0u; j < ql::min(N, M); ++j)
				{
					this->data[i][j] += other[i][j];
				}
			}
			return *this;
		}

		constexpr matrixN& operator+=(const matrixN& other)
		{
			for (ql::size i = 0u; i < N; ++i)
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
			for (ql::size i = 0u; i < ql::min(N, M); ++i)
			{
				for (ql::size j = 0u; j < ql::min(N, M); ++j)
				{
					this->data[i][j] -= other[i][j];
				}
			}
			return *this;
		}

		constexpr matrixN& operator-=(const matrixN& other)
		{
			for (ql::size i = 0u; i < N; ++i)
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

			for (ql::size i = 0u; i < N; ++i)
			{
				vec sum;
				for (ql::size j = 0u; j < N; ++j)
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
			for (ql::size i = 0u; i < N; ++i)
			{
				for (ql::size j = 0u; j < N; ++j)
				{
					result.data[i] += this->data[j][i] * vec.data[j];
				}
			}
			return result;
		}

		template <typename U, ql::size M>
		constexpr matrixN& operator/=(const matrixN<U, M>& other)
		{
			for (ql::size i = 0u; i < ql::min(N, M); ++i)
			{
				for (ql::size j = 0u; j < ql::min(N, M); ++j)
				{
					this->data[i][j] /= other[i][j];
				}
			}
			return *this;
		}

		constexpr matrixN& operator/=(const matrixN& other)
		{
			for (ql::size i = 0u; i < N; ++i)
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
			for (auto& i : copy)
			{
				i = -i;
			}
			return copy;
		}

		constexpr matrixN operator+() const
		{
			auto copy = *this;
			for (auto& i : copy)
			{
				i = +i;
			}
			return copy;
		}

		constexpr bool operator==(const matrixN& other) const
		{
			for (ql::size i = 0u; i < N; ++i)
			{
				if (this->data[i] != other[i])
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
		requires (ql::is_arithmetic<U>())
		constexpr void fill(U value)
		{
			for (auto& i : this->data)
			{
				i.fill(static_cast<T>(value));
			}
		}

		template <typename A, typename U>
		requires (N == 4)
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
		requires (N == 4)
		constexpr matrixN& rotate(A angle, const ql::vector3<U>& vec)
		{
			*this = this->rotated(angle, vec);
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static matrixN<T, N> filled(U value)
		{
			matrixN<T, N> result;

			for (auto& v : result)
			{
				v = vec::filled(value);
			}

			return result;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static matrixN<T, N> filled_front(U value)
		{
			matrixN<T, N> result;

			for (auto& v : result)
			{
				v = vec(value);
			}

			return result;
		}

		template <typename U>
		requires (ql::is_arithmetic<U>())
		[[nodiscard]] constexpr static matrixN<T, N> filled_diagonally(U value)
		{
			matrixN<T, N> result;

			for (ql::size i = 0u; i < N; ++i)
			{
				result.data[i][i] = static_cast<T>(value);
			}
			return result;
		}

		template <typename A>
		requires (N == 4)
		[[nodiscard]] constexpr static matrixN rotate(const matrixN& matrix, A angle, const ql::vector3<T>& vec)
		{
			return matrix.rotated(angle, vec);
		}

		template <typename A, typename U>
		requires (N == 4)
		[[nodiscard]] constexpr static matrixN rotate(const matrixN& matrix, A angle, const ql::vector3<U>& vec)
		{
			return matrix.rotated(angle, vec);
		}

		template <typename U>
		requires (N == 4)
		[[nodiscard]] constexpr static matrixN translate(const matrixN& matrix, const ql::vector3<U>& vec)
		{
			matrixN result(matrix);
			result[3] = matrix[0] * vec.x + matrix[1] * vec.y + matrix[2] * vec.z + matrix[3];
			return result;
		}

		template <typename U, typename V, typename W>
		requires (N == 4)
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
		requires (N == 4)
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
		requires (N == 4)
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
			for (ql::size i = 0u; i < N; ++i)
			{
				for (ql::size j = 0u; j < N; ++j)
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
			for (ql::size i = 0u; i < N; ++i)
			{
				for (ql::size j = 0u; j < N; ++j)
				{
					this->data[i][j] = static_cast<T>(mat[static_cast<length_type>(i)][static_cast<length_type>(j)]);
				}
			}
		}
#endif

		constexpr void clear()
		{
			for (auto& i : this->data)
			{
				i.clear();
			}
		}

		std::string to_string() const
		{
			return ql::to_string(this->data);
		}
	};

	
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

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator+(U value, const matrixN<T, N>& mat)
	{
		return matrixN<T, N>::filled(value) + mat;
	}

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator-(U value, const matrixN<T, N>& mat)
	{
		return matrixN<T, N>::filled(value) - mat;
	}

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator*(U value, const matrixN<T, N>& mat)
	{
		return matrixN<T, N>::filled(value) * mat;
	}

	template <typename T, typename U, ql::size N>
	requires (ql::is_arithmetic<U>())
	constexpr auto operator/(U value, const matrixN<T, N>& mat)
	{
		return matrixN<T, N>::filled(value) / mat;
	}

}

namespace std
{
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