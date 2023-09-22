#pragma once

// Library of convenience functions that wrap some functionality in ImGui

#include "imgui.h"
#include <string>

namespace journy::ui
{
    enum class TooltipDelay
    {
        None = ImGuiHoveredFlags_DelayNone,
        Short = ImGuiHoveredFlags_DelayShort,
        Normal = ImGuiHoveredFlags_DelayNormal
    };

    /**
     * Adds a tooltip to the last submitted component, with a specified delay.
     */
    void AddTooltipWithDelay(std::string const& text, TooltipDelay delay);
    void AddTooltipWithDelay(char const* text, TooltipDelay delay);
}