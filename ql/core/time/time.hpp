#pragma once
#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/iterative/ema.hpp>
#include <ql/core/type/type.hpp>
#include <ql/core/transform/transform.hpp>

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <set>
#include <functional>

#if defined QL_GRAPHIC
namespace ql
{
	struct event_manager;
}
#endif

namespace ql
{
	struct time
	{
		ql::u64 ns;

		constexpr time(ql::u64 ns = ql::u64{}) noexcept : ns(ns)
		{
		}

		time& operator=(const ql::time& other) = default;

		QL_SOURCE time& operator+=(const ql::time& other);
		QL_SOURCE time operator+(const ql::time& other) const;

		QL_SOURCE time& operator-=(const ql::time& other);
		QL_SOURCE time operator-(const ql::time& other) const;

		QL_SOURCE time& operator/=(const ql::time& other);
		QL_SOURCE time operator/(const ql::time& other) const;

		QL_SOURCE time& operator%=(const ql::time& other);
		QL_SOURCE time operator%(const ql::time& other) const;

		QL_SOURCE bool operator==(const ql::time& other) const;
		QL_SOURCE bool operator!=(const ql::time& other) const;
		QL_SOURCE bool operator<(const ql::time& other) const;
		QL_SOURCE bool operator<=(const ql::time& other) const;
		QL_SOURCE bool operator>(const ql::time& other) const;
		QL_SOURCE bool operator>=(const ql::time& other) const;

		QL_SOURCE std::string single_short_nsecs_string() const;
		QL_SOURCE std::string single_short_usecs_string() const;
		QL_SOURCE std::string single_short_msecs_string() const;
		QL_SOURCE std::string single_short_secs_string() const;
		QL_SOURCE std::string single_short_mins_string() const;
		QL_SOURCE std::string single_short_hours_string() const;
		QL_SOURCE std::string single_short_days_string() const;
		QL_SOURCE std::string single_short_days_week_string() const;
		QL_SOURCE std::string single_short_weeks_string() const;
		QL_SOURCE std::string single_short_years_string() const;

		QL_SOURCE std::string single_descriptive_nsecs_string() const;
		QL_SOURCE std::string single_descriptive_usecs_string() const;
		QL_SOURCE std::string single_descriptive_msecs_string() const;
		QL_SOURCE std::string single_descriptive_secs_string() const;
		QL_SOURCE std::string single_descriptive_mins_string() const;
		QL_SOURCE std::string single_descriptive_hours_string() const;
		QL_SOURCE std::string single_descriptive_days_string() const;
		QL_SOURCE std::string single_descriptive_days_week_string() const;
		QL_SOURCE std::string single_descriptive_weeks_string() const;
		QL_SOURCE std::string single_descriptive_years_string() const;

		QL_SOURCE std::string nsecs_string(bool short_string = true) const;
		QL_SOURCE std::string usecs_string(bool short_string = true) const;
		QL_SOURCE std::string msecs_string(bool short_string = true) const;
		QL_SOURCE std::string secs_string(bool short_string = true) const;
		QL_SOURCE std::string mins_string(bool short_string = true) const;
		QL_SOURCE std::string hours_string(bool short_string = true) const;
		QL_SOURCE std::string days_string(bool short_string = true) const;
		QL_SOURCE std::string days_week_string(bool short_string = true) const;
		QL_SOURCE std::string weeks_string(bool short_string = true) const;
		QL_SOURCE std::string years_string(bool short_string = true) const;

		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_nsecs_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_usecs_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_msecs_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_secs_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_mins_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_hours_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_days_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_days_week_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_weeks_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_short_pair_years_string() const;

		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_nsecs_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_usecs_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_msecs_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_secs_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_mins_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_hours_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_days_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_days_week_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_weeks_string() const;
		QL_SOURCE std::pair<ql::size, std::string> single_descriptive_pair_years_string() const;

		QL_SOURCE std::pair<ql::size, std::string> pair_nsecs_string(bool short_string = true) const;
		QL_SOURCE std::pair<ql::size, std::string> pair_usecs_string(bool short_string = true) const;
		QL_SOURCE std::pair<ql::size, std::string> pair_msecs_string(bool short_string = true) const;
		QL_SOURCE std::pair<ql::size, std::string> pair_secs_string(bool short_string = true) const;
		QL_SOURCE std::pair<ql::size, std::string> pair_mins_string(bool short_string = true) const;
		QL_SOURCE std::pair<ql::size, std::string> pair_hours_string(bool short_string = true) const;
		QL_SOURCE std::pair<ql::size, std::string> pair_days_string(bool short_string = true) const;
		QL_SOURCE std::pair<ql::size, std::string> pair_days_week_string(bool short_string = true) const;
		QL_SOURCE std::pair<ql::size, std::string> pair_weeks_string(bool short_string = true) const;
		QL_SOURCE std::pair<ql::size, std::string> pair_years_string(bool short_string = true) const;

		QL_SOURCE std::vector<std::pair<ql::size, std::string>>
		get_string_pair_segments(bool short_string = true, bool weeks = true) const;
		QL_SOURCE std::vector<std::string> get_string_segments(bool short_string = true, bool weeks = true) const;
		QL_SOURCE std::vector<std::string> get_full_string_segments(bool short_string = true, bool weeks = true) const;
		QL_SOURCE std::vector<std::string> get_string_active_segments(
				ql::size stop_at_segment,
				bool short_string = true,
				bool weeks = true,
				ql::size precision = ql::size_max
		) const;

		QL_SOURCE std::string string_full(
				std::string_view parantheses = "[]",
				std::string_view seperation = " : ",
				bool short_string = true,
				bool weeks = true
		) const;
		QL_SOURCE std::string string_until_segment(
				ql::size stop_at_segment,
				std::string_view parantheses = "[]",
				std::string_view seperation = " : ",
				bool short_string = true,
				bool weeks = true,
				ql::size precision = ql::size_max,
				bool use_and = true
		) const;

		QL_SOURCE std::string string(
				std::string_view parantheses = "[]",
				std::string_view seperation = " : ",
				bool short_string = true,
				bool weeks = true,
				ql::size precision = ql::size_max
		) const;
		QL_SOURCE std::string string_until_hour(
				std::string_view parantheses = "[]",
				std::string_view seperation = " : ",
				bool short_string = true,
				bool weeks = true,
				ql::size precision = ql::size_max
		) const;
		QL_SOURCE std::string string_until_min(
				std::string_view parantheses = "[]",
				std::string_view seperation = " : ",
				bool short_string = true,
				bool weeks = true,
				ql::size precision = ql::size_max
		) const;
		QL_SOURCE std::string string_until_sec(
				std::string_view parantheses = "[]",
				std::string_view seperation = " : ",
				bool short_string = true,
				bool weeks = true,
				ql::size precision = ql::size_max
		) const;
		QL_SOURCE std::string string_until_ms(
				std::string_view parantheses = "[]",
				std::string_view seperation = " : ",
				bool short_string = true,
				bool weeks = true,
				ql::size precision = ql::size_max
		) const;

		QL_SOURCE std::string
		descriptive_string(ql::size precision = ql::size_max, bool weeks = true, ql::size stop_at_segment = ql::size_max) const;
		QL_SOURCE std::string
		descriptive_string_no_and(ql::size precision = ql::size_max, bool weeks = true, ql::size stop_at_segment = ql::size_max) const;
		QL_SOURCE std::string
		compact_string(ql::size precision = ql::size_max, bool weeks = true, ql::size stop_at_segment = ql::size_max) const;

		QL_SOURCE std::string small_string(
				ql::size precision = 2u,
				bool weeks = true,
				bool short_string = true,
				std::string_view parantheses = "[]",
				std::string_view seperation = " : "
		) const;
		QL_SOURCE std::string small_descriptive_string(ql::size precision = 2u, bool weeks = true) const;
		QL_SOURCE std::string small_descriptive_string_no_and(ql::size precision = 2u, bool weeks = true) const;
		QL_SOURCE std::string small_compact_string(ql::size precision = 2u, bool weeks = true) const;

		QL_SOURCE std::string to_string() const;

		QL_SOURCE static time clock_time();
		QL_SOURCE ql::f64 frequency() const;

		QL_SOURCE ql::u64 nsecs() const;
		QL_SOURCE ql::u64 usecs() const;
		QL_SOURCE ql::u64 msecs() const;
		QL_SOURCE ql::u64 secs() const;
		QL_SOURCE ql::u64 mins() const;
		QL_SOURCE ql::u64 hours() const;
		QL_SOURCE ql::u64 days() const;
		QL_SOURCE ql::u64 weeks() const;
		QL_SOURCE ql::u64 years() const;

		QL_SOURCE ql::u64 nsecs_mod() const;
		QL_SOURCE ql::u64 usecs_mod() const;
		QL_SOURCE ql::u64 msecs_mod() const;
		QL_SOURCE ql::u64 secs_mod() const;
		QL_SOURCE ql::u64 mins_mod() const;
		QL_SOURCE ql::u64 hours_mod() const;
		QL_SOURCE ql::u64 days_mod() const;
		QL_SOURCE ql::u64 days_week_mod() const;
		QL_SOURCE ql::u64 weeks_mod() const;
		QL_SOURCE ql::u64 years_mod() const;

		QL_SOURCE ql::f64 nsecs_f() const;
		QL_SOURCE ql::f64 usecs_f() const;
		QL_SOURCE ql::f64 msecs_f() const;
		QL_SOURCE ql::f64 secs_f() const;
		QL_SOURCE ql::f64 mins_f() const;
		QL_SOURCE ql::f64 hours_f() const;
		QL_SOURCE ql::f64 days_f() const;
		QL_SOURCE ql::f64 years_f() const;

		constexpr static ql::u64 nsecs_in_usec = ql::u64{1000ull};
		constexpr static ql::u64 usecs_in_msec = ql::u64{1000ull};
		constexpr static ql::u64 msecs_in_sec = ql::u64{1000ull};
		constexpr static ql::u64 secs_in_min = ql::u64{60ull};
		constexpr static ql::u64 mins_in_hour = ql::u64{60ull};
		constexpr static ql::u64 hours_in_day = ql::u64{24ull};
		constexpr static ql::u64 days_in_year = ql::u64{365ull};
		constexpr static ql::u64 days_in_week = ql::u64{7ull};
		constexpr static ql::u64 weeks_in_year = ql::u64{52ull};

		constexpr static ql::u64 nsecs_in_nsec = ql::u64{1ull};
		constexpr static ql::u64 nsecs_in_msec = usecs_in_msec * nsecs_in_usec;
		constexpr static ql::u64 nsecs_in_sec = msecs_in_sec * nsecs_in_msec;
		constexpr static ql::u64 nsecs_in_min = secs_in_min * nsecs_in_sec;
		constexpr static ql::u64 nsecs_in_hour = mins_in_hour * nsecs_in_min;
		constexpr static ql::u64 nsecs_in_day = hours_in_day * nsecs_in_hour;
		constexpr static ql::u64 nsecs_in_week = days_in_week * nsecs_in_day;
		constexpr static ql::u64 nsecs_in_year = days_in_year * nsecs_in_day;

		QL_SOURCE void set(ql::u64 ns);
		QL_SOURCE operator ql::u64() const;
	};

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::time nsecs(T value)
	{
		return ql::time{static_cast<ql::u64>(value)};
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::time usecs(T value)
	{
		return ql::time{static_cast<ql::u64>(value * ql::time::nsecs_in_usec)};
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::time msecs(T value)
	{
		return ql::time{static_cast<ql::u64>(value * ql::time::nsecs_in_msec)};
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::time secs(T value)
	{
		return ql::time{static_cast<ql::u64>(value * ql::time::nsecs_in_sec)};
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::time mins(T value)
	{
		return ql::time{static_cast<ql::u64>(value * ql::time::nsecs_in_min)};
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::time hours(T value)
	{
		return ql::time{static_cast<ql::u64>(value * ql::time::nsecs_in_hour)};
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::time days(T value)
	{
		return ql::time{static_cast<ql::u64>(value * ql::time::nsecs_in_day)};
	}

	template <typename T>
	requires (ql::is_arithmetic<T>())
	constexpr ql::time years(T value)
	{
		return ql::time{static_cast<ql::u64>(value * ql::time::nsecs_in_year)};
	}

	class clock
	{
		ql::time m_pause;
		ql::time m_pause_sum;
		ql::time m_begin;
		mutable ql::time m_end;
		bool m_running;

	 public:
		clock(bool running = true)
		{
			this->init(running);
		}

		QL_SOURCE void reset();
		QL_SOURCE void pause();
		QL_SOURCE void reset_pause();
		QL_SOURCE void resume();
		QL_SOURCE bool is_running() const;
		QL_SOURCE bool is_paused() const;

		QL_SOURCE ql::time elapsed() const;
		QL_SOURCE std::string elapsed_str() const;
		QL_SOURCE ql::f64 elapsed_f() const;

		QL_SOURCE ql::time elapsed_reset();
		QL_SOURCE std::string elapsed_str_reset();
		QL_SOURCE ql::f64 elapsed_f_reset();

		QL_SOURCE void add(ql::f64 seconds);
		QL_SOURCE void add(ql::time time);
		QL_SOURCE void subtract(ql::f64 seconds);
		QL_SOURCE void subtract(ql::time time);

		QL_SOURCE bool has_elapsed(ql::f64 seconds) const;
		QL_SOURCE bool has_elapsed(ql::time duration) const;
		QL_SOURCE bool has_elapsed_reset(ql::f64 seconds);
		QL_SOURCE bool has_elapsed_reset(ql::time duration);

		QL_SOURCE void measure() const;
		QL_SOURCE void init(bool running);

		QL_SOURCE std::string to_string() const;
	};

	class halted_clock : public ql::clock
	{
	 public:
		halted_clock() : ql::clock(false)
		{
		}
	};

	class small_clock
	{
	 public:
		small_clock()
		{
			this->reset();
		}

		QL_SOURCE void reset();

		QL_SOURCE ql::time elapsed() const;
		QL_SOURCE std::string elapsed_str() const;
		QL_SOURCE ql::f64 elapsed_f() const;

		QL_SOURCE ql::time elapsed_reset();
		QL_SOURCE std::string elapsed_str_reset();
		QL_SOURCE ql::f64 elapsed_f_reset();

		QL_SOURCE void add(ql::f64 seconds);
		QL_SOURCE void add(ql::time time);
		QL_SOURCE void subtract(ql::f64 seconds);
		QL_SOURCE void subtract(ql::time time);

		QL_SOURCE bool has_elapsed(ql::f64 seconds) const;
		QL_SOURCE bool has_elapsed(ql::time duration) const;
		QL_SOURCE bool has_elapsed_reset(ql::f64 seconds);
		QL_SOURCE bool has_elapsed_reset(ql::time duration);

		ql::time m_begin;
	};

	struct fps_counter
	{
		fps_counter()
		{
			this->reset();
		}

		void set_time_period(ql::u32 time_period)
		{
			this->ema.time_period = time_period;
		}

		ql::u32 get_time_period() const
		{
			return ql::u32_cast(this->ema.time_period);
		}

		void reset()
		{
			this->ema.reset();
			this->ema.time_period = 100u;
			this->clock.reset();
			this->start = false;
		}

		void measure()
		{
			if (!this->start)
			{
				this->start = true;
				this->clock.reset();
			}
			else
			{
				this->ema.add(this->clock.elapsed_f_reset());
			}
		}

		ql::u32 get_fps_u32() const
		{
			if (!this->ema.get_average())
			{
				return 0u;
			}
			return ql::u32_cast(1.0 / this->ema.get_average());
		}

		ql::f64 get_fps() const
		{
			if (!this->ema.get_average())
			{
				return 0.0;
			}
			return 1.0 / this->ema.get_average();
		}

		bool start;
		ql::clock clock;
		ql::exponential_moving_average ema;
	};

	QL_SOURCE void wait(ql::time duration);
	QL_SOURCE void wait(double seconds);
	QL_SOURCE void wait_while(double seconds);

	template <typename T>
	constexpr std::time_t to_time_t(T t)
	{
		using namespace std::chrono;
		auto sctp = time_point_cast<system_clock::duration>(t - T::clock::now() + system_clock::now());
		return system_clock::to_time_t(sctp);
	}

	template <typename T>
	std::string get_time_string(T duration, std::string format = "%Y-%m-%d-%H-%M-%S")
	{
		std::time_t time;
		if constexpr (ql::is_same<T, std::time_t>())
		{
			time = duration;
		}
		else
		{
			time = ql::to_time_t(duration);
		}

#pragma warning(push)
#pragma warning(disable : 4996)
		std::tm* gmt = std::localtime(&time);
#pragma warning(pop)

		std::ostringstream buffer;
		buffer << std::put_time(gmt, format.c_str());
		return buffer.str();
	}

	QL_SOURCE std::chrono::system_clock::time_point get_current_local_time();
	QL_SOURCE std::chrono::system_clock::time_point get_current_system_time();
	QL_SOURCE std::chrono::utc_clock::time_point get_current_utc_time();
	QL_SOURCE std::chrono::local_time<std::chrono::system_clock::duration> get_current_zoned_time();

	QL_SOURCE std::string get_current_time_string(const std::string_view& format = "%Y-%m-%d-%H-%M-%S");
	QL_SOURCE std::string get_current_time_string_ms();
	QL_SOURCE std::string get_current_time_string_ymd_hms();
	QL_SOURCE std::string get_current_time_string_ymd_hmsms();
	QL_SOURCE std::string get_current_time_string_ymd_hmsms_compact();
	QL_SOURCE std::string get_current_time_string_ymdhmsms_compact();

	QL_SOURCE std::optional<std::chrono::system_clock::time_point>
	utc_data_ymdhm_to_utc_timepoint(std::string date, std::string format = "%F %T");

	template <typename C>
	requires (ql::is_container<C>())
	auto data_ymdhm_to_timepoint(const C& values)
	{
		std::tm tm = {
				/* tm_sec  */ 0,
				/* tm_min  */ ql::i32_cast(values.at(4)),
				/* tm_hour */ ql::i32_cast(values.at(3)),
				/* tm_mday */ ql::i32_cast(values.at(2)),
				/* tm_mon  */ ql::i32_cast(values.at(1) - 1),
				/* tm_year */ ql::i32_cast(values.at(0) - 1900),
		};
		// tm.tm_isdst = -1; // local time zone
		return std::chrono::system_clock::from_time_t(std::mktime(&tm));
	}

	template <typename C>
	requires (ql::is_container<C>())
	auto data_ymdhms_to_timepoint(const C& values)
	{
		std::tm tm = {
				/* tm_sec  */ ql::i32_cast(values.at(5)),
				/* tm_min  */ ql::i32_cast(values.at(4)),
				/* tm_hour */ ql::i32_cast(values.at(3)),
				/* tm_mday */ ql::i32_cast(values.at(2)),
				/* tm_mon  */ ql::i32_cast(values.at(1) - 1),
				/* tm_year */ ql::i32_cast(values.at(0) - 1900),
		};
		// tm.tm_isdst = -1; // local time zone
		return std::chrono::system_clock::from_time_t(std::mktime(&tm));
	}

	QL_SOURCE ql::time get_remaining_time(ql::f64 progress, ql::time elapsed);
	QL_SOURCE ql::time get_remaining_time(ql::f64 progress, ql::clock timer);

	template <typename T, typename U>
	requires (ql::is_integer<T>() && ql::is_integer<U>())
	ql::time get_remaining_time(T start, U end, ql::time elapsed)
	{
		return ql::get_remaining_time(ql::f64_cast(start) / end, elapsed);
	}

	template <typename T, typename U>
	requires (ql::is_integer<T>() && ql::is_integer<U>())
	ql::time get_remaining_time(T start, U end, ql::clock timer)
	{
		return ql::get_remaining_time(ql::f64_cast(start) / end, timer.elapsed());
	}

	namespace detail
	{
		QL_SOURCE extern std::unordered_map<std::string, std::unordered_map<std::string, ql::halted_clock>> sub_benchmark_clocks;
		QL_SOURCE extern std::unordered_map<std::string, ql::halted_clock> benchmark_clocks;
		QL_SOURCE extern std::string last_benchmark_name;
		QL_SOURCE extern std::string last_sub_benchmark_name;

		QL_SOURCE extern clock signal_clock;
		QL_SOURCE extern ql::u64 signal_count;
	}	 // namespace detail

	QL_SOURCE void begin_benchmark_end_previous(const std::string& name);
	QL_SOURCE void begin_benchmark_end_previous(const std::string& sub, const std::string& name);
	QL_SOURCE ql::halted_clock get_benchmark(const std::string& name = "");
	QL_SOURCE void begin_benchmark(const std::string& name = "");
	QL_SOURCE void begin_benchmark(const std::string& sub, const std::string& name);
	QL_SOURCE void end_benchmark();
	QL_SOURCE void end_benchmark(const std::string& name);

	template <typename F>
	void benchmark(std::string name, F&& function)
	{
		ql::begin_benchmark(name);
		std::invoke(function);
		ql::end_benchmark(name);
	}

	QL_SOURCE void clear_benchmark();
	QL_SOURCE void reset_benchmark();
	QL_SOURCE void begin_benchmark_segments();
	QL_SOURCE void print_benchmark();
	QL_SOURCE void print_benchmark(const std::string& name);

	QL_SOURCE void reset_time_signal();
	QL_SOURCE bool get_time_signal(double seconds);
	QL_SOURCE bool get_time_signal(ql::time time);

	QL_SOURCE void reset_count_signal();
	QL_SOURCE bool get_count_signal(ql::u64 when);

	struct animation
	{
		ql::f64 duration = 1.0;
		ql::f64 progress = 0.0;
		ql::f64 progress_before = ql::f64_max;
		bool reversed = false;
		bool running = false;
		bool just_finish = false;
		bool just_finish_reverse = false;
		bool just_finish_no_reverse = false;
		bool internal_change_flag = false;
		bool progress_change_flag = true;

		QL_SOURCE void internal_reset();
		QL_SOURCE void reset();
		QL_SOURCE void start();
		QL_SOURCE void stop();
		QL_SOURCE void reset_and_start();
		QL_SOURCE void reset_and_start_reverse();
		QL_SOURCE void set_duration(ql::f64 duration);
		QL_SOURCE void update(ql::f64 frame_time);
#if defined QL_GRAPHIC
		QL_SOURCE void update(const ql::event_manager& event);
#endif
		QL_SOURCE bool is_running() const;
		QL_SOURCE bool is_reversed() const;
		QL_SOURCE bool changed() const;
		QL_SOURCE void go_forwards();
		QL_SOURCE void go_backwards();
		QL_SOURCE bool just_finished() const;
		QL_SOURCE bool just_finished_reverse() const;
		QL_SOURCE bool just_finished_no_reverse() const;
		QL_SOURCE bool has_progress() const;
		QL_SOURCE void set_progress(ql::f64 progress, bool backwards = false);
		QL_SOURCE ql::f64 get_progress() const;
		QL_SOURCE ql::f64 get_curve_progress(ql::f64 curve = 1.5) const;
		QL_SOURCE ql::f64 get_double_curve_progress(ql::f64 curve = 1.5) const;
	};

	template <typename T>
	struct value_animation : animation
	{
		T begin;
		T end;
		double curve = 1.5;
		bool use_double_curve = true;

		void set_begin(T value)
		{
			this->begin = value;
		}

		void set_end(T value)
		{
			this->end = value;
		}

		void set_range(T begin, T end)
		{
			this->begin = begin;
			this->end = end;
		}

		void set_curve(ql::f64 curve)
		{
			this->curve = curve;
		}

		void enable_double_curve()
		{
			this->use_double_curve = true;
		}

		void disable_double_curve()
		{
			this->use_double_curve = false;
		}

		ql::f64 get_resulting_progress() const
		{
			if (this->use_double_curve)
			{
				return this->get_double_curve_progress(this->curve);
			}
			else
			{
				return this->get_curve_progress(this->curve);
			}
		}

		T get() const
		{
			auto p = this->get_resulting_progress();
			return ql::linear_interpolation(this->begin, this->end, p);
		}

		T get(T begin) const
		{
			auto p = this->get_resulting_progress();
			return ql::linear_interpolation(begin, this->end, p);
		}

		T get(T begin, T end) const
		{
			auto p = this->get_resulting_progress();
			return ql::linear_interpolation(begin, end, p);
		}
	};

	struct timed_task
	{
		ql::small_clock clock;
		ql::time wait_duration;
		std::function<void(void)> function;
		std::string name = "";
		bool done_before = false;
		bool just_finish = false;

		timed_task()
		{
		}

		timed_task(ql::time wait_duration, std::function<void(void)> function, const std::string& name = "")
		{
			this->wait_duration = wait_duration;
			this->function = function;
			this->name = name;
		}

		timed_task(ql::f64 wait_duration, std::function<void(void)> function, const std::string& name = "")
		{
			this->wait_duration = ql::secs(wait_duration);
			this->function = function;
			this->name = name;
		}

		QL_SOURCE void update();
		QL_SOURCE bool is_done() const;
		QL_SOURCE bool is_running() const;
		QL_SOURCE bool just_finished() const;
		QL_SOURCE void set_wait_duration(ql::time time);
		QL_SOURCE void set_wait_duration(ql::f64 seconds);
		QL_SOURCE ql::f64 get_wait_progress() const;
	};

	struct timed_task_manager
	{
		std::vector<timed_task> tasks;
		std::set<std::string> finished_tasks;

		QL_SOURCE void clear();
		QL_SOURCE void cleanup();
		QL_SOURCE bool is_task_finished(const std::string& name);
		QL_SOURCE bool is_task_running(const std::string& name);
		QL_SOURCE void add_timed_task(ql::time time, std::function<void(void)> function, const std::string& name = "");
		QL_SOURCE void add_timed_task(ql::f64 time, std::function<void(void)> function, const std::string& name = "");
		QL_SOURCE void update();
	};

	namespace detail
	{
		QL_SOURCE extern timed_task_manager tasks;
	}

	QL_SOURCE void start_timed_task(ql::time time, const std::string& name, std::function<void(void)> function);
	QL_SOURCE void start_timed_task(ql::time time, std::function<void(void)> function);
	QL_SOURCE void start_timed_task(ql::f64 time, const std::string& name, std::function<void(void)> function);
	QL_SOURCE void start_timed_task(ql::f64 time, std::function<void(void)> function);
	QL_SOURCE bool timed_task_finished(const std::string& name = "");
	QL_SOURCE bool timed_task_running(const std::string& name = "");
	QL_SOURCE void clear_timed_tasks();
	QL_SOURCE void update_tasks();
}	 // namespace ql