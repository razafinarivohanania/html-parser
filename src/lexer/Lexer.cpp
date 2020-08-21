#include "Lexer.h"

Lexer::Lexer(const std::string &html) : html(html),
                                        currentLine(0),
                                        currentColumn(0),
                                        currentIndex(0)
{
    htmlSize = html.size();
}

void Lexer::jumSpacesFamily()
{
    while (StringUtils::isSpaceFamily(getCurrentCharacter()))
    {
        if (!advance())
        {
            return;
        }
    }
}

char Lexer::getCurrentCharacter()
{
    return html[currentIndex];
}

bool Lexer::advance()
{
    if (currentIndex >= htmlSize - 1)
    {
        return false;
    }

    if (getCurrentCharacter() == '\n')
    {
        currentLine++;
        currentColumn = 0;
    }
    else
    {
        currentColumn++;
    }

    currentIndex++;
    return true;
}

std::string Lexer::getStringPosition()
{
    return "line [" + std::to_string(currentLine + 1) + "] and column [" + std::to_string(currentColumn) + "]";
}

bool Lexer::isLeftArrowCharacter()
{
    return getCurrentCharacter() == '<';
}

bool Lexer::isRightArrowCharacter()
{
    return getCurrentCharacter() == '>';
}

bool Lexer::isExclamationPointCharacter()
{
    return getCurrentCharacter() == '!';
}

bool Lexer::isEqualsCharacter()
{
    return getCurrentCharacter() == '=';
}

void Lexer::setCurrentIndex(int currentIndex)
{
    this->currentIndex = currentIndex;
}