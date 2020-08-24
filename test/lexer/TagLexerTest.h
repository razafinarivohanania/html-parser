#ifndef TAG_LEXER_TEST_H
#define TAG_LEXER_TEST_H

#include <iostream>
#include <vector>

#include "../../src/lexer/TagLexer.h"
#include "TokenTest.h"

namespace Test
{
    namespace Lexer
    {
        void testBeginTag();
        void testBeginTagWithAttributeWithoutValue();
        void testBeginTagWithAttributeWithValue();
        void testBeginTagWithTwoAttributesWithoutValues();
        void testBeginTagWithTwoAttributesWithValues();
        void testBeginTagWithAttributeWithoutValueAndAttributeWithValue();
        void testBeginTagWithAttributeWithValueAndAttributeWithoutValue();

        void testOrphanTag();
        void testOrphanTagWithAttributeWithoutValue();
        void testOrphanTagWithAttributeWithValue();
        void testOrphanTagWithTwoAttributesWithoutValues();
        void testOrphanTagWithTwoAttributesWithValues();
        void testOrphanTagWithAttributeWithoutValueAndAttributeWithValue();
        void testOrphanTagWithAttributeWithValueAndAttributeWithoutValue();

        void testEndTag();
    } // namespace Lexer
} // namespace Test
#endif