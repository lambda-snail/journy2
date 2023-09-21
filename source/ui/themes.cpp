#include "ui/themes.h"

namespace themes
{
    ImColor AddTransparency(ImColor const& color, float alpha)
    {
        assert(alpha >= 0 and alpha <= 1);
        return { color.Value.x, color.Value.y, color.Value.z, alpha };
    }

    ImColor LinearInterpolation(ImColor const& start, ImColor const& end, float weight, bool preserveAlpha)
    {
        assert(weight >= 0 and weight <= 1);

        auto x = start.Value.x + (end.Value.x - start.Value.x) * weight;
        auto y = start.Value.y + (end.Value.y - start.Value.y) * weight;
        auto z = start.Value.z + (end.Value.z - start.Value.z) * weight;
        auto a = preserveAlpha ? start.Value.w : start.Value.w + (end.Value.w - start.Value.w) * weight;

        return { x, y, z, a };
    }

    void UseDarkTheme()
    {
        ImGuiStyle& style = ImGui::GetStyle();

        ImVec4* colors = style.Colors;
        colors[ImGuiCol_Text]                   = White_75;
        colors[ImGuiCol_TextDisabled]           = White_35;
        colors[ImGuiCol_WindowBg]               = PrimaryColor_100;
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = AddTransparency(SecondaryColor_60, 0.15);
        colors[ImGuiCol_FrameBgHovered]         = AddTransparency(SecondaryColor_80, 0.67);
        colors[ImGuiCol_FrameBgActive]          = AddTransparency(SecondaryColor_80, 0.80);
        colors[ImGuiCol_TitleBg]                = PrimaryColor_200;
        colors[ImGuiCol_TitleBgActive]          = SecondaryColor_60;
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = AccentColor_100;
        colors[ImGuiCol_ScrollbarGrabActive]    = AccentColor_200;
        colors[ImGuiCol_CheckMark]              = SecondaryColor_200;
        colors[ImGuiCol_SliderGrab]             = SecondaryColor_100;
        colors[ImGuiCol_SliderGrabActive]       = SecondaryColor_200;
        colors[ImGuiCol_Button]                 = SecondaryColor_100;
        colors[ImGuiCol_ButtonHovered]          = SecondaryColor_200;
        colors[ImGuiCol_ButtonActive]           = SecondaryColor_300;
        colors[ImGuiCol_Header]                 = SecondaryColor_100;
        colors[ImGuiCol_HeaderHovered]          = SecondaryColor_200;
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.47f, 0.47f, 0.47f, 0.67f);
        colors[ImGuiCol_Separator]              = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
        colors[ImGuiCol_ResizeGrip]             = AccentColor_100;
        colors[ImGuiCol_ResizeGripHovered]      = AccentColor_200;
        colors[ImGuiCol_ResizeGripActive]       = White;
        colors[ImGuiCol_Tab]                    = SecondaryColor_60;
        colors[ImGuiCol_TabHovered]             = SecondaryColor_300;
        colors[ImGuiCol_TabActive]              = SecondaryColor_100;
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.05f, 0.05f, 0.05f, 0.90f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.13f, 0.13f, 0.13f, 0.74f);
        colors[ImGuiCol_DockingPreview]         = ImVec4(0.47f, 0.47f, 0.47f, 0.47f);
        colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
        colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
        colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

        style.WindowMinSize        = ImVec2( 160, 20 );
        style.FramePadding         = ImVec2( 4, 2 );
        style.ItemSpacing          = ImVec2( 6, 2 );
        style.ItemInnerSpacing     = ImVec2( 6, 4 );
        style.Alpha                = 0.95f;
        style.WindowRounding       = 4.0f;
        style.FrameRounding        = 2.0f;
        style.IndentSpacing        = 6.0f;
        style.ItemInnerSpacing     = ImVec2( 2, 4 );
        style.ColumnsMinSpacing    = 50.0f;
        style.GrabMinSize          = 14.0f;
        style.GrabRounding         = 16.0f;
        style.ScrollbarSize        = 12.0f;
        style.ScrollbarRounding    = 16.0f;
    }
}