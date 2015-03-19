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

#ifndef HITIT_HEALTHBAR_HPP
#define HITIT_HEALTHBAR_HPP

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <list>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RectangleShape.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "RectangleNode.hpp"
class Player;
////////////////////////////////////////////////

class HealthBar : public RectangleNode
{
    public:
        /**
         * \brief Constructor
         *
         * \param texture texture of ONE hitpoint.
         * \param player player node to track.
         */
        HealthBar(const sf::Texture& texture, const Player& player);


        /**
         * \brief Update bar.
         */
        virtual void updateCurrent();

    private:
        /**
         * \brief Offset current hp
         *
         * \param hp amount to offset.
         */
        void offsetHp(int hp);

        /**
         * \brief Update rectangle shape.
         */
        void updateShape();

    private:
        const Player&           mPlayer; ///< Player node to keep track of.
        int                     mNumHitPoints;
};


/************************************************
 * \class HealthBar
 *
 * For displaying the health of the player node.
 *
************************************************/


#endif // HITIT_HEALTHBAR_HPP
