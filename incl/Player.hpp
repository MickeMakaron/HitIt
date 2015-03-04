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

#ifndef HITIT_PLAYER_HPP
#define HITIT_PLAYER_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "SpriteNode.hpp"
////////////////////////////////////////////////


class Player : public SpriteNode
{
    public:
        Player(const sf::Texture& texture, int hp, sf::Vector2f position = sf::Vector2f(0.f, 0.f));

        virtual bool            isMarkedForRemoval() const;

        void damage(int points);
        void destroy();
        bool isDestroyed() const;
        void accelerate(float a);

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void updateCurrent();

    private:
        int             mHp;
        float           mMovementSpeed;
        float           mDiagonalMovementSpeed;
};

#endif // HITIT_PLAYER_HPP
