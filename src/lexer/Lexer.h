#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "HtmlToken.h"
#include "../utils/StringUtils.h"

class Lexer
{
public:
    Lexer(const std::string &html);
    virtual std::vector<HtmlToken *> getTokens() = 0;
    bool hasError();
    std::string getError();

protected:
    void skipSpacesFamily();
    bool advance();
    char getCurrentCharacter();
    std::string getPositionAsString();

    bool isLeftArrowCharacter();
    bool isRightArrowCharacter();
    bool isExclamationPointCharacter();
    bool isEqualsCharacter();
    bool isSlashCharacter();
    bool isSpaceCharacterFamily();

    void setCurrentIndex(int currentIndex);
    void setError(std::string error);
    std::string buildUnexpectedCharacterError(char expectedCharacter);
    std::string buildUnexpectedCharacterError();

    std::string HTML_NOT_ENDED_CORRECTLY = "HTML not ended correctly";

private:
    int currentLine;
    int currentColumn;
    int currentIndex;
    int htmlSize;

    std::string html;
    std::string error;
};

#endif