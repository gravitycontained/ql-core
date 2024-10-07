#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>
#include <ql/core/type/transform/tuple-to-array.hpp>

#include <array>

namespace ql
{
	namespace detail
	{
		template <typename T, ql::size N>
		struct possibilities_iterator
		{
			std::array<T, N> values;
			std::array<T, N> min;
			std::array<T, N> max;

			constexpr possibilities_iterator(const std::array<T, N>& max) : min(), values(), max()
			{
				this->values.fill(T{});
				this->max = max;
			}

			constexpr possibilities_iterator(const std::array<T, N>& min, const std::array<T, N>& max) : min(), values(), max()
			{
				this->values = min;
				this->min = min;
				this->max = max;
			}

			constexpr possibilities_iterator() : min(), values(), max()
			{
				this->values.fill(T{});
				this->min.fill(T{});
				this->max.fill(T{});
			}

			constexpr bool operator==(const possibilities_iterator& other)
			{
				return this->values == other.values;
			}

			constexpr bool operator!=(const possibilities_iterator& other)
			{
				return this->values != other.values;
			}

			constexpr void set_end()
			{
				for (auto& i : this->values)
				{
					i = ql::type_max<T>();
				}
			}

			constexpr possibilities_iterator& operator++(int)
			{
				bool ended = false;
				for (ql::u32 i = 0u; i < this->values.size(); ++i)
				{
					++this->values[i];
					if (this->values[i] == this->max[i])
					{
						this->values[i] = this->min[i];
					}
					else
					{
						ended = true;
						break;
					}
				}
				if (!ended)
				{
					this->set_end();
				}
				return *this;
			}

			constexpr possibilities_iterator operator++()
			{
				auto copy = *this;
				this->operator++(0);
				return copy;
			}

			constexpr auto operator*() const
			{
				return ql::array_to_tuple(this->values);
			}
		};

		template <typename T, ql::size N>
		struct possibilities_reverse_iterator
		{
			std::array<T, N> values;
			std::array<T, N> min;
			std::array<T, N> max;

			constexpr possibilities_reverse_iterator(const std::array<T, N>& max) : min(), values(), max()
			{
				this->values = max;
				for (auto& i : this->values)
				{
					--i;
				}
				this->min.fill(T{});
				this->max = max;
			}

			constexpr possibilities_reverse_iterator() : min(), values(), max()
			{
				this->values.fill(T{});
				this->max.fill(T{});
			}

			constexpr bool operator==(const possibilities_reverse_iterator& other)
			{
				return this->values == other.values;
			}

			constexpr bool operator!=(const possibilities_reverse_iterator& other)
			{
				return this->values != other.values;
			}

			constexpr void set_end()
			{
				for (auto& i : this->values)
				{
					i = ql::type_max<T>();
				}
			}

			constexpr possibilities_reverse_iterator& operator++(int)
			{
				bool ended = false;
				for (ql::u32 i = 0u; i < this->values.size(); ++i)
				{
					auto index = this->values.size() - i - 1;
					if (this->values[index] == this->min[i])
					{
						this->values[index] = this->max[index] - 1;
					}
					else
					{
						--this->values[index];
						ended = true;
						break;
					}
				}
				if (!ended)
				{
					this->set_end();
				}
				return *this;
			}

			constexpr possibilities_reverse_iterator operator++()
			{
				auto copy = *this;
				this->operator++(0);
				return copy;
			}

			constexpr auto operator*() const
			{
				return ql::array_to_tuple(this->values);
			}
		};

		template <typename T, ql::size N>
		struct possibilities
		{
			std::array<T, N> min;
			std::array<T, N> max;

			constexpr possibilities(const std::array<T, N>& max) : min(), max()
			{
				this->max = max;
			}

			constexpr possibilities(const std::array<T, N>& min, const std::array<T, N>& max) : min(), max()
			{
				this->min = min;
				this->max = max;
			}

			constexpr possibilities_iterator<T, N> cbegin() const
			{
				possibilities_iterator<T, N> it(this->min, this->max);
				return it;
			}

			constexpr possibilities_iterator<T, N> begin() const
			{
				return this->cbegin();
			}

			constexpr possibilities_iterator<T, N> cend() const
			{
				possibilities_iterator<T, N> it;
				it.set_end();
				return it;
			}

			constexpr possibilities_iterator<T, N> end() const
			{
				return this->cend();
			}

			constexpr possibilities_reverse_iterator<T, N> crbegin() const
			{
				possibilities_reverse_iterator<T, N> it(this->min, this->max);
				return it;
			}

			constexpr possibilities_reverse_iterator<T, N> rbegin() const
			{
				return this->crbegin();
			}

			constexpr possibilities_reverse_iterator<T, N> crend() const
			{
				possibilities_reverse_iterator<T, N> it;
				it.set_end();
				return it;
			}

			constexpr possibilities_reverse_iterator<T, N> rend() const
			{
				return this->crend();
			}
		};

		template <typename T, ql::size N>
		struct reverse_possibilities
		{
			std::array<T, N> min;
			std::array<T, N> max;

			constexpr reverse_possibilities(const std::array<T, N>& max) : min(), max()
			{
				this->max = max;
			}

			constexpr reverse_possibilities(const std::array<T, N>& min, const std::array<T, N>& max) : min(), max()
			{
				this->min = min;
				this->max = max;
			}

			constexpr possibilities_reverse_iterator<T, N> cbegin() const
			{
				possibilities_reverse_iterator<T, N> it(this->min, this->max);
				return it;
			}

			constexpr possibilities_reverse_iterator<T, N> begin() const
			{
				return this->cbegin();
			}

			constexpr possibilities_reverse_iterator<T, N> cend() const
			{
				possibilities_reverse_iterator<T, N> it;
				it.set_end();
				return it;
			}

			constexpr possibilities_reverse_iterator<T, N> end() const
			{
				return this->cend();
			}

			constexpr possibilities_iterator<T, N> crbegin() const
			{
				possibilities_iterator<T, N> it(this->min, this->max);
				return it;
			}

			constexpr possibilities_iterator<T, N> rbegin() const
			{
				return this->crbegin();
			}

			constexpr possibilities_iterator<T, N> crend() const
			{
				possibilities_iterator<T, N> it;
				it.set_end();
				return it;
			}

			constexpr possibilities_iterator<T, N> rend() const
			{
				return this->crend();
			}
		};
	}	 // namespace detail

	template <typename... Ts>
	requires (ql::variadic_size<Ts...>() > 1)
	constexpr auto list_possibilities(Ts... values)
	{
		return ql::detail::possibilities(ql::tuple_to_array(values...));
	}

	template <typename T, ql::size N>
	constexpr auto list_possibilities(const std::array<T, N>& start)
	{
		return ql::detail::possibilities(start);
	}

	template <typename T, ql::size N>
	constexpr auto list_possibilities(const std::array<T, N>& start, const std::array<T, N>& end)
	{
		return ql::detail::possibilities(start, end);
	}

	template <typename... Ts>
	constexpr auto list_reverse_possibilities(Ts... values)
	{
		return ql::detail::reverse_possibilities(ql::tuple_to_array(values...));
	}

	template <typename T, ql::size N>
	constexpr auto list_reverse_possibilities(const std::array<T, N>& start)
	{
		return ql::detail::reverse_possibilities(start);
	}

	template <typename T, ql::size N>
	constexpr auto list_reverse_possibilities(const std::array<T, N>& start, const std::array<T, N>& end)
	{
		return ql::detail::reverse_possibilities(start, end);
	}
}	 // namespace ql