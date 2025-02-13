#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

#include <ql/core/string/to-string.hpp>
#include <ql/core/system/print/print.hpp>

#include <array>

namespace ql
{

	template <typename T, ql::size N, bool BOUNDARY_CHECK = ql::detail::array_boundary_check>
	struct array : std::array<T, N>
	{
		constexpr void index_check(ql::size index, bool at) const
		{
			if (index >= this->size())
			{
				std::ostringstream stream;
				stream << ql::to_string(
						"ql::array<", ql::type_name<T>(), ", ", N, ">", at ? ".at()" : "::operator[]", " : index is ", index
				);
				ql::i32 convert = ql::i32_cast(index);
				if (convert < 0)
				{
					stream << ql::to_string(" (= ", convert, ") ");
				}
				if constexpr (ql::debug::print)
					ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", stream.str());
				
				throw std::exception(stream.str().c_str());
			}
		}

	 public:
		constexpr auto& operator=(const std::array<T, N>& other)
		{
			return std::array<T, N>::operator=(other);
		}

		constexpr T& operator[](ql::size index)
		{
			if constexpr (BOUNDARY_CHECK)
			{
				this->index_check(index, false);
			}
			return std::array<T, N>::operator[](index);
		}

		constexpr const T& operator[](ql::size index) const
		{
			if constexpr (BOUNDARY_CHECK)
			{
				this->index_check(index, false);
			}
			return std::array<T, N>::operator[](index);
		}

		constexpr T& at(ql::size index)
		{
			if constexpr (BOUNDARY_CHECK)
			{
				this->index_check(index, true);
			}
			return std::array<T, N>::at(index);
		}

		constexpr const T& at(ql::size index) const
		{
			if constexpr (BOUNDARY_CHECK)
			{
				this->index_check(index, true);
			}
			return std::array<T, N>::at(index);
		}
	};
}	 // namespace ql
