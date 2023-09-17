#include "ui/fonthelpers.h"

ImFont *journy::ui::fonts::FontPool::AddFont(char const* file, float pixel_size) {
    ImGuiIO &io = ImGui::GetIO();
    ImFontConfig config;
    config.SizePixels = pixel_size;
    config.OversampleH = config.OversampleV = 1;
    config.PixelSnapH = true;
    ImFont* font = io.Fonts->AddFontFromFileTTF(file, pixel_size, &config);
    return font;
}

ImFont* journy::ui::fonts::FontPool::Roboto_Regular { nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Bold { nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Italic {nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Header1 { nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Header2 {nullptr };

void journy::ui::fonts::FontPool::InitFonts() {
    Roboto_Regular = AddFont("resources/fonts/Roboto-Regular.ttf", 12);
    Roboto_Bold = AddFont("resources/fonts/Roboto-Bold.ttf", 12);
    Roboto_Italic = AddFont("resources/fonts/Roboto-Italic.ttf", 12);
    Roboto_Header1 = AddFont("resources/fonts/Roboto-Bold.ttf", 16);
    Roboto_Header2 = AddFont("resources/fonts/Roboto-Bold.ttf", 14);

    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Regular != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Bold != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Italic != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Header1 != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Header2 != nullptr);
}
