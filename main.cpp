#include <iostream>
#include <string>

#include "test/lexer/CommentLexerTest.h"
#include "test/lexer/AttributeLexerTest.h"
#include "test/lexer/TagLexerTest.h"
#include "test/lexer/DoctypeLexerTest.h"

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

void testDoctypes()
{
    Test::Lexer::testDoctype("<!doctype html>", "html");
    /* Test::Lexer::testDoctype("<!DOCTYPE html>", "html");
    Test::Lexer::testDoctype("<!DOCTYPE HTML>", "HTML");
    Test::Lexer::testDoctype("<!doctype html  >", "html");
    Test::Lexer::testDoctype("<!DOCTYPE html  >", "html");
    Test::Lexer::testDoctype("<!DOCTYPE HTML  >", "HTML");
    Test::Lexer::testDoctype("<!doctype    html>", "html");
    Test::Lexer::testDoctype("<!DOCTYPE    html>", "html");
    Test::Lexer::testDoctype("<!DOCTYPE    HTML>", "HTML");
    Test::Lexer::testDoctype("<!doctype   html  >", "html");
    Test::Lexer::testDoctype("<!DOCTYPE   html  >", "html");
    Test::Lexer::testDoctype("<!DOCTYPE   HTML  >", "HTML"); */
}

void testComments()
{
    Test::Lexer::testEmptyComment();
    Test::Lexer::testNotEmptyComment();
    Test::Lexer::testNotComment();
    Test::Lexer::testNotEndingComment();
}

int main()
{
    //testComments();
    testDoctypes();
    //testAttributes();
    //testTags();
}