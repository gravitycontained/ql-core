#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/advanced-type/container/array.hpp>

#include <ql/core/string/base/base.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{

	template <ql::u64 bits, bool BOUNDARY_CHECK = ql::detail::array_boundary_check>
	class bitset
	{
	 public:
		using uint_type = ql::conditional<ql::if_true<(bits <= 64u)>, ql::ubit<bits>, ql::default_type, ql::u64>;

		using holding_type = ql::conditional<
				ql::if_true<(bits <= 64u)>,
				ql::ubit<bits>,
				ql::default_type,
				ql::array<ql::u64, ql::approximate_multiple_up(bits, ql::u64{64}) / 64, BOUNDARY_CHECK>>;

		class bitset_range_proxy
		{
		 public:
			bitset_range_proxy(bitset& data, ql::u32 begin, ql::u32 end)
			{
				this->ptr = &data;
				this->begin = begin;
				this->end = end;
			}

			uint_type get() const
			{
				return this->ptr->get_range(this->begin, this->end);
			}

			operator bool() const
			{
				return this->get();
			}

			bitset_range_proxy operator=(uint_type value) const
			{
				this->ptr->set_range(this->begin, this->end, value);
				return *this;
			}

			bitset_range_proxy operator|=(uint_type value) const
			{
				this->ptr->set_range(this->begin, this->end, this->get() | value);
				return *this;
			}

			uint_type operator|(uint_type value) const
			{
				return this->get() | value;
			}

			bitset_range_proxy operator&=(uint_type value) const
			{
				this->ptr->set_range(this->begin, this->end, this->get() & value);
				return *this;
			}

			uint_type operator&(uint_type value) const
			{
				return this->get() & value;
			}

			bitset_range_proxy operator^=(uint_type value) const
			{
				this->ptr->set_range(this->begin, this->end, this->get() ^ value);
				return *this;
			}

			uint_type operator^(uint_type value) const
			{
				return this->get() ^ value;
			}

			bitset* ptr;
			ql::u32 begin;
			ql::u32 end;
		};

		class bitset_range_const_proxy
		{
		 public:
			bitset_range_const_proxy(const bitset& data, ql::u32 begin, ql::u32 end)
			{
				this->ptr = &data;
				this->begin = begin;
				this->end = end;
			}

			uint_type get() const
			{
				return this->ptr->get_range(this->begin, this->end);
			}

			operator bool() const
			{
				return this->get();
			}

			uint_type operator|(uint_type value) const
			{
				return this->get() | value;
			}

			uint_type operator&(uint_type value) const
			{
				return this->get() & value;
			}

			uint_type operator^(uint_type value) const
			{
				return this->get() ^ value;
			}

			const bitset* ptr;
			ql::u32 begin;
			ql::u32 end;
		};

		class bitset_proxy
		{
		 public:
			bitset_proxy(bitset& data, ql::size index)
			{
				this->ptr = &data;
				this->index = index;
			}

			bool get() const
			{
				return this->ptr->get(this->index);
			}

			operator bool() const
			{
				return this->get();
			}

			bitset_proxy operator=(bool value) const
			{
				this->ptr->set(this->index, value);
				return *this;
			}

			bitset_proxy operator|=(bool value) const
			{
				this->ptr->set(this->index, this->ptr->get(this->index) | value);
				return *this;
			}

			bool operator|(bool value) const
			{
				return this->ptr->get(this->index) || value;
			}

			bitset_proxy operator&=(bool value) const
			{
				this->ptr->set(this->index, this->ptr->get(this->index) & value);
				return *this;
			}

			bool operator&(bool value) const
			{
				return this->ptr->get(this->index) && value;
			}

			bitset_proxy operator^=(bool value) const
			{
				this->ptr->set(this->index, this->ptr->get(this->index) ^ value);
				return *this;
			}

			bool operator^(bool value) const
			{
				return this->ptr->get(this->index) ^ value;
			}

			bitset* ptr;
			ql::size index;
		};

		class bitset_const_proxy
		{
		 public:
			constexpr bitset_const_proxy(const bitset& data, ql::size index) : ptr(&data), index(index)
			{
			}

			constexpr bool get() const
			{
				return this->ptr->get(this->index);
			}

			constexpr operator bool() const
			{
				return this->get();
			}

			bool operator|(bool value) const
			{
				return this->ptr->get(this->index) || value;
			}

			bool operator&(bool value) const
			{
				return this->ptr->get(this->index) && value;
			}

			bool operator^(bool value) const
			{
				return this->ptr->get(this->index) ^ value;
			}

			const bitset* ptr;
			ql::size index;
		};

		class bitset_iterator
		{
		 public:
			bitset_iterator(bitset& data, ql::size index)
			{
				this->ptr = &data;
				this->index = index;
			}

			bitset_iterator& operator++()
			{
				++this->index;
				return *this;
			}

			bitset_iterator operator++(int dummy)
			{
				auto copy = *this;
				++this->index;
				return copy;
			}

			bool operator==(const bitset_iterator& other) const
			{
				return (this->ptr == other.ptr && this->index == other.index);
			}

			bool operator!=(const bitset_iterator& other) const
			{
				return !(*this == other);
			}

			const bitset_proxy& operator*()
			{
				return bitset_proxy(*ptr, index);
			}

			const bitset_const_proxy& operator*() const
			{
				return bitset_const_proxy(*ptr, index);
			}

			bitset* ptr;
			ql::size index;
		};

		class bitset_const_iterator
		{
		 public:
			constexpr bitset_const_iterator(const bitset& data, ql::size index) : ptr(&data), index(index)
			{
			}

			constexpr bitset_const_iterator& operator++()
			{
				++this->index;
			}

			constexpr bitset_const_iterator operator++(int dummy)
			{
				auto copy = *this;
				++this->index;
				return copy;
			}

			constexpr bool operator==(const bitset_iterator& other) const
			{
				return (this->ptr == other.ptr && this->index == other.index);
			}

			constexpr bool operator!=(const bitset_iterator& other) const
			{
				return !(*this == other);
			}

			constexpr bitset_const_proxy& operator*() const
			{
				return bitset_const_proxy(*ptr, index);
			}

			const bitset* const ptr;
			ql::size index;
		};

		constexpr static ql::u64 memory_size()
		{
			return sizeof(holding_type) * ql::bits_in_byte();
		}

		constexpr static ql::size size()
		{
			return bits;
		}

		constexpr static bool is_array()
		{
			return bits > 64u;
		}

		constexpr static ql::size array_size()
		{
			if (!is_array())
			{
				return 0;
			}
			return ql::approximate_multiple_up(bits, ql::u64{64}) / 64;
		}

		constexpr ql::size number_of_set_bits() const
		{
			if constexpr (is_array())
			{
				ql::size size = 0u;
				for (ql::u32 i = 0u; i < this->data.size(); ++i)
				{
					size += ql::number_of_set_bits(this->data[i]);
				}
				return size;
			}
			else
			{
				return ql::number_of_set_bits(this->data);
			}
		}

		constexpr bitset()
		{
			this->clear();
		}

		template <typename T>
		constexpr bitset(T value) : data()
		{
			this->set(value);
		}

		constexpr bitset& operator|=(const bitset& other)
		{
			if constexpr (is_array())
			{
				for (ql::u32 i = 0u; i < this->data.size(); ++i)
				{
					this->data[i] |= other.data[i];
				}
			}
			else
			{
				this->data |= other.data;
			}
			return *this;
		}

		constexpr bitset operator|(const bitset& other) const
		{
			auto result = *this;
			return result |= other;
		}

		constexpr bitset& operator&=(const bitset& other)
		{
			if constexpr (is_array())
			{
				for (ql::u32 i = 0u; i < this->data.size(); ++i)
				{
					this->data[i] &= other.data[i];
				}
			}
			else
			{
				this->data &= other.data;
			}
			return *this;
		}

		constexpr bitset operator&(const bitset& other) const
		{
			auto result = *this;
			return result &= other;
		}

		constexpr bitset& operator^=(const bitset& other)
		{
			if constexpr (is_array())
			{
				for (ql::u32 i = 0u; i < this->data.size(); ++i)
				{
					this->data[i] ^= other.data[i];
				}
			}
			else
			{
				this->data ^= other.data;
			}
			return *this;
		}

		constexpr bitset operator^(const bitset& other) const
		{
			auto result = *this;
			return result ^= other;
		}

		constexpr static auto last_bits_mask()
		{
			return (uint_type{1} << (bits % ql::bits_in_type<uint_type>())) - 1;
		}

		constexpr void clear()
		{
			if constexpr (is_array())
			{
				for (auto& i : this->data)
				{
					i = uint_type{0u};
				}
			}
			else
			{
				this->data = uint_type{0u};
			}
		}

		constexpr void fill(bool n)
		{
			if (n == false)
			{
				this->clear();
			}
			else
			{
				if constexpr (is_array())
				{
					for (ql::size i = 0u; i < this->data.size() - 1; ++i)
					{
						this->data[i] = ql::type_max<uint_type>();
					}
					this->data.back() = last_bits_mask();
				}
				else
				{
					this->data = last_bits_mask();
				}
			}
		}

		constexpr bool operator==(const bitset& other) const
		{
			if constexpr (is_array())
			{
				for (ql::u32 i = 0u; i < this->data.size(); ++i)
				{
					if (this->data[i] != other.data[i])
					{
						return false;
					}
				}
				return true;
			}
			else
			{
				return this->data == other.data;
			}
		}

		constexpr bool operator!=(const bitset& other) const
		{
			return !(*this == other);
		}

		constexpr auto get_masked_data() const
		requires (!is_array())
		{
			return this->data & last_bits_mask();
		}

		constexpr ql::size significant_bit() const
		{
			if constexpr (is_array())
			{
				for (ql::u32 i = 0u; i < this->data.size(); ++i)
				{
					auto index = this->data.size() - i - 1;
					if (this->data[index])
					{
						return ql::significant_bit(this->data[index]) + (i * ql::bits_in_type<uint_type>());
					}
				}
			}
			else
			{
				return ql::significant_bit(this->get_masked_data());
			}
		}

		constexpr bool get(ql::size index) const
		{
			if constexpr (is_array())
			{
				return ql::get_bit(this->data[index / 64u], index % 64u);
			}
			else
			{
				return ql::get_bit(this->data, index);
			}
		}

		constexpr void set(ql::size index, bool value)
		{
			if constexpr (is_array())
			{
				ql::set_bit(this->data[index / 64u], index % 64u, value);
			}
			else
			{
				ql::set_bit(this->data, index, value);
			}
		}

		constexpr void set(holding_type data)
		{
			this->data = data;
		}

		template <typename T>
		constexpr void set_range(ql::u32 begin, ql::u32 end, T value)
		{
			if constexpr (is_array())
			{
				auto div = begin / 64u;

				auto extract = (value & (~T{} >> (ql::bits_in_type<T>() - ((end - (div * 64)) - (begin - (div * 64))) - 1)));
				this->data[div] |= extract << (begin - (div * 64));
			}
			else
			{
				auto extract = (value & (~T{} >> (ql::bits_in_type<T>() - (end - begin) - 1)));
				this->data |= extract << begin;
			}
		}

		constexpr uint_type get_range(ql::u32 begin, ql::u32 end) const
		{
			if constexpr (is_array())
			{
				auto div = begin / 64u;

				auto shift = this->data[div] >> (begin - (div * 64));
				return (shift & (~uint_type{} >> (ql::bits_in_type<uint_type>() - ((end - (div * 64)) - (begin - (div * 64))) - 1)));
			}
			else
			{
				auto shift = this->data >> begin;
				return (shift & (~uint_type{} >> (ql::bits_in_type<uint_type>() - (end - begin) - 1)));
			}
		}

		constexpr bool empty() const
		{
			if constexpr (is_array())
			{
				for (auto& i : this->data)
				{
					if (i)
					{
						return false;
					}
				}
				return true;
			}
			else
			{
				return this->data == holding_type{0};
			}
		}

		constexpr bool full() const
		{
			if constexpr (is_array())
			{
				for (ql::size i = 0u; i < this->data.size() - 1; ++i)
				{
					if (this->data[i] != ql::u64_max)
					{
						return false;
					}
				}
				if (this->data.back() != last_bits_mask())
				{
					return false;
				}
				return true;
			}
			else
			{
				return this->data == last_bits_mask();
			}
		}

		std::string to_string() const
		{
			if constexpr (is_array())
			{
				std::ostringstream stream;
				stream << ql::string_prepended(ql::binary_string(this->data.back()), '0', this->size() % ql::bits_in_type<ql::u64>());
				for (ql::u32 i = 0u; i < this->data.size() - 1; ++i)
				{
					stream << ql::binary_string_full(this->data[this->data.size() - 2 - i]);
				}
				return stream.str();
			}
			else
			{
				auto str = ql::binary_string(this->data);
				return ql::string_prepended(str, '0', this->size());
			}
		}

		std::string to_string_full() const
		{
			if constexpr (is_array())
			{
				std::ostringstream stream;
				for (ql::u32 i = 0u; i < this->data.size(); ++i)
				{
					stream << ql::binary_string_full(this->data[this->data.size() - 1 - i]);
				}
				return stream.str();
			}
			else
			{
				auto str = ql::binary_string(this->data);
				return ql::string_prepended(str, '0', this->size());
			}
		}

		std::string to_hex_string_full(bool seperated = false) const
		{
			if constexpr (is_array())
			{
				std::ostringstream stream;

				if (seperated)
				{
					for (ql::u32 i = 0u; i < this->data.size(); ++i)
					{
						if (i)
							stream << ", ";
						stream << ql::hex_string_full(this->data[this->data.size() - 1 - i]);
					}
				}
				else
				{
					stream << "0x";
					for (ql::u32 i = 0u; i < this->data.size(); ++i)
					{
						stream << ql::hex_string_full(this->data[this->data.size() - 1 - i], "");
					}
				}
				return stream.str();
			}
			else
			{
				auto str = ql::hex_string(this->data, "");
				return ql::to_string("0x", ql::string_prepended(str, '0', this->size()));
			}
		}

		constexpr bitset_iterator begin()
		{
			return bitset_iterator(*this, 0u);
		}

		constexpr bitset_const_iterator begin() const
		{
			return bitset_const_iterator(*this, 0u);
		}

		constexpr bitset_const_iterator cbegin() const
		{
			return bitset_const_iterator(*this, 0u);
		}

		constexpr bitset_iterator end()
		{
			return bitset_iterator(*this, this->size());
		}

		constexpr bitset_const_iterator end() const
		{
			return bitset_const_iterator(*this, this->size());
		}

		constexpr bitset_const_iterator cend() const
		{
			return bitset_const_iterator(*this, this->size());
		}

		constexpr bitset_proxy operator[](ql::size index)
		{
			return bitset_proxy(*this, index);
		}

		constexpr bitset_const_proxy operator[](ql::size index) const
		{
			bitset_const_proxy result(*this, index);
			return result;
		}

		constexpr bitset_range_proxy operator[](std::pair<ql::u32, ql::u32> range)
		{
			return bitset_range_proxy(*this, range.first, range.second);
		}

		constexpr bitset_range_const_proxy operator[](std::pair<ql::u32, ql::u32> range) const
		{
			bitset_range_const_proxy result(*this, range.first, range.second);
			return result;
		}

		constexpr bitset_proxy front()
		{
			return bitset_proxy(*this, 0u);
		}

		constexpr bitset_const_proxy front() const
		{
			return bitset_const_proxy(*this, 0u);
		}

		constexpr bitset_proxy back()
		{
			return bitset_proxy(*this, this->size() - 1);
		}

		constexpr bitset_const_proxy back() const
		{
			return bitset_const_proxy(*this, this->size() - 1);
		}

		holding_type data;
	};
}	 // namespace ql