#pragma once

#include <ql/core/file-system/path/path.hpp>
#include <ql/core/file-system/paths/paths.hpp>
#include <ql/core/file-system/action/action.hpp>

#include <ql/core/string/string.hpp>
#include <ql/core/system/print/print.hpp>

#include <fstream>

namespace ql::filesys
{
	ql::filesys::path& ql::filesys::path::operator=(const std::wstring_view& str)
	{
		std::wstring wstr(str);
		return this->operator=(std::string_view{ql::wstring_to_utf8(wstr)});
	}

	ql::filesys::path& ql::filesys::path::operator=(const std::string_view& str)
	{
		this->m_string.clear();

		bool seperator = false;
		for (ql::u32 i = 0u; i < str.size(); ++i)
		{
			seperator = false;
			while (i < str.size() && (str[i] == '\\' || str[i] == '/'))
			{
				seperator = true;
				++i;
			}

			if (seperator)
			{
				this->m_string.push_back('/');
			}
			if (i < str.size())
			{
				this->m_string.push_back(str[i]);
			}
		}
		return *this;
	}

	ql::filesys::path& ql::filesys::path::operator=(const std::wstring& str)
	{
		return this->operator=(std::string_view{ql::wstring_to_utf8(str)});
	}

	ql::filesys::path& ql::filesys::path::operator=(const std::string& str)
	{
		return this->operator=(std::string_view{str.c_str()});
	}

	ql::filesys::path& ql::filesys::path::operator=(const char* str)
	{
		return this->operator=(std::string_view{str});
	}

	ql::filesys::path& ql::filesys::path::operator=(const wchar_t* str)
	{
		return this->operator=(std::wstring_view{str});
	}

	path& ql::filesys::path::operator=(const std::filesystem::directory_entry& entry)
	{
		this->m_string = entry.path().string();
		for (ql::u32 i = 0u; i < this->m_string.size(); ++i)
		{
			if (this->m_string[i] == '\\')
			{
				this->m_string[i] = '/';
			}
		}

		this->m_is_file = entry.is_regular_file() || entry.is_block_file() || entry.is_character_file();
		this->m_is_directory = entry.is_directory();
		this->m_exists = entry.exists();
		return *this;
	}

	bool ql::filesys::path::operator==(const path& other) const
	{
		std::string name1 = this->m_string;
		std::string name2 = other.m_string;

		if (this->is_directory() && name1.back() != '/')
		{
			name1.append("/");
		}
		if (other.is_directory() && name2.back() != '/')
		{
			name2.append("/");
		}
		return ql::string_equals_ignore_case(name1, name2);
	}

	bool ql::filesys::path::file_content_equals(const path& other) const
	{
		if (this->is_file() && other.is_file())
		{
			auto fs1 = this->file_size();
			auto fs2 = other.file_size();

			if (fs1 != fs2)
			{
				return false;
			}

			auto str1 = this->read();
			auto str2 = other.read();
			return str1 == str2;
		}
		return false;
	}

	bool ql::filesys::path::file_equals(const path& other) const
	{
		if (this->is_file() && other.is_file())
		{
			auto name1 = this->get_full_file_name();
			auto name2 = other.get_full_file_name();

			if (name1 != name2)
			{
				return false;
			}
			auto fs1 = this->file_size();
			auto fs2 = other.file_size();

			if (fs1 != fs2)
			{
				return false;
			}
			auto time1 = this->last_write_time();
			auto time2 = other.last_write_time();

			if (time1 != time2)
			{
				return false;
			}
			auto str1 = this->read();
			auto str2 = other.read();
			return str1 == str2;
		}
		return false;
	}

	bool ql::filesys::path::file_equals_no_read(const path& other) const
	{
		if (this->is_file() && other.is_file())
		{
			auto name1 = this->get_full_file_name();
			auto name2 = other.get_full_file_name();

			if (name1 != name2)
			{
				return false;
			}
			auto fs1 = this->file_size();
			auto fs2 = other.file_size();

			if (fs1 != fs2)
			{
				return false;
			}
			auto time1 = this->last_write_time();
			auto time2 = other.last_write_time();

			return time1 == time2;
		}
		return false;
	}

	ql::filesys::path ql::filesys::path::current_path()
	{
		return std::filesystem::current_path().string();
	}

	void ql::filesys::path::set_current_path()
	{
		*this = ql::filesys::path::current_path();
	}

	const char* ql::filesys::path::data() const
	{
		return this->m_string.data();
	}

	const char* ql::filesys::path::c_str() const
	{
		return this->m_string.c_str();
	}

	std::string ql::filesys::path::to_string() const
	{
		return this->m_string;
	}

	ql::filesys::path::operator std::string() const
	{
		return this->m_string;
	}

	bool ql::filesys::path::empty() const
	{
		return this->m_string.empty();
	}

	void ql::filesys::path::clear()
	{
		this->m_string.clear();
	}

	void ql::filesys::path::clear_file_content()
	{
		if (this->is_file())
		{
			std::ofstream ofs;
			ofs.open(this->to_string(), std::ofstream::out | std::ofstream::trunc);
			ofs.close();
		}
	}

	void ql::filesys::path::create() const
	{
		if (this->exists() || this->empty())
		{
			return;
		}
		if (this->is_file())
		{
			std::ofstream file(this->to_string());
			file.close();
		}
		else if (this->is_directory())
		{
			std::filesystem::create_directory(this->to_string());
		}
	}

	ql::filesys::path ql::filesys::path::make_file(std::string file_name) const
	{
		auto path = this->to_string();
		if (this->is_file())
		{
			path = this->get_parent_branch();
		}
		auto path_slash = path.back() == '/';
		auto file_slash = file_name.front() == '/';
		if (path_slash && file_slash)
		{
			path.pop_back();
			path += file_name;
		}
		else if (!path_slash && !file_slash)
		{
			path += "/" + file_name;
		}
		else
		{
			path += file_name;
		}
		ql::filesys::create(path);
		return path;
	}

	std::string ql::filesys::path::read() const
	{
		if (this->empty())
		{
			return "";
		}

		return ql::filesys::read_file(this->to_string());
	}

	void ql::filesys::path::write(const std::string& data) const
	{
		std::ofstream file(this->to_string(), std::ios::binary);
		file << data;
		file.close();
	}

	void ql::filesys::path::writeUtf8(const std::string& data) const
	{
		ql::filesys::write_to_file(data, this->to_string());
	}

	std::filesystem::file_time_type ql::filesys::path::last_write_time() const
	{
		return std::filesystem::last_write_time(this->to_string());
	}

	ql::u64 ql::filesys::path::file_size() const
	{
		return std::filesystem::file_size(this->to_string());
	}

	ql::u64 ql::filesys::path::file_size_recursive() const
	{
		if (this->is_file())
		{
			return this->file_size();
		}

		ql::u64 result = 0u;
		auto paths = this->list_current_directory_tree();
		for (auto& path : paths)
		{
			if (path.is_file())
			{
				result += path.file_size();
			}
		}
		return result;
	}

	bool ql::filesys::path::file_content_equals(const path& other)
	{
		std::wifstream file1(this->to_string(), std::wifstream::ate | std::wifstream::binary);
		std::wifstream file2(other.to_string(), std::wifstream::ate | std::wifstream::binary);

		if (file1.tellg() != file2.tellg())
		{
			return false;
		}

		file1.seekg(0);
		file2.seekg(0);

		std::istreambuf_iterator<wchar_t> begin1{file1};
		std::istreambuf_iterator<wchar_t> begin2{file2};

		return std::equal(begin1, std::istreambuf_iterator<wchar_t>(), begin2);
	}

	bool ql::filesys::path::has_root(const path& other) const
	{
		return this->m_string.starts_with(other.ensured_directory_backslash().to_string());
	}

	bool ql::filesys::path::exists() const
	{
		this->update();
		return this->m_exists;
	}

	bool ql::filesys::path::is_file() const
	{
		this->update();
		return this->m_is_file;
	}

	bool ql::filesys::path::is_directory() const
	{
		this->update();
		return this->m_is_directory;
	}

	bool ql::filesys::path::has_extension() const
	{
		if (!this->is_file() || this->empty())
		{
			return false;
		}
		for (auto it = this->m_string.crbegin(); it != this->m_string.crend(); ++it)
		{
			if (*it == '/')
			{
				return false;
			}
			if (*it == '.')
			{
				return true;
			}
		}
		return false;
	}

	std::string ql::filesys::path::get_file_extension() const
	{
		return std::string{this->get_file_extension_view()};
	}

	std::string ql::filesys::path::get_name() const
	{
		return std::string{this->get_name_view()};
	}

	std::string ql::filesys::path::get_full_name(bool add_slash_on_directory) const
	{
		if (this->empty())
		{
			return "";
		}
		if (this->is_file())
		{
			return this->get_full_file_name();
		}
		else if (this->is_directory())
		{
			auto str = this->get_directory_name();
			if (add_slash_on_directory && str.back() != '/')
			{
				str.push_back('/');
			}
			return str;
		}
		return "";
	}

	std::string ql::filesys::path::get_file_name() const
	{
		return std::string{this->get_file_name_view()};
	}

	std::string ql::filesys::path::get_full_file_name() const
	{
		return std::string{this->get_full_file_name_view()};
	}

	std::string ql::filesys::path::get_directory_name() const
	{
		return std::string{this->get_directory_name_view()};
	}

	std::string_view ql::filesys::path::get_file_extension_view() const
	{
		if (!this->is_file() || this->empty())
		{
			return "";
		}

		auto it = this->m_string.cend() - 1;
		for (; it != this->m_string.cbegin(); --it)
		{
			if (*it == '.')
			{
				++it;
				break;
			}
		}
		auto result = std::string_view(
				this->m_string.data() + std::distance(this->m_string.cbegin(), it), std::distance(it, this->m_string.cend())
		);
		return result;
	}

	std::string_view ql::filesys::path::get_name_view() const
	{
		if (this->empty())
		{
			return "";
		}
		if (this->is_file())
		{
			return this->get_file_name_view();
		}
		else if (this->is_directory())
		{
			return this->get_directory_name_view();
		}
		return "";
	}

	std::string_view ql::filesys::path::get_full_file_name_view() const
	{
		if (!this->is_file() || this->empty())
		{
			return "";
		}

		auto it = this->m_string.cend() - 1;
		for (; it != this->m_string.cbegin(); --it)
		{
			if (*it == '/')
			{
				++it;
				break;
			}
		}
		return std::string_view(
				this->m_string.data() + std::distance(this->m_string.cbegin(), it), std::distance(it, this->m_string.cend())
		);
	}

	std::string_view ql::filesys::path::get_file_name_view() const
	{
		if (!this->is_file() || this->empty())
		{
			return "";
		}

		auto file_name = this->get_full_file_name_view();

		auto it = file_name.cend() - 1;
		for (; it != file_name.cbegin(); --it)
		{
			if (*it == '.')
			{
				break;
			}
		}
		return std::string_view(file_name.cbegin(), it);
	}

	std::string_view ql::filesys::path::get_directory_name_view() const
	{
		if (!this->is_directory() || this->empty())
		{
			return "";
		}

		bool end_slash = false;
		auto it = this->m_string.cend() - 1;
		if (it != this->m_string.cbegin() && *it == '/')
		{
			--it;
			end_slash = true;
		}

		for (; it != this->m_string.cbegin(); --it)
		{
			if (*it == '/')
			{
				++it;
				break;
			}
		}
		return std::string_view(
				this->m_string.data() + std::distance(this->m_string.cbegin(), it), std::distance(it, this->m_string.cend() - end_slash)
		);
	}

	ql::filesys::path ql::filesys::path::with_file_name(std::string file_name) const
	{
		ql::filesys::path copy = ql::to_string(this->get_parent_branch().to_string(), file_name, ".", this->get_file_extension());
		return copy;
	}

	ql::filesys::path ql::filesys::path::with_full_file_name(std::string file_name) const
	{
		ql::filesys::path copy = ql::to_string(this->get_parent_branch().to_string(), file_name);
		return copy;
	}

	ql::filesys::path ql::filesys::path::with_extension(std::string extension) const
	{
		ql::filesys::path copy = ql::to_string(this->get_parent_branch().to_string(), this->get_file_name(), ".", extension);
		return copy;
	}

	bool ql::filesys::path::extension_equals(const std::string_view& str) const
	{
		if (str.front() == '.' && str.size())
		{
			return this->get_file_extension_view() == str.substr(1, str.size() - 1);
		}
		return this->get_file_extension_view() == str;
	}

	bool ql::filesys::path::extension_equals(const char* str) const
	{
		return this->extension_equals(std::string_view{str});
	}

	bool ql::filesys::path::extension_equals(const std::string& str) const
	{
		return this->extension_equals(std::string_view{str});
	}

	bool ql::filesys::path::extension_contains(const std::string_view& str) const
	{
		auto extension = this->get_file_extension_view();
		for (ql::i32 i = 0; i < ql::signed_cast(extension.size()) - ql::signed_cast(str.size()) + 1; ++i)
		{
			if (extension.substr(i, str.size()) == str)
			{
				return true;
			}
		}
		return false;
	}

	bool ql::filesys::path::extension_contains(const char* str) const
	{
		return this->extension_contains(std::string_view{str});
	}

	bool ql::filesys::path::extension_contains(const std::string& str) const
	{
		return this->extension_contains(std::string_view{str});
	}

	bool ql::filesys::path::extension_matches(const std::string& regex) const
	{
		const std::regex reg{regex};
		return std::regex_search(this->get_file_extension(), reg);
	}

	bool ql::filesys::path::extension_matches(const std::regex& regex) const
	{
		return std::regex_match(this->get_file_extension(), regex);
	}

	bool ql::filesys::path::file_name_equals(const std::string_view& str) const
	{
		return this->get_file_name_view() == str;
	}

	bool ql::filesys::path::file_name_equals(const char* str) const
	{
		return this->file_name_equals(std::string_view{str});
	}

	bool ql::filesys::path::file_name_equals(const std::string& str) const
	{
		return this->file_name_equals(std::string_view{str});
	}

	bool ql::filesys::path::file_name_contains(const std::string_view& str) const
	{
		auto name = this->get_file_name_view();
		for (ql::i32 i = 0; i < ql::signed_cast(name.size()) - ql::signed_cast(str.size()) + 1; ++i)
		{
			if (name.substr(i, str.size()) == str)
			{
				return true;
			}
		}
		return false;
	}

	bool ql::filesys::path::file_name_contains(const char* str) const
	{
		return this->file_name_contains(std::string_view{str});
	}

	bool ql::filesys::path::file_name_contains(const std::string& str) const
	{
		return this->file_name_contains(std::string_view{str});
	}

	bool ql::filesys::path::file_name_matches(const std::string& regex) const
	{
		const std::regex reg{regex};
		return std::regex_search(this->get_file_name(), reg);
	}

	bool ql::filesys::path::file_name_matches(const std::regex& regex) const
	{
		return std::regex_match(this->get_file_name(), regex);
	}

	bool ql::filesys::path::full_file_name_equals(const std::string_view& str) const
	{
		return this->get_full_file_name_view() == str;
	}

	bool ql::filesys::path::full_file_name_equals(const char* str) const
	{
		return this->full_file_name_equals(std::string_view{str});
	}

	bool ql::filesys::path::full_file_name_equals(const std::string& str) const
	{
		return this->full_file_name_equals(std::string_view{str});
	}

	bool ql::filesys::path::full_file_name_contains(const std::string_view& str) const
	{
		auto name = this->get_full_file_name_view();
		for (ql::i32 i = 0; i < ql::signed_cast(name.size()) - ql::signed_cast(str.size()) + 1; ++i)
		{
			if (name.substr(i, str.size()) == str)
			{
				return true;
			}
		}
		return false;
	}

	bool ql::filesys::path::full_file_name_contains(const char* str) const
	{
		return this->full_file_name_contains(std::string_view{str});
	}

	bool ql::filesys::path::full_file_name_contains(const std::string& str) const
	{
		return this->full_file_name_contains(std::string_view{str});
	}

	bool ql::filesys::path::full_file_name_matches(const std::string& regex) const
	{
		const std::regex reg{regex};
		return std::regex_search(this->get_full_file_name(), reg);
	}

	bool ql::filesys::path::full_file_name_matches(const std::regex& regex) const
	{
		return std::regex_match(this->get_full_file_name(), regex);
	}

	bool ql::filesys::path::name_equals(const std::string_view& str) const
	{
		auto name = this->get_name_view();
		if (this->is_directory())
		{
			auto off = ql::size{};
			auto size = str.size();
			if (str.front() == '/')
			{
				++off;
			}
			if (str.back() == '/')
			{
				--size;
			}

			if (size > off)
			{
				return name == str.substr(off, size);
			}
		}
		return name == str;
	}

	bool ql::filesys::path::name_equals(const char* str) const
	{
		return this->name_equals(std::string_view{str});
	}

	bool ql::filesys::path::name_equals(const std::string& str) const
	{
		return this->name_equals(std::string_view{str});
	}

	bool ql::filesys::path::name_contains(const std::string_view& str) const
	{
		auto name = this->get_name_view();
		for (ql::i32 i = 0; i < ql::signed_cast(name.size()) - ql::signed_cast(str.size()) + 1; ++i)
		{
			if (name.substr(i, str.size()) == str)
			{
				return true;
			}
		}
		return false;
	}

	bool ql::filesys::path::name_contains(const char* str) const
	{
		return this->name_contains(std::string_view{str});
	}

	bool ql::filesys::path::name_contains(const std::string& str) const
	{
		return this->name_contains(std::string_view{str});
	}

	bool ql::filesys::path::name_matches(const std::string& regex) const
	{
		const std::regex reg{regex};
		return std::regex_search(this->get_name(), reg);
	}

	bool ql::filesys::path::name_matches(const std::regex& regex) const
	{
		return std::regex_match(this->get_name(), regex);
	}

	void ql::filesys::path::rename(const ql::filesys::path& new_name)
	{
		std::filesystem::rename(this->to_string(), new_name.to_string());
		this->m_string = new_name;
	}

	void ql::filesys::path::set_file_name(const std::string& new_name)
	{
		auto p = this->get_parent_branch().to_string();
		if (p.back() != '/')
		{
			p.push_back('/');
		}
		auto string = p + new_name + "." + this->get_file_extension();
		std::filesystem::rename(this->to_string(), string);
		this->m_string = string;
	}

	void ql::filesys::path::set_file_extension_name(const std::string& new_extension)
	{
		auto p = this->get_parent_branch().to_string();
		if (p.back() != '/')
		{
			p.push_back('/');
		}
		auto string = this->to_string() + p + this->get_file_name() + "." + new_extension;
		std::filesystem::rename(this->to_string(), string);
		this->m_string = string;
	}

	void ql::filesys::path::set_full_file_name(const std::string& new_file)
	{
		auto p = this->get_parent_branch().to_string();
		if (p.back() != '/')
		{
			p.push_back('/');
		}
		auto string = this->to_string() + p + new_file;
		std::filesystem::rename(this->to_string(), string);
		this->m_string = string;
	}

	void ql::filesys::path::remove() const
	{
		if (!this->exists())
		{
			ql::println("ql::filesys::path::remove: ", this->to_string(), " doesn't exist");
			return;
		}
		std::filesystem::remove_all(this->to_string());
	}

	void ql::filesys::path::encrypt(const ql::filesys::path& destination, const std::string& key, ql::aes::mode mode) const
	{
		if (this->is_file())
		{
			auto content = this->read();
			ql::encrypt_keep_size(content, key, mode);
			ql::write_data_file(content, destination);
		}
	}

	void ql::filesys::path::decrypt(const ql::filesys::path& destination, const std::string& key, ql::aes::mode mode) const
	{
		if (this->is_file())
		{
			auto content = this->read();
			ql::decrypt_keep_size(content, key, mode);
			ql::write_data_file(content, destination);
		}
	}

	void ql::filesys::path::copy(const ql::filesys::path& path_destination) const
	{
		if (!this->exists())
		{
			ql::println("ql::filesys::path::copy: ", this->to_string(), " doesn't exist");
			return;
		}
		path_destination.ensure_branches_exist();
		if (path_destination.is_directory())
		{
			if (!path_destination.exists())
			{
				path_destination.create();
			}
			std::filesystem::copy(this->to_string(), path_destination.to_string(), std::filesystem::copy_options::recursive);
		}
		else
		{
			std::filesystem::copy(this->to_string(), path_destination.to_string(), std::filesystem::copy_options::recursive);
		}
	}

	void ql::filesys::path::copy_overwrite(const ql::filesys::path& path_destination) const
	{
		if (!this->exists())
		{
			ql::println("ql::filesys::path::copy_overwrite: ", this->to_string(), " doesn't exist");
			return;
		}
		if (path_destination.is_directory())
		{
			if (!path_destination.exists())
			{
				path_destination.create();
			}
			std::filesystem::copy(
					this->to_string(), path_destination.to_string(),
					std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
			);
		}
		else
		{
			std::filesystem::copy(
					this->to_string(), path_destination.to_string(),
					std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
			);
		}
	}

	void ql::filesys::path::move(const ql::filesys::path& path_destination) const
	{
		if (!this->exists())
		{
			ql::println("ql::filesys::path::move: ", this->to_string(), " doesn't exist");
			return;
		}
		this->copy(path_destination);
		this->remove();
	}

	void ql::filesys::path::move_overwrite(const ql::filesys::path& path_destination) const
	{
		if (!this->exists())
		{
			ql::println("ql::filesys::path::move_overwrite: ", this->to_string(), " doesn't exist");
			return;
		}
		this->copy_overwrite(path_destination);
		this->remove();
	}

	void ql::filesys::path::move_and_apply_path(const ql::filesys::path& path_destination)
	{
		if (!this->exists())
		{
			ql::println("ql::filesys::path::move_and_apply_path: ", this->to_string(), " doesn't exist");
			return;
		}
		this->move(path_destination);
		*this = path_destination;
	}

	void ql::filesys::path::move_overwrite_and_apply_path(const ql::filesys::path& path_destination)
	{
		if (!this->exists())
		{
			ql::println("ql::filesys::path::move_overwrite_and_apply_path: ", this->to_string(), " doesn't exist");
			return;
		}
		this->move_overwrite(path_destination);
		*this = path_destination;
	}

	ql::size ql::filesys::path::branch_size() const
	{
		ql::size ctr = 0u;
		for (auto& i : this->m_string)
		{
			if (i == '/')
			{
				++ctr;
			}
		}
		if (this->is_directory() && this->m_string.back() != '/')
		{
			++ctr;
		}
		return ctr;
	}

	ql::filesys::path ql::filesys::path::get_branch_at(ql::size index) const
	{
		ql::u32 ctr = 0u;
		auto it = this->m_string.cbegin();
		for (; it != this->m_string.cend(); ++it)
		{
			if (*it == '/' && (ctr++ == index))
			{
				++it;
				break;
			}
		}
		return {std::string(this->m_string.cbegin(), it)};
	}

	ql::filesys::paths ql::filesys::path::get_branches() const
	{
		ql::filesys::paths result;

		auto it = this->m_string.cbegin();
		for (; it != this->m_string.cend(); ++it)
		{
			if (*it == '/')
			{
				auto string = std::string(this->m_string.cbegin(), it);
				string.push_back('/');
				result.push_back(string);
			}
		}
		if (this->is_directory() && this->m_string.back() != '/')
		{
			result.push_back(*this);
			result.back().append('/');
		}
		return result;
	}

	ql::filesys::path ql::filesys::path::get_branch_earlier(ql::u32 n) const
	{
		if (this->empty() || n == 0u)
		{
			return *this;
		}

		auto it = this->m_string.cend() - 1;
		if (this->is_directory() && *it == '/')
		{
			--it;
		}
		for (; it != this->m_string.cbegin(); --it)
		{
			if (*it == '/')
			{
				--n;
				if (!n)
				{
					++it;
					break;
				}
			}
		}
		return {std::string(this->m_string.cbegin(), it)};
	}

	ql::filesys::path ql::filesys::path::get_parent_branch() const
	{
		if (this->empty())
		{
			return *this;
		}
		auto it = this->m_string.cend() - 1;
		if (this->is_directory() && *it == '/')
		{
			--it;
		}
		for (; it != this->m_string.cbegin(); --it)
		{
			if (*it == '/')
			{
				++it;
				break;
			}
		}
		return {std::string(this->m_string.cbegin(), it)};
	}

	ql::filesys::path ql::filesys::path::get_last_branch() const
	{
		return this->get_branch_at(this->branch_size() - 1);
	}

	std::vector<std::string> ql::filesys::path::get_branch_names() const
	{
		std::vector<std::string> result;

		auto it = this->m_string.cbegin();
		auto it_before = it;

		for (; it != this->m_string.cend(); ++it)
		{
			if (*it == '/')
			{
				result.push_back(std::string(it_before, it));
				it_before = it + 1;
			}
		}
		return result;
	}

	ql::filesys::path ql::filesys::path::with_branch(ql::size index, std::string branch_name) const
	{
		auto copy = *this;
		copy.set_branch(index, branch_name);
		return copy;
	}

	void ql::filesys::path::set_branch(ql::size index, std::string branch_name)
	{
		ql::size ctr = 0u;
		for (ql::size i = 0u; i < this->m_string.length(); ++i)
		{
			if (this->m_string[i] == '/')
			{
				++ctr;
				if (ctr == index || !index)
				{
					if (!index)
					{
						i = 0u;
					}
					auto end = i + 1;
					while (true)
					{
						if (end >= this->m_string.length())
						{
							return;
						}
						if (this->m_string[end] == '/')
						{
							break;
						}
						++end;
					}
					if (index)
					{
						auto string_a = this->m_string.substr(0u, i + 1u);
						auto string_b = this->m_string.substr(end);
						this->m_string = string_a + branch_name + string_b;
					}
					else
					{
						auto string_b = this->m_string.substr(end);
						this->m_string = branch_name + string_b;
					}
					return;
				}
			}
		}
	}

	ql::filesys::path ql::filesys::path::subpath(ql::size off, ql::size size) const
	{
		ql::u32 ctr = 0u;
		auto begin = this->m_string.cbegin();
		for (; begin != this->m_string.cend(); ++begin)
		{
			if (*begin == '/' && (ctr++ == off))
			{
				++begin;
				break;
			}
		}
		ctr = 0u;
		auto end = begin;
		for (; end != this->m_string.cend(); ++end)
		{
			if (*end == '/' && (ctr++ == size))
			{
				++end;
				break;
			}
		}

		return {std::string(begin, end)};
	}

	void ql::filesys::path::ensure_branches_exist() const
	{
		if (this->exists())
		{
			return;
		}

		auto branches = this->get_branches();
		for (auto& i : branches)
		{
			if (!i.exists())
			{
				i.create();
			}
		}
	}

	void ql::filesys::path::ensure_directory_backslash()
	{
		if (this->is_directory())
		{
			this->ensure_backslash();
		}
	}

	void ql::filesys::path::ensure_backslash()
	{
		if (this->m_string.back() != '/')
		{
			this->m_string.push_back('/');
		}
	}

	ql::filesys::path ql::filesys::path::ensured_directory_backslash() const
	{
		auto copy = *this;
		copy.ensure_directory_backslash();
		return copy;
	}

	ql::filesys::path ql::filesys::path::ensured_backslash() const
	{
		auto copy = *this;
		copy.ensure_backslash();
		return copy;
	}

	bool ql::filesys::path::is_root() const
	{
		return this->branch_size() == ql::size{1};
	}

	path& ql::filesys::path::go_root()
	{
		return *this = this->get_branch_at(ql::u32{0});
	}

	bool ql::filesys::path::go_directories_back(ql::u32 steps)
	{
		if (this->empty())
		{
			return false;
		}
		auto size = this->branch_size() - 1;
		auto level = (steps > size ? ql::size{} : size - steps);
		if (level != size)
		{
			*this = this->get_branch_at(static_cast<ql::u32>(level));
			return true;
		}
		return false;
	}

	bool ql::filesys::path::go_directory_back()
	{
		return this->go_directories_back(ql::size{1});
	}

	path& ql::filesys::path::go_into_directory(const std::string& directory_name)
	{
		if (this->m_string.back() != '/' && directory_name.front() != '/')
		{
			this->m_string.append("/");
		}
		else if (this->m_string.back() == '/' && directory_name.front() == '/')
		{
			this->m_string.pop_back();
		}
		this->m_string.append(directory_name);

		if (this->m_string.back() != '/')
		{
			this->m_string.push_back('/');
		}
		this->m_exists = false;
		return *this;
	}

	path& ql::filesys::path::go_into_file(const std::string& file_name)
	{
		if (this->m_string.back() != '/' && file_name.front() != '/')
		{
			this->m_string.append("/");
		}
		else if (this->m_string.back() == '/' && file_name.front() == '/')
		{
			this->m_string.pop_back();
		}
		this->m_string.append(file_name);
		return *this;
	}

	path& ql::filesys::path::go_into(const std::string& entry)
	{
		auto dir = *this;
		dir.go_into_directory(entry);

		if (dir.exists())
		{
			return *this = dir;
		}

		auto file = *this;
		file.go_into_file(entry);
		if (file.exists())
		{
			return *this = file;
		}

		this->append(entry);
		return *this;
	}

	path& ql::filesys::path::cd(const std::string& directory_name)
	{
		this->go_into_directory(directory_name);
		return *this;
	}

	void ql::filesys::path::append(const std::string& string)
	{
		this->m_string.append(string);
	}

	void ql::filesys::path::append(char c)
	{
		this->m_string += c;
	}

	path ql::filesys::path::appended(const std::string& string) const
	{
		auto copy = *this;
		copy.append(string);
		return copy;
	}

	path ql::filesys::path::appended(char c) const
	{
		auto copy = *this;
		copy.append(c);
		return copy;
	}

	ql::size ql::filesys::path::directory_content_count() const
	{
		return std::distance(std::filesystem::directory_iterator(this->to_string()), std::filesystem::directory_iterator{});
	}

	ql::filesys::paths ql::filesys::path::list_current_directory() const
	{
		ql::filesys::paths list;
		auto str = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(str, std::filesystem::directory_options::skip_permission_denied))
		{
			list.push_back({i.path().string()});
		}
		return {list};
	}

	ql::filesys::paths ql::filesys::path::list_current_directory_include_self() const
	{
		ql::filesys::paths list;
		list.push_back(*this);
		auto str = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(str, std::filesystem::directory_options::skip_permission_denied))
		{
			list.push_back({i.path().string()});
		}
		return {list};
	}

	ql::filesys::paths ql::filesys::path::list_current_directory_tree() const
	{
		if (!this->exists())
		{
			return {};
		}
		ql::filesys::paths list;
		auto str = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::recursive_directory_iterator(str, std::filesystem::directory_options::skip_permission_denied))
		{
			list.push_back({i.path().string()});
		}
		return {list};
	}

	ql::filesys::paths ql::filesys::path::list_current_directory_tree_include_self() const
	{
		if (!this->exists())
		{
			return {};
		}
		ql::filesys::paths list;
		list.push_back(*this);
		auto str = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::recursive_directory_iterator(str, std::filesystem::directory_options::skip_permission_denied))
		{
			list.push_back({i.path().string()});
		}
		return {list};
	}

	void ql::filesys::path::print_current_directory() const
	{
		auto list = this->list_current_directory();
		list.print_tree();
	}

	void ql::filesys::path::print_tree() const
	{
		auto str = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();

		std::vector<ql::size> widths;
		if (this->is_root())
		{
			widths.push_back(0);
		}

		ql::size depth_before = this->branch_size() + 1;

		for (ql::size i = 0u; i < depth_before - 1; ++i)
		{
			for (ql::u32 i = 0u; i < widths.size(); ++i)
			{
				ql::print(ql::string_repeat(' ', widths[i] + 1));
				if (i == widths.size() - 1)
				{
					ql::print("|");
				}
				else
				{
					ql::print("|");
				}
			}
			auto str = this->get_branch_at(i);
			ql::print("_ ");
			ql::print(str.get_name());
			widths.push_back(str.get_name().length());
			ql::println();
		}

		for (auto i : std::filesystem::recursive_directory_iterator(str, std::filesystem::directory_options::skip_permission_denied))
		{
			auto path = ql::filesys::path(i.path().string());
			auto depth = path.branch_size();

			while (depth_before < depth)
			{
				if (depth_before)
				{
					auto name = path.get_branch_at(static_cast<ql::u32>(depth_before - 1)).get_name();
					widths.push_back(name.size());
				}
				++depth_before;
			}
			while (depth_before > depth)
			{
				if (depth_before)
				{
					widths.pop_back();
				}
				--depth_before;
			}
			for (ql::u32 i = 0u; i < widths.size(); ++i)
			{
				ql::print(ql::string_repeat(' ', widths[i] + 1));
				if (i == widths.size() - 1)
				{
					ql::print("|");
				}
				else
				{
					ql::print("|");
				}
			}

			ql::print("_ ");
			ql::println(path.get_name());
		}
	}

	ql::filesys::paths ql::filesys::path::make_directory_range() const
	{
		return ql::filesys::paths(this->list_current_directory());
	}

	ql::filesys::paths ql::filesys::path::make_directory_range_tree() const
	{
		return ql::filesys::paths(this->list_current_directory_tree());
	}

	ql::size ql::filesys::path::last_common_branch(const ql::filesys::path& path) const
	{
		ql::size result = 0u;
		auto stop = ql::min(this->m_string.size(), path.m_string.size());
		for (ql::u32 i = 0; i < stop; ++i)
		{
			if (this->m_string[i] != path.m_string[i])
			{
				return result;
			}
			else if (this->m_string[i] == '/')
			{
				++result;
			}
		}
		return result;
	}

	ql::filesys::path ql::filesys::path::get_common_branch(const ql::filesys::path& other) const
	{
		auto branches_a = this->get_branches();
		auto branches_b = other.get_branches();
		auto min = ql::min(branches_a.size(), branches_b.size());

		ql::size i = 0u;
		for (; i < min; ++i)
		{
			if (branches_a[i] != branches_b[i])
			{
				if (i == 0u)
					return "";
				return branches_a[i - 1];
			}
		}
		if (i == 0u)
			return "";
		return branches_a[i - 1];
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_equals(const std::string_view& extension) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.extension_equals(extension))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_equals(const char* extension) const
	{
		return this->search_where_extension_equals(std::string_view{extension});
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_equals(const std::string& extension) const
	{
		return this->search_where_extension_equals(std::string_view{extension});
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_contains(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.extension_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_contains(const char* str) const
	{
		return this->search_where_extension_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_contains(const std::string& str) const
	{
		return this->search_where_extension_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_matches(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.extension_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_name_equals(const std::string_view& name) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.name_equals(name))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_name_equals(const char* name) const
	{
		return this->search_where_name_equals(std::string_view{name});
	}

	ql::filesys::paths ql::filesys::path::search_where_name_equals(const std::string& name) const
	{
		return this->search_where_name_equals(std::string_view{name});
	}

	ql::filesys::paths ql::filesys::path::search_where_name_contains(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.name_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_name_contains(const char* str) const
	{
		return this->search_where_name_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_name_contains(const std::string& str) const
	{
		return this->search_where_name_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_name_matches(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.name_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_equals(const std::string_view& file_name) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.file_name_equals(file_name))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_equals(const char* file_name) const
	{
		return this->search_where_file_name_equals(std::string_view{file_name});
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_equals(const std::string& file_name) const
	{
		return this->search_where_file_name_equals(std::string_view{file_name});
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_contains(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.file_name_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_contains(const char* str) const
	{
		return this->search_where_file_name_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_contains(const std::string& str) const
	{
		return this->search_where_file_name_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_matches(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.file_name_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_doesnt_equal(const std::string_view& extension) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.extension_equals(extension))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_doesnt_equal(const char* extension) const
	{
		return this->search_where_extension_doesnt_equal(std::string_view{extension});
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_doesnt_equal(const std::string& extension) const
	{
		return this->search_where_extension_doesnt_equal(std::string_view{extension});
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_doesnt_contain(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.extension_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_doesnt_contain(const char* str) const
	{
		return this->search_where_extension_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_doesnt_contain(const std::string& str) const
	{
		return this->search_where_extension_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_extension_doesnt_match(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.extension_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_name_doesnt_equal(const std::string_view& name) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.name_equals(name))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_name_doesnt_equal(const char* name) const
	{
		return this->search_where_name_doesnt_equal(std::string_view{name});
	}

	ql::filesys::paths ql::filesys::path::search_where_name_doesnt_equal(const std::string& name) const
	{
		return this->search_where_name_doesnt_equal(std::string_view{name});
	}

	ql::filesys::paths ql::filesys::path::search_where_name_doesnt_contain(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.name_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_name_doesnt_contain(const char* str) const
	{
		return this->search_where_name_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_name_doesnt_contain(const std::string& str) const
	{
		return this->search_where_name_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_name_doesnt_match(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.name_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_doesnt_equal(const std::string_view& file_name) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.file_name_equals(file_name))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_doesnt_equal(const char* file_name) const
	{
		return this->search_where_file_name_doesnt_equal(std::string_view{file_name});
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_doesnt_equal(const std::string& file_name) const
	{
		return this->search_where_file_name_doesnt_equal(std::string_view{file_name});
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_doesnt_contain(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.file_name_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_doesnt_contain(const char* str) const
	{
		return this->search_where_file_name_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_doesnt_contain(const std::string& str) const
	{
		return this->search_where_file_name_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_where_file_name_doesnt_match(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.file_name_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_directories() const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.is_directory())
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_files() const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i : std::filesystem::directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.is_file())
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_equals(const std::string_view& extension) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.extension_equals(extension))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_equals(const char* extension) const
	{
		return this->search_recursively_where_extension_equals(std::string_view{extension});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_equals(const std::string& extension) const
	{
		return this->search_recursively_where_extension_equals(std::string_view{extension});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_contains(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.extension_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_contains(const char* str) const
	{
		return this->search_recursively_where_extension_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_contains(const std::string& str) const
	{
		return this->search_recursively_where_extension_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_matches(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.extension_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_equals(const std::string_view& name) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.name_equals(name))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_equals(const char* name) const
	{
		return this->search_recursively_where_name_equals(std::string_view{name});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_equals(const std::string& name) const
	{
		return this->search_recursively_where_name_equals(std::string_view{name});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_contains(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.name_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_contains(const char* str) const
	{
		return this->search_recursively_where_name_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_contains(const std::string& str) const
	{
		return this->search_recursively_where_name_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_matches(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.name_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_equals(const std::string_view& file_name) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.file_name_equals(file_name))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_equals(const char* file_name) const
	{
		return this->search_recursively_where_file_name_equals(std::string_view{file_name});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_equals(const std::string& file_name) const
	{
		return this->search_recursively_where_file_name_equals(std::string_view{file_name});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_contains(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.file_name_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_contains(const char* str) const
	{
		return this->search_recursively_where_file_name_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_contains(const std::string& str) const
	{
		return this->search_recursively_where_file_name_contains(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_matches(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.file_name_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_doesnt_equal(const std::string_view& extension) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.extension_equals(extension))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_doesnt_equal(const char* extension) const
	{
		return this->search_recursively_where_extension_doesnt_equal(std::string_view{extension});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_doesnt_equal(const std::string& extension) const
	{
		return this->search_recursively_where_extension_doesnt_equal(std::string_view{extension});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_doesnt_contain(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.extension_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_doesnt_contain(const char* str) const
	{
		return this->search_recursively_where_extension_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_doesnt_contain(const std::string& str) const
	{
		return this->search_recursively_where_extension_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_extension_doesnt_match(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.extension_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_doesnt_equal(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.name_equals(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_doesnt_equal(const char* str) const
	{
		return this->search_recursively_where_name_doesnt_equal(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_doesnt_equal(const std::string& str) const
	{
		return this->search_recursively_where_name_doesnt_equal(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_doesnt_contain(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.name_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_doesnt_contain(const char* str) const
	{
		return this->search_recursively_where_name_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_doesnt_contain(const std::string& str) const
	{
		return this->search_recursively_where_name_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_name_doesnt_match(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.name_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_doesnt_equal(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.file_name_equals(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_doesnt_equal(const char* str) const
	{
		return this->search_recursively_where_file_name_doesnt_equal(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_doesnt_equal(const std::string& str) const
	{
		return this->search_recursively_where_file_name_doesnt_equal(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_doesnt_contain(const std::string_view& str) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.file_name_contains(str))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_doesnt_contain(const char* str) const
	{
		return this->search_recursively_where_file_name_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_doesnt_contain(const std::string& str) const
	{
		return this->search_recursively_where_file_name_doesnt_contain(std::string_view{str});
	}

	ql::filesys::paths ql::filesys::path::search_recursively_where_file_name_doesnt_match(const std::regex& regex) const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (!path.file_name_matches(regex))
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_directories() const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.is_directory())
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	ql::filesys::paths ql::filesys::path::search_recursively_files() const
	{
		ql::filesys::paths result;
		auto directory = this->is_directory() ? this->to_string() : this->get_parent_branch().to_string();
		for (auto i :
				 std::filesystem::recursive_directory_iterator(directory, std::filesystem::directory_options::skip_permission_denied))
		{
			ql::filesys::path path = i;
			if (path.is_file())
			{
				result.emplace_back(path);
			}
		}
		return result;
	}

	void ql::filesys::path::update() const
	{
		this->m_exists = std::filesystem::exists(this->to_string());

		if (this->empty())
		{
			this->m_is_file = false;
			this->m_is_directory = false;
		}
		else if (!this->m_exists)
		{
			this->m_is_file = this->m_string.back() != '/';
			this->m_is_directory = !this->m_is_file;
		}
		else
		{
			this->m_is_directory = std::filesystem::is_directory(this->to_string());
			this->m_is_file = this->m_is_directory ? false
																						 : std::filesystem::is_regular_file(this->to_string()) ||
																									 std::filesystem::is_block_file(this->to_string()) ||
																									 std::filesystem::is_character_file(this->to_string());
		}
	}

	void ql::filesys::path::construct()
	{
		this->m_is_file = false;
		this->m_string = "";
	}

	std::ostream& ql::filesys::operator<<(std::ostream& os, const ql::filesys::path& path)
	{
		return os << path.to_string();
	}
}	 // namespace ql::filesys