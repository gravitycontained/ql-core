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
		//std::shared_ptr<T> value = std::make_shared<T>();

		~injectable()
		{
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
				ql::println(
					ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_gray,
					ql::string_left_spaced("received injection! ", 24), ql::color::aqua, this, " ", ql::color::bright_blue,
					ql::type_name<T>()
				);
				//this->value = std::make_shared<T>(value);
				this->value = &value;
			}
		}

		void update_injection(ql::state_manager& manager)
		{
			if (!this->value)
			{
				ql::println(
					ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_blue,
					ql::string_left_spaced("update injection ", 24), ql::color::aqua, this, " ", ql::color::bright_blue, ql::type_name<T>()
				);
				manager.provide();
			}
		}

		constexpr operator bool()
		{
			return this->value != nullptr;
		}

		constexpr T*& operator->()
		{
			//return this->value.operator->();
			return this->value;
		}

		
		constexpr T& get()
		{
			if (!this->value)
				throw std::runtime_error(ql::to_string("ql::injectable<", ql::type_name<T>(), ">: no injection received"));

			return *this->value;
		}

		constexpr const T& get() const
		{
			if (!this->value)
				throw std::runtime_error(ql::to_string("ql::injectable<", ql::type_name<T>(), ">: no injection received"));

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