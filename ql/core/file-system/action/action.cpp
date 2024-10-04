#include <ql/core/file-system/action/action.hpp>

#include <ql/core/file-system/path/path.hpp>
#include <ql/core/file-system/paths/paths.hpp>

#include <ql/core/string/to-string.hpp>
#include <ql/core/system/print/print.hpp>

#include <fstream>

namespace ql
{
	namespace filesys
	{

		bool ql::filesys::file_content_equals(const ql::filesys::path& path1, const ql::filesys::path& path2)
		{
			return path1.file_content_equals(path2);
		}

		ql::size ql::filesys::file_lines(const ql::filesys::path& path)
		{
			std::stringstream str;
			str << ql::filesys::read_file(path).data();

			std::string line;
			ql::size ctr = 0u;
			while (std::getline(str, line))
			{
				++ctr;
			}
			return ctr;
		}

		ql::size ql::filesys::file_bytes(const ql::filesys::path& path)
		{
			std::stringstream str;
			str << ql::filesys::read_file(path).data();

			return str.str().size();
		}

		std::vector<ql::size> ql::filesys::file_line_differences(const ql::filesys::path& path1, const ql::filesys::path& path2)
		{
			std::vector<ql::size> result;
			std::stringstream str1;
			str1 << ql::filesys::read_file(path1).data();
			std::stringstream str2;
			str2 << ql::filesys::read_file(path2).data();

			std::string line1, line2;
			ql::size ctr = 0u;
			while (std::getline(str1, line1) && std::getline(str2, line2))
			{
				if (line1 != line2)
				{
					result.push_back(ctr);
				}
				++ctr;
			}
			return result;
		}

		ql::f64 ql::filesys::file_lines_difference_percentage(const ql::filesys::path& path1, const ql::filesys::path& path2)
		{
			std::stringstream str1;
			str1 << ql::filesys::read_file(path1).data();
			std::stringstream str2;
			str2 << ql::filesys::read_file(path2).data();

			std::string line1, line2;
			ql::size ctr = 0u;
			ql::size sum = 0u;
			while (std::getline(str1, line1) && std::getline(str2, line2))
			{
				if (line1 != line2)
				{
					++ctr;
				}
				++sum;
			}
			return static_cast<ql::f64>(ctr) / sum;
		}

		void ql::filesys::split_file(const ql::filesys::path& path, ql::u32 bytes)
		{
			auto content = ql::filesys::read_file(path);
			auto splits = (content.size() - 1) / bytes + 1;

			for (ql::u32 i = 0u; i < splits; ++i)
			{
				auto file_name = ql::to_string(
						path, ".PART", ql::string_prepended(i, '0', ql::size_cast(std::log(splits) / std::log(10) + 1))
				);
				std::ofstream file(file_name.c_str(), std::ios::binary);
				if (!file.good())
				{
					ql::println("there was a problem creating \"", file_name, "\"");
				}
				file << content.substr(i * bytes, bytes);
				file.flush();
			}
		}

		void ql::filesys::combine_files(const ql::filesys::paths& paths, const ql::filesys::path& destination)
		{
			std::ofstream file(destination.c_str(), std::ios::binary);
			if (!file.good())
			{
				ql::println("there was a problem creating \"", destination, "\"");
			}
			for (auto& i : paths)
			{
				file << i.read();
			}
			file.flush();
		}

		ql::filesys::paths ql::filesys::list_directory(const ql::filesys::path& path)
		{
			return path.list_current_directory();
		}

		ql::filesys::paths ql::filesys::list_current_directory()
		{
			return ql::filesys::list_directory(ql::filesys::get_current_location());
		}

		ql::filesys::paths ql::filesys::list_directory_tree(const ql::filesys::path& path)
		{
			return path.list_current_directory_tree();
		}

		ql::filesys::paths ql::filesys::list_current_directory_tree()
		{
			return ql::filesys::list_directory_tree(ql::filesys::get_current_location());
		}

		void ql::filesys::print_current_tree()
		{
			auto p = ql::filesys::list_current_directory_tree();
			p.print_tree();
		}

		void ql::filesys::print_tree(ql::filesys::path path)
		{
			auto p = ql::filesys::list_directory_tree(path);
			p.print_tree();
		}

		void ql::filesys::cd(ql::filesys::path& path, const ql::filesys::path& target)
		{
			path.go_into_directory(target);
		}

		void ql::filesys::create(const ql::filesys::path& path)
		{
			path.create();
			path.update();
		}

		void ql::filesys::create_file(const ql::filesys::path& path, const std::string& content)
		{
			path.create();
			path.update();
			path.write(content);
		}

		bool ql::filesys::last_write_time_equal(const ql::filesys::path& path1, const ql::filesys::path& path2)
		{
			if (!path1.exists() || !path2.exists())
			{
				return false;
			}
			return path1.last_write_time() == path2.last_write_time();
		}

		bool ql::filesys::is_file(const ql::filesys::path& path)
		{
			return path.is_file();
		}

		bool ql::filesys::is_directory(const ql::filesys::path& path)
		{
			return path.is_directory();
		}

		bool ql::filesys::has_extension(const ql::filesys::path& path)
		{
			return path.has_extension();
		}

		std::string ql::filesys::get_name(const ql::filesys::path& path)
		{
			return path.get_name();
		}

		std::string ql::filesys::get_file_extension(const ql::filesys::path& path)
		{
			return path.get_file_extension();
		}

		std::string ql::filesys::get_file_name(const ql::filesys::path& path)
		{
			return path.get_file_name();
		}

		std::string ql::filesys::get_full_file_name(const ql::filesys::path& path)
		{
			return path.get_full_file_name();
		}

		std::string_view get_name_view(const ql::filesys::path& path)
		{
			return path.get_name_view();
		}

		std::string_view get_file_extension_view(const ql::filesys::path& path)
		{
			return path.get_file_extension_view();
		}

		std::string_view get_file_name_view(const ql::filesys::path& path)
		{
			return path.get_file_name_view();
		}

		std::string_view get_full_file_name_view(const ql::filesys::path& path)
		{
			return path.get_full_file_name_view();
		}

		ql::filesys::path ql::filesys::get_parent_branch(const ql::filesys::path& path)
		{
			return path.get_parent_branch();
		}

		bool ql::filesys::extension_equals(const ql::filesys::path& path, const std::string_view& str)
		{
			return path.extension_equals(str);
		}

		bool ql::filesys::extension_equals(const ql::filesys::path& path, const std::string& str)
		{
			return path.extension_equals(str);
		}

		bool ql::filesys::extension_contains(const ql::filesys::path& path, const std::string_view& str)
		{
			return path.extension_contains(str);
		}

		bool ql::filesys::extension_contains(const ql::filesys::path& path, const std::string& str)
		{
			return path.extension_contains(str);
		}

		bool ql::filesys::extension_matches(const ql::filesys::path& path, const std::string& regex)
		{
			return path.extension_matches(regex);
		}

		bool ql::filesys::extension_matches(const ql::filesys::path& path, const std::regex& regex)
		{
			return path.extension_matches(regex);
		}

		bool ql::filesys::file_name_equals(const ql::filesys::path& path, const std::string_view& str)
		{
			return path.file_name_equals(str);
		}

		bool ql::filesys::file_name_equals(const ql::filesys::path& path, const std::string& str)
		{
			return path.file_name_equals(str);
		}

		bool ql::filesys::file_name_contains(const ql::filesys::path& path, const std::string_view& str)
		{
			return path.file_name_contains(str);
		}

		bool ql::filesys::file_name_contains(const ql::filesys::path& path, const std::string& str)
		{
			return path.file_name_contains(str);
		}

		bool ql::filesys::file_name_matches(const ql::filesys::path& path, const std::string& regex)
		{
			return path.file_name_matches(regex);
		}

		bool ql::filesys::file_name_matches(const ql::filesys::path& path, const std::regex& regex)
		{
			return path.file_name_matches(regex);
		}

		bool ql::filesys::full_file_name_equals(const ql::filesys::path& path, const std::string_view& str)
		{
			return path.full_file_name_equals(str);
		}

		bool ql::filesys::full_file_name_equals(const ql::filesys::path& path, const std::string& str)
		{
			return path.full_file_name_equals(str);
		}

		bool ql::filesys::full_file_name_contains(const ql::filesys::path& path, const std::string_view& str)
		{
			return path.full_file_name_contains(str);
		}

		bool ql::filesys::full_file_name_contains(const ql::filesys::path& path, const std::string& str)
		{
			return path.full_file_name_contains(str);
		}

		bool ql::filesys::full_file_name_matches(const ql::filesys::path& path, const std::string& regex)
		{
			return path.full_file_name_matches(regex);
		}

		bool ql::filesys::full_file_name_matches(const ql::filesys::path& path, const std::regex& regex)
		{
			return path.full_file_name_matches(regex);
		}

		bool ql::filesys::name_equals(const ql::filesys::path& path, const std::string_view& str)
		{
			return path.name_equals(str);
		}

		bool ql::filesys::name_equals(const ql::filesys::path& path, const std::string& str)
		{
			return path.name_equals(str);
		}

		bool ql::filesys::name_contains(const ql::filesys::path& path, const std::string_view& str)
		{
			return path.name_contains(str);
		}

		bool ql::filesys::name_contains(const ql::filesys::path& path, const std::string& str)
		{
			return path.name_contains(str);
		}

		bool ql::filesys::name_matches(const ql::filesys::path& path, const std::string& regex)
		{
			return path.name_matches(regex);
		}

		bool ql::filesys::name_matches(const ql::filesys::path& path, const std::regex& regex)
		{
			return path.name_matches(regex);
		}

		bool ql::filesys::exists(const ql::filesys::path& path_source)
		{
			return path_source.exists();
		}

		void ql::filesys::rename(ql::filesys::path& path_source, const ql::filesys::path& new_name)
		{
			path_source.rename(new_name);
		}

		void ql::filesys::rename(const ql::filesys::path& path_source, const ql::filesys::path& new_name)
		{
			std::filesystem::rename(path_source.to_string(), new_name.to_string());
		}

		void ql::filesys::remove(const ql::filesys::path& path_target)
		{
			path_target.remove();
		}

		void ql::filesys::copy(const ql::filesys::path& path_source, const ql::filesys::path& path_destination)
		{
			path_source.copy(path_destination);
		}

		void ql::filesys::copy_overwrite(const ql::filesys::path& path_source, const ql::filesys::path& path_destination)
		{
			path_source.copy_overwrite(path_destination);
		}

		void ql::filesys::move(const ql::filesys::path& path_source, const ql::filesys::path& path_destination)
		{
			path_source.move(path_destination);
		}

		void ql::filesys::move_overwrite(const ql::filesys::path& path_source, const ql::filesys::path& path_destination)
		{
			path_source.move_overwrite(path_destination);
		}

		void ql::filesys::partially_rename_all(ql::filesys::paths& files, const std::string& regex, const std::string& replace)
		{
			const std::regex reg{regex};
			auto path = files.front().get_parent_branch();
			for (auto& i : files)
			{
				if (std::regex_search(i.get_name(), reg))
				{
					i.rename(path.to_string() + std::regex_replace(i.get_name(), reg, replace));
				}
			}
		}

		void partially_rename_all(ql::filesys::path& path, const std::string& regex, const std::string& replace)
		{
			auto files = ql::filesys::list_directory(path);
			const std::regex reg{regex};
			for (auto& i : files)
			{
				if (std::regex_search(i.get_name(), reg))
				{
					i.rename(path.to_string() + std::regex_replace(i.get_name(), reg, replace));
				}
			}
		}

		void ql::filesys::copy_unpack_directory(const ql::filesys::path& path)
		{
			if (!path.is_directory())
			{
				return;
			}
			auto cd = path;
			cd.go_directory_back();
			auto l = path.list_current_directory();
			for (auto& i : l)
			{
				i.copy(cd);
			}
		}

		void ql::filesys::move_unpack_directory(const ql::filesys::path& path)
		{
			if (!path.is_directory())
			{
				return;
			}
			auto cd = path;
			cd.go_directory_back();
			auto l = path.list_current_directory();
			for (auto& i : l)
			{
				i.move(cd);
			}
			path.remove();
		}

		ql::filesys::paths
		ql::filesys::search_where_extension_equals(const ql::filesys::path& directory, const std::string& extension)
		{
			return directory.search_where_extension_equals(extension);
		}

		ql::filesys::paths ql::filesys::search_where_extension_contains(const ql::filesys::path& directory, const std::string& regex)
		{
			return directory.search_where_extension_contains(regex);
		}

		ql::filesys::paths ql::filesys::search_where_name_equals(const ql::filesys::path& directory, const std::string& name)
		{
			return directory.search_where_name_equals(name);
		}

		ql::filesys::paths ql::filesys::search_where_name_contains(const ql::filesys::path& directory, const std::string& regex)
		{
			return directory.search_where_name_contains(regex);
		}

		ql::filesys::paths
		ql::filesys::search_where_extension_doesnt_equal(const ql::filesys::path& directory, const std::string& extension)
		{
			return directory.search_where_extension_doesnt_equal(extension);
		}

		ql::filesys::paths
		ql::filesys::search_where_extension_doesnt_contain(const ql::filesys::path& directory, const std::string& regex)
		{
			return directory.search_where_extension_doesnt_contain(regex);
		}

		ql::filesys::paths ql::filesys::search_where_name_doesnt_equal(const ql::filesys::path& directory, const std::string& name)
		{
			return directory.search_where_name_doesnt_equal(name);
		}

		ql::filesys::paths ql::filesys::search_where_name_doesnt_contain(const ql::filesys::path& directory, const std::string& regex)
		{
			return directory.search_where_name_doesnt_contain(regex);
		}

		void ql::filesys::remove_all(const ql::filesys::paths& files)
		{
			for (auto& i : files)
			{
				i.remove();
			}
		}

		void ql::filesys::move_all(const ql::filesys::paths& files, const ql::filesys::path& path_destination)
		{
			for (auto& i : files)
			{
				i.move(path_destination);
			}
		}

		void ql::filesys::copy_all(const ql::filesys::paths& files, const ql::filesys::path& path_destination)
		{
			for (auto& i : files)
			{
				i.copy(path_destination);
			}
		}

		void ql::filesys::move_all_overwrite(const ql::filesys::paths& files, const ql::filesys::path& path_destination)
		{
			for (auto& i : files)
			{
				i.move_overwrite(path_destination);
			}
		}

		void ql::filesys::copy_all_overwrite(const ql::filesys::paths& files, const ql::filesys::path& path_destination)
		{
			for (auto& i : files)
			{
				ql::println(i);
			}
		}

		void ql::filesys::move_all_files(const ql::filesys::paths& files, const ql::filesys::path& path_destination)
		{
			for (auto& i : files)
			{
				if (i.is_file())
				{
					i.move(path_destination);
				}
			}
		}

		void ql::filesys::copy_all_files(const ql::filesys::paths& files, const ql::filesys::path& path_destination)
		{
			for (auto& i : files)
			{
				if (i.is_file())
				{
					i.copy(path_destination);
				}
			}
		}

		void ql::filesys::move_all_files_overwrite(const ql::filesys::paths& files, const ql::filesys::path& path_destination)
		{
			for (auto& i : files)
			{
				if (i.is_file())
				{
					i.move_overwrite(path_destination);
				}
			}
		}

		void ql::filesys::copy_all_files_overwrite(const ql::filesys::paths& files, const ql::filesys::path& path_destination)
		{
			for (auto& i : files)
			{
				if (i.is_file())
				{
					i.copy_overwrite(path_destination);
				}
			}
		}

		std::string ql::filesys::read_file(const std::string& path)
		{
			std::ifstream file(path, std::ios::ate | std::ios::binary);

			if (!file.is_open())
			{
				throw std::runtime_error(ql::to_string("ql::filesys::read_file: failed to open file \"", path, "\"").c_str());
			}

			auto file_size = (size_t)file.tellg();
			std::string buffer;
			buffer.resize(file_size);

			file.seekg(0);
			file.read(buffer.data(), file_size);

			file.close();

			return buffer;
		}

		std::string read_rest_of_file(std::ifstream& file, bool close_file)
		{
			if (!file.is_open())
			{
				return "";
			}

			auto file_pos = (size_t)file.tellg();
			file.seekg(0, std::ios::end);
			auto file_size = ((size_t)file.tellg() - file_pos);

			std::string buffer;
			buffer.resize(file_size);

			file.seekg(file_pos);
			file.read(buffer.data(), file_size);

			if (close_file)
			{
				file.close();
			}

			return buffer;
		}

		std::filesystem::file_time_type ql::filesys::file_last_write_time(const std::string& path)
		{
			ql::filesys::path p = path;
			return p.last_write_time();
		}

		std::string ql::filesys::file_last_write_time_str(const std::string& path)
		{
			return ql::get_time_string(ql::filesys::file_last_write_time(path));
		}

		void ql::filesys::write_to_file(const std::string& text, const std::string& path)
		{
			std::ofstream file(path, std::ios::app);
			file << text;
			file.close();
		}

		void ql::filesys::write_to_file(const std::wstring& text, const std::string& path)
		{
			FILE* outFile;
			auto error = fopen_s(&outFile, path.c_str(), "a,ccs=UTF-8");
			if (error || !outFile)
			{
				throw ql::exception("error opening ", path);
			}

			fputws(text.c_str(), outFile);
			fclose(outFile);
		}

		void ql::filesys::writeln_to_file(const std::string& text, const std::string& path)
		{
			std::ofstream file(path, std::ios::app);
			file << text << '\n';
			file.close();
		}

		void ql::filesys::writeln_to_file(const std::wstring& text, const std::string& path)
		{
			std::wofstream file(path, std::ios::app);
			file << text << L'\n';
			file.close();
		}

		void ql::filesys::write_data_file(const std::string& data, const std::string& path)
		{
			std::ofstream file(path, std::ios::binary);
			file << data;
			file.close();
		}

		void ql::filesys::write_text_file(const std::string& data, const std::string& path)
		{
			std::ofstream file(path);
			file << data;
			file.close();
		}

		ql::filesys::path ql::filesys::get_current_location()
		{
			return ql::filesys::path::current_path();
		}

		std::string ql::filesys::file_encrypt(const std::string& path, const std::string& key, ql::aes::mode mode)
		{
			return ql::encrypted_keep_size(ql::filesys::read_file(path), key, mode);
		}

		void ql::filesys::file_encrypt_to(
				const std::string& source_path,
				const std::string& dest_path,
				const std::string& key,
				ql::aes::mode mode
		)
		{
			auto content = ql::filesys::file_encrypt(source_path, key, mode);
			ql::filesys::write_data_file(content, dest_path);
		}

		std::string ql::filesys::file_decrypt(const std::string& path, const std::string& key, ql::aes::mode mode)
		{
			return ql::decrypted_keep_size(ql::filesys::read_file(path), key, mode);
		}

		void ql::filesys::file_decrypt_to(
				const std::string& source_path,
				const std::string& dest_path,
				const std::string& key,
				ql::aes::mode mode
		)
		{
			auto content = ql::filesys::file_decrypt(source_path, key, mode);
			ql::filesys::write_data_file(content, dest_path);
		}
	}	 // namespace filesys

	std::string ql::read_file(const std::string& path)
	{
		return ql::filesys::read_file(path);
	}

	void ql::write_to_file(const std::string& text, const std::string& path)
	{
		return ql::filesys::write_to_file(text, path);
	}

	void ql::write_data_file(const std::string& data, const std::string& path)
	{
		return ql::filesys::write_data_file(data, path);
	}

	void ql::write_text_file(const std::string& data, const std::string& path)
	{
		return ql::filesys::write_text_file(data, path);
	}

}	 // namespace ql