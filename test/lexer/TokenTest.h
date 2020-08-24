#ifndef TOKEN_TEST_H
#define TOKEN_TEST_H

#include <vector>
#include <iostream>
#include "../../src/lexer/HtmlToken.h"

namespace Test
{
    namespace Lexer
    {
        void printTokens(std::vector<HtmlToken *> tokens);
        void testTokens(std::vector<HtmlToken *> expectedTokens, std::vector<HtmlToken *> actualTokens);
        bool testToken(HtmlToken *expectedToken, HtmlToken *actualToken);
        void emptyTokensAndFreeMemories(std::vector<HtmlToken *> tokens);
        void emptyTokensAndFreeMemories(std::vector<HtmlToken *> expectedTokens, std::vector<HtmlToken *> actualTokens);
    } // namespace Lexer

} // namespace Test

#endif