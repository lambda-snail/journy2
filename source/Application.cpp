#include <iostream>

#include "Application.h"

#include "imgui.h"

void Application::Startup()
{
    p_Db = std::make_unique<todo::DatabaseManager>(R"(C:\Projects\cpp\journy2\resources\todo.db)", false);

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

        ImGui::BeginChild("Entry List", {256.f, 0.f}, true, ImGuiWindowFlags_None);
        if(ImGui::BeginTable("Entries", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
        {
            for (auto const& entry : journalEntries)
            {
                ImGui::TableNextColumn();
                ImGui::Button(entry.toString().c_str(), ImVec2(-FLT_MIN, 0.0f));
            }

            ImGui::EndTable();
        }

        ImGui::EndChild();

    ImGui::End();



    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}
