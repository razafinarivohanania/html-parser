#include "Attribute.h"

Attribute::Attribute() : m_name(""),
                         m_value(""),
                         m_noValue(false)
{
}

Attribute *Attribute::setName(std::string name)
{
    m_name = name;
    return this;
}

Attribute *Attribute::setValue(std::string value)
{
    m_value = value;
    return this;
}

Attribute *Attribute::setNoValue(bool noValue)
{
    m_noValue = noValue;
    return this;
}

std::string Attribute::toHtml()
{
    if (m_name == "")
    {
        return "";
    }

    if (m_noValue)
    {
        return m_name;
    }

    return m_name + "=\"" + m_value + "\"";
}

std::string Attribute::getName()
{
    return m_name;
}

std::string Attribute::getValue()
{
    return m_value;
}

std::vector<Attribute *> Attribute::parse(std::string rawAttributes)
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
        if (action == SEARCH_VALUE)
        {
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
        }

        if (action == SEARCH_QUOT)
        {
            if (character == '\'' || character == '\"')
            {
                quot = character;
                value = "";
                action = SEARCH_VALUE;
                continue;
            }

            name = "";
            action = SEARCH_NAME;
            continue;
        }

        if (action == SEARCH_EQUALS)
        {
            if (character == '=')
            {
                action = SEARCH_QUOT;
                continue;
            }

            Attribute *attribute = new Attribute();
            attributes.push_back(attribute->setName(name)->setNoValue(true));
            name = "";
            action = SEARCH_NAME;
            continue;
        }

        if (action == VALIDATE_NAME)
        {
            if (isValidName(name))
            {
                action = SEARCH_EQUALS;
                continue;
            }

            name = "";
            action = SEARCH_NAME;
            continue;
        }

        if (action == SEARCH_NAME)
        {
            if (character == ' ')
            {
                action = VALIDATE_NAME;
                continue;
            }

            name += character;
        }
    }

    return attributes;
}

bool Attribute::isValidName(std::string &name)
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