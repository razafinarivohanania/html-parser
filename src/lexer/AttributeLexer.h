#ifndef ATTRIBUTE_LEXER_H
#define ATTRIBUTE_LEXER_H

#include <string>
#include <vector>
#include <iostream>

#include "Lexer.h"
#include "HtmlCursor.h"
#include "HtmlToken.h"
#include "Result.h"

class AttributeLexer : public Lexer
{
public:
    explicit AttributeLexer(HtmlCursor &htmlCursor);
    virtual std::vector<HtmlToken *> getTokens();
    bool foundFromOrphanTag();
    bool isSuccess();

private:
    bool success;
    bool fromOphanTag;
    std::vector<HtmlToken *> tokens;

    std::string INVALID_ATTRIBUTE_NAME_CHARACTERS = "<>/";//TODO

    void process();
    Result getAttributeName();
    Result getAttributeValue();
};

#endif