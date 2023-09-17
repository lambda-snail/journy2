#pragma once

#include "imgui.h"

#include "markdown/parser/MarkdownBaseListener.h"

namespace journy::markdown
{
    class MarkdownToVector : public marky::MarkdownBaseListener
    {
    public:
        explicit MarkdownToVector(ImDrawList* dl, ImVec4 background_color) : draw{dl}, clear_color{background_color} {};

        void visitTerminal(antlr4::tree::TerminalNode* node) override;

        void enterBlock(marky::MarkdownParser::BlockContext* ctx) override;
        void exitBlock(marky::MarkdownParser::BlockContext* ctx) override;

    private:
        ImDrawList* draw;

        ImVec2 blank_size { ImGui::CalcTextSize(" ") };
        ImVec2 cursor { ImGui::GetCursorScreenPos() };
        ImVec2 offset { 0,0 };
        ImU32 color = { ImGui::GetColorU32(clear_color) };
        ImVec4 clear_color;

        float row_distance_in_paragraph { 8 };
    };
}