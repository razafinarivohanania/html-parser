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

void HtmlToken::appendValue(const std::string value)
{
    int size = value.size();
    for (int i = 0; i < size; i++) {
        this->value.push_back(value[i]);
    }
}

std::string HtmlToken::toString()
{
    std::string typeAsString = getTypeAsString();
    return "HtmlToken { type : " + typeAsString + ", value : " + StringUtils::encodeNewLines(value) + " }";
}

std::string HtmlToken::getTypeAsString()
{
    switch (type)
    {
    case DOCTYPE:
        return "DOCTYPE";
    case BEGIN_TAG:
        return "BEGIN_TAG";
    case ORPHAN_TAG:
        return "ORPHAN_TAG";
    case END_TAG:
        return "END_TAG";
    case ATTRIBUTE_NAME_WITH_VALUE:
        return "ATTRIBUTE_NAME_WITH_VALUE";
    case ATTRIBUTE_VALUE:
        return "ATTRIBUTE_VALUE";
    case ATTRIBUTE_NAME_WITHOUT_VALUE:
        return "ATTRIBUTE_NAME_WITHOUT_VALUE";
    case TEXT:
        return "TEXT";
    case COMMENT:
        return "COMMENT";
    default:
        return "[unknown]";
    }
}