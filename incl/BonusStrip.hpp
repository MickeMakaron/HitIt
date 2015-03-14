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

#ifndef HITIT_BONUSSTRIP_HPP
#define HITIT_BONUSSTRIP_HPP



////////////////////////////////////////////////
// STD - C++ Standard Library
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/ConvexShape.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers

#include "VertexArrayNode.hpp"
////////////////////////////////////////////////


class BonusStrip : public VertexArrayNode
{
    public:
        BonusStrip(const VertexArrayNode& obstacles, sf::Vector2f windowSize, int category = 0);

	    /**
	     * \brief Update this node.
	     */
		virtual void updateCurrent();

        float    getDistance(sf::Vector2f p) const;
        float   getWidth() const;

    private:
        void initializeStrip();

        void removeQuad();
        void insertQuad(float topLeft, float botLeft, float top, float bot, bool isLeft);

        float getBusiestPosition() const;

    private:
        const VertexArrayNode&      M_OBSTACLES;
        const sf::Vector2f          M_SIZE;
        const float                 M_SCROLL_SPEED;
        std::queue<unsigned int>    mQuadIndexQueue;
        float                       mTimer;
        const float                 M_UPDATE_INTERVAL = 0.5f;
};

/************************************************
 * \class BonusStrip
 *
 *
 *
************************************************/

#endif // HITIT_BONUSSTRIP_HPP
