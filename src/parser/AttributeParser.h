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
    std::vector<Attribute *> m_attributes;
    std::vector<Attribute *> parse(std::string &rawAttributes);
    bool isValidName();
    bool isQuotCharacter();
    bool isSpaceCharacter();

    std::string m_name;
    std::string m_value;
    std::string m_invalidCharacters;
    char m_character;
    char m_quot;

    ActionParser searchName();
    ActionParser searchQuot();
    ActionParser searchValue();
    void reinitializeAttribute();
    ActionParser saveAttribute(std::vector<Attribute *> &attributes, bool noValue);
};

#endif