#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/type/type.hpp>

namespace ql
{

	struct sha512
	{
		using utype = ql::u64;

		constexpr static ql::size bits = 64u;
		constexpr static ql::size message_size = 1024u;
		constexpr static ql::size sequence_size = (message_size / bits);
		constexpr static ql::size hash_size = 8u;
		constexpr static ql::size working_size = 8u;
		constexpr static ql::size round_size = 80u;
		constexpr static ql::size output_size = 8u;
		constexpr static ql::size state_size = 8u;
		constexpr static ql::size block_size = 128u;
		constexpr static ql::size digest_bits = bits * ql::bits_in_byte();

		std::array<utype, block_size> data{};
		std::array<utype, state_size> state;
		utype blocklen;
		ql::size bitlen;

		using hash_result = std::array<ql::u8, bits>;

		static constexpr auto table = std::array{
				0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL, 0x3956c25bf348b538ULL,
				0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
				0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL, 0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL,
				0xc19bf174cf692694ULL, 0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
				0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL, 0x983e5152ee66dfabULL,
				0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL, 0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
				0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL,
				0x53380d139d95b3dfULL, 0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
				0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 0xd192e819d6ef5218ULL,
				0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL, 0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
				0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL, 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL,
				0x682e6ff3d6b2b8a3ULL, 0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
				0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL, 0xca273eceea26619cULL,
				0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL, 0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
				0x113f9804bef90daeULL, 0x1b710b35131c471bULL, 0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL,
				0x431d67c49c100d4cULL, 0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL,
		};

		sha512()
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
			return rotr(x, 1u) ^ rotr(x, 8u) ^ (x >> 7u);
		}

		static constexpr auto sig1(utype x)
		{
			return rotr(x, 19u) ^ rotr(x, 61u) ^ (x >> 6u);
		}

		QL_SOURCE void reset();
		QL_SOURCE void update(const std::string_view& data);
		QL_SOURCE ql::sha512::hash_result digest();
		QL_SOURCE void transform();
		QL_SOURCE void add_padding();
		QL_SOURCE void revert(ql::sha512::hash_result& hash);
		QL_SOURCE static std::string to_string(const ql::sha512::hash_result& hash);
	};

	namespace detail
	{
		QL_SOURCE extern ql::sha512 sha512_t;
	}	 // namespace detail

	QL_SOURCE std::string sha512_hash(const std::string_view& string);

	constexpr auto sha512_object = std::make_pair(sha512_hash, 512u);
}