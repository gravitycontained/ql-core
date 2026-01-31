#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

#include <ql/core/file-system/action/action.hpp>

#include <ql/core/transform/sort.hpp>
#include <ql/core/string/format/format.hpp>

#include <ql/core/file-system/path/path.hpp>

#include <string>

#include <filesystem>
#include <functional>
#include <regex>
#include <fstream>

namespace ql
{
	namespace filesys
	{
		struct paths
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
			QL_SOURCE void
			list_recursively_add_where_extension_contains(const ql::filesys::path& directory, const std::string_view& str);

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
			QL_SOURCE void
			list_recursively_add_where_file_name_contains(const ql::filesys::path& directory, const std::string_view& str);

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
			QL_SOURCE void
			list_recursively_add_where_name_doesnt_equal(const ql::filesys::path& directory, const std::string_view& name);
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

	}	 // namespace filesys
}	 // namespace ql