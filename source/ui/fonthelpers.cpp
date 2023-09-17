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

ImFont* journy::ui::fonts::FontPool::Normal { nullptr };
ImFont* journy::ui::fonts::FontPool::Bold {nullptr };
ImFont* journy::ui::fonts::FontPool::Normal_200 { nullptr };
ImFont* journy::ui::fonts::FontPool::Normal_300 { nullptr };
ImFont* journy::ui::fonts::FontPool::Normal_400 { nullptr };

void journy::ui::fonts::FontPool::InitFonts() {
    Normal = AddFont("resources/fonts/Roboto-Regular.ttf", 12);
    Bold = AddFont("resources/fonts/Roboto-Bold.ttf", 12);
}
