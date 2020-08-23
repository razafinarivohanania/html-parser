#ifndef TAG_LEXER_H
#define TAG_LEXER_H

#include <vector>

#include "Lexer.h"
#include "HtmlCursor.h"
#include "HtmlToken.h"
#include "AttributeLexer.h"

class TagLexer : public Lexer
{
public:
    TagLexer(HtmlCursor &htmlCursor);
    virtual std::vector<HtmlToken *> getTokens();

private:
    std::vector<HtmlToken *> tokens;

    const std::string INVALID_BEGIN_CHARACTER_TAG = ".-\\/!|<>=\"'"; //TODO to complete
    const std::string INVALID_MIDDLE_CHARACTER_TAG = "\\/!|<>=\"'";         //TODO to complete

    void process();
    void getComment();
    bool getDoctype();
    void getEndTag();
    std::string getBeginTagName();
};

#endif