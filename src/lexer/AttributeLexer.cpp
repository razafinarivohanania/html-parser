#include "AttributeLexer.h"

AttributeLexer::AttributeLexer(HtmlCursor &htmlCursor) : Lexer(htmlCursor)
{
    fromOphanTag = false;
    process();
}

void AttributeLexer::process()
{
    htmlCursor.skipSpacesFamily();

    if (htmlCursor.endReached() || htmlCursor.isSlashCharacter() || htmlCursor.isRightArrowCharacter())
    {
        return;
    }

    std::string attributeName = getAttributeName();
    if (hasError())
    {
        return;
    }

    htmlCursor.skipSpacesFamily();

    if (htmlCursor.isEqualsCharacter())
    {
        htmlCursor.skipSpacesFamily();

        if (!htmlCursor.advance())
        {
            setError(buildUnexpectedCharacterError());
            return;
        }

        htmlCursor.skipSpacesFamily();

        std::string attributeValue = getAttributeValue();
        if (hasError())
        {
            return;
        }

        HtmlToken *nameToken = new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, attributeName);
        HtmlToken *valueToken = new HtmlToken(TokenType::ATTRIBUTE_VALUE, attributeValue);

        tokens.push_back(nameToken);
        tokens.push_back(valueToken);
    }
    else
    {
        HtmlToken *token = new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, attributeName);
        tokens.push_back(token);
    }

    htmlCursor.skipSpacesFamily();

    //Retrieve others attribute name and value
    process();
}

std::string AttributeLexer::getAttributeName()
{
    std::string attributeName = "";

    if (StringUtils::containsCharacter(INVALID_ATTRIBUTE_NAME_CHARACTERS, htmlCursor.getCharacter()))
    {
        setError(buildUnexpectedCharacterError());
        return "";
    }

    attributeName.push_back(htmlCursor.getCharacter());

    while (true)
    {
        if (!htmlCursor.advance() ||
            htmlCursor.isEqualsCharacter() ||
            htmlCursor.isSpaceCharacterFamily() ||
            htmlCursor.isSlashCharacter() ||
            htmlCursor.isRightArrowCharacter())
        {
            break;
        }

        if (StringUtils::containsCharacter(INVALID_ATTRIBUTE_NAME_CHARACTERS, htmlCursor.getCharacter()))
        {
            setError(buildUnexpectedCharacterError());
            return "";
        }

        attributeName.push_back(htmlCursor.getCharacter());
    }

    if (attributeName.empty())
    {
        setError(buildUnexpectedCharacterError());
    }

    return attributeName;
}

std::string AttributeLexer::getAttributeValue()
{
    bool isQuote = htmlCursor.isQuote();

    if (!isQuote && !htmlCursor.isDoubleQuote())
    {
        setError(buildUnexpectedCharacterError());
        return "";
    }

    std::string attributeValue = "";

    while (true)
    {
        if (!htmlCursor.advance())
        {
            setError(buildUnexpectedCharacterError());
            return "";
        }

        if ((htmlCursor.isQuote() && isQuote) || (htmlCursor.isDoubleQuote() && !isQuote))
        {
            htmlCursor.advance();
            return attributeValue;
        }
    }
}

std::vector<HtmlToken *> AttributeLexer::getTokens()
{
    return tokens;
}