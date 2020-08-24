#include "HtmlLexerTest.h"

static void testHtml(const std::string &filePath)
{
    std::string html = FileReader::readFileAsString(filePath);
    HtmlLexer htmlLexer(&html);
    std::vector<HtmlToken *> expectedToken = htmlLexer.getTokens();
    Test::Lexer::printTokens(expectedToken);
    Test::Lexer::emptyTokensAndFreeMemories(expectedToken);
}

namespace Test
{
    namespace Lexer
    {
        void testSimpleHtml()
        {
            testHtml("test/resources/complexe-html.html");
        }

        void testComplexHtml()
        {
            testHtml("test/resources/youtube.html");
        }
    } // namespace Lexer
} // namespace Test