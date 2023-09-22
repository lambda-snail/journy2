#include "ui/imguiextensions.h"

void journy::ui::AddTooltipWithDelay(std::string const& text, journy::ui::TooltipDelay delay) {
    AddTooltipWithDelay(text.c_str(), delay);
}

void journy::ui::AddTooltipWithDelay(char const* text, journy::ui::TooltipDelay delay) {
    if (ImGui::IsItemActive() || ImGui::IsItemHovered(static_cast<int>(delay) | ImGuiHoveredFlags_ForTooltip))
        ImGui::SetTooltip("%s", text);
}
