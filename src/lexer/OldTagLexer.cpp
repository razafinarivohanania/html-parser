#include "OldTagLexer.h"

OldTagLexer::OldTagLexer(HtmlCursor &htmlCursor) : Lexer(htmlCursor)
{
    process();
}

void OldTagLexer::process()
{
    if (htmlCursor.endReached())
    {
        return;
    }

    if (getDoctype())
    {
        process();
        return;
    }

    if (false) {
        return;
    }

    // <
    if (!htmlCursor.isLeftArrowCharacter())
    {
        setError(buildUnexpectedCharacterError('<'));
        return;
    }

    if (!htmlCursor.advance())
    {
        setError(HTML_NOT_ENDED_CORRECTLY);
        return;
    }

    // <!
    if (htmlCursor.isExclamationPointCharacter())
    {
        if (!htmlCursor.advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        // <!-
        if (htmlCursor.isHyphenCharacter())
        {
            if (!htmlCursor.advance())
            {
                setError(HTML_NOT_ENDED_CORRECTLY);
                return;
            }

            // <!--
            if (htmlCursor.isHyphenCharacter())
            {
                if (!htmlCursor.advance())
                {
                    setError(HTML_NOT_ENDED_CORRECTLY);
                    return;
                }

                getComment();
                return;
            }
        }
        // <!D
        else if (htmlCursor.matchesIgnoreCaseCharacter('D'))
        {
            getDoctype();
            return;
        }

        setError(buildUnexpectedCharacterError());
        return;
    }

    // </
    if (htmlCursor.isSlashCharacter())
    {
        getEndTag();
        return;
    }

    std::string beginTagName = getBeginTagName();
    AttributeLexer attributeLexer(htmlCursor);
    if (!attributeLexer.isSuccess())
    {
        return;
    }

    TokenType tagTokenType = TokenType::ORPHAN_TAG;
    HtmlToken *token = new HtmlToken(tagTokenType, beginTagName);
    tokens.push_back(token);

    std::vector<HtmlToken *> attributeTokens = attributeLexer.getTokens();
    for (auto &attributeToken : attributeTokens)
    {
        tokens.push_back(attributeToken);
    }

    //TODO close tag
}

/**
 * Treat following syntaxes :
 * <!---->
 * <!-- -->
 * <!--x-->
 * <!-- x -->
 * <!--xx-->
 * <!-- xx -->
 **/
bool OldTagLexer::getComment()
{
    std::string beginComment = "<!--";
    if (htmlCursor.startsWith(beginComment, false))
    {
        htmlCursor.skipBlocs(beginComment.size());

        std::string endComment = "-->";
        Result result = htmlCursor.getStringBefore(endComment);
        if (result.success)
        {
            std::string comment = result.content;
            htmlCursor.skipBlocs(comment.size() + endComment.size());
            HtmlToken *htmlToken = new HtmlToken(TokenType::COMMENT, comment);
            tokens.push_back(htmlToken);
            return true;
        }
    }

    return false;
}

/**
 * Treat following syntaxes :
 * <!doctype html>
 * <!DOCTYPE html>
 * <!doctype   html>
 * <!DOCTYPE   html>
 * <!doctype html  >
 * <!DOCTYPE html  >
 * <!doctype    html  >
 * <!DOCTYPE    html  >
 **/
bool OldTagLexer::getDoctype()
{
    std::string doctype = "<!DOCTYPE";
    if (htmlCursor.startsWith(doctype, true))
    {
        htmlCursor.skipBlocs(doctype.size());
        htmlCursor.skipSpacesFamily();
        Result result = htmlCursor.getStringStarting("html", true);
        if (result.success)
        {
            std::string html = result.content;
            htmlCursor.skipBlocs(html.size());
            htmlCursor.skipSpacesFamily();
            if (htmlCursor.isRightArrowCharacter())
            {
                htmlCursor.advance();
                HtmlToken *htmlToken = new HtmlToken(TokenType::DOCTYPE, html);
                tokens.push_back(htmlToken);
                return true;
            }
        }
    }

    return false;
}

void OldTagLexer::getEndTag()
{
    // </

    if (!htmlCursor.advance())
    {
        setError(HTML_NOT_ENDED_CORRECTLY);
        return;
    }

    if (StringUtils::containsCharacter(INVALID_BEGIN_CHARACTER_TAG, htmlCursor.getCharacter()))
    {
        setError(buildUnexpectedCharacterError());
        return;
    }

    std::string tagName = "";
    bool spaceAlreadyFound = false;

    while (true)
    {
        if (!htmlCursor.advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        if (htmlCursor.isRightArrowCharacter())
        {
            break;
        }

        if (htmlCursor.isSpaceCharacterFamily())
        {
            if (spaceAlreadyFound)
            {
                setError(buildUnexpectedCharacterError());
                return;
            }

            htmlCursor.skipSpacesFamily();
            spaceAlreadyFound = true;
        }

        if (StringUtils::containsCharacter(INVALID_MIDDLE_CHARACTER_TAG, htmlCursor.getCharacter()))
        {
            setError(buildUnexpectedCharacterError());
            return;
        }
    }

    if (tagName.empty())
    {
        setError(buildUnexpectedCharacterError());
        return;
    }

    HtmlToken *htmlToken = new HtmlToken(TokenType::END_TAG, tagName);
    tokens.push_back(htmlToken);
}

std::string OldTagLexer::getBeginTagName()
{
    // <

    if (!htmlCursor.advance())
    {
        setError(HTML_NOT_ENDED_CORRECTLY);
        return "";
    }

    if (StringUtils::containsCharacter(INVALID_BEGIN_CHARACTER_TAG, htmlCursor.getCharacter()))
    {
        setError(buildUnexpectedCharacterError());
        return "";
    }

    std::string tagName = "";

    while (true)
    {
        if (!htmlCursor.advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return "";
        }

        // /
        if (htmlCursor.isSpaceCharacterFamily() || htmlCursor.isSlashCharacter() || htmlCursor.isRightArrowCharacter())
        {
            break;
        }

        tagName.push_back(htmlCursor.getCharacter());
    }

    if (tagName.empty())
    {
        setError(buildUnexpectedCharacterError());
        return "";
    }

    return tagName;
}

std::vector<HtmlToken *> OldTagLexer::getTokens()
{
    return tokens;
}