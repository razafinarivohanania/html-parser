#ifndef ATTRIBUTE_PARSER_H
#define ATTRIBUTE_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "./../node/tag/Attribute.h"

class AttributeParser
{
public:
    AttributeParser(std::string &rawAttributes);
    std::vector<Attribute *> getAttributes();

private:
    static int const SEARCH_NAME = 0;
    static int const VALIDATE_NAME = 1;
    static int const SEARCH_VALUE = 2;
    static int const SEARCH_EQUALS = 3;
    static int const SEARCH_QUOT = 4;

    std::vector<Attribute *> m_attributes;
    std::vector<Attribute *> parse(std::string &rawAttributes);
    bool isValidName(std::string &name);
    bool isSpace(char &character);
};

#endif