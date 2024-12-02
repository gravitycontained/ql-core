#pragma once

#include <sstream>
#include <string>

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/string/is-printable.hpp>

#include <ql/core/type/container/is-container.hpp>
#include <ql/core/type/container/method.hpp>

#include <ql/core/type/string/string.hpp>
#include <ql/core/type/tuple/size.hpp>
#include <ql/core/type/arithmetic/arithmetic.hpp>

#include <ql/core/type/container/type.hpp>

namespace ql
{

	namespace detail
	{

		template <typename T, typename U>
		concept castable_test_default = requires(T v, U x) { v = static_cast<T>(x); };

		template <typename T>
		concept castable_test_stream = requires(T x, std::wstringstream stream) {
			stream << x;
			stream >> x;
		};

		template <typename T>
		concept castable_test_from_chars =
				requires(T x, std::string_view sv) { std::from_chars(sv.data(), sv.data() + sv.size(), x); };
	}	 // namespace detail

	template <typename T, typename U>
	constexpr bool type_castable()
	{
		if constexpr (ql::is_container<U>() && !ql::is_long_string_type<U>())
		{
			if constexpr (ql::has_resize_and_access<ql::container_change_subtype<U, T>>())
			{
				if constexpr (ql::has_square_brackets<ql::container_change_subtype<U, T>>())
				{
					return ql::type_castable<T, decltype(ql::declval<U>()[0])>();
				}
				else if constexpr (ql::has_at<ql::container_change_subtype<U, T>>())
				{
					return ql::type_castable<T, decltype(ql::declval<U>().at(0))>();
				}
				else
				{
					return false;
				}
			}
			else
			{
				if constexpr (ql::has_push_back<ql::container_change_subtype<U, T>>())
				{
					return ql::type_castable<T, decltype(*ql::declval<U>().begin())>();
				}
				else if constexpr (ql::has_insert<ql::container_change_subtype<U, T>>())
				{
					return ql::type_castable<T, decltype(*ql::declval<U>().begin())>();
				}
				else
				{
					return false;
				}
			}
		}
		else if constexpr (ql::is_long_standard_string_type<U>())
		{
			return false;
			//return detail::castable_test_from_chars<T>;
		}
		else if constexpr (ql::is_long_wstring_type<U>())
		{
			return detail::castable_test_stream<T>;
		}
		else if constexpr (ql::is_long_standard_string_type<T>())
		{
			return ql::is_printable<T>();
		}
		else if constexpr (ql::is_long_wstring_type<T>())
		{
			return ql::is_printable<T>();
		}
		else
		{
			return detail::castable_test_default<T, U>;
		}
	}

	constexpr auto test = ql::type_castable<std::string, std::string>();

	template <typename T, typename Tuple>
	constexpr bool type_castable_tuple()
	{
		auto unpack = [&]<typename T, typename Tuple, ql::size... Ints>(std::index_sequence<Ints...>)
		{ return ((ql::type_castable<T, std::tuple_element_t<Ints, Tuple>>()) && ...); };

		return unpack.template operator()<T, Tuple>(std::make_index_sequence<ql::tuple_size<Tuple>()>());
	}

	template <typename T, typename U>
	requires (ql::type_castable<T, U>())
	constexpr inline auto type_cast(U&& data)
	{
		if constexpr (ql::is_container<U>() && !ql::is_long_string_type<U>())
		{
			typename ql::container_change_subtype<U, T> result;
			if constexpr (ql::has_resize_and_access<ql::container_change_subtype<U, T>>())
			{
				result.resize(data.size());
				for (ql::size i = 0u; i < data.size(); ++i)
				{
					if constexpr (ql::has_square_brackets<ql::container_change_subtype<U, T>>())
					{
						result[i] = ql::type_cast<T>(data[i]);
					}
					else if constexpr (ql::has_at<ql::container_change_subtype<U, T>>())
					{
						result.at(i) = ql::type_cast<T>(data.at(i));
					}
					else
					{
						static_assert("type_cast: T has no [] nor .at()");
					}
				}
			}
			else
			{
				for (const auto& i : data)
				{
					if constexpr (ql::has_push_back<ql::container_change_subtype<U, T>>())
					{
						result.push_back(ql::type_cast<T>(i));
					}
					else if constexpr (ql::has_insert<ql::container_change_subtype<U, T>>())
					{
						result.insert(ql::type_cast<T>(i));
					}
					else
					{
						static_assert("type_cast: T has no pushback nor insert");
					}
				}
			}
			return result;
		}
		else if constexpr (ql::is_long_standard_string_type<U>())
		{
			std::string_view sv{data};
			T value;
			std::from_chars(sv.data(), sv.data() + sv.size(), value);
			return value;
		}
		else if constexpr (ql::is_long_wstring_type<U>())
		{
			std::wstringstream stream;
			stream << data;
			T value;
			stream >> value;

			return value;
		}
		else if constexpr (ql::is_long_standard_string_type<T>())
		{
			std::ostringstream stream;
			stream << data;
			return stream.str();
		}
		else if constexpr (ql::is_long_wstring_type<T>())
		{
			std::wostringstream stream;
			stream << data;
			return stream.str();
		}
		else
		{
			return static_cast<T>(data);
		}
	}

	template <typename T>
	constexpr inline auto u8_cast(T&& data)
	{
		return ql::type_cast<ql::u8>(data);
	}

	template <typename T>
	constexpr inline auto i8_cast(T&& data)
	{
		return ql::type_cast<ql::i8>(data);
	}

	template <typename T>
	constexpr inline auto u16_cast(T&& data)
	{
		return ql::type_cast<ql::u16>(data);
	}

	template <typename T>
	constexpr inline auto i16_cast(T&& data)
	{
		return ql::type_cast<ql::i16>(data);
	}

	template <typename T>
	constexpr inline auto u32_cast(T&& data)
	{
		return ql::type_cast<ql::u32>(data);
	}

	template <typename T>
	constexpr inline auto i32_cast(T&& data)
	{
		return ql::type_cast<ql::i32>(data);
	}

	template <typename T>
	constexpr inline auto u64_cast(T&& data)
	{
		return ql::type_cast<ql::u64>(data);
	}

	template <typename T>
	constexpr inline auto i64_cast(T&& data)
	{
		return ql::type_cast<ql::i64>(data);
	}

	template <typename T>
	constexpr inline auto size_cast(T&& data)
	{
		return ql::type_cast<ql::size>(data);
	}

	template <typename T>
	constexpr inline auto isize_cast(T&& data)
	{
		return ql::type_cast<ql::isize>(data);
	}

	template <typename T>
	constexpr inline auto signed_size_cast(T&& data)
	{
		return static_cast<ql::signed_type<ql::size>>(data);
	}

	template <typename T>
	constexpr inline auto char_cast(T&& data)
	{
		return ql::type_cast<ql::char_type>(data);
	}

	template <typename T>
	constexpr inline auto wchar_cast(T&& data)
	{
		return ql::type_cast<ql::wchar_type>(data);
	}

	template <typename T>
	constexpr inline auto f32_cast(T&& data)
	{
		return ql::type_cast<ql::f32>(data);
	}

	template <typename T>
	constexpr inline auto f64_cast(T&& data)
	{
		return ql::type_cast<ql::f64>(data);
	}

	template <typename T>
	constexpr inline auto bool_cast(T&& data)
	{
		return ql::type_cast<bool>(data);
	}

	template <typename T>
	constexpr inline auto signed_cast(T&& value)
	{
		return ql::type_cast<signed_type<T>>(value);
	}

	template <typename T>
	constexpr inline auto unsigned_cast(T&& value)
	{
		return ql::type_cast<unsigned_type<T>>(value);
	}

	template <typename T>
	constexpr inline auto int_cast(T&& value)
	{
		return ql::type_cast<int_type<T>>(value);
	}

	template <typename T>
	constexpr inline auto float_cast(T&& value)
	{
		return ql::type_cast<float_type<T>>(value);
	}

}	 // namespace ql