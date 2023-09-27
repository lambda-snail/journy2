#pragma once

#include "imgui_internal.h"
#include "imgui.h"
#include <chrono>

namespace ImGuiExtensions
{
    enum class DatePickerLevel
    {
        Days,
        Months,
        Years
    };

    bool DatePicker(const char* id, DatePickerLevel& level, std::chrono::year_month_day& t) noexcept;
}