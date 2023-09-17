#pragma once

#include <imgui.h>
#include <memory>
#include <string>

namespace journy::ui::fonts {
    class FontPool
    {
    public:
        static void InitFonts();

        static ImFont* Roboto_Regular;
        static ImFont* Roboto_Bold;
        static ImFont* Roboto_Italic;
        static ImFont* Roboto_Header1;
        static ImFont* Roboto_Header2;

        static ImFont* AddFont(char const* file, float pixel_size);
    };
}