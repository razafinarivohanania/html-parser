#ifndef ATTRIBUTE_LEXER_H
#define ATTRIBUTE_LEXER_H

#include <string>
#include <vector>

#include "Lexer.h"
#include "HtmlToken.h"

class AttributeLexer : Lexer
{
public:
    AttributeLexer(const std::string &html, int &currentIndex);

    virtual std::vector<HtmlToken *> getTokens();

private:
    std::vector<HtmlToken *> tokens;

    void process();
};

#endif