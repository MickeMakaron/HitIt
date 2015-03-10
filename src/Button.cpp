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
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RenderTarget.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "Button.hpp"
#include "SoundPlayer.hpp"
////////////////////////////////////////////////

Button::Button(const sf::Text& text, SoundPlayer& soundPlayer, Callback callback)
: mText(text)
, mSoundPlayer(soundPlayer)
, mCallback(callback)
{
    sf::FloatRect textBounds = mText.getGlobalBounds();
    setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    mText.setColor(sf::Color::Black);
}

void Button::select()
{
    GUIElement::select();
    mText.setColor(sf::Color::White);
}

void Button::deselect()
{
    GUIElement::deselect();
    mSoundPlayer.play();
    mText.setColor(sf::Color::Black);
}

void Button::activate()
{
    mSoundPlayer.play();
    mCallback();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mText, states);
}

bool Button::isSelectable() const
{
    return true;
}

sf::FloatRect Button::getBoundingRect() const
{
    return getWorldTransform().transformRect(mText.getGlobalBounds());
}
