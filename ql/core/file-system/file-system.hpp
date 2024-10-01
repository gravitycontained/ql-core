#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

#include <ql/core/encryption/encryption.hpp>

#include <ql/core/advanced-type/memory/string-collection.hpp>

#include <ql/core/advanced-type/memory/save-state.hpp>

#include <ql/core/transform/sort.hpp>
#include <ql/core/string/format/format.hpp>
#include <string>

#include <filesystem>
#include <functional>
#include <regex>
#include <fstream>

namespace ql
{

	namespace filesys
	{
		class paths;

		class path
		{
		 public:
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
			QL_SOURCE path& operator=(const path& other);
			QL_SOURCE path& operator=(const std::filesystem::directory_entry& entry);

			QL_SOURCE bool operator==(const path& other) const;
			QL_SOURCE bool file_content_equals(const path& other) const;
			QL_SOURCE bool file_equals(const path& other) const;
			QL_SOURCE bool file_equals_no_read(const path& other) const;

			QL_SOURCE static ql::filesys::path current_path();
			QL_SOURCE void set_current_path();

			QL_SOURCE const char* data() const;
			QL_SOURCE const char* c_str() const;
			QL_SOURCE std::string string() const;
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

		class paths
		{
		 public:
			paths()
			{
			}

			paths(const std::vector<ql::filesys::path>& paths)
			{
				*this = paths;
			}

			paths(const ql::filesys::paths& paths)
			{
				*this = paths;
			}

			QL_SOURCE paths& operator=(const std::vector<ql::filesys::path>& paths);
			QL_SOURCE paths& operator=(const ql::filesys::paths& paths);

			QL_SOURCE std::vector<ql::filesys::path>::iterator begin();
			QL_SOURCE std::vector<ql::filesys::path>::const_iterator begin() const;
			QL_SOURCE std::vector<ql::filesys::path>::const_iterator cbegin() const;
			QL_SOURCE std::vector<ql::filesys::path>::reverse_iterator rbegin();
			QL_SOURCE std::vector<ql::filesys::path>::iterator end();
			QL_SOURCE std::vector<ql::filesys::path>::const_iterator end() const;
			QL_SOURCE std::vector<ql::filesys::path>::const_iterator cend() const;
			QL_SOURCE std::vector<ql::filesys::path>::reverse_iterator rend();

			QL_SOURCE void copy_to(ql::filesys::path destination);
			QL_SOURCE void move_to(ql::filesys::path destination);
			QL_SOURCE void copy_overwrite_to(ql::filesys::path destination);
			QL_SOURCE void move_overwrite_to(ql::filesys::path destination);

			QL_SOURCE void copy_files_to(ql::filesys::path destination);
			QL_SOURCE void move_files_to(ql::filesys::path destination);
			QL_SOURCE void copy_overwrite_files_to(ql::filesys::path destination);
			QL_SOURCE void move_overwrite_files_to(ql::filesys::path destination);

			QL_SOURCE void copy_as_tree_to(ql::filesys::path destination);
			QL_SOURCE void move_as_tree_to(ql::filesys::path destination);
			QL_SOURCE void copy_overwrite_as_tree_to(ql::filesys::path destination);
			QL_SOURCE void move_overwrite_as_tree_to(ql::filesys::path destination);

			QL_SOURCE ql::size size() const;
			QL_SOURCE bool empty() const;
			QL_SOURCE ql::size capacity() const;
			QL_SOURCE void resize(ql::size new_size);
			QL_SOURCE void reserve(ql::size new_cap);
			QL_SOURCE void clear();

			QL_SOURCE ql::filesys::path& front();
			QL_SOURCE const ql::filesys::path& front() const;
			QL_SOURCE ql::filesys::path& back();
			QL_SOURCE const ql::filesys::path& back() const;

			QL_SOURCE void push_back(const ql::filesys::path& path);
			QL_SOURCE void emplace_back(ql::filesys::path& path);
			QL_SOURCE void pop_back();

			QL_SOURCE ql::filesys::path& operator[](ql::size index);
			QL_SOURCE const ql::filesys::path& operator[](ql::size index) const;
			QL_SOURCE ql::filesys::path& at(ql::size index);
			QL_SOURCE const ql::filesys::path& at(ql::size index) const;

			QL_SOURCE void print_tree() const;

			QL_SOURCE void list_remove_where_lambda(const std::function<bool(ql::filesys::path)>& check);
			QL_SOURCE void list_keep_where_lambda(const std::function<bool(ql::filesys::path)>& check);

			QL_SOURCE void list_add(const ql::filesys::path& path);
			QL_SOURCE void list_add_recursively(const ql::filesys::path& path);

			QL_SOURCE void list_add_directories(const ql::filesys::path& directory);
			QL_SOURCE void list_recursively_add_directories(const ql::filesys::path& directory);
			QL_SOURCE void list_remove_directories();
			QL_SOURCE void list_add_files(const ql::filesys::path& directory);
			QL_SOURCE void list_recursively_add_files(const ql::filesys::path& directory);
			QL_SOURCE void list_remove_files();

			QL_SOURCE bool find_directory(const std::string_view& directory_name);

			QL_SOURCE void list_remove_where_directory_matches(const std::string& str);

			QL_SOURCE void list_remove_where_extension_equals(const std::string_view& extension);
			QL_SOURCE void list_add_where_extension_equals(const ql::filesys::path& directory, const std::string_view& extension);
			QL_SOURCE void
			list_recursively_add_where_extension_equals(const ql::filesys::path& directory, const std::string_view& extension);
			QL_SOURCE void list_remove_where_extension_contains(const std::string_view& str);
			QL_SOURCE void list_add_where_extension_contains(const ql::filesys::path& directory, const std::string_view& str);
			QL_SOURCE void list_recursively_add_where_extension_contains(const ql::filesys::path& directory, const std::string_view& str);

			QL_SOURCE void list_remove_where_name_equals(const std::string_view& name);
			QL_SOURCE void list_add_where_name_equals(const ql::filesys::path& directory, const std::string_view& name);
			QL_SOURCE void list_recursively_add_where_name_equals(const ql::filesys::path& directory, const std::string_view& name);
			QL_SOURCE void list_remove_where_name_contains(const std::string_view& name);
			QL_SOURCE void list_add_where_name_contains(const ql::filesys::path& directory, const std::string_view& str);
			QL_SOURCE void list_recursively_add_where_name_contains(const ql::filesys::path& directory, const std::string_view& str);

			QL_SOURCE void list_remove_where_file_name_equals(const std::string_view& file_name);
			QL_SOURCE void list_add_where_file_name_equals(const ql::filesys::path& directory, const std::string_view& file_name);
			QL_SOURCE void
			list_recursively_add_where_file_name_equals(const ql::filesys::path& directory, const std::string_view& file_name);
			QL_SOURCE void list_remove_where_file_name_contains(const std::string_view& file_name);
			QL_SOURCE void list_add_where_file_name_contains(const ql::filesys::path& directory, const std::string_view& str);
			QL_SOURCE void list_recursively_add_where_file_name_contains(const ql::filesys::path& directory, const std::string_view& str);

			QL_SOURCE void list_keep_where_extension_equals(const std::string_view& extension);
			QL_SOURCE void list_add_where_extension_doesnt_equal(const ql::filesys::path& directory, const std::string_view& extension);
			QL_SOURCE void
			list_recursively_add_where_extension_doesnt_equal(const ql::filesys::path& directory, const std::string_view& extension);
			QL_SOURCE void list_keep_where_extension_contains(const std::string_view& str);
			QL_SOURCE void list_add_where_extension_doesnt_contain(const ql::filesys::path& directory, const std::string_view& str);
			QL_SOURCE void
			list_recursively_add_where_extension_doesnt_contain(const ql::filesys::path& directory, const std::string_view& str);

			QL_SOURCE void list_keep_where_name_equals(const std::string_view& name);
			QL_SOURCE void list_add_where_name_doesnt_equal(const ql::filesys::path& directory, const std::string_view& name);
			QL_SOURCE void list_recursively_add_where_name_doesnt_equal(const ql::filesys::path& directory, const std::string_view& name);
			QL_SOURCE void list_keep_where_name_contains(const std::string_view& name);
			QL_SOURCE void list_add_where_name_doesnt_contain(const ql::filesys::path& directory, const std::string_view& str);
			QL_SOURCE void
			list_recursively_add_where_name_doesnt_contain(const ql::filesys::path& directory, const std::string_view& str);

			QL_SOURCE void list_keep_where_file_name_equals(const std::string_view& file_name);
			QL_SOURCE void list_add_where_file_name_doesnt_equal(const ql::filesys::path& directory, const std::string_view& file_name);
			QL_SOURCE void
			list_recursively_add_where_file_name_doesnt_equal(const ql::filesys::path& directory, const std::string_view& file_name);
			QL_SOURCE void list_keep_where_file_name_contains(const std::string_view& file_name);
			QL_SOURCE void list_add_where_file_name_doesnt_contain(const ql::filesys::path& directory, const std::string_view& str);
			QL_SOURCE void
			list_recursively_add_where_file_name_doesnt_contain(const ql::filesys::path& directory, const std::string_view& str);

			std::vector<ql::filesys::path> m_paths;
		};

		QL_SOURCE std::ostream& operator<<(std::ostream& os, const ql::filesys::path& path);

		QL_SOURCE bool file_content_equals(const ql::filesys::path& path1, const ql::filesys::path& path2);

		QL_SOURCE ql::size file_lines(const ql::filesys::path& path);

		QL_SOURCE ql::size file_bytes(const ql::filesys::path& path);

		QL_SOURCE std::vector<ql::size> file_line_differences(const ql::filesys::path& path1, const ql::filesys::path& path2);
		QL_SOURCE ql::f64 file_lines_difference_percentage(const ql::filesys::path& path1, const ql::filesys::path& path2);

		QL_SOURCE void split_file(const ql::filesys::path& path, ql::u32 bytes);
		QL_SOURCE void combine_files(const ql::filesys::paths& paths, const ql::filesys::path& destination);

		QL_SOURCE ql::filesys::paths list_directory(const ql::filesys::path& path);
		QL_SOURCE ql::filesys::paths list_current_directory();
		QL_SOURCE ql::filesys::paths list_directory_tree(const ql::filesys::path& path);
		QL_SOURCE ql::filesys::paths list_current_directory_tree();
		QL_SOURCE void print_current_tree();
		QL_SOURCE void print_tree(ql::filesys::path path);

		QL_SOURCE void cd(ql::filesys::path& path, const ql::filesys::path& target);

		QL_SOURCE void create(const ql::filesys::path& path);
		QL_SOURCE void create_file(const ql::filesys::path& path, const std::string& file_content);
		QL_SOURCE bool last_write_time_equal(const ql::filesys::path& path1, const ql::filesys::path& path2);

		QL_SOURCE bool is_file(const ql::filesys::path& path);
		QL_SOURCE bool is_directory(const ql::filesys::path& path);
		QL_SOURCE bool has_extension(const ql::filesys::path& path);
		QL_SOURCE std::string get_name(const ql::filesys::path& path);
		QL_SOURCE std::string get_file_extension(const ql::filesys::path& path);
		QL_SOURCE std::string get_file_name(const ql::filesys::path& path);
		QL_SOURCE std::string get_full_file_name(const ql::filesys::path& path);
		QL_SOURCE std::string_view get_name_view(const ql::filesys::path& path);
		QL_SOURCE std::string_view get_file_extension_view(const ql::filesys::path& path);
		QL_SOURCE std::string_view get_file_name_view(const ql::filesys::path& path);
		QL_SOURCE std::string_view get_full_file_name_view(const ql::filesys::path& path);
		QL_SOURCE ql::filesys::path get_parent_branch(const ql::filesys::path& path);

		QL_SOURCE bool extension_equals(const ql::filesys::path& path, const std::string_view& str);
		QL_SOURCE bool extension_equals(const ql::filesys::path& path, const std::string& str);
		QL_SOURCE bool extension_contains(const ql::filesys::path& path, const std::string_view& str);
		QL_SOURCE bool extension_contains(const ql::filesys::path& path, const std::string& str);
		QL_SOURCE bool extension_matches(const ql::filesys::path& path, const std::string& regex);
		QL_SOURCE bool extension_matches(const ql::filesys::path& path, const std::regex& regex);
		QL_SOURCE bool file_name_equals(const ql::filesys::path& path, const std::string_view& str);
		QL_SOURCE bool file_name_equals(const ql::filesys::path& path, const std::string& str);
		QL_SOURCE bool file_name_contains(const ql::filesys::path& path, const std::string_view& str);
		QL_SOURCE bool file_name_contains(const ql::filesys::path& path, const std::string& str);
		QL_SOURCE bool file_name_matches(const ql::filesys::path& path, const std::string& regex);
		QL_SOURCE bool file_name_matches(const ql::filesys::path& path, const std::regex& regex);
		QL_SOURCE bool full_file_name_equals(const ql::filesys::path& path, const std::string_view& str);
		QL_SOURCE bool full_file_name_equals(const ql::filesys::path& path, const std::string& str);
		QL_SOURCE bool full_file_name_contains(const ql::filesys::path& path, const std::string_view& str);
		QL_SOURCE bool full_file_name_contains(const ql::filesys::path& path, const std::string& str);
		QL_SOURCE bool full_file_name_matches(const ql::filesys::path& path, const std::string& regex);
		QL_SOURCE bool full_file_name_matches(const ql::filesys::path& path, const std::regex& regex);
		QL_SOURCE bool name_equals(const ql::filesys::path& path, const std::string_view& str);
		QL_SOURCE bool name_equals(const ql::filesys::path& path, const std::string& str);
		QL_SOURCE bool name_contains(const ql::filesys::path& path, const std::string_view& str);
		QL_SOURCE bool name_contains(const ql::filesys::path& path, const std::string& str);
		QL_SOURCE bool name_matches(const ql::filesys::path& path, const std::string& regex);
		QL_SOURCE bool name_matches(const ql::filesys::path& path, const std::regex& regex);

		QL_SOURCE bool exists(const ql::filesys::path& path_source);
		QL_SOURCE void rename(ql::filesys::path& path_source, const ql::filesys::path& new_name);
		QL_SOURCE void rename(const ql::filesys::path& path_source, const ql::filesys::path& new_name);
		QL_SOURCE void remove(const ql::filesys::path& path_target);
		QL_SOURCE void copy(const ql::filesys::path& path_source, const ql::filesys::path& path_destination);
		QL_SOURCE void copy_overwrite(const ql::filesys::path& path_source, const ql::filesys::path& path_destination);
		QL_SOURCE void move(const ql::filesys::path& path_source, const ql::filesys::path& path_destination);
		QL_SOURCE void move_overwrite(const ql::filesys::path& path_source, const ql::filesys::path& path_destination);

		QL_SOURCE void partially_rename_all(ql::filesys::paths& files, const std::string& regex, const std::string& replace);
		QL_SOURCE void partially_rename_all(ql::filesys::path& path, const std::string& regex, const std::string& replace);
		QL_SOURCE void copy_unpack_directory(const ql::filesys::path& path);
		QL_SOURCE void move_unpack_directory(const ql::filesys::path& path);
		QL_SOURCE void remove_all(const ql::filesys::paths& files);

		QL_SOURCE void move_all(const ql::filesys::paths& files, const ql::filesys::path& path_destination);
		QL_SOURCE void copy_all(const ql::filesys::paths& files, const ql::filesys::path& path_destination);
		QL_SOURCE void move_all_overwrite(const ql::filesys::paths& files, const ql::filesys::path& path_destination);
		QL_SOURCE void copy_all_overwrite(const ql::filesys::paths& files, const ql::filesys::path& path_destination);

		QL_SOURCE void move_all_files(const ql::filesys::paths& files, const ql::filesys::path& path_destination);
		QL_SOURCE void copy_all_files(const ql::filesys::paths& files, const ql::filesys::path& path_destination);
		QL_SOURCE void move_all_files_overwrite(const ql::filesys::paths& files, const ql::filesys::path& path_destination);
		QL_SOURCE void copy_all_files_overwrite(const ql::filesys::paths& files, const ql::filesys::path& path_destination);

		QL_SOURCE ql::filesys::paths search_where_extension_equals(const ql::filesys::path& directory, const std::string& extension);
		QL_SOURCE ql::filesys::paths search_where_extension_contains(const ql::filesys::path& directory, const std::string& regex);
		QL_SOURCE ql::filesys::paths search_where_name_equals(const ql::filesys::path& directory, const std::string& name);
		QL_SOURCE ql::filesys::paths search_where_name_contains(const ql::filesys::path& directory, const std::string& regex);

		QL_SOURCE ql::filesys::paths
		search_where_extension_doesnt_equal(const ql::filesys::path& directory, const std::string& extension);
		QL_SOURCE ql::filesys::paths
		search_where_extension_doesnt_contain(const ql::filesys::path& directory, const std::string& regex);
		QL_SOURCE ql::filesys::paths search_where_name_doesnt_equal(const ql::filesys::path& directory, const std::string& name);
		QL_SOURCE ql::filesys::paths search_where_name_doesnt_contain(const ql::filesys::path& directory, const std::string& regex);

		QL_SOURCE std::string read_file(const std::string& path);
		QL_SOURCE std::string read_rest_of_file(std::ifstream& file, bool close_file = true);
		QL_SOURCE std::filesystem::file_time_type file_last_write_time(const std::string& path);
		QL_SOURCE std::string file_last_write_time_str(const std::string& path);
		QL_SOURCE void write_to_file(const std::string& text, const std::string& path);
		QL_SOURCE void write_to_file(const std::wstring& text, const std::string& path);
		QL_SOURCE void writeln_to_file(const std::string& text, const std::string& path);
		QL_SOURCE void writeln_to_file(const std::wstring& text, const std::string& path);

		QL_SOURCE void write_data_file(const std::string& data, const std::string& path);
		QL_SOURCE void write_text_file(const std::string& data, const std::string& path);
		QL_SOURCE ql::filesys::path get_current_location();

		template <typename C>
		void container_memory_to_file(const C& data, const std::string& path)
		{
			if constexpr (ql::has_data<C>() && ql::has_size<C>())
			{
				ql::filesys::write_data_file(ql::container_memory_to_string(data), path);
			}
			else
			{
				std::ofstream file(path, std::ios::binary);
				file.write(reinterpret_cast<const char*>(data.data()), data.size() * ql::bytes_in_type<ql::container_subtype<C>>());
				file.close();
			}
		}

		template <typename C>
		void container_memory_from_file(C& data, const std::string& path)
		{
			if constexpr (ql::has_data<C>() && ql::has_size<C>())
			{
				ql::string_to_container_memory(ql::filesys::read_file(path), data);
			}
			else
			{
				std::ifstream file(path, std::ios::ate | std::ios::binary);

				if (!file.is_open())
				{
					throw std::runtime_error(ql::to_string("failed to open file \"", path, "\"").c_str());
				}

				auto file_size = (size_t)file.tellg();
				data.resize((file_size - 1) / ql::bytes_in_type<ql::container_subtype<C>>() + 1);

				file.seekg(0);
				file.read(reinterpret_cast<char*>(data.data()), file_size);

				file.close();
			}
		}

		QL_SOURCE std::string file_encrypt(const std::string& path, const std::string& key, ql::aes::mode mode = ql::aes::mode::_256);
		QL_SOURCE void file_encrypt_to(const std::string& source_path,
																const std::string& dest_path,
																const std::string& key,
																ql::aes::mode mode = ql::aes::mode::_256);
		QL_SOURCE std::string file_decrypt(const std::string& path, const std::string& key, ql::aes::mode mode = ql::aes::mode::_256);
		QL_SOURCE void file_decrypt_to(const std::string& source_path,
																const std::string& dest_path,
																const std::string& key,
																ql::aes::mode mode = ql::aes::mode::_256);
	}	 // namespace filesys

	QL_SOURCE std::string read_file(const std::string& path);
	QL_SOURCE void write_to_file(const std::string& text, const std::string& path);
	QL_SOURCE void write_data_file(const std::string& data, const std::string& path);
	QL_SOURCE void write_text_file(const std::string& data, const std::string& path);

	struct file_encrypter
	{
		ql::filesys::paths paths;
		ql::filesys::path common_branch;
		std::unordered_map<std::string, ql::filesys::paths> part_paths;
		std::string keyword_string_part = "CIPHER_PART";
		std::string keyword_string_enrypted = "ENCRYPTED";
		std::string keyword_string_derypted = "DECRYPTED";

		void clear();
		void add(std::string path);

		template <typename F>
		std::string encrypted_string(const std::string& key, F&& encryption_function)
		{
			if (this->paths.empty())
			{
				return "";
			}
			auto common_size = this->common_branch.branch_size() - 1;

			ql::save_state save_state;
			save_state.save(this->common_branch.string());
			save_state.save(this->paths.size());

			for (auto& i : this->paths)
			{
				save_state.save(i.string());
				save_state.save(i.is_file());
			}

			for (auto& i : this->paths)
			{
				if (i.is_file())
				{
					// save_state.save(ql::wstring_to_utf8(ql::winsys::read_utf8_file(i.string())));
					save_state.save(i.read());
				}
			}

			this->clear();
			auto str = save_state.get_finalized_string();
			str = encryption_function(str, key);
			return str;
		}

		template <typename F>
		ql::filesys::paths encrypt(const std::string& key,
																std::string output_name,
																F&& encryption_function,
																ql::filesys::path destination_path,
																ql::size split_size = ql::size_max)
		{
			if (!destination_path.empty() && destination_path.string().back() != '/')
			{
				destination_path.append("/");
			}

			auto str = this->encrypted_string(key, encryption_function);

			ql::filesys::path encrypted_path = ql::to_string(destination_path, output_name, '.', this->keyword_string_enrypted);

			ql::size ctr = 0u;
			while (encrypted_path.exists())
			{
				encrypted_path = ql::to_string(destination_path, output_name, '.', this->keyword_string_enrypted, ctr);
				++ctr;
			}
			auto splits = ql::string_split_every(str, split_size);
			if (splits.size() > 1)
			{
				auto log = std::log10(splits.size() - 1) + 1;
				for (ql::size i = 0u; i < splits.size(); ++i)
				{
					auto part_string = ql::to_string(".", this->keyword_string_part,
																						ql::string_prepended(ql::to_string(i), '0', ql::size_cast(log)));

					auto path = encrypted_path;
					path.append(part_string);

					while (path.exists())
					{
						encrypted_path = ql::to_string(destination_path, output_name, '.', this->keyword_string_enrypted, ctr);
						path = encrypted_path;
						path.append(part_string);
						++ctr;
					}

					ql::filesys::write_data_file(splits[i], path.string());
				}
			}
			else
			{
				encrypted_path.writeUtf8(str);
			}

			return this->paths;
		}

		ql::filesys::paths encrypt(const std::string& key,
																std::string output_name,
																ql::aes::mode mode,
																ql::filesys::path destination_path = "",
																ql::size split_size = ql::size_max);

		template <typename F>
		ql::filesys::paths decrypt(const std::string& key, F decryption_function, ql::filesys::path destination_path = "") const
		{
			if (!destination_path.empty() && destination_path.string().back() != '/')
			{
				destination_path.append("/");
			}
			ql::filesys::paths tree;
			for (auto& path : this->paths)
			{
				auto string = path.read();
				this->internal_decrypt(string, key, decryption_function, destination_path, tree);
			}
			for (auto& part : this->part_paths)
			{
				std::string string;

				const auto& paths = part.second;
				std::vector<std::pair<ql::filesys::path, ql::size>> sorted_parts(paths.size());
				for (ql::size i = 0u; i < sorted_parts.size(); ++i)
				{
					auto n = ql::size_cast(paths[i].get_file_extension().substr(this->keyword_string_part.length()));
					sorted_parts[i] = std::make_pair(paths[i], n);
				}
				ql::sort(sorted_parts, [](const auto& a, const auto& b) { return a.second < b.second; });

				auto p = sorted_parts.size() == 1u ? "part" : "parts";
				for (auto& file : sorted_parts)
				{
					string += file.first.read();
				}
				this->internal_decrypt(string, key, decryption_function, destination_path, tree);
			}

			return tree;
		}

		ql::filesys::paths decrypt(const std::string& key, ql::aes::mode mode, ql::filesys::path destination_path = "") const;

		ql::size additions = 0u;
		bool adding_parts = false;

		template <typename F>
		void internal_decrypt(const std::string& string,
													const std::string& key,
													F decryption_function,
													ql::filesys::path destination_path,
													ql::filesys::paths& tree) const
		{
			auto str = decryption_function(string, key);

			ql::load_state load_state;
			std::string s;
			load_state.set_string(str);
			load_state.load(s);
			ql::filesys::path common = s;

			ql::size size;
			load_state.load(size);
			ql::filesys::paths loaded_paths;
			loaded_paths.resize(size);

			std::unordered_set<std::string> is_file_hash;
			for (auto& i : loaded_paths)
			{
				std::string path_str;
				load_state.load(path_str);
				bool is_file;
				load_state.load(is_file);
				if (is_file)
				{
					is_file_hash.insert(path_str);
				}
				i = path_str;
			}

			std::string branch_name;
			auto split = ql::string_split(common.get_full_name(), '.');

			branch_name = common.get_full_name();
			if (split.size() && split.back() == this->keyword_string_enrypted)
			{
				split.pop_back();
				branch_name = ql::to_string_format("a.b", split);
			}
			branch_name += ql::to_string('.', this->keyword_string_derypted);
			auto original_branch_name = branch_name;

			ql::filesys::path decrypted_path = ql::to_string(destination_path, branch_name, "/");

			ql::size ctr = 0u;
			while (decrypted_path.exists())
			{
				branch_name = ql::to_string(original_branch_name, ctr);
				decrypted_path = ql::to_string(destination_path, branch_name, "/");
				++ctr;
			}

			ctr = 0u;
			for (auto& i : loaded_paths)
			{
				decrypted_path = i;
				decrypted_path.set_branch(common.branch_size() - 1, branch_name);
				decrypted_path = ql::to_string(destination_path, branch_name, "/", decrypted_path.subpath(common.branch_size() - 1));

				decrypted_path.ensure_branches_exist();

				bool is_file = is_file_hash.find(i) != is_file_hash.cend();
				if (is_file)
				{
					std::string data_str;
					load_state.load(data_str);

					ql::filesys::write_data_file(data_str, decrypted_path.string());
				}
				tree.push_back(decrypted_path);
			}
		}
	};

}	 // namespace ql