#pragma once

#include <ql/definition/definition.hpp>

#include <vector>

namespace ql
{
	template <typename T>
	bool is_prime(T value)
	{
		if (value <= 7u)
		{
			return value == 2u || value == 3u || value == 5u || value == 7u;
		}
		if (value % 2u == 0u || value % 3u == 0u)
		{
			return false;
		}

		ql::u32 add = 4u;
		auto sqrt = std::sqrt(value);
		for (ql::u32 i = 5u; i <= sqrt; i += add)
		{
			if (value % i == 0)
			{
				return false;
			}

			add = 6u - add;
		}
		return true;
	}

	template <typename T>
	std::vector<T> prime_factors(T value)
	{
		if (ql::is_prime(value))
		{
			return {value};
		}
		std::vector<T> result;

		for (T i = 2; value > T{1}; ++i)
		{
			if (ql::is_prime(i))
			{
				while (value % i == T{})
				{
					result.push_back(i);
					value /= i;
				}
			}
		}
		return result;
	}

	template <typename T, ql::size N>
	std::array<T, N> generate_primes()
	{
		if (N == 1u)
		{
			return {T{2u}};
		}
		else if (N == 2u)
		{
			return {T{2u}, T{3u}};
		}

		std::array<T, N> primes;
		primes[0u] = 2u;
		primes[1u] = 3u;
		primes[2u] = 5u;

		ql::size ctr = 3u;
		ql::size add = 4u;
		for (ql::size n = 5u; ctr < N; n += add)
		{
			bool is_prime = true;
			for (ql::size p = 0u; p < ctr; ++p)
			{
				if (n % primes[p] == 0)
				{
					is_prime = false;
					break;
				}
			}
			if (is_prime)
			{
				primes[ctr] = ql::type_cast<T>(n);
				++ctr;
			}
			add = 6u - add;
		}
		return primes;
	}

	template <typename T>
	std::vector<T> generate_primes(ql::size size)
	{
		if (size == 1u)
		{
			return {2u};
		}
		else if (size == 2u)
		{
			return {2u, 3u};
		}

		std::vector<T> primes(size);
		primes[0u] = 2u;
		primes[1u] = 3u;
		primes[2u] = 5u;

		ql::size ctr = 3u;
		ql::u32 add = 4u;
		for (ql::size n = 5u; ctr < size; n += add)
		{
			bool is_prime = true;
			for (ql::size p = 0u; p < ctr; ++p)
			{
				if (n % primes[p] == 0)
				{
					is_prime = false;
					break;
				}
			}
			if (is_prime)
			{
				primes[ctr] = ql::type_cast<T>(n);
				++ctr;
			}
			add = 6u - add;
		}
		return primes;
	}
}	 // namespace ql