#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename T, ql::size N = 0>
	struct circular_array
	{
		struct iterator
		{
			circular_array* data;
			ql::size index = 0u;

			iterator(circular_array& array, ql::size index) : data(&array), index(index)
			{
			}

			iterator& operator++()
			{
				++this->index;
				return *this;
			}

			iterator operator++(int dummy)
			{
				auto copy = *this;
				++this->index;
				return copy;
			}

			bool operator==(const iterator& other) const
			{
				return this->index == other.index;
			}

			bool operator!=(const iterator& other) const
			{
				return this->index != other.index;
			}

			T& operator*()
			{
				return this->data->get(this->index);
			}

			const T& operator*() const
			{
				return this->data->get(this->index);
			}
		};

		struct const_iterator
		{
			const circular_array* data;
			ql::size index = 0u;

			const_iterator(const circular_array& array, ql::size index) : data(&array), index(index)
			{
			}

			const_iterator& operator++()
			{
				++this->index;
				return *this;
			}

			const_iterator operator++(int dummy)
			{
				auto copy = *this;
				++this->index;
				return copy;
			}

			bool operator==(const const_iterator& other) const
			{
				return this->index == other.index;
			}

			bool operator!=(const const_iterator& other) const
			{
				return this->index != other.index;
			}

			const T& operator*() const
			{
				return this->data->get(this->index);
			}
		};

		circular_array()
		{
			this->index = 0u;
			this->rotation_finished = false;
			if constexpr (this->is_array() && ql::is_arithmetic<T>())
			{
				this->data.fill(0u);
			}
		}

		void clear()
		{
			if constexpr (is_array() && ql::is_arithmetic<T>())
			{
				this->data.fill(T{});
			}
			else
			{
				std::fill(this->data.begin(), this->data.end(), T{});
			}
			this->index = 0u;
			this->rotation_finished = false;
		}

		void reset()
		{
			this->index = 0u;
			this->rotation_finished = false;
		}

		void add(T value)
		{
			if (this->rotation_finished)
			{
				this->data[this->index] = std::move(value);
				++this->index;

				if (this->index == this->size())
				{
					this->index = 0u;
				}
			}
			else
			{
				this->data[this->index] = std::move(value);
				++this->index;

				if (this->index == this->size())
				{
					this->index = 0u;
					this->rotation_finished = true;
				}
			}
		}

		template <typename R = ql::conditional<ql::if_true<ql::is_floating_point<T>()>, T, ql::f64>>
		R get_average() const
		{
			R sum = 0;
			if (this->rotation_finished)
			{
				for (auto& i : this->data)
				{
					sum += i;
				}
				return sum / this->size();
			}
			else
			{
				for (ql::size i = 0u; i < this->index; ++i)
				{
					sum += this->data[i];
				}
				return sum / this->index;
			}
		}

		T get_min() const
		{
			T min = ql::type_max<T>();
			if (this->rotation_finished)
			{
				for (auto& i : this->data)
				{
					if (i < min)
					{
						min = i;
					}
				}
				return min;
			}
			else
			{
				for (ql::size i = 0u; i < this->index; ++i)
				{
					if (this->data[i] < min)
					{
						min = this->data[i];
					}
				}
				return min;
			}
		}

		T get_max() const
		{
			T max = ql::type_min<T>();
			if (this->rotation_finished)
			{
				for (auto& i : this->data)
				{
					if (i > max)
					{
						max = i;
					}
				}
				return max;
			}
			else
			{
				for (ql::size i = 0u; i < this->index; ++i)
				{
					if (this->data[i] > max)
					{
						max = this->data[i];
					}
				}
				return max;
			}
		}

		T get_sum() const
		{
			T sum = 0;
			if (this->rotation_finished)
			{
				for (auto& i : this->data)
				{
					sum += i;
				}
				return sum;
			}
			else
			{
				for (ql::size i = 0u; i < this->index; ++i)
				{
					sum += this->data[i];
				}
				return sum;
			}
		}

		T get_sum_of_last_n(ql::size last_n) const
		{
			if (last_n == this->size())
			{
				return this->get_sum();
			}
			T sum = 0;
			if (this->rotation_finished)
			{
				ql::size start = 0u;
				if (last_n > (this->index - 1))
				{
					start = this->size() - 1 - (last_n - (this->index - 1));
				}
				else
				{
					start = this->index - 1 - last_n;
				}
				for (ql::size i = 0u; i < last_n; ++i)
				{
					sum += this->data[(start + i) % this->size()];
				}
				return sum;
			}
			else
			{
				for (ql::size i = this->index - 1 - last_n; i < this->index; ++i)
				{
					sum += this->data[i];
				}
				return sum;
			}
		}

		std::pair<T, T> get_min_max() const
		{
			std::pair<T, T> min_max = std::make_pair(ql::type_max<T>(), ql::type_min<T>());
			if (this->rotation_finished)
			{
				for (auto& i : this->data)
				{
					if (i < min_max.first)
					{
						min_max.first = i;
					}
					if (i > min_max.second)
					{
						min_max.second = i;
					}
				}
				return min_max;
			}
			else
			{
				for (ql::size i = 0u; i < this->index; ++i)
				{
					if (this->data[i] < min_max.first)
					{
						min_max.first = this->data[i];
					}
					if (this->data[i] > min_max.second)
					{
						min_max.second = this->data[i];
					}
				}
				return min_max;
			}
		}

		void resize(ql::size size)
		{
			if constexpr (is_vector())
			{
				this->data.resize(size);
				std::fill(this->data.begin(), this->data.end(), T{});
				this->index = 0u;
				this->rotation_finished = false;
			}
		}

		constexpr static bool is_vector()
		{
			return N == ql::size{0u};
		}

		constexpr static bool is_array()
		{
			return N != ql::size{0};
		}

		T& get_actual(ql::size index)
		{
			return this->data[index];
		}

		const T& get_actual(ql::size index) const
		{
			return this->data[index];
		}

		T& get_previous(ql::size index)
		{
			return this->get(this->used_size() - index - 1);
		}

		const T& get_previous(ql::size index) const
		{
			return this->get(this->used_size() - index - 1);
		}

		T& get(ql::size index)
		{
			if (this->rotation_finished)
			{
				auto idx = (index + this->index) % this->used_size();
				return this->data[idx];
			}
			else
			{
				return this->data[index];
			}
		}

		const T& get(ql::size index) const
		{
			if (this->rotation_finished)
			{
				auto idx = (index + this->index) % this->used_size();
				return this->data[idx];
			}
			else
			{
				return this->data[index];
			}
		}

		T& operator[](ql::size index)
		{
			return this->get(index);
		}

		const T& operator[](ql::size index) const
		{
			return this->get(index);
		}

		auto begin()
		{
			return iterator(*this, 0u);
		}

		auto cbegin()
		{
			return const_iterator(*this, 0u);
		}

		auto end()
		{
			return iterator(*this, this->used_size());
		}

		auto cend()
		{
			return const_iterator(*this, this->used_size());
		}

		T& front()
		{
			if (this->rotation_finished)
			{
				return this->data[this->index];
			}
			else
			{
				return this->data[0u];
			}
		}

		const T& front() const
		{
			if (this->rotation_finished)
			{
				return this->data[this->index];
			}
			else
			{
				return this->data[0u];
			}
		}

		T& back()
		{
			auto index = this->index;
			if (index)
			{
				--index;
			}
			else
			{
				index = 0u;
			}
			return this->data[index];
		}

		const T& back() const
		{
			auto index = this->index;
			if (index)
			{
				--index;
			}
			else
			{
				index = 0u;
			}
			return this->data[index];
		}

		constexpr ql::size size() const
		{
			return this->data.size();
		}

		ql::size used_size() const
		{
			if (this->rotation_finished)
			{
				return this->size();
			}
			else
			{
				return this->index;
			}
		}

		bool empty() const
		{
			return this->used_size() == 0u;
		}

		ql::conditional<ql::if_true<N == 0>, std::vector<T>, std::array<T, N>> data;
		ql::size index = 0u;
		bool rotation_finished = false;
	};

}