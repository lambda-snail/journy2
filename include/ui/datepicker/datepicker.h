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

    /**
     * Displays a date picker widget that allows for choosing a date. The date picker is must be embedded in a window or
     * child widget, or in a modal. Returns true when the selection is done.
     * @param id The id of the widget.
     * @param level The selection level - days, months or years. This is managed by the date picker but can also be used
     *  to programmatically change the current stage of selection.
     * @param t If DatePicker returns true, this will be set to the selected date. If DatePicker returns false this will
     *  contain an intermediate stage of selection.
     * @return true iff the selection is complete.
     * @see OpenDatePickerModal
     */
    bool DatePicker(char const* id, DatePickerLevel& level, std::chrono::year_month_day& t) noexcept;

    /**
     * Displays a date picker in a modal window with the given id. The function returns true when the selection is
     * complete.
     * @param id The id of the widget.
     * @param t If OpenDatePickerModal returns true, this will be set to the selected date. If OpenDatePickerModal
     *  returns false this will contain an intermediate stage of selection.
     * @return true iff the selection is complete.
     */
    bool OpenDatePickerModal(char const* id, std::chrono::year_month_day& t) noexcept;
}