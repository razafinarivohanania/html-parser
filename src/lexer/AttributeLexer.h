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
    bool foundFromOrphanTag();

private:
    bool fromOphanTag;
    std::vector<HtmlToken *> tokens;

    std::string INVALID_ATTRIBUTE_NAME_CHARACTERS = "<>/";//TODO

    void process();
    std::string getAttributeName();
    std::string getAttributeValue();
};

#endif