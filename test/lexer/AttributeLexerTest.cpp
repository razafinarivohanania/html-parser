#include "AttributeLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testNoAttribute()
        {
            std::cout << "Test no attribute ..." << std::endl;

            std::string html = "";
            HtmlCursor htmlCursor(html);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }

        void testOneAttributeWithoutValue()
        {
            std::cout << "Test one attribute with one value ..." << std::endl;

            std::string attribute = "checked";
            HtmlCursor htmlCursor(attribute);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "checked"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }

        void testTwoAttributesWithoutValues()
        {
            std::cout << "Test two attributes without values ..." << std::endl;

            std::string attributes = "checked fullWidth";
            HtmlCursor htmlCursor(attributes);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "checked"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "fullWidth"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }

        void testAttributeWithValueUsingQuote()
        {
            std::cout << "Test attribute with value using quote ..." << std::endl;

            std::string attribute = "class='content'";
            HtmlCursor htmlCursor(attribute);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }

        void testTwoAttributesWithValuesUsingQuote()
        {
            std::cout << "Test two attributes with values using quote ..." << std::endl;

            std::string attributes = "id='main' class='content'";
            HtmlCursor htmlCursor(attributes);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }

        void testAttributeWithValueUsingDoubleQuote()
        {
            std::cout << "Test attribute with value using double quote ..." << std::endl;

            std::string attribute = "class=\"content\"";
            HtmlCursor htmlCursor(attribute);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }

        void testTwoAttributesWithValuesUsingDoubleQuote()
        {
            std::cout << "Test two attributes with values using double quote ..." << std::endl;

            std::string attributes = "id=\"main\" class=\"content\"";
            HtmlCursor htmlCursor(attributes);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }

        void testTwoAttributesWithValuesUsingQuoteAndDoubleQuote()
        {
            std::cout << "Test two attributes with values quote and double quote ..." << std::endl;

            std::string attributes = "id=\'main\' class=\"content\"";
            HtmlCursor htmlCursor(attributes);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }

        void testTwoAttributesWithValuesUsingDoubleQuoteAndQuote()
        {
            std::cout << "Test two attributes with values using double quote and quote ..." << std::endl;

            std::string attributes = "id=\"main\" class=\'content\'";
            HtmlCursor htmlCursor(attributes);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }

        void testThreeAttributesWithValuesAndWithoutValueUsingQuoteAndDoubleQuote()
        {
            std::cout << "Test three attributes with values and without value using quote and double quote ..." << std::endl;

            std::string attributes = "id=\"main\" class=\'content\' checked";
            HtmlCursor htmlCursor(attributes);
            AttributeLexer attributeLexer(htmlCursor);

            if (!attributeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving attribute failed";
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "checked"));

            std::vector<HtmlToken *> actualTokens = attributeLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
        }
    } // namespace Lexer

} // namespace Test