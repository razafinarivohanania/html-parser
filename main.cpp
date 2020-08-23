#include <iostream>
#include <string>

#include "test/lexer/AttributeLexerTest.h"
#include "test/lexer/TagLexerTest.h"

void testAttributes()
{
    Test::Lexer::testNoAttribute();
    Test::Lexer::testOneAttributeWithoutValue();
    Test::Lexer::testTwoAttributesWithoutValues();
    Test::Lexer::testAttributeWithValueUsingQuote();
    Test::Lexer::testTwoAttributesWithValuesUsingQuote();
    Test::Lexer::testAttributeWithValueUsingDoubleQuote();
    Test::Lexer::testTwoAttributesWithValuesUsingDoubleQuote();
    Test::Lexer::testTwoAttributesWithValuesUsingQuoteAndDoubleQuote();
    Test::Lexer::testTwoAttributesWithValuesUsingDoubleQuoteAndQuote();
}

void testTags()
{
    Test::Lexer::testDoctype();
}

int main()
{
    testAttributes();
    //testTags();
}