#include <iostream>
#include <string>

#include "test/lexer/CommentLexerTest.h"
#include "test/lexer/AttributeLexerTest.h"
#include "test/lexer/TagLexerTest.h"
#include "test/lexer/DoctypeLexerTest.h"
#include "test/lexer/TagLexerTest.h"
#include "test/lexer/HtmlLexerTest.h"

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
    Test::Lexer::testDoctype("<!DOCTYPE html>", "html");
    Test::Lexer::testDoctype("<!DOCTYPE HTML>", "HTML");
    Test::Lexer::testDoctype("<!doctype html  >", "html");
    Test::Lexer::testDoctype("<!DOCTYPE html  >", "html");
    Test::Lexer::testDoctype("<!DOCTYPE HTML  >", "HTML");
    Test::Lexer::testDoctype("<!doctype    html>", "html");
    Test::Lexer::testDoctype("<!DOCTYPE    html>", "html");
    Test::Lexer::testDoctype("<!DOCTYPE    HTML>", "HTML");
    Test::Lexer::testDoctype("<!doctype   html  >", "html");
    Test::Lexer::testDoctype("<!DOCTYPE   html  >", "html");
    Test::Lexer::testDoctype("<!DOCTYPE   HTML  >", "HTML");
    Test::Lexer::testNotDoctype();
    Test::Lexer::testNotEndingDoctype();
}

void testComments()
{
    Test::Lexer::testEmptyComment();
    Test::Lexer::testNotEmptyComment();
    Test::Lexer::testNotComment();
    Test::Lexer::testNotEndingComment();
}

void testTags()
{
    Test::Lexer::testBeginTag();
    Test::Lexer::testBeginTagWithAttributeWithoutValue();
    Test::Lexer::testBeginTagWithAttributeWithValue();
    Test::Lexer::testBeginTagWithTwoAttributesWithoutValues();
    Test::Lexer::testBeginTagWithTwoAttributesWithValues();
    Test::Lexer::testBeginTagWithAttributeWithoutValueAndAttributeWithValue();
    Test::Lexer::testBeginTagWithAttributeWithValueAndAttributeWithoutValue();

    Test::Lexer::testOrphanTag();
    Test::Lexer::testOrphanTagWithAttributeWithoutValue();
    Test::Lexer::testOrphanTagWithAttributeWithValue();
    Test::Lexer::testOrphanTagWithTwoAttributesWithoutValues();
    Test::Lexer::testOrphanTagWithTwoAttributesWithValues();
    Test::Lexer::testOrphanTagWithAttributeWithoutValueAndAttributeWithValue();
    Test::Lexer::testOrphanTagWithAttributeWithValueAndAttributeWithoutValue();

    Test::Lexer::testEndTag();
}

void testHtmls() {
    Test::Lexer::testSimpleHtml();
}

int main()
{
    /* testTags();
    testComments();
    testDoctypes();
    testAttributes();
    testTags();*/
    testHtmls();
}