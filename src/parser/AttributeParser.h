#ifndef ATTRIBUTE_PARSER_H
#define ATTRIBUTE_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "./../node/tag/Attribute.h"
#include "ActionParser.h"

enum Action
{
    SEARCH_NAME
};

class AttributeParser
{
public:
    AttributeParser(std::string &rawAttributes);
    std::vector<Attribute *> getAttributes();

private:
    char m_character;
    char m_quot;

    std::string m_name;
    std::string m_value;
    std::string m_invalidCharacters;

    std::vector<Attribute *> m_attributes;
    void parse(std::string &rawAttributes);
    bool isValidName();
    bool isQuotCharacter();
    bool isSpaceCharacter();

    ActionParser searchName();
    ActionParser searchEquals();
    ActionParser searchQuot();
    ActionParser searchValue();
    void reinitializeAttribute();
    ActionParser saveAttribute(bool noValue);
};

#endif