#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

#include <ql/core/string/to-string.hpp>

#include <vector>

namespace ql
{
	template <typename T, bool BOUNDARY_CHECK = ql::detail::vector_boundary_check>
	struct vector : std::vector<T>
	{
		constexpr void index_check(ql::size index, bool at) const
		{
			if (index >= this->size())
			{
				std::ostringstream stream;
				stream << ql::to_string("ql::vector<", ql::type_name<T>(), ">", at ? ".at()" : "::operator[]", " : index is ", index);
				auto convert = ql::signed_cast(index);
				if (convert < 0)
				{
					stream << ql::to_string(" (= ", convert, ") ");
				}
				stream << " - size of vector is " << this->size();
				throw std::exception(stream.str().c_str());
			}
		}

		constexpr void front_check(bool front) const
		{
			if (this->empty())
			{
				std::ostringstream stream;
				stream << ql::to_string("ql::vector<", ql::type_name<T>(), ">", front ? ".front()" : ".back()", " : vector is empty");
				throw std::exception(stream.str().c_str());
			}
		}

	 public:

		constexpr auto& operator=(const std::vector<T>& other)
		{
			return std::vector<T>::operator=(other);
		}

		constexpr T& operator[](ql::size index)
		{
			if constexpr (BOUNDARY_CHECK)
			{
				this->index_check(index, false);
			}
			return std::vector<T>::operator[](index);
		}

		constexpr const T& operator[](ql::size index) const
		{
			if constexpr (BOUNDARY_CHECK)
			{
				this->index_check(index, false);
			}
			return std::vector<T>::operator[](index);
		}

		constexpr T& at(ql::size index)
		{
			if constexpr (BOUNDARY_CHECK)
			{
				this->index_check(index, true);
			}
			return std::vector<T>::at(index);
		}

		constexpr const T& at(ql::size index) const
		{
			if constexpr (BOUNDARY_CHECK)
			{
				this->index_check(index, true);
			}
			return std::vector<T>::at(index);
		}
	};
}	 // namespace ql