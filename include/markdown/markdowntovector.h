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

        void enterHeader(marky::MarkdownParser::HeaderContext* ctx) override;
        void exitHeader(marky::MarkdownParser::HeaderContext* ctx) override;

        void enterBlock(marky::MarkdownParser::BlockContext* ctx) override;
        void exitBlock(marky::MarkdownParser::BlockContext* ctx) override;

    private:
        ImDrawList* draw;

        ImVec2 blank_size { ImGui::CalcTextSize(" ") };
        ImVec2 cursor { ImGui::GetCursorScreenPos() };
        ImVec2 offset { 0,0 };
        ImU32 text_color = {ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_Text]) };
        ImVec4 clear_color;

        float row_distance_within_paragraph { 4 };
        float row_distance_between_paragraphs { 16 };

        int HTML_MaxHeaderLevel { 6 };
    };
}