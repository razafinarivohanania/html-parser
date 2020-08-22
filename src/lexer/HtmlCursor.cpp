#include "HtmlCursor.h"

HtmlCursor::HtmlCursor(const std::string &html)
{
    this->html = html;
    htmlSize = html.size();
    position = 0;
    line = 0;
    column = 0;
}

int HtmlCursor::getPosition()
{
    return position;
}

int HtmlCursor::getLine()
{
    return line;
}

int HtmlCursor::getColumn()
{
    return column;
}

char HtmlCursor::getCharacter()
{
    return html[position];
}

bool HtmlCursor::isLeftArrowCharacter()
{
    return getCharacter() == '<';
}

bool HtmlCursor::isRightArrowCharacter()
{
    return getCharacter() == '>';
}

bool HtmlCursor::isExclamationPointCharacter()
{
    return getCharacter() == '!';
}

bool HtmlCursor::isEqualsCharacter()
{
    return getCharacter() == '=';
}

bool HtmlCursor::isSlashCharacter()
{
    return getCharacter() == '!';
}

bool HtmlCursor::isSpaceCharacterFamily()
{
    return StringUtils::isSpaceFamily(getCharacter());
}

bool HtmlCursor::isHyphenCharacter(){
    return getCharacter() == '-';
}

bool HtmlCursor::matchesIgnoreCaseCharacter(char character) {
    return StringUtils::equalsIgnoreCase(getCharacter(), character);
}

bool HtmlCursor::advance()
{
    if (position >= htmlSize - 1)
    {
        return false;
    }

    if (getCharacter() == '\n')
    {
        line++;
        column = 0;
    }
    else
    {
        column++;
    }

    position++;
    return true;
}

void HtmlCursor::skipSpacesFamily()
{
    while (StringUtils::isSpaceFamily(getCharacter()))
    {
        if (!advance())
        {
            return;
        }
    }
}

std::string HtmlCursor::getPositionAsString()
{
    std::string currentLine = std::to_string(line + 1);
    std::string currentColumn = std::to_string(column + 1);
    return "line [" + currentLine + "] and column [" + currentColumn + "]";
}