#include "DoctypeLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testDoctype(const std::string &html, const std::string &expectedDoctype)
        {
            std::cout << "Test " << html << " ..." << std::endl;

            std::string doctype = html;
            HtmlCursor htmlCursor(&doctype);
            DoctypeLexer doctypeLexer(&htmlCursor);

            if (!doctypeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving doctype failed" << std::endl;
                return;
            }

            HtmlToken *expectedToken = new HtmlToken(TokenType::DOCTYPE, expectedDoctype);
            HtmlToken *actualToken = doctypeLexer.getToken();
            if (Test::Lexer::testToken(expectedToken, actualToken))
            {
                std::cout << "Test success" << std::endl;
            }

            delete expectedToken;
            delete actualToken;
            std::cout << std::endl;
        }

        void testNotDoctype()
        {
            std::cout << "Test not doctype ..." << std::endl;

            std::string html = "<span>Not doctype</span>";
            HtmlCursor htmlCursor(&html);
            DoctypeLexer doctypeLexer(&htmlCursor);

            if (!doctypeLexer.isSuccess())
            {
                std::cout << "Test success" << std::endl << std::endl;
                return;
            }

            std::cout << "Not doctype expected" << std::endl;

            HtmlToken *actualToken = doctypeLexer.getToken();
            if (actualToken != nullptr)
            {
                delete actualToken;
            }

            std::cout << std::endl;
        }

        void testNotEndingDoctype()
        {
            std::cout << "Test not ending doctype  ..." << std::endl;

            std::string html = "<!doctype html";
            HtmlCursor htmlCursor(&html);
            DoctypeLexer doctypeLexer(&htmlCursor);

            if (!doctypeLexer.isSuccess())
            {
                std::cout << "Test success" << std::endl << std::endl;
                return;
            }

            std::cout << "Not ending doctype expected" << std::endl;

            HtmlToken *actualToken = doctypeLexer.getToken();
            if (actualToken != nullptr)
            {
                delete actualToken;
            }

            std::cout << std::endl;
        }
    } // namespace Lexer
} // namespace Test