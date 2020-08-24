#ifndef DOCTYPE_LEXER_H
#define DOCTYPE_LEXER_H

#include "HtmlCursor.h"
#include "HtmlToken.h"

class DoctypeLexer
{
public:
    DoctypeLexer(HtmlCursor *htmlCursor);
    HtmlToken *getToken();
    int getInitialPosition();
    bool isSuccess();

private:
    HtmlCursor *htmlCursor;
    int initalPosition;
    bool success;
    HtmlToken *token;
    void process();
};

#endif