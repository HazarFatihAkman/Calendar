#include "../include/date.h"

static const char *day_names[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
static const char *month_names[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
static const Date start_date = { .day = 1, .month = 1, .year = 2024, .day_name = "Monday" };
static const int day_counts_fourth_year[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static const int day_counts[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int get_day_count(int month, int year) {
    int smaller_than_start_year = year < start_date.year;
    int excess_year = smaller_than_start_year
        ? start_date.year - 4
        : start_date.year;

    if (smaller_than_start_year) {
        for (int i = 0; i < start_date.year - year; i++) {
            if (excess_year == year - i) {
                excess_year -= 4;
            }
        }
    }
    else {
        for (int i = 0; i < year - start_date.year; i++) {
            if (excess_year == year + i) {
                excess_year += 4;
            }
        }
    }
    return excess_year == year ? day_counts_fourth_year[month - 1] : day_counts[month - 1];
}

static char* day_name_index(Date *date) {
    int month_diff = date->month - start_date.month;

    int smaller_than_start_year = date->year < start_date.year;
    int index = smaller_than_start_year ? 7 : 0;

    int year_diff = smaller_than_start_year
        ? start_date.year - date->year
        : date->year - start_date.year;

    int excess_year = smaller_than_start_year
        ? start_date.year - 4
        : start_date.year;

    if (smaller_than_start_year) {
        for (int i = 1; i < year_diff; i++) {
            if (excess_year == start_date.year - i) {
                index -= 2;
                excess_year -= 4;
            }
            else {
                --index;
            }

            if (index < 0) {
                index += 7;
            }
        }
    }
    else {
        for (int i = 0; i <= year_diff; i++) {
            if (excess_year == start_date.year + i) {
                index = index + 2;
                excess_year += 4;
            }
            else {
                ++index;
            }

            if (index > 7) {
                index -= 7;
            }
        }
    }
    if (date->day == 1 && date->month == 1) {
        return day_names[index - 1];
    }
    else {
        for (int i = 1; i <= month_diff; i++) {
            int days = get_day_count(i, date->year);
            int week_count = days % 7;

            index += week_count;

            if (index < 0) {
                index += 7;
            }
            else if (index > 7) {
                index -= 7;
            }
            
        }
        if (date->day == 1) {
            return day_names[index - 1];
        }
        else {
            for (int i = 1; i < date->day; i++) {
                ++index;
                if (index == 8) {
                    index = 1;
                }
            }
            return day_names[index - 1];
        }
    }
}

Date* create_day(int day, int month, int year) {
    Date* r = (Date*)malloc(sizeof(Date));
    r->day = day;
    r->month = month;
    r->year = year;
    r->day_name = day_name_index(r);
    r->month_name = month_names[r->month - 1];
    return r;
}

Date** create_month(int month, int year) {
    int day_count = get_day_count(month, year);
    Date **days = (Date**)malloc(day_count * sizeof(Date));
    int day = 1;

    for (int i = 0; i < day_count; i++) {
        days[i] = create_day(day, month, year);
        day++;
    }

    return days;
}

Date*** create_year(int year) {
    Date ***months = (Date***)malloc(12 * sizeof(Date));

    for (int i = 1; i <= 12; i++) {
        months[i - 1] = create_month(i, year);
    }

    return months;
}

int validate_date(Date date) {
    if (date.day == 0 || date.day > DAY_MAX || date.day <= get_day_count(date.month, date.year)) {
        printf(INVALID, "day", "0 or higher than MAX");
        return 0;
    }

    if (date.month == 0 || date.month > MONTH_MAX) {
        printf(INVALID, "month", "0 or higher than MAX");
        return 0;
    }

    if (date.year == 0) {
        printf(INVALID, "year", "should not be 0");
        return 0;
    }
}
