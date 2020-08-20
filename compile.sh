rm ./html-parser

g++ -std=c++11 \
-Wall \
main.cpp \
src/lexer/HtmlLexer.cpp \
src/lexer/HtmlLexer.h \
src/lexer/HtmlToken.cpp \
src/lexer/HtmlToken.h \
src/utils/StringUtils.cpp \
src/utils/StringUtils.h \
src/utils/FileReader.cpp \
src/utils/FileReader.h \
-o html-parser

./html-parser