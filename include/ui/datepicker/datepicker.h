#pragma once

#include "imgui_internal.h"
#include "imgui.h"
#include <chrono>



static inline bool IsLeapYear(int year) {
    return  year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

// Returns the number of days in a month, accounting for Feb. leap years. #month is zero indexed.
static inline int GetDaysInMonth(int year, int month) {
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return  days[month] + (int)(month == 1 && IsLeapYear(year));
}

bool DatePicker(const char* id, int* level, std::chrono::year_month_day* t);