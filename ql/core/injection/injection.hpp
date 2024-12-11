#pragma once

#include <ql/core/definition/definition.hpp>

#ifdef QL_GRAPHIC

#include <ql/core/injection/provide.hpp>

#include <ql/core/advanced-type/interactive/type.hpp>

#include <ql/graphic/interactive/declare.hpp>
#include <ql/graphic/state/state-manager/state-manager.hpp>

namespace ql
{

	template <typename T>
	struct injectable
	{
		ql_declare_interactive;
		T* value = nullptr;

		void inject(T& value)
		{
			if (this->value == nullptr)
				this->value = &value;
		}

		void update_injection(ql::state_manager& manager)
		{
			if (this->value == nullptr)
			{
				ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "update injection! ", ql::color::aqua, this);
				manager.provide();
			}
		}

		constexpr operator T&()
		{
			return *this->value;
		}

		constexpr T& operator()()
		{
			return *this->value;
		}
	};
}

#endif