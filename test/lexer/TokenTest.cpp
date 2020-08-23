#include "TokenTest.h"

static void freeMemories(std::vector<HtmlToken *> tokens)
{
    for (auto &token : tokens)
    {
        delete token;
    }
}

namespace Test
{
    namespace Lexer
    {
        void testTokens(std::vector<HtmlToken *> expectedTokens,
                        std::vector<HtmlToken *> actualTokens)
        {
            size_t expectedSize = expectedTokens.size();
            if (expectedSize != actualTokens.size())
            {
                std::cout << "ERROR : Expected tokens size [" << expectedSize << "] but found [" << actualTokens.size() << "]" << std::endl;
                return;
            }

            for (size_t i = 0; i < expectedSize; i++)
            {
                HtmlToken *expectedToken = expectedTokens[i];
                HtmlToken *actualToken = actualTokens[i];

                if (expectedToken->getType() != actualToken->getType())
                {
                    std::cout << "ERROR : Expected type [" << expectedToken->getTypeAsString() << "] but found [" << actualToken->getTypeAsString() << "] on [" << i << "] index" << std::endl;
                    return;
                }
            }

            std::cout << "Test success" << std::endl;
        };

        void freeMemories(std::vector<HtmlToken *> expectedTokens,
                          std::vector<HtmlToken *> actualTokens)
        {
            freeMemories(expectedTokens);
            freeMemories(actualTokens);
        }
    } // namespace Lexer
} // namespace Test
