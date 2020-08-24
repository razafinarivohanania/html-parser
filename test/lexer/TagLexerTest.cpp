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