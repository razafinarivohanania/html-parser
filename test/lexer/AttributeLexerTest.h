#ifndef ATTRIBUTE_LEXER_TEST_H
#define ATTRIBUTE_LEXER_TEST_H

#include <vector>
#include <iostream>

#include "../../src/lexer/AttributeLexer.h"
#include "../../src/lexer/HtmlCursor.h"
#include "TokenTest.h"

namespace Test
{
    namespace Lexer
    {
        void testOneAttributeWithoutValue();
        void testTwoAttributesWithoutValues();
        void testAttributeWithValueUsingQuote();
    } // namespace Lexer

} // namespace Test

#endif