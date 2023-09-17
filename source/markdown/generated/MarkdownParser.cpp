
// Generated from .\Markdown.g4 by ANTLR 4.13.0


#include "markdown/parser/MarkdownListener.h"
#include "markdown/parser/MarkdownVisitor.h"

#include "markdown/parser/MarkdownParser.h"


using namespace antlrcpp;
using namespace marky;

using namespace antlr4;

namespace {

struct MarkdownParserStaticData final {
  MarkdownParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MarkdownParserStaticData(const MarkdownParserStaticData&) = delete;
  MarkdownParserStaticData(MarkdownParserStaticData&&) = delete;
  MarkdownParserStaticData& operator=(const MarkdownParserStaticData&) = delete;
  MarkdownParserStaticData& operator=(MarkdownParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag markdownParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
MarkdownParserStaticData *markdownParserStaticData = nullptr;

void markdownParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (markdownParserStaticData != nullptr) {
    return;
  }
#else
  assert(markdownParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MarkdownParserStaticData>(
    std::vector<std::string>{
      "markdown", "block", "raw_stream", "italics_stream", "bold_stream", 
      "code_stream_inl", "code_stream_blk", "w_stream", "header", "paragraph"
    },
    std::vector<std::string>{
      "", "'\\'", "'#'", "", "", "", "", "'*'", "'_'", "'`'"
    },
    std::vector<std::string>{
      "", "ESCAPE_CHAR", "HEADER_START", "BLANK", "EOL", "WHITESPACE", "WORD", 
      "BOLD_ENVELOPE", "ITALICS_ENVELOPE", "CODE_ENVELOPE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,9,127,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,2,8,7,8,2,9,7,9,1,0,5,0,22,8,0,10,0,12,0,25,9,0,1,0,5,0,28,8,0,10,
  	0,12,0,31,9,0,1,1,1,1,1,1,3,1,36,8,1,1,1,4,1,39,8,1,11,1,12,1,40,1,1,
  	3,1,44,8,1,1,2,1,2,5,2,48,8,2,10,2,12,2,51,9,2,4,2,53,8,2,11,2,12,2,54,
  	1,3,1,3,5,3,59,8,3,10,3,12,3,62,9,3,1,3,1,3,1,3,5,3,67,8,3,10,3,12,3,
  	70,9,3,1,4,1,4,5,4,74,8,4,10,4,12,4,77,9,4,1,4,1,4,1,4,5,4,82,8,4,10,
  	4,12,4,85,9,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,5,7,
  	100,8,7,10,7,12,7,103,9,7,4,7,105,8,7,11,7,12,7,106,1,7,3,7,110,8,7,1,
  	8,4,8,113,8,8,11,8,12,8,114,1,8,5,8,118,8,8,10,8,12,8,121,9,8,1,8,1,8,
  	1,9,1,9,1,9,1,106,0,10,0,2,4,6,8,10,12,14,16,18,0,0,136,0,23,1,0,0,0,
  	2,35,1,0,0,0,4,52,1,0,0,0,6,56,1,0,0,0,8,71,1,0,0,0,10,86,1,0,0,0,12,
  	90,1,0,0,0,14,109,1,0,0,0,16,112,1,0,0,0,18,124,1,0,0,0,20,22,5,4,0,0,
  	21,20,1,0,0,0,22,25,1,0,0,0,23,21,1,0,0,0,23,24,1,0,0,0,24,29,1,0,0,0,
  	25,23,1,0,0,0,26,28,3,2,1,0,27,26,1,0,0,0,28,31,1,0,0,0,29,27,1,0,0,0,
  	29,30,1,0,0,0,30,1,1,0,0,0,31,29,1,0,0,0,32,36,3,12,6,0,33,36,3,18,9,
  	0,34,36,3,16,8,0,35,32,1,0,0,0,35,33,1,0,0,0,35,34,1,0,0,0,36,43,1,0,
  	0,0,37,39,5,4,0,0,38,37,1,0,0,0,39,40,1,0,0,0,40,38,1,0,0,0,40,41,1,0,
  	0,0,41,44,1,0,0,0,42,44,5,0,0,1,43,38,1,0,0,0,43,42,1,0,0,0,44,3,1,0,
  	0,0,45,49,5,6,0,0,46,48,5,3,0,0,47,46,1,0,0,0,48,51,1,0,0,0,49,47,1,0,
  	0,0,49,50,1,0,0,0,50,53,1,0,0,0,51,49,1,0,0,0,52,45,1,0,0,0,53,54,1,0,
  	0,0,54,52,1,0,0,0,54,55,1,0,0,0,55,5,1,0,0,0,56,60,5,8,0,0,57,59,5,3,
  	0,0,58,57,1,0,0,0,59,62,1,0,0,0,60,58,1,0,0,0,60,61,1,0,0,0,61,63,1,0,
  	0,0,62,60,1,0,0,0,63,64,3,14,7,0,64,68,5,8,0,0,65,67,5,3,0,0,66,65,1,
  	0,0,0,67,70,1,0,0,0,68,66,1,0,0,0,68,69,1,0,0,0,69,7,1,0,0,0,70,68,1,
  	0,0,0,71,75,5,7,0,0,72,74,5,3,0,0,73,72,1,0,0,0,74,77,1,0,0,0,75,73,1,
  	0,0,0,75,76,1,0,0,0,76,78,1,0,0,0,77,75,1,0,0,0,78,79,3,14,7,0,79,83,
  	5,7,0,0,80,82,5,3,0,0,81,80,1,0,0,0,82,85,1,0,0,0,83,81,1,0,0,0,83,84,
  	1,0,0,0,84,9,1,0,0,0,85,83,1,0,0,0,86,87,5,9,0,0,87,88,3,14,7,0,88,89,
  	5,9,0,0,89,11,1,0,0,0,90,91,5,9,0,0,91,92,3,14,7,0,92,93,5,9,0,0,93,13,
  	1,0,0,0,94,105,3,6,3,0,95,105,3,8,4,0,96,105,3,10,5,0,97,101,5,6,0,0,
  	98,100,5,3,0,0,99,98,1,0,0,0,100,103,1,0,0,0,101,99,1,0,0,0,101,102,1,
  	0,0,0,102,105,1,0,0,0,103,101,1,0,0,0,104,94,1,0,0,0,104,95,1,0,0,0,104,
  	96,1,0,0,0,104,97,1,0,0,0,105,106,1,0,0,0,106,107,1,0,0,0,106,104,1,0,
  	0,0,107,110,1,0,0,0,108,110,5,6,0,0,109,104,1,0,0,0,109,108,1,0,0,0,110,
  	15,1,0,0,0,111,113,5,2,0,0,112,111,1,0,0,0,113,114,1,0,0,0,114,112,1,
  	0,0,0,114,115,1,0,0,0,115,119,1,0,0,0,116,118,5,3,0,0,117,116,1,0,0,0,
  	118,121,1,0,0,0,119,117,1,0,0,0,119,120,1,0,0,0,120,122,1,0,0,0,121,119,
  	1,0,0,0,122,123,3,4,2,0,123,17,1,0,0,0,124,125,3,14,7,0,125,19,1,0,0,
  	0,17,23,29,35,40,43,49,54,60,68,75,83,101,104,106,109,114,119
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  markdownParserStaticData = staticData.release();
}

}

MarkdownParser::MarkdownParser(TokenStream *input) : MarkdownParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MarkdownParser::MarkdownParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MarkdownParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *markdownParserStaticData->atn, markdownParserStaticData->decisionToDFA, markdownParserStaticData->sharedContextCache, options);
}

MarkdownParser::~MarkdownParser() {
  delete _interpreter;
}

const atn::ATN& MarkdownParser::getATN() const {
  return *markdownParserStaticData->atn;
}

std::string MarkdownParser::getGrammarFileName() const {
  return "Markdown.g4";
}

const std::vector<std::string>& MarkdownParser::getRuleNames() const {
  return markdownParserStaticData->ruleNames;
}

const dfa::Vocabulary& MarkdownParser::getVocabulary() const {
  return markdownParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MarkdownParser::getSerializedATN() const {
  return markdownParserStaticData->serializedATN;
}


//----------------- MarkdownContext ------------------------------------------------------------------

MarkdownParser::MarkdownContext::MarkdownContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MarkdownParser::MarkdownContext::EOL() {
  return getTokens(MarkdownParser::EOL);
}

tree::TerminalNode* MarkdownParser::MarkdownContext::EOL(size_t i) {
  return getToken(MarkdownParser::EOL, i);
}

std::vector<MarkdownParser::BlockContext *> MarkdownParser::MarkdownContext::block() {
  return getRuleContexts<MarkdownParser::BlockContext>();
}

MarkdownParser::BlockContext* MarkdownParser::MarkdownContext::block(size_t i) {
  return getRuleContext<MarkdownParser::BlockContext>(i);
}


size_t MarkdownParser::MarkdownContext::getRuleIndex() const {
  return MarkdownParser::RuleMarkdown;
}

void MarkdownParser::MarkdownContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMarkdown(this);
}

void MarkdownParser::MarkdownContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMarkdown(this);
}


std::any MarkdownParser::MarkdownContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitMarkdown(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::MarkdownContext* MarkdownParser::markdown() {
  MarkdownContext *_localctx = _tracker.createInstance<MarkdownContext>(_ctx, getState());
  enterRule(_localctx, 0, MarkdownParser::RuleMarkdown);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MarkdownParser::EOL) {
      setState(20);
      match(MarkdownParser::EOL);
      setState(25);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(29);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 964) != 0)) {
      setState(26);
      block();
      setState(31);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

MarkdownParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MarkdownParser::Code_stream_blkContext* MarkdownParser::BlockContext::code_stream_blk() {
  return getRuleContext<MarkdownParser::Code_stream_blkContext>(0);
}

MarkdownParser::ParagraphContext* MarkdownParser::BlockContext::paragraph() {
  return getRuleContext<MarkdownParser::ParagraphContext>(0);
}

MarkdownParser::HeaderContext* MarkdownParser::BlockContext::header() {
  return getRuleContext<MarkdownParser::HeaderContext>(0);
}

tree::TerminalNode* MarkdownParser::BlockContext::EOF() {
  return getToken(MarkdownParser::EOF, 0);
}

std::vector<tree::TerminalNode *> MarkdownParser::BlockContext::EOL() {
  return getTokens(MarkdownParser::EOL);
}

tree::TerminalNode* MarkdownParser::BlockContext::EOL(size_t i) {
  return getToken(MarkdownParser::EOL, i);
}


size_t MarkdownParser::BlockContext::getRuleIndex() const {
  return MarkdownParser::RuleBlock;
}

void MarkdownParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void MarkdownParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any MarkdownParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::BlockContext* MarkdownParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 2, MarkdownParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(35);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(32);
      code_stream_blk();
      break;
    }

    case 2: {
      setState(33);
      paragraph();
      break;
    }

    case 3: {
      setState(34);
      header();
      break;
    }

    default:
      break;
    }
    setState(43);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MarkdownParser::EOL: {
        setState(38); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(37);
          match(MarkdownParser::EOL);
          setState(40); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == MarkdownParser::EOL);
        break;
      }

      case MarkdownParser::EOF: {
        setState(42);
        match(MarkdownParser::EOF);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Raw_streamContext ------------------------------------------------------------------

MarkdownParser::Raw_streamContext::Raw_streamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MarkdownParser::Raw_streamContext::WORD() {
  return getTokens(MarkdownParser::WORD);
}

tree::TerminalNode* MarkdownParser::Raw_streamContext::WORD(size_t i) {
  return getToken(MarkdownParser::WORD, i);
}

std::vector<tree::TerminalNode *> MarkdownParser::Raw_streamContext::BLANK() {
  return getTokens(MarkdownParser::BLANK);
}

tree::TerminalNode* MarkdownParser::Raw_streamContext::BLANK(size_t i) {
  return getToken(MarkdownParser::BLANK, i);
}


size_t MarkdownParser::Raw_streamContext::getRuleIndex() const {
  return MarkdownParser::RuleRaw_stream;
}

void MarkdownParser::Raw_streamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRaw_stream(this);
}

void MarkdownParser::Raw_streamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRaw_stream(this);
}


std::any MarkdownParser::Raw_streamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitRaw_stream(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::Raw_streamContext* MarkdownParser::raw_stream() {
  Raw_streamContext *_localctx = _tracker.createInstance<Raw_streamContext>(_ctx, getState());
  enterRule(_localctx, 4, MarkdownParser::RuleRaw_stream);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(45);
      match(MarkdownParser::WORD);
      setState(49);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MarkdownParser::BLANK) {
        setState(46);
        match(MarkdownParser::BLANK);
        setState(51);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(54); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == MarkdownParser::WORD);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Italics_streamContext ------------------------------------------------------------------

MarkdownParser::Italics_streamContext::Italics_streamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MarkdownParser::Italics_streamContext::ITALICS_ENVELOPE() {
  return getTokens(MarkdownParser::ITALICS_ENVELOPE);
}

tree::TerminalNode* MarkdownParser::Italics_streamContext::ITALICS_ENVELOPE(size_t i) {
  return getToken(MarkdownParser::ITALICS_ENVELOPE, i);
}

MarkdownParser::W_streamContext* MarkdownParser::Italics_streamContext::w_stream() {
  return getRuleContext<MarkdownParser::W_streamContext>(0);
}

std::vector<tree::TerminalNode *> MarkdownParser::Italics_streamContext::BLANK() {
  return getTokens(MarkdownParser::BLANK);
}

tree::TerminalNode* MarkdownParser::Italics_streamContext::BLANK(size_t i) {
  return getToken(MarkdownParser::BLANK, i);
}


size_t MarkdownParser::Italics_streamContext::getRuleIndex() const {
  return MarkdownParser::RuleItalics_stream;
}

void MarkdownParser::Italics_streamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterItalics_stream(this);
}

void MarkdownParser::Italics_streamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitItalics_stream(this);
}


std::any MarkdownParser::Italics_streamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitItalics_stream(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::Italics_streamContext* MarkdownParser::italics_stream() {
  Italics_streamContext *_localctx = _tracker.createInstance<Italics_streamContext>(_ctx, getState());
  enterRule(_localctx, 6, MarkdownParser::RuleItalics_stream);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    match(MarkdownParser::ITALICS_ENVELOPE);
    setState(60);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MarkdownParser::BLANK) {
      setState(57);
      match(MarkdownParser::BLANK);
      setState(62);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(63);
    w_stream();
    setState(64);
    match(MarkdownParser::ITALICS_ENVELOPE);
    setState(68);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MarkdownParser::BLANK) {
      setState(65);
      match(MarkdownParser::BLANK);
      setState(70);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bold_streamContext ------------------------------------------------------------------

MarkdownParser::Bold_streamContext::Bold_streamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MarkdownParser::Bold_streamContext::BOLD_ENVELOPE() {
  return getTokens(MarkdownParser::BOLD_ENVELOPE);
}

tree::TerminalNode* MarkdownParser::Bold_streamContext::BOLD_ENVELOPE(size_t i) {
  return getToken(MarkdownParser::BOLD_ENVELOPE, i);
}

MarkdownParser::W_streamContext* MarkdownParser::Bold_streamContext::w_stream() {
  return getRuleContext<MarkdownParser::W_streamContext>(0);
}

std::vector<tree::TerminalNode *> MarkdownParser::Bold_streamContext::BLANK() {
  return getTokens(MarkdownParser::BLANK);
}

tree::TerminalNode* MarkdownParser::Bold_streamContext::BLANK(size_t i) {
  return getToken(MarkdownParser::BLANK, i);
}


size_t MarkdownParser::Bold_streamContext::getRuleIndex() const {
  return MarkdownParser::RuleBold_stream;
}

void MarkdownParser::Bold_streamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBold_stream(this);
}

void MarkdownParser::Bold_streamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBold_stream(this);
}


std::any MarkdownParser::Bold_streamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitBold_stream(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::Bold_streamContext* MarkdownParser::bold_stream() {
  Bold_streamContext *_localctx = _tracker.createInstance<Bold_streamContext>(_ctx, getState());
  enterRule(_localctx, 8, MarkdownParser::RuleBold_stream);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(MarkdownParser::BOLD_ENVELOPE);
    setState(75);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MarkdownParser::BLANK) {
      setState(72);
      match(MarkdownParser::BLANK);
      setState(77);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(78);
    w_stream();
    setState(79);
    match(MarkdownParser::BOLD_ENVELOPE);
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MarkdownParser::BLANK) {
      setState(80);
      match(MarkdownParser::BLANK);
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Code_stream_inlContext ------------------------------------------------------------------

MarkdownParser::Code_stream_inlContext::Code_stream_inlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MarkdownParser::Code_stream_inlContext::CODE_ENVELOPE() {
  return getTokens(MarkdownParser::CODE_ENVELOPE);
}

tree::TerminalNode* MarkdownParser::Code_stream_inlContext::CODE_ENVELOPE(size_t i) {
  return getToken(MarkdownParser::CODE_ENVELOPE, i);
}

MarkdownParser::W_streamContext* MarkdownParser::Code_stream_inlContext::w_stream() {
  return getRuleContext<MarkdownParser::W_streamContext>(0);
}


size_t MarkdownParser::Code_stream_inlContext::getRuleIndex() const {
  return MarkdownParser::RuleCode_stream_inl;
}

void MarkdownParser::Code_stream_inlContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCode_stream_inl(this);
}

void MarkdownParser::Code_stream_inlContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCode_stream_inl(this);
}


std::any MarkdownParser::Code_stream_inlContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitCode_stream_inl(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::Code_stream_inlContext* MarkdownParser::code_stream_inl() {
  Code_stream_inlContext *_localctx = _tracker.createInstance<Code_stream_inlContext>(_ctx, getState());
  enterRule(_localctx, 10, MarkdownParser::RuleCode_stream_inl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(MarkdownParser::CODE_ENVELOPE);
    setState(87);
    w_stream();
    setState(88);
    match(MarkdownParser::CODE_ENVELOPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Code_stream_blkContext ------------------------------------------------------------------

MarkdownParser::Code_stream_blkContext::Code_stream_blkContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MarkdownParser::Code_stream_blkContext::CODE_ENVELOPE() {
  return getTokens(MarkdownParser::CODE_ENVELOPE);
}

tree::TerminalNode* MarkdownParser::Code_stream_blkContext::CODE_ENVELOPE(size_t i) {
  return getToken(MarkdownParser::CODE_ENVELOPE, i);
}

MarkdownParser::W_streamContext* MarkdownParser::Code_stream_blkContext::w_stream() {
  return getRuleContext<MarkdownParser::W_streamContext>(0);
}


size_t MarkdownParser::Code_stream_blkContext::getRuleIndex() const {
  return MarkdownParser::RuleCode_stream_blk;
}

void MarkdownParser::Code_stream_blkContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCode_stream_blk(this);
}

void MarkdownParser::Code_stream_blkContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCode_stream_blk(this);
}


std::any MarkdownParser::Code_stream_blkContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitCode_stream_blk(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::Code_stream_blkContext* MarkdownParser::code_stream_blk() {
  Code_stream_blkContext *_localctx = _tracker.createInstance<Code_stream_blkContext>(_ctx, getState());
  enterRule(_localctx, 12, MarkdownParser::RuleCode_stream_blk);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    match(MarkdownParser::CODE_ENVELOPE);
    setState(91);
    w_stream();
    setState(92);
    match(MarkdownParser::CODE_ENVELOPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- W_streamContext ------------------------------------------------------------------

MarkdownParser::W_streamContext::W_streamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MarkdownParser::Italics_streamContext *> MarkdownParser::W_streamContext::italics_stream() {
  return getRuleContexts<MarkdownParser::Italics_streamContext>();
}

MarkdownParser::Italics_streamContext* MarkdownParser::W_streamContext::italics_stream(size_t i) {
  return getRuleContext<MarkdownParser::Italics_streamContext>(i);
}

std::vector<MarkdownParser::Bold_streamContext *> MarkdownParser::W_streamContext::bold_stream() {
  return getRuleContexts<MarkdownParser::Bold_streamContext>();
}

MarkdownParser::Bold_streamContext* MarkdownParser::W_streamContext::bold_stream(size_t i) {
  return getRuleContext<MarkdownParser::Bold_streamContext>(i);
}

std::vector<MarkdownParser::Code_stream_inlContext *> MarkdownParser::W_streamContext::code_stream_inl() {
  return getRuleContexts<MarkdownParser::Code_stream_inlContext>();
}

MarkdownParser::Code_stream_inlContext* MarkdownParser::W_streamContext::code_stream_inl(size_t i) {
  return getRuleContext<MarkdownParser::Code_stream_inlContext>(i);
}

std::vector<tree::TerminalNode *> MarkdownParser::W_streamContext::WORD() {
  return getTokens(MarkdownParser::WORD);
}

tree::TerminalNode* MarkdownParser::W_streamContext::WORD(size_t i) {
  return getToken(MarkdownParser::WORD, i);
}

std::vector<tree::TerminalNode *> MarkdownParser::W_streamContext::BLANK() {
  return getTokens(MarkdownParser::BLANK);
}

tree::TerminalNode* MarkdownParser::W_streamContext::BLANK(size_t i) {
  return getToken(MarkdownParser::BLANK, i);
}


size_t MarkdownParser::W_streamContext::getRuleIndex() const {
  return MarkdownParser::RuleW_stream;
}

void MarkdownParser::W_streamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterW_stream(this);
}

void MarkdownParser::W_streamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitW_stream(this);
}


std::any MarkdownParser::W_streamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitW_stream(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::W_streamContext* MarkdownParser::w_stream() {
  W_streamContext *_localctx = _tracker.createInstance<W_streamContext>(_ctx, getState());
  enterRule(_localctx, 14, MarkdownParser::RuleW_stream);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(109);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(104); 
      _errHandler->sync(this);
      alt = 1 + 1;
      do {
        switch (alt) {
          case 1 + 1: {
                setState(104);
                _errHandler->sync(this);
                switch (_input->LA(1)) {
                  case MarkdownParser::ITALICS_ENVELOPE: {
                    setState(94);
                    italics_stream();
                    break;
                  }

                  case MarkdownParser::BOLD_ENVELOPE: {
                    setState(95);
                    bold_stream();
                    break;
                  }

                  case MarkdownParser::CODE_ENVELOPE: {
                    setState(96);
                    code_stream_inl();
                    break;
                  }

                  case MarkdownParser::WORD: {
                    setState(97);
                    match(MarkdownParser::WORD);
                    setState(101);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                    while (_la == MarkdownParser::BLANK) {
                      setState(98);
                      match(MarkdownParser::BLANK);
                      setState(103);
                      _errHandler->sync(this);
                      _la = _input->LA(1);
                    }
                    break;
                  }

                default:
                  throw NoViableAltException(this);
                }
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(106); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
      } while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(108);
      match(MarkdownParser::WORD);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HeaderContext ------------------------------------------------------------------

MarkdownParser::HeaderContext::HeaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MarkdownParser::Raw_streamContext* MarkdownParser::HeaderContext::raw_stream() {
  return getRuleContext<MarkdownParser::Raw_streamContext>(0);
}

std::vector<tree::TerminalNode *> MarkdownParser::HeaderContext::HEADER_START() {
  return getTokens(MarkdownParser::HEADER_START);
}

tree::TerminalNode* MarkdownParser::HeaderContext::HEADER_START(size_t i) {
  return getToken(MarkdownParser::HEADER_START, i);
}

std::vector<tree::TerminalNode *> MarkdownParser::HeaderContext::BLANK() {
  return getTokens(MarkdownParser::BLANK);
}

tree::TerminalNode* MarkdownParser::HeaderContext::BLANK(size_t i) {
  return getToken(MarkdownParser::BLANK, i);
}


size_t MarkdownParser::HeaderContext::getRuleIndex() const {
  return MarkdownParser::RuleHeader;
}

void MarkdownParser::HeaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHeader(this);
}

void MarkdownParser::HeaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHeader(this);
}


std::any MarkdownParser::HeaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitHeader(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::HeaderContext* MarkdownParser::header() {
  HeaderContext *_localctx = _tracker.createInstance<HeaderContext>(_ctx, getState());
  enterRule(_localctx, 16, MarkdownParser::RuleHeader);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(112); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(111);
      match(MarkdownParser::HEADER_START);
      setState(114); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == MarkdownParser::HEADER_START);
    setState(119);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MarkdownParser::BLANK) {
      setState(116);
      match(MarkdownParser::BLANK);
      setState(121);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(122);
    raw_stream();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParagraphContext ------------------------------------------------------------------

MarkdownParser::ParagraphContext::ParagraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MarkdownParser::W_streamContext* MarkdownParser::ParagraphContext::w_stream() {
  return getRuleContext<MarkdownParser::W_streamContext>(0);
}


size_t MarkdownParser::ParagraphContext::getRuleIndex() const {
  return MarkdownParser::RuleParagraph;
}

void MarkdownParser::ParagraphContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParagraph(this);
}

void MarkdownParser::ParagraphContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MarkdownListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParagraph(this);
}


std::any MarkdownParser::ParagraphContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MarkdownVisitor*>(visitor))
    return parserVisitor->visitParagraph(this);
  else
    return visitor->visitChildren(this);
}

MarkdownParser::ParagraphContext* MarkdownParser::paragraph() {
  ParagraphContext *_localctx = _tracker.createInstance<ParagraphContext>(_ctx, getState());
  enterRule(_localctx, 18, MarkdownParser::RuleParagraph);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    w_stream();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void MarkdownParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  markdownParserInitialize();
#else
  ::antlr4::internal::call_once(markdownParserOnceFlag, markdownParserInitialize);
#endif
}
