#include "AttributeLexer.h"

AttributeLexer::AttributeLexer(HtmlCursor &htmlCursor) : Lexer(htmlCursor)
{
    fromOphanTag = false;
    success = true;
    process();
}

bool AttributeLexer::isSuccess()
{
    return success;
}

void AttributeLexer::process()
{
    htmlCursor.skipSpacesFamily();

    if (htmlCursor.endReached() || htmlCursor.isSlashCharacter() || htmlCursor.isRightArrowCharacter())
    {
        return;
    }

    Result attributeName = getAttributeName();
    if (!attributeName.success)
    {
        success = false;
        return;
    }

    htmlCursor.skipSpacesFamily();

    if (htmlCursor.isEqualsCharacter())
    {
        htmlCursor.skipSpacesFamily();

        if (!htmlCursor.advance())
        {
            success = false;
            return;
        }

        htmlCursor.skipSpacesFamily();

        Result attributeValue = getAttributeValue();
        if (!attributeValue.success)
        {
            success = false;
            return;
        }

        HtmlToken *nameToken = new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, attributeName.content);
        HtmlToken *valueToken = new HtmlToken(TokenType::ATTRIBUTE_VALUE, attributeValue.content);

        tokens.push_back(nameToken);
        tokens.push_back(valueToken);
    }
    else
    {
        HtmlToken *token = new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, attributeName.content);
        tokens.push_back(token);
    }

    htmlCursor.skipSpacesFamily();

    //Retrieve others attribute name and value
    process();
}

Result AttributeLexer::getAttributeName()
{
    std::string attributeName = "";

    Result result;
    result.success = false;
    result.content = "";

    if (StringUtils::containsCharacter(INVALID_ATTRIBUTE_NAME_CHARACTERS, htmlCursor.getCharacter()))
    {
        return result;
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
            return result;
        }

        attributeName.push_back(htmlCursor.getCharacter());
    }

    result.success = true;
    result.content = attributeName;
    return result;
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