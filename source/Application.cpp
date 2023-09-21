#include <chrono>
#include <iostream>

#include "Application.h"

#include "imgui.h"
#include "ui/fonthelpers.h"
#include "ui/datepicker/datepicker.h"

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

    auto vp_dockId = ImGui::DockSpaceOverViewport(vp, ImGuiDockNodeFlags_None);
    ImGui::SetNextWindowDockID(vp_dockId);

    ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize  );

        if(bShouldInitDockEntryList)
        {
            auto const mainWindowId = ImGui::GetWindowDockID();//ImGui::GetItemID();
            ImGui::SetNextWindowDockID(mainWindowId);
            bShouldInitDockEntryList = false;
        }

        //ImGui::BeginChild("Entry List", {256.f, 0.f}, true, ImGuiWindowFlags_None);
        ImGui::Begin("Entry List", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar );

            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, {16.f, 4.f});
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {16.f, 4.f});

            if(ImGui::Button("New"))
            {
                ImGui::OpenPopup("NewEntry");
            }

            ImGui::SameLine();
            ImGui::Button("Delete");

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
                    //bIsCreateModalOpen = false;
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

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
                            openEntries[entry.getDate()] = std::make_unique<journy::ui::MarkdownEditor>(&entry);
                        }
                    }
                }

                ImGui::EndTable();
            }

            ImGui::PopStyleVar(2);
        ImGui::End(); // Entry list

        auto saveEntry = [this](todo::JournalEntry const& entry) {
            this->p_Db->UpdateJournalEntryContent(entry);
        };

        for(auto const& [date, editor] : openEntries)
        {
            editor->BuildUi(saveEntry);
        }
    ImGui::End();
//
//    ImGui::BeginChild("Status Bar", ImVec2 { 0, 32.f });
//        ImGui::Text("Status: ");
//    ImGui::EndChild();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
}
