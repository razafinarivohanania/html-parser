#ifndef NODE_COMMENT_H
#define NODE_COMMENT_H

#include <string>
#include "Node.h"

class Comment : public Node
{
public:
    explicit Comment();
    void setComment(std::string comment);
    std::string getComment();

    virtual std::string toHtml();

private:
    std::string m_comment;
};

#endif