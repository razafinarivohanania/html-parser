#include "DoctypeLexer.h"

DoctypeLexer::DoctypeLexer(HtmlCursor &htmlCursor) : htmlCursor(htmlCursor)
{
    token = nullptr;
    success = false;
    initalPosition = htmlCursor.getPosition();
    process();
}

HtmlToken *DoctypeLexer::getToken()
{
    return token;
}

bool DoctypeLexer::isSuccess()
{
    return success;
}

int DoctypeLexer::getInitialPosition()
{
    return initalPosition;
}

void DoctypeLexer::process()
{
    std::string doctype = "<!DOCTYPE";
    if (!htmlCursor.startsWith(doctype, true))
    {
        return;
    }

    htmlCursor.skipBlocs(doctype.size());
    htmlCursor.skipSpacesFamily();
    Result result = htmlCursor.getStringStarting("html", true);
    if (!result.success)
    {
        return;
    }

    std::string html = result.content;
    htmlCursor.skipBlocs(html.size());
    htmlCursor.skipSpacesFamily();
    if (!htmlCursor.isRightArrowCharacter())
    {
        return;
    }

    htmlCursor.advance();
    token = new HtmlToken(TokenType::DOCTYPE, html);
}