#ifndef ATTRIBUTE_LEXER_H
#define ATTRIBUTE_LEXER_H

#include <string>
#include <vector>
#include <iostream>

#include "HtmlCursor.h"
#include "HtmlToken.h"
#include "Result.h"

class AttributeLexer
{
public:
    explicit AttributeLexer(HtmlCursor *htmlCursor);
    virtual std::vector<HtmlToken *> getTokens();
    bool isSuccess();

private:
    HtmlCursor *htmlCursor;
    bool success;
    std::vector<HtmlToken *> tokens;

    std::string INVALID_ATTRIBUTE_NAME_CHARACTERS = "<>/"; //TODO

    void process();
    Result getAttributeName();
    Result getAttributeValue();
};

#endif