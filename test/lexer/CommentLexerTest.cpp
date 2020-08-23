#include "CommentLexerTest.h"

namespace Test
{
    namespace Lexer
    {
        void testEmptyComment()
        {
            std::cout << "Test empty comment ..." << std::endl;

            std::string html = "<!---->";
            HtmlCursor htmlCursor(html);
            CommentLexer commentLexer(htmlCursor);

            if (!commentLexer.isCommentFound())
            {
                std::cout << "ERROR : Retrieving comment failed" << std::endl;
                return;
            }

            HtmlToken *expectedToken = new HtmlToken(TokenType::COMMENT, "");
            HtmlToken *actualToken = commentLexer.getToken();
            if (Test::Lexer::testToken(expectedToken, actualToken))
            {
                std::cout << "Test success" << std::endl
                          << std::endl;
            }

            delete expectedToken;
            delete actualToken;
        }

        void testNotEmptyComment()
        {
            std::cout << "Test not empty comment ..." << std::endl;

            std::string html = "<!-- Comment -->";
            HtmlCursor htmlCursor(html);
            CommentLexer commentLexer(htmlCursor);

            if (!commentLexer.isCommentFound())
            {
                std::cout << "ERROR : Retrieving comment failed" << std::endl;
                return;
            }

            HtmlToken *expectedToken = new HtmlToken(TokenType::COMMENT, " Comment ");
            HtmlToken *actualToken = commentLexer.getToken();
            if (Test::Lexer::testToken(expectedToken, actualToken))
            {
                std::cout << "Test success" << std::endl
                          << std::endl;
            }

            delete expectedToken;
            delete actualToken;
        }

        void testNotComment()
        {
            std::cout << "Test not comment ..." << std::endl;

            std::string html = "<span>Not comment</span>";
            HtmlCursor htmlCursor(html);
            CommentLexer commentLexer(htmlCursor);

            if (!commentLexer.isCommentFound())
            {
                std::cout << "Test success" << std::endl
                          << std::endl;

                return;
            }

            std::cout << "Not comment must be found" << std::endl;
            HtmlToken *actualToken = commentLexer.getToken();
            if (actualToken != nullptr)
            {
                delete actualToken;
            }
        }

        void testNotEndingComment()
        {
            std::cout << "Test not ending comment ..." << std::endl;

            std::string html = "<!-- Not ending comment";
            HtmlCursor htmlCursor(html);
            CommentLexer commentLexer(htmlCursor);

            if (!commentLexer.isCommentFound())
            {
                std::cout << "Test success" << std::endl
                          << std::endl;

                return;
            }

            std::cout << "Not comment must be found" << std::endl;
            HtmlToken *actualToken = commentLexer.getToken();
            if (actualToken != nullptr)
            {
                delete actualToken;
            }
        }
    } // namespace Lexer
} // namespace Test