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

#ifndef HITIT_BUTTON_HPP
#define HITIT_BUTTON_HPP

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Text.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "GUIElement.hpp"
class SoundPlayer;
////////////////////////////////////////////////

class Button : public GUIElement
{
    public:
        typedef std::function<void()> Callback;

        Button(const sf::Text& text, SoundPlayer& soundPlayer, Callback callback);

        virtual bool isSelectable() const;
        virtual void select();
        virtual void deselect();
        virtual void activate();

        virtual sf::FloatRect getBoundingRect() const;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text	    mText;
        SoundPlayer&    mSoundPlayer;
        Callback	    mCallback;
};


#endif // HITIT_BUTTON_HPP
