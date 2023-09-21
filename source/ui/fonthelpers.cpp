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
ImFont* journy::ui::fonts::FontPool::Roboto_Italic { nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Header1 { nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Header2 { nullptr };

ImFont* journy::ui::fonts::FontPool::FontAwesome_Regular { nullptr };

void journy::ui::fonts::FontPool::InitFonts()
{
    float baseFontSize = 13.f;
    Roboto_Regular = AddFont("resources/fonts/Roboto-Regular.ttf", baseFontSize);

    // https://github.com/juliettef/IconFontCppHeaders/tree/main
    // https://www.fileformat.info/info/unicode/char/e072/index.htm
    static const ImWchar icons_ranges[] = { 0xe000, 0xf8ff, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    FontAwesome_Regular = ImGui::GetIO().Fonts->AddFontFromFileTTF("resources/fonts/MaterialIcons-Regular.ttf", baseFontSize, &icons_config, icons_ranges);

    Roboto_Bold = AddFont("resources/fonts/Roboto-Bold.ttf", baseFontSize);
    Roboto_Italic = AddFont("resources/fonts/Roboto-Italic.ttf", baseFontSize);
    Roboto_Header1 = AddFont("resources/fonts/Roboto-Bold.ttf", baseFontSize + 4.f);
    Roboto_Header2 = AddFont("resources/fonts/Roboto-Bold.ttf", baseFontSize + 2.f);

    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Regular != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Bold != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Italic != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Header1 != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Header2 != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::FontAwesome_Regular != nullptr);
}
