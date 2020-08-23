#include "TagLexerTest.h"

static void testStringDoctype(const std::string &html, const std::string &expectedDoctype)
{
    std::cout << "Test " << html << " ..." << std::endl;

    std::string doctype = html;
    HtmlCursor htmlCursor(doctype);
    TagLexer tagLexer(htmlCursor);

    if (!tagLexer.isSuccess())
    {
        std::cout << "ERROR : Retrieving tag failed";
    }

    std::vector<HtmlToken *> expectedTokens;
    expectedTokens.push_back(new HtmlToken(TokenType::DOCTYPE, expectedDoctype));

    std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
    Test::Lexer::testTokens(expectedTokens, actualTokens);
    Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
}

namespace Test
{
    namespace Lexer
    {
        void testDoctype()
        {
            testStringDoctype("<!doctype html>", "html");
            testStringDoctype("<!DOCTYPE html>", "html");
            testStringDoctype("<!DOCTYPE HTML>", "HTML");
            testStringDoctype("<!doctype html  >", "html");
            testStringDoctype("<!DOCTYPE html  >", "html");
            testStringDoctype("<!DOCTYPE HTML  >", "HTML");
            testStringDoctype("<!doctype    html>", "html");
            testStringDoctype("<!DOCTYPE    html>", "html");
            testStringDoctype("<!DOCTYPE    HTML>", "HTML");
            testStringDoctype("<!doctype   html  >", "html");
            testStringDoctype("<!DOCTYPE   html  >", "html");
            testStringDoctype("<!DOCTYPE   HTML  >", "HTML");
        }
    } // namespace Lexer
} // namespace Test