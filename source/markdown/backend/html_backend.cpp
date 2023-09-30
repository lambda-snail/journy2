#include "markdown/backend/html_backend.h"

#include <antlr4-runtime.h>
#include <numeric>

#include "markdown/parser/MarkdownLexer.h"
#include "markdown/parser/MarkdownParser.h"
#include "markdown/parser/MarkdownBaseListener.h"

std::string marky::backend::html::MarkdownToHtml::get_html() {
    std::string html;
    const int reserve_length = std::accumulate(
            m_elements.begin(),
            m_elements.end(),
            0,
            [](int a, std::string const& w) { return a + w.length(); });
    html.reserve(reserve_length);

    for(auto const& elm : m_elements)
    {
        html += elm;
    }

    return html;
}

void marky::backend::html::MarkdownToHtml::visitTerminal(antlr4::tree::TerminalNode* node) {
    auto token = node->getSymbol();
    switch(token->getType())
    {
        case MarkdownLexer::WORD:
            m_elements.emplace_back(node->getText());
            m_elements.emplace_back(" ");
    };
}

void marky::backend::html::MarkdownToHtml::enterParagraph(marky::MarkdownParser::ParagraphContext* context) {
    m_elements.emplace_back("<p>");
}

void marky::backend::html::MarkdownToHtml::exitParagraph(marky::MarkdownParser::ParagraphContext* context) {
    m_elements.emplace_back("</p>");
}

void marky::backend::html::MarkdownToHtml::enterMarkdown(marky::MarkdownParser::MarkdownContext* context) {
    m_elements.emplace_back("<div>");
}

void marky::backend::html::MarkdownToHtml::exitMarkdown(marky::MarkdownParser::MarkdownContext* context) {
    m_elements.emplace_back("</div>");
}

void marky::backend::html::MarkdownToHtml::enterHeader(marky::MarkdownParser::HeaderContext* context) {
    int lvl = static_cast<int>(context->HEADER_START().size());
    if(lvl <= HTML_MaxHeaderLevel)
    {
        m_elements.emplace_back("<h" + std::to_string(lvl) + ">");
    }
    else
    {
        m_elements.emplace_back("<p>");
    }
}

void marky::backend::html::MarkdownToHtml::exitHeader(marky::MarkdownParser::HeaderContext* context) {
    int lvl = static_cast<int>(context->HEADER_START().size());
    if(lvl <= HTML_MaxHeaderLevel)
    {
        m_elements.emplace_back("</h" + std::to_string(lvl) + ">");
    }
    else
    {
        m_elements.emplace_back("</p>");
    }
}

void marky::backend::html::MarkdownToHtml::enterItalics_stream(marky::MarkdownParser::Italics_streamContext* context) {
    m_elements.emplace_back("<i>");
}

void marky::backend::html::MarkdownToHtml::exitItalics_stream(marky::MarkdownParser::Italics_streamContext* context) {
    m_elements.emplace_back("</i>");
}

void marky::backend::html::MarkdownToHtml::enterBold_stream(marky::MarkdownParser::Bold_streamContext* context) {
    m_elements.emplace_back("<b>");
}

void marky::backend::html::MarkdownToHtml::exitBold_stream(marky::MarkdownParser::Bold_streamContext* context) {
    m_elements.emplace_back("</b>");
}

void marky::backend::html::MarkdownToHtml::enterCode_stream_inl(MarkdownParser::Code_stream_inlContext* context)  {
    m_elements.emplace_back("<code>");
}

void marky::backend::html::MarkdownToHtml::exitCode_stream_inl(MarkdownParser::Code_stream_inlContext* context)  {
    m_elements.emplace_back("</code>");
}

void marky::backend::html::MarkdownToHtml::enterCode_stream_blk(MarkdownParser::Code_stream_blkContext* context)  {
    m_elements.emplace_back("<code>");
}

void marky::backend::html::MarkdownToHtml::exitCode_stream_blk(MarkdownParser::Code_stream_blkContext* context)  {
    m_elements.emplace_back("</code>");
}