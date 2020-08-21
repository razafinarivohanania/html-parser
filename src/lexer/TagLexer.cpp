#include "TagLexer.h"

void TagLexer::process()
{
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

    std::string beginTagName = getBeginTagName();
    if (hasError())
    {
        return;
    }

    htmlCursor.skipSpacesFamily();

    if (htmlCursor.isSlashCharacter())
    {
        if (!htmlCursor.advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        if (!htmlCursor.isRightArrowCharacter())
        {
            setError(buildUnexpectedCharacterError('>'));
            return;
        }

        HtmlToken *htmlToken = new HtmlToken(TokenType::BEGIN_TAG, beginTagName);
        tokens.push_back(htmlToken);
        return;
    }

    //AttributeLexer attributeLexer;
}

std::string TagLexer::getBeginTagName()
{
    std::string beginTagName = "";

    if (StringUtils::containsCharacter(INVALID_BEGIN_CHARACTER__BEGIN_TAG, htmlCursor.getCharacter()))
    {
        setError(buildUnexpectedCharacterError());
        return "";
    }

    beginTagName.push_back(htmlCursor.getCharacter());

    while (true)
    {
        if (!htmlCursor.advance())
        {
            if (!htmlCursor.isRightArrowCharacter())
            {
                setError(HTML_NOT_ENDED_CORRECTLY);
                return "";
            }

            return beginTagName;
        }

        if (htmlCursor.isSpaceCharacterFamily() || htmlCursor.isSlashCharacter() || htmlCursor.isRightArrowCharacter())
        {
            return beginTagName;
        }

        if (StringUtils::containsCharacter(INVALID_MIDDLE_CHARACTER_TAG, htmlCursor.getCharacter()))
        {
            setError(buildUnexpectedCharacterError());
            return "";
        }

        beginTagName.push_back(htmlCursor.getCharacter());
    }
}

std::vector<HtmlToken *> TagLexer::getTokens()
{
    return tokens;
}