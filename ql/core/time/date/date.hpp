#pragma once

#include <ql/core/definition/definition.hpp>

namespace ql
{
	enum class week_days : ql::i32
	{
		monday = 1,
		tuesday = 2,
		wednesday = 3,
		thursday = 4,
		friday = 5,
		saturday = 6,
		sunday = 7,
	};

	struct date_ms
	{
		ql::u16 years = 0;
		ql::u8 months = 0;
		ql::u8 days = 0;
		ql::u8 hours = 0;
		ql::u8 minutes = 0;
		ql::u8 seconds = 0;
		ql::u16 milliseconds = 0;

		date_ms() {

		}

		QL_SOURCE void set(std::string string);
		QL_SOURCE std::string string() const;
	};

	//date_ms get_current_time();

	struct year_month_day
	{
		ql::u16 year = 0;
		ql::u8 month = 0;
		ql::u8 day = 0;

		year_month_day() {

		}
		year_month_day(std::string_view str) {
			*this = str;
		}


		QL_SOURCE week_days get_week_day() const;

		QL_SOURCE std::string_view get_week_day_string() const;
		QL_SOURCE bool is_monday() const;
		QL_SOURCE bool is_tuesday() const;
		QL_SOURCE bool is_wednesday() const;
		QL_SOURCE bool is_thursday() const;
		QL_SOURCE bool is_friday() const;
		QL_SOURCE bool is_saturday() const;
		QL_SOURCE bool is_sunday() const;

		QL_SOURCE year_month_day& operator=(std::string_view date);
		QL_SOURCE bool operator==(const year_month_day& other) const;
		QL_SOURCE bool operator>(const year_month_day& other) const;
		QL_SOURCE bool operator<=(const year_month_day& other) const;
		QL_SOURCE bool operator<(const year_month_day& other) const;
		QL_SOURCE bool operator>=(const year_month_day& other) const;

		QL_SOURCE ql::size days() const;
		QL_SOURCE std::string string()const;
	};

	struct hour_minutes {
		ql::u8 hour = 0;
		ql::u8 minute = 0;

		hour_minutes() {

		}
		hour_minutes(std::string_view str) {
			*this = str;
		}
		QL_SOURCE double days() const;
		QL_SOURCE ql::size minutes() const;
		QL_SOURCE hour_minutes& operator=(std::string_view date);
		QL_SOURCE bool operator==(const hour_minutes& other) const;
		QL_SOURCE bool operator>(const hour_minutes& other) const;
		QL_SOURCE bool operator<=(const hour_minutes& other) const;
		QL_SOURCE bool operator<(const hour_minutes& other) const;
		QL_SOURCE bool operator>=(const hour_minutes& other) const;
		QL_SOURCE std::string string()const;
	};

	struct date {
		year_month_day ymd;
		hour_minutes hm;
		date() {

		}
		date(const std::string_view& ymd, const std::string_view& hm) : ymd(ymd), hm(hm) {

		}
		QL_SOURCE void set(const date_ms& date);
		QL_SOURCE date& operator=(const date_ms& date);
		QL_SOURCE date& operator=(const date& other);
		QL_SOURCE double days() const;

		QL_SOURCE std::string string() const;
	};
}