#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/encryption/encryption.hpp>

#include <filesystem>
#include <regex>

namespace ql
{
	namespace filesys
	{
		struct path;
		struct paths;

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
		QL_SOURCE void file_encrypt_to(
				const std::string& source_path,
				const std::string& dest_path,
				const std::string& key,
				ql::aes::mode mode = ql::aes::mode::_256
		);
		QL_SOURCE std::string file_decrypt(const std::string& path, const std::string& key, ql::aes::mode mode = ql::aes::mode::_256);
		QL_SOURCE void file_decrypt_to(
				const std::string& source_path,
				const std::string& dest_path,
				const std::string& key,
				ql::aes::mode mode = ql::aes::mode::_256
		);

	}	 // namespace filsys

	QL_SOURCE std::string read_file(const std::string& path);
	QL_SOURCE void write_to_file(const std::string& text, const std::string& path);
	QL_SOURCE void write_data_file(const std::string& data, const std::string& path);
	QL_SOURCE void write_text_file(const std::string& data, const std::string& path);
}	 // namespace ql