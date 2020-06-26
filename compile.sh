g++ -std=c++11 \
-Wall \
main.cpp \
src/node/Node.cpp \
src/node/Node.h \
src/node/tag/Attribute.cpp \
src/node/tag/Attribute.h \
src/node/tag/Tag.cpp \
src/node/tag/Tag.h \
src/node/Comment.cpp \
src/node/Comment.h \
src/node/NodeType.h \
src/node/Text.cpp \
src/node/Text.h \
src/parser/ActionParser.h \
src/parser/AttributeParser.cpp \
src/parser/AttributeParser.h \
-o html-parser

./html-parser