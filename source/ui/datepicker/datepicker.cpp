#include "ui/datepicker/datepicker.h"

static const char* names_mo[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
static const char* abrvs_mo[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
static const char* abrvs_wd[] = {"Mo","Tu","We","Th","Fr","Sa", "Su"};

/**
 * Index into the abbreviations array from a c-based index (Sunday is index 0).
 */
inline const char* getWeekdayAbbreviation(std::chrono::weekday const& wd)
{
    return abrvs_wd[wd.iso_encoding()-1];
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
    ImGui::Text("%s", names_mo[static_cast<unsigned int>(date.month()) - 1]); // chrono::month index starts at 1

    ImGui::Separator();

    auto lastDay = static_cast<unsigned int>((year_month_day {date.year() / date.month() / last }).day());
    weekday weekdayOfFirstday = sys_days{ year_month_day { date.year() / date.month() / 1 } };

    if(ImGui::BeginTable("Days", 7))
    {
        for(auto const* day : abrvs_wd)
        {
            if(ImGui::TableNextColumn())
            {
                ImGui::Text("%s", day);
            }
        }

        // Fill in days that come before the first day of active month
        for(int i { 0 }; i < weekdayOfFirstday.iso_encoding()-1; ++i)
        {
            if(ImGui::TableNextColumn())
            {
                ImGui::Text("%s", "x");
            }
        }

        //ImGui::TableSetColumnIndex(static_cast<int>(weekdayOfFirstday.iso_encoding()));

        for(int i {1}; i <= lastDay; ++i)
        {
            if(ImGui::TableNextColumn())
            {
                ImGui::Text("%i", i);
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndGroup();
    ImGui::PopID();

    return false;
}
