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

std::string Attribute::toString()
{
    return "Name = " + m_name + " | Value = " + m_value;
}

std::string Attribute::getName()
{
    return m_name;
}

std::string Attribute::getValue()
{
    return m_value;
}