#include "HtmlLexer.h"

HtmlLexer::HtmlLexer(std::string *html)
{
    htmlCursor = new HtmlCursor(html);
    process();
}

std::vector<HtmlToken *> HtmlLexer::getTokens()
{
    return tokens;
}

void HtmlLexer::process()
{
    if (htmlCursor->endReached())
    {
        return;
    }

    CommentLexer commentLexer(htmlCursor);
    if (commentLexer.isBeginTagFound())
    {
        if (commentLexer.isCommentFound())
        {
            tokens.push_back(commentLexer.getToken());
            process();
        }

        return;
    }

    DoctypeLexer doctypeLexer(htmlCursor);
    if (doctypeLexer.isSuccess())
    {
        tokens.push_back(doctypeLexer.getToken());
        process();
        return;
    }

    htmlCursor->setPosition(doctypeLexer.getInitialPosition());

    TagLexer tagLexer(htmlCursor);
    if (tagLexer.isSuccess())
    {
        for (auto &token : tagLexer.getTokens())
        {
            tokens.push_back(token);
        }

        process();
        return;
    }

    htmlCursor->setPosition(tagLexer.getInitialPosition());

    std::string text = getText();
    if (text.empty())
    {
        return;
    }

    tokens.push_back(new HtmlToken(TokenType::TEXT, text));
    process();
}

std::string HtmlLexer::getText()
{
    Result text = htmlCursor->getStringBefore("<");
    if (text.success)
    {
        htmlCursor->advance();
        return text.content;
    }

    return htmlCursor->getRestContent();
}