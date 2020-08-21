#include "Lexer.h"

Lexer::Lexer(const std::string &html)
{
    this->html = html;
    htmlSize = html.size();
    currentLine = 0;
    currentIndex = 0;
}

std::string Lexer::getHtml()
{
    return html;
}

bool Lexer::hasError()
{
    return !error.empty();
}

std::string Lexer::getError()
{
    return error;
}

std::string Lexer::buildUnexpectedCharacterError(char expectedCharacter)
{
    std::string error = "Expected character [";
    error.push_back(expectedCharacter);
    error += "] instead of [";
    error.push_back(getCurrentCharacter());
    return error + "] at " + getPositionAsString();
}

std::string Lexer::buildUnexpectedCharacterError()
{
    std::string error = "Unexpected character [";
    error.push_back(getCurrentCharacter());
    return error + "] at " + getPositionAsString();
}

void Lexer::setError(std::string error)
{
    this->error = error;
}

void Lexer::skipSpacesFamily()
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

int Lexer::getCurrentIndex() {
    return currentIndex;
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

std::string Lexer::getPositionAsString()
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

bool Lexer::isSlashCharacter()
{
    return getCurrentCharacter() == '/';
}

bool Lexer::isSpaceCharacterFamily()
{
    return StringUtils::isSpaceFamily(getCurrentCharacter());
}

void Lexer::setCurrentIndex(int currentIndex)
{
    this->currentIndex = currentIndex;
}