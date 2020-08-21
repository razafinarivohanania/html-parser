#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>

namespace StringUtils {
    bool equalsIgnoreCase(const std::string &string1, const std::string &string2);
    bool containsCharacter(const std::string &string, const char character);
    bool isSpaceFamily(const char character);
}

#endif