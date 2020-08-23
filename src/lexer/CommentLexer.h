#ifndef COMMENT_LEXER_H
#define COMMENT_LEXER_H

#include <vector>
#include "HtmlCursor.h"
#include "HtmlToken.h"

class CommentLexer
{
public:
    CommentLexer(HtmlCursor *htmlCursor);
    bool isBeginTagFound();
    bool isCommentFound();
    HtmlToken* getToken();

private:
    HtmlToken *token;
    HtmlCursor *htmlCursor;
    bool beginTagFound;
    bool commentFound;

    void process();
};

#endif