#include "TagLexer.h"

TagLexer::TagLexer(HtmlCursor &htmlCursor) : Lexer(htmlCursor)
{
    process();
}

void TagLexer::process()
{
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

    getBeginTag();

    if (hasError())
    {
        return;
    }

    // Here begin tag skip when found state and not again handle end tag symbols
    // /
    if (htmlCursor.isSlashCharacter())
    {
        if (!htmlCursor.advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        // />
        if (!htmlCursor.isRightArrowCharacter())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        // Because of ending tag we don't retrieve attributes, so skip
        return;
    }

    htmlCursor.skipSpacesFamily();

    AttributeLexer attributeLexer(htmlCursor);
    if (attributeLexer.hasError()) {
        return;
    }

    std::vector<HtmlToken *> attributeTokens = attributeLexer.getTokens();
    for (auto &attributeToken : attributeTokens)
    {
        tokens.push_back(attributeToken);
    }

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

void TagLexer::getDoctype()
{
    // Already <!D

    std::string octype = "OCTYPE";
    int size = octype.size();

    for (int i = 0; i < size; i++)
    {
        if (!htmlCursor.advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        char expectedCharacter = octype[i];
        if (!htmlCursor.matchesIgnoreCaseCharacter(expectedCharacter))
        {
            setError(buildUnexpectedCharacterError(expectedCharacter));
            return;
        }
    }

    // Already <!DOCTYPE

    htmlCursor.skipSpacesFamily();

    std::string html = "html";
    size = html.size();

    for (int i = 0; i < size; i++)
    {
        if (!htmlCursor.advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        char expectedCharacter = html[i];
        if (!htmlCursor.matchesIgnoreCaseCharacter(expectedCharacter))
        {
            setError(buildUnexpectedCharacterError(expectedCharacter));
            return;
        }
    }

    HtmlToken *htmlToken = new HtmlToken(TokenType::DOCTYPE, html);
    tokens.push_back(htmlToken);
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

void TagLexer::getBeginTag()
{
    // <

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
    bool isOrphan = false;

    while (true)
    {
        if (!htmlCursor.advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        // /
        if (htmlCursor.isSlashCharacter())
        {
            if (!htmlCursor.advance())
            {
                setError(HTML_NOT_ENDED_CORRECTLY);
                return;
            }

            // />
            if (!htmlCursor.isRightArrowCharacter())
            {
                setError(buildUnexpectedCharacterError());
                return;
            }

            isOrphan = true;
            break;
        }

        if (htmlCursor.isSpaceCharacterFamily())
        {
            htmlCursor.skipSpacesFamily();
            break;
        }

        if (htmlCursor.isRightArrowCharacter())
        {
            break;
        }

        tagName.push_back(htmlCursor.getCharacter());
    }

    if (tagName.empty())
    {
        setError(buildUnexpectedCharacterError());
        return;
    }

    TokenType tokenType = isOrphan ? TokenType::ORPHAN_TAG : TokenType::BEGIN_TAG;
    HtmlToken *htmlToken = new HtmlToken(tokenType, tagName);
    tokens.push_back(htmlToken);
}

std::vector<HtmlToken *> TagLexer::getTokens()
{
    return tokens;
}