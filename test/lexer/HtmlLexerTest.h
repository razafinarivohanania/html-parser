#ifndef HTML_LEXER_TEST_H
#define HTML_LEXER_TEST_H

#include <iostream>

#include "../../src/utils/FileReader.h"
#include "../../src/lexer/HtmlLexer.h"
#include "TokenTest.h"

namespace Test
{
    namespace Lexer
    {
        void testSimpleHtml();
    }
} // namespace Test

#endif