#ifndef NODE_TEXT_H
#define NODE_TEXT_H

#include <string>
#include "Node.h"

class Text : public Node
{
public:
    Text();
    void setText(std::string text);
    std::string getText();

    virtual std::string toHtml();
    virtual ~Text();
private:
    std::string m_text;
};

#endif