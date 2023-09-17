
// Generated from .\Markdown.g4 by ANTLR 4.13.0


#include "markdown/parser/MarkdownLexer.h"

using namespace marky;
using namespace antlr4;

namespace {

struct MarkdownLexerStaticData final {
  MarkdownLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MarkdownLexerStaticData(const MarkdownLexerStaticData&) = delete;
  MarkdownLexerStaticData(MarkdownLexerStaticData&&) = delete;
  MarkdownLexerStaticData& operator=(const MarkdownLexerStaticData&) = delete;
  MarkdownLexerStaticData& operator=(MarkdownLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag markdownlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
MarkdownLexerStaticData *markdownlexerLexerStaticData = nullptr;

void markdownlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (markdownlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(markdownlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MarkdownLexerStaticData>(
    std::vector<std::string>{
      "ALNUM", "ESCAPE_CHAR", "HEADER_START", "BLANK", "EOL", "WHITESPACE", 
      "WORD", "BOLD_ENVELOPE", "ITALICS_ENVELOPE", "CODE_ENVELOPE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,9,55,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,
  	2,7,7,7,2,8,7,8,2,9,7,9,1,0,1,0,1,0,1,0,3,0,26,8,0,1,1,1,1,1,2,1,2,1,
  	3,1,3,1,3,1,3,1,4,1,4,1,4,3,4,39,8,4,1,5,1,5,3,5,43,8,5,1,6,4,6,46,8,
  	6,11,6,12,6,47,1,7,1,7,1,8,1,8,1,9,1,9,0,0,10,1,0,3,1,5,2,7,3,9,4,11,
  	5,13,6,15,7,17,8,19,9,1,0,2,6,0,9,10,12,13,32,32,35,35,42,42,95,96,2,
  	0,9,9,32,32,57,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,
  	0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,1,25,1,0,0,
  	0,3,27,1,0,0,0,5,29,1,0,0,0,7,31,1,0,0,0,9,38,1,0,0,0,11,42,1,0,0,0,13,
  	45,1,0,0,0,15,49,1,0,0,0,17,51,1,0,0,0,19,53,1,0,0,0,21,26,8,0,0,0,22,
  	23,3,3,1,0,23,24,5,96,0,0,24,26,1,0,0,0,25,21,1,0,0,0,25,22,1,0,0,0,26,
  	2,1,0,0,0,27,28,5,92,0,0,28,4,1,0,0,0,29,30,5,35,0,0,30,6,1,0,0,0,31,
  	32,7,1,0,0,32,33,1,0,0,0,33,34,6,3,0,0,34,8,1,0,0,0,35,39,5,10,0,0,36,
  	37,5,13,0,0,37,39,5,12,0,0,38,35,1,0,0,0,38,36,1,0,0,0,39,10,1,0,0,0,
  	40,43,3,9,4,0,41,43,3,7,3,0,42,40,1,0,0,0,42,41,1,0,0,0,43,12,1,0,0,0,
  	44,46,3,1,0,0,45,44,1,0,0,0,46,47,1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,
  	48,14,1,0,0,0,49,50,5,42,0,0,50,16,1,0,0,0,51,52,5,95,0,0,52,18,1,0,0,
  	0,53,54,5,96,0,0,54,20,1,0,0,0,5,0,25,38,42,47,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  markdownlexerLexerStaticData = staticData.release();
}

}

MarkdownLexer::MarkdownLexer(CharStream *input) : Lexer(input) {
  MarkdownLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *markdownlexerLexerStaticData->atn, markdownlexerLexerStaticData->decisionToDFA, markdownlexerLexerStaticData->sharedContextCache);
}

MarkdownLexer::~MarkdownLexer() {
  delete _interpreter;
}

std::string MarkdownLexer::getGrammarFileName() const {
  return "Markdown.g4";
}

const std::vector<std::string>& MarkdownLexer::getRuleNames() const {
  return markdownlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& MarkdownLexer::getChannelNames() const {
  return markdownlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& MarkdownLexer::getModeNames() const {
  return markdownlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& MarkdownLexer::getVocabulary() const {
  return markdownlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MarkdownLexer::getSerializedATN() const {
  return markdownlexerLexerStaticData->serializedATN;
}

const atn::ATN& MarkdownLexer::getATN() const {
  return *markdownlexerLexerStaticData->atn;
}




void MarkdownLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  markdownlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(markdownlexerLexerOnceFlag, markdownlexerLexerInitialize);
#endif
}
