#ifndef ATTRIBUTE_LEXER_H
#define ATTRIBUTE_LEXER_H

#include <string>
#include <vector>

#include "Lexer.h"
#include "HtmlCursor.h"
#include "HtmlToken.h"

class AttributeLexer : public Lexer
{
public:
    explicit AttributeLexer(HtmlCursor &htmlCursor);
    virtual std::vector<HtmlToken *> getTokens();

private:
    std::vector<HtmlToken *> tokens;

    void process();
};

#endif