#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>

namespace StringUtils
{
    bool equalsIgnoreCase(const std::string &string1, const std::string &string2);
    bool equalsIgnoreCase(char character1, char character2);
    bool containsCharacter(const std::string &string, const char character);
    bool isSpaceFamily(const char character);
    std::string encodeNewLines(std::string &text);
} // namespace StringUtils

#endif