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

    bool isSpaceFamily(const char character)
    {
        return character == ' ' ||
               character == '\n' ||
               character == '\r' ||
               character == '\t';
    }
} // namespace StringUtils
