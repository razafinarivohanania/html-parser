#ifndef NODE_H
#define NODE_H

#include <string>
#include "NodeType.h"

class Node
{
public:
    Node(NodeType nodeType);
    NodeType getNodeType();

    virtual std::string toHtml() = 0;
private:
    NodeType m_nodeType;
};

#endif
