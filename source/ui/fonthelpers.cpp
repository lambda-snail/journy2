#include "ui/fonthelpers.h"

ImFont *journy::ui::fonts::FontPool::AddFont(char const* file, float pixel_size, float dpi) {
    ImGuiIO &io = ImGui::GetIO();
    ImFontConfig config;
    config.SizePixels = pixel_size;
    config.OversampleH = config.OversampleV = 1;
    config.PixelSnapH = true;
    ImFont* font = io.Fonts->AddFontFromFileTTF(file, pixel_size * dpi, &config);
    return font;
}

ImFont* journy::ui::fonts::FontPool::Roboto_Regular { nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Bold { nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Italic { nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Header1 { nullptr };
ImFont* journy::ui::fonts::FontPool::Roboto_Header2 { nullptr };

ImFont* journy::ui::fonts::FontPool::FontAwesome_Regular { nullptr };

void journy::ui::fonts::FontPool::InitFonts(float dpi_scale)
{
    float baseFontSize = 13.f;
    Roboto_Regular = AddFont("resources/fonts/Roboto-Regular.ttf", baseFontSize, dpi_scale);

    // https://github.com/juliettef/IconFontCppHeaders/tree/main
    // https://www.fileformat.info/info/unicode/char/e072/index.htm
    static const ImWchar icons_ranges[] = { 0xe000, 0xf8ff, 0 };
    ImFontConfig icons_config;
    icons_config.GlyphOffset = { 0,3 * dpi_scale }; // 2 for baseFontSize and 3 for 1.3*bfs looks fairly good
    icons_config.MergeMode = true;
    FontAwesome_Regular = ImGui::GetIO().Fonts->AddFontFromFileTTF("resources/fonts/MaterialIcons-Regular.ttf", dpi_scale * baseFontSize, &icons_config, icons_ranges);

    Roboto_Bold = AddFont("resources/fonts/Roboto-Bold.ttf", baseFontSize, dpi_scale);
    Roboto_Italic = AddFont("resources/fonts/Roboto-Italic.ttf", baseFontSize, dpi_scale);
    Roboto_Header1 = AddFont("resources/fonts/Roboto-Bold.ttf", baseFontSize + 4.f, dpi_scale);
    Roboto_Header2 = AddFont("resources/fonts/Roboto-Bold.ttf", baseFontSize + 2.f, dpi_scale);

    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Regular != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Bold != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Italic != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Header1 != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::Roboto_Header2 != nullptr);
    IM_ASSERT(journy::ui::fonts::FontPool::FontAwesome_Regular != nullptr);
}
