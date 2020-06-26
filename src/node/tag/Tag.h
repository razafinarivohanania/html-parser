#ifndef NODE_TAG_H
#define NODE_TAG_H

#include <vector>
#include <string>
#include <iostream>
#include "./../Node.h"
#include "Attribute.h"

class Tag : public Node
{
public:
    Tag();
    Tag *setName(std::string name);
    Tag *setIsOrphan(bool isOrphan);
    Tag *addAttribute(Attribute *attribute);
    Tag *addAttributes(std::vector<Attribute *> attributes);
    Tag *addNode(Node *node);

    std::vector<Attribute *> getAttributes();
    std::vector<Node *> getNodes();

    virtual std::string toHtml();
    ~Tag();

private:
    std::string m_name;
    bool m_isOrphan;
    std::vector<Attribute *> m_attributes;
    std::vector<Node *> m_nodes;

    std::string attributesToHtml();
    std::string nodesToHtml();
};

#endif