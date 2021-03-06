#include "StringUtils.h"

namespace StringUtils
{
    bool equalsIgnoreCase(const std::string &string1, const std::string &string2)
    {
        int string1Size = string1.size();
        int string2Size = string2.size();

        if (string1Size != string2Size)
        {
            return false;
        }

        if (string1Size == 0)
        {
            return true;
        }

        for (int i = 0; i < string1Size; i++)
        {
            if (std::tolower(string1[i]) != std::tolower(string2[i]))
            {
                return false;
            }
        }

        return true;
    }

    bool containsCharacter(const std::string &string, const char character)
    {
        int size = string.size();
        for (int i = 0; i < size; i++)
        {
            if (string[i] == character)
            {
                return true;
            }
        }

        return false;
    }

    bool equalsIgnoreCase(char character1, char character2)
    {
        return std::tolower(character1) == std::tolower(character2);
    }

    bool isSpaceFamily(const char character)
    {
        return character == ' ' ||
               character == '\n' ||
               character == '\r' ||
               character == '\t';
    }

    std::string encodeNewLines(std::string &text)
    {
        std::string encodedNewLines = "";
        int size = text.size();

        for (int i = 0; i < size; i++)
        {
            char character = text[i];
            if (character == '\n')
            {
                encodedNewLines.push_back('\\');
                encodedNewLines.push_back('n');
            } else {
                encodedNewLines.push_back(character);
            }
        }

        return encodedNewLines;
    }
} // namespace StringUtils
