#ifndef COMMENCT_LEXER_TEST_H
#define COMMENCT_LEXER_TEST_H

#include <iostream>

#include "../../src/lexer/CommentLexer.h"
#include "TokenTest.h"

namespace Test
{
    namespace Lexer
    {
        void testEmptyComment();
        void testNotEmptyComment();
        void testNotComment();
        void testNotEndingComment();
    }
} // namespace Test

#endif