#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

#include <ql/core/advanced-type/memory/string-collection.hpp>

#include <ql/core/transform/memory/memory.hpp>

#include <ql/core/system/exception/exception.hpp>

namespace ql
{
	struct save_state;
	struct load_state;

	namespace detail
	{
		template <typename T>
		concept has_save = requires(const T a, save_state& state) { a.save(state); };

		template <typename T>
		concept has_load = requires(T a, load_state& state) { a.load(state); };
	}
	template <typename T>
	constexpr bool has_save()
	{
		if constexpr (ql::is_container<T>() && ql::has_size<T>())
		{
			return ql::has_save<ql::container_subtype<T>>();
		}
		else
		{
			return ql::detail::has_save<T>;
		}
	}

	template <typename T>
	constexpr bool has_load()
	{
		if constexpr (ql::is_container<T>() && ql::has_resize<T>())
		{
			return ql::has_load<ql::container_subtype<T>>();
		}
		else
		{
			return ql::detail::has_load<T>;
		}
	}

	struct save_state
	{
		ql::string_collection string_collection;
		ql::size ctr = 0u;

		save_state()
		{
		}

		template <typename... Ts>
		save_state(const Ts&... saves)
		{
			this->save(saves...);
		}

		QL_SOURCE void clear();
		QL_SOURCE void file_save(std::string path);
		QL_SOURCE void file_save(std::string path, const std::array<ql::u64, 4>& key);
		QL_SOURCE void finalize_string();
		QL_SOURCE std::string get_string() const;
		QL_SOURCE std::string get_finalized_string();
		QL_SOURCE std::string get_next_string();

		template <typename T>
		void save_single(const T& data)
		{
			if constexpr (ql::is_standard_string_type<T>())
			{
				this->string_collection.add_string(data);
			}
			else if constexpr (ql::has_save<T>())
			{
				if constexpr (ql::is_container<T>() && ql::has_size<T>())
				{
					this->save_single(data.size());
					for (auto& i : data)
					{
						this->save_single(i);
					}
				}
				else
				{
					data.save(*this);
				}
			}
			else if constexpr (ql::has_data<T>() && ql::has_size<T>())
			{
				if constexpr (ql::is_std_array_type<T>())
				{
					auto str = ql::heap_memory_to_string(data);
					this->string_collection.add_string(str);
				}
				else
				{
					this->save_single(data.size());
					auto str = ql::heap_memory_to_string(data);
					this->string_collection.add_string(str);
				}
			}
			else
			{
				auto str = ql::stack_memory_to_string(data);
				this->string_collection.add_string(str);
			}
		}

		template <typename... Ts>
		void save(const Ts&... data)
		{
			(this->save_single(data), ...);
		}

		template <typename C>
		requires (ql::is_container<C>())
		void save_container(const C& data)
		{
			this->save(data.size());
			for (auto& i : data)
			{
				this->save(i);
			}
		}
	};

	struct load_state
	{
		ql::string_collection string_collection;
		ql::size ctr = 0u;

		load_state()
		{
		}

		template <typename... Ts>
		load_state(const Ts&... loads)
		{
			this->load(loads...);
		}

		QL_SOURCE void clear();
		QL_SOURCE void file_load(std::string path);
		QL_SOURCE void file_load(std::string path, const std::array<ql::u64, 4>& key);
		QL_SOURCE void set_string(const std::string& str);

		template <typename T>
		void load_single(T& data)
		{
			if (this->ctr >= this->string_collection.size())
			{
				throw ql::exception("save_state: trying to load resource #", this->ctr, " but size is only ",
														 this->string_collection.size());
			}
			if constexpr (ql::is_standard_string_type<T>())
			{
				data = this->string_collection.get_string(this->ctr);
				++this->ctr;
			}
			else if constexpr (ql::has_load<T>())
			{
				if constexpr (ql::is_container<T>() && ql::has_size<T>())
				{
					ql::size size;
					this->load_single(size);
					data.resize(size);
					for (auto& i : data)
					{
						this->load_single(i);
					}
				}
				else
				{
					data.load(*this);
				}
			}
			else if constexpr (ql::has_data<T>() && ql::has_size<T>())
			{
				if constexpr (ql::is_std_array_type<T>())
				{
					ql::string_to_stack_memory(this->string_collection.get_string(this->ctr), data);
				}
				else
				{
					ql::size size;
					this->load_single(size);
					data.resize(size);
					ql::string_to_heap_memory(this->string_collection.get_string(this->ctr), data);
				}
				++this->ctr;
			}
			else
			{
				ql::string_to_stack_memory(this->string_collection.get_string(this->ctr), data);
				++this->ctr;
			}
		}

		template <typename... Ts>
		void load(Ts&... data)
		{
			(this->load_single(data), ...);
		}

		template <typename C>
		requires (ql::is_container<C>())
		void load_container(C& data)
		{
			ql::size size;
			this->load(size);
			data.resize(size);
			for (ql::size i = 0u; i < size; ++i)
			{
				this->load(data[i]);
			}
		}
	};
}