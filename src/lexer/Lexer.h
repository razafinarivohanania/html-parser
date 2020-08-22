#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "HtmlCursor.h"
#include "HtmlToken.h"
#include "../utils/StringUtils.h"

class Lexer
{
public:
    Lexer(HtmlCursor &htmlCursor);
    virtual std::vector<HtmlToken *> getTokens() = 0;

    bool hasError();
    std::string getError();

protected:
    std::string HTML_NOT_ENDED_CORRECTLY = "HTML not ended correctly";

    void setError(std::string error);

    HtmlCursor htmlCursor;

    std::string buildUnexpectedCharacterError(char expectedCharacter);
    std::string buildUnexpectedCharacterError();

private:
    std::string error;
};

#endif