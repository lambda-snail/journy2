#pragma once

#include "imgui.h"

namespace themes
{
    ImColor AddTransparency(ImColor const& color, float alpha);
    ImColor LinearInterpolation(ImColor const& start, ImColor const& end, float weight, bool preserveAlpha = true);

    void UseDarkTheme();

    ImColor const PrimaryColor_100 = ImColor(31, 34, 32, 255);
    ImColor const PrimaryColor_200 = ImColor(51, 51, 51, 255);

    ImColor const SecondaryColor_60 = ImColor(98, 46, 4, 255);
    ImColor const SecondaryColor_80 = ImColor(122, 58, 5, 255);  // Darker
    ImColor const SecondaryColor_100 = ImColor(150, 70, 6, 255); // Base
    ImColor const SecondaryColor_200 = ImColor(170, 80, 6, 255); // Brighter
    ImColor const SecondaryColor_300 = ImColor(200, 97, 6, 255);

    ImColor const AccentColor_100 = ImColor(176, 218, 241);
    ImColor const AccentColor_200 = ImColor(190, 223, 255);

    ImColor const AccentColor2 = ImColor(141,145,199);
    ImColor const AccentColor3 = ImColor(110,117,168);

    ImColor const White = ImColor(255,255,255);
    ImColor const Black = ImColor(0,0,0);

    ImColor const White_35 = LinearInterpolation(Black, White, .35f);
    ImColor const White_75 = LinearInterpolation(Black, White, .75f);
}