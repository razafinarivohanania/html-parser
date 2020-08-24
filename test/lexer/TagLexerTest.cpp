#include "TagLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testBeginTag()
        {
            std::cout << "Test begin tag ..." << std::endl;

            std::string html = "<div>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

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

        void testBeginTagWithAttributeWithoutValue()
        {
            std::cout << "Test begin tag with attribute without value ..." << std::endl;

            std::string html = "<div fullWidth>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving begin tag with attribute failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::BEGIN_TAG, "div"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "fullWidth"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testBeginTagWithAttributeWithValue()
        {
            std::cout << "Test begin tag with attribute with value ..." << std::endl;

            std::string html = "<div style=\"background-color:white; color: blue\">";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving begin tag with attribute failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::BEGIN_TAG, "div"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "style"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "background-color:white; color: blue"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testBeginTagWithTwoAttributesWithoutValues()
        {
            std::cout << "Test begin tag with two attributes without values ..." << std::endl;

            std::string html = "<div fullHeight focus>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving begin tag with attribute failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::BEGIN_TAG, "div"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "fullHeight"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "focus"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testBeginTagWithTwoAttributesWithValues()
        {
            std::cout << "Test begin tag with two attributes with values ..." << std::endl;

            std::string html = "<div id=\"main\" class='content'>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving begin tag with attribute failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::BEGIN_TAG, "div"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "id"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "main"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "content"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testBeginTagWithAttributeWithoutValueAndAttributeWithValue()
        {
            std::cout << "Test begin tag with attribute without value and attribute with value ..." << std::endl;

            std::string html = "<div rapid v-for='loop'>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving begin tag with attribute failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::BEGIN_TAG, "div"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "rapid"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "v-for"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "loop"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testBeginTagWithAttributeWithValueAndAttributeWithoutValue()
        {
            std::cout << "Test begin tag with attribute with value and attribute without value ..." << std::endl;

            std::string html = "<div v-for=\"loop\" rapid >";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving begin tag with attribute failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::BEGIN_TAG, "div"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "v-for"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "loop"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "rapid"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testOrphanTag()
        {
            std::cout << "Test orphan tag ..." << std::endl;

            std::string html = "<br/>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving orphan tag failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ORPHAN_TAG, "br"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testOrphanTagWithAttributeWithoutValue()
        {
            std::cout << "Test orphan tag without attribute value ..." << std::endl;

            std::string html = "<br clicked/>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving orphan tag failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ORPHAN_TAG, "br"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "clicked"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testOrphanTagWithAttributeWithValue()
        {
            std::cout << "Test orphan tag with attribute ..." << std::endl;

            std::string html = "<br class='skipLine'/>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving orphan tag failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ORPHAN_TAG, "br"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "skipLine"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testOrphanTagWithTwoAttributesWithoutValues()
        {
            std::cout << "Test orphan tag with two attributes without values ..." << std::endl;

            std::string html = "<br fullWidth fullHeight/>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving orphan tag failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ORPHAN_TAG, "br"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "fullWidth"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "fullHeight"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testOrphanTagWithTwoAttributesWithValues()
        {
            std::cout << "Test orphan tag with two attributes with values ..." << std::endl;

            std::string html = "<br class='line' ng-if=\"true\"/>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving orphan tag failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ORPHAN_TAG, "br"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "class"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "line"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "ng-if"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "true"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testOrphanTagWithAttributeWithoutValueAndAttributeWithValue()
        {
            std::cout << "Test orphan tag with attribute without value and attribute with value ..." << std::endl;

            std::string html = "<br test data-url=\"url\"/>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving orphan tag failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ORPHAN_TAG, "br"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "test"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "data-url"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "url"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testOrphanTagWithAttributeWithValueAndAttributeWithoutValue()
        {
            std::cout << "Test orphan tag with attribute with value and attribute without value ..." << std::endl;

            std::string html = "<br data-url='url' test />";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving orphan tag failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::ORPHAN_TAG, "br"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITH_VALUE, "data-url"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_VALUE, "url"));
            expectedTokens.push_back(new HtmlToken(TokenType::ATTRIBUTE_NAME_WITHOUT_VALUE, "test"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }

        void testEndTag()
        {
            std::cout << "Test end tag ..." << std::endl;

            std::string html = "</div>";
            HtmlCursor htmlCursor(&html);
            TagLexer tagLexer(&htmlCursor);

            if (!tagLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving end tag failed" << std::endl;
            }

            std::vector<HtmlToken *> expectedTokens;
            expectedTokens.push_back(new HtmlToken(TokenType::END_TAG, "div"));

            std::vector<HtmlToken *> actualTokens = tagLexer.getTokens();
            Test::Lexer::testTokens(expectedTokens, actualTokens);
            Test::Lexer::emptyTokensAndFreeMemories(expectedTokens, actualTokens);
            std::cout << std::endl;
        }
    } // namespace Lexer
} // namespace Test