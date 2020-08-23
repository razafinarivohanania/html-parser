#ifndef HTML_CURSOR_H
#define HTML_CURSOR_H

#include <string>
#include <iostream>

#include "../utils/StringUtils.h"
#include "Result.h"

class HtmlCursor
{
public:
    HtmlCursor(std::string &html);

    void resetHtml(std::string &html);

    int getHtmlSize();
    int getPosition();
    int getLine();
    int getColumn();

    char getCharacter();
    char getCharacter(const size_t position);

    bool startsWith(const std::string &string, const bool ignoreCase);
    void skipBlocs(const int sizeBlocs);
    Result getStringStarting(const std::string &string, const bool ignoreCase);
    Result getStringBefore(const std::string &string);
    Result getStringBeforeFirstCharacterFound(const std::string &characters);

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
    bool isOneOfCharacters(const std::string &characters);

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