#include "AttributeParser.h"

AttributeParser::AttributeParser(std::string &rawAttributes)
{
    m_attributes = parse(rawAttributes);
}

std::vector<Attribute *> AttributeParser::parse(std::string &rawAttributes)
{
    std::vector<Attribute *> attributes;
    if (rawAttributes == "")
    {
        return attributes;
    }

    int action = SEARCH_NAME;
    std::string name = "";
    std::string value = "";
    char quot = '"';

    for (auto &character : rawAttributes)
    {
        switch (action)
        {
        case SEARCH_VALUE:
            if (character == quot)
            {
                Attribute *attribute = new Attribute();
                attributes.push_back(attribute->setName(name)->setValue(value));
                name = "";
                value = "";
                action = SEARCH_NAME;
                continue;
            }

            value += character;
            continue;
        case SEARCH_QUOT:
            if (character == '"' || character == '\'')
            {
                quot = character;
                action = SEARCH_VALUE;
                continue;
            }

            name = "";
            value = "";
            action = SEARCH_NAME;
            continue;
        case SEARCH_NAME:
            if (character == '=')
            {
                if (isValidName(name))
                {
                    action = SEARCH_QUOT;
                    continue;
                }

                name = "";
                value = "";
                action = SEARCH_NAME;
                continue;
            }

            if (character == ' ' || character == '\n' || character == '\r')
            {
                continue;
            }

            name += character;
            std::cout << name << std::endl;
            continue;
        }
    }

    return attributes;
}

std::vector<Attribute *> AttributeParser::getAttributes()
{
    return m_attributes;
}

bool AttributeParser::isSpace(char &character)
{
    return character == ' ' ||
           character == '\n' ||
           character == '\t' ||
           character == '\r';
}

bool AttributeParser::isValidName(std::string &name)
{
    if (name == "")
    {
        return false;
    }

    std::string invalidCharacters = "²&~\"#'{([|`\\^)°]+=}/*^¨$£¤%<>?,;.:!§ ";

    for (auto &character : name)
    {
        for (auto &invalidCharacter : invalidCharacters)
        {
            if (character == invalidCharacter)
            {
                return false;
            }
        }
    }

    return true;
}