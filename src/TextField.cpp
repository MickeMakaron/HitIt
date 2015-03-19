/****************************************************************
****************************************************************
*
* HitIt - Top-down 2D game where the goal is NOT to hit the music.
* Copyright (C) 2015 Mikael Hernvall (mikael.hernvall@gmail.com)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************
****************************************************************/



////////////////////////////////////////////////
// C++ Standard Library
#include <cassert>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Event.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "TextField.hpp"
////////////////////////////////////////////////

TextField::TextField(sf::Text text, const sf::SoundBuffer& soundBuffer, unsigned int maxLength)
: GUIElement()
, mText(text)
, mSoundPlayer(soundBuffer)
, mInsertionCursor(sf::Vector2f(mText.getCharacterSize() / 10.f, mText.getGlobalBounds().height))
, mMaxLength(maxLength)
{
    sf::FloatRect textBounds = mText.getGlobalBounds();
    mText.setColor(sf::Color::Black);

    mInsertionCursor.setPosition(textBounds.left + textBounds.width, textBounds.top);
    mInsertionCursor.setFillColor(mText.getColor());
}

void TextField::handleEventCurrent(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Key::Return:
            case sf::Keyboard::Key::Escape:
                toggleActivation();
                break;

            case sf::Keyboard::Key::BackSpace:
                erase();
                break;

            default:
                break;
        }
    }
    else if(event.type == sf::Event::TextEntered && ((event.text.unicode >= ' ' && event.text.unicode <= '~') || event.text.unicode >= 160))
            insert(event.text.unicode);
}


bool TextField::isActivatable() const
{
    return true;
}

void TextField::select()
{
    mText.setColor(sf::Color::White);
}

void TextField::deselect()
{
    mSoundPlayer.play();
    mText.setColor(sf::Color::Black);
}

void TextField::activate()
{
    mSoundPlayer.play();
}

void TextField::deactivate()
{
    mSoundPlayer.play();
}

bool TextField::isSelectable() const
{
    return true;
}

void TextField::insert(char character)
{

    sf::String str = mText.getString();

    if(str.getSize() >= mMaxLength)
        return;

    str.insert(str.getSize(), sf::String(character));

    float width = mText.getGlobalBounds().width;
    mText.setString(str);
    float dWidth = mText.getGlobalBounds().width - width;

    mInsertionCursor.move(dWidth, 0);
}

void TextField::erase()
{
    sf::String str = mText.getString();
    if(str.getSize() != 0)
        str.erase(str.getSize() - 1, 1);

    float width = mText.getGlobalBounds().width;
    mText.setString(str);
    float dWidth = mText.getGlobalBounds().width - width;

    mInsertionCursor.move(dWidth, 0);
}

void TextField::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mText, states);

    if(isActive())
        target.draw(mInsertionCursor, states);
}

sf::FloatRect TextField::getBoundingRect() const
{
    return getWorldTransform().transformRect(mText.getGlobalBounds());
}

std::string TextField::getString() const
{
    return mText.getString();
}
