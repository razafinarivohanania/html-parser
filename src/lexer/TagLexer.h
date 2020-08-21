#ifndef TAG_LEXER_H
#define TAG_LEXER_H

#include "Lexer.h"
#include <vector>

class TagLexer : Lexer
{
public:
    explicit TagLexer(const std::string &html, int currentIndex);

    virtual std::vector<HtmlToken *> getTokens();

private:
    std::vector<HtmlToken *> tokens;
};

#endif