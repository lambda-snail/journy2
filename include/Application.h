#pragma once

#include <imgui.h>

class Application {
public:
    explicit Application(ImGuiIO& imguiio) : io(imguiio) {};

    void Startup();
    void BuildUi();
    void Render(ImDrawData* main_draw_data);
    void Teardown();

    ~Application() = default;
private:
    ImGuiIO& io;

    bool show_demo_window = true;
    bool show_another_window = false;
};
