#ifndef HTML_TOKEN
#define HTML_TOKEN

#include <string>

enum TokenType
{
    DOCTYPE,
    TAG_COMMENT,
    TAG_NAME,
    ATTRIBUTE_NAME,
    ATTRIBUTE_VALUE,
    TAG_CONTENT
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