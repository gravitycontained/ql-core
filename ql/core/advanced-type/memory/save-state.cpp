#include <ql/core/advanced-type/memory/save-state.hpp>

#include <ql/core/encryption/encryption.hpp>

#include <ql/core/file-system/file-system.hpp>

namespace ql
{
	void ql::save_state::clear()
	{
		this->string_collection.clear();
		this->ctr = 0u;
	}

	void ql::save_state::file_save(std::string path)
	{
		this->string_collection.finalize();
		auto str = this->string_collection.get_string();
		ql::filesys::write_data_file(str, path);
	}

	void ql::save_state::file_save(std::string path, const std::array<ql::u64, 4>& key)
	{
		this->string_collection.finalize();
		auto str = this->string_collection.get_string();
		str = ql::encrypt(str, key);
		ql::filesys::write_data_file(str, path);
	}

	void ql::save_state::finalize_string()
	{
		this->string_collection.finalize();
	}

	std::string ql::save_state::get_string() const
	{
		return this->string_collection.get_string();
	}

	std::string ql::save_state::get_finalized_string()
	{
		this->finalize_string();
		return this->string_collection.get_string();
	}

	std::string ql::save_state::get_next_string()
	{
		return this->string_collection.get_string(this->ctr++);
	}

	void ql::load_state::clear()
	{
		this->string_collection.clear();
		this->ctr = 0u;
	}

	void ql::load_state::file_load(std::string path)
	{
		this->ctr = 0u;
		auto str = ql::filesys::read_file(path);
		this->string_collection.set_string(str);
		if (!this->string_collection.read_info())
		{
			throw ql::exception("save_state: \"", path, "\" failed to load.");
		}
	}

	void ql::load_state::file_load(std::string path, const std::array<ql::u64, 4>& key)
	{
		this->ctr = 0u;
		auto str = ql::filesys::read_file(path);
		str = ql::decrypt(str, key);
		this->string_collection.set_string(str);
		if (!this->string_collection.read_info())
		{
			throw ql::exception("save_state: \"", path, "\" failed to load.");
		}
	}

	void ql::load_state::set_string(const std::string& str)
	{
		this->string_collection.set_string(str);
		if (!this->string_collection.read_info())
		{
			throw ql::exception("save_state::set_string: failed to load.");
		}
	}
}
