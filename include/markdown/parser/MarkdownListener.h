
// Generated from .\Markdown.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "MarkdownParser.h"


namespace marky {

/**
 * This interface defines an abstract listener for a parse tree produced by MarkdownParser.
 */
class  MarkdownListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterMarkdown(MarkdownParser::MarkdownContext *ctx) = 0;
  virtual void exitMarkdown(MarkdownParser::MarkdownContext *ctx) = 0;

  virtual void enterBlock(MarkdownParser::BlockContext *ctx) = 0;
  virtual void exitBlock(MarkdownParser::BlockContext *ctx) = 0;

  virtual void enterRaw_stream(MarkdownParser::Raw_streamContext *ctx) = 0;
  virtual void exitRaw_stream(MarkdownParser::Raw_streamContext *ctx) = 0;

  virtual void enterItalics_stream(MarkdownParser::Italics_streamContext *ctx) = 0;
  virtual void exitItalics_stream(MarkdownParser::Italics_streamContext *ctx) = 0;

  virtual void enterBold_stream(MarkdownParser::Bold_streamContext *ctx) = 0;
  virtual void exitBold_stream(MarkdownParser::Bold_streamContext *ctx) = 0;

  virtual void enterCode_stream_inl(MarkdownParser::Code_stream_inlContext *ctx) = 0;
  virtual void exitCode_stream_inl(MarkdownParser::Code_stream_inlContext *ctx) = 0;

  virtual void enterCode_stream_blk(MarkdownParser::Code_stream_blkContext *ctx) = 0;
  virtual void exitCode_stream_blk(MarkdownParser::Code_stream_blkContext *ctx) = 0;

  virtual void enterW_stream(MarkdownParser::W_streamContext *ctx) = 0;
  virtual void exitW_stream(MarkdownParser::W_streamContext *ctx) = 0;

  virtual void enterHeader(MarkdownParser::HeaderContext *ctx) = 0;
  virtual void exitHeader(MarkdownParser::HeaderContext *ctx) = 0;

  virtual void enterParagraph(MarkdownParser::ParagraphContext *ctx) = 0;
  virtual void exitParagraph(MarkdownParser::ParagraphContext *ctx) = 0;


};

}  // namespace marky
