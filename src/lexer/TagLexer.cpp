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
        return;
    }

    if (!htmlCursor.isLeftArrowCharacter())
    {
        return;
    }

    htmlCursor.advance();

    if (htmlCursor.isSlashCharacter())
    {
        getEndTag();
    }
    else
    {
        getBeginOrOrphanTag();
    }
}

void TagLexer::getEndTag()
{
    htmlCursor.advance();
    Result tagName = htmlCursor.getStringBeforeFirstCharacterFound(" >");
    if (!tagName.success || !isValidTagName(tagName.content))
    {
        return;
    }

    htmlCursor.skipBlocs(tagName.content.size());

    if (htmlCursor.isSpaceCharacterFamily())
    {
        htmlCursor.skipSpacesFamily();
    }

    if (!htmlCursor.isRightArrowCharacter())
    {
        return;
    }

    htmlCursor.advance();
    success = true;
    tokens.push_back(new HtmlToken(TokenType::END_TAG, tagName.content));
}

void TagLexer::getBeginOrOrphanTag()
{
    Result tagName = htmlCursor.getStringBeforeFirstCharacterFound(" />");
    if (!tagName.success || !isValidTagName(tagName.content))
    {
        return;
    }

    htmlCursor.skipBlocs(tagName.content.size());

    if (htmlCursor.isSpaceCharacterFamily())
    {
        htmlCursor.skipSpacesFamily();
    }

    if (htmlCursor.isSlashCharacter())
    {
        getOrphanTag(tagName.content);
        return;
    }

    if (htmlCursor.isRightArrowCharacter())
    {
        htmlCursor.advance();
        success = true;
        tokens.push_back(new HtmlToken(TokenType::BEGIN_TAG, tagName.content));
        return;
    }

    //TODO
}

void TagLexer::getOrphanTag(const std::string &tagName)
{
    htmlCursor.advance();

    if (!htmlCursor.isRightArrowCharacter())
    {
        return;
    }

    htmlCursor.advance();
    success = true;
    tokens.push_back(new HtmlToken(TokenType::ORPHAN_TAG, tagName));
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