#include <chrono>
#include <iostream>

#include "Application.h"

#include "imgui.h"
#include "ui/fonthelpers.h"
#include "ui/font/iconsmaterialdesign.h"
#include "ui/datepicker/datepicker.h"
#include "ui/imguiextensions.h"
#include "version.h"

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

    // We keep this for now - could come in handy :)
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    BuildMenu();
}

void Application::BuildMenu() {

    // Workaround for modal opened from inside menu items
    // https://github.com/ocornut/imgui/issues/331#issuecomment-1542969157
    ImGuiID popup_id = ImHashStr( "About Journy" );

    if(ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Exit"))
            {
                bShouldClose = true;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if(ImGui::MenuItem("About"))
            {
                ImGui::PushOverrideID( popup_id );
                ImGui::OpenPopup("About Journy");
                ImGui::PopID();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();

        // About modal
        ImGui::PushOverrideID( popup_id );
        if(ImGui::BeginPopupModal("About Journy"))
        {
            ImGui::Text("Journy created by Niclas Blomberg (lambda-snail)");
            ImGui::Separator();
            ImGui::Text("Licensed under MIT license. Source code available at https://github.com/lambda-snail/journy2");
            ImGui::Text("This build is based on version %s of the project. Feel free to donwload the latest build if you are out of date!", JOURNY_VERSION);

            if(ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
        ImGui::PopID();
    }
}

bool Application::ShouldCloseApplication() const {
    return bShouldClose;
}
