#include "AttributeParser.h"

AttributeParser::AttributeParser(std::string &rawAttributes) : m_name(""),
                                                               m_value(""),
                                                               m_character(' '),
                                                               m_quot('"'),
                                                               m_invalidCharacters("²&~\"#'{([|`\\^)°]+=}/*^¨$£¤%<>?,;.:!§ ")
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

    ActionParser action = ActionParser::SEARCH_ATTRIBUTE_NAME;

    for (auto &character : rawAttributes)
    {
        m_character = character;

        switch (action)
        {
        case ActionParser::SEARCH_ATTRIBUTE_NAME:
            action = searchName();
            continue;
        case ActionParser::SEARCH_ATTRIBUTE_QUOT:
            action = searchQuot();
            continue;
        case ActionParser::SEARCH_ATTRIBUTE_VALUE:
            action = searchValue();
            continue;
        case ActionParser::SAVE_ATTRIBUTE_WITH_NO_VALUE:
            action = saveAttribute(attributes, true);
            continue;
        case ActionParser::SAVE_ATTRIBUTE_WITH_VALUE:
            action = saveAttribute(attributes, false);
        }
    }

    if (m_name != "") {
        if (action == SEARCH_ATTRIBUTE_VALUE) {
            saveAttribute(attributes, false);
        } else {
            saveAttribute(attributes, true);
        }
    }
    
    return attributes;
}

ActionParser AttributeParser::searchName()
{
    if (isSpaceCharacter())
    {
        if (m_name == "")
        {
            return ActionParser::SEARCH_ATTRIBUTE_NAME;
        }

        return ActionParser::SAVE_ATTRIBUTE_WITH_NO_VALUE;
    }

    if (m_character == '=')
    {
        if (isValidName())
        {
            return searchQuot();
        }

        reinitializeAttribute();
        return ActionParser::SEARCH_ATTRIBUTE_NAME;
    }

    m_name += m_character;
    return SEARCH_ATTRIBUTE_NAME;
}

ActionParser AttributeParser::searchQuot()
{
    if (isSpaceCharacter())
    {
        return ActionParser::SEARCH_ATTRIBUTE_QUOT;
    }

    if (isQuotCharacter())
    {
        m_quot = m_character;
        return ActionParser::SEARCH_ATTRIBUTE_VALUE;
    }

    reinitializeAttribute();
    m_name += m_character;
    return ActionParser::SEARCH_ATTRIBUTE_NAME;
}

ActionParser AttributeParser::searchValue()
{
    if (m_quot == m_character) {
        return ActionParser::SAVE_ATTRIBUTE_WITH_VALUE;
    }

    m_value += m_character;
    return ActionParser::SEARCH_ATTRIBUTE_VALUE;
}

ActionParser AttributeParser::saveAttribute(std::vector<Attribute *> &attributes, bool noValue)
{
    Attribute *attribute = new Attribute();

    attribute->setName(m_name);
    if (noValue)
    {
        attribute->setNoValue(true);
    }
    else
    {
        attribute->setValue(m_value);
    }

    attributes.push_back(attribute);
    reinitializeAttribute();
    return ActionParser::SEARCH_ATTRIBUTE_NAME;
}

void AttributeParser::reinitializeAttribute()
{
    m_name = "";
    m_value = "";
}

std::vector<Attribute *> AttributeParser::getAttributes()
{
    return m_attributes;
}

bool AttributeParser::isQuotCharacter()
{
    return m_character == '"' || m_character == '\'';
}

bool AttributeParser::isSpaceCharacter()
{
    return m_character == ' ' ||
           m_character == '\n' ||
           m_character == '\t' ||
           m_character == '\r';
}

bool AttributeParser::isValidName()
{
    if (m_name == "")
    {
        return false;
    }

    for (auto &character : m_name)
    {
        for (auto &invalidCharacter : m_invalidCharacters)
        {
            if (character == invalidCharacter)
            {
                return false;
            }
        }
    }

    return true;
}