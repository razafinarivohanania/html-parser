#include "DoctypeLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testDoctype(const std::string &html, const std::string &expectedDoctype)
        {
            std::cout << "Test " << html << " ..." << std::endl;

            std::string doctype = html;
            HtmlCursor htmlCursor(doctype);
            DoctypeLexer doctypeLexer(htmlCursor);

            if (!doctypeLexer.isSuccess())
            {
                std::cout << "ERROR : Retrieving doctype failed" << std::endl;
                return;
            }

            HtmlToken *expectedToken = new HtmlToken(TokenType::DOCTYPE, expectedDoctype);
            HtmlToken *actualToken = doctypeLexer.getToken();
            if (Test::Lexer::testToken(expectedToken, actualToken)) {
                std::cout << "Test success" << std::endl << std::endl;
            }

            delete expectedToken;
            delete actualToken;
        }
    } // namespace Lexer
} // namespace Test