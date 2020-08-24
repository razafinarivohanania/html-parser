#ifndef HTML_TOKEN
#define HTML_TOKEN

#include <string>
#include "../utils/StringUtils.h"

enum TokenType
{
    DOCTYPE,
    COMMENT,
    BEGIN_TAG,
    ORPHAN_TAG,
    END_TAG,
    ATTRIBUTE_NAME_WITH_VALUE,
    ATTRIBUTE_VALUE,
    ATTRIBUTE_NAME_WITHOUT_VALUE,
    TEXT
};

class HtmlToken
{
public:
    HtmlToken(TokenType type, std::string value);

    TokenType getType();
    std::string getTypeAsString();
    std::string getValue();
    void appendValue(const std::string value);
    std::string toString();

private:
    TokenType type;
    std::string value;
};

#endif