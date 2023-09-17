#pragma once

#include <imgui.h>
#include <memory>
#include <string>

namespace journy::ui::fonts {
    class FontPool
    {
    public:
        static void InitFonts();

        static ImFont* Normal;
        static ImFont* Bold;
        static ImFont* Normal_200;
        static ImFont* Normal_300;
        static ImFont* Normal_400;

        static ImFont* AddFont(char const* file, float pixel_size);
    };
}