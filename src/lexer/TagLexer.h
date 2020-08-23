#ifndef TAG_LEXER_H
#define TAG_LEXER_H

#include <vector>
#include "HtmlCursor.h"
#include "HtmlToken.h"
#include "AttributeLexer.h"
#include "../utils/StringUtils.h"

class TagLexer
{
public:
    TagLexer(HtmlCursor &htmlCursor);
    std::vector<HtmlToken *> getTokens();
    bool isSuccess();
    int getInitialPosition();

private:
    const std::string INVALID_BEGIN_CHARACTER_TAG = ".-\\/!|<>=\"'"; // TODO to complet
    const std::string INVALID_MIDDLE_CHARACTER_TAG = "\\/!|<>=\"'";  // TODO to complete

    HtmlCursor htmlCursor;
    std::vector<HtmlToken *> tokens;
    bool success;
    int initialPosition;

    void process();
    bool isValidTagName(const std::string &tagName);
};

#endif