#ifndef ATTRIBUTE_LEXER_H
#define ATTRIBUTE_LEXER_H

#include <string>
#include <vector>

#include "Lexer.h"
#include "HtmlCursor.h"
#include "HtmlToken.h"

class AttributeLexer : Lexer
{
public:
    virtual std::vector<HtmlToken *> getTokens();

private:
    HtmlCursor htmlCursor;
    std::vector<HtmlToken *> tokens;

    void process();
};

#endif