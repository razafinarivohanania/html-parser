rm ./html-parser

g++ -std=c++11 \
-Wall \
main.cpp \
src/lexer/HtmlCursor.cpp \
src/lexer/HtmlCursor.h \
src/lexer/Lexer.cpp \
src/lexer/Lexer.h \
src/lexer/HtmlLexer.cpp \
src/lexer/HtmlLexer.h \
src/lexer/HtmlToken.cpp \
src/lexer/HtmlToken.h \
src/lexer/AttributeLexer.cpp \
src/lexer/AttributeLexer.h \
src/lexer/TagLexer.cpp \
src/lexer/TagLexer.h \
src/utils/StringUtils.cpp \
src/utils/StringUtils.h \
src/utils/FileReader.cpp \
src/utils/FileReader.h \
-o html-parser

./html-parser