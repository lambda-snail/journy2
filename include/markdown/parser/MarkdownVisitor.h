
// Generated from .\Markdown.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "MarkdownParser.h"


namespace marky {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by MarkdownParser.
 */
class  MarkdownVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MarkdownParser.
   */
    virtual std::any visitMarkdown(MarkdownParser::MarkdownContext *context) = 0;

    virtual std::any visitBlock(MarkdownParser::BlockContext *context) = 0;

    virtual std::any visitRaw_stream(MarkdownParser::Raw_streamContext *context) = 0;

    virtual std::any visitItalics_stream(MarkdownParser::Italics_streamContext *context) = 0;

    virtual std::any visitBold_stream(MarkdownParser::Bold_streamContext *context) = 0;

    virtual std::any visitCode_stream_inl(MarkdownParser::Code_stream_inlContext *context) = 0;

    virtual std::any visitCode_stream_blk(MarkdownParser::Code_stream_blkContext *context) = 0;

    virtual std::any visitW_stream(MarkdownParser::W_streamContext *context) = 0;

    virtual std::any visitHeader(MarkdownParser::HeaderContext *context) = 0;

    virtual std::any visitParagraph(MarkdownParser::ParagraphContext *context) = 0;


};

}  // namespace marky
