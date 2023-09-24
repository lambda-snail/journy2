#pragma once

#include <map>
#include <imgui.h>
#include "ui/markdowneditor.h"
#include "journal/databasemanager.h"

class Application {
public:
    explicit Application(ImGuiIO& imguiio) : io(imguiio), p_Db{nullptr} {};

    void Startup();
    void BuildUi();
    void BuildMenu();
    void Render(ImDrawData* main_draw_data);
    void Teardown();

    bool ShouldCloseApplication() const;

    ~Application() = default;
private:
    ImGuiIO& io;
    bool bShouldClose { false };

    bool show_demo_window { true };

    std::vector<todo::JournalEntry> journalEntries;
    std::unique_ptr<todo::DatabaseManager> p_Db;

    std::map<std::chrono::year_month_day, std::unique_ptr<journy::ui::MarkdownEditor>> openEntries;
};
