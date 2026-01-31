#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/type/type.hpp>

#include <ql/core/encryption/encryption.hpp>

#include <ql/core/advanced-type/memory/string-collection.hpp>

#include <ql/core/advanced-type/memory/save-state.hpp>

#include <ql/core/transform/sort.hpp>
#include <ql/core/string/format/format.hpp>

#include <ql/core/file-system/paths/paths.hpp>

#include <string>

#include <filesystem>
#include <functional>
#include <regex>
#include <fstream>

namespace ql
{
	namespace filesys
	{
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
	}

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
			save_state.save(this->common_branch.to_string());
			save_state.save(this->paths.size());

			for (auto& i : this->paths)
			{
				save_state.save(i.to_string());
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
		ql::filesys::paths encrypt(
				const std::string& key,
				std::string output_name,
				F&& encryption_function,
				ql::filesys::path destination_path,
				ql::size split_size = ql::size_max
		)
		{
			if (!destination_path.empty() && destination_path.to_string().back() != '/')
				destination_path.append("/");

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
					auto part_string =
							ql::to_string(".", this->keyword_string_part, ql::string_prepended(ql::to_string(i), '0', ql::size_cast(log)));

					auto path = encrypted_path;
					path.append(part_string);

					while (path.exists())
					{
						encrypted_path = ql::to_string(destination_path, output_name, '.', this->keyword_string_enrypted, ctr);
						path = encrypted_path;
						path.append(part_string);
						++ctr;
					}

					ql::filesys::write_data_file(splits[i], path.to_string());
				}
			}
			else
				encrypted_path.write_data_file(str);

			return this->paths;
		}

		ql::filesys::paths encrypt(
			const std::string& key,
			std::string output_name,
			ql::aes::mode mode,
			ql::filesys::path destination_path = "",
			ql::size split_size = ql::size_max
		);

		template <typename F>
		ql::filesys::paths decrypt(const std::string& key, F decryption_function, ql::filesys::path destination_path = "") const
		{
			if (!destination_path.empty() && destination_path.to_string().back() != '/')
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
		void internal_decrypt(
			const std::string& string,
			const std::string& key,
			F decryption_function,
			ql::filesys::path destination_path,
			ql::filesys::paths& tree
		) const
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
					is_file_hash.insert(path_str);

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

					ql::filesys::write_data_file(data_str, decrypted_path.to_string());
				}
				tree.push_back(decrypted_path);
			}
		}
	};
}	 // namespace ql