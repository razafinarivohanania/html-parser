#ifndef HTML_LEXER_H
#define HTML_LEXER_H

#include <string>
#include <iostream>
#include <vector>
#include "HtmlToken.h"
#include "../utils/StringUtils.h"

class HtmlLexer
{

public:
    HtmlLexer(const std::string &html);

    bool hasError();
    std::string getError();
    std::string toString();

    ~HtmlLexer();
private:
    std::vector<HtmlToken*> htmlTokens;
    const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::string html;

    std::string error;

    int htmlSize;
    int currentColumn;
    int currentLine;
    int currentIndex;

    void process();
    bool advance();

    void skipSpaceFamilies();
    void gotoFirstArrowMin();
    char getCurrentCharacter();
    void getDoctype();
    std::string getSuccessiveAlphabet();
    void buildUnexpectedCharacterError(char expectedCharacter);
    void buildUnexpectedCharacterError();
};

#endif
