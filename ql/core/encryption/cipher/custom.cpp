#include <ql/core/encryption/cipher/custom.hpp>

#include <ql/core/string/to-string.hpp>

#include <ql/core/transform/bit/bit.hpp>

#include <ql/core/transform/limit.hpp>
#include <sstream>
#include <iomanip>

namespace ql
{

	void ql::sha256::reset()
	{
		this->blocklen = 0u;
		this->bitlen = 0u;

		this->state[0] = 0x6a09e667u;
		this->state[1] = 0xbb67ae85u;
		this->state[2] = 0x3c6ef372u;
		this->state[3] = 0xa54ff53au;
		this->state[4] = 0x510e527fu;
		this->state[5] = 0x9b05688cu;
		this->state[6] = 0x1f83d9abu;
		this->state[7] = 0x5be0cd19u;
	}

	void ql::sha256::update(const std::string_view& data)
	{
		for (ql::size i = 0u; i < data.length(); ++i)
		{
			this->data[this->blocklen] = ql::u8_cast(data[i]);

			++this->blocklen;
			if (this->blocklen == 64u)
			{
				this->transform();

				// End of the block
				this->bitlen += this->message_size;
				this->blocklen = 0u;
			}
		}
	}

	auto ql::sha256::digest()
	{
		hash_result hash;

		this->add_padding();
		this->revert(hash);

		return hash;
	}

	void ql::sha256::transform()
	{
		utype maj, xorA, ch, xorE, sum, newA, newE;

		std::array<utype, this->round_size> m;
		std::array<utype, this->state_size> new_state;

		for (ql::size i = 0u, j = 0u; i < this->sequence_size; ++i, j += 4)
		{
			m[i] = (this->data[j + 0u] << 24u) | (this->data[j + 1u] << 16u) | (this->data[j + 2u] << 8u) | (this->data[j + 3u]);
		}

		for (ql::size i = this->sequence_size; i < m.size(); ++i)
		{
			m[i] = this->sig1(m[i - 2u]) + m[i - 7u] + this->sig0(m[i - 15u]) + m[i - 16u];
		}

		for (ql::size i = 0u; i < this->state.size(); ++i)
		{
			new_state[i] = this->state[i];
		}

		for (uint8_t i = 0; i < this->round_size; i++)
		{
			maj = this->majority(new_state[0u], new_state[1u], new_state[2u]);
			xorA = this->rotr(new_state[0u], 2u) ^ this->rotr(new_state[0], 13u) ^ this->rotr(new_state[0u], 22u);

			ch = this->choose(new_state[4u], new_state[5u], new_state[6u]);

			xorE = this->rotr(new_state[4u], 6u) ^ this->rotr(new_state[4u], 11u) ^ this->rotr(new_state[4u], 25u);

			sum = m[i] + this->table[i] + new_state[7] + ch + xorE;
			newA = xorA + maj + sum;
			newE = new_state[3] + sum;

			new_state[7u] = new_state[6u];
			new_state[6u] = new_state[5u];
			new_state[5u] = new_state[4u];
			new_state[4u] = newE;
			new_state[3u] = new_state[2u];
			new_state[2u] = new_state[1u];
			new_state[1u] = new_state[0u];
			new_state[0u] = newA;
		}

		for (ql::size i = 0u; i < this->state.size(); ++i)
		{
			this->state[i] += new_state[i];
		}
	}

	void ql::sha256::add_padding()
	{
		constexpr auto sub_size = this->block_size - 8u;
		auto end = this->blocklen < sub_size ? sub_size : this->block_size;

		ql::u64 index = this->blocklen;
		this->data[index] = 0x80u;
		++index;

		while (index < end)
		{
			this->data[index] = 0x0u;
			++index;
		}

		if (this->blocklen >= sub_size)
		{
			this->transform();
			memset(this->data.data(), 0u, sub_size);
		}

		this->bitlen += this->blocklen * 8u;

		for (ql::size i = 0u; i < 8u; ++i)
		{
			auto shift = (8u - i - 1);
			this->data[sub_size + shift] = ql::u8_cast(this->bitlen >> (i * 8u));
		}
		this->transform();
	}

	void ql::sha256::revert(ql::sha256::hash_result& hash)
	{
		for (ql::size i = 0u; i < 4u; ++i)
		{
			for (ql::size j = 0u; j < 8u; ++j)
			{
				hash[i + (j * 4u)] = (this->state[j] >> (24u - i * 8u)) & 0xffu;
			}
		}
	}

	std::string ql::sha256::to_string(const ql::sha256::hash_result& hash)
	{
		std::stringstream s;
		s << std::setfill('0') << std::hex;

		for (ql::size i = 0u; i < hash.size(); ++i)
		{
			s << std::setw(2u) << ql::u32_cast(hash[i]);
		}

		return s.str();
	}

	void ql::sha512::reset()
	{
		this->blocklen = 0u;
		this->bitlen = 0u;

		this->state[0] = 0x6a09e667f3bcc908uLL;
		this->state[1] = 0xbb67ae8584caa73buLL;
		this->state[2] = 0x3c6ef372fe94f82buLL;
		this->state[3] = 0xa54ff53a5f1d36f1uLL;
		this->state[4] = 0x510e527fade682d1uLL;
		this->state[5] = 0x9b05688c2b3e6c1fuLL;
		this->state[6] = 0x1f83d9abfb41bd6buLL;
		this->state[7] = 0x5be0cd19137e2179uLL;
	}

	void ql::sha512::update(const std::string_view& data)
	{
		for (ql::size i = 0u; i < data.length(); ++i)
		{
			this->data[this->blocklen] = ql::u8_cast(data[i]);

			++this->blocklen;
			if (this->blocklen == 128u)
			{
				this->transform();

				// End of the block
				this->bitlen += this->message_size;
				this->blocklen = 0u;
			}
		}
	}

	auto ql::sha512::digest()
	{
		hash_result hash;

		this->add_padding();
		this->revert(hash);

		return hash;
	}

	void ql::sha512::transform()
	{
		utype maj, xorA, ch, xorE, sum, newA, newE;

		std::array<utype, this->block_size> m{};
		std::array<utype, this->state_size> new_state;

		for (ql::size i = 0u, j = 0u; i < this->sequence_size; ++i, j += 8)
		{
			m[i] = (this->data[j + 0u] << 56u) | (this->data[j + 1u] << 48u) | (this->data[j + 2u] << 40u) |
						 (this->data[j + 3u] << 32u) | (this->data[j + 4u] << 24u) | (this->data[j + 5u] << 16u) |
						 (this->data[j + 6u] << 8u) | (this->data[j + 7u]);
		}

		for (ql::size i = this->sequence_size; i < m.size(); ++i)
		{
			m[i] = this->sig1(m[i - 2u]) + m[i - 7u] + this->sig0(m[i - 15u]) + m[i - 16u];
		}

		for (ql::size i = 0u; i < this->state.size(); ++i)
		{
			new_state[i] = this->state[i];
		}

		for (uint8_t i = 0; i < this->round_size; i++)
		{
			maj = this->majority(new_state[0u], new_state[1u], new_state[2u]);

			xorA = this->rotr(new_state[0u], 28u) ^ this->rotr(new_state[0], 34u) ^ this->rotr(new_state[0u], 39u);

			ch = this->choose(new_state[4u], new_state[5u], new_state[6u]);

			xorE = this->rotr(new_state[4u], 14u) ^ this->rotr(new_state[4u], 18u) ^ this->rotr(new_state[4u], 41u);

			sum = m[i] + this->table[i] + new_state[7] + ch + xorE;
			newA = xorA + maj + sum;
			newE = new_state[3] + sum;

			new_state[7u] = new_state[6u];
			new_state[6u] = new_state[5u];
			new_state[5u] = new_state[4u];
			new_state[4u] = newE;
			new_state[3u] = new_state[2u];
			new_state[2u] = new_state[1u];
			new_state[1u] = new_state[0u];
			new_state[0u] = newA;
		}

		for (ql::size i = 0u; i < this->state.size(); ++i)
		{
			this->state[i] += new_state[i];
		}
	}

	void ql::sha512::add_padding()
	{
		constexpr auto sub_size = this->block_size - 8u;
		auto end = this->blocklen < sub_size ? sub_size : this->block_size;

		ql::u64 index = this->blocklen;
		this->data[index] = 0x80ull;
		++index;

		while (index < end)
		{
			this->data[index] = 0x0ull;
			++index;
		}

		if (this->blocklen >= sub_size)
		{
			this->transform();
			memset(this->data.data(), 0u, sub_size);
		}

		this->bitlen += this->blocklen * 8u;

		for (ql::size i = 0u; i < 8u; ++i)
		{
			auto shift = (8u - i - 1);
			this->data[sub_size + shift] = (this->bitlen >> (i * 8u));
		}
		this->transform();
	}

	void ql::sha512::revert(ql::sha512::hash_result& hash)
	{
		for (ql::size i = 0u; i < 8u; ++i)
		{
			for (ql::size j = 0u; j < 8u; ++j)
			{
				hash[i + (j * 8u)] = (this->state[j] >> (56u - i * 8u)) & 0xffull;
			}
		}
	}

	std::string ql::sha512::to_string(const ql::sha512::hash_result& hash)
	{
		std::stringstream s;
		s << std::setfill('0') << std::hex;

		for (ql::size i = 0u; i < hash.size(); ++i)
		{
			s << std::setw(2u) << ql::u64_cast(hash[i]);
		}

		return s.str();
	}

	ql::sha256 ql::detail::sha256_t;
	ql::sha512 ql::detail::sha512_t;

	std::string ql::sha256_hash(const std::string_view& string)
	{
		ql::detail::sha256_t.reset();
		ql::detail::sha256_t.update(string);
		auto digest = ql::detail::sha256_t.digest();
		return ql::sha256::to_string(digest);
	}

	std::string ql::sha512_hash(const std::string_view& string)
	{
		ql::detail::sha512_t.reset();
		ql::detail::sha512_t.update(string);
		auto digest = ql::detail::sha512_t.digest();
		return ql::sha512::to_string(digest);
	}

	std::string ql::mgf1(const std::string_view& seed, ql::size length, hash_type hash_object)
	{
		if (length == 0u)
		{
			return "";
		}
		std::string result = "";
		auto blocks = ((length - 1) / (hash_object.second / 4u) + 1);
		for (ql::size i = 0u; i < blocks; ++i)
		{
			auto input = ql::to_string(seed, i);
			result += hash_object.first(input);
		}
		result.resize(length);
		return result;
	}

	std::unique_ptr<ql::detail::aes_tables_t> ql::detail::aes_tables_deprecated;

	void ql::detail::calculate_mul1()
	{
		for (ql::size i = 0u; i < ql::detail::aes_tables_deprecated->mul1.size(); ++i)
		{
			ql::detail::aes_tables_deprecated->mul1[i] = static_cast<ql::u8>(i);
		}
	}

	void ql::detail::calculate_mul2()
	{
		for (ql::size i = 0u; i < ql::detail::aes_tables_deprecated->mul2.size(); ++i)
		{
			ql::detail::aes_tables_deprecated->mul2[i] = static_cast<ql::u8>((i << 1) ^ ((i & 0x80) ? 0x1B : 0x00));
		}
	}

	void ql::detail::calculate_mul3()
	{
		for (ql::size i = 0u; i < ql::detail::aes_tables_deprecated->mul3.size(); ++i)
		{
			ql::detail::aes_tables_deprecated->mul3[i] = static_cast<ql::u8>(ql::detail::aes_tables_deprecated->mul2[i] ^ i);
		}
	}

	void ql::detail::calculate_rcon()
	{
		ql::detail::aes_tables_deprecated->rcon[0] = 0x8d;
		ql::u8 x = 1;
		for (ql::size i = 1u; i < 255u; ++i)
		{
			ql::detail::aes_tables_deprecated->rcon[i] = static_cast<ql::u8>(x);
			x = ql::detail::aes_tables_deprecated->mul2[x];
		}
	}

	void ql::detail::calculate_sbox()
	{
		ql::u8 p = 1, q = 1;

		do
		{
			// multiply p by 2
			p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);

			// divide q by 2
			q ^= q << 1;
			q ^= q << 2;
			q ^= q << 4;
			q ^= q & 0x80 ? 0x09 : 0;

			// compute affine transformation
			unsigned char xformed =
					q ^ ql::bit_rotate_left(q, 1) ^ ql::bit_rotate_left(q, 2) ^ ql::bit_rotate_left(q, 3) ^ ql::bit_rotate_left(q, 4);
			ql::detail::aes_tables_deprecated->sbox[p] = xformed ^ 0x63;

		} while (p - 1);

		// 0 is a special case since it has no inverse
		ql::detail::aes_tables_deprecated->sbox[0] = 0x63;
	}

	void ql::detail::calculate_sbox_inv()
	{
		for (ql::size i = 0u; i < ql::detail::aes_tables_deprecated->sbox_inv.size(); ++i)
		{
			ql::detail::aes_tables_deprecated->sbox_inv[ql::detail::aes_tables_deprecated->sbox[i]] = static_cast<ql::u8>(i);
		}
	}

	void ql::generate_all_aes_tables()
	{
		if (!ql::detail::aes_tables_deprecated)
		{
			ql::detail::aes_tables_deprecated = std::make_unique<detail::aes_tables_t>();
		}
		ql::detail::calculate_mul1();
		ql::detail::calculate_mul2();
		ql::detail::calculate_mul3();
		ql::detail::calculate_rcon();
		ql::detail::calculate_sbox();
		ql::detail::calculate_sbox_inv();
	}

	void ql::aes::construct()
	{
		this->m_constructed = true;
		this->set_mode(mode::_128);
	}

	void ql::aes::error_if_not_constructed() const
	{
		if (!this->m_constructed)
		{
			throw std::exception(ql::to_string("ql::aes: tries to access, but it was not constructed yet. call construct()").c_str());
		}
	}

	void ql::aes::check_constructed()
	{
		if (!this->m_constructed)
		{
			this->construct();
		}
	}

	std::string ql::aes::encrypted(const std::array<ql::u8, 16>& message, const std::string& key)
	{
		this->check_constructed();
		this->set_state(message);
		this->set_key(key);
		this->expand_key();
		this->cipher();
		return this->get_message();
	}

	std::string ql::aes::encrypted(const ql::u8* message, ql::size size, const std::string& key)
	{
		this->check_constructed();
		this->set_key(key);
		this->expand_key();

		std::array<ql::u8, 16> last_block;
		std::array<ql::u8, 16> input_block;
		bool first_block = true;

		std::string result;
		result.reserve((((size ? size - 1 : 0) / this->m_state.size()) + 1) * this->m_state.size());

		for (ql::size i = 0u; i < size / this->m_state.size(); ++i)
		{
			if (first_block)
			{
				for (ql::size c = 0u; c < this->m_state.size(); ++c)
				{
					input_block[c] = message[i * this->m_state.size() + c];
				}
				first_block = false;
			}
			else
			{
				for (ql::size c = 0u; c < this->m_state.size(); ++c)
				{
					input_block[c] = last_block[c] ^ message[i * this->m_state.size() + c];
				}
			}

			this->set_state(input_block);

			this->cipher();

			result.append(reinterpret_cast<const char*>(this->m_state.data()), this->m_state.size());
			std::memcpy(last_block.data(), this->m_state.data(), this->m_state.size());
		}
		if (size % this->m_state.size())
		{
			if (first_block)
			{
				for (ql::size c = 0u; c < this->m_state.size(); ++c)
				{
					if (c >= size % this->m_state.size())
					{
						input_block[c] = ql::u8{};
					}
					else
					{
						input_block[c] = message[(size / this->m_state.size()) * this->m_state.size() + c];
					}
				}
			}
			else
			{
				for (ql::size c = 0u; c < this->m_state.size(); ++c)
				{
					if (c >= size % this->m_state.size())
					{
						input_block[c] = last_block[c] ^ ql::u8{};
					}
					else
					{
						input_block[c] = last_block[c] ^ message[(size / this->m_state.size()) * this->m_state.size() + c];
					}
				}
			}

			this->set_state(input_block);
			this->cipher();
			result.append(reinterpret_cast<const char*>(this->m_state.data()), this->m_state.size());
		}

		return result;
	}

	std::string ql::aes::encrypted(const std::string& message, const std::string& key)
	{
		// auto s = this->encrypted(reinterpret_cast<const ql::u8*>(message.c_str()), message.length(), key);
		// return std::string(std::move(reinterpret_cast<const char*>(s.data())), s.size());
		return this->encrypted(reinterpret_cast<const ql::u8*>(message.c_str()), message.length(), key);
	}

	std::wstring ql::aes::encrypted(const std::wstring& message, const std::string& key)
	{
		auto s = this->encrypted(reinterpret_cast<const ql::u8*>(message.c_str()),
														 message.length() * (sizeof(wchar_t) / sizeof(char)), key);
		return std::wstring(std::move(reinterpret_cast<const wchar_t*>(s.data())), s.size() / (sizeof(wchar_t) / sizeof(char)));
	}

	std::string ql::aes::encrypted(const std::vector<char>& message, const std::string& key)
	{
		auto s = this->encrypted(reinterpret_cast<const ql::u8*>(message.data()), message.size(), key);
		return std::string(std::move(reinterpret_cast<const char*>(s.data())), s.size());
	}

	std::wstring ql::aes::encrypted(const std::vector<wchar_t>& message, const std::string& key)
	{
		auto s =
				this->encrypted(reinterpret_cast<const ql::u8*>(message.data()), message.size() * (sizeof(wchar_t) / sizeof(char)), key);
		return std::wstring(std::move(reinterpret_cast<const wchar_t*>(s.data())), s.size() / (sizeof(wchar_t) / sizeof(char)));
	}

	void ql::aes::encrypt(std::string& message, const std::string& key)
	{
		message = this->encrypted(reinterpret_cast<const ql::u8*>(message.c_str()), message.length(), key);
		// ql::container_memory_to_string(s, message);
	}

	void ql::aes::encrypt(std::wstring& message, const std::string& key)
	{
		auto s = this->encrypted(reinterpret_cast<const ql::u8*>(message.c_str()),
														 message.length() * (sizeof(wchar_t) / sizeof(char)), key);
		ql::container_memory_to_wstring(s, message);
	}

	std::string ql::aes::decrypted(const std::array<ql::u8, 16>& message, const std::string& key)
	{
		this->check_constructed();
		this->set_state(message);
		this->set_key(key);
		this->expand_key();
		this->decipher();
		return this->get_message();
	}

	std::string ql::aes::decrypted(const ql::u8* message, ql::size size, const std::string& key, bool remove_null_terminations)
	{
		this->check_constructed();
		this->set_key(key);
		this->expand_key();

		std::array<ql::u8, 16> last_block;
		std::array<ql::u8, 16> input_block;
		std::array<ql::u8, 16> output_block;
		bool first_block = true;

		std::string result;
		// result.reserve((((size ? size - 1 : 0) / 16) + 1) * 16);
		result.reserve(size);

		ql::size length = size;
		for (ql::size i = 0u; i < length / this->m_state.size(); ++i)
		{
			for (ql::size c = 0u; c < this->m_state.size(); ++c)
			{
				input_block[c] = message[i * this->m_state.size() + c];
			}
			this->set_state(input_block);
			this->decipher();
			if (first_block)
			{
				for (ql::size c = 0u; c < this->m_state.size(); ++c)
				{
					output_block[c] = this->m_state[c];
				}
				first_block = false;
			}
			else
			{
				for (ql::size c = 0u; c < this->m_state.size(); ++c)
				{
					output_block[c] = last_block[c] ^ this->m_state[c];
				}
			}
			for (ql::size i = 0u; i < this->m_state.size(); ++i)
			{
				result.push_back(output_block[i]);
			}
			std::memcpy(last_block.data(), input_block.data(), last_block.size());
		}
		if (size % this->m_state.size())
		{
			for (ql::size c = 0; c < this->m_state.size(); ++c)
			{
				input_block[c] = c >= size ? 0 : message[(size / this->m_state.size()) * this->m_state.size() + c];
			}

			this->set_state(input_block);
			this->decipher();
			if (first_block)
			{
				for (ql::size c = 0u; c < this->m_state.size(); ++c)
				{
					if (c >= size)
					{
						output_block[c] = ql::u8{};
					}
					else
					{
						output_block[c] = this->m_state[c];
					}
				}
			}
			else
			{
				for (ql::size c = 0u; c < this->m_state.size(); ++c)
				{
					if (c >= size)
					{
						output_block[c] = last_block[c] ^ ql::u8{};
					}
					else
					{
						output_block[c] = last_block[c] ^ this->m_state[c];
					}
				}
			}
			for (ql::size i = 0u; i < this->m_state.size(); ++i)
			{
				result.push_back(output_block[i]);
			}
		}
		if (remove_null_terminations)
		{
			auto last = result.size() - 1;
			while (last && result[last] == ql::u8{})
			{
				--last;
			}
			result.resize(last + 1);
		}
		return result;
	}

	std::string ql::aes::decrypted(const std::string& message, const std::string& key, bool remove_null_terminations)
	{
		return ql::aes::decrypted(reinterpret_cast<const ql::u8*>(message.c_str()), message.length(), key,
															 remove_null_terminations);
	}

	std::wstring ql::aes::decrypted(const std::wstring& message, const std::string& key, bool remove_null_terminations)
	{
		auto s = ql::aes::decrypted(reinterpret_cast<const ql::u8*>(message.c_str()),
																 message.length() * (sizeof(wchar_t) / sizeof(char)), key, remove_null_terminations);
		return std::wstring(std::move(reinterpret_cast<const wchar_t*>(s.data())), s.size() / (sizeof(wchar_t) / sizeof(char)));
	}

	std::string ql::aes::decrypted(const std::vector<char>& message, const std::string& key, bool remove_null_terminations)
	{
		auto s = ql::aes::decrypted(reinterpret_cast<const ql::u8*>(message.data()), message.size(), key, remove_null_terminations);
		return std::string(std::move(reinterpret_cast<const char*>(s.data())), s.size());
	}

	std::wstring ql::aes::decrypted(const std::vector<wchar_t>& message, const std::string& key, bool remove_null_terminations)
	{
		auto s = ql::aes::decrypted(reinterpret_cast<const ql::u8*>(message.data()),
																 message.size() * (sizeof(wchar_t) / sizeof(char)), key, remove_null_terminations);
		return std::wstring(std::move(reinterpret_cast<const wchar_t*>(s.data())), s.size() / (sizeof(wchar_t) / sizeof(char)));
	}

	void ql::aes::decrypt(std::string& message, const std::string& key, bool remove_null_terminations)
	{
		message =
				ql::aes::decrypted(reinterpret_cast<const ql::u8*>(message.c_str()), message.size(), key, remove_null_terminations);
	}

	void ql::aes::decrypt(std::wstring& message, const std::string& key, bool remove_null_terminations)
	{
		auto s = ql::aes::decrypted(reinterpret_cast<const ql::u8*>(message.c_str()),
																 message.size() * (sizeof(wchar_t) / sizeof(char)), key, remove_null_terminations);
		ql::container_memory_to_wstring(s, message);
	}

	void ql::aes::set_mode(mode m)
	{
		this->check_constructed();
		this->m_mode = m;

		if (m == mode::_128)
		{
			this->m_key_size = 16u;
			this->m_cipher_rounds = 10u;
		}
		else if (m == mode::_192)
		{
			this->m_key_size = 24u;
			this->m_cipher_rounds = 12u;
		}
		else if (m == mode::_256)
		{
			this->m_key_size = 32u;
			this->m_cipher_rounds = 14u;
		}
		this->m_round_key_size = this->m_state.size() * (this->m_cipher_rounds + 1);

		this->m_key.resize(this->m_key_size);
		this->m_round_key.resize(this->m_round_key_size);
	}

	ql::size ql::aes::get_cipher_rounds() const
	{
		return this->m_cipher_rounds;
	}

	void ql::aes::set_cipher_rounds(ql::size count)
	{
		this->check_constructed();
		this->m_cipher_rounds = count;
		this->m_round_key_size = this->m_state.size() * (this->m_cipher_rounds + 1);
		this->m_round_key.resize(this->m_round_key_size);
	}

	void ql::aes::copy_message(ql::u8* newState) const
	{
		this->error_if_not_constructed();
		for (ql::u32 i = 0u; i < this->m_state.size(); ++i)
		{
			newState[i] = this->m_state[i];
		}
	}

	std::string ql::aes::get_message() const
	{
		this->error_if_not_constructed();
		std::string result;
		result.reserve(this->m_state.size());
		for (ql::size i = 0u; i < this->m_state.size(); ++i)
		{
			result += this->m_state[i];
		}
		return result;
	}

	bool ql::aes::is_constructed() const
	{
		return this->m_constructed;
	}

	void ql::aes::set_state(const std::array<ql::u8, 16>& state)
	{
		this->m_state = state;
	}

	void ql::aes::set_state(const std::string state)
	{
		ql::size i = 0;
		for (; i < ql::min(state.length(), this->m_state.size()); ++i)
		{
			this->m_state[i] = state[i];
		}
		for (; i < this->m_state.size(); ++i)
		{
			this->m_state[i] = 0u;
		}
	}

	void ql::aes::set_key(const std::vector<ql::u8>& key)
	{
		ql::size i = 0;
		for (; i < ql::min(key.size(), this->m_key_size); ++i)
		{
			this->m_key[i] = key[i];
		}
		for (; i < this->m_key_size; ++i)
		{
			this->m_key[i] = 0u;
		}
	}

	void ql::aes::set_key(const std::string& key)
	{
		ql::size i = 0;
		for (; i < ql::min(key.length(), this->m_key_size); ++i)
		{
			this->m_key[i] = key[i];
		}
		for (; i < this->m_key_size; ++i)
		{
			this->m_key[i] = 0u;
		}
	}

	void ql::aes::expand_key()
	{
		ql::size bytes_generated = 0;
		ql::u8 helperWORD[4];

		for (; bytes_generated < this->m_key_size; ++bytes_generated)
		{
			this->m_round_key[bytes_generated] = this->m_key[bytes_generated];
		}

		for (; bytes_generated < this->m_round_key_size; bytes_generated += 4)
		{
			for (ql::u32 i = 0u; i < 4u; ++i)
			{
				helperWORD[i] = this->m_round_key[(bytes_generated - 4) + i];
			}

			if (bytes_generated % this->m_key_size == 0)
			{
				// function rotWORD()
				ql::u8 temp = helperWORD[0];
				helperWORD[0] = helperWORD[1];
				helperWORD[1] = helperWORD[2];
				helperWORD[2] = helperWORD[3];
				helperWORD[3] = temp;

				for (ql::size i = 0u; i < 4u; ++i)
				{
					helperWORD[i] = ql::detail::aes_tables::sbox[helperWORD[i]];
				}

				helperWORD[0] ^= ql::detail::aes_tables::rcon[bytes_generated / this->m_key_size];
			}

			if (this->m_key_size == 32u && bytes_generated % this->m_key_size == 16)
			{
				for (ql::u32 i = 0u; i < 4u; ++i)
				{
					helperWORD[i] = ql::detail::aes_tables::sbox[helperWORD[i]];
				}
			}

			for (ql::u32 i = 0u; i < 4u; ++i)
			{
				this->m_round_key[bytes_generated + i] = this->m_round_key[(bytes_generated - this->m_key_size) + i] ^ helperWORD[i];
			}
		}
	}

	void ql::aes::cipher()
	{
		this->add_round_key(0);

		for (ql::size round = 1u; round < this->m_cipher_rounds; ++round)
		{
			this->sub_bytes();
			this->shift_rows();
			this->mix_columns();
			this->add_round_key(round);
		}
		this->sub_bytes();
		this->shift_rows();
		this->add_round_key(this->m_cipher_rounds);
	}

	void ql::aes::decipher()
	{
		this->add_round_key(this->m_cipher_rounds);
		for (auto round = ql::i32_cast(this->m_cipher_rounds - 1); round > 0; --round)
		{
			this->unshift_rows();
			this->unsub_bytes();
			this->add_round_key(round);
			this->unmix_columns();
		}

		this->unshift_rows();
		this->unsub_bytes();
		this->add_round_key(0);
	}

	void ql::aes::add_round_key(ql::size rounds)
	{
		for (ql::u32 i = 0u; i < this->m_state.size(); ++i)
		{
			this->m_state[i] ^= this->m_round_key[rounds * this->m_state.size() + i];
		}
	}

	void ql::aes::sub_bytes()
	{
		for (ql::u32 i = 0u; i < this->m_state.size(); ++i)
		{
			this->m_state[i] = ql::detail::aes_tables::sbox[this->m_state[i]];
		}
	}

	void ql::aes::unsub_bytes()
	{
		for (ql::u32 i = 0u; i < this->m_state.size(); ++i)
		{
			this->m_state[i] = ql::detail::aes_tables::sbox_inv[this->m_state[i]];
		}
	}

	void ql::aes::shift_rows()
	{
		std::array<u8, 4u> temp;
		for (ql::u32 row = 1u; row < 4u; ++row)
		{
			for (ql::u32 i = 0u; i < 4u; ++i)
			{
				temp[i] = this->m_state[((i + row) % 4u) * 4u + row];
			}
			for (ql::u32 i = 0u; i < 4u; ++i)
			{
				this->m_state[i * 4u + row] = temp[i];
			}
		}
	}

	void ql::aes::unshift_rows()
	{
		std::array<u8, 4u> temp;
		for (ql::u32 row = 1u; row < 4u; ++row)
		{
			for (ql::u32 i = 0u; i < 4u; ++i)
			{
				temp[i] = this->m_state[((4u + i - row) % 4u) * 4u + row];
			}
			for (ql::u32 i = 0u; i < 4u; ++i)
			{
				this->m_state[i * 4u + row] = temp[i];
			}
		}
	}

	void ql::aes::mix_columns()
	{
		for (ql::u32 columns = 0u; columns < 4u; ++columns)
		{
			auto index0 = columns * 4 + 0;
			auto index1 = columns * 4 + 1;
			auto index2 = columns * 4 + 2;
			auto index3 = columns * 4 + 3;

			std::array<ql::u8, 4u> temp;
			temp[0] = ql::detail::aes_tables::mul2[this->m_state[index0]] ^ ql::detail::aes_tables::mul3[this->m_state[index1]] ^
								ql::detail::aes_tables::mul1[this->m_state[index2]] ^ ql::detail::aes_tables::mul1[this->m_state[index3]];
			temp[1] = ql::detail::aes_tables::mul1[this->m_state[index0]] ^ ql::detail::aes_tables::mul2[this->m_state[index1]] ^
								ql::detail::aes_tables::mul3[this->m_state[index2]] ^ ql::detail::aes_tables::mul1[this->m_state[index3]];
			temp[2] = ql::detail::aes_tables::mul1[this->m_state[index0]] ^ ql::detail::aes_tables::mul1[this->m_state[index1]] ^
								ql::detail::aes_tables::mul2[this->m_state[index2]] ^ ql::detail::aes_tables::mul3[this->m_state[index3]];
			temp[3] = ql::detail::aes_tables::mul3[this->m_state[index0]] ^ ql::detail::aes_tables::mul1[this->m_state[index1]] ^
								ql::detail::aes_tables::mul1[this->m_state[index2]] ^ ql::detail::aes_tables::mul2[this->m_state[index3]];

			for (ql::u32 i = 0; i < 4; ++i)
			{
				this->m_state[columns * 4 + i] = temp[i];
			}
		}
	}

	void ql::aes::unmix_columns()
	{
		for (ql::u32 columns = 0u; columns < 4u; ++columns)
		{
			auto index0 = columns * 4 + 0;
			auto index1 = columns * 4 + 1;
			auto index2 = columns * 4 + 2;
			auto index3 = columns * 4 + 3;

			std::array<ql::u8, 4u> temp;
			temp[0] = ql::detail::aes_tables::mul14[this->m_state[index0]] ^ ql::detail::aes_tables::mul11[this->m_state[index1]] ^
								ql::detail::aes_tables::mul13[this->m_state[index2]] ^ ql::detail::aes_tables::mul9[this->m_state[index3]];
			temp[1] = ql::detail::aes_tables::mul9[this->m_state[index0]] ^ ql::detail::aes_tables::mul14[this->m_state[index1]] ^
								ql::detail::aes_tables::mul11[this->m_state[index2]] ^ ql::detail::aes_tables::mul13[this->m_state[index3]];
			temp[2] = ql::detail::aes_tables::mul13[this->m_state[index0]] ^ ql::detail::aes_tables::mul9[this->m_state[index1]] ^
								ql::detail::aes_tables::mul14[this->m_state[index2]] ^ ql::detail::aes_tables::mul11[this->m_state[index3]];
			temp[3] = ql::detail::aes_tables::mul11[this->m_state[index0]] ^ ql::detail::aes_tables::mul13[this->m_state[index1]] ^
								ql::detail::aes_tables::mul9[this->m_state[index2]] ^ ql::detail::aes_tables::mul14[this->m_state[index3]];

			for (ql::u32 i = 0u; i < 4u; ++i)
			{
				this->m_state[columns * 4u + i] = temp[i];
			}
		}
	}

	ql::aes ql::detail::aes(false);

	std::string ql::aes_256_encrypted(const std::string& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		return ql::detail::aes.encrypted(message, key);
	}

	std::string ql::aes_192_encrypted(const std::string& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		return ql::detail::aes.encrypted(message, key);
	}

	std::string ql::aes_128_encrypted(const std::string& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		return ql::detail::aes.encrypted(message, key);
	}

	std::string ql::aes_256_encrypted(const std::string& message, const std::array<ql::u64, 4>& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		std::string s;
		ql::container_memory_to_string(key, s);
		return ql::detail::aes.encrypted(message, s);
	}

	std::string ql::aes_192_encrypted(const std::string& message, const std::array<ql::u64, 3>& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		std::string s;
		ql::container_memory_to_string(key, s);
		return ql::detail::aes.encrypted(message, s);
	}

	std::string ql::aes_128_encrypted(const std::string& message, const std::array<ql::u64, 2>& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		std::string s;
		ql::container_memory_to_string(key, s);
		return ql::detail::aes.encrypted(message, s);
	}

	std::string ql::aes_256_decrypted(const std::string& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		return ql::detail::aes.decrypted(message, key, remove_null_terminations);
	}

	std::string ql::aes_192_decrypted(const std::string& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		return ql::detail::aes.decrypted(message, key, remove_null_terminations);
	}

	std::string ql::aes_128_decrypted(const std::string& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		return ql::detail::aes.decrypted(message, key, remove_null_terminations);
	}

	std::string
	ql::aes_256_decrypted(const std::string& message, const std::array<ql::u64, 4>& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		std::string s;
		ql::container_memory_to_string(key, s);
		return ql::detail::aes.decrypted(message, s, remove_null_terminations);
	}

	std::string
	ql::aes_192_decrypted(const std::string& message, const std::array<ql::u64, 3>& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		std::string s;
		ql::container_memory_to_string(key, s);
		return ql::detail::aes.decrypted(message, s, remove_null_terminations);
	}

	std::string
	ql::aes_128_decrypted(const std::string& message, const std::array<ql::u64, 2>& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		std::string s;
		ql::container_memory_to_string(key, s);
		return ql::detail::aes.decrypted(message, s, remove_null_terminations);
	}

	void ql::aes_256_encrypt(std::string& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		ql::detail::aes.encrypt(message, key);
	}

	void ql::aes_192_encrypt(std::string& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		ql::detail::aes.encrypt(message, key);
	}

	void ql::aes_128_encrypt(std::string& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		ql::detail::aes.encrypt(message, key);
	}

	void ql::aes_256_encrypt(std::string& message, const std::array<ql::u64, 4>& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		std::string s;
		ql::container_memory_to_string(key, s);
		ql::detail::aes.encrypt(message, s);
	}

	void ql::aes_192_encrypt(std::string& message, const std::array<ql::u64, 3>& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		std::string s;
		ql::container_memory_to_string(key, s);
		ql::detail::aes.encrypt(message, s);
	}

	void ql::aes_128_encrypt(std::string& message, const std::array<ql::u64, 2>& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		std::string s;
		ql::container_memory_to_string(key, s);
		ql::detail::aes.encrypt(message, s);
	}

	void ql::aes_256_decrypt(std::string& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		ql::detail::aes.decrypt(message, key, remove_null_terminations);
	}

	void ql::aes_192_decrypt(std::string& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		ql::detail::aes.decrypt(message, key, remove_null_terminations);
	}

	void ql::aes_128_decrypt(std::string& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		ql::detail::aes.decrypt(message, key, remove_null_terminations);
	}

	void ql::aes_256_decrypt(std::string& message, const std::array<ql::u64, 4>& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		std::string s;
		ql::container_memory_to_string(key, s);
		ql::detail::aes.decrypt(message, s, remove_null_terminations);
	}

	void ql::aes_192_decrypt(std::string& message, const std::array<ql::u64, 3>& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		std::string s;
		ql::container_memory_to_string(key, s);
		ql::detail::aes.decrypt(message, s, remove_null_terminations);
	}

	void ql::aes_128_decrypt(std::string& message, const std::array<ql::u64, 2>& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		std::string s;
		ql::container_memory_to_string(key, s);
		ql::detail::aes.decrypt(message, s, remove_null_terminations);
	}

	std::wstring ql::aes_256_encrypted(const std::wstring& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		return ql::detail::aes.encrypted(message, key);
	}

	std::wstring ql::aes_192_encrypted(const std::wstring& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		return ql::detail::aes.encrypted(message, key);
	}

	std::wstring ql::aes_128_encrypted(const std::wstring& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		return ql::detail::aes.encrypted(message, key);
	}

	std::wstring ql::aes_256_decrypted(const std::wstring& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		return ql::detail::aes.decrypted(message, key, remove_null_terminations);
	}

	std::wstring ql::aes_192_decrypted(const std::wstring& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		return ql::detail::aes.decrypted(message, key, remove_null_terminations);
	}

	std::wstring ql::aes_128_decrypted(const std::wstring& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		return ql::detail::aes.decrypted(message, key, remove_null_terminations);
	}

	void ql::aes_256_encrypt(std::wstring& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		ql::detail::aes.encrypt(message, key);
	}

	void ql::aes_192_encrypt(std::wstring& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		ql::detail::aes.encrypt(message, key);
	}

	void ql::aes_128_encrypt(std::wstring& message, const std::string& key)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		ql::detail::aes.encrypt(message, key);
	}

	void ql::aes_256_decrypt(std::wstring& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_256);
		ql::detail::aes.decrypt(message, key, remove_null_terminations);
	}

	void ql::aes_192_decrypt(std::wstring& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_192);
		ql::detail::aes.decrypt(message, key, remove_null_terminations);
	}

	void ql::aes_128_decrypt(std::wstring& message, const std::string& key, bool remove_null_terminations)
	{
		ql::detail::aes.set_mode(ql::aes::mode::_128);
		ql::detail::aes.decrypt(message, key, remove_null_terminations);
	}

	void make_string_multiple_of_16_bytes(std::string& string)
	{
		auto s = string.size() % 16;
		if (!s)
			return;
		string.append(std::string(16 - s, '\0'));
	}

	std::string ql::encrypt(const std::string& message, const std::string& key)
	{
		return ql::aes_256_encrypted(message, key);
	}

	std::string ql::decrypt(const std::string& message, const std::string& key, bool remove_null_terminations)
	{
		return ql::aes_256_decrypted(message, key, remove_null_terminations);
	}

	void ql::aes_128_encrypt_keep_size(std::string& string, const std::string& key)
	{
		auto n = ((string.length() - 1) / 16);
		auto diff = ql::u8_cast((n + 1) * 16u - string.length());
		ql::aes_128_encrypt(string, key);

		auto size = string.length();
		string.resize(size + 1);
		memcpy(string.data() + size, &diff, 1u);
	}

	std::string ql::aes_128_encrypted_keep_size(std::string string, const std::string& key)
	{
		ql::aes_128_encrypt_keep_size(string, key);
		return string;
	}

	void ql::aes_128_decrypt_keep_size(std::string& string, const std::string& key)
	{
		ql::u8 diff;
		memcpy(&diff, &string.back(), 1u);
		string.pop_back();

		ql::aes_128_decrypt(string, key);
		string.resize(string.length() - diff);
	}

	std::string ql::aes_128_decrypted_keep_size(std::string string, const std::string& key)
	{
		ql::aes_128_decrypt_keep_size(string, key);
		return string;
	}

	void ql::aes_192_encrypt_keep_size(std::string& string, const std::string& key)
	{
		auto n = ((string.length() - 1) / 16);
		auto diff = ql::u8_cast((n + 1) * 16u - string.length());
		ql::aes_192_encrypt(string, key);

		auto size = string.length();
		string.resize(size + 1);
		memcpy(string.data() + size, &diff, 1u);
	}

	std::string ql::aes_192_encrypted_keep_size(std::string string, const std::string& key)
	{
		ql::aes_192_encrypt_keep_size(string, key);
		return string;
	}

	void ql::aes_192_decrypt_keep_size(std::string& string, const std::string& key)
	{
		ql::u8 diff;
		memcpy(&diff, &string.back(), 1u);
		string.pop_back();

		ql::aes_192_decrypt(string, key);
		string.resize(string.length() - diff);
	}

	std::string ql::aes_192_decrypted_keep_size(std::string string, const std::string& key)
	{
		ql::aes_192_decrypt_keep_size(string, key);
		return string;
	}

	void ql::aes_256_encrypt_keep_size(std::string& string, const std::string& key)
	{
		auto n = ((string.length() - 1) / 16);
		auto diff = ql::u8_cast((n + 1) * 16u - string.length());
		ql::aes_256_encrypt(string, key);

		auto size = string.length();
		string.resize(size + 1);
		memcpy(string.data() + size, &diff, 1u);
	}

	std::string ql::aes_256_encrypted_keep_size(std::string string, const std::string& key)
	{
		ql::aes_256_encrypt_keep_size(string, key);
		return string;
	}

	void ql::aes_256_decrypt_keep_size(std::string& string, const std::string& key)
	{
		ql::u8 diff;
		memcpy(&diff, &string.back(), 1u);
		string.pop_back();

		ql::aes_256_decrypt(string, key);
		string.resize(string.length() - diff);
	}

	std::string ql::aes_256_decrypted_keep_size(std::string string, const std::string& key)
	{
		ql::aes_256_decrypt_keep_size(string, key);
		return string;
	}

	void ql::encrypt_keep_size(std::string& string, const std::string& key, ql::aes::mode mode)
	{
		switch (mode)
		{
			case ql::aes::mode::_128: ql::aes_128_encrypt_keep_size(string, key); break;
			case ql::aes::mode::_192: ql::aes_192_encrypt_keep_size(string, key); break;
			case ql::aes::mode::_256: ql::aes_256_encrypt_keep_size(string, key); break;
		}
	}

	std::string ql::encrypted_keep_size(std::string string, const std::string& key, ql::aes::mode mode)
	{
		switch (mode)
		{
			case ql::aes::mode::_128: return ql::aes_128_encrypted_keep_size(string, key); break;
			case ql::aes::mode::_192: return ql::aes_192_encrypted_keep_size(string, key); break;
			case ql::aes::mode::_256: return ql::aes_256_encrypted_keep_size(string, key); break;
		}
		return "";
	}

	void ql::decrypt_keep_size(std::string& string, const std::string& key, ql::aes::mode mode)
	{
		switch (mode)
		{
			case ql::aes::mode::_128: ql::aes_128_decrypt_keep_size(string, key); break;
			case ql::aes::mode::_192: ql::aes_192_decrypt_keep_size(string, key); break;
			case ql::aes::mode::_256: ql::aes_256_decrypt_keep_size(string, key); break;
		}
	}

	std::string ql::decrypted_keep_size(std::string string, const std::string& key, ql::aes::mode mode)
	{
		switch (mode)
		{
			case ql::aes::mode::_128: return ql::aes_128_decrypted_keep_size(string, key); break;
			case ql::aes::mode::_192: return ql::aes_192_decrypted_keep_size(string, key); break;
			case ql::aes::mode::_256: return ql::aes_256_decrypted_keep_size(string, key); break;
		}
		return "";
	}

#ifdef QL_CIPHER
	ql::cipher_ultra_fast ql::cipher::ultra_fast;
	ql::cipher_fast ql::cipher::fast;
	ql::cipher_mid ql::cipher::mid;
	ql::cipher_secure ql::cipher::secure;
	ql::cipher_very_secure ql::cipher::very_secure;

	std::string ql::encrypt_ultra_fast(const std::string& message, const std::string& key)
	{
		return ql::cipher::ultra_fast.encrypted(message, key);
	}

	std::string ql::decrypt_ultra_fast(const std::string& message, const std::string& key)
	{
		return ql::cipher::ultra_fast.decrypted(message, key);
	}

	std::string ql::encrypt_fast(const std::string& message, const std::string& key)
	{
		return ql::cipher::fast.encrypted(message, key);
	}

	std::string ql::decrypt_fast(const std::string& message, const std::string& key)
	{
		return ql::cipher::fast.decrypted(message, key);
	}

	std::string ql::encrypt_mid(const std::string& message, const std::string& key)
	{
		return ql::cipher::mid.encrypted(message, key);
	}

	std::string ql::decrypt_mid(const std::string& message, const std::string& key)
	{
		return ql::cipher::mid.decrypted(message, key);
	}

	std::string ql::encrypt_secure(const std::string& message, const std::string& key)
	{
		return ql::cipher::secure.encrypted(message, key);
	}

	std::string ql::decrypt_secure(const std::string& message, const std::string& key)
	{
		return ql::cipher::secure.decrypted(message, key);
	}

	std::string ql::encrypt_very_secure(const std::string& message, const std::string& key)
	{
		return ql::cipher::very_secure.encrypted(message, key);
	}

	std::string ql::decrypt_very_secure(const std::string& message, const std::string& key)
	{
		return ql::cipher::very_secure.decrypted(message, key);
	}

#endif

#ifdef QL_RSA
	bool ql::RSA_key_pair::empty() const
	{
		return this->mod == 0 || this->key == 0;
	}

	void ql::RSA_key_pair::set(const std::string_view& mod, const std::string_view& key)
	{
		this->mod.set_str(mod.data(), 16);
		this->key.set_str(key.data(), 16);
	}

	void ql::RSA_key_pair::set_base64(const std::string_view& mod, const std::string_view& key)
	{
		auto hex_mod = ql::base64_to_hex_string(mod);
		auto hex_key = ql::base64_to_hex_string(key);

		this->mod.set_str(hex_mod, 16);
		this->key.set_str(hex_key, 16);
	}

	std::string ql::RSA_key_pair::string()
	{
		return ql::to_string("\"", this->mod.get_str(16), "\",\n\"", this->key.get_str(16), "\"");
	}

	ql::size ql::RSA_key_pair::bits() const
	{
		return this->mod.get_str(2u).length();
	}

	void ql::RSA::set_decryption_key(const mpz_class& key, const mpz_class& mod)
	{
		this->private_key = key;
		this->mod = mod;

		this->bits = this->mod.get_str(2).length();
	}

	void ql::RSA::set_encryption_key(const mpz_class& key, const mpz_class& mod)
	{
		this->public_key = key;
		this->mod = mod;

		this->bits = this->mod.get_str(2).length();
	}

	void ql::RSA::set_decryption_key(const RSA_key_pair& key)
	{
		this->set_decryption_key(key.key, key.mod);
	}

	void ql::RSA::set_encryption_key(const RSA_key_pair& key)
	{
		this->set_encryption_key(key.key, key.mod);
	}

	ql::RSA_key_pair ql::RSA::get_public_key() const
	{
		RSA_key_pair result;
		result.mod = this->mod;
		result.key = this->public_key;
		return result;
	}

	ql::RSA_key_pair ql::RSA::get_private_key() const
	{
		RSA_key_pair result;
		result.mod = this->mod;
		result.key = this->private_key;
		return result;
	}

	ql::size ql::RSA::get_bits() const
	{
		return this->bits;
	}

	bool ql::RSA::check(const std::string& prime1, const std::string& prime2)
	{
		mpz_class p1;
		p1.set_str(prime1, 16);
		mpz_class p2;
		p2.set_str(prime2, 16);
		return this->check(p1, p2);
	}

	void ql::RSA::create(const std::string& prime1, const std::string& prime2)
	{
		mpz_class p1;
		p1.set_str(prime1, 16);
		mpz_class p2;
		p2.set_str(prime2, 16);
		this->create(p1, p2);
	}

	void ql::RSA::create(mpz_class prime1, mpz_class prime2, mpz_class lambda)
	{
		if (lambda == 0)
		{
			auto p1 = mpz_class{prime1 - 1};
			auto p2 = mpz_class{prime2 - 1};
			lambda = mpz_class{lcm(p1, p2)};
		}

		this->mod = mpz_class{prime1 * prime2};
		this->bits = this->mod.get_str(2).length();

		mpz_class e = (1 << 15) + 1u;
		for (; e < lambda; ++e)
		{
			if (gcd(e, lambda) == 1)
			{
				this->private_key = ql::mod_inverse(e, lambda);
				if (this->private_key != e)
				{
					this->public_key = e;
					break;
				}
			}
		}
	}

	bool ql::RSA::check(mpz_class prime1, mpz_class prime2)
	{
		auto p1 = mpz_class{prime1 - 1};
		auto p2 = mpz_class{prime2 - 1};
		auto lambda = mpz_class{lcm(p1, p2)};

		if (lambda == p1 || lambda == p2)
		{
			return false;
		}
		if (prime1 == prime2)
		{
			return false;
		}
		auto mod = mpz_class{prime1 * prime2};
		if (mod.get_str(2u).length() % 8u)
		{
			return false;
		}

		this->create(prime1, prime2, lambda);
		return true;
	}

	mpz_class ql::RSA::encrypt_integer(mpz_class message) const
	{
		mpz_class result;
		mpz_powm(result.get_mpz_t(), message.get_mpz_t(), this->public_key.get_mpz_t(), this->mod.get_mpz_t());
		return result;
	}

	mpz_class ql::RSA::decrypt_integer(mpz_class message) const
	{
		mpz_class result;
		mpz_powm(result.get_mpz_t(), message.get_mpz_t(), this->private_key.get_mpz_t(), this->mod.get_mpz_t());
		return result;
	}

	void ql::RSA::pad_string(std::string& string) const
	{
		auto diff = ql::signed_cast(this->get_bits() / 4) - ql::signed_cast(string.length());
		if (diff > 0)
		{
			string = ql::to_string(ql::to_string_repeat("0", diff), string);
		}
	}

	std::string ql::RSA::encrypt_single_hex(const std::string& message) const
	{
		mpz_class n;
		n.set_str(message, 16);
		auto str = this->encrypt_integer(n).get_str(16);
		this->pad_string(str);
		return str;
	}

	std::string ql::RSA::decrypt_single_hex(const std::string& message) const
	{
		mpz_class n;
		n.set_str(message, 16);
		auto str = this->decrypt_integer(n).get_str(16);
		this->pad_string(str);
		return str;
	}

	ql::size ql::RSA::get_max_message_length(ql::hash_type hash_object) const
	{
		auto hash_size = hash_object.second / 8u;
		auto k = this->get_bits() / 8;
		auto message_length = (k - hash_size * 2 - 2u);
		return message_length;
	}

	std::optional<std::string>
	ql::RSA::encrypt_hex_OAEP(const std::string_view& message, std::string label, ql::hash_type hash_object) const
	{
		auto hash_size = hash_object.second / 8u;
		auto k = this->get_bits() / 4;
		auto lhash = hash_object.first(label);

		auto ps_length = ql::signed_cast(k) - 2 * ql::signed_cast(message.length()) - 4 * ql::signed_cast(hash_size) - 3;

		if (ps_length < 0)
		{
			return std::nullopt;
		}
		std::string ps;
		ps.resize(ps_length, '0');

		auto seed = ql::get_random_string_full_range(hash_size);

		std::string db;
		db.append(lhash);
		db.append(ps);
		db.append("1");
		db.append(ql::hex_string(message));

		auto db_mask_size = k - 2 * hash_size - 1;
		auto db_mask = ql::mgf1(seed, db_mask_size, hash_object);
		auto masked_db = ql::hex_string_xor(db, db_mask);
		auto seed_mask = ql::mgf1(ql::from_hex_string(masked_db), hash_size * 2, hash_object);
		auto masked_seed = ql::hex_string_xor(seed_mask, ql::hex_string(seed));

		std::string em;
		em.append("0");
		em.append(masked_seed);
		em.append(masked_db);
		return this->encrypt_single_hex(em);
	}

	std::optional<std::string>
	ql::RSA::decrypt_hex_OAEP(const std::string_view& message, std::string label, ql::hash_type hash_object) const
	{
		auto em = this->decrypt_single_hex(std::string{message});
		auto hash_size = hash_object.second / 8u;
		auto k = this->get_bits() / 4;
		auto lhash = hash_object.first(label);
		auto db_mask_size = k - 2 * hash_size - 1;
		auto masked_seed = em.substr(2u, hash_size * 2);
		auto masked_db = em.substr(hash_size * 2 + 2u);
		auto seed_mask = ql::mgf1(ql::from_hex_string(masked_db), hash_size * 2, hash_object);
		auto seed = ql::from_hex_string(ql::hex_string_xor(seed_mask, masked_seed));
		auto db_mask = ql::mgf1(seed, db_mask_size, hash_object);
		auto db = ql::hex_string_xor(db_mask, masked_db);
		auto check_lhash = db.substr(0u, lhash.length());

		if (check_lhash != lhash)
		{
			return std::nullopt;
		}
		ql::size ps_index = lhash.length();
		while (db[ps_index] == '0')
		{
			++ps_index;
		}
		if (db[ps_index] != '1')
		{
			return std::nullopt;
		}

		return ql::from_hex_string(db.substr(ps_index + 1u));
	}

	std::optional<std::string>
	ql::RSA::encrypt(const std::string_view& message, std::string label, ql::hash_type hash_object) const
	{
		auto message_length = this->get_max_message_length(hash_object);
		auto message_blocks = ql::signed_cast(message.length() - 1) / ql::signed_cast(message_length) + 1;

		std::string result;
		result.reserve(message_blocks * message_length);

		for (ql::isize i = 0; i < message_blocks; ++i)
		{
			auto sub = message.substr(i * message_length, message_length);
			auto e = this->encrypt_hex_OAEP(sub, label, hash_object);
			if (!e.has_value())
			{
				return std::nullopt;
			}
			result.append(e.value());
		}
		return result;
	}

	std::optional<std::string>
	ql::RSA::decrypt(const std::string_view& message, std::string label, ql::hash_type hash_object) const
	{
		auto block_length = this->get_bits() / 4;
		auto blocks = (message.length()) / block_length;

		if (message.length() % block_length)
		{
			return std::nullopt;
		}

		std::string result;
		result.reserve((block_length / 2) * blocks);

		for (ql::size i = 0u; i < blocks; ++i)
		{
			auto sub = message.substr(i * block_length, block_length);
			auto d = this->decrypt_hex_OAEP(sub, label, hash_object);

			if (!d.has_value())
			{
				return std::nullopt;
			}
			result.append(d.value());
		}
		return result;
	}

	std::string
	ql::RSA::sign_RSASSA_PSS(const std::string_view& signature, ql::hash_type hash_object, ql::size salt_length) const
	{
		if (salt_length == ql::size_max)
		{
			salt_length = hash_object.second / 8u;
		}

		auto hash = hash_object.first(signature);
		auto hash_size = hash_object.second / 4u;
		auto k = this->get_bits() / 4;
		auto m_size = 16 + hash_size + salt_length * 2;
		auto db_size = k - m_size - 1;
		auto ps_size = db_size - salt_length * 2 - 1;

		auto salt = ql::get_random_string_full_range(salt_length);

		std::string padding;
		padding.resize(16, '0');

		std::string m;
		m.append(padding);
		m.append(hash);
		m.append(ql::hex_string(salt));

		std::string ps;
		ps.resize(ps_size, '0');

		std::string db;
		db.append(ps);
		db.append("1");
		db.append(ql::hex_string(salt));

		auto mhash = ql::mgf1(hash_object.first(m), m_size, hash_object);
		auto db_mask = ql::mgf1(mhash, db_size, hash_object);
		auto masked_db = ql::hex_string_xor(db, db_mask);

		std::string em;
		em.append("0");
		em.append(masked_db);
		em.append(mhash);

		return this->encrypt_single_hex(em);
	}

	bool ql::RSA::verify_RSASSA_PSS(const std::string& message,
																	 const std::string_view& signature,
																	 ql::hash_type hash_object,
																	 ql::size salt_length) const
	{
		if (salt_length == ql::size_max)
		{
			salt_length = hash_object.second / 8u;
		}
		auto hash_size = hash_object.second / 4u;
		auto k = this->get_bits() / 4;
		auto m_size = 16 + hash_size + salt_length * 2;
		auto db_size = k - m_size - 1;
		auto ps_size = db_size - salt_length * 2 - 1;

		auto hash = hash_object.first(signature);
		auto em = this->decrypt_single_hex(message);

		auto masked_db = em.substr(1u, db_size);
		auto mhash = em.substr(1u + db_size);
		auto db_mask = ql::mgf1(mhash, db_size, hash_object);
		auto db = ql::hex_string_xor(db_mask, masked_db);

		ql::size db_index = 0u;
		while (db[db_index] == '0')
		{
			++db_index;
		}
		if (db[db_index] != '1')
		{
			return false;
		}
		auto salt = db.substr(db_index + 1u);

		std::string padding;
		padding.resize(16, '0');

		std::string m;
		m.append(padding);
		m.append(hash);
		m.append(salt);

		auto check_mhash = ql::mgf1(hash_object.first(m), m_size, hash_object);
		return check_mhash == mhash;
	}

	std::optional<std::string>
	ql::RSA_encrypt(const std::string_view& message, const RSA_key_pair& private_key, std::string label, ql::hash_type hash_object)
	{
		ql::RSA rsa;
		rsa.set_encryption_key(private_key);
		return rsa.encrypt(message, label, hash_object);
	}

	std::optional<std::string>
	ql::RSA_decrypt(const std::string_view& message, const RSA_key_pair& public_key, std::string label, ql::hash_type hash_object)
	{
		ql::RSA rsa;
		rsa.set_decryption_key(public_key);
		return rsa.decrypt(message, label, hash_object);
	}

	std::string ql::RSASSA_PSS_sign(const std::string_view& signature, const RSA_key_pair& private_key, ql::hash_type hash_object)
	{
		ql::RSA rsa;
		rsa.set_encryption_key(private_key);
		return rsa.sign_RSASSA_PSS(signature, hash_object);
	}

	bool ql::RSASSA_PSS_verify(const std::string& message,
															const std::string_view& signature,
															const RSA_key_pair& public_key,
															ql::hash_type hash_object)
	{
		ql::RSA rsa;
		rsa.set_decryption_key(public_key);
		return rsa.verify_RSASSA_PSS(message, signature, hash_object);
	}

	bool ql::RSASSA_PSS_OAEP::empty() const
	{
		return this->cipher_key.empty() || this->signature_key.empty();
	}

	void ql::RSASSA_PSS_OAEP::load_keys(const std::string& data)
	{
		auto lines = ql::string_split(data, '\n');
		if (lines.size() != 5u)
		{
			ql::println("ql::RSASSA_PSS_OAEP::load_keys : invalid keys file");
			return;
		}
		for (auto& i : lines)
		{
			if (i.back() == '\r')
			{
				i.pop_back();
			}
		}
		this->set_cipher_key(lines[0], lines[1]);
		this->set_signature_key(lines[3], lines[4]);
	}

	void ql::RSASSA_PSS_OAEP::load_keys_from_file(const std::string& path)
	{
		this->load_keys(ql::filesys::read_file(path));
	}

	void RSASSA_PSS_OAEP::set_signature_key(const std::string_view& mod, const std::string_view& key)
	{
		this->signature_key.set(mod, key);
	}

	void ql::RSASSA_PSS_OAEP::set_cipher_key(const std::string_view& mod, const std::string_view& key)
	{
		this->cipher_key.set(mod, key);
	}

	std::optional<std::string> ql::RSASSA_PSS_OAEP::add_signature_and_encrypt(const std::string_view& message,
																																						 const std::string_view& signature,
																																						 std::string label,
																																						 ql::hash_type hash_object) const
	{
		if (this->empty())
		{
			return std::nullopt;
		}
		std::string result;
		auto signature_string = ql::RSASSA_PSS_sign(signature, this->signature_key, hash_object);
		auto encrypted_string = ql::RSA_encrypt(message, this->cipher_key, label, hash_object);
		if (!encrypted_string.has_value())
		{
			return std::nullopt;
		}
		result.append(ql::from_hex_string(signature_string));
		result.append(ql::from_hex_string(encrypted_string.value()));
		return result;
	}

	std::optional<std::string> ql::RSASSA_PSS_OAEP::verify_and_decrypt(const std::string& message,
																																			const std::string_view& signature,
																																			std::string label,
																																			ql::hash_type hash_object) const
	{
		if (this->empty())
		{
			return std::nullopt;
		}
		auto signature_offset = this->signature_key.bits() / 8u;
		auto verify_string = message.substr(0u, signature_offset);
		auto verified = ql::RSASSA_PSS_verify(ql::hex_string(verify_string), signature, this->signature_key, hash_object);

		if (!verified)
		{
			return std::nullopt;
		}
		auto decrypted_string =
				ql::RSA_decrypt(ql::hex_string(message.substr(signature_offset)), this->cipher_key, label, hash_object);
		if (!decrypted_string.has_value())
		{
			return std::nullopt;
		}
		return decrypted_string.value();
	}
#endif
}	 // namespace ql