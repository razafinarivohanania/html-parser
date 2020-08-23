#include "CommentLexer.h"

CommentLexer::CommentLexer(HtmlCursor &htmlCursor) : htmlCursor(htmlCursor)
{
    token = nullptr;
    beginTagFound = false;
    commentFound = false;

    process();
}

bool CommentLexer::isBeginTagFound()
{
    return beginTagFound;
}

bool CommentLexer::isCommentFound()
{
    return commentFound;
}

HtmlToken *CommentLexer::getToken()
{
    return token;
}

/**
 * Treat following syntaxes :
 * <!---->
 * <!-- -->
 * <!--x-->
 * <!-- x -->
 * <!--xx-->
 * <!-- xx -->
 **/
void CommentLexer::process()
{
    std::string beginComment = "<!--";
    if (!htmlCursor.startsWith(beginComment, false))
    {
        return;
    }

    beginTagFound = true;
    htmlCursor.skipBlocs(beginComment.size());

    std::string endComment = "-->";
    Result result = htmlCursor.getStringBefore(endComment);
    if (!result.success)
    {
        return;
    }

    commentFound = true;
    std::string comment = result.content;
    htmlCursor.skipBlocs(comment.size() + endComment.size());
    token = new HtmlToken(TokenType::COMMENT, comment);
}