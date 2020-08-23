#include "HtmlCursor.h"

HtmlCursor::HtmlCursor(std::string *html)
{
    resetHtml(html);
}

void HtmlCursor::resetHtml(std::string *html)
{
    this->html = html;
    htmlSize = html->size();
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
    return (*html)[position];
}

char HtmlCursor::getCharacter(const size_t position)
{
    return position < html->size() ? (*html)[position] : '\0';
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

        char htmlCharacter = (*html)[j];
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

void HtmlCursor::skipBlocs(const int sizeBlocs)
{
    for (int i = 0; i < sizeBlocs; i++)
    {
        advance();
    }
}

Result HtmlCursor::getStringStarting(const std::string &string,
                                     const bool ignoreCase)
{
    int size = string.size();
    std::string stringFound = "";

    Result result;
    result.success = false;
    result.content = "";

    for (int i = 0; i < size; i++)
    {
        char character = string[i];
        if (ignoreCase)
        {
            character = std::tolower(character);
        }

        int j = position + i;
        if (j >= htmlSize)
        {
            return result;
        }

        char htmlCharacter = (*html)[j];
        if (ignoreCase)
        {
            htmlCharacter = std::tolower(htmlCharacter);
        }

        if (character != htmlCharacter)
        {
            return result;
        }

        stringFound.push_back((*html)[j]);
    }

    result.success = true;
    result.content = stringFound;
    return result;
}

Result HtmlCursor::getStringBefore(const std::string &string)
{
    int size = string.size();
    std::string stringBefore = "";

    Result result;
    result.success = false;
    result.content = "";

    for (int i = position; i < htmlSize; i++)
    {
        bool found = true;
        for (int j = 0; j < size; j++)
        {
            int k = i + j;
            if (k >= htmlSize)
            {
                return result;
            }

            if ((*html)[k] != string[j])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            result.success = true;
            result.content = stringBefore;
            break;
        }

        stringBefore.push_back((*html)[i]);
    }

    return result;
}

Result HtmlCursor::getStringBeforeFirstCharacterFound(const std::string &characters)
{
    int size = characters.size();

    Result result;
    result.success = false;
    result.content = "";

    std::string stringBefore = "";

    for (int i = position; i < htmlSize; i++)
    {
        bool found = false;
        char character = (*html)[i];
        for (int j = 0; j < size; j++)
        {
            if (character == characters[j])
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            result.success = true;
            result.content = stringBefore;
            break;
        }

        stringBefore.push_back(character);
    }

    return result;
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
    return getCharacter() == '/';
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

bool HtmlCursor::isOneOfCharacters(const std::string &characters)
{
    int size = characters.size();
    for (int i = 0; i < size; i++)
    {
        if (getCharacter() == characters[i])
        {
            return true;
        }
    }

    return false;
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

std::string HtmlCursor::getRestContent() {
    std::string restContent = "";

    for (int i = position; i < htmlSize; i++){
        restContent.push_back((*html)[i]);
    }

    return restContent;
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