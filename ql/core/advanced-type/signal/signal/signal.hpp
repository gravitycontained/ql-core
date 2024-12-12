#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/signal/signal-update-manager/signal-update-manager.hpp>

#include <ql/core/type/type.hpp>

#include <ql/core/system/print/print.hpp>

#include <ql/core/injection/injection.hpp>

namespace ql
{
	template <typename T>
	struct signal
	{
		T value;
		T value_before;

		std::vector<std::pair<ql::size, std::function<void(const T&)>>> listeners;
		std::vector<std::pair<ql::size, std::function<void(void)>>> voidListeners;

		ql::signal_update_manager* update_manager = nullptr;

		bool fire_next_time = false;

		constexpr operator T&()
		{
			return this->value;
		}

		constexpr T& operator=(const T& newValue)
		{
			this->value = newValue;
			return *this;
		}

		constexpr operator const T&() const
		{
			return this->value;
		}

		constexpr const auto& operator()() const
		{
			return this->value;
		}

		constexpr auto& operator()()
		{
			return this->value;
		}

		constexpr void runListeners() const
		{
			for (const auto& [index, listener] : this->voidListeners)
			{
				if (this->update_manager && this->update_manager->cycle_allowed_store(index))
				{
					listener();
				}
			}

			for (const auto& [index, listener] : this->listeners)
			{
				if (this->update_manager && this->update_manager->cycle_allowed_store(index))
				{
					listener(this->value);
				}
			}
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

		void init_interaction(ql::signal_update_manager& update)
		{
			if (this->update_manager == nullptr)
			{
				this->update_manager = &update;
			}
		}

		void update(ql::signal_update_manager& update)
		{
			this->init_interaction(update);
		}

		void addListener(const std::function<void(const T&)>& listener)
		{
			if (this->update_manager)
			{
				auto index = this->update_manager->advance_count();
				this->listeners.push_back(std::make_pair(index, listener));
			}
		}

		void addListener(const std::function<void(void)>& listener)
		{
			if (this->update_manager)
			{
				auto index = this->update_manager->advance_count();
				this->voidListeners.push_back(std::make_pair(index, listener));
			}
		}

		void emit()
		{
			this->fire_next_time = true;
		}

		void update_phase_signal_run()
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

		void update_phase_signal_detect()
		{
			if (this->update_manager)
			{
				if constexpr (ql::is_same<T, ql::empty_type>())
				{
					if (this->fire_next_time)
					{
						this->update_manager->active = true;
					}
				}
				else
				{
					if (this->fire_next_time || this->value != this->value_before)
					{
						this->update_manager->active = true;
					}
				}
			}
		}
	};

	using subject = ql::signal<ql::empty_type>;
}	 // namespace ql
