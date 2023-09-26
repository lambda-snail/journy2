#include "ui/datepicker/datepicker.h"

static const char* names_mo[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
static const char* abrvs_mo[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
static const char* abrvs_wd[] = {"Mo","Tu","We","Th","Fr","Sa", "Su"};

const int min_yr = 1970;
const int max_yr = 2100;

bool DatePicker(const char *id, int *level, std::chrono::year_month_day& t)
{
    const std::chrono::year_month_day thisYear { std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now()) };

    ImGui::PushID(id);
    ImGui::BeginGroup();





    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::EndGroup();
    ImGui::PopID();

    return false;
}
