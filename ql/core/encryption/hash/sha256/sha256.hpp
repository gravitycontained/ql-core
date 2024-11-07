#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{
	struct sha256
	{
		using utype = ql::u32;

		constexpr static ql::size bits = 32u;
		constexpr static ql::size message_size = 512u;
		constexpr static ql::size sequence_size = (message_size / bits);
		constexpr static ql::size hash_size = 8u;
		constexpr static ql::size working_size = 8u;
		constexpr static ql::size round_size = 64u;
		constexpr static ql::size output_size = 8u;
		constexpr static ql::size state_size = 8u;
		constexpr static ql::size block_size = 64u;
		constexpr static ql::size digest_bits = bits * ql::bits_in_byte();

		std::array<utype, block_size> data{};
		std::array<utype, state_size> state;
		utype blocklen;
		ql::size bitlen;

		using hash_result = std::array<ql::u8, bits>;

		static constexpr auto table = std::array{
				0x428a2f98u, 0x71374491u, 0xb5c0fbcfu, 0xe9b5dba5u, 0x3956c25bu, 0x59f111f1u, 0x923f82a4u, 0xab1c5ed5u,
				0xd807aa98u, 0x12835b01u, 0x243185beu, 0x550c7dc3u, 0x72be5d74u, 0x80deb1feu, 0x9bdc06a7u, 0xc19bf174u,
				0xe49b69c1u, 0xefbe4786u, 0x0fc19dc6u, 0x240ca1ccu, 0x2de92c6fu, 0x4a7484aau, 0x5cb0a9dcu, 0x76f988dau,
				0x983e5152u, 0xa831c66du, 0xb00327c8u, 0xbf597fc7u, 0xc6e00bf3u, 0xd5a79147u, 0x06ca6351u, 0x14292967u,
				0x27b70a85u, 0x2e1b2138u, 0x4d2c6dfcu, 0x53380d13u, 0x650a7354u, 0x766a0abbu, 0x81c2c92eu, 0x92722c85u,
				0xa2bfe8a1u, 0xa81a664bu, 0xc24b8b70u, 0xc76c51a3u, 0xd192e819u, 0xd6990624u, 0xf40e3585u, 0x106aa070u,
				0x19a4c116u, 0x1e376c08u, 0x2748774cu, 0x34b0bcb5u, 0x391c0cb3u, 0x4ed8aa4au, 0x5b9cca4fu, 0x682e6ff3u,
				0x748f82eeu, 0x78a5636fu, 0x84c87814u, 0x8cc70208u, 0x90befffau, 0xa4506cebu, 0xbef9a3f7u, 0xc67178f2u,
		};

		sha256()
		{
			this->reset();
		}

		static constexpr auto rotr(utype x, utype n)
		{
			return (x >> n) | (x << (bits - n));
		}

		static constexpr auto choose(utype e, utype f, utype g)
		{
			return (e & f) ^ (~e & g);
		}

		static constexpr auto majority(utype a, utype b, utype c)
		{
			return (a & (b | c)) | (b & c);
		}

		static constexpr auto sig0(utype x)
		{
			return rotr(x, 7u) ^ rotr(x, 18u) ^ (x >> 3u);
		}

		static constexpr auto sig1(utype x)
		{
			return rotr(x, 17u) ^ rotr(x, 19u) ^ (x >> 10u);
		}

		QL_SOURCE void reset();
		QL_SOURCE void update(const std::string_view& data);
		QL_SOURCE ql::sha256::hash_result digest();
		QL_SOURCE void transform();
		QL_SOURCE void add_padding();
		QL_SOURCE void revert(ql::sha256::hash_result& hash);
		QL_SOURCE static std::string to_string(const ql::sha256::hash_result& hash);
	};

	namespace detail
	{
		QL_SOURCE extern ql::sha256 sha256_t;
	}	 // namespace detail

	QL_SOURCE std::string sha256_hash(const std::string_view& string);

	constexpr auto sha256_object = std::make_pair(sha256_hash, 256u);
}	 // namespace ql