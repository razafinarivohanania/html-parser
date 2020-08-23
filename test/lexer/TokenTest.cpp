#include "TokenTest.h"

static void emptyTokensAndFreeMemories(std::vector<HtmlToken *> tokens)
{
    for (auto &token : tokens)
    {
        delete token;
    }

    int size = tokens.size();
    for (int i = 0; i < size; i++)
    {
        tokens.pop_back();
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
                std::cout << "ERROR : Expected tokens size [" << expectedSize << "] but found [" << actualTokens.size() << "]" << std::endl
                          << std::endl;
                return;
            }

            for (size_t i = 0; i < expectedSize; i++)
            {
                HtmlToken *expectedToken = expectedTokens[i];
                HtmlToken *actualToken = actualTokens[i];

                if (expectedToken->getType() != actualToken->getType())
                {
                    std::cout << "ERROR : Expected type [" << expectedToken->getTypeAsString() << "] but found [" << actualToken->getTypeAsString() << "] on [" << i << "] index" << std::endl
                              << std::endl;
                    return;
                }

                if (expectedToken->getValue() != actualToken->getValue())
                {
                    std::cout << "ERROR : Expected value [" << expectedToken->getValue() << "] but found [" << actualToken->getValue() << "] on [" << i << "] index" << std::endl
                              << std::endl;
                    return;
                }
            }

            std::cout << "Test success" << std::endl
                      << std::endl;
        };

        void emptyTokensAndFreeMemories(std::vector<HtmlToken *> expectedTokens,
                                        std::vector<HtmlToken *> actualTokens)
        {
            emptyTokensAndFreeMemories(expectedTokens);
            emptyTokensAndFreeMemories(actualTokens);
        }
    } // namespace Lexer
} // namespace Test
