#include "AttributeLexer.h"

AttributeLexer::AttributeLexer(const std::string &html, int &currentIndex) : Lexer(html)
{
    setCurrentIndex(currentIndex);
    process();
}

void AttributeLexer::process()
{

}

std::vector<HtmlToken *> AttributeLexer::getTokens()
{
    return tokens;
}