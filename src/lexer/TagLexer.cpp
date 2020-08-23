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
    //TODO
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
        htmlCursor.advance();
        getEndTag();
    }
    else
    {
        getBeginOrOrphanTag();
    }
}

void TagLexer::getEndTag()
{
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