#include "AttributeParser.h"

AttributeParser::AttributeParser(std::string &rawAttributes) : m_character(' '),
                                                               m_quot('"'),
                                                               m_name(""),
                                                               m_value(""),
                                                               m_invalidCharacters("²&~\"#'{([|`\\^)°]+=}/*^¨$£¤%<>?,;.:!§ ")
{
    parse(rawAttributes);
}

void AttributeParser::parse(std::string &rawAttributes)
{
    if (rawAttributes == "")
    {
        return;
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
        case ActionParser::SEARCH_EQUALS:
            action = searchEquals();
            continue;
        case ActionParser::SEARCH_ATTRIBUTE_QUOT:
            action = searchQuot();
            continue;
        case ActionParser::SEARCH_ATTRIBUTE_VALUE:
            action = searchValue();
            continue;
        case ActionParser::SAVE_ATTRIBUTE_WITH_NO_VALUE:
            action = saveAttribute(true);
            continue;
        case ActionParser::SAVE_ATTRIBUTE_WITH_VALUE:
            action = saveAttribute(false);
        }
    }

    if (m_name != "")
    {
        if (action == SAVE_ATTRIBUTE_WITH_VALUE)
        {
            saveAttribute(false);
        }
        else
        {
            saveAttribute(true);
        }
    }
}

ActionParser AttributeParser::searchName()
{
    std::cout << "SEARCH_NAME : [" << m_name << "] [" << m_value << "] [" << m_character << "]" << std::endl;
    if (isSpaceCharacter())
    {
        if (m_name == "")
        {
            return ActionParser::SEARCH_ATTRIBUTE_NAME;
        }

        return ActionParser::SEARCH_EQUALS;
    }

    if (m_character == '=')
    {
        if (isValidName())
        {
            return ActionParser::SEARCH_ATTRIBUTE_QUOT;
        }

        reinitializeAttribute();
        return ActionParser::SEARCH_ATTRIBUTE_NAME;
    }

    m_name += m_character;
    return SEARCH_ATTRIBUTE_NAME;
}

ActionParser AttributeParser::searchEquals()
{
    std::cout << "SEARCH_EQUALS : [" << m_name << "] [" << m_value << "] [" << m_character << "]" << std::endl;
    if (isSpaceCharacter())
    {
        return ActionParser::SEARCH_EQUALS;
    }

    if (m_character == '=')
    {
        if (isValidName())
        {
            return ActionParser::SEARCH_ATTRIBUTE_QUOT;
        }

        reinitializeAttribute();
        return ActionParser::SEARCH_ATTRIBUTE_NAME;
    }

    saveAttribute(true);
    m_name = m_character;
    return SEARCH_ATTRIBUTE_NAME;
}

ActionParser AttributeParser::searchQuot()
{
    std::cout << "SEARCH_QUOT : [" << m_name << "] [" << m_value << "] [" << m_character << "]" << std::endl;
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
    std::cout << "SEARCH_VALUE : [" << m_name << "] [" << m_value << "] [" << m_character << "]" << std::endl;
    if (m_quot == m_character)
    {
        return ActionParser::SAVE_ATTRIBUTE_WITH_VALUE;
    }

    m_value += m_character;
    return ActionParser::SEARCH_ATTRIBUTE_VALUE;
}

ActionParser AttributeParser::saveAttribute(bool noValue)
{
    std::cout << "SAVE_ATTRIBUTE : [" << m_name << "] [" << m_value << "] [" << m_character << "] [" << noValue << "]" << std::endl;
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

    m_attributes.push_back(attribute);
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