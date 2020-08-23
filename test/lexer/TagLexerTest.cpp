#include "TagLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testLowerCaseDoctype()
        {
            std::cout << "Test lower case doctype ..." << std::endl;

            HtmlCursor htmlCursor("<!doctype html>");
            TagLexer tagLexer(htmlCursor);

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::DOCTYPE, "html"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }
    } // namespace Lexer
} // namespace Test