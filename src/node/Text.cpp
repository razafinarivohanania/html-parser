#include "Text.h"

Text::Text() : Node(NodeType::TEXT),
               m_text("")
{
}

void Text::setText(std::string text)
{
    m_text = text;
}

std::string Text::getText()
{
    return m_text;
}

std::string Text::toHtml()
{
    return m_text;
}