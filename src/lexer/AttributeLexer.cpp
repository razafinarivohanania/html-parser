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

        Result result = getAttributeValue();
        if (!result.success)
        {
            return;
        }

        HtmlToken *nameToken = new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, attributeName);
        HtmlToken *valueToken = new HtmlToken(TokenType::ATTRIBUTE_VALUE, result.content);

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
        if (!htmlCursor.advance() || htmlCursor.isOneOfCharacters("= />"))
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

/**
 * Treat syntax
 * ''
 * 'x'
 * 'xx'
 * ""
 * "x"
 * "xx"
 * */
Result AttributeLexer::getAttributeValue()
{
    bool isQuote = htmlCursor.isQuote();
    if (isQuote || htmlCursor.isDoubleQuote())
    {
        htmlCursor.advance();
        Result result = htmlCursor.getStringBefore(isQuote ? "'" : "\"");
        if (result.success)
        {
            htmlCursor.skipBlocs(result.content.size() + 1);
            htmlCursor.skipSpacesFamily();
            return result;
        }
    }

    Result result;
    result.success = false;
    result.content = "";
    return result;
}

std::vector<HtmlToken *> AttributeLexer::getTokens()
{
    return tokens;
}