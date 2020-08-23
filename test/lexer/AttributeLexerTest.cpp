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

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "checked"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }

        void testTwoAttributesWithoutValues()
        {

        }
    } // namespace Lexer

} // namespace Test