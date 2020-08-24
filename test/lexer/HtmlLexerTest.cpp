#include "HtmlLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testSimpleHtml()
        {
            std::string html = FileReader::readFileAsString("test/resources/sample-html.html");
            HtmlLexer htmlLexer(&html);
            std::vector<HtmlToken *> expectedToken = htmlLexer.getTokens();
            Test::Lexer::printTokens(expectedToken);
            Test::Lexer::emptyTokensAndFreeMemories(expectedToken);

        }
    } // namespace Lexer
} // namespace Test