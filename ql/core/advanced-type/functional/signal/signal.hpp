#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

#include <ql/core/system/print/print.hpp>

namespace ql
{

	namespace detail
	{
		QL_SOURCE extern std::unordered_set<ql::size> signal_listeners;
		QL_SOURCE extern ql::size signal_index;
	}	 // namespace detail

	QL_SOURCE void reset_signal_listeners();

	template <typename T>
	struct signal
	{
		T value;
		T value_before;

		std::vector<std::pair<ql::size, std::function<void(const T&)>>> listeners;
		std::vector<std::pair<ql::size, std::function<void(void)>>> voidListeners;

		bool fire_next_time = false;

		constexpr operator T&()
		{
			return this->value;
		}

		constexpr operator const T&() const
		{
			return this->value;
		}

		constexpr auto operator()() const
		{
			return this->value;
		}

		void check_id()
		{
			if (this->id == ql::size_max)
			{
				this->id = detail::signal_index++;
			}
		}

		constexpr void runListeners() const
		{
			for (const auto& [index, listener] : this->voidListeners)
			{
				if (detail::signal_listeners.find(index) == detail::signal_listeners.cend())
				{
					detail::signal_listeners.insert(index);
					listener();
				}
			}

			for (const auto& [index, listener] : this->listeners)
			{
				if (detail::signal_listeners.find(index) == detail::signal_listeners.cend())
				{
					detail::signal_listeners.insert(index);
					listener(this->value);
				}
			}
		}

		constexpr signal& operator=(const T& newValue)
		{
			this->value = newValue;
			return *this;
		}

		constexpr void set(const T& newValue)
		{
			this->value = newValue;
		}

		constexpr signal& operator+=(const T& value)
		{
			this->value += value;
			return *this;
		}

		constexpr signal& operator*=(const T& value)
		{
			this->value *= value;
			return *this;
		}

		constexpr signal& operator/=(const T& value)
		{
			this->value /= value;
			return *this;
		}

		constexpr signal& operator<<=(const T& value)
		{
			this->value <<= value;
			return *this;
		}

		constexpr signal& operator>>=(const T& value)
		{
			this->value >>= value;
			return *this;
		}

		void addListener(const std::function<void(const T&)>& listener)
		{
			this->listeners.push_back(std::make_pair(ql::detail::signal_index++, listener));
		}

		void addListener(const std::function<void(void)>& listener)
		{
			this->voidListeners.push_back(std::make_pair(ql::detail::signal_index++, listener));
		}

		void emit()
		{
			this->fire_next_time = true;
		}

		void post_update()
		{
			if constexpr (ql::is_same<T, ql::empty_type>())
			{
				if (this->fire_next_time)
				{
					this->runListeners();
					this->fire_next_time = false;
				}
			}
			else
			{
				if (this->fire_next_time || this->value != this->value_before)
				{
					this->runListeners();
					this->value_before = this->value;
					this->fire_next_time = false;
				}
			}
		}
	};

	using subject = ql::signal<ql::empty_type>;
}	 // namespace ql
