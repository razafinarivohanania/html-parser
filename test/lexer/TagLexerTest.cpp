#include "TagLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testBeginTag()
        {
            std::cout << "Test begin tag ..." << std::endl;

            std::string html = "<div>";
            HtmlCursor htmlCursor(html);
            TagLexer tagLexer(htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving begin tag failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::BEGIN_TAG, "div"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }
    } // namespace Lexer
} // namespace Test