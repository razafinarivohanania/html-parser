#ifndef TOKEN_TEST_H
#define TOKEN_TEST_H

#include <vector>
#include <iostream>
#include "../../src/lexer/HtmlToken.h"

namespace Test
{
    namespace Lexer
    {
        void testTokens(std::vector<HtmlToken *> expectedTokens, std::vector<HtmlToken *> actualTokens);
        void emptyTokensAndFreeMemories(std::vector<HtmlToken *> expectedTokens, std::vector<HtmlToken *> actualTokens);
    } // namespace Lexer

} // namespace Test

#endif