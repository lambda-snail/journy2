#include "markdown/markdowntovector.h"
#include "markdown/parser/MarkdownLexer.h"
#include "ui/fonthelpers.h"

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
        ImFont* font = nullptr;
        switch(lvl)
        {
            case 1:
                font = journy::ui::fonts::FontPool::Roboto_Header1;
                break;
            case 2:
                font = journy::ui::fonts::FontPool::Roboto_Header2;
                break;
            default:
                font = journy::ui::fonts::FontPool::Roboto_Bold;
                break;
        }

        ImGui::PushFont(font);

        // This should probably be improved on later
        std::string h{};
//        for(auto const& token : ctx->raw_stream()->getTokens(marky::MarkdownLexer::WORD))
//        {
//            h += token->getText() + " ";
//        }

        auto const& tokens = ctx->raw_stream()->getTokens(marky::MarkdownLexer::WORD);
        for(int i { 0 }; i < tokens.size(); ++i)
        {
            h += tokens[i]->getText() + (i != tokens.size()-1 ? " " : "");
        }

        outline.push_back({ .header = h, .level = lvl });
    }
}

void journy::markdown::MarkdownToVector::exitHeader(marky::MarkdownParser::HeaderContext* ctx) {
    int lvl = static_cast<int>(ctx->HEADER_START().size());
    if(lvl <= HTML_MaxHeaderLevel)
    {
        ImGui::PopFont();
    }
}

void journy::markdown::MarkdownToVector::enterItalics_stream(marky::MarkdownParser::Italics_streamContext* ctx) {
    ImGui::PushFont(journy::ui::fonts::FontPool::Roboto_Italic);
}

void journy::markdown::MarkdownToVector::exitItalics_stream(marky::MarkdownParser::Italics_streamContext* ctx) {
    ImGui::PopFont();
}

void journy::markdown::MarkdownToVector::enterBold_stream(marky::MarkdownParser::Bold_streamContext *ctx) {
    ImGui::PushFont(journy::ui::fonts::FontPool::Roboto_Bold);
}

void journy::markdown::MarkdownToVector::exitBold_stream(marky::MarkdownParser::Bold_streamContext *ctx) {
    ImGui::PopFont();
}

std::vector<journy::markdown::MarkdownOutlineDescriptor> const* journy::markdown::MarkdownToVector::GetOutline() const {
    return &outline;
}

void journy::markdown::MarkdownToVector::enterMarkdown(marky::MarkdownParser::MarkdownContext *ctx) {
    outline.clear();
}
