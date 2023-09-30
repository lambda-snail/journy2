#include <chrono>
#include <iostream>

#include "Application.h"
#include "applicationstrings.h"

#include "imgui.h"
#include "ui/fonthelpers.h"
#include "ui/font/iconsmaterialdesign.h"
#include "ui/datepicker/datepicker.h"
#include "ui/imguiextensions.h"
#include "version.h"

void Application::LoadConfiguration()
{
    m_Config.SetUnicode();
    m_Config.LoadFile(APPLICATION_CONFIG_FILE);

    bShouldInitDatabase = not m_Config.GetBoolValue(CONFIG_SECTION_DB, CONFIG_DB_INITIALIZED, false);
    m_ActiveDatabaseName = m_Config.GetValue(CONFIG_SECTION_DB, CONFIG_DB_NAME_KEY, CONFIG_DB_DEFAULT_NAME);

    m_Db = std::make_unique<todo::DatabaseManager>(m_ActiveDatabaseName, bShouldInitDatabase);
    if(bShouldInitDatabase)
    {
        bShouldInitDatabase = false;
        m_Config.SetBoolValue(CONFIG_SECTION_DB, CONFIG_DB_INITIALIZED, true);
        m_Config.SetValue(CONFIG_SECTION_DB, CONFIG_DB_NAME_KEY, m_ActiveDatabaseName.c_str());
    }
}

void Application::Startup()
{
    using namespace std::chrono;

    LoadConfiguration();

    auto now = std::chrono::time_point<std::chrono::system_clock>::clock::now();
    auto today = year_month_day { floor<days>(now) };

    auto min = year_month_day { today.year() / January / 1 };
    auto max = year_month_day { today.year() / December / 31 };

    m_JournalEntries = m_Db->GetAllJournalEntriesBetween(min, max);
    for(auto const& e : m_JournalEntries)
    {
        std::cout << e.toString() << std::endl;
    }
}

void Application::Teardown()
{
    m_Config.SaveFile(APPLICATION_CONFIG_FILE);
}

void Application::BuildUi()
{
    using namespace ImGuiExtensions;

//    static bool done { false };
//    auto const now { floor<std::chrono::days>(std::chrono::system_clock::now()) };
//    static DatePickerLevel l { DatePickerLevel::Days };
//    static std::chrono::year_month_day testDate { now };
//
//    if(not done)
//    {
//        done = OpenDatePickerModal("Calendar", testDate);
//    }

    ImGuiID vpDockSpace = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
    static bool bShouldInitialize = true;

    static ImGuiID vpLeftDock, vpRightDock, vpCenterDock;
    if (bShouldInitialize){
        bShouldInitialize = false;
        ImGui::DockBuilderRemoveNode(vpDockSpace);
        ImGui::DockBuilderAddNode(vpDockSpace);
        ImGui::DockBuilderSetNodeSize(vpDockSpace, ImGui::GetMainViewport()->Size);

        ImGui::DockBuilderSplitNode(vpDockSpace, ImGuiDir_Left, 0.2f, &vpLeftDock, &vpRightDock);
        ImGui::DockBuilderSplitNode(vpRightDock, ImGuiDir_Right, 0.2f, &vpRightDock, &vpCenterDock);

        ImGui::DockBuilderDockWindow("Entry List", vpLeftDock);
        ImGui::DockBuilderDockWindow("Dear ImGui Demo", vpRightDock);
        ImGui::DockBuilderDockWindow("Outline", vpRightDock);

        for(auto const& entry : m_OpenEntries)
        {
            if(entry.second->IsOpen())
            {
                ImGui::DockBuilderDockWindow(entry.second->GetName().c_str(), vpCenterDock);
            }
        }

        ImGui::DockBuilderFinish(vpDockSpace);
    }

    static todo::JournalEntry* selectedItem { nullptr };
    ImGui::Begin("Entry List", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar );
        auto scale = journy::ui::GetDpiScaleFactor();
        float size = 32.f * scale;
        ImGui::BeginChild("Entry Commands", { 0.f, size });

            static bool showDatePicker { false };
            if(ImGui::Button(ICON_MD_ADD, { size, size }))
            {
                showDatePicker = true;
            }
            journy::ui::AddTooltipWithDelay("Start a new journal entry", journy::ui::TooltipDelay::Normal);

            ImGui::SameLine();
            ImGui::Button(ICON_MD_DELETE, { size, size });
            journy::ui::AddTooltipWithDelay("Delete a journal entry. Warning - cannot be undone!", journy::ui::TooltipDelay::Normal);

            auto const now { floor<std::chrono::days>(std::chrono::system_clock::now()) };
            static DatePickerLevel l { DatePickerLevel::Days };
            static std::chrono::year_month_day date { now };

            bool dateSelected = OpenDatePickerModal("Select Date", showDatePicker, date);
            if(dateSelected)
            {
                todo::JournalEntry entry{ date, {} };
                m_Db->AddNewJournalEntry(entry);
                m_JournalEntries.push_back(entry);
            }

        ImGui::EndChild();
        ImGui::Separator();

        if(ImGui::BeginTable("Entries", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
        {
            for (auto& entry : m_JournalEntries)
            {
                ImGui::TableNextColumn();
                bool isSelected = (selectedItem == &entry);
                if(ImGui::Selectable(entry.toString().c_str(), isSelected))
                {
                    selectedItem = &entry;
                    if(m_OpenEntries.contains(entry.getDate()))
                    {
                        std::unique_ptr<journy::ui::MarkdownEditor> const& editor = m_OpenEntries.at(entry.getDate());
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
                        m_OpenEntries[entry.getDate()] = std::make_unique<journy::ui::MarkdownEditor>(&entry, vpCenterDock);
                    }
                }

                if(isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndTable();
        }
    ImGui::End(); // Entry list

    std::function<void(todo::JournalEntry const&)> const saveEntryFunction = [this](todo::JournalEntry const& entry) {
        this->m_Db->UpdateJournalEntryContent(entry);
    };

    for(auto const& [_, editor] : m_OpenEntries)
    {
        editor->BuildUi(saveEntryFunction);
    }

    // We keep this for now - could come in handy :)
    if (bShowDemoWindow)
        ImGui::ShowDemoWindow(&bShowDemoWindow);

    BuildMenu();
}

void Application::BuildMenu()
{
    // Workaround for modal opened from inside menu items
    // https://github.com/ocornut/imgui/issues/331#issuecomment-1542969157
    ImGuiID aboutPopupId = ImHashStr("About Journy" );

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
                ImGui::PushOverrideID(aboutPopupId );
                ImGui::OpenPopup("About Journy");
                ImGui::PopID();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();

        // About modal
        ImGui::PushOverrideID(aboutPopupId );
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

bool Application::ShouldCloseApplication() const
{
    return bShouldClose;
}
