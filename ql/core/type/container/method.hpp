#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/container/subtype.hpp>

namespace ql
{

	template <typename T>
	concept has_size_c = requires(const T x) { x.size(); };

	template <typename T>
	constexpr bool has_size()
	{
		return has_size_c<T>;
	}

	template <typename T>
	concept has_data_c = requires(T x) {
		{ x.data() } -> std::same_as<ql::container_subtype<T>*>;
	};

	template <typename T>
	constexpr bool has_data()
	{
		return has_data_c<T>;
	}

	template <typename T>
	concept has_resize_c = requires(T& x) {
		x.resize(ql::size{});
		x.size();
	};

	template <typename T>
	constexpr bool has_resize()
	{
		return has_resize_c<T>;
	};

	template <typename T>
	concept has_reserve_c = requires(T& x) { x.reserve(ql::size{}); };

	template <typename T>
	constexpr bool has_reserve()
	{
		return has_reserve_c<T>;
	};

	template <typename T>
	concept has_push_back_c = requires(T& x) { x.push_back(ql::declval<ql::container_subtype<T>>()); };

	template <typename T>
	constexpr bool has_push_back()
	{
		return has_push_back_c<T>;
	}

	template <typename T>
	concept has_emplace_back_c = requires(T& x) { x.emplace_back(std::move(ql::declval<ql::container_subtype<T>>())); };

	template <typename T>
	constexpr bool has_emplace_back()
	{
		return has_emplace_back_c<T>;
	}

	template <typename T>
	concept has_pop_back_c = requires(T& x) { x.pop_back(); };

	template <typename T>
	constexpr bool has_pop_back()
	{
		return has_pop_back_c<T>;
	}

	template <typename T>
	concept has_push_front_c = requires(T& x) { x.push_front(ql::container_subtype<T>{}); };

	template <typename T>
	constexpr bool has_push_front()
	{
		return has_push_front_c<T>;
	}

	template <typename T>
	concept has_pop_front_c = requires(T& x) { x.pop_front(); };

	template <typename T>
	constexpr bool has_pop_front()
	{
		return has_pop_front_c<T>;
	}

	template <typename T>
	concept has_insert_c = requires(T& x) { x.insert(ql::container_subtype<T>{}); };

	template <typename T>
	constexpr bool has_insert()
	{
		return has_insert_c<T>;
	}

	template <typename T>
	concept can_grow_c = has_push_back_c<T> || has_insert_c<T>;

	template <typename T>
	constexpr bool can_grow()
	{
		return can_grow_c<T>;
	}

	template <typename T>
	concept has_erase_c = requires(T& x) { x.erase(ql::container_subtype<T>{}); };

	template <typename T>
	constexpr bool has_erase()
	{
		return has_erase_c<T>;
	}

	template <typename T>
	concept has_less_c = requires(const T x) {
		{ x < T{} } -> std::same_as<bool>;
	};

	template <typename T>
	constexpr bool has_less()
	{
		return has_less_c<T>;
	};

	template <typename T>
	concept has_greater_c = requires(const T x) {
		{ x > T{} } -> std::same_as<bool>;
	};

	template <typename T>
	constexpr bool has_greater()
	{
		return has_greater_c<T>;
	};

	template <typename T>
	concept has_equal_c = requires(const T x) {
		{ x == T{} } -> std::same_as<bool>;
	};

	template <typename T>
	constexpr bool has_equal()
	{
		return has_equal_c<T>;
	};

	template <typename T>
	concept has_not_equal_c = requires(const T x) {
		{ x != T{} } -> std::same_as<bool>;
	};

	template <typename T>
	constexpr bool has_not_equal()
	{
		return has_not_equal_c<T>;
	};

	template <typename T>
	concept has_less_equal_c = requires(const T x) {
		{ x <= T{} } -> std::same_as<bool>;
	};

	template <typename T>
	constexpr bool has_less_equal()
	{
		return has_less_equal_c<T>;
	};

	template <typename T>
	concept has_grater_equal_c = requires(const T x) {
		{ x >= T{} } -> std::same_as<bool>;
	};

	template <typename T>
	constexpr bool has_grater_equal()
	{
		return has_grater_equal_c<T>;
	};

	template <typename T, typename U>
	concept is_equal_comparable_c = requires(const T x, const U y) {
		{ x == y } -> std::same_as<bool>;
	};

	template <typename T, typename U>
	constexpr bool is_equal_comparable()
	{
		return is_equal_comparable_c<T, U>;
	};

	template <typename T, typename U>
	concept is_not_equal_comparable_c = requires(const T x, const U y) {
		{ x != y } -> std::same_as<bool>;
	};

	template <typename T, typename U>
	constexpr bool is_not_equal_comparable()
	{
		return is_not_equal_comparable_c<T, U>;
	};

	template <typename T, typename U>
	concept is_greater_comparable_c = requires(const T x, const U y) {
		{ x > y } -> std::same_as<bool>;
	};

	template <typename T, typename U>
	constexpr bool is_greater_comparable()
	{
		return is_greater_comparable_c<T, U>;
	};

	template <typename T, typename U>
	concept is_less_comparable_c = requires(const T x, const U y) {
		{ x < y } -> std::same_as<bool>;
	};

	template <typename T, typename U>
	constexpr bool is_less_comparable()
	{
		return is_less_comparable_c<T, U>;
	};

	template <typename T, typename U>
	concept is_less_equal_comparable_c = requires(const T x, const U y) {
		{ x <= y } -> std::same_as<bool>;
	};

	template <typename T, typename U>
	constexpr bool is_less_equal_comparable()
	{
		return is_less_equal_comparable_c<T, U>;
	};

	template <typename T, typename U>
	concept is_greater_equal_comparable_c = requires(const T x, const U y) {
		{ x >= y } -> std::same_as<bool>;
	};

	template <typename T, typename U>
	constexpr bool is_greater_equal_comparable()
	{
		return is_greater_equal_comparable_c<T, U>;
	};
}	 // namespace ql