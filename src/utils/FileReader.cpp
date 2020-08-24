#include "FileReader.h"

namespace FileReader
{
    std::string readFileAsString(std::string filePath)
    {
        std::ifstream t(filePath);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }
} // namespace FileReader