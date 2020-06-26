#include "Node.h"

Node::Node(NodeType nodeType) : m_nodeType(nodeType)
{
}

NodeType Node::getNodeType()
{
    return m_nodeType;
}

Node::~Node()
{
}