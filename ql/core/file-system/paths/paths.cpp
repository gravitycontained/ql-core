#include <ql/core/file-system/file-system.hpp>

#include <ql/core/string/compare.hpp>

namespace ql
{
	namespace filesys
	{
		ql::filesys::paths& ql::filesys::paths::operator=(const std::vector<ql::filesys::path>& paths)
		{
			this->m_paths = paths;
			return *this;
		}

		ql::filesys::paths& ql::filesys::paths::operator=(const ql::filesys::paths& paths)
		{
			this->m_paths = paths.m_paths;
			return *this;
		}

		std::vector<ql::filesys::path>::iterator ql::filesys::paths::begin()
		{
			return this->m_paths.begin();
		}

		std::vector<ql::filesys::path>::const_iterator ql::filesys::paths::begin() const
		{
			return this->m_paths.cbegin();
		}

		std::vector<ql::filesys::path>::const_iterator ql::filesys::paths::cbegin() const
		{
			return this->m_paths.cbegin();
		}

		std::vector<ql::filesys::path>::reverse_iterator ql::filesys::paths::rbegin()
		{
			return this->m_paths.rbegin();
		}

		std::vector<ql::filesys::path>::iterator ql::filesys::paths::end()
		{
			return this->m_paths.end();
		}

		std::vector<ql::filesys::path>::const_iterator ql::filesys::paths::end() const
		{
			return this->m_paths.cend();
		}

		std::vector<ql::filesys::path>::const_iterator ql::filesys::paths::cend() const
		{
			return this->m_paths.cend();
		}

		std::vector<ql::filesys::path>::reverse_iterator ql::filesys::paths::rend()
		{
			return this->m_paths.rend();
		}

		void ql::filesys::paths::copy_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			for (auto& i : this->m_paths)
			{
				std::filesystem::copy(i.to_string(), destination.to_string(), std::filesystem::copy_options::recursive);
			}
		}

		void ql::filesys::paths::move_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			for (auto& i : this->m_paths)
			{
				std::filesystem::copy(i.to_string(), destination.to_string(), std::filesystem::copy_options::recursive);
				i.remove();
			}
		}

		void ql::filesys::paths::copy_overwrite_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			for (auto& i : this->m_paths)
			{
				std::filesystem::copy(
						i.to_string(), destination.to_string(),
						std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
				);
			}
		}

		void ql::filesys::paths::move_overwrite_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			for (auto& i : this->m_paths)
			{
				std::filesystem::copy(
						i.to_string(), destination.to_string(),
						std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
				);
				i.remove();
			}
		}

		void ql::filesys::paths::copy_files_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			for (auto& i : this->m_paths)
			{
				if (i.is_file())
				{
					std::filesystem::copy(i.to_string(), destination.to_string(), std::filesystem::copy_options::recursive);
				}
			}
		}

		void ql::filesys::paths::move_files_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			for (auto& i : this->m_paths)
			{
				if (i.is_file())
				{
					std::filesystem::copy(i.to_string(), destination.to_string(), std::filesystem::copy_options::recursive);
					i.remove();
				}
			}
		}

		void ql::filesys::paths::copy_overwrite_files_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			for (auto& i : this->m_paths)
			{
				if (i.is_file())
				{
					std::filesystem::copy(
							i.to_string(), destination.to_string(),
							std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
					);
				}
			}
		}

		void ql::filesys::paths::move_overwrite_files_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			for (auto& i : this->m_paths)
			{
				if (i.is_file())
				{
					std::filesystem::copy(
							i.to_string(), destination.to_string(),
							std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
					);
					i.remove();
				}
			}
		}

		void ql::filesys::paths::copy_as_tree_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			ql::filesys::path tree_destination = destination;
			auto levels = this->m_paths.front().branch_size() - 1;
			ql::u32 depth_ctr = ql::u32_cast(levels);

			for (auto& i : this->m_paths)
			{
				auto branch_size = i.branch_size();

				if (depth_ctr != branch_size)
				{
					tree_destination = destination;
					depth_ctr = ql::u32_cast(levels);
					for (ql::size l = levels; l < i.branch_size(); ++l)
					{
						tree_destination.go_into(i.get_branch_at(l).get_name());
						++depth_ctr;
					}
				}

				if (i.is_directory())
				{
					tree_destination.create();
				}
				else if (i.is_file())
				{
					std::filesystem::copy(i.to_string(), tree_destination.to_string(), std::filesystem::copy_options::recursive);
				}
			}
		}

		void ql::filesys::paths::move_as_tree_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			ql::filesys::path tree_destination = destination;
			auto levels = this->m_paths.front().branch_size() - 1;
			ql::size depth_ctr = levels;

			for (auto& i : this->m_paths)
			{
				auto branch_size = i.branch_size();

				if (depth_ctr != branch_size)
				{
					tree_destination = destination;
					depth_ctr = levels;
					for (ql::size l = levels; l < i.branch_size(); ++l)
					{
						tree_destination.go_into(i.get_branch_at(l).get_name());
						++depth_ctr;
					}
				}

				if (i.is_directory())
				{
					tree_destination.create();
				}
				else if (i.is_file())
				{
					std::filesystem::copy(i.to_string(), tree_destination.to_string(), std::filesystem::copy_options::recursive);
					i.remove();
				}
			}
		}

		void ql::filesys::paths::copy_overwrite_as_tree_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			ql::filesys::path tree_destination = destination;
			auto levels = this->m_paths.front().branch_size() - 1;
			ql::u32 depth_ctr = ql::u32_cast(levels);

			for (auto& i : this->m_paths)
			{
				auto branch_size = i.branch_size();

				if (depth_ctr != branch_size)
				{
					tree_destination = destination;
					depth_ctr = ql::u32_cast(levels);
					for (ql::size l = levels; l < i.branch_size(); ++l)
					{
						tree_destination.go_into(i.get_branch_at(l).get_name());
						++depth_ctr;
					}
				}

				if (i.is_directory())
				{
					tree_destination.create();
				}
				else if (i.is_file())
				{
					std::filesystem::copy(
							i.to_string(), tree_destination.to_string(),
							std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
					);
				}
			}
		}

		void ql::filesys::paths::move_overwrite_as_tree_to(ql::filesys::path destination)
		{
			if (destination.is_directory())
			{
				if (!destination.exists())
				{
					destination.create();
				}
			}

			ql::filesys::path tree_destination = destination;
			auto levels = this->m_paths.front().branch_size() - 1;
			auto depth_ctr = levels;

			for (auto& i : this->m_paths)
			{
				auto branch_size = i.branch_size();

				if (depth_ctr != branch_size)
				{
					tree_destination = destination;
					depth_ctr = levels;
					for (ql::size l = levels; l < i.branch_size(); ++l)
					{
						tree_destination.go_into(i.get_branch_at(l).get_name());
						++depth_ctr;
					}
				}

				if (i.is_directory())
				{
					tree_destination.create();
				}
				else if (i.is_file())
				{
					std::filesystem::copy(
							i.to_string(), tree_destination.to_string(),
							std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive
					);
					i.remove();
				}
			}
		}

		ql::size ql::filesys::paths::size() const
		{
			return this->m_paths.size();
		}

		bool ql::filesys::paths::empty() const
		{
			return this->m_paths.empty();
		}

		ql::size ql::filesys::paths::capacity() const
		{
			return this->m_paths.capacity();
		}

		void ql::filesys::paths::resize(ql::size new_size)
		{
			this->m_paths.resize(new_size);
		}

		void ql::filesys::paths::reserve(ql::size new_cap)
		{
			this->m_paths.reserve(new_cap);
		}

		void ql::filesys::paths::clear()
		{
			this->m_paths.clear();
		}

		ql::filesys::path& ql::filesys::paths::front()
		{
			return this->m_paths.front();
		}

		const ql::filesys::path& ql::filesys::paths::front() const
		{
			return this->m_paths.front();
		}

		ql::filesys::path& ql::filesys::paths::back()
		{
			return this->m_paths.back();
		}

		const ql::filesys::path& ql::filesys::paths::back() const
		{
			return this->m_paths.back();
		}

		void ql::filesys::paths::push_back(const ql::filesys::path& path)
		{
			this->m_paths.push_back(path);
		}

		void ql::filesys::paths::emplace_back(ql::filesys::path& path)
		{
			this->m_paths.emplace_back(path);
		}

		void ql::filesys::paths::pop_back()
		{
			this->m_paths.pop_back();
		}

		ql::filesys::path& ql::filesys::paths::operator[](ql::size index)
		{
			return this->m_paths[index];
		}

		const ql::filesys::path& ql::filesys::paths::operator[](ql::size index) const
		{
			return this->m_paths[index];
		}

		ql::filesys::path& ql::filesys::paths::at(ql::size index)
		{
			return this->m_paths.at(index);
		}

		const ql::filesys::path& ql::filesys::paths::at(ql::size index) const
		{
			return this->m_paths.at(index);
		}

		void ql::filesys::paths::print_tree() const
		{
			if (this->m_paths.empty())
			{
				return;
			}

			std::vector<std::string> branch_names = this->m_paths.front().get_branch_names();
			std::vector<std::string> current_branch_names;

			auto print_branch_space = [&](ql::size stop)
			{
				for (ql::size i = 0u; i < stop; ++i)
				{
					auto width = branch_names[i].length();
					ql::print(ql::string_repeat(' ', width + 1));
					if (i == branch_names.size() - 1)
					{
						ql::print("|");
					}
					else
					{
						ql::print("|");
					}
				}
			};

			auto print_branch_names = [&](ql::u32 start)
			{
				for (ql::u32 i = start; i < branch_names.size(); ++i)
				{
					print_branch_space(i);

					ql::println("_ ", branch_names[i]);
				}
			};

			print_branch_names(0u);

			for (auto& path : this->m_paths)
			{
				current_branch_names = path.get_branch_names();

				bool not_equal = false;
				ql::u32 i = 0u;
				for (; i < current_branch_names.size() && i < branch_names.size(); ++i)
				{
					not_equal = !ql::string_equals_ignore_case(current_branch_names[i], branch_names[i]);
					if (not_equal)
					{
						branch_names = current_branch_names;
						print_branch_names(i);

						if (path.is_file())
						{
							print_branch_space(branch_names.size());
							ql::println("_ ", path.get_full_name(true));
						}
						break;
					}
				}

				if (!not_equal)
				{
					branch_names = current_branch_names;
					print_branch_space(branch_names.size());
					ql::println("_ ", path.get_full_name(true));
				}
			}
		}

		void ql::filesys::paths::list_remove_where_lambda(const std::function<bool(ql::filesys::path)>& check)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (!check(i))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_keep_where_lambda(const std::function<bool(ql::filesys::path)>& check)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (check(i))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add(const ql::filesys::path& path)
		{
			this->m_paths.push_back(path);
		}

		void ql::filesys::paths::list_add_recursively(const ql::filesys::path& path)
		{
			auto list = path.list_current_directory_tree();
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_add_directories(const ql::filesys::path& directory)
		{
			auto list = directory.search_directories();
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_directories(const ql::filesys::path& directory)
		{
			auto list = directory.search_recursively_directories();
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_remove_directories()
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (!i.is_directory())
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add_files(const ql::filesys::path& directory)
		{
			auto list = directory.search_files();
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_files(const ql::filesys::path& directory)
		{
			auto list = directory.search_recursively_files();
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_remove_files()
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (!i.is_file())
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_remove_where_directory_matches(const std::string& str)
		{
			ql::size level = 0u;
			bool remove = false;

			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (i.get_name() == str)
				{
					remove = true;
					level = i.branch_size() - 1;
				}
				else if (remove)
				{
					if (i.get_branch_at(level).get_name() != str)
					{
						this->emplace_back(i);
						remove = false;
					}
				}
				else
				{
					this->emplace_back(i);
				}
			}

			for (auto& i : this->m_paths)
			{
				if (i.get_name() == str)
				{
				}
			}
		}

		void ql::filesys::paths::list_remove_where_extension_equals(const std::string_view& extension)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (!i.extension_equals(extension))
				{
					this->emplace_back(i);
				}
			}
		}

		void
		ql::filesys::paths::list_add_where_extension_equals(const ql::filesys::path& directory, const std::string_view& extension)
		{
			auto list = directory.search_where_extension_equals(extension);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_extension_equals(
				const ql::filesys::path& directory,
				const std::string_view& extension
		)
		{
			auto list = directory.search_recursively_where_extension_equals(extension);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_remove_where_extension_contains(const std::string_view& str)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (!i.extension_contains(str))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add_where_extension_contains(const ql::filesys::path& directory, const std::string_view& str)
		{
			auto list = directory.search_where_extension_contains(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_extension_contains(
				const ql::filesys::path& directory,
				const std::string_view& str
		)
		{
			auto list = directory.search_recursively_where_extension_contains(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_remove_where_name_equals(const std::string_view& name)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (!i.name_equals(name))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add_where_name_equals(const ql::filesys::path& directory, const std::string_view& name)
		{
			auto list = directory.search_where_name_equals(name);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void
		ql::filesys::paths::list_recursively_add_where_name_equals(const ql::filesys::path& directory, const std::string_view& name)
		{
			auto list = directory.search_recursively_where_name_equals(name);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_remove_where_name_contains(const std::string_view& str)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (!i.name_contains(str))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add_where_name_contains(const ql::filesys::path& directory, const std::string_view& str)
		{
			auto list = directory.search_where_name_contains(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void
		ql::filesys::paths::list_recursively_add_where_name_contains(const ql::filesys::path& directory, const std::string_view& str)
		{
			auto list = directory.search_recursively_where_name_contains(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_remove_where_file_name_equals(const std::string_view& file_name)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (!i.file_name_equals(file_name))
				{
					this->emplace_back(i);
				}
			}
		}

		void
		ql::filesys::paths::list_add_where_file_name_equals(const ql::filesys::path& directory, const std::string_view& file_name)
		{
			auto list = directory.search_where_file_name_equals(file_name);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_file_name_equals(
				const ql::filesys::path& directory,
				const std::string_view& file_name
		)
		{
			auto list = directory.search_recursively_where_file_name_equals(file_name);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_remove_where_file_name_contains(const std::string_view& str)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (!i.file_name_contains(str))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add_where_file_name_contains(const ql::filesys::path& directory, const std::string_view& str)
		{
			auto list = directory.search_where_file_name_contains(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_file_name_contains(
				const ql::filesys::path& directory,
				const std::string_view& str
		)
		{
			auto list = directory.search_recursively_where_file_name_contains(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_keep_where_extension_equals(const std::string_view& extension)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (i.extension_equals(extension))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add_where_extension_doesnt_equal(
				const ql::filesys::path& directory,
				const std::string_view& extension
		)
		{
			auto list = directory.search_where_extension_doesnt_equal(extension);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_extension_doesnt_equal(
				const ql::filesys::path& directory,
				const std::string_view& extension
		)
		{
			auto list = directory.search_recursively_where_extension_doesnt_equal(extension);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_keep_where_extension_contains(const std::string_view& str)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (i.extension_contains(str))
				{
					this->emplace_back(i);
				}
			}
		}

		void
		ql::filesys::paths::list_add_where_extension_doesnt_contain(const ql::filesys::path& directory, const std::string_view& str)
		{
			auto list = directory.search_where_extension_doesnt_contain(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_extension_doesnt_contain(
				const ql::filesys::path& directory,
				const std::string_view& str
		)
		{
			auto list = directory.search_recursively_where_extension_doesnt_contain(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_keep_where_name_equals(const std::string_view& name)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (i.name_equals(name))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add_where_name_doesnt_equal(const ql::filesys::path& directory, const std::string_view& name)
		{
			auto list = directory.search_where_name_doesnt_equal(name);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_name_doesnt_equal(
				const ql::filesys::path& directory,
				const std::string_view& name
		)
		{
			auto list = directory.search_recursively_where_name_doesnt_equal(name);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_keep_where_name_contains(const std::string_view& str)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (i.name_contains(str))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add_where_name_doesnt_contain(const ql::filesys::path& directory, const std::string_view& str)
		{
			auto list = directory.search_where_name_doesnt_contain(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_name_doesnt_contain(
				const ql::filesys::path& directory,
				const std::string_view& str
		)
		{
			auto list = directory.search_recursively_where_name_doesnt_contain(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_keep_where_file_name_equals(const std::string_view& file_name)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (i.file_name_equals(file_name))
				{
					this->emplace_back(i);
				}
			}
		}

		void ql::filesys::paths::list_add_where_file_name_doesnt_equal(
				const ql::filesys::path& directory,
				const std::string_view& file_name
		)
		{
			auto list = directory.search_where_file_name_doesnt_equal(file_name);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_file_name_doesnt_equal(
				const ql::filesys::path& directory,
				const std::string_view& file_name
		)
		{
			auto list = directory.search_recursively_where_file_name_doesnt_equal(file_name);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_keep_where_file_name_contains(const std::string_view& str)
		{
			auto copy = this->m_paths;
			this->clear();
			for (auto& i : copy)
			{
				if (i.file_name_contains(str))
				{
					this->emplace_back(i);
				}
			}
		}

		void
		ql::filesys::paths::list_add_where_file_name_doesnt_contain(const ql::filesys::path& directory, const std::string_view& str)
		{
			auto list = directory.search_where_file_name_doesnt_contain(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

		void ql::filesys::paths::list_recursively_add_where_file_name_doesnt_contain(
				const ql::filesys::path& directory,
				const std::string_view& str
		)
		{
			auto list = directory.search_recursively_where_file_name_doesnt_contain(str);
			this->m_paths.insert(this->m_paths.end(), list.m_paths.begin(), list.m_paths.end());
		}

	}	 // namespace filesys
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
			{
				++this->additions;
			}
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
		{
			this->common_branch = path;
		}
		else
		{
			this->common_branch = this->common_branch.get_common_branch(path);
		}

		if (file_path.is_file())
		{
			return;
		}

		auto files = file_path.list_current_directory_tree();
		for (auto& i : files)
		{
			if (i.is_directory())
			{
				if (i.to_string().back() != '/')
				{
					i.append("/");
				}
			}
			this->paths.push_back(i);

			if (this->common_branch.empty())
			{
				this->common_branch = i;
			}
			else
			{
				this->common_branch = this->common_branch.get_common_branch(i);
			}
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

	ql::filesys::paths
	ql::file_encrypter::decrypt(const std::string& key, ql::aes::mode mode, ql::filesys::path destination_path) const
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
