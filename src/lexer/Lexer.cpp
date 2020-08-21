#include "Lexer.h"

void Lexer::setError(std::string error)
{
    this->error = error;
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
    error.push_back(htmlCursor.getCharacter());
    return error + "] at " + htmlCursor.getPositionAsString();
}

std::string Lexer::buildUnexpectedCharacterError()
{
    std::string error = "Unexpected character [";
    error.push_back(htmlCursor.getCharacter());
    return error + "] at " + htmlCursor.getPositionAsString();
}