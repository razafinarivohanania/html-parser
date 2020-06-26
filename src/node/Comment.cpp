#include "Comment.h"

Comment::Comment() : Node(NodeType::COMMENT),
                     m_comment("")
{
}

void Comment::setComment(std::string comment)
{
    m_comment = comment;
}

std::string Comment::getComment()
{
    return m_comment;
}

std::string Comment::toHtml()
{
    return "<!--" + m_comment + "-->";
}

Comment::~Comment()
{
}