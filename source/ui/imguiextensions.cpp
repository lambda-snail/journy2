#include "ui/imguiextensions.h"
#include "GLFW/glfw3.h"

void journy::ui::AddTooltipWithDelay(std::string const& text, journy::ui::TooltipDelay delay) {
    AddTooltipWithDelay(text.c_str(), delay);
}

void journy::ui::AddTooltipWithDelay(char const* text, journy::ui::TooltipDelay delay) {
    if (ImGui::IsItemActive() || ImGui::IsItemHovered(static_cast<int>(delay) | ImGuiHoveredFlags_ForTooltip))
        ImGui::SetTooltip("%s", text);
}

float journy::ui::GetDpiScaleFactor() {
    static float dpi_scale = -1.f;
    if(dpi_scale > 0.f)
    {
        return dpi_scale;
    }

    float _;
    glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &dpi_scale, &_);
    assert(dpi_scale > 0);
    return dpi_scale;
}
