#ifndef TAG_LEXER_H
#define TAG_LEXER_H

#include <vector>
#include "Lexer.h"
#include "HtmlToken.h"

class TagLexer : Lexer
{
public:
    explicit TagLexer(const std::string &html, int currentIndex);

    virtual std::vector<HtmlToken *> getTokens();

private:
    std::vector<HtmlToken *> tokens;

    const std::string INVALID_BEGIN_CHARACTER__BEGIN_TAG = ".-\\/!|<>=\"'"; //TODO to complete
    const std::string INVALID_MIDDLE_CHARACTER_TAG = "\\/!|<>=\"'"; //TODO to complete

    void process();
    std::string getBeginTagName();
};

#endif