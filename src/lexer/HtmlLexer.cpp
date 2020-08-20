#include "HtmlLexer.h"

HtmlLexer::HtmlLexer(const std::string &html)
{
    htmlSize = html.size();
    currentColumn = 0;
    currentLine = 0;
    currentIndex = 0;
    error = "";
    this->html = html;
    process();
}

void HtmlLexer::process()
{
    if (htmlSize == 0)
    {
        error = "Html is empty";
        return;
    }

    skipSpaceFamilies();

    char currentCharacter = getCurrentCharacter();
    if (currentCharacter != '<')
    {
        buildUnexpectedCharacterError('<');
        return;
    }

    if (!advance())
    {
        error = "HTML not ended correctly";
        return;
    }

    if (getCurrentCharacter() == '!')
    {
        if (!advance())
        {
            error = "HTML not ended correctly";
            return;
        }

        getDoctype();
    }
}

bool HtmlLexer::hasError()
{
    return !error.empty();
}

std::string HtmlLexer::getError()
{
    return error;
}

void HtmlLexer::skipSpaceFamilies()
{
    while (true)
    {
        if (StringUtils::isSpaceFamily(getCurrentCharacter()))
        {
            if (advance())
            {
                continue;
            }
            else
            {
                return;
            }
        }

        return;
    }
}

std::string HtmlLexer::toString()
{
    std::string tokens = "";

    std::cout << htmlTokens.size() << std::endl;
    for (const auto &htmlToken : htmlTokens)
    {
        std::cout << htmlToken->toString() << std::endl;
    }

    return tokens;
}

bool HtmlLexer::advance()
{
    if (currentIndex >= htmlSize - 1)
    {
        return false;
    }

    if (getCurrentCharacter() == '\n')
    {
        currentLine++;
        currentColumn = 0;
    }
    else
    {
        currentColumn++;
    }

    currentIndex++;
    return true;
}

char HtmlLexer::getCurrentCharacter()
{
    return html[currentIndex];
}

void HtmlLexer::getDoctype()
{
    int oldLine = currentLine;
    int oldColumn = currentColumn;

    std::string successiveAlphabet = getSuccessiveAlphabet();
    if (!StringUtils::equalsIgnoreCase(successiveAlphabet, "DOCTYPE"))
    {
        error = "Expected keyword \"DOCTYPE\" instead of \"" + successiveAlphabet + "\" at line [";
        error += std::to_string(oldLine + 1);
        error += "] and column [";
        error += std::to_string(oldColumn + 1) + "]";
        return;
    }

    char currentCharacter = getCurrentCharacter();
    if (!StringUtils::isSpaceFamily(currentCharacter))
    {
        buildUnexpectedCharacterError(' ');
        return;
    }

    skipSpaceFamilies();

    successiveAlphabet = getSuccessiveAlphabet();

    if (successiveAlphabet.empty())
    {
        buildUnexpectedCharacterError();
        return;
    }

    if (getCurrentCharacter() != '>')
    {
        buildUnexpectedCharacterError('>');
        return;
    }

    HtmlToken *htmlToken = new HtmlToken(TokenType::DOCTYPE, successiveAlphabet);
    htmlTokens.push_back(htmlToken);
}

std::string HtmlLexer::getSuccessiveAlphabet()
{
    std::string successiveAlphabet = "";
    int alphabetSize = ALPHABET.size();

    while (true)
    {
        char currentCharacter = getCurrentCharacter();
        bool alphabetFound = false;

        for (int i = 0; i < alphabetSize; i++)
        {
            if (currentCharacter == ALPHABET[i])
            {
                alphabetFound = true;
                break;
            }
        }

        if (alphabetFound)
        {
            successiveAlphabet.push_back(currentCharacter);
            advance();
        }
        else
        {
            return successiveAlphabet;
        }
    }
}

void HtmlLexer::buildUnexpectedCharacterError(char expectedCharacter)
{
    error = "Expected character \"";
    error += expectedCharacter;
    error += "\" instead of \"";
    error += getCurrentCharacter();
    error += "\" at line [";
    error += std::to_string(currentLine + 1);
    error += "] and column [";
    error += std::to_string(currentColumn + 1) + "].";
}

void HtmlLexer::buildUnexpectedCharacterError()
{
    error = "Unexpected character \"";
    error += getCurrentCharacter();
    error += "\" at line [";
    error += std::to_string(currentLine + 1);
    error += "] and column [";
    error += std::to_string(currentColumn + 1) + "].";
}

HtmlLexer::~HtmlLexer()
{
    for (const auto &htmlToken : htmlTokens)
    {
        delete htmlToken;
    }
}