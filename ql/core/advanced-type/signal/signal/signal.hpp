#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/signal/signal-update-manager/signal-update-manager.hpp>

#include <ql/core/type/type.hpp>

#include <ql/core/system/print/print.hpp>

#include <ql/core/injection/injection.hpp>

#include <ql/core/encryption/encryption.hpp>

#include <ql/graphic/sync/type/type.hpp>

namespace ql
{
	template <typename T>
	struct signal
	{
		struct
		{
			ql_sync;
			ql::injectable<ql::signal_update_manager> update_manager;
		} sync;

		T value;
		T value_before;

		std::vector<std::pair<ql::size, std::function<void(const T&)>>> listeners;
		std::vector<std::pair<ql::size, std::function<void(void)>>> voidListeners;

		bool fire_next_time = false;

		~signal()
		{
			ql::println(
				ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", ql::color::bright_gray, ql::string_left_spaced("destruct signal ", 24),
				ql::color::aqua, this, " ", ql::color::bright_blue, ql::type_name<T>()
			);
		}

		constexpr T& operator=(const T& newValue)
		{
			this->value = newValue;
			return *this;
		}

		constexpr signal() = default;

		constexpr signal(const signal<T>& other)
		{
			auto message = ql::to_string("ql::signal<", ql::type_name<T>(), ">: avoid signal copies");
			//throw std::runtime_error(message);
			ql::println(message);

			*this = other;
		}

		signal<T>& operator=(const signal<T>& other)
		{
			auto message = ql::to_string("ql::signal<", ql::type_name<T>(), ">: avoid signal copies");
			//throw std::runtime_error(message);
			ql::println(message);

			this->value = other.value;
			return *this;
		}

		constexpr signal(signal<T>&& other) = default;
		constexpr signal& operator=(signal<T>&& other) = default;

		constexpr signal& operator=(T&& newValue)
		{
			this->value = std::move(newValue);
			return *this;
		}

		constexpr T& get()
		{
			return this->value;
		}

		constexpr const T& get() const
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

		constexpr void runListeners()
		{
			for (const auto& [index, listener] : this->voidListeners)
			{
				if (this->sync.update_manager && this->sync.update_manager().cycle_allowed_store(index))
				{
					listener();
				}
			}

			for (const auto& [index, listener] : this->listeners)
			{
				if (this->sync.update_manager && this->sync.update_manager().cycle_allowed_store(index))
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

		constexpr signal& operator++()
		{
			++this->value;
			return *this;
		}

		constexpr signal& operator--()
		{
			--this->value;
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
			if (this->sync.update_manager)
			{
				auto index = this->sync.update_manager->advance_count();
				this->listeners.push_back(std::make_pair(index, listener));
			}
		}

		void addListener(const std::function<void(void)>& listener)
		{
			if (this->sync.update_manager)
			{
				auto index = this->sync.update_manager->advance_count();
				this->voidListeners.push_back(std::make_pair(index, listener));
			}
		}

		void removeListener(const std::function<void(const T&)>& listener)
		{
			if (this->listeners.empty())
				return;

			this->listeners.erase(
				std::remove_if(
					this->listeners.begin(), this->listeners.end(),
					[&](const auto& pair) { return pair.second.target<void(const T&)>() == listener.target<void(const T&)>(); }
				),
				this->listeners.end()
			);
		}

		void removeListener(const std::function<void(void)>& listener)
		{
			if (this->voidListeners.empty())
				return;

			this->voidListeners.erase(
				std::remove_if(
					this->voidListeners.begin(), this->voidListeners.end(),
					[&](const auto& pair) { return pair.second.target<void(void)>() == listener.target<void(void)>(); }
				),
				this->voidListeners.end()
			);
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

			else if (this->fire_next_time || this->value != this->value_before)
			{
				this->runListeners();
				this->value_before = this->value;
				this->fire_next_time = false;
			}
		}

		void update_phase_signal_detect()
		{
			if (this->sync.update_manager)
			{
				if constexpr (ql::is_same<T, ql::empty_type>())
				{
					if (this->fire_next_time)
						this->sync.update_manager->active = true;
				}
				else
					if (this->fire_next_time || this->value != this->value_before)
						this->sync.update_manager->active = true;
			}
		}
	};

	using subject = ql::signal<ql::empty_type>;
}	 // namespace ql
