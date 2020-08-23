#include "TokenTest.h"

static void emptyTokensAndFreeMemories(std::vector<HtmlToken *> tokens)
{
    for (auto &token : tokens)
    {
        if (token != nullptr)
        {
            delete token;
        }
    }

    int size = tokens.size();
    for (int i = 0; i < size; i++)
    {
        tokens.pop_back();
    }
}

static void printTokens(std::vector<HtmlToken *> tokens)
{
    for (auto &token : tokens)
    {
        std::cout << token->toString() << std::endl;
    }
}

static bool testToken(HtmlToken *expectedToken, HtmlToken *actualToken, const int index)
{
    if (expectedToken->getType() != actualToken->getType())
    {
        std::cout << "ERROR : Expected type [" << expectedToken->getTypeAsString() << "] but found [" << actualToken->getTypeAsString() << "]";
        if (index >= 0)
        {
            std::cout << " on [" << index << "] index";
        }

        std::cout << std::endl;
        return false;
    }

    if (expectedToken->getValue() != actualToken->getValue())
    {
        std::cout << "ERROR : Expected value [" << expectedToken->getValue() << "] but found [" << actualToken->getValue() << "]";
        if (index >= 0)
        {
            std::cout << " on [" << index << "] index";
        }

        std::cout << std::endl;
        return false;
    }

    return true;
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
                printTokens(actualTokens);
                std::cout << "ERROR : Expected tokens size [" << expectedSize << "] but found [" << actualTokens.size() << "]" << std::endl
                          << std::endl;

                return;
            }

            for (size_t i = 0; i < expectedSize; i++)
            {
                if (!testToken(expectedTokens[i], actualTokens[i], i))
                {
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

        bool testToken(HtmlToken *expectedToken, HtmlToken *actualToken)
        {
            return testToken(expectedToken, actualToken, -1);
        }
    } // namespace Lexer
} // namespace Test
