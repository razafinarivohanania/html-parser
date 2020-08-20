#include <iostream>
#include "src/lexer/HtmlLexer.h"
#include "src/lexer/HtmlToken.h"

#include <string>
#include "src/utils/FileReader.h"

int main()
{
    std::string html = FileReader::readFileAsString("index.html");
    HtmlLexer htmlLexer(html);
    if (htmlLexer.hasError()) {
        std::cout << htmlLexer.getError() << std::endl;
    } else {
        std::cout << htmlLexer.toString() << std::endl;
    }
    return 0;
}