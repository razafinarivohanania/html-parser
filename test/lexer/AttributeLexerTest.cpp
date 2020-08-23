#include "AttributeLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testOneAttributeWithoutValue()
        {
            std::cout << "Test one attribute with one value ..." << std::endl;

            HtmlCursor htmlCursor("checked");
            AttributeLexer attributeLexer(htmlCursor);

            if (attributeLexer.hasError())
            {
                std::cout << attributeLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "checked"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }

        void testTwoAttributesWithoutValues()
        {
            std::cout << "Test two attributes without values ..." << std::endl;

            HtmlCursor htmlCursor("checked fullWidth");
            AttributeLexer attributeLexer(htmlCursor);

            if (attributeLexer.hasError())
            {
                std::cout << attributeLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "checked"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "fullWidth"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }

        void testAttributeWithValueUsingQuote()
        {
            std::cout << "Test attribute with value ..." << std::endl;

            HtmlCursor htmlCursor("class='content'");
            AttributeLexer attributeLexer(htmlCursor);

            if (attributeLexer.hasError())
            {
                std::cout << attributeLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }
    } // namespace Lexer

} // namespace Test