#pragma once

#include "markdown/parser/MarkdownBaseListener.h"

#include <string>

namespace marky::backend::html
{
    class MarkdownToHtml : public marky::MarkdownBaseListener
    {
    public:
        std::string get_html();

        void enterMarkdown(MarkdownParser::MarkdownContext* context) override;
        void exitMarkdown(MarkdownParser::MarkdownContext* context) override;

        void enterHeader(MarkdownParser::HeaderContext* context) override;
        void exitHeader(MarkdownParser::HeaderContext* context) override;

        void enterParagraph(MarkdownParser::ParagraphContext* context) override;
        void exitParagraph(MarkdownParser::ParagraphContext* context) override;

        void enterItalics_stream(MarkdownParser::Italics_streamContext* context) override;
        void exitItalics_stream(MarkdownParser::Italics_streamContext* context) override;

        void enterCode_stream_inl(MarkdownParser::Code_stream_inlContext* context) override;
        void exitCode_stream_inl(MarkdownParser::Code_stream_inlContext* context) override;

        void enterCode_stream_blk(MarkdownParser::Code_stream_blkContext* context) override;
        void exitCode_stream_blk(MarkdownParser::Code_stream_blkContext* context) override;

        void enterBold_stream(MarkdownParser::Bold_streamContext* context) override;
        void exitBold_stream(MarkdownParser::Bold_streamContext* context) override;

        void visitTerminal(antlr4::tree::TerminalNode *) override;

        static constexpr int HTML_MaxHeaderLevel { 6 };
    private:
        std::vector<std::string> m_elements;
    };
}