#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/container/method.hpp>
#include <ql/core/type/compare/compare.hpp>

namespace ql
{
	namespace detail
	{
		template <typename T, typename F = void>
		struct has_iterator_concept_type
		{
			constexpr static bool value = false;
			using type = typename ql::error_type;
		};

		template <typename T>
		struct has_iterator_concept_type<T, std::void_t<typename T::iterator::iterator_concept>>
		{
			constexpr static bool value = true;
			using type = typename T::iterator::iterator_concept;
		};
	}	 // namespace detail

	template <typename T>
	constexpr bool is_contiguous_container()
	{
		return ql::is_same_decayed<typename ql::detail::has_iterator_concept_type<T>::type, std::contiguous_iterator_tag>() &&
					 ql::has_data<T>();
	}
}	 // namespace ql