#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>
#include <sstream>

namespace FileReader
{
    std::string readFileAsString(std::string filePath);
}

#endif