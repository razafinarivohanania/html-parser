#include "Tag.h"

Tag::Tag() : Node(NodeType::TAG),
             m_name(""),
             m_isOrphan(false)
{
}

Tag *Tag::setName(std::string name)
{
    m_name = name;
    return this;
}

Tag *Tag::setIsOrphan(bool isOrphan)
{
    m_isOrphan = isOrphan;
    return this;
}

Tag *Tag::addAttribute(Attribute *attribute)
{
    m_attributes.push_back(attribute);
    return this;
}

Tag *Tag::addAttributes(std::vector<Attribute *> attributes)
{
    for (auto &attribute : attributes)
    {
        m_attributes.push_back(attribute);
    }

    return this;
}

Tag *Tag::addNode(Node *node)
{
    m_nodes.push_back(node);
    return this;
}

std::vector<Attribute *> Tag::getAttributes()
{
    return m_attributes;
}

std::vector<Node *> Tag::getNodes()
{
    return m_nodes;
}

std::string Tag::toHtml()
{
    if (m_name == "")
    {
        return "";
    }

    std::string tagHtml = "<" + m_name;
    std::string attributesHtml = attributesToHtml();
    if (attributesHtml != "")
    {
        tagHtml += " " + attributesHtml;
    }

    if (m_isOrphan)
    {
        tagHtml += "/>";
    }
    else
    {
        tagHtml += ">" + nodesToHtml() + "</" + m_name + ">";
    }

    return tagHtml;
}

std::string Tag::attributesToHtml()
{
    std::string attributesHtml = "";
    auto size = m_attributes.size();

    for (auto i = 0; i < size; i++)
    {
        std::string attributeHtml = m_attributes[i]->toHtml();
        if (attributeHtml != "")
        {
            attributesHtml += attributeHtml;
            if (i != size - 1)
            {
                attributesHtml += " ";
            }
        }
    }

    return attributesHtml;
}

std::string Tag::nodesToHtml()
{
    std::string nodesHtml = "";

    for (auto &node : m_nodes)
    {
        nodesHtml += node->toHtml();
    }

    return nodesHtml;
}

Tag::~Tag()
{
    for (int i = 0; i < m_attributes.size(); i++)
    {
        if (m_attributes[i] != nullptr)
        {
            delete m_attributes[i];
            m_attributes[i] = nullptr;
        }
    }

    for (int i = 0; i < m_nodes.size(); i++)
    {
        if (m_nodes[i] != nullptr)
        {
            delete m_nodes[i];
            m_nodes[i] = nullptr;
        }
    }
}