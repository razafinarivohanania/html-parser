#include "TagLexer.h"

TagLexer::TagLexer(const std::string &html, int currentIndex) : Lexer(html)
{
    setCurrentIndex(currentIndex);
}

std::vector<HtmlToken *> TagLexer::getTokens()
{
    return tokens;
}