#include <string>

#include "ui/datepicker/datepicker.h"

static const char* MonthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
static const char* DayNames[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};

static const int DaysPerWeek { 7 };

/**
 * Index into the abbreviations array from a c-based index (Sunday is index 0).
 */
inline const char* getWeekdayAbbreviation(std::chrono::weekday const& wd)
{
    return DayNames[wd.iso_encoding() - 1];
}

const int min_yr = 1970;
const int max_yr = 2100;

bool DatePicker(const char *id, int& level, std::chrono::year_month_day& date)
{
    using namespace std::chrono;

    ImGui::PushID(id);
    ImGui::BeginGroup();

    ImGui::Text("%i", static_cast<int>(date.year())); ImGui::SameLine();

    ImGui::SameLine();
    if(ImGui::ArrowButton("Up", ImGuiDir_Up))
    {
        date -= months{ 1 };
    }

    ImGui::SameLine();
    if(ImGui::ArrowButton("Down", ImGuiDir_Down))
    {
        date += months{ 1 };
    }

    ImGui::SameLine();
    ImGui::Text("%s", MonthNames[static_cast<unsigned int>(date.month()) - 1]); // chrono::month index starts at 1

    ImGui::Separator();

    auto lastDayOfMonth = year_month_day {date.year() / date.month() / last };
    auto lastDay_int = static_cast<unsigned int>(lastDayOfMonth.day());
    weekday weekdayOfFirstDay = sys_days{year_month_day { date.year() / date.month() / 1 } };
    weekday weekdayOfLastDay = sys_days{ lastDayOfMonth };

    if(ImGui::BeginTable("Days", 7))
    {
        for(auto const* day : DayNames)
        {
            ImGui::TableSetupColumn( day );
        }

        ImGui::TableHeadersRow();

        // Fill in days that come before the first day of active month
        for(int i { 0 }; i < weekdayOfFirstDay.iso_encoding() - 1; ++i)
        {
            if(ImGui::TableNextColumn())
            {
                ImGui::Text("%s", "x");
            }
        }

        //ImGui::TableSetColumnIndex(static_cast<int>(weekdayOfFirstDay.iso_encoding()));

        for(int i {1}; i <= lastDay_int; ++i)
        {
            if(ImGui::TableNextColumn())
            {
                ImGui::Text("%i", i);
            }
        }

        // Fill the remaining days of the calendar after the last day - if any
        for(auto i { DaysPerWeek }; i > static_cast<unsigned int>(weekdayOfLastDay.iso_encoding()); --i)
        {
            if(ImGui::TableNextColumn())
            {
                ImGui::Text("%s", "x");
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndGroup();
    ImGui::PopID();

    return false;
}
