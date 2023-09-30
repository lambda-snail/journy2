
// Generated from .\Markdown.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "MarkdownVisitor.h"


namespace marky {

/**
 * This class provides an empty implementation of MarkdownVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MarkdownBaseVisitor : public MarkdownVisitor {
public:

  virtual std::any visitMarkdown(MarkdownParser::MarkdownContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(MarkdownParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRaw_stream(MarkdownParser::Raw_streamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitItalics_stream(MarkdownParser::Italics_streamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBold_stream(MarkdownParser::Bold_streamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCode_stream_inl(MarkdownParser::Code_stream_inlContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCode_stream_blk(MarkdownParser::Code_stream_blkContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitW_stream(MarkdownParser::W_streamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitHeader(MarkdownParser::HeaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParagraph(MarkdownParser::ParagraphContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace marky
