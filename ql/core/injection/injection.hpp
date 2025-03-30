#pragma once

#include <ql/core/definition/definition.hpp>

#ifdef QL_GRAPHIC

#include <ql/graphic/sync/type/type.hpp>
#include <ql/graphic/state/state-manager/state-manager.hpp>

namespace ql
{

	template <typename T>
	struct injectable
	{
		T* value = nullptr;

		injectable()
		{
			ql::println(
				ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_gray,
				ql::string_left_spaced("construct injectable ", 24), ql::color::aqua, this, " ", ql::color::bright_blue, ql::type_name<T>()
			);

			++ql::detail::sync_injection_request_count;
		}

		~injectable()
		{
			if constexpr (ql::debug::print)
				ql::println(
					ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_gray,
					ql::string_left_spaced("destruct injectable ", 24), ql::color::aqua, this, " ", ql::color::bright_blue, ql::type_name<T>()
				);

			this->value = nullptr;
		}

		void inject(T& value)
		{
			if (!this->value)
			{
				if constexpr (ql::debug::print)
					ql::println(
						ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_gray,
						ql::string_left_spaced("received injection! ", 24), ql::color::aqua, this, " ", ql::color::bright_blue,
						ql::type_name<T>()
					);
					
				if (ql::detail::sync_injection_request_count)
					--ql::detail::sync_injection_request_count;

				this->value = &value;
			}
		}

		void update_injection(ql::state_manager& manager)
		{
			if (!this->value)
			{
				if constexpr (ql::debug::print)
					ql::println(
						ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_blue,
						ql::string_left_spaced("update injection ", 24), ql::color::aqua, this, " ", ql::color::bright_blue, ql::type_name<T>()
					);

				if (ql::detail::sync_injection_request_count)
					--ql::detail::sync_injection_request_count;

				manager.provide();
			}
		}

		constexpr operator bool()
		{
			return this->value != nullptr;
		}

		constexpr T*& operator->()
		{
			return this->value;
		}

		void sanity_check() const
		{
			if (!this->value)
			{
				ql::println('\n',
					ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_red,
					ql::to_string("ql::injectable<", ql::type_name<T>(), ">: no injection received -> calling manual provide")
				);
				ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::aqua, "-> the state management needs to be extended OR the order of operations outside this framework need to be reworked.\n");

				ql::detail::state_manager->provide();

				if (!this->value)
					throw std::runtime_error(ql::to_string("ql::injectable<", ql::type_name<T>(), ">: no injection received"));
			}
		}
		
		constexpr T& get()
		{
			this->sanity_check();
			return *this->value;
		}

		constexpr const T& get() const
		{
			this->sanity_check();
			return *this->value;
		}

		constexpr T& operator()()
		{
			return this->get();
		}

		constexpr const T& operator()() const
		{
			return this->get();
		}
	};
}

#endif
