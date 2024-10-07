#include <ql/core/time/time.hpp>

#include <chrono>
#include <algorithm>
#include <ctime>
#include <thread>

#include <ql/core/type/type.hpp>
#include <ql/core/maths/maths.hpp>
#include <ql/core/string/to-string.hpp>

#include <ql/core/transform/interpolate/curve.hpp>

#include <ql/core/system/system.hpp>

#ifdef QL_SFML
#include <ql/graphic/event-info.hpp>
#endif

namespace ql
{
	ql::time ql::time::clock_time()
	{
		return ql::time{static_cast<ql::u64>(
				std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()
		)};
	}

	ql::time& ql::time::operator+=(const ql::time& other)
	{
		this->ns += other.ns;
		return *this;
	}

	ql::time ql::time::operator+(const ql::time& other) const
	{
		auto copy = *this;
		copy += other;
		return copy;
	}

	ql::time& ql::time::operator-=(const ql::time& other)
	{
		if (other.ns >= this->ns)
		{
			this->ns = 0;
		}
		else
		{
			this->ns -= other.ns;
		}
		return *this;
	}

	ql::time ql::time::operator-(const ql::time& other) const
	{
		auto copy = *this;
		copy -= other;
		return copy;
	}

	ql::time& ql::time::operator/=(const ql::time& other)
	{
		this->ns /= other.ns;
		return *this;
	}

	ql::time ql::time::operator/(const ql::time& other) const
	{
		auto copy = *this;
		copy /= other;
		return copy;
	}

	ql::time& ql::time::operator%=(const ql::time& other)
	{
		this->ns %= other.ns;
		return *this;
	}

	ql::time ql::time::operator%(const ql::time& other) const
	{
		auto copy = *this;
		copy %= other;
		return copy;
	}

	bool ql::time::operator==(const ql::time& other) const
	{
		return this->ns == other.ns;
	}

	bool ql::time::operator!=(const ql::time& other) const
	{
		return this->ns != other.ns;
	}

	bool ql::time::operator<(const ql::time& other) const
	{
		return this->ns < other.ns;
	}

	bool ql::time::operator<=(const ql::time& other) const
	{
		return this->ns <= other.ns;
	}

	bool ql::time::operator>(const ql::time& other) const
	{
		return this->ns > other.ns;
	}

	bool ql::time::operator>=(const ql::time& other) const
	{
		return this->ns >= other.ns;
	}

	std::string ql::time::single_short_nsecs_string() const
	{
		return ql::to_string(
				ql::string_to_fit(ql::to_string(this->nsecs_mod()), '0', ql::number_of_digits(this->nsecs_in_usec - 1)),
				this->nsecs_mod(), "ns"
		);
	}

	std::string ql::time::single_short_usecs_string() const
	{
		return ql::to_string(
				ql::string_to_fit(ql::to_string(this->usecs_mod()), '0', ql::number_of_digits(this->usecs_in_msec - 1)),
				this->usecs_mod(), "us"
		);
	}

	std::string ql::time::single_short_msecs_string() const
	{
		return ql::to_string(
				ql::string_to_fit(ql::to_string(this->msecs_mod()), '0', ql::number_of_digits(this->msecs_in_sec - 1)), this->msecs_mod(),
				"ms"
		);
	}

	std::string ql::time::single_short_secs_string() const
	{
		return ql::to_string(
				ql::string_to_fit(ql::to_string(this->secs_mod()), '0', ql::number_of_digits(this->secs_in_min - 1)), this->secs_mod(),
				's'
		);
	}

	std::string ql::time::single_short_mins_string() const
	{
		return ql::to_string(
				ql::string_to_fit(ql::to_string(this->mins_mod()), '0', ql::number_of_digits(this->mins_in_hour - 1)), this->mins_mod(),
				'm'
		);
	}

	std::string ql::time::single_short_hours_string() const
	{
		return ql::to_string(
				ql::string_to_fit(ql::to_string(this->hours_mod()), '0', ql::number_of_digits(this->hours_in_day - 1)), this->hours_mod(),
				'h'
		);
	}

	std::string ql::time::single_short_days_string() const
	{
		return ql::to_string(
				ql::string_to_fit(ql::to_string(this->days_mod()), '0', ql::number_of_digits(this->days_in_year - 1)), this->days_mod(),
				'd'
		);
	}

	std::string ql::time::single_short_days_week_string() const
	{
		return ql::to_string(
				ql::string_to_fit(ql::to_string(this->days_week_mod()), '0', ql::number_of_digits(this->days_in_week - 1)),
				this->days_week_mod(), 'd'
		);
	}

	std::string ql::time::single_short_weeks_string() const
	{
		return ql::to_string(
				ql::string_to_fit(ql::to_string(this->weeks_mod()), '0', ql::number_of_digits(this->weeks_in_year - 1)),
				this->weeks_mod(), 'w'
		);
	}

	std::string ql::time::single_short_years_string() const
	{
		return ql::to_string(this->years(), 'y');
	}

	std::string ql::time::single_descriptive_nsecs_string() const
	{
		return ql::to_string(this->nsecs_mod(), " nanosecond", this->nsecs_mod() == 1u ? "" : "s");
	}

	std::string ql::time::single_descriptive_usecs_string() const
	{
		return ql::to_string(this->usecs_mod(), " microsecond", this->usecs_mod() == 1u ? "" : "s");
	}

	std::string ql::time::single_descriptive_msecs_string() const
	{
		return ql::to_string(this->msecs_mod(), " millisecond", this->msecs_mod() == 1u ? "" : "s");
	}

	std::string ql::time::single_descriptive_secs_string() const
	{
		return ql::to_string(this->secs_mod(), " second", this->secs_mod() == 1u ? "" : "s");
	}

	std::string ql::time::single_descriptive_mins_string() const
	{
		return ql::to_string(this->mins_mod(), " minute", this->mins_mod() == 1u ? "" : "s");
	}

	std::string ql::time::single_descriptive_hours_string() const
	{
		return ql::to_string(this->hours_mod(), " hour", this->hours_mod() == 1u ? "" : "s");
	}

	std::string ql::time::single_descriptive_days_string() const
	{
		return ql::to_string(this->days_mod(), " day", this->days_mod() == 1u ? "" : "s");
	}

	std::string ql::time::single_descriptive_days_week_string() const
	{
		return ql::to_string(this->days_week_mod(), " day", this->days_week_mod() == 1u ? "" : "s");
	}

	std::string ql::time::single_descriptive_weeks_string() const
	{
		return ql::to_string(this->weeks_mod(), " week", this->weeks_mod() == 1u ? "" : "s");
	}

	std::string ql::time::single_descriptive_years_string() const
	{
		return ql::to_string(this->years(), " year", this->years() == 1u ? "" : "s");
	}

	std::string ql::time::nsecs_string(bool short_string) const
	{
		return short_string ? this->single_short_nsecs_string() : this->single_descriptive_nsecs_string();
	}

	std::string ql::time::usecs_string(bool short_string) const
	{
		return short_string ? this->single_short_usecs_string() : this->single_descriptive_usecs_string();
	}

	std::string ql::time::msecs_string(bool short_string) const
	{
		return short_string ? this->single_short_msecs_string() : this->single_descriptive_msecs_string();
	}

	std::string ql::time::secs_string(bool short_string) const
	{
		return short_string ? this->single_short_secs_string() : this->single_descriptive_secs_string();
	}

	std::string ql::time::mins_string(bool short_string) const
	{
		return short_string ? this->single_short_mins_string() : this->single_descriptive_mins_string();
	}

	std::string ql::time::hours_string(bool short_string) const
	{
		return short_string ? this->single_short_hours_string() : this->single_descriptive_hours_string();
	}

	std::string ql::time::days_string(bool short_string) const
	{
		return short_string ? this->single_short_days_string() : this->single_descriptive_days_string();
	}

	std::string ql::time::days_week_string(bool short_string) const
	{
		return short_string ? this->single_short_days_week_string() : this->single_descriptive_days_week_string();
	}

	std::string ql::time::weeks_string(bool short_string) const
	{
		return short_string ? this->single_short_weeks_string() : this->single_descriptive_weeks_string();
	}

	std::string ql::time::years_string(bool short_string) const
	{
		return short_string ? this->single_short_years_string() : this->single_descriptive_years_string();
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_nsecs_string() const
	{
		return std::make_pair(this->nsecs_mod(), "ns");
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_usecs_string() const
	{
		return std::make_pair(this->usecs_mod(), "us");
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_msecs_string() const
	{
		return std::make_pair(this->msecs_mod(), "ms");
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_secs_string() const
	{
		return std::make_pair(this->secs_mod(), "s");
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_mins_string() const
	{
		return std::make_pair(this->mins_mod(), "m");
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_hours_string() const
	{
		return std::make_pair(this->hours_mod(), "h");
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_days_string() const
	{
		return std::make_pair(this->days_mod(), "d");
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_days_week_string() const
	{
		return std::make_pair(this->days_mod(), "d");
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_weeks_string() const
	{
		return std::make_pair(this->weeks_mod(), "w");
	}

	std::pair<ql::size, std::string> ql::time::single_short_pair_years_string() const
	{
		return std::make_pair(this->years(), "y");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_nsecs_string() const
	{
		return std::make_pair(this->nsecs_mod(), this->nsecs_mod() == 1u ? "nanosecond" : "nanoseconds");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_usecs_string() const
	{
		return std::make_pair(this->usecs_mod(), this->usecs_mod() == 1u ? "microsecond" : "microseconds");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_msecs_string() const
	{
		return std::make_pair(this->msecs_mod(), this->msecs_mod() == 1u ? "millisecond" : "milliseconds");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_secs_string() const
	{
		return std::make_pair(this->secs_mod(), this->secs_mod() == 1u ? "second" : "seconds");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_mins_string() const
	{
		return std::make_pair(this->mins_mod(), this->mins_mod() == 1u ? "minute" : "minutes");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_hours_string() const
	{
		return std::make_pair(this->mins_mod(), this->mins_mod() == 1u ? "hour" : "hours");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_days_string() const
	{
		return std::make_pair(this->days_mod(), this->days_mod() == 1u ? "day" : "days");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_days_week_string() const
	{
		return std::make_pair(this->days_week_mod(), this->days_week_mod() == 1u ? "day" : "days");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_weeks_string() const
	{
		return std::make_pair(this->weeks_mod(), this->weeks_mod() == 1u ? "week" : "weeks");
	}

	std::pair<ql::size, std::string> ql::time::single_descriptive_pair_years_string() const
	{
		return std::make_pair(this->years(), this->years() == 1u ? "year" : "years");
	}

	std::pair<ql::size, std::string> ql::time::pair_nsecs_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_nsecs_string() : this->single_descriptive_pair_nsecs_string();
	}

	std::pair<ql::size, std::string> ql::time::pair_usecs_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_usecs_string() : this->single_descriptive_pair_usecs_string();
	}

	std::pair<ql::size, std::string> ql::time::pair_msecs_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_msecs_string() : this->single_descriptive_pair_msecs_string();
	}

	std::pair<ql::size, std::string> ql::time::pair_secs_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_secs_string() : this->single_descriptive_pair_secs_string();
	}

	std::pair<ql::size, std::string> ql::time::pair_mins_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_mins_string() : this->single_descriptive_pair_mins_string();
	}

	std::pair<ql::size, std::string> ql::time::pair_hours_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_hours_string() : this->single_descriptive_pair_hours_string();
	}

	std::pair<ql::size, std::string> ql::time::pair_days_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_days_string() : this->single_descriptive_pair_days_string();
	}

	std::pair<ql::size, std::string> ql::time::pair_days_week_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_days_week_string() : this->single_descriptive_pair_days_week_string();
	}

	std::pair<ql::size, std::string> ql::time::pair_weeks_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_weeks_string() : this->single_descriptive_pair_weeks_string();
	}

	std::pair<ql::size, std::string> ql::time::pair_years_string(bool short_string) const
	{
		return short_string ? this->single_short_pair_years_string() : this->single_descriptive_pair_years_string();
	}

	std::vector<std::pair<ql::size, std::string>> ql::time::get_string_pair_segments(bool short_string, bool weeks) const
	{
		std::vector<std::pair<ql::size, std::string>> result;
		if (this->years())
		{
			result.emplace_back(this->pair_years_string(short_string));
		}
		else
		{
			result.push_back(std::make_pair(0ull, ""));
		}
		if (weeks)
		{
			if (this->weeks_mod())
			{
				result.emplace_back(this->pair_weeks_string(short_string));
			}
			else
			{
				result.push_back(std::make_pair(0ull, ""));
			}
			if (this->days_week_mod())
			{
				result.emplace_back(this->pair_days_week_string(short_string));
			}
			else
			{
				result.push_back(std::make_pair(0ull, ""));
			}
		}
		else
		{
			if (this->days_mod())
			{
				result.emplace_back(this->pair_days_string(short_string));
			}
			else
			{
				result.push_back(std::make_pair(0ull, ""));
			}
		}
		if (this->hours_mod())
		{
			result.emplace_back(this->pair_hours_string(short_string));
		}
		else
		{
			result.push_back(std::make_pair(0ull, ""));
		}
		if (this->mins_mod())
		{
			result.emplace_back(this->pair_mins_string(short_string));
		}
		else
		{
			result.push_back(std::make_pair(0ull, ""));
		}
		if (this->secs_mod())
		{
			result.emplace_back(this->pair_secs_string(short_string));
		}
		else
		{
			result.push_back(std::make_pair(0ull, ""));
		}
		if (this->msecs_mod())
		{
			result.emplace_back(this->pair_msecs_string(short_string));
		}
		else
		{
			result.push_back(std::make_pair(0ull, ""));
		}
		if (this->usecs_mod())
		{
			result.emplace_back(this->pair_usecs_string(short_string));
		}
		else
		{
			result.push_back(std::make_pair(0ull, ""));
		}
		return result;
	}

	std::vector<std::string> ql::time::get_string_segments(bool short_string, bool weeks) const
	{
		std::vector<std::string> result;
		if (this->years())
		{
			result.emplace_back(this->years_string(short_string));
		}
		else
		{
			result.emplace_back("");
		}
		if (weeks)
		{
			if (this->weeks_mod())
			{
				result.emplace_back(this->weeks_string(short_string));
			}
			else
			{
				result.emplace_back("");
			}
			if (this->days_week_mod())
			{
				result.emplace_back(this->days_week_string(short_string));
			}
			else
			{
				result.emplace_back("");
			}
		}
		else
		{
			if (this->days_mod())
			{
				result.emplace_back(this->days_string(short_string));
			}
			else
			{
				result.emplace_back("");
			}
		}
		if (this->hours_mod())
		{
			result.emplace_back(this->hours_string(short_string));
		}
		else
		{
			result.emplace_back("");
		}
		if (this->mins_mod())
		{
			result.emplace_back(this->mins_string(short_string));
		}
		else
		{
			result.emplace_back("");
		}
		if (this->secs_mod())
		{
			result.emplace_back(this->secs_string(short_string));
		}
		else
		{
			result.emplace_back("");
		}
		if (this->msecs_mod())
		{
			result.emplace_back(this->msecs_string(short_string));
		}
		else
		{
			result.emplace_back("");
		}
		if (this->usecs_mod())
		{
			result.emplace_back(this->usecs_string(short_string));
		}
		else
		{
			result.emplace_back("");
		}
		return result;
	}

	std::vector<std::string> ql::time::get_full_string_segments(bool short_string, bool weeks) const
	{
		std::vector<std::string> result;
		result.emplace_back(this->years_string(short_string));
		if (weeks)
		{
			result.emplace_back(this->weeks_string(short_string));
			result.emplace_back(this->days_week_string(short_string));
		}
		else
		{
			result.emplace_back(this->days_string(short_string));
		}
		result.emplace_back(this->hours_string(short_string));
		result.emplace_back(this->mins_string(short_string));
		result.emplace_back(this->secs_string(short_string));
		result.emplace_back(this->msecs_string(short_string));
		result.emplace_back(this->usecs_string(short_string));
		return result;
	}

	std::vector<std::string>
	ql::time::get_string_active_segments(ql::size stop_at_segment, bool short_string, bool weeks, ql::size precision) const
	{
		auto segments = this->get_string_segments(short_string, weeks);

		auto stop = ql::min(stop_at_segment, segments.size());
		ql::size found = 0u;
		std::vector<std::string> result;
		for (ql::size i = 0u; i < stop && found < precision; ++i)
		{
			if (!segments[i].empty())
			{
				++found;
				result.emplace_back(segments[i]);
			}
		}
		if (segments.empty())
		{
			segments.emplace_back(segments[stop_at_segment]);
		}
		return result;
	}

	std::string ql::time::string_until_segment(
			ql::size stop_at_segment,
			std::string_view parantheses,
			std::string_view seperation,
			bool short_string,
			bool weeks,
			ql::size precision,
			bool use_and
	) const
	{
		std::ostringstream stream;
		if (parantheses.size() > 0)
		{
			stream << parantheses[0];
		}
		auto segments = this->get_string_active_segments(stop_at_segment, short_string, weeks, precision);
		auto stop = ql::min(segments.size(), stop_at_segment);

		for (ql::size i = 0u; i < stop; ++i)
		{
			if (i)
			{
				if (use_and && !short_string && i == stop - 1)
				{
					stream << " and ";
				}
				else
				{
					stream << seperation;
				}
			}
			stream << segments[i];
		}

		if (parantheses.size() > 1)
		{
			stream << parantheses[1];
		}
		return stream.str();
	}

	std::string
	ql::time::string_full(std::string_view parantheses, std::string_view seperation, bool short_string, bool weeks) const
	{
		std::ostringstream stream;
		if (parantheses.size() > 0)
		{
			stream << parantheses[0];
		}

		auto segments = this->get_full_string_segments(short_string, weeks);
		for (ql::size i = 0u; i < segments.size(); ++i)
		{
			if (i)
			{
				if (!short_string && i == segments.size() - 1)
				{
					stream << " and ";
				}
				else
				{
					stream << seperation;
				}
			}
			stream << segments[i];
		}

		if (parantheses.size() > 1)
		{
			stream << parantheses[1];
		}
		return stream.str();
	}

	std::string
	ql::time::string(std::string_view parantheses, std::string_view seperation, bool short_string, bool weeks, ql::size precision)
			const
	{
		return this->string_until_segment(ql::size_max, parantheses, seperation, short_string, weeks, precision);
	}

	std::string ql::time::string_until_hour(
			std::string_view parantheses,
			std::string_view seperation,
			bool short_string,
			bool weeks,
			ql::size precision
	) const
	{
		return this->string_until_segment(weeks ? 4u : 3u, parantheses, seperation, short_string, weeks, precision);
	}

	std::string ql::time::string_until_min(
			std::string_view parantheses,
			std::string_view seperation,
			bool short_string,
			bool weeks,
			ql::size precision
	) const
	{
		return this->string_until_segment(weeks ? 5u : 4u, parantheses, seperation, short_string, weeks, precision);
	}

	std::string ql::time::string_until_sec(
			std::string_view parantheses,
			std::string_view seperation,
			bool short_string,
			bool weeks,
			ql::size precision
	) const
	{
		return this->string_until_segment(weeks ? 6u : 5u, parantheses, seperation, short_string, weeks, precision);
	}

	std::string ql::time::string_until_ms(
			std::string_view parantheses,
			std::string_view seperation,
			bool short_string,
			bool weeks,
			ql::size precision
	) const
	{
		return this->string_until_segment(weeks ? 7u : 6u, parantheses, seperation, short_string, weeks, precision);
	}

	std::string ql::time::descriptive_string(ql::size precision, bool weeks, ql::size stop_at_segment) const
	{
		return this->string_until_segment(stop_at_segment, "", ", ", false, weeks, precision);
	}

	std::string ql::time::descriptive_string_no_and(ql::size precision, bool weeks, ql::size stop_at_segment) const
	{
		return this->string_until_segment(stop_at_segment, "", ", ", false, weeks, precision, false);
	}

	std::string ql::time::compact_string(ql::size precision, bool weeks, ql::size stop_at_segment) const
	{
		return this->string_until_segment(stop_at_segment, "[]", " : ", true, weeks, precision);
	}

	std::string ql::time::small_string(
			ql::size precision,
			bool weeks,
			bool short_string,
			std::string_view parantheses,
			std::string_view seperation
	) const
	{
		return this->string(parantheses, seperation, short_string, weeks, precision);
	}

	std::string ql::time::small_descriptive_string(ql::size precision, bool weeks) const
	{
		return this->descriptive_string(precision, weeks);
	}

	std::string ql::time::small_descriptive_string_no_and(ql::size precision, bool weeks) const
	{
		return this->descriptive_string_no_and(precision, weeks);
	}

	std::string ql::time::small_compact_string(ql::size precision, bool weeks) const
	{
		return this->compact_string(precision, weeks);
	}

	std::string ql::time::to_string() const
	{
		return this->string();
	}

	ql::f64 ql::time::frequency() const
	{
		auto x = ql::f64_cast(this->ns);
		return ql::time::nsecs_in_sec / x;
	}

	ql::u64 ql::time::nsecs() const
	{
		return this->ns;
	}

	ql::u64 ql::time::usecs() const
	{
		return this->ns / ql::time::nsecs_in_usec;
	}

	ql::u64 ql::time::msecs() const
	{
		return this->ns / ql::time::nsecs_in_msec;
	}

	ql::u64 ql::time::secs() const
	{
		return this->ns / ql::time::nsecs_in_sec;
	}

	ql::u64 ql::time::mins() const
	{
		return this->ns / ql::time::nsecs_in_min;
	}

	ql::u64 ql::time::hours() const
	{
		return this->ns / ql::time::nsecs_in_hour;
	}

	ql::u64 ql::time::days() const
	{
		return this->ns / ql::time::nsecs_in_day;
	}

	ql::u64 ql::time::weeks() const
	{
		return this->ns / ql::time::nsecs_in_week;
	}

	ql::u64 ql::time::years() const
	{
		return this->ns / ql::time::nsecs_in_year;
	}

	ql::u64 ql::time::nsecs_mod() const
	{
		return this->nsecs() % this->nsecs_in_usec;
	}

	ql::u64 ql::time::usecs_mod() const
	{
		return this->usecs() % this->usecs_in_msec;
	}

	ql::u64 ql::time::msecs_mod() const
	{
		return this->msecs() % this->msecs_in_sec;
	}

	ql::u64 ql::time::secs_mod() const
	{
		return this->secs() % this->secs_in_min;
	}

	ql::u64 ql::time::mins_mod() const
	{
		return this->mins() % this->mins_in_hour;
	}

	ql::u64 ql::time::hours_mod() const
	{
		return this->hours() % this->hours_in_day;
	}

	ql::u64 ql::time::days_mod() const
	{
		return this->days() % this->days_in_year;
	}

	ql::u64 ql::time::days_week_mod() const
	{
		return (this->days() % this->days_in_year) % this->days_in_week;
	}

	ql::u64 ql::time::weeks_mod() const
	{
		return (this->weeks() % this->weeks_in_year);
	}

	ql::u64 ql::time::years_mod() const
	{
		return this->years();
	}

	ql::f64 ql::time::nsecs_f() const
	{
		return ql::f64_cast(this->ns);
	}

	ql::f64 ql::time::usecs_f() const
	{
		return ql::f64_cast(this->ns) / ql::f64_cast(ql::time::nsecs_in_usec);
	}

	ql::f64 ql::time::msecs_f() const
	{
		return ql::f64_cast(this->ns) / ql::f64_cast(ql::time::nsecs_in_msec);
	}

	ql::f64 ql::time::secs_f() const
	{
		return ql::f64_cast(this->ns) / ql::f64_cast(ql::time::nsecs_in_sec);
	}

	ql::f64 ql::time::mins_f() const
	{
		return ql::f64_cast(this->ns) / ql::f64_cast(ql::time::nsecs_in_min);
	}

	ql::f64 ql::time::hours_f() const
	{
		return ql::f64_cast(this->ns) / ql::f64_cast(ql::time::nsecs_in_hour);
	}

	ql::f64 ql::time::days_f() const
	{
		return ql::f64_cast(this->ns) / ql::f64_cast(ql::time::nsecs_in_day);
	}

	ql::f64 ql::time::years_f() const
	{
		return ql::f64_cast(this->ns) / ql::f64_cast(ql::time::nsecs_in_year);
	}

	void ql::time::set(ql::u64 ns)
	{
		this->ns = ns;
	}

	ql::time::operator ql::u64() const
	{
		return this->ns;
	}

	void ql::clock::reset()
	{
		this->m_begin = ql::time::clock_time();
		this->m_running = true;
		this->m_pause_sum = ql::u64{};
	}

	void ql::clock::pause()
	{
		if (this->is_running())
		{
			this->measure();
		}
		this->m_running = false;
		this->m_pause = ql::time::clock_time();
	}

	void ql::clock::reset_pause()
	{
		if (this->is_running())
		{
			this->measure();
		}
		this->m_begin = ql::time::clock_time();
		this->m_running = false;
		this->m_pause = ql::time::clock_time();
		this->m_pause_sum = ql::u64{};
	}

	ql::time ql::clock::elapsed() const
	{
		if (this->is_running())
		{
			this->measure();
		}
		return this->m_end - (this->m_begin + this->m_pause_sum);
	}

	std::string ql::clock::elapsed_str() const
	{
		return this->elapsed().string();
	}

	ql::f64 ql::clock::elapsed_f() const
	{
		return this->elapsed().secs_f();
	}

	ql::time ql::clock::elapsed_reset()
	{
		auto result = this->elapsed();
		this->reset();
		return result;
	}

	std::string ql::clock::elapsed_str_reset()
	{
		auto result = this->elapsed_str();
		this->reset();
		return result;
	}

	ql::f64 ql::clock::elapsed_f_reset()
	{
		auto result = this->elapsed_f();
		this->reset();
		return result;
	}

	void ql::clock::add(ql::f64 seconds)
	{
		this->m_begin += ql::u64_cast(seconds * ql::time::nsecs_in_sec);
	}

	void ql::clock::add(ql::time time)
	{
		this->m_begin += time;
	}

	void ql::clock::subtract(ql::f64 seconds)
	{
		this->m_begin -= ql::u64_cast(seconds * ql::time::nsecs_in_sec);
	}

	void ql::clock::subtract(ql::time time)
	{
		this->m_begin -= time;
	}

	bool ql::clock::has_elapsed(ql::f64 seconds) const
	{
		return this->elapsed_f() > seconds;
	}

	bool ql::clock::has_elapsed(ql::time duration) const
	{
		return this->elapsed() > duration;
	}

	bool ql::clock::has_elapsed_reset(ql::f64 seconds)
	{
		auto result = this->has_elapsed(seconds);
		if (result)
		{
			this->reset();
		}
		return result;
	}

	bool ql::clock::has_elapsed_reset(ql::time duration)
	{
		auto result = this->has_elapsed(duration);
		if (result)
		{
			this->reset();
		}
		return result;
	}

	void ql::clock::resume()
	{
		if (this->is_running())
		{
			return;
		}
		this->m_running = true;
		this->m_pause_sum += (ql::time::clock_time() - this->m_pause);
	}

	bool ql::clock::is_running() const
	{
		return this->m_running;
	}

	bool ql::clock::is_paused() const
	{
		return !this->m_running;
	}

	void ql::clock::measure() const
	{
		if (this->is_running())
		{
			this->m_end = ql::time::clock_time();
		}
	}

	void ql::clock::init(bool running)
	{
		this->m_begin = ql::time::clock_time();
		this->m_end = this->m_begin;
		this->m_pause_sum = ql::u64{};
		this->m_running = running;
		if (this->is_paused())
		{
			this->m_pause = this->m_begin;
		}
	}

	std::string ql::clock::to_string() const
	{
		return this->elapsed().to_string();
	}

	void ql::small_clock::reset()
	{
		this->m_begin = ql::time::clock_time();
	}

	ql::time ql::small_clock::elapsed() const
	{
		auto time = ql::time::clock_time();
		return time - this->m_begin;
	}

	std::string ql::small_clock::elapsed_str() const
	{
		return this->elapsed().string();
	}

	ql::f64 ql::small_clock::elapsed_f() const
	{
		return this->elapsed().secs_f();
	}

	ql::time ql::small_clock::elapsed_reset()
	{
		auto result = this->elapsed();
		this->reset();
		return result;
	}

	std::string ql::small_clock::elapsed_str_reset()
	{
		auto result = this->elapsed_str();
		this->reset();
		return result;
	}

	ql::f64 ql::small_clock::elapsed_f_reset()
	{
		auto result = this->elapsed_f();
		this->reset();
		return result;
	}

	void ql::small_clock::add(ql::f64 seconds)
	{
		this->m_begin += ql::u64_cast(seconds * ql::time::nsecs_in_sec);
	}

	void ql::small_clock::add(ql::time time)
	{
		this->m_begin += time;
	}

	void ql::small_clock::subtract(ql::f64 seconds)
	{
		this->m_begin -= ql::u64_cast(seconds * ql::time::nsecs_in_sec);
	}

	void ql::small_clock::subtract(ql::time time)
	{
		this->m_begin -= time;
	}

	bool ql::small_clock::has_elapsed(ql::f64 seconds) const
	{
		return this->elapsed_f() > seconds;
	}

	bool ql::small_clock::has_elapsed(ql::time duration) const
	{
		return this->elapsed() > duration;
	}

	bool ql::small_clock::has_elapsed_reset(ql::f64 seconds)
	{
		auto result = this->has_elapsed(seconds);
		if (result)
		{
			this->reset();
		}
		return result;
	}

	bool ql::small_clock::has_elapsed_reset(ql::time duration)
	{
		auto result = this->has_elapsed(duration);
		if (result)
		{
			this->reset();
		}
		return result;
	}

	std::ostream& operator<<(std::ostream& os, const ql::clock& clock)
	{
		return (os << clock.elapsed().string());
	}

	std::ostream& operator<<(std::ostream& os, const ql::halted_clock& clock)
	{
		return (os << clock.elapsed().string());
	}

	void wait(ql::time duration)
	{
		std::this_thread::sleep_for(std::chrono::nanoseconds(duration.nsecs()));
	}

	void wait(double seconds)
	{
		if (seconds <= 0)
			return;
		ql::wait(ql::secs(seconds));
	}

	void wait_while(double seconds)
	{
		if (seconds <= 0)
			return;
		auto n = ql::secs(seconds);
		ql::clock clock;
		while (clock.elapsed() < n)
		{
		}
	}

	std::chrono::system_clock::time_point get_current_local_time()
	{
		auto now = std::chrono::system_clock::now();
		auto now_time_t = std::chrono::system_clock::to_time_t(now);

#pragma warning(push)
#pragma warning(disable : 4996)
		std::tm local_tm = *std::localtime(&now_time_t);
		std::tm utc_tm = *std::gmtime(&now_time_t);
#pragma warning(pop)

		auto local_time_as_timepoint = std::chrono::system_clock::from_time_t(mktime(&local_tm));

		auto utc_time_as_timepoint = std::chrono::system_clock::from_time_t(mktime(&utc_tm));

		auto offset = local_time_as_timepoint - utc_time_as_timepoint;

		// Adjust for DST
		if (local_tm.tm_isdst > 0)
		{
			offset += std::chrono::hours(1);
		}
		else if (local_tm.tm_isdst < 0)
		{
			// DST information is unavailable
			// You can decide how to handle this case
		}
		return (now + offset);
	}

	std::chrono::local_time<std::chrono::system_clock::duration> get_current_zoned_time()
	{
		auto now = std::chrono::system_clock::now();
		auto x = std::chrono::zoned_time(std::chrono::current_zone(), now);
		return x.get_local_time();
	}

	std::chrono::system_clock::time_point get_current_system_time()
	{
		return std::chrono::system_clock::now();
	}

	std::chrono::utc_clock::time_point get_current_utc_time()
	{
		return std::chrono::utc_clock::now();
	}

	std::string get_current_time_string(const std::string_view& format)
	{
		std::time_t rawtime{};
		std::tm* timeinfo = nullptr;

		constexpr auto buffer_size = 80;
		std::array<char, buffer_size> buffer;

		std::time(&rawtime);

#pragma warning(push)
#pragma warning(disable : 4996)
		timeinfo = std::localtime(&rawtime);
#pragma warning(pop)

		std::strftime(buffer.data(), buffer_size, format.data(), timeinfo);
		return ql::to_string(buffer.data());
	}

	std::optional<std::chrono::system_clock::time_point> utc_data_ymdhm_to_utc_timepoint(std::string date, std::string format)
	{
		std::istringstream stream{date};
		std::chrono::system_clock::time_point result;
		if (!std::chrono::from_stream(stream, format.c_str(), result))
		{
			// throw ql::exception("utc_data_ymdhm_to_utc_timepoint error : cannot parse date ", date);
			return std::nullopt;
		}
		return result;
	}

	ql::time get_remaining_time(ql::f64 progress, ql::time elapsed)
	{
		ql::time f = 0;
		if (progress)
		{
			f = ql::u64_cast(elapsed.nsecs() / progress);
		}
		return ql::u64_cast(f.nsecs() * (1 - progress));
	}

	ql::time get_remaining_time(ql::f64 progress, ql::clock timer)
	{
		return ql::get_remaining_time(progress, timer.elapsed());
	}

	std::string get_current_time_string_ms()
	{
		auto current_time = std::chrono::system_clock::now();

		auto transformed = current_time.time_since_epoch().count() / 10000;

		auto millis = transformed % 1000;

		auto str = get_current_time_string();
		return ql::to_string(str, "-", ql::string_prepended(millis, '0', 3));
	}

	std::string get_current_time_string_ymd_hms()
	{
		return ql::get_current_time_string("%Y-%m-%d %H:%M:%S");
	}

	std::string get_current_time_string_ymd_hmsms()
	{
		auto value = ql::get_current_time_string("%Y-%m-%d %H:%M:%S");

		auto current_time = std::chrono::system_clock::now();

		auto transformed = current_time.time_since_epoch().count() / 10000;

		auto millis = transformed % 1000;

		return ql::to_string(value, ":", ql::string_prepended(millis, '0', 3));
	}

	std::string ql::get_current_time_string_ymd_hmsms_compact()
	{
		auto value = ql::get_current_time_string("%Y%m%d% H%M%S");

		auto current_time = std::chrono::system_clock::now();

		auto transformed = current_time.time_since_epoch().count() / 10000;

		auto millis = transformed % 1000;

		return ql::to_string(value, ql::string_prepended(millis, '0', 3));
	}

	std::string ql::get_current_time_string_ymdhmsms_compact()
	{
		auto value = ql::get_current_time_string("%Y%m%d%H%M%S");

		auto current_time = std::chrono::system_clock::now();

		auto transformed = current_time.time_since_epoch().count() / 10000;

		auto millis = transformed % 1000;

		return ql::to_string(value, ql::string_prepended(millis, '0', 3));
	}

	std::unordered_map<std::string, std::unordered_map<std::string, ql::halted_clock>> ql::detail::sub_benchmark_clocks;
	std::unordered_map<std::string, ql::halted_clock> ql::detail::benchmark_clocks;
	std::string ql::detail::last_benchmark_name;
	std::string ql::detail::last_sub_benchmark_name;

	ql::clock ql::detail::signal_clock;
	ql::u64 ql::detail::signal_count;

	void begin_benchmark_end_previous(const std::string& name)
	{
		ql::end_benchmark();
		ql::begin_benchmark(name);
	}

	void begin_benchmark_end_previous(const std::string& sub, const std::string& name)
	{
		ql::end_benchmark();
		ql::begin_benchmark(sub, name);
	}

	ql::halted_clock ql::get_benchmark(const std::string& name)
	{
		return ql::detail::benchmark_clocks[name];
	}

	void begin_benchmark(const std::string& name)
	{
		ql::detail::last_benchmark_name = name;
		ql::detail::benchmark_clocks[name].resume();
	}

	void begin_benchmark(const std::string& sub, const std::string& name)
	{
		ql::detail::last_benchmark_name = name;
		ql::detail::last_sub_benchmark_name = sub;
		ql::detail::sub_benchmark_clocks[sub][name].resume();
	}

	void end_benchmark(const std::string& name)
	{
		ql::detail::benchmark_clocks[name].pause();
	}

	void end_benchmark()
	{
		if (!ql::detail::last_sub_benchmark_name.empty())
		{
			ql::detail::sub_benchmark_clocks[ql::detail::last_sub_benchmark_name][ql::detail::last_benchmark_name].pause();
			ql::detail::last_sub_benchmark_name.clear();
			ql::detail::last_benchmark_name.clear();
		}
		else if (!ql::detail::last_benchmark_name.empty())
		{
			ql::detail::benchmark_clocks[ql::detail::last_benchmark_name].pause();
			ql::detail::last_benchmark_name.clear();
		}
	}

	void begin_benchmark_segments()
	{
		ql::detail::benchmark_clocks.clear();
	}

	void clear_benchmark()
	{
		ql::detail::benchmark_clocks.clear();
	}

	void reset_benchmark()
	{
		ql::clear_benchmark();
	}

	void print_benchmark()
	{
		ql::time sum = 0;

		ql::size length_max = 0u;
		std::vector<std::pair<std::string, double>> sorted;
		for (auto& i : ql::detail::benchmark_clocks)
		{
			length_max = ql::max(length_max, i.first.length());
			sum += i.second.elapsed();
			sorted.emplace_back(std::make_pair(i.first, i.second.elapsed_f()));
		}
		std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

		for (auto i : ql::detail::benchmark_clocks)
		{
			if (i.first == sorted.front().first && sorted.size() >= 2u)
			{
				ql::print(ql::bright_green);
			}
			else if (i.first == sorted.back().first && sorted.size() >= 3u)
			{
				ql::print(ql::bright_red);
			}
			auto f = i.second.elapsed().nsecs_f() / sum.nsecs_f();

			auto precision = ql::size{3};
			auto percentage_string = ql::string_percentage_precision(f, precision);
			percentage_string = ql::string_prepended(percentage_string, ' ', precision + 4);
			ql::print(ql::to_string(
					ql::string_right_spaced(i.first, length_max + 1), " - ", ql::string_left_spaced(percentage_string, 10),
					" time usage : ", i.second.elapsed().string()
			));

			if (i.first != sorted.back().first && sorted.size() >= 2u)
			{
				auto p = ql::size_cast(sorted.back().second / i.second.elapsed_f());
				ql::print(" [ ", ql::string_precision(3, p), "x ]");
			}
			ql::println();
		}

		for (auto& sub : ql::detail::sub_benchmark_clocks)
		{
			ql::println();
			sum = 0;
			length_max = 0u;
			sorted.clear();
			for (auto& i : sub.second)
			{
				length_max = ql::max(length_max, i.first.length());
				sum += i.second.elapsed();
				sorted.emplace_back(std::make_pair(i.first, i.second.elapsed_f()));
			}
			std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

			for (auto& i : sub.second)
			{
				if (i.first == sorted.front().first && sorted.size() >= 2u)
				{
					ql::print(ql::bright_green);
				}
				else if (i.first == sorted.back().first && sorted.size() >= 3u)
				{
					ql::print(ql::bright_red);
				}

				auto f = i.second.elapsed().nsecs_f() / sum.nsecs_f();
				if (i.first != sorted.back().first && sorted.size() >= 2u)
				{
					auto p = ql::size_cast(sorted.back().second / i.second.elapsed_f());
					ql::println(ql::to_string(
							sub.first, ": ", ql::string_left_spaced(i.first, length_max + 1), " - ",
							ql::string_left_spaced(ql::string_precision(7, ql::size_cast(f * 100)), 14),
							"% time usage : ", i.second.elapsed().string(), " [ ", ql::string_precision(3, p), "x ]"
					));
				}
				else
				{
					ql::println(ql::to_string(
							sub.first, ": ", ql::string_left_spaced(i.first, length_max + 1), " - ",
							ql::string_left_spaced(ql::string_precision(7, ql::size_cast(f * 100)), 14),
							"% time usage : ", i.second.elapsed().string()
					));
				}
			}
		}
	}

	void print_benchmark(const std::string& name)
	{
		ql::println(name, " took ", ql::detail::benchmark_clocks[name].elapsed_reset().string());
	}

	void reset_time_signal()
	{
		ql::detail::signal_clock.reset();
	}

	bool get_time_signal(double seconds)
	{
		return (ql::detail::signal_clock.has_elapsed_reset(seconds));
	}

	bool get_time_signal(ql::time time)
	{
		return (ql::detail::signal_clock.has_elapsed_reset(time));
	}

	void reset_count_signal()
	{
		ql::detail::signal_count = ql::u64{};
	}

	bool get_count_signal(ql::u64 when)
	{
		++ql::detail::signal_count;
		if (ql::detail::signal_count >= when)
		{
			ql::detail::signal_count = ql::u64{};
			return true;
		}
		return false;
	}

	void ql::animation::internal_reset()
	{
		this->just_finish = false;
		this->just_finish_reverse = false;
		this->just_finish_no_reverse = false;
		this->internal_change_flag = false;
	}

	void ql::animation::reset()
	{
		this->progress = 0.0;
		this->running = false;
		this->reversed = false;
		this->internal_reset();
	}

	void ql::animation::start()
	{
		this->running = true;
	}

	void ql::animation::stop()
	{
		this->running = true;
	}

	void ql::animation::reset_and_start()
	{
		this->progress = 0.0;
		this->running = true;
		this->reversed = false;
		this->internal_reset();
	}

	void ql::animation::reset_and_start_reverse()
	{
		this->progress = 1.0;
		this->running = true;
		this->reversed = true;
		this->internal_reset();
	}

	void ql::animation::set_duration(ql::f64 duration)
	{
		this->duration = duration;
	}

	void ql::animation::update(ql::f64 frame_time)
	{
		if (this->just_finish && !this->internal_change_flag)
		{
			this->running = false;
		}
		this->internal_change_flag = false;
		this->just_finish = false;
		this->just_finish_reverse = false;
		this->just_finish_no_reverse = false;

		if (this->running)
		{
			auto before = this->progress;

			auto f = frame_time / this->duration;
			if (this->reversed)
			{
				this->progress -= f;
			}
			else
			{
				this->progress += f;
			}

			this->progress = ql::clamp(this->progress);
			if (this->progress == 1.0 && before < 1.0)
			{
				this->just_finish = this->just_finish_no_reverse = true;
			}
			else if (this->progress == 0.0 && before > 0.0)
			{
				this->just_finish = this->just_finish_reverse = true;
			}
		}

		this->progress_change_flag = (this->progress != this->progress_before);
		this->progress_before = this->progress;
	}
#ifdef QL_SFML
	void ql::animation::update(const ql::event_info& event)
	{
		this->update(event.frame_time_f());
	}
#endif
	void ql::animation::go_forwards()
	{
		this->start();
		this->reversed = false;
		this->internal_change_flag = true;
	}

	void ql::animation::go_backwards()
	{
		this->start();
		this->reversed = true;
		this->internal_change_flag = true;
	}

	bool ql::animation::is_running() const
	{
		return this->running;
	}

	bool ql::animation::is_reversed() const
	{
		return this->reversed;
	}

	bool ql::animation::changed() const
	{
		return this->progress_change_flag;
	}

	bool ql::animation::just_finished() const
	{
		return this->just_finish;
	}

	bool ql::animation::just_finished_reverse() const
	{
		return this->just_finish_reverse;
	}

	bool ql::animation::just_finished_no_reverse() const
	{
		return this->just_finish_no_reverse;
	}

	bool ql::animation::has_progress() const
	{
		return ql::bool_cast(this->progress);
	}

	void ql::animation::set_progress(ql::f64 progress, bool backwards)
	{
		this->progress = ql::clamp(progress);
		if (backwards)
		{
			this->go_backwards();
		}
		else
		{
			this->go_forwards();
		}
	}

	ql::f64 ql::animation::get_progress() const
	{
		return this->progress;
	}

	ql::f64 ql::animation::get_curve_progress(ql::f64 curve) const
	{
		return ql::curve_slope(this->progress, curve);
	}

	ql::f64 ql::animation::get_double_curve_progress(ql::f64 curve) const
	{
		return ql::double_curve_slope(this->progress, curve);
	}

	void ql::timed_task::update()
	{
		auto done = this->is_done();
		this->just_finish = !this->done_before && done;
		if (this->just_finish)
		{
			this->function();
		}
		this->done_before = done;
	}

	bool ql::timed_task::is_done() const
	{
		return this->clock.elapsed() > this->wait_duration;
	}

	bool ql::timed_task::is_running() const
	{
		return !this->is_done();
	}

	bool ql::timed_task::just_finished() const
	{
		return this->just_finish;
	}

	void ql::timed_task::set_wait_duration(ql::time time)
	{
		this->wait_duration = time;
	}

	void ql::timed_task::set_wait_duration(ql::f64 seconds)
	{
		this->wait_duration = ql::secs(seconds);
	}

	ql::f64 ql::timed_task::get_wait_progress() const
	{
		auto p = this->clock.elapsed_f();
		return p / this->wait_duration.secs_f();
	}

	timed_task_manager ql::detail::tasks;

	void ql::timed_task_manager::clear()
	{
		this->tasks.clear();
	}

	void ql::timed_task_manager::cleanup()
	{
		std::vector<timed_task> temp;
		temp.reserve(this->tasks.size());
		for (auto& i : this->tasks)
		{
			if (i.is_done())
			{
				this->finished_tasks.insert(i.name);
			}
			else
			{
				temp.emplace_back(i);
			}
		}
		this->tasks = temp;
	}

	bool ql::timed_task_manager::is_task_finished(const std::string& name)
	{
		return this->finished_tasks.find(name) != this->finished_tasks.cend();
	}

	bool ql::timed_task_manager::is_task_running(const std::string& name)
	{
		for (auto& i : this->tasks)
		{
			if (i.name == name)
			{
				return i.is_running();
			}
		}
		return false;
	}

	void ql::timed_task_manager::add_timed_task(ql::time time, std::function<void(void)> function, const std::string& name)
	{
		this->tasks.push_back(ql::timed_task(time, function, name));
	}

	void ql::timed_task_manager::add_timed_task(ql::f64 time, std::function<void(void)> function, const std::string& name)
	{
		this->tasks.push_back(ql::timed_task(time, function, name));
	}

	void ql::timed_task_manager::update()
	{
		bool any_done = false;
		for (auto& i : this->tasks)
		{
			i.update();
			if (i.is_done())
			{
				any_done = true;
			}
		}
		this->finished_tasks.clear();
		if (any_done)
		{
			this->cleanup();
		}
	}

	void start_timed_task(ql::time time, std::function<void(void)> function)
	{
		ql::detail::tasks.add_timed_task(time, function);
	}

	void start_timed_task(ql::time time, const std::string& name, std::function<void(void)> function)
	{
		ql::detail::tasks.add_timed_task(time, function, name);
	}

	void start_timed_task(ql::f64 time, std::function<void(void)> function)
	{
		ql::detail::tasks.add_timed_task(time, function);
	}

	void start_timed_task(ql::f64 time, const std::string& name, std::function<void(void)> function)
	{
		ql::detail::tasks.add_timed_task(time, function, name);
	}

	bool timed_task_finished(const std::string& name)
	{
		return ql::detail::tasks.is_task_finished(name);
	}

	bool timed_task_running(const std::string& name)
	{
		return ql::detail::tasks.is_task_running(name);
	}

	void clear_timed_tasks()
	{
		ql::detail::tasks.clear();
	}

	void update_tasks()
	{
		ql::detail::tasks.update();
	}
}	 // namespace ql