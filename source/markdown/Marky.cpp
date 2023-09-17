#include "markdown/Marky.h"

#include "markdown/parser/MarkdownListener.h"
#include "markdown/parser/MarkdownLexer.h"

void marky::Marky::process_markdown(marky::MarkdownListener* backend, std::string_view markdown) const {
    antlr4::ANTLRInputStream input(markdown);
    marky::MarkdownLexer lexer(&input);

    antlr4::CommonTokenStream tokens(&lexer);
    marky::MarkdownParser parser(&tokens);

    auto* tree = parser.markdown();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(backend, tree);
}
