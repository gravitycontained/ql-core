#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{
	template <typename T>
	struct signal
	{
		T value;

		mutable std::vector<std::function<void(const T&)>> listeners;
		mutable std::vector<std::function<void(void)>> voidListeners;

		constexpr signal()
		{
		}

		constexpr signal(const T& value)
		{
			this->value = value;
		}

		constexpr operator T&()
		{
			return this->value;
		}

		constexpr operator const T&() const
		{
			return this->value;
		}

		constexpr void runListeners() const
		{
			for (const auto& listener : this->voidListeners)
				listener();

			for (const auto& listener : this->listeners)
				listener(this->value);
		}

		constexpr signal& operator=(const T& newValue)
		{
			auto before = this->value;
			this->value = newValue;
			auto changed = (before != this->value);

			if (changed)
				this->runListeners();

			return *this;
		}

		constexpr signal& operator+=(const T& value)
		{
			auto before = this->value;
			this->value += value;
			auto changed = (before != this->value);

			if (changed)
				this->runListeners();

			return *this;
		}

		constexpr signal& operator*=(const T& value)
		{
			auto before = this->value;
			this->value *= value;
			auto changed = (before != this->value);

			if (changed)
				this->runListeners();

			return *this;
		}

		constexpr signal& operator/=(const T& value)
		{
			auto before = this->value;
			this->value /= value;
			auto changed = (before != this->value);

			if (changed)
				this->runListeners();

			return *this;
		}

		constexpr signal& operator<<=(const T& value)
		{
			auto before = this->value;
			this->value <<= value;
			auto changed = (before != this->value);

			if (changed)
				this->runListeners();

			return *this;
		}

		constexpr signal& operator>>=(const T& value)
		{
			auto before = this->value;
			this->value >>= value;
			auto changed = (before != this->value);

			if (changed)
				this->runListeners();

			return *this;
		}

		void addListener(const std::function<void(const T&)>& listener) const
		{
			this->listeners.push_back(listener);
		}

		void addListener(const std::function<void(void)>& listener) const
		{
			this->voidListeners.push_back(listener);
		}
	};
}	 // namespace ql
