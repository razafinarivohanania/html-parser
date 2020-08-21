#include "AttributeLexer.h"

AttributeLexer::AttributeLexer(HtmlCursor &htmlCursor) : Lexer(htmlCursor)
{
}

void AttributeLexer::process()
{
}

std::vector<HtmlToken *> AttributeLexer::getTokens()
{
    return tokens;
}