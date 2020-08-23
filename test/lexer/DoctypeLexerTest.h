#ifndef DOCTYPE_LEXER_TEST_H
#define DOCTYPE_LEXER_TEST_H

#include <iostream>
#include "../../src/lexer/DoctypeLexer.h"
#include "TokenTest.h"

namespace Test {
    namespace Lexer {
        void testDoctype(const std::string &html, const std::string &expectedDoctype);
    }
}

#endif