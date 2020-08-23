#include <iostream>
#include <string>

#include "test/lexer/AttributeLexerTest.h"

int main()
{
    Test::Lexer::testOneAttributeWithoutValue();
    Test::Lexer::testTwoAttributesWithoutValues();
    Test::Lexer::testAttributeWithValueUsingQuote();
}