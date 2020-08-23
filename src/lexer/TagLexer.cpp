#include "TagLexer.h"

TagLexer::TagLexer(HtmlCursor &htmlCursor) : htmlCursor(htmlCursor)
{
    initialPosition = htmlCursor.getPosition();
    success = false;
    process();
}

std::vector<HtmlToken *> TagLexer::getTokens()
{
    return tokens;
}

/** Treat syntaxes
 * <x>
 * </x>
 * <x/>
*  <x a='a' b='b'/>
 * <x a='a' b="b"/>
 * <x a="a" b='b'/>
 * <x a="a" b="b"/>
 * <x a>
 * <x a='a'>
 * <x a="a">
 * <x a='a' b='b'>
 * <x a='a' b="b">
 * <x a="a" b='b'>
 * <x a="a" b="b">
 **/
void TagLexer::process()
{
    if (htmlCursor.endReached())
    {
        success = true;
        return;
    }

    if (!htmlCursor.isLeftArrowCharacter())
    {
        return;
    }

    htmlCursor.advance();

    bool endTag = false;
    if (htmlCursor.isSlashCharacter())
    {
        endTag = true;
        htmlCursor.advance();
    }

    Result tagName = htmlCursor.getStringBeforeFirstCharacterFound(" />");
    if (!tagName.success || !isValidTagName(tagName.content))
    {
        return;
    }

    htmlCursor.skipSpacesFamily();

    if (htmlCursor.isSlashCharacter())
    {
        if (endTag)
        {
            return;
        }

        htmlCursor.advance();

        if (!htmlCursor.isRightArrowCharacter())
        {
            return;
        }

        htmlCursor.advance();

        success = true;
        HtmlToken *htmlToken = new HtmlToken(TokenType::ORPHAN_TAG, tagName.content);
        tokens.push_back(htmlToken);
        return;
    }

    AttributeLexer attributeLexer(htmlCursor);
    if (!attributeLexer.isSuccess())
    {
        return;
    }

    for (auto &token : attributeLexer.getTokens())
    {
        tokens.push_back(token);
    }

    if (htmlCursor.isSlashCharacter())
    {
        if (endTag)
        {
            return;
        }

        htmlCursor.advance();

        if (!htmlCursor.isRightArrowCharacter())
        {
            return;
        }

        htmlCursor.advance();

        success = true;
        HtmlToken *htmlToken = new HtmlToken(TokenType::ORPHAN_TAG, tagName.content);
        tokens.push_back(htmlToken);
        return;
    }

    htmlCursor.advance();

    success = true;
    HtmlToken *htmlToken = new HtmlToken(TokenType::BEGIN_TAG, tagName.content);
    tokens.push_back(htmlToken);
}

bool TagLexer::isValidTagName(const std::string &tagName)
{
    if (tagName.empty() || StringUtils::containsCharacter(INVALID_BEGIN_CHARACTER_TAG, tagName[0]))
    {
        return false;
    }

    int size = tagName.size();
    for (int i = 1; i < size; i++)
    {
        if (StringUtils::containsCharacter(INVALID_MIDDLE_CHARACTER_TAG, tagName[i]))
        {
            return false;
        }
    }

    return true;
}

int TagLexer::getInitialPosition()
{
    return initialPosition;
}

bool TagLexer::isSuccess()
{
    return success;
}