#include "markdown/markdowntovector.h"
#include "markdown/parser/MarkdownLexer.h"

void journy::markdown::MarkdownToVector::exitBlock(marky::MarkdownParser::BlockContext *ctx) {
    MarkdownBaseListener::exitBlock(ctx);
}

void journy::markdown::MarkdownToVector::enterBlock(marky::MarkdownParser::BlockContext *ctx) {
    MarkdownBaseListener::enterBlock(ctx);
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
        offset.y += row_distance_in_paragraph + blank_size.y;
    }

    ImVec2 draw_pos { cursor.x + offset.x, cursor.y + offset.y };

    draw->AddText(draw_pos, color, str.c_str());
    offset.x += length;

    draw->AddText(draw_pos, color, " ");
    offset.x += blank_size.x;
}
