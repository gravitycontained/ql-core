#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/container/is-container.hpp>
#include <ql/core/type/compare/compare.hpp>
#include <ql/core/type/container/subtype.hpp>

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <forward_list>
#include <deque>
#include <vector>
#include <list>
#include <array>


namespace ql
{
	namespace detail
	{

		template <typename T, typename F = void>
		struct has_key_type
		{
			constexpr static bool value = false;
			using type = ql::error_type;
		};

		template <typename T>
		struct has_key_type<T, std::void_t<typename T::key_type>>
		{
			constexpr static bool value = true;
			using type = typename T::key_type;
		};

		template <typename T, typename F = void>
		struct has_value_type
		{
			constexpr static bool value = false;
			using type = ql::error_type;
		};

		template <typename T>
		struct has_value_type<T, std::void_t<typename T::value_type>>
		{
			constexpr static bool value = true;
			using type = typename T::value_type;
		};

		template <typename T, typename F = void>
		struct has_mapped_type
		{
			constexpr static bool value = false;
			using type = ql::error_type;
		};

		template <typename T>
		struct has_mapped_type<T, std::void_t<typename T::mapped_type>>
		{
			constexpr static bool value = true;
			using type = typename T::mapped_type;
		};

		template <typename T, typename F = void>
		struct has_key_compare_type
		{
			constexpr static bool value = false;
			using type = ql::error_type;
		};

		template <typename T>
		struct has_key_compare_type<T, std::void_t<typename T::key_compare>>
		{
			constexpr static bool value = true;
			using type = typename T::key_compare;
		};

		template <typename T, typename F = void>
		struct has_key_equal_type
		{
			constexpr static bool value = false;
			using type = ql::error_type;
		};

		template <typename T>
		struct has_key_equal_type<T, std::void_t<typename T::key_equal>>
		{
			constexpr static bool value = true;
			using type = typename T::key_equal;
		};

		template <typename T, typename F = void>
		struct has_allocator_type
		{
			constexpr static bool value = false;
			using type = ql::error_type;
		};

		template <typename T>
		struct has_allocator_type<T, std::void_t<typename T::allocator_type>>
		{
			constexpr static bool value = true;
			using type = typename T::allocator_type;
		};

		template <typename T, typename F = void>
		struct has_hasher_type
		{
			constexpr static bool value = false;
			using type = ql::error_type;
		};

		template <typename T>
		struct has_hasher_type<T, std::void_t<typename T::hasher>>
		{
			constexpr static bool value = true;
			using type = typename T::hasher;
		};

		template <ql::size N, bool B>
		struct std_array_size_info
		{
			constexpr static ql::size size = N;
			constexpr static bool value = B;
		};

		template <typename T>
		constexpr auto std_array_size(T &&f)
		{
			return std_array_size_info<0u, false>{};
		}

		template <typename T, ql::size N>
		constexpr auto std_array_size(std::array<T, N> &&f)
		{
			return std_array_size_info<N, true>{};
		}

		template <typename T>
		constexpr auto value_type()
		{
			if constexpr(ql::detail::has_key_type<T>::value)
			{
				return ql::declval<ql::detail::has_key_type<T>::type>();
			}
			else
			{
				return ql::declval<ql::detail::has_key_type<T>::type>();
			}
		}

		template <typename T>
		constexpr auto mapped_type()
		{
			if constexpr(ql::detail::has_mapped_type<T>::value)
			{
				return ql::declval<ql::detail::has_mapped_type<T>::type>();
			}
			else
			{
				return ql::size{};
			}
		}
	}	 // namespace detail

	template <typename C>
	requires(ql::is_container<C>())
	using container_key_type = ql::detail::has_key_type<C>::type;

	template <typename C>
	requires(ql::is_container<C>())
	using container_value_type = ql::detail::has_value_type<C>::type;

	template <typename C>
	requires(ql::is_container<C>())
	using container_mapped_type = ql::detail::has_mapped_type<C>::type;

	template <typename C>
	requires(ql::is_container<C>())
	using container_allocator_type = ql::detail::has_allocator_type<C>::type;

	template <typename C>
	requires(ql::is_container<C>())
	using container_key_compare_type = ql::detail::has_key_compare_type<C>::type;

	template <typename C>
	requires(ql::is_container<C>())
	using container_key_equal_type = ql::detail::has_key_equal_type<C>::type;

	template <typename C>
	requires(ql::is_container<C>())
	using container_hasher_type = ql::detail::has_hasher_type<C>::type;


	template <typename T>
	constexpr bool has_key_type()
	{
		return ql::detail::has_key_type<T>::value;
	}

	template <typename T>
	constexpr bool has_value_type()
	{
		return ql::detail::has_value_type<T>::value;
	}

	template <typename T>
	constexpr bool has_mapped_type()
	{
		return ql::detail::has_mapped_type<T>::value;
	}

	template <typename T>
	constexpr auto mapped_type()
	{
		if constexpr(ql::has_mapped_type<T>())
		{
			return ql::declval<ql::container_mapped_type<T>>();
		}
		else
		{
			return ql::size{};
		}
	}

	template <typename T>
	constexpr bool has_key_compare_type()
	{
		return ql::detail::has_key_compare_type<T>::value;
	}

	template <typename T>
	constexpr bool has_key_equal_type()
	{
		return ql::detail::has_key_equal_type<T>::value;
	}

	template <typename T>
	constexpr bool has_hasher_type()
	{
		return ql::detail::has_hasher_type<T>::value;
	}

	template <typename T>
	constexpr bool has_allocator_type()
	{
		return ql::detail::has_allocator_type<T>::value;
	}

	template <typename T>
	constexpr bool has_std_array_size()
	{
		return decltype(ql::detail::std_array_size(T{}))::value;
	}

	template <typename T>
	constexpr ql::size std_array_size()
	{
		return decltype(ql::detail::std_array_size(T{}))::size;
	}

	template <typename T>
	concept is_sortable_c = std::sortable<T>;

	template <typename T>
	constexpr bool is_sortable()
	{
		return true || is_sortable_c<T>;
	}

	template <typename T>
	concept is_iterator_c = requires(T a, const T &b) {
		a.operator*();
		++a;
		{ b == T{} } -> std::same_as<bool>;
		{ b != T{} } -> std::same_as<bool>;
	};

	template <typename T>
	constexpr bool is_iterator()
	{
		return is_iterator_c<T>;
	}

	template <typename C>
	concept has_map_signature_c =
			(ql::is_container<C>() && ql::has_value_type<C>() &&
			 ql::has_mapped_type<C>() && ql::has_key_compare_type<C>() &&
			 ql::has_allocator_type<C>());

	template <typename C>
	constexpr bool has_map_signature()
	{
		return has_map_signature_c<C>;
	}

	template <typename C>
	constexpr bool is_std_set_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_key_type<C>() && ql::has_key_compare_type<C>() &&
									 ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C, std::set<ql::container_key_type<C>,
																		 ql::container_key_compare_type<C>,
																		 ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_multiset_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_key_type<C>() && ql::has_key_compare_type<C>() &&
									 ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C, std::multiset<ql::container_key_type<C>,
																					ql::container_key_compare_type<C>,
																					ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_unordered_set_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_key_type<C>() && ql::has_hasher_type<C>() &&
									 ql::has_key_equal_type<C>() && ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C,
												 std::unordered_set<ql::container_key_type<C>,
																						ql::container_hasher_type<C>,
																						ql::container_key_equal_type<C>,
																						ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_unordered_multiset_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_key_type<C>() && ql::has_hasher_type<C>() &&
									 ql::has_key_equal_type<C>() && ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C, std::unordered_multiset<
																ql::container_key_type<C>,
																ql::container_hasher_type<C>,
																ql::container_key_equal_type<C>,
																ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_map_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_key_type<C>() && ql::has_mapped_type<C>() &&
									 ql::has_key_compare_type<C>() && ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C, std::map<ql::container_key_type<C>,
																		 ql::container_mapped_type<C>,
																		 ql::container_key_compare_type<C>,
																		 ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_multimap_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_key_type<C>() && ql::has_mapped_type<C>() &&
									 ql::has_key_compare_type<C>() && ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C, std::multimap<ql::container_key_type<C>,
																					ql::container_mapped_type<C>,
																					ql::container_key_compare_type<C>,
																					ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_unordered_map_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_key_type<C>() && ql::has_mapped_type<C>() &&
									 ql::has_hasher_type<C>() && ql::has_key_equal_type<C>() &&
									 ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C,
												 std::unordered_map<ql::container_key_type<C>,
																						ql::container_mapped_type<C>,
																						ql::container_hasher_type<C>,
																						ql::container_key_equal_type<C>,
																						ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_unordered_multimap_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_key_type<C>() && ql::has_mapped_type<C>() &&
									 ql::has_hasher_type<C>() && ql::has_key_equal_type<C>() &&
									 ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C, std::unordered_multimap<
																ql::container_key_type<C>,
																ql::container_mapped_type<C>,
																ql::container_hasher_type<C>,
																ql::container_key_equal_type<C>,
																ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_vector_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_value_type<C>() && ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C, std::vector<ql::container_value_type<C>,
																				ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_list_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_value_type<C>() && ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C, std::list<ql::container_value_type<C>,
																			ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_forward_list_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_value_type<C>() && ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C,
												 std::forward_list<ql::container_value_type<C>,
																					 ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_deque_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_value_type<C>() && ql::has_allocator_type<C>())
			{
				if constexpr(ql::is_same_decayed<
												 C, std::deque<ql::container_value_type<C>,
																			 ql::container_allocator_type<C>>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	constexpr bool is_std_array_type()
	{
		if constexpr(ql::is_container<C>())
		{
			if constexpr(ql::has_value_type<C>() && ql::has_std_array_size<C>())
			{
				if constexpr(ql::is_same<C, std::array<ql::container_value_type<C>,
																							 ql::std_array_size<C>()>>())
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename C>
	requires(ql::is_container<C>())
	constexpr bool is_sorted_container()
	{
		return ql::is_std_set_type<C>() || ql::is_std_multiset_type<C>() ||
					 ql::is_std_map_type<C>() || ql::is_std_multimap_type<C>();
	}

	template <typename C>
	requires(ql::is_container<C>())
	constexpr bool is_unsorted_container()
	{
		return !ql::is_sorted_container<C>();
	}

	template <typename C>
	requires(ql::is_container<C>())
	constexpr bool is_std_container()
	{
		return ql::is_std_set_type<C>() || ql::is_std_multiset_type<C>() ||
					 ql::is_std_unordered_set_type<C>() ||
					 ql::is_std_unordered_multiset_type<C>() ||
					 ql::is_std_map_type<C>() || ql::is_std_multimap_type<C>() ||
					 ql::is_std_unordered_map_type<C>() ||
					 ql::is_std_unordered_multimap_type<C>() ||
					 ql::is_std_vector_type<C>() || ql::is_std_list_type<C>() ||
					 ql::is_std_forward_list_type<C>() || ql::is_std_array_type<C>() ||
					 ql::is_std_deque_type<C>();
	}

	namespace impl
	{
		template <typename T>
		constexpr auto mapped_type()
		{
			if constexpr(ql::has_mapped_type<T>())
			{
				return ql::declval<ql::container_mapped_type<T>>();
			}
			else
			{
				return ql::size{};
			}
		}

		template <typename T>
		constexpr auto value_type()
		{
			if constexpr(ql::has_key_type<T>())
			{
				return ql::declval<ql::container_key_type<T>>();
			}
			else
			{
				return ql::declval<ql::container_subtype<T>>();
			}
		}
	}	 // namespace impl

	template <typename T>
	concept has_square_brackets_c = requires(T &x, const T &y) {
		x[ql::detail::mapped_type<T>()] = ql::detail::value_type<T>();
		y[ql::detail::mapped_type<T>()];
	};

	template <typename T>
	constexpr bool has_square_brackets()
	{
		return has_square_brackets_c<T>;
	}

	template <typename T>
	concept has_square_brackets_read_c =
			requires(const T &n) { n[ql::detail::mapped_type<T>()]; };

	template <typename T>
	constexpr bool has_square_brackets_read()
	{
		return has_square_brackets_read_c<T>;
	}

	template <typename T>
	concept has_square_brackets_write_c = requires(T &n) {
		n[ql::detail::mapped_type<T>()] = ql::detail::value_type<T>();
	};

	template <typename T>
	constexpr bool has_square_brackets_write()
	{
		return has_square_brackets_write_c<T>;
	}

	template <typename T>
	concept has_at_c = requires(T &x, const T &y) {
		x.at(ql::detail::mapped_type<T>()) = ql::detail::value_type<T>();
		y.at(ql::detail::mapped_type<T>());
	};

	template <typename T>
	constexpr bool has_at()
	{
		return has_at_c<T>;
	}

	template <typename T>
	concept has_at_read_c =
			requires(const T &n) { n.at(ql::detail::mapped_type<T>()); };

	template <typename T>
	constexpr bool has_at_read()
	{
		return has_at_read_c<T>;
	}

	template <typename T>
	concept has_at_write_c = requires(T &n) {
		n.at(ql::detail::mapped_type<T>()) = ql::detail::value_type<T>();
	};

	template <typename T>
	constexpr bool has_at_write()
	{
		return has_at_write_c<T>;
	}

	//template <typename T>
	//concept has_resize_c = requires(T &x) {
	//	x.resize(ql::size{});
	//	x.size();
	//};
	//
	//template <typename T>
	//constexpr bool has_resize()
	//{
	//	return has_resize_c<T>;
	//};

	template <typename T>
	concept has_resize_and_access_c =
			has_resize_c<T> && (has_square_brackets_c<T> || has_at_c<T>);

	template <typename T>
	constexpr bool has_resize_and_access()
	{
		return has_resize_and_access_c<T>;
	}
}	 // namespace ql