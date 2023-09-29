#pragma once

#include "imgui_internal.h"
#include "imgui.h"
#include <chrono>

namespace ImGuiExtensions
{
    struct DatePickerOptions
    {

    };

    enum class DatePickerLevel
    {
        Days,
        Months,
        Years
    };

    bool DatePicker(char const* id, DatePickerLevel& level, std::chrono::year_month_day& t) noexcept;
}