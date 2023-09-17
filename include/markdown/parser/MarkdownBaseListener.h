
// Generated from .\Markdown.g4 by ANTLR 4.13.0

#pragma once


#include "antlr4-runtime.h"
#include "MarkdownListener.h"


namespace marky {

/**
 * This class provides an empty implementation of MarkdownListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  MarkdownBaseListener : public MarkdownListener {
public:

  virtual void enterMarkdown(MarkdownParser::MarkdownContext * /*ctx*/) override { }
  virtual void exitMarkdown(MarkdownParser::MarkdownContext * /*ctx*/) override { }

  virtual void enterBlock(MarkdownParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(MarkdownParser::BlockContext * /*ctx*/) override { }

  virtual void enterRaw_stream(MarkdownParser::Raw_streamContext * /*ctx*/) override { }
  virtual void exitRaw_stream(MarkdownParser::Raw_streamContext * /*ctx*/) override { }

  virtual void enterItalics_stream(MarkdownParser::Italics_streamContext * /*ctx*/) override { }
  virtual void exitItalics_stream(MarkdownParser::Italics_streamContext * /*ctx*/) override { }

  virtual void enterBold_stream(MarkdownParser::Bold_streamContext * /*ctx*/) override { }
  virtual void exitBold_stream(MarkdownParser::Bold_streamContext * /*ctx*/) override { }

  virtual void enterCode_stream_inl(MarkdownParser::Code_stream_inlContext * /*ctx*/) override { }
  virtual void exitCode_stream_inl(MarkdownParser::Code_stream_inlContext * /*ctx*/) override { }

  virtual void enterCode_stream_blk(MarkdownParser::Code_stream_blkContext * /*ctx*/) override { }
  virtual void exitCode_stream_blk(MarkdownParser::Code_stream_blkContext * /*ctx*/) override { }

  virtual void enterW_stream(MarkdownParser::W_streamContext * /*ctx*/) override { }
  virtual void exitW_stream(MarkdownParser::W_streamContext * /*ctx*/) override { }

  virtual void enterHeader(MarkdownParser::HeaderContext * /*ctx*/) override { }
  virtual void exitHeader(MarkdownParser::HeaderContext * /*ctx*/) override { }

  virtual void enterParagraph(MarkdownParser::ParagraphContext * /*ctx*/) override { }
  virtual void exitParagraph(MarkdownParser::ParagraphContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace marky
