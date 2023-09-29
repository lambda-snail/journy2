#include <string>

#include "ui/datepicker/datepicker.h"

namespace ImGuiExtensions {

    static char const* MonthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August",
                                       "September", "October", "November", "December"};
    static char const* MonthNamesShort[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Augu",
                                       "Sep", "Oct", "Nov", "Dec"};
    static char const* DayNames[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};

    void SelectDay(std::chrono::year_month_day& date, std::chrono::year_month_day const &lastDayOfMonth,
                   std::chrono::weekday const &weekdayOfFirstDay, std::chrono::weekday const &weekdayOfLastDay) noexcept;
    void SelectMonth(std::chrono::year_month_day &date, DatePickerLevel &level);
    void SelectYear(std::chrono::year_month_day &date, DatePickerLevel &level);

    static const int DaysPerWeek{ 7 };
    static const int MonthsPerYear{ 12 };

/**
 * Index into the abbreviations array from a c-based index (Sunday is index 0).
 */
    inline const char *getWeekdayAbbreviation(std::chrono::weekday const &wd) {
        return DayNames[wd.iso_encoding() - 1];
    }

    bool DatePicker(const char *id, DatePickerLevel &level, std::chrono::year_month_day &date) noexcept {
        using namespace std::chrono;

        ImGui::PushID(id);
        ImGui::BeginGroup();

        if(ImGui::Button(std::to_string(static_cast<int>(date.year())).c_str()))
        {
            level = DatePickerLevel::Years;
        }

        // Display year related controls when selecting days
        if(level == DatePickerLevel::Months)
        {
            ImGui::SameLine();
            if (ImGui::ArrowButton("Up", ImGuiDir_Up)) {
                date -= years{1};
            }

            ImGui::SameLine();
            if (ImGui::ArrowButton("Down", ImGuiDir_Down)) {
                date += years{1};
            }
        }

        // Display month related controls when selecting days
        if(level == DatePickerLevel::Days)
        {
            ImGui::SameLine();
            if (ImGui::Button(
                    MonthNames[static_cast<unsigned int>(date.month()) - 1])) // chrono::month index starts at 1{
            {
                level = DatePickerLevel::Months;
            }

            ImGui::SameLine();
            if (ImGui::ArrowButton("Up", ImGuiDir_Up)) {
                date -= months{1};
            }

            ImGui::SameLine();
            if (ImGui::ArrowButton("Down", ImGuiDir_Down)) {
                date += months{1};
            }
        }

        ImGui::Separator();

        auto lastDayOfMonth = year_month_day{date.year() / date.month() / last};
        weekday weekdayOfFirstDay = sys_days{year_month_day{date.year() / date.month() / 1}};
        weekday weekdayOfLastDay = sys_days{lastDayOfMonth};

        switch(level)
        {
            case DatePickerLevel::Days:
                SelectDay(date, lastDayOfMonth, weekdayOfFirstDay, weekdayOfLastDay);
                break;
            case DatePickerLevel::Months:
                SelectMonth(date, level);
                break;
            default:
                SelectYear(date, level);
                break;
        }


        ImGui::EndGroup();
        ImGui::PopID();

        return false;
    }

    void SelectDay(std::chrono::year_month_day &date, std::chrono::year_month_day const &lastDayOfMonth,
                   std::chrono::weekday const &weekdayOfFirstDay, std::chrono::weekday const &weekdayOfLastDay) noexcept
    {
        if (ImGui::BeginTable("Days", 7)) {
            for (auto const *day: DayNames) {
                ImGui::TableSetupColumn(day);
            }

            ImGui::TableHeadersRow();

            // Fill in days that come before the first day of active month
            for (int i{0}; i < weekdayOfFirstDay.iso_encoding() - 1; ++i)
            {
                if (ImGui::TableNextColumn()) {
                    ImGui::Text("%s", "x");
                }
            }

            for (int i{1}; i <= static_cast<unsigned int>(lastDayOfMonth.day()); ++i)
            {
                if (ImGui::TableNextColumn()) {
                    ImGui::Text("%i", i);
                }
            }

            // Fill the remaining days of the calendar after the last day - if any
            for (auto i{DaysPerWeek}; i > static_cast<unsigned int>(weekdayOfLastDay.iso_encoding()); --i)
            {
                if (ImGui::TableNextColumn()) {
                    ImGui::Text("%s", "x");
                }
            }

            ImGui::EndTable();
        }
    }

    void SelectMonth(std::chrono::year_month_day &date, DatePickerLevel &level)
    {
        if (ImGui::BeginTable("Months", 3))
        {
            for(int i { 0 }; i < MonthsPerYear; ++i)
            {
                if(ImGui::TableNextColumn())
                {
                    if(ImGui::Button(MonthNamesShort[i]))
                    {
                        date = {
                            date.year(),
                            std::chrono::month{ static_cast<unsigned int>(i+1) },
                            date.day() };

                        level = DatePickerLevel::Days;
                        break;
                    }
                }
            }

            ImGui::EndTable();
        }
    }

    void SelectYear(std::chrono::year_month_day& date, DatePickerLevel& level) {
        if (ImGui::BeginTable("Years", 5))
        {
            int selectedYear = static_cast<int>(date.year());
            for(int i { selectedYear - 7 }; i <= selectedYear + 7; ++i)
            {
                if(ImGui::TableNextColumn())
                {
                    if(ImGui::Button(std::to_string(i).c_str()))
                    {
                        date = {
                                std::chrono::year{ i },
                                date.month(),
                                date.day() };

                        level = DatePickerLevel::Months;
                        break;
                    }
                }
            }

            ImGui::EndTable();
        }
    }
}