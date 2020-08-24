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
        std::cout << "AAAAAAAAAAAAAAAAAA" << std::endl;
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

    getTextToken(text);
    process();
}

void HtmlLexer::getTextToken(const std::string &text)
{
    if (tokens.size() > 0)
    {
        HtmlToken *lastToken = tokens.at(tokens.size() - 1);
        if (lastToken->getType() == TokenType::TEXT)
        {
            lastToken->appendValue(text);
            return;
        }
    }

    tokens.push_back(new HtmlToken(TokenType::TEXT, text));
}

std::string HtmlLexer::getText()
{
    Result result = htmlCursor->getStringBefore("<");
    if (!result.success)
    {
        std::string restContent = htmlCursor->getRestContent();
        htmlCursor->skipBlocs(restContent.size());
        return restContent;
    }

    if (!result.content.empty())
    {
        htmlCursor->skipBlocs(result.content.size());
        return result.content;
    }

    std::string text = "<";
    if (!htmlCursor->advance())
    {
        return text;
    }

    return text + getText();
}

HtmlLexer::~HtmlLexer()
{
    delete htmlCursor;
}