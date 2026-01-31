#include <ql/core/encryption/file-encrypter/file-encrypter.hpp>

#include <ql/core/string/compare.hpp>

namespace ql
{
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

	void ql::file_encrypter::clear()
	{
		this->paths.clear();
		this->additions = 0u;
		this->part_paths.clear();
	}

	void ql::file_encrypter::add(std::string path)
	{
		auto file_path = ql::filesys::path(path);

		auto adding = file_path.get_file_extension().starts_with(this->keyword_string_part);

		if (adding)
		{
			if (!this->adding_parts)
				++this->additions;

			auto name = file_path.get_file_name();
			this->part_paths[name].push_back(file_path);
		}
		else
		{
			this->paths.push_back(path);
			++this->additions;
		}
		this->adding_parts = adding;

		if (this->common_branch.empty())
			this->common_branch = path;

		else
			this->common_branch = this->common_branch.get_common_branch(path);

		if (file_path.is_file())
			return;

		auto files = file_path.list_current_directory_tree();
		for (auto& i : files)
		{
			if (i.is_directory())
			{
				if (i.to_string().back() != '/')
					i.append("/");
			}
			this->paths.push_back(i);

			if (this->common_branch.empty())
				this->common_branch = i;

			else
				this->common_branch = this->common_branch.get_common_branch(i);
		}
	}

	ql::filesys::paths ql::file_encrypter::encrypt(
			const std::string& key,
			std::string output_name,
			ql::aes::mode mode,
			ql::filesys::path destination_path,
			ql::size split_size
	)
	{
		switch (mode)
		{
			case ql::aes::mode::_128:
				return this->encrypt(key, output_name, ql::aes_128_encrypted_keep_size, destination_path, split_size);
				break;

			case ql::aes::mode::_192:
				return this->encrypt(key, output_name, ql::aes_192_encrypted_keep_size, destination_path, split_size);
				break;

			case ql::aes::mode::_256:
				return this->encrypt(key, output_name, ql::aes_256_encrypted_keep_size, destination_path, split_size);
				break;
		}
		return {};
	}

	ql::filesys::paths ql::file_encrypter::decrypt(const std::string& key, ql::aes::mode mode, ql::filesys::path destination_path) const
	{
		switch (mode)
		{
			case ql::aes::mode::_128:
				return this->decrypt(key, ql::aes_128_decrypted_keep_size, destination_path);
				break;

			case ql::aes::mode::_192:
				return this->decrypt(key, ql::aes_192_decrypted_keep_size, destination_path);
				break;

			case ql::aes::mode::_256:
				return this->decrypt(key, ql::aes_256_decrypted_keep_size, destination_path);
				break;
		}
		return {};
	}
}	 // namespace ql
