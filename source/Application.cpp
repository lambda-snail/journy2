#include <chrono>
#include <iostream>

#include "Application.h"

#include "imgui.h"
#include "ui/fonthelpers.h"
#include "ui/font/iconsmaterialdesign.h"
#include "ui/datepicker/datepicker.h"
#include "ui/imguiextensions.h"

void Application::Startup()
{
    p_Db = std::make_unique<todo::DatabaseManager>(R"(../resources/todo.db)", false);

    std::chrono::year_month_day min{};// { std::chrono::January / 1 / 2023 };
    std::chrono::year_month_day max{};// { std::chrono::December / 31 / 2023 };

    std::stringstream minstream("2023-01-01");
    std::stringstream maxstream("2023-12-31");

    std::chrono::from_stream(minstream, "%F", min);
    std::chrono::from_stream(maxstream, "%F", max);

    journalEntries = p_Db->GetAllJournalEntriesBetween(min, max);
    for(auto const& e : journalEntries)
    {
        std::cout << e.toString() << std::endl;
    }
}

void Application::Teardown() {

}

void Application::Render(ImDrawData* main_draw_data) {
}

void Application::BuildUi() {

#ifdef IMGUI_HAS_VIEWPORT
    auto const* vp = ImGui::GetMainViewport();
#else
    ImGui::SetNextWindowPos({0.f, 0.f});
    ImGui::SetNextWindowSize(io.DisplaySize);
#endif

    // TODO: Split the right window into two, put open entries in the center by default
    // Open outline in the right-most dock
    ImGuiID vp_dockspace = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
    static bool bShouldInitialize = true;

    static ImGuiID vp_left_d, vp_right_d, vp_center_d;
    if (bShouldInitialize){
        bShouldInitialize = false;
        ImGui::DockBuilderRemoveNode(vp_dockspace);
        ImGui::DockBuilderAddNode(vp_dockspace);
        ImGui::DockBuilderSetNodeSize(vp_dockspace, ImGui::GetMainViewport()->Size);

        ImGui::DockBuilderSplitNode(vp_dockspace, ImGuiDir_Left, 0.2f, &vp_left_d, &vp_right_d);
        ImGui::DockBuilderSplitNode(vp_right_d, ImGuiDir_Right, 0.2f, &vp_right_d, &vp_center_d);

        ImGui::DockBuilderDockWindow("Entry List", vp_left_d);
        ImGui::DockBuilderDockWindow("Dear ImGui Demo", vp_right_d);
        ImGui::DockBuilderDockWindow("Outline", vp_right_d);

        for(auto const& entry : openEntries)
        {
            if(entry.second->IsOpen())
            {
                ImGui::DockBuilderDockWindow(entry.second->GetName().c_str(), vp_center_d);
            }
        }

        ImGui::DockBuilderFinish(vp_dockspace);
    }

    //ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
//        if(bShouldInitDockEntryList)
//        {
//            bShouldInitDockEntryList = false;
//
//            //auto vp_dockId = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
//            auto main_dockId = ImGui::DockSpace(ImGui::DockId);
//            ImGui::DockBuilderRemoveNode(main_dockId);
//            ImGui::DockBuilderAddNode(main_dockId);
//            ImGui::DockBuilderSetNodeSize(main_dockId, ImGui::GetMainViewport()->Size);
//
//            ImGui::DockBuilderSplitNode(main_dockId, ImGuiDir_Left, 0.5f, &vp_dock_left, &vp_dock_right);
//            ImGui::DockBuilderDockWindow("Entry List", vp_dock_left);
//            ImGui::DockBuilderDockWindow("Dear ImGui Demo", vp_dock_right);
//
//            ImGui::DockBuilderFinish(main_dockId);
//        }

//        if(bShouldInitDockEntryList && d_left)
//        {
//            ImGui::SetNextWindowDockID(d_left);
//        }

        ImGui::Begin("Entry List", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar );
            auto scale = journy::ui::GetDpiScaleFactor();
            float size = 32.f * scale;
            ImGui::BeginChild("Entry Commands", { 0.f, size });
                if(ImGui::Button(ICON_MD_ADD, { size, size }))
                {
                    ImGui::OpenPopup("NewEntry");
                }
                journy::ui::AddTooltipWithDelay("Start a new journal entry", journy::ui::TooltipDelay::Normal);

                ImGui::SameLine();
                ImGui::Button(ICON_MD_DELETE, { size, size });
                journy::ui::AddTooltipWithDelay("Delete a journal entry. Warning - cannot be undone!", journy::ui::TooltipDelay::Normal);

                if(ImGui::BeginPopupModal("NewEntry"))
                {
                    ImGui::Text("Choose a date for the entry");

                    static int day {0};
                    ImGui::InputInt("Day", &day);
                    if(day < 1) day = 1;
                    if(day > 32) day = 32;

                    const char* items[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
                    static int month = 0;
                    ImGui::Combo("Month", &month, items, IM_ARRAYSIZE(items));

                    static int year {2023};
                    ImGui::InputInt("Year", &year);
                    if(year < 1990) year = 1990;

                    bool create = ImGui::Button("Create"); ImGui::SameLine();
                    bool cancel = ImGui::Button("Cancel");

                    if(create)
                    {
                        std::chrono::year_month_day date( std::chrono::day{static_cast<unsigned int>(day)} / (month+1) / year);
                        todo::JournalEntry entry{ date, {} };
                        p_Db->AddNewJournalEntry(entry);
                        journalEntries.push_back(entry);
                    }

                    if(create || cancel)
                    {
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();
                }

            ImGui::EndChild();
            ImGui::Separator();

            if(ImGui::BeginTable("Entries", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
            {
                for (auto& entry : journalEntries)
                {
                    ImGui::TableNextColumn();
                    if(ImGui::Button(entry.toString().c_str(), ImVec2(-FLT_MIN, 0.0f)))
                    {
                        if(openEntries.contains(entry.getDate()))
                        {
                            std::unique_ptr<journy::ui::MarkdownEditor> const& editor = openEntries.at(entry.getDate());
                            if(not editor->IsOpen())
                            {
                                editor->SetOpen(true);
                            }
                            else
                            {
                                // Focus or bring to foreground

                            }
                        }
                        else
                        {
                            openEntries[entry.getDate()] = std::make_unique<journy::ui::MarkdownEditor>(&entry, vp_center_d);
                        }
                    }
                }

                ImGui::EndTable();
            }
        ImGui::End(); // Entry list

        auto saveEntry = [this](todo::JournalEntry const& entry) {
            this->p_Db->UpdateJournalEntryContent(entry);
        };

        for(auto const& [date, editor] : openEntries)
        {
            editor->BuildUi(saveEntry);
        }
    //ImGui::End();
//
//    ImGui::BeginChild("Status Bar", ImVec2 { 0, 32.f });
//        ImGui::Text("Status: ");
//    ImGui::EndChild();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
}
