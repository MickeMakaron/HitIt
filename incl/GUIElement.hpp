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

#ifndef HITIT_GUIELEMENT_HPP
#define HITIT_GUIELEMENT_HPP

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
namespace sf
{
    class Event;
    class RenderTarget;
}
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SpriteNode.hpp"
////////////////////////////////////////////////

class GUIElement : public SpriteNode
{
    public:
        GUIElement(const sf::Texture& texture);
        virtual ~GUIElement();

        bool isSelected();

        virtual void select();
        virtual void deselect();

        virtual void update();
        virtual void handleEvent(const sf::Event& event);

        virtual void activate() = 0;

    private:
        bool mIsSelected;
};


#endif // HITIT_GUIELEMENT_HPP
