#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/encryption/encryption.hpp>

#include <ql/core/type/type.hpp>
#include <filesystem>
#include <regex>

namespace ql::filesys
{
	struct paths;

	struct path
	{
		path()
		{
			this->construct();
		}

		path(const std::wstring& str)
		{
			this->construct();
			*this = str;
		}

		path(const std::string& str)
		{
			this->construct();
			*this = str;
		}

		path(const std::wstring_view& str)
		{
			this->construct();
			*this = str;
		}

		path(const std::string_view& str)
		{
			this->construct();
			*this = str;
		}

		path(const wchar_t* str)
		{
			this->construct();
			*this = str;
		}

		path(const char* str)
		{
			this->construct();
			*this = str;
		}

		path(const ql::filesys::path& other)
		{
			*this = other;
		}

		path(const std::filesystem::directory_entry& entry)
		{
			*this = entry;
		}

		QL_SOURCE path& operator=(const std::wstring& str);
		QL_SOURCE path& operator=(const std::string& str);
		QL_SOURCE path& operator=(const std::wstring_view& str);
		QL_SOURCE path& operator=(const std::string_view& str);
		QL_SOURCE path& operator=(const char* str);
		QL_SOURCE path& operator=(const wchar_t* str);
		QL_SOURCE path& operator=(const path& other) = default;
		QL_SOURCE path& operator=(const std::filesystem::directory_entry& entry);

		QL_SOURCE bool operator==(const path& other) const;
		QL_SOURCE bool file_content_equals(const path& other) const;
		QL_SOURCE bool file_equals(const path& other) const;
		QL_SOURCE bool file_equals_no_read(const path& other) const;

		QL_SOURCE static ql::filesys::path current_path();
		QL_SOURCE void set_current_path();

		QL_SOURCE const char* data() const;
		QL_SOURCE const char* c_str() const;
		QL_SOURCE std::string to_string() const;
		QL_SOURCE operator std::string() const;
		QL_SOURCE bool empty() const;
		QL_SOURCE void clear();
		QL_SOURCE void clear_file_content();

		QL_SOURCE void create() const;
		QL_SOURCE ql::filesys::path make_file(std::string file_name) const;
		QL_SOURCE std::string read() const;
		QL_SOURCE void write(const std::string& data) const;
		QL_SOURCE void writeUtf8(const std::string& data) const;

		QL_SOURCE std::filesystem::file_time_type last_write_time() const;
		QL_SOURCE ql::u64 file_size() const;
		QL_SOURCE ql::u64 file_size_recursive() const;
		QL_SOURCE bool file_content_equals(const path& other);
		QL_SOURCE bool has_root(const path& other) const;

		QL_SOURCE bool exists() const;
		QL_SOURCE bool is_file() const;
		QL_SOURCE bool is_directory() const;

		QL_SOURCE bool has_extension() const;

		QL_SOURCE std::string get_name() const;
		QL_SOURCE std::string get_full_name(bool add_slash_on_directory = false) const;
		QL_SOURCE std::string get_file_extension() const;
		QL_SOURCE std::string get_full_file_name() const;
		QL_SOURCE std::string get_file_name() const;
		QL_SOURCE std::string get_directory_name() const;

		QL_SOURCE std::string_view get_name_view() const;
		QL_SOURCE std::string_view get_file_extension_view() const;
		QL_SOURCE std::string_view get_full_file_name_view() const;
		QL_SOURCE std::string_view get_file_name_view() const;
		QL_SOURCE std::string_view get_directory_name_view() const;

		QL_SOURCE ql::filesys::path with_file_name(std::string file_name) const;
		QL_SOURCE ql::filesys::path with_full_file_name(std::string file_name) const;
		QL_SOURCE ql::filesys::path with_extension(std::string extension) const;

		QL_SOURCE bool extension_equals(const std::string_view& str) const;
		QL_SOURCE bool extension_equals(const char* str) const;
		QL_SOURCE bool extension_equals(const std::string& str) const;
		QL_SOURCE bool extension_contains(const std::string_view& str) const;
		QL_SOURCE bool extension_contains(const char* str) const;
		QL_SOURCE bool extension_contains(const std::string& str) const;
		QL_SOURCE bool extension_matches(const std::string& regex) const;
		QL_SOURCE bool extension_matches(const std::regex& regex) const;

		QL_SOURCE bool file_name_equals(const std::string_view& str) const;
		QL_SOURCE bool file_name_equals(const char* str) const;
		QL_SOURCE bool file_name_equals(const std::string& str) const;
		QL_SOURCE bool file_name_contains(const std::string_view& str) const;
		QL_SOURCE bool file_name_contains(const char* str) const;
		QL_SOURCE bool file_name_contains(const std::string& str) const;
		QL_SOURCE bool file_name_matches(const std::string& regex) const;
		QL_SOURCE bool file_name_matches(const std::regex& regex) const;

		QL_SOURCE bool full_file_name_equals(const std::string_view& str) const;
		QL_SOURCE bool full_file_name_equals(const char* str) const;
		QL_SOURCE bool full_file_name_equals(const std::string& str) const;
		QL_SOURCE bool full_file_name_contains(const std::string_view& str) const;
		QL_SOURCE bool full_file_name_contains(const char* str) const;
		QL_SOURCE bool full_file_name_contains(const std::string& str) const;
		QL_SOURCE bool full_file_name_matches(const std::string& regex) const;
		QL_SOURCE bool full_file_name_matches(const std::regex& regex) const;

		QL_SOURCE bool name_equals(const std::string_view& str) const;
		QL_SOURCE bool name_equals(const char* str) const;
		QL_SOURCE bool name_equals(const std::string& str) const;
		QL_SOURCE bool name_contains(const std::string_view& str) const;
		QL_SOURCE bool name_contains(const char* str) const;
		QL_SOURCE bool name_contains(const std::string& str) const;
		QL_SOURCE bool name_matches(const std::string& regex) const;
		QL_SOURCE bool name_matches(const std::regex& regex) const;

		QL_SOURCE void rename(const ql::filesys::path& new_name);
		QL_SOURCE void set_file_name(const std::string& new_name);
		QL_SOURCE void set_file_extension_name(const std::string& new_extension);
		QL_SOURCE void set_full_file_name(const std::string& new_file);
		QL_SOURCE void remove() const;
		QL_SOURCE void
		encrypt(const ql::filesys::path& destination, const std::string& key, ql::aes::mode mode = ql::aes::mode::_256) const;
		QL_SOURCE void
		decrypt(const ql::filesys::path& destination, const std::string& key, ql::aes::mode mode = ql::aes::mode::_256) const;
		QL_SOURCE void copy(const ql::filesys::path& path_destination) const;
		QL_SOURCE void copy_overwrite(const ql::filesys::path& path_destination) const;
		QL_SOURCE void move(const ql::filesys::path& path_destination) const;
		QL_SOURCE void move_overwrite(const ql::filesys::path& path_destination) const;
		QL_SOURCE void move_and_apply_path(const ql::filesys::path& path_destination);
		QL_SOURCE void move_overwrite_and_apply_path(const ql::filesys::path& path_destination);

		QL_SOURCE ql::size branch_size() const;
		QL_SOURCE ql::filesys::path get_branch_at(ql::size index) const;
		QL_SOURCE ql::filesys::paths get_branches() const;
		QL_SOURCE ql::filesys::path get_branch_earlier(ql::u32 n) const;
		QL_SOURCE ql::filesys::path get_parent_branch() const;
		QL_SOURCE ql::filesys::path get_last_branch() const;
		QL_SOURCE std::vector<std::string> get_branch_names() const;

		QL_SOURCE ql::filesys::path with_branch(ql::size index, std::string branch_name) const;
		QL_SOURCE void set_branch(ql::size index, std::string branch_name);
		QL_SOURCE ql::filesys::path subpath(ql::size off, ql::size size = ql::size_max) const;
		QL_SOURCE void ensure_branches_exist() const;
		QL_SOURCE void ensure_directory_backslash();
		QL_SOURCE void ensure_backslash();
		QL_SOURCE ql::filesys::path ensured_directory_backslash() const;
		QL_SOURCE ql::filesys::path ensured_backslash() const;

		QL_SOURCE bool is_root() const;
		QL_SOURCE path& go_root();

		// returns false if empty path or afterwards at root, otherwise true
		QL_SOURCE bool go_directories_back(ql::u32 steps);
		// returns false if empty path or afterwards at root, otherwise true
		QL_SOURCE bool go_directory_back();
		QL_SOURCE path& go_into_directory(const std::string& directory_name);
		QL_SOURCE path& go_into_file(const std::string& file_name);
		QL_SOURCE path& go_into(const std::string& entry);
		QL_SOURCE path& cd(const std::string& directory_name);
		QL_SOURCE void append(const std::string& string);
		QL_SOURCE void append(char c);
		QL_SOURCE path appended(const std::string& string) const;
		QL_SOURCE path appended(char c) const;

		QL_SOURCE ql::size directory_content_count() const;
		QL_SOURCE ql::filesys::paths list_current_directory() const;
		QL_SOURCE ql::filesys::paths list_current_directory_include_self() const;
		QL_SOURCE ql::filesys::paths list_current_directory_tree() const;
		QL_SOURCE ql::filesys::paths list_current_directory_tree_include_self() const;
		QL_SOURCE void print_current_directory() const;
		QL_SOURCE void print_tree() const;

		QL_SOURCE ql::filesys::paths make_directory_range() const;
		QL_SOURCE ql::filesys::paths make_directory_range_tree() const;

		QL_SOURCE ql::size last_common_branch(const ql::filesys::path& path) const;
		QL_SOURCE ql::filesys::path get_common_branch(const ql::filesys::path& other) const;

		QL_SOURCE ql::filesys::paths search_where_extension_equals(const std::string_view& extension) const;
		QL_SOURCE ql::filesys::paths search_where_extension_equals(const char* extension) const;
		QL_SOURCE ql::filesys::paths search_where_extension_equals(const std::string& extension) const;
		QL_SOURCE ql::filesys::paths search_where_extension_contains(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_where_extension_contains(const char* str) const;
		QL_SOURCE ql::filesys::paths search_where_extension_contains(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_where_extension_matches(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_where_name_equals(const std::string_view& name) const;
		QL_SOURCE ql::filesys::paths search_where_name_equals(const char* name) const;
		QL_SOURCE ql::filesys::paths search_where_name_equals(const std::string& name) const;
		QL_SOURCE ql::filesys::paths search_where_name_contains(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_where_name_contains(const char* str) const;
		QL_SOURCE ql::filesys::paths search_where_name_contains(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_where_name_matches(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_where_file_name_equals(const std::string_view& file_name) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_equals(const char* file_name) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_equals(const std::string& file_name) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_contains(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_contains(const char* str) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_contains(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_matches(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_where_extension_doesnt_equal(const std::string_view& extension) const;
		QL_SOURCE ql::filesys::paths search_where_extension_doesnt_equal(const char* extension) const;
		QL_SOURCE ql::filesys::paths search_where_extension_doesnt_equal(const std::string& extension) const;
		QL_SOURCE ql::filesys::paths search_where_extension_doesnt_contain(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_where_extension_doesnt_contain(const char* str) const;
		QL_SOURCE ql::filesys::paths search_where_extension_doesnt_contain(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_where_extension_doesnt_match(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_where_name_doesnt_equal(const std::string_view& name) const;
		QL_SOURCE ql::filesys::paths search_where_name_doesnt_equal(const char* name) const;
		QL_SOURCE ql::filesys::paths search_where_name_doesnt_equal(const std::string& name) const;
		QL_SOURCE ql::filesys::paths search_where_name_doesnt_contain(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_where_name_doesnt_contain(const char* str) const;
		QL_SOURCE ql::filesys::paths search_where_name_doesnt_contain(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_where_name_doesnt_match(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_where_file_name_doesnt_equal(const std::string_view& file_name) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_doesnt_equal(const char* file_name) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_doesnt_equal(const std::string& file_name) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_doesnt_contain(const std::string_view& file_name) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_doesnt_contain(const char* str) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_doesnt_contain(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_where_file_name_doesnt_match(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_directories() const;
		QL_SOURCE ql::filesys::paths search_files() const;

		QL_SOURCE ql::filesys::paths search_recursively_where_extension_equals(const std::string_view& extension) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_equals(const char* extension) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_equals(const std::string& extension) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_contains(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_contains(const char* str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_contains(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_matches(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_recursively_where_name_equals(const std::string_view& name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_equals(const char* name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_equals(const std::string& name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_contains(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_contains(const char* str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_contains(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_matches(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_equals(const std::string_view& file_name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_equals(const char* file_name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_equals(const std::string& file_name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_contains(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_contains(const char* str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_contains(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_matches(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_recursively_where_extension_doesnt_equal(const std::string_view& extension) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_doesnt_equal(const char* extension) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_doesnt_equal(const std::string& extension) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_doesnt_contain(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_doesnt_contain(const char* str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_doesnt_contain(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_extension_doesnt_match(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_recursively_where_name_doesnt_equal(const std::string_view& name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_doesnt_equal(const char* name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_doesnt_equal(const std::string& name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_doesnt_contain(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_doesnt_contain(const char* str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_doesnt_contain(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_name_doesnt_match(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_doesnt_equal(const std::string_view& file_name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_doesnt_equal(const char* file_name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_doesnt_equal(const std::string& file_name) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_doesnt_contain(const std::string_view& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_doesnt_contain(const char* str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_doesnt_contain(const std::string& str) const;
		QL_SOURCE ql::filesys::paths search_recursively_where_file_name_doesnt_match(const std::regex& regex) const;

		QL_SOURCE ql::filesys::paths search_recursively_directories() const;
		QL_SOURCE ql::filesys::paths search_recursively_files() const;

		QL_SOURCE void update() const;

		QL_SOURCE void construct();

		std::string m_string;
		mutable bool m_is_file;
		mutable bool m_is_directory;
		mutable bool m_exists;
	};

}