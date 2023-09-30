#pragma once

#include <map>
#include <imgui.h>
#include <SimpleIni.h>
#include "ui/markdowneditor.h"
#include "journal/databasemanager.h"

class Application {
public:
    explicit Application() : m_Db{nullptr} {};

    void Startup();
    void BuildUi();
    void BuildMenu();
    void Teardown();

    [[nodiscard]] bool ShouldCloseApplication() const;

    ~Application() = default;
private:
    CSimpleIniA m_Config;
    bool bShouldClose { false };

    bool bShowDemoWindow {true };
    ImGuiID m_VpLeftDock, m_VpRightDock, m_VpCenterDock;

    std::vector<todo::JournalEntry> m_JournalEntries;

    bool bShouldInitDatabase { false };
    std::string m_ActiveDatabaseName;
    std::unique_ptr<todo::DatabaseManager> m_Db;

    std::map<std::chrono::year_month_day, std::unique_ptr<journy::ui::MarkdownEditor>> m_OpenEntries;

    void LoadConfiguration();
    void BuildDockspaces(ImGuiID& vpDockSpaceID);
};
