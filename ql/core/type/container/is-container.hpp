#pragma once

namespace ql
{
	template <typename T>
	concept is_read_container_c = requires(const T a) {
		a.cbegin();
		a.cend();
	};

	template <typename T>
	constexpr bool is_read_container()
	{
		return is_read_container_c<T>;
	}

	template <typename T>
	concept is_write_container_c = requires(T a) {
		a.begin();
		a.end();
	};

	template <typename T>
	constexpr bool is_write_container()
	{
		return is_write_container_c<T>;
	}

	template <typename T>
	concept is_container_c = is_read_container_c<T> || is_write_container_c<T>;

	template <typename T>
	constexpr bool is_container()
	{
		return is_container_c<T>;
	}
}	 // namespace ql