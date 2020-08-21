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
    case TAG:
        return "TAG";
    case ATTRIBUTE_NAME:
        return "ATTRIBUTE_NAME";
    case ATTRIBUTE_VALUE:
        return "ATTRIBUTE_VALUE";
    case TEXT:
        return "TEXT";
    case COMMENT:
        return "COMMENT";
    default:
        return "[unknown]";
    }
}