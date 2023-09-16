#pragma once

#include <imgui.h>
#include "journal/databasemanager.h"

class Application {
public:
    explicit Application(ImGuiIO& imguiio) : io(imguiio), p_Db{nullptr} {};

    void Startup();
    void BuildUi();
    void Render(ImDrawData* main_draw_data);
    void Teardown();

    ~Application() = default;
private:
    ImGuiIO& io;

    bool show_demo_window = true;
    bool show_another_window = false;

    std::vector<todo::JournalEntry> journalEntries;
    std::unique_ptr<todo::DatabaseManager> p_Db;
};
