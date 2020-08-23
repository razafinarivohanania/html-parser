#include "TagLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testLowerCaseDoctype()
        {
            std::cout << "Test lower case doctype ..." << std::endl;

            std::string doctype = "<!doctype html>";
            HtmlCursor htmlCursor(doctype);
            TagLexer tagLexer(htmlCursor);

            if (tagLexer.hasError())
            {
                std::cout << "ERROR : " << tagLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::DOCTYPE, "html"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }
    } // namespace Lexer
} // namespace Test