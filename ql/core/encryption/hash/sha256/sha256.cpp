#include <ql/core/encryption/hash/sha256/sha256.hpp>

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

	ql::sha256::hash_result ql::sha256::digest()
	{
		ql::sha256::hash_result hash;

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

	ql::sha256 ql::detail::sha256_t;

	std::string sha256_hash(const std::string_view& string)
	{
		ql::detail::sha256_t.reset();
		ql::detail::sha256_t.update(string);
		auto digest = ql::detail::sha256_t.digest();
		return ql::sha256::to_string(digest);
	}
}