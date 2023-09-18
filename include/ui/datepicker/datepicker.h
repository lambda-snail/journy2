// Attempted adaption from ImPlot
// https://github.com/epezent/implot/blob/fbfd41047b384438efbcf6a6e4f26bd4a9c80ca0/implot.cpp#L3359
//
// All credits to the ImPlot team

#pragma once

#include "time.h"

#include "imgui_internal.h"
#include "imgui.h"
#include <chrono>

inline void BeginDisabledControls(bool cond) {
    if (cond) {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.25f);
    }
}

inline void EndDisabledControls(bool cond) {
    if (cond) {
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
    }
}

static inline bool IsLeapYear(int year) {
    return  year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}
// Returns the number of days in a month, accounting for Feb. leap years. #month is zero indexed.
static inline int GetDaysInMonth(int year, int month) {
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return  days[month] + (int)(month == 1 && IsLeapYear(year));
}

bool ShowDatePicker(const char* id, int* level, std::chrono::year_month_day* t) {

    ImGui::PushID(id);
    ImGui::BeginGroup();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));

    static const char* names_mo[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    static const char* abrvs_mo[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    static const char* abrvs_wd[] = {"Su","Mo","Tu","We","Th","Fr","Sa"};

    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4 col_txt    = style.Colors[ImGuiCol_Text];
    ImVec4 col_dis    = style.Colors[ImGuiCol_TextDisabled];
    const float ht    = ImGui::GetFrameHeight();
    ImVec2 cell_size(ht*1.25f,ht);
    char buff[32];
    bool clk = false;

    const int min_yr = 1970;
    const int max_yr = 2999;

    const std::chrono::time_point now { std::chrono::system_clock::now() };
    const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(now) };

    // day widget
    if (*level == 0) {
        //*t = std::chrono::year_month_day{ t->year(), t->month(), std::chrono::day{1} };

        const int this_year = static_cast<int>(ymd.year());
        const int last_year = this_year - 1;
        const int next_year = this_year + 1;
        const int this_mon  = static_cast<int>(static_cast<unsigned int>(ymd.month()));//Tm.tm_mon;
        const int last_mon  = this_mon == 0 ? 11 : this_mon - 1;
        const int next_mon  = this_mon == 11 ? 0 : this_mon + 1;
        const int days_this_mo = GetDaysInMonth(this_year, this_mon);
        const int days_last_mo = GetDaysInMonth(this_mon == 0 ? last_year : this_year, last_mon);


        auto now_local = std::chrono::current_zone()->to_local(now);
        std::chrono::weekday wd{floor<std::chrono::days>(now_local)};

        const int first_wd = static_cast<int>(wd.c_encoding());
        // month year
        snprintf(buff, 32, "%s %d", names_mo[this_mon], this_year);
        if (ImGui::Button(buff))
            *level = 1;
        ImGui::SameLine(5*cell_size.x);
        BeginDisabledControls(this_year <= min_yr && this_mon == 0);
        if (ImGui::ArrowButtonEx("##Up",ImGuiDir_Up,cell_size)) {
            *t -= std::chrono::months{1};
        }

        EndDisabledControls(this_year <= min_yr && this_mon == 0);
        ImGui::SameLine();
        BeginDisabledControls(this_year >= max_yr && this_mon == 11);
        if (ImGui::ArrowButtonEx("##Down",ImGuiDir_Down,cell_size)) {
            *t += std::chrono::months{1};;
        }

        EndDisabledControls(this_year >= max_yr && this_mon == 11);
        // render weekday abbreviations
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        for (int i = 0; i < 7; ++i) {
            ImGui::Button(abrvs_wd[i],cell_size);
            if (i != 6) { ImGui::SameLine(); }
        }
        ImGui::PopItemFlag();
        // 0 = last mo, 1 = this mo, 2 = next mo
        int mo = first_wd > 0 ? 0 : 1;
        int day = mo == 1 ? 1 : days_last_mo - first_wd + 1;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                if (mo == 0 && day > days_last_mo) {
                    mo = 1; day = 1;
                }
                else if (mo == 1 && day > days_this_mo) {
                    mo = 2; day = 1;
                }
                const int now_yr = (mo == 0 && this_mon == 0) ? last_year : ((mo == 2 && this_mon == 11) ? next_year : this_year);
                const int now_mo = mo == 0 ? last_mon : (mo == 1 ? this_mon : next_mon);
                const int now_md = day;

                const bool off_mo   = mo == 0 || mo == 2;
                const bool t1_or_t2 = false;//     (t1 != NULL && t1_mo == now_mo && t1_yr == now_yr && t1_md == now_md) ||
                                                // (t2 != NULL && t2_mo == now_mo && t2_yr == now_yr && t2_md == now_md);

                if (off_mo)
                    ImGui::PushStyleColor(ImGuiCol_Text, col_dis);
                if (t1_or_t2) {
                    ImGui::PushStyleColor(ImGuiCol_Button, col_dis);
                    ImGui::PushStyleColor(ImGuiCol_Text, col_txt);
                }
                ImGui::PushID(i*7+j);
                snprintf(buff,32,"%d",day);
                if (now_yr == min_yr-1 || now_yr == max_yr+1) {
                    ImGui::Dummy(cell_size);
                }
                else if (ImGui::Button(buff,cell_size) && !clk) {
                    *t = std::chrono::year_month_day{ std::chrono::year{now_yr}, std::chrono::month{static_cast<unsigned int>(now_mo)}, std::chrono::day{static_cast<unsigned int>(now_md)} };
                    clk = true;
                }
                ImGui::PopID();
                if (t1_or_t2)
                    ImGui::PopStyleColor(2);
                if (off_mo)
                    ImGui::PopStyleColor();
                if (j != 6)
                    ImGui::SameLine();
                day++;
            }
        }
    }
        // month widget
    else if (*level == 1) {
        *t = std::chrono::year_month_day{ t->year(), t->month(), std::chrono::day{1} };

        int this_yr  = 2023;//Tm.tm_year + 1900;
        snprintf(buff, 32, "%d", this_yr);
        if (ImGui::Button(buff))
            *level = 2;
        BeginDisabledControls(this_yr <= min_yr);
        ImGui::SameLine(5*cell_size.x);
        if (ImGui::ArrowButtonEx("##Up",ImGuiDir_Up,cell_size))
        {
            *t -= std::chrono::years{1};
        }

        EndDisabledControls(this_yr <= min_yr);
        ImGui::SameLine();
        BeginDisabledControls(this_yr >= max_yr);
        if (ImGui::ArrowButtonEx("##Down",ImGuiDir_Down,cell_size))
        {
            *t += std::chrono::years{1};
        }

        EndDisabledControls(this_yr >= max_yr);
        // ImGui::Dummy(cell_size);
        cell_size.x *= 7.0f/4.0f;
        cell_size.y *= 7.0f/3.0f;
        int mo = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                const bool t1_or_t2 = false; //(t1 != NULL && t1_yr == this_yr && t1_mo == mo) ||
                                      //(t2 != NULL && t2_yr == this_yr && t2_mo == mo);
                if (t1_or_t2)
                    ImGui::PushStyleColor(ImGuiCol_Button, col_dis);
                if (ImGui::Button(abrvs_mo[mo],cell_size) && !clk) {
                    *t = std::chrono::year_month_day{ std::chrono::year{this_yr}, std::chrono::month{static_cast<unsigned int>(mo)}, std::chrono::day{1} };
                    *level = 0;
                }
                if (t1_or_t2)
                    ImGui::PopStyleColor();
                if (j != 3)
                    ImGui::SameLine();
                mo++;
            }
        }
    }
    else if (*level == 2) {
        *t = std::chrono::year_month_day{ t->year(), std::chrono::January, std::chrono::day{1} };

        int this_yr = static_cast<int>(t->year());
        int yr = this_yr - this_yr % 20;
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        snprintf(buff,32,"%d-%d",yr,yr+19);
        ImGui::Button(buff);
        ImGui::PopItemFlag();
        ImGui::SameLine(5*cell_size.x);
        BeginDisabledControls(yr <= min_yr);
        if (ImGui::ArrowButtonEx("##Up",ImGuiDir_Up,cell_size))
        {
            *t = (std::chrono::January/1/yr) - std::chrono::years{20}; //*t = MakeTime(yr-20);
        }

        EndDisabledControls(yr <= min_yr);
        ImGui::SameLine();
        BeginDisabledControls(yr + 20 >= max_yr);
        if (ImGui::ArrowButtonEx("##Down",ImGuiDir_Down,cell_size))
        {
            *t = (std::chrono::January/1/yr) + std::chrono::years{20}; //*t = MakeTime(yr+20);
        }

        EndDisabledControls(yr+ 20 >= max_yr);
        // ImGui::Dummy(cell_size);
        cell_size.x *= 7.0f/4.0f;
        cell_size.y *= 7.0f/5.0f;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 4; ++j) {
                const bool t1_or_t2 = false;// (t1 != NULL && t1_yr == yr) || (t2 != NULL && t2_yr == yr);
                if (t1_or_t2)
                    ImGui::PushStyleColor(ImGuiCol_Button, col_dis);
                snprintf(buff,32,"%d",yr);
                if (yr<1970||yr>3000) {
                    ImGui::Dummy(cell_size);
                }
                else if (ImGui::Button(buff,cell_size)) {
                    *t = std::chrono::January/1/yr;
                    *level = 1;
                }
                if (t1_or_t2)
                    ImGui::PopStyleColor();
                if (j != 3)
                    ImGui::SameLine();
                yr++;
            }
        }
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::EndGroup();
    ImGui::PopID();
    return clk;
}