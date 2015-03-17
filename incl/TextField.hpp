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

#ifndef HITIT_TEXTFIELD_HPP
#define HITIT_TEXTFIELD_HPP

////////////////////////////////////////////////
// C++ Standard Library
#include <limits>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "GUIElement.hpp"
class SoundPlayer;
////////////////////////////////////////////////

class TextField : public GUIElement
{
    public:
        TextField(sf::Text text, SoundPlayer& soundPlayer, unsigned int maxLength = std::numeric_limits<unsigned int>::max());

        virtual sf::FloatRect getBoundingRect() const;

        virtual void handleEvent(const sf::Event& event);

        virtual bool isActivatable() const;
        virtual bool isSelectable() const;

        std::string getString() const;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void activate();
        virtual void deactivate();

        virtual void select();
        virtual void deselect();

        void erase();
        void insert(char character);


    private:
       sf::Text             mText;
       SoundPlayer&         mSoundPlayer;
       sf::RectangleShape   mInsertionCursor;
       unsigned int         mMaxLength;
};


#endif // HITIT_TEXTFIELD_HPP
