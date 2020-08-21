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

protected:
    void jumSpacesFamily();
    bool advance();
    char getCurrentCharacter();
    std::string getStringPosition();

    bool isLeftArrowCharacter();
    bool isRightArrowCharacter();
    bool isExclamationPointCharacter();
    bool isEqualsCharacter();

    void setCurrentIndex(int currentIndex);

private:
    int currentLine;
    int currentColumn;
    int currentIndex;
    int htmlSize;

    std::string html;
};

#endif