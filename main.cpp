#include <iostream>

#include <string>
#include "src/node/tag/Tag.h"
#include "src/node/Text.h"
#include "src/node/tag/Attribute.h"
#include "src/node/Comment.h"

int main()
{

    Attribute *href = new Attribute();
    href->setName("href")->setValue("https://www.google.com");

    Attribute *disable = new Attribute();
    disable->setName("disable")
        ->setValue("true")
        ->setNoValue(true);

    Text *text = new Text();
    text->setText("Google");

    Attribute *src = new Attribute();
    src->setName("src")->setValue("https://www.google.com/img.jpg");

    Tag *img = new Tag();
    img->setIsOrphan(true)
        ->setName("img")
        ->addAttribute(src);

    Comment *comment = new Comment();
    comment->setComment("It's a comment");
    
    Tag a;
    a.setName("a")
        ->addAttribute(href)
        ->addAttribute(disable)
        ->addNode(comment)
        ->addNode(text)
        ->addNode(img);

    std::cout << a.toHtml() << std::endl;
}