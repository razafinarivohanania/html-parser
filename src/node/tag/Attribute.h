#ifndef NODE_ATTRIBUTE_H
#define NODE_ATTRIBUTE_H

#include <vector>
#include <string>

class Attribute
{
public:
    explicit Attribute();
    Attribute *setName(std::string name);
    Attribute *setValue(std::string value);
    Attribute *setNoValue(bool noValue);

    std::string getName();
    std::string getValue();

    std::string toHtml();

    static std::vector<Attribute *> parse(std::string rawAttributes);

private:
    std::string m_name;
    std::string m_value;
    bool m_noValue;

    static int const SEARCH_NAME = 0;
    static int const VALIDATE_NAME = 1;
    static int const SEARCH_VALUE = 2;
    static int const SEARCH_EQUALS = 3;
    static int const SEARCH_QUOT = 4;

    static bool isValidName(std::string &name);
};

#endif