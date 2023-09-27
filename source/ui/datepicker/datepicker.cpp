#include <string>

#include "ui/datepicker/datepicker.h"

namespace ImGuiExtensions {

    static const char *MonthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August",
                                       "September", "October", "November", "December"};
    static const char *DayNames[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};

    void SelectDay(std::chrono::year_month_day const &lastDayOfMonth, std::chrono::weekday const &weekdayOfFirstDay,
                   std::chrono::weekday const &weekdayOfLastDay) noexcept;

    static const int DaysPerWeek{7};

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

        ImGui::Text("%i", static_cast<int>(date.year()));
        ImGui::SameLine();

        ImGui::SameLine();
        if (ImGui::ArrowButton("Up", ImGuiDir_Up)) {
            date -= months{1};
        }

        ImGui::SameLine();
        ImGui::Text("%s", MonthNames[static_cast<unsigned int>(date.month()) - 1]); // chrono::month index starts at 1

        ImGui::SameLine();
        if (ImGui::ArrowButton("Down", ImGuiDir_Down)) {
            date += months{1};
        }

        ImGui::Separator();

        auto lastDayOfMonth = year_month_day{date.year() / date.month() / last};
        weekday weekdayOfFirstDay = sys_days{year_month_day{date.year() / date.month() / 1}};
        weekday weekdayOfLastDay = sys_days{lastDayOfMonth};

        SelectDay(lastDayOfMonth, weekdayOfFirstDay, weekdayOfLastDay);

        ImGui::EndGroup();
        ImGui::PopID();

        return false;
    }

    void SelectDay(std::chrono::year_month_day const &lastDayOfMonth, std::chrono::weekday const &weekdayOfFirstDay,
                   std::chrono::weekday const &weekdayOfLastDay) noexcept {
        if (ImGui::BeginTable("Days", 7)) {
            for (auto const *day: DayNames) {
                ImGui::TableSetupColumn(day);
            }

            ImGui::TableHeadersRow();

            // Fill in days that come before the first day of active month
            for (int i{0}; i < weekdayOfFirstDay.iso_encoding() - 1; ++i) {
                if (ImGui::TableNextColumn()) {
                    ImGui::Text("%s", "x");
                }
            }

            for (int i{1}; i <= static_cast<unsigned int>(lastDayOfMonth.day()); ++i) {
                if (ImGui::TableNextColumn()) {
                    ImGui::Text("%i", i);
                }
            }

            // Fill the remaining days of the calendar after the last day - if any
            for (auto i{DaysPerWeek}; i > static_cast<unsigned int>(weekdayOfLastDay.iso_encoding()); --i) {
                if (ImGui::TableNextColumn()) {
                    ImGui::Text("%s", "x");
                }
            }

            ImGui::EndTable();
        }
    }
}