#ifndef HTML_LEXER_H
#define HTML_LEXER_H

#include <vector>

#include "HtmlCursor.h"
#include "HtmlToken.h"
#include "CommentLexer.h"
#include "DoctypeLexer.h"
#include "TagLexer.h"

class HtmlLexer
{
public:
    HtmlLexer(std::string *html);
    std::vector<HtmlToken *> getTokens();

private:
    std::vector<HtmlToken *> tokens;
    HtmlCursor *htmlCursor;

    void process();
    std::string getText();
};

#endif