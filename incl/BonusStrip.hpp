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
#include "SFML/Audio/Sound.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "VertexArrayNode.hpp"
////////////////////////////////////////////////


class BonusStrip : public VertexArrayNode
{
    public:
        BonusStrip(const VertexArrayNode& obstacles, sf::Vector2f windowSize, float noteWidth, int category = 0);

	    /**
	     * \brief Update this node.
	     */
		virtual void updateCurrent();

        float   getDistance(sf::Vector2f p) const;
        float   getWidth() const;

        float fetchPointsScore();
        void gatherPoint(SceneNode* point);

        const std::list<SceneNode*>& getPoints() const;
    private:
        void initializeStrip();

        void removeQuad();
        void insertQuad(float topLeft, float botLeft, float top, float bot, bool isLeft);

        float getBusiestPosition() const;

        void spawnPoint(float x);

    private:
        const VertexArrayNode&      M_OBSTACLES;
        const sf::Vector2f          M_SIZE;
        const float                 M_SCROLL_SPEED;
        const float                 M_NOTE_WIDTH;
        std::queue<unsigned int>    mQuadIndexQueue;
        float                       mTimer;
        float                       mPointTimer;
        const float                 M_UPDATE_INTERVAL = 0.5f;
        const float                 M_POINT_SPAWN_INTERVAL = 2.f;
        float                       mPointsScore;
        std::list<SceneNode*>       mPoints;
        sf::Sound                   mPointSound;;
};

/************************************************
 * \class BonusStrip
 *
 *
 *
************************************************/

#endif // HITIT_BONUSSTRIP_HPP
