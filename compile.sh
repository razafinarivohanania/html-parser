rm ./html-parser

g++ -std=c++11 \
-Wall \
main.cpp \
src/lexer/DoctypeLexer.cpp \
src/lexer/DoctypeLexer.h \
src/lexer/CommentLexer.cpp \
src/lexer/CommentLexer.h \
src/lexer/HtmlCursor.cpp \
src/lexer/HtmlCursor.h \
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
test/lexer/AttributeLexerTest.h \
test/lexer/AttributeLexerTest.cpp \
test/lexer/TokenTest.h \
test/lexer/TokenTest.cpp \
test/lexer/TagLexerTest.cpp \
test/lexer/TagLexerTest.h \
-o html-parser

./html-parser