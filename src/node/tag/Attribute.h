#ifndef NODE_ATTRIBUTE_H
#define NODE_ATTRIBUTE_H

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

private:
    std::string m_name;
    std::string m_value;
    bool m_noValue;
};

#endif