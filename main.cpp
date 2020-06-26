#include <iostream>

#include <string>
#include "src/node/tag/Tag.h"
#include "src/node/Text.h"
#include "src/node/tag/Attribute.h"
#include "src/node/Comment.h"
#include "src/parser/AttributeParser.h"

int main()
{
    std::string rawAttributes = "class='cool' id=\"first\" disable";
    AttributeParser attributeParser(rawAttributes);
    std::vector<Attribute *> attributes = attributeParser.getAttributes();
    for (std::string::size_type i = 0; i < attributes.size(); i++)
    {
        if (attributes[i] != nullptr)
        {
            std::cout << attributes[i]->toString() << std::endl;
            delete attributes[i];
            attributes[i] = nullptr;
        }
    }
}