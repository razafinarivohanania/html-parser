#include "TagLexer.h"

TagLexer::TagLexer(const std::string &html, int &currentIndex) : Lexer(html)
{
    setCurrentIndex(currentIndex);
    process();
}

void TagLexer::process()
{
    if (!isLeftArrowCharacter())
    {
        setError(buildUnexpectedCharacterError('<'));
        return;
    }

    if (!advance())
    {
        setError(HTML_NOT_ENDED_CORRECTLY);
        return;
    }

    std::string beginTagName = getBeginTagName();
    if (hasError())
    {
        return;
    }

    skipSpacesFamily();

    if (isSlashCharacter())
    {
        if (!advance())
        {
            setError(HTML_NOT_ENDED_CORRECTLY);
            return;
        }

        if (!isRightArrowCharacter())
        {
            setError(buildUnexpectedCharacterError('>'));
            return;
        }

        HtmlToken *htmlToken = new HtmlToken(TokenType::BEGIN_TAG, beginTagName);
        tokens.push_back(htmlToken);
        return;
    }

    std::string html = getHtml();
    int currentIndex = getCurrentIndex();
    AttributeLexer attributeLexer(html, currentIndex);
}

std::string TagLexer::getBeginTagName()
{
    std::string beginTagName = "";

    if (StringUtils::containsCharacter(INVALID_BEGIN_CHARACTER__BEGIN_TAG, getCurrentCharacter()))
    {
        setError(buildUnexpectedCharacterError());
        return "";
    }

    beginTagName.push_back(getCurrentCharacter());

    while (true)
    {
        if (!advance())
        {
            if (!isRightArrowCharacter())
            {
                setError(HTML_NOT_ENDED_CORRECTLY);
                return "";
            }

            return beginTagName;
        }

        if (isSpaceCharacterFamily() || isSlashCharacter() || isRightArrowCharacter())
        {
            return beginTagName;
        }

        if (StringUtils::containsCharacter(INVALID_MIDDLE_CHARACTER_TAG, getCurrentCharacter()))
        {
            setError(buildUnexpectedCharacterError());
            return "";
        }

        beginTagName.push_back(getCurrentCharacter());
    }
}

std::vector<HtmlToken *> TagLexer::getTokens()
{
    return tokens;
}