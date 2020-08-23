#ifndef HTML_TOKEN
#define HTML_TOKEN

#include <string>

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
    std::string getValue();
    std::string toString();
private:
    TokenType type;
    std::string value;

    std::string typeToString();
};

#endif