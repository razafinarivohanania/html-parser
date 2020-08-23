#include "AttributeLexerTest.h"

namespace Test
{
    void testOneAttributeWithoutValue()
    {
        HtmlCursor htmlCursor("checked");
        AttributeLexer attributeLexer(htmlCursor);
        std::vector<HtmlToken *> tokens = attributeLexer.getTokens();

        if (attributeLexer.hasError()) {
            std::cout << "ERROR : " << attributeLexer.getError() << std::endl;
            return;
        }

        if (tokens.size() != 1)
        {
            std::cout << "ERROR : Expected tokens size [1] but found [" << tokens.size() << "]" << std::endl;
            return;
        }

        HtmlToken *htmlToken = tokens.at(0);
        std::string expectedToken = "HtmlToken { type : ATTRIBUTE_NAME_WITHOUT_VALUE, value : checked }";

        if (htmlToken->toString() != expectedToken) {
            std::cout << "ERROR : Expected token" << std::endl;
            std::cout << "        " << expectedToken << std::endl;
            std::cout << "but found" << std::endl;
            std::cout << "        " << htmlToken->toString() << std::endl;
        } else {
            std::cout << htmlToken->toString() << std::endl;
        }

        delete htmlToken;
    }
} // namespace Test