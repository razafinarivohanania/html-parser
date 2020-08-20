#include "HtmlToken.h"

HtmlToken::HtmlToken(TokenType type, std::string value)
{
    this->type = type;
    this->value = value;
}

TokenType HtmlToken::getType()
{
    return type;
}

std::string HtmlToken::getValue()
{
    return value;
}

std::string HtmlToken::toString()
{
    std::string typeAsString = typeToString();
    return "HtmlToken { type : " + typeAsString + ", value : " + value + "}";
}

std::string HtmlToken::typeToString()
{
    switch (type)
    {
    case DOCTYPE:
        return "DOCTYPE";
    case TAG_NAME:
        return "TAG_NAME";
    case ATTRIBUTE_NAME:
        return "ATTRIBUTE_NAME";
    case ATTRIBUTE_VALUE:
        return "ATTRIBUTE_VALUE";
    case TAG_CONTENT:
        return "TAG_CONTENT";
    case TAG_COMMENT:
        return "TAG_COMMENT";
    default:
        return "[unknown]";
    }
}