#include "markdown/markdowntovector.h"
#include "markdown/parser/MarkdownLexer.h"
#include "ui/fonthelpers.h"

#include <iostream>

void journy::markdown::MarkdownToVector::exitBlock(marky::MarkdownParser::BlockContext *ctx) {
    MarkdownBaseListener::exitBlock(ctx);
}

void journy::markdown::MarkdownToVector::enterBlock(marky::MarkdownParser::BlockContext *ctx) {
    offset.x = 0;
    offset.y += row_distance_between_paragraphs + blank_size.y;
}

void journy::markdown::MarkdownToVector::visitTerminal(antlr4::tree::TerminalNode *node)
{
    auto token = node->getSymbol();
    if(token->getType() != marky::MarkdownLexer::WORD)
    {
       return;
    };

    auto const& str = token->getText();

    float window_width = ImGui::GetWindowSize().x;
    float length = ImGui::CalcTextSize(str.c_str()).x;

    if (offset.x + length > window_width)
    {
        offset.x = 0;
        offset.y += row_distance_within_paragraph + blank_size.y;
    }

    ImVec2 draw_pos { cursor.x + offset.x, cursor.y + offset.y };

    draw->AddText(draw_pos, text_color, str.c_str());
    offset.x += length;

    draw->AddText(draw_pos, text_color, " ");
    offset.x += blank_size.x;
}

void journy::markdown::MarkdownToVector::enterHeader(marky::MarkdownParser::HeaderContext* ctx) {
    int lvl = static_cast<int>(ctx->HEADER_START().size());
    if(lvl <= HTML_MaxHeaderLevel)
    {
        ImGui::PushFont(journy::ui::fonts::FontPool::Bold);
    }
}

void journy::markdown::MarkdownToVector::exitHeader(marky::MarkdownParser::HeaderContext *ctx) {
    ImGui::PopFont();
}
