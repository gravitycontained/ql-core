#include <ql/core/advanced-type/memory/string-collection.hpp>
#include <ql/core/type/bit/bit.hpp>
#include <ql/core/transform/cast/cast.hpp>

namespace ql
{
	void ql::string_collection::set_string(const std::string& string)
	{
		this->string = string;
		this->index = 0u;
	}

	bool ql::string_collection::set_string_and_read(const std::string& string)
	{
		this->set_string(string);
		return this->read_info();
	}

	bool ql::string_collection::read_info()
	{
		if (this->string.length() < ql::bytes_in_type<ql::u32>())
		{
			return false;
		}
		ql::size position = 0;
		ql::u32 size_size;
		this->index = 0u;
		memcpy(&size_size, this->string.data() + position, ql::bytes_in_type<ql::u32>());
		position += ql::bytes_in_type<ql::u32>();

		if (string.length() < (position + size_size * ql::bytes_in_type<ql::size>() * 2))
		{
			return false;
		}
		this->sizes.resize(size_size);
		for (ql::u32 i = 0u; i < size_size; ++i)
		{
			ql::size size;
			memcpy(&size, this->string.data() + position, ql::bytes_in_type<ql::size>());
			position += ql::bytes_in_type<ql::size>();
			this->sizes[i].first = size;
			memcpy(&size, this->string.data() + position, ql::bytes_in_type<ql::size>());
			position += ql::bytes_in_type<ql::size>();
			this->sizes[i].second = size;
		}
		return true;
	}

	std::string ql::string_collection::get_next_string() const
	{
		return this->get_string(this->index++);
	}

	std::string_view ql::string_collection::get_next_string_sv() const
	{
		return this->get_string_sv(this->index++);
	}

	std::string ql::string_collection::get_string() const
	{
		return this->string;
	}

	std::string_view ql::string_collection::get_string_sv() const
	{
		return this->string;
	}

	std::string ql::string_collection::get_string(ql::size index) const
	{
		if (index >= this->sizes.size())
		{
			throw std::exception(
					ql::to_string("ql::string_collection::get_string(", index, "): size is only ", this->sizes.size()).c_str());
		}
		return std::string(this->string.begin() + this->sizes[index].first, this->string.begin() + this->sizes[index].second);
	}

	std::string_view ql::string_collection::get_string_sv(ql::size index) const
	{
		if (index >= this->sizes.size())
		{
			throw std::exception(
					ql::to_string("ql::string_collection::get_string_sv(", index, "): size is only ", this->sizes.size()).c_str());
		}
		return std::string_view(this->string.begin() + this->sizes[index].first, this->string.begin() + this->sizes[index].second);
	}

	std::string ql::string_collection::get_finalized_string()
	{
		this->finalize();
		return this->get_string();
	}

	std::string_view ql::string_collection::get_finalized_string_sv()
	{
		this->finalize();
		return this->get_string_sv();
	}

	void ql::string_collection::add_string(const std::string& string)
	{
		auto back = this->string.length();
		this->string.append(string);
		this->sizes.push_back({ql::size_cast(back), ql::size_cast(back + string.length())});
	}

	void ql::string_collection::finalize()
	{
		auto header_size = ql::bytes_in_type<ql::u32>() + (this->sizes.size() * 2 * ql::bytes_in_type<ql::size>());
		std::ostringstream stream;

		ql::u32 size_size = ql::u32_cast(this->sizes.size());
		stream.write(reinterpret_cast<const char*>(&size_size), ql::bytes_in_type<ql::u32>());
		for (auto& i : this->sizes)
		{
			i.first += header_size;
			i.second += header_size;
			stream.write(reinterpret_cast<const char*>(&i.first), ql::bytes_in_type<ql::size>());
			stream.write(reinterpret_cast<const char*>(&i.second), ql::bytes_in_type<ql::size>());
		}

		auto copy = this->string;
		this->string.clear();
		this->string.append(stream.str());
		this->string.append(copy);
	}

	ql::size ql::string_collection::size() const
	{
		return this->sizes.size();
	}

	void ql::string_collection::clear()
	{
		this->sizes.clear();
		this->string.clear();
	}
}