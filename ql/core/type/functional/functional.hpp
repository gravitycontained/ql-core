#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/declval.hpp>
#include <ql/core/type/compare/compare.hpp>
#include <ql/core/type/tuple/tuple.hpp>
#include <functional>

namespace ql
{
	namespace detail
	{

		template <typename R, typename... A>
		constexpr auto return_type(R (*)(A...))
		{
			if constexpr (ql::is_same_decayed<R, void>())
				return ql::empty_type{};
			else
				return ql::declval<R>();
		}

		template <typename R, typename... A>
		constexpr auto return_type(std::function<R(A...)>)
		{
			if constexpr (ql::is_same_decayed<R, void>())
				return ql::empty_type{};
			else
				return ql::declval<R>();
		}

		template <typename C, typename R, typename... A>
		constexpr auto return_type(R (C::*)(A...))
		{
			if constexpr (ql::is_same_decayed<R, void>())
				return ql::empty_type{};
			else
				return ql::declval<R>();
		}

		template <typename C, typename R, typename... A>
		constexpr auto return_type(R (C::*)(A...) const)
		{
			if constexpr (ql::is_same_decayed<R, void>())
				return ql::empty_type{};
			else
				return ql::declval<R>();
		}

		template <typename F>
		constexpr auto return_type(F)
		{
			return return_type(std::function{ql::declval<F>()});
		}

		template <typename C, typename R, typename... A>
		constexpr C method_class_type(R (C::*)(A...))
		{
			return ql::declval<C>();
		}

		template <typename C, typename R, typename... A>
		constexpr C method_class_type(R (C::*)(A...) const)
		{
			return ql::declval<C>();
		}

		template <typename R, typename... A>
		constexpr auto parameter_type(R (*)(A...))
		{
			return std::tuple<A...>{};
		}

		template <typename R, typename... A>
		constexpr auto parameter_type(std::function<R(A...)>)
		{
			return std::tuple<A...>{};
		}

		template <typename C, typename R, typename... A>
		constexpr auto parameter_type(R (C::*)(A...))
		{
			return std::tuple<A...>{};
		}

		template <typename C, typename R, typename... A>
		constexpr auto parameter_type(R (C::*)(A...) const)
		{
			return std::tuple<A...>{};
		}

		template <typename F>
		constexpr auto parameter_type(F)
		{
			return parameter_type(std::function{F{}});
		}

		template <typename R, typename... A>
		constexpr auto function_type(R (*)(A...))
		{
			return std::tuple<R, A...>{};
		}

		template <typename R, typename... A>
		constexpr auto function_type(std::function<R(A...)>)
		{
			return std::tuple<R, A...>{};
		}

		template <typename C, typename R, typename... A>
		constexpr auto function_type(R (C::*)(A...))
		{
			return std::tuple<R, A...>{};
		}

		template <typename C, typename R, typename... A>
		constexpr auto function_type(R (C::*)(A...) const)
		{
			return std::tuple<R, A...>{};
		}

		template <typename F>
		constexpr auto function_type(F)
		{
			return function_type(std::function{F{}});
		}

		template <typename R, typename... A>
		constexpr auto make_function()
		{
			return ql::declval<R (*)(A...)>();
		}

		template <typename C, typename R, typename... A>
		constexpr auto make_method_help()
		{
			return ql::declval<R (C::*)(A...)>();
		}

		template <typename C, typename F>
		constexpr auto make_method()
		{
			auto unpack_tuple = [&]<class C, class Tuple, size_t... Ints>(std::index_sequence<Ints...>)
			{ return make_method_help<C, std::tuple_element_t<Ints, Tuple>...>(); };
			using function_type = decltype(ql::detail::function_type(ql::declval<F>()));
			return unpack_tuple.template operator()<C, function_type>(std::make_index_sequence<ql::tuple_size<function_type>()>{});
		}

		template <typename C, typename F, typename = void>
		struct has_method : std::false_type
		{
		};

		template <typename C, typename F>
		struct has_method<C, F, std::void_t<decltype(make_method<C, F>())>> : std::true_type
		{
		};
	}	 // namespace detail

	template <typename F>
	constexpr bool is_function(F&& function)
	{
		return std::is_function_v<F>;
	}

	template <typename F>
	constexpr bool is_function()
	{
		return std::is_function_v<F>;
	}

	template <typename F>
	constexpr bool is_method(F&& function)
	{
		return std::is_member_function_pointer_v<F>;
	}

	template <typename F>
	constexpr bool is_method()
	{
		return std::is_member_function_pointer_v<F>;
	}

	template <typename F>
	concept is_callable_c = requires(F f) { std::function{f}; };

	template <typename F>
	constexpr bool is_callable()
	{
		return is_callable_c<F>;
	}

	template <typename... Args>
	using make_function = decltype(ql::detail::make_function<Args...>());

	template <typename C, typename F>
	using make_method = decltype(ql::detail::make_method<C, F>());

	template <typename C, typename F>
	constexpr bool has_method()
	{
		return ql::detail::has_method<C, F>::value;
	}

	template <typename F>
	struct return_type_t
	{
		using type = decltype(ql::detail::return_type(ql::declval<F>()));
	};

	template <typename F>
	struct parameter_type_t
	{
		using type = decltype(ql::detail::parameter_type(ql::declval<F>()));
	};

	template <typename F>
	struct method_class_type_t
	{
		using type = decltype(ql::detail::method_class_type(ql::declval<F>()));
	};

	template <typename F>
	struct function_type_t
	{
		using type = decltype(ql::detail::function_type(ql::declval<F>()));
	};

	template <typename F>
	using return_type = decltype(ql::detail::return_type(ql::declval<F>()));

	template <typename F>
	using parameter_type = decltype(ql::detail::parameter_type(ql::declval<F>()));

	template <typename F>
	using method_class_type = decltype(ql::detail::method_class_type(ql::declval<F>()));

	template <typename F>
	using function_type = decltype(ql::detail::function_type(ql::declval<F>()));

	template <typename F>
	constexpr ql::size return_size(F)
	{
		return ql::tuple_size<ql::return_type<F>>();
	}

	template <typename F>
	constexpr ql::size return_size()
	{
		if constexpr (ql::is_same<ql::return_type<F>, ql::empty_type>())
		{
			return 0ull;
		}
		else
		{
			return ql::tuple_size<ql::return_type<F>>();
		}
	}

	template <typename F>
	constexpr ql::size parameter_size(F)
	{
		return ql::tuple_size<ql::parameter_type<F>>();
	}

	template <typename F>
	constexpr ql::size parameter_size()
	{
		return ql::tuple_size<ql::parameter_type<F>>();
	}

	template <typename F>
	constexpr ql::size function_size(F)
	{
		return ql::tuple_size<ql::function_type<F>>();
	}

	template <typename F>
	constexpr ql::size function_size()
	{
		return ql::tuple_size<ql::function_type<F>>();
	}
}	 // namespace ql