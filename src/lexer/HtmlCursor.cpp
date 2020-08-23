#include "HtmlCursor.h"

HtmlCursor::HtmlCursor(std::string &html)
{
    resetHtml(html);
}

void HtmlCursor::resetHtml(std::string &html)
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

int HtmlCursor::getHtmlSize()
{
    return htmlSize;
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

char HtmlCursor::getCharacter(const size_t position)
{
    return position < html.size() ? html[position] : '\0';
}

bool HtmlCursor::startsWith(const std::string &string,
                            const bool ignoreCase)
{
    int size = string.size();

    for (int i = 0; i < size; i++)
    {
        char character = string[i];
        if (ignoreCase)
        {
            character = std::tolower(character);
        }

        int j = position + i;
        if (j >= htmlSize - 1)
        {
            return false;
        }

        char htmlCharacter = html[j];
        if (ignoreCase)
        {
            htmlCharacter = std::tolower(htmlCharacter);
        }

        if (character != htmlCharacter)
        {
            return false;
        }
    }

    return true;
}

bool HtmlCursor::skipIfFound(const std::string &string,
                             const bool ignoreCase)
{
    if (!startsWith(string, ignoreCase))
    {
        return false;
    }

    int size = string.size();
    for (int i = 0; i < size; i++)
    {
        advance();
    }

    return true;
}

std::string HtmlCursor::skipAndGetStringFound(const std::string &string,
                                              const bool ignoreCase)
{
    int size = string.size();
    std::string stringFound = "";

    for (int i = 0; i < size; i++)
    {
        char character = string[i];
        if (ignoreCase)
        {
            character = std::tolower(character);
        }

        int j = position + i;
        if (j >= htmlSize - 1)
        {
            return "";
        }

        char htmlCharacter = html[j];
        if (ignoreCase)
        {
            htmlCharacter = std::tolower(htmlCharacter);
        }

        if (character != htmlCharacter)
        {
            return "";
        }

        stringFound.push_back(html[j]);
    }

    size = string.size();
    for (int i = 0; i < size; i++)
    {
        advance();
    }

    return stringFound;
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

bool HtmlCursor::isHyphenCharacter()
{
    return getCharacter() == '-';
}

bool HtmlCursor::matchesIgnoreCaseCharacter(char character)
{
    return StringUtils::equalsIgnoreCase(getCharacter(), character);
}

bool HtmlCursor::isQuote()
{
    return getCharacter() == '\'';
}

bool HtmlCursor::isDoubleQuote()
{
    return getCharacter() == '"';
}

bool HtmlCursor::advance()
{
    if (endReached())
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

bool HtmlCursor::endReached()
{
    return position >= htmlSize - 1;
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