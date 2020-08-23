#ifndef HTML_CURSOR_H
#define HTML_CURSOR_H

#include <string>
#include <iostream>

#include "../utils/StringUtils.h"

class HtmlCursor
{
public:
    HtmlCursor(const std::string &html);

    int getPosition();
    int getLine();
    int getColumn();

    char getCharacter();

    bool isLeftArrowCharacter();
    bool isRightArrowCharacter();
    bool isExclamationPointCharacter();
    bool isEqualsCharacter();
    bool isSlashCharacter();
    bool isSpaceCharacterFamily();
    bool isHyphenCharacter();
    bool isQuote();
    bool isDoubleQuote();
    bool matchesIgnoreCaseCharacter(char character);

    bool endReached();

    bool advance();
    void skipSpacesFamily();
    std::string getPositionAsString();
private:
    std::string html;
    int htmlSize;
    int position;
    int line;
    int column;
};

#endif