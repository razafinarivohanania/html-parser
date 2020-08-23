#ifndef OLD_TAG_LEXER_H
#define OLD_TAG_LEXER_H

#include <vector>

#include "Lexer.h"
#include "HtmlCursor.h"
#include "HtmlToken.h"
#include "AttributeLexer.h"
#include "CommentLexer.h"

class OldTagLexer : public Lexer
{
public:
    OldTagLexer(HtmlCursor &htmlCursor);
    virtual std::vector<HtmlToken *> getTokens();

private:
    std::vector<HtmlToken *> tokens;

    const std::string INVALID_BEGIN_CHARACTER_TAG = ".-\\/!|<>=\"'"; //TODO to complete
    const std::string INVALID_MIDDLE_CHARACTER_TAG = "\\/!|<>=\"'"; //TODO to complete

    void process();
    bool getComment();
    bool getDoctype();
    void getEndTag();
    std::string getBeginTagName();
};

#endif