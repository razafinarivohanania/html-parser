#include "TagLexer.h"

TagLexer::TagLexer(HtmlCursor &htmlCursor) : Lexer(htmlCursor)
{
    process();
}

void TagLexer::process()
{
    htmlCursor.skipSpacesFamily();

    if (htmlCursor.endReached())
    {
        return;
    }

    if (getDoctype()) {
        process();
    }

    if (true) {
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
    if (attributeLexer.hasError())
    {
        return;
    }

    bool foundFromOrphanTag = attributeLexer.foundFromOrphanTag();
    TokenType tagTokenType = foundFromOrphanTag ? TokenType::ORPHAN_TAG : TokenType::BEGIN_TAG;
    HtmlToken *token = new HtmlToken(tagTokenType, beginTagName);
    tokens.push_back(token);

    std::vector<HtmlToken *> attributeTokens = attributeLexer.getTokens();
    for (auto &attributeToken : attributeTokens)
    {
        tokens.push_back(attributeToken);
    }

    //TODO close tag
}

void TagLexer::getComment()
{
    // <!--

    std::string comment = "";
    while (true)
    {
        if (!htmlCursor.advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        // -
        if (htmlCursor.isHyphenCharacter())
        {
            if (!htmlCursor.advance())
            {
                setError(HTML_NOT_ENDED_CORRECTLY);
                return;
            }

            // --
            if (htmlCursor.isHyphenCharacter())
            {
                if (!htmlCursor.advance())
                {
                    setError(HTML_NOT_ENDED_CORRECTLY);
                    return;
                }

                // -->
                if (htmlCursor.isRightArrowCharacter())
                {
                    break;
                }
            }
        }

        comment.push_back(htmlCursor.getCharacter());
    }

    HtmlToken *htmlToken = new HtmlToken(TokenType::COMMENT, comment);
    tokens.push_back(htmlToken);
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
bool TagLexer::getDoctype()
{
    if (htmlCursor.skipIfFound("<!DOCTYPE", true))
    {
        htmlCursor.skipSpacesFamily();
        std::string html = htmlCursor.skipAndGetStringFound("html", true);
        if (!html.empty())
        {
            htmlCursor.skipSpacesFamily();
            if (htmlCursor.isRightArrowCharacter())
            {
                HtmlToken *htmlToken = new HtmlToken(TokenType::DOCTYPE, html);
                tokens.push_back(htmlToken);
                return true;
            }
        }
    }

    return false;
}

void TagLexer::getEndTag()
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

std::string TagLexer::getBeginTagName()
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

std::vector<HtmlToken *> TagLexer::getTokens()
{
    return tokens;
}

bool AttributeLexer::foundFromOrphanTag()
{
    return fromOphanTag;
}