#include "AttributeLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testNoAttribute()
        {
            std::cout << "Test no attribute ..." << std::endl;

            HtmlCursor htmlCursor("");
            AttributeLexer attributeLexer(htmlCursor);

            if (attributeLexer.hasError())
            {
                std::cout << attributeLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }

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
            std::cout << "Test attribute with value using quote ..." << std::endl;

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

        void testTwoAttributesWithValuesUsingQuote()
        {
            std::cout << "Test two attributes with values using quote ..." << std::endl;

            HtmlCursor htmlCursor("id='main' class='content'");
            AttributeLexer attributeLexer(htmlCursor);

            if (attributeLexer.hasError())
            {
                std::cout << attributeLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }

        void testAttributeWithValueUsingDoubleQuote()
        {
            std::cout << "Test attribute with value using double quote ..." << std::endl;

            HtmlCursor htmlCursor("class=\"content\"");
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

        void testTwoAttributesWithValuesUsingDoubleQuote()
        {
            std::cout << "Test two attributes with values using double quote ..." << std::endl;

            HtmlCursor htmlCursor("id=\"main\" class=\"content\"");
            AttributeLexer attributeLexer(htmlCursor);

            if (attributeLexer.hasError())
            {
                std::cout << attributeLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }

        void testTwoAttributesWithValuesUsingQuoteAndDoubleQuote()
        {
            std::cout << "Test two attributes with values quote and double quote ..." << std::endl;

            HtmlCursor htmlCursor("id=\'main\' class=\"content\"");
            AttributeLexer attributeLexer(htmlCursor);

            if (attributeLexer.hasError())
            {
                std::cout << attributeLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }

        void testTwoAttributesWithValuesUsingDoubleQuoteAndQuote()
        {
            std::cout << "Test two attributes with values using double quote and quote ..." << std::endl;

            HtmlCursor htmlCursor("id=\"main\" class=\'content\'");
            AttributeLexer attributeLexer(htmlCursor);

            if (attributeLexer.hasError())
            {
                std::cout << attributeLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }

        void testThreeAttributesWithValuesAndWithoutValueUsingQuoteAndDoubleQuote()
        {
            std::cout << "Test three attributes with values and without value using quote and double quote ..." << std::endl;

            HtmlCursor htmlCursor("id=\"main\" class=\'content\' checked");
            AttributeLexer attributeLexer(htmlCursor);

            if (attributeLexer.hasError())
            {
                std::cout << attributeLexer.getError() << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "checked"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::freeMemories(expectedTokens, actualTokens);
        }
    } // namespace Lexer

} // namespace Test