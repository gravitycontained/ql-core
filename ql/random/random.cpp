#include <ql/random/random.hpp>
#include <ql/transform/memory/memory.hpp>

namespace ql
{
	ql::detail::rng_t ql::detail::rng;

	void set_random_range_i(ql::i64 max)
	{
		ql::detail::rng.idist.set_range(max);
	}

	void set_random_range_i(ql::i64 min, ql::i64 max)
	{
		ql::detail::rng.idist.set_range(min, max);
	}

	void set_random_range_u(ql::u64 max)
	{
		ql::detail::rng.udist.set_range(max);
	}

	void set_random_range_u(ql::u64 min, ql::u64 max)
	{
		ql::detail::rng.udist.set_range(min, max);
	}

	void set_random_range_f(ql::f64 max)
	{
		ql::detail::rng.fdist.set_range(max);
	}

	void set_random_range_f(ql::f64 min, ql::f64 max)
	{
		ql::detail::rng.fdist.set_range(min, max);
	}

	void set_random_seed(ql::u64 seed)
	{
		ql::detail::rng.engine.seed(seed);
	}

	bool random_b()
	{
		return ql::detail::rng.engine.generate() & 0x1ull;
	}

	bool random_b(ql::f64 probability)
	{
		return ql::random_f(1.0) <= probability;
	}

	ql::i64 random_i()
	{
		return ql::detail::rng.engine.generate(ql::detail::rng.idist);
	}

	ql::u64 random_u()
	{
		return ql::detail::rng.engine.generate(ql::detail::rng.udist);
	}

	ql::f64 random_f()
	{
		return ql::reinterpret_memory<ql::f64>(ql::detail::rng.engine.generate());
	}

	ql::u64 random_current()
	{
		return ql::detail::rng.engine.get_current();
	}

	ql::i64 random_i(ql::i64 min, ql::i64 max)
	{
		return ql::detail::rng.engine.generate(min, max);
	}

	ql::u64 random_u(ql::u64 min, ql::u64 max)
	{
		return ql::detail::rng.engine.generate(min, max);
	}

	ql::f64 random_f(ql::f64 min, ql::f64 max)
	{
		return ql::detail::rng.engine.generate(min, max);
	}

	ql::i64 random_i(ql::i64 max)
	{
		return ql::detail::rng.engine.generate(max);
	}

	ql::u64 random_u(ql::u64 max)
	{
		return ql::detail::rng.engine.generate(max);
	}

	ql::f64 random_f(ql::f64 max)
	{
		return ql::detail::rng.engine.generate(max);
	}

	ql::u64 random()
	{
		return ql::detail::rng.engine.generate();
	}

	ql::f64 random_falling(ql::f64 n)
	{
		return (1.0 / ql::random(0.0, 1.0 / n)) - n;
	}
}	 // namespace ql
