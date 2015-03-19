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
// HitIt internal headers
#include "VertexArrayNode.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Audio/Sound.hpp"
////////////////////////////////////////////////

class BonusStrip : public VertexArrayNode
{
    public:
        /**
         * \brief Constructor
         *
         * \param obstacles Array of all obstacle primitives in the scene
         * \param worldSize Size of world to adjust the strip's width to
         * \param noteWidth For spawning correctly sized points
         * \param category Category of this node
         */
        BonusStrip(const VertexArrayNode& obstacles, sf::Vector2f worldSize, float noteWidth, int category = 0);

	    /**
	     * \brief Update this node
	     */
		virtual void updateCurrent();

        /**
         * \brief Get shortest distance from point to strip center
         *
         * \param p Point to check
         *
          \return Shortest distance to bonus strip's center
         */
        float   getDistance(sf::Vector2f p) const;

        /**
         * \brief Get width of strip
         *
         * \return Width of bonus strip
         */
        float   getWidth() const;

        /**
         * \brief Get number of gathered points
         *
         * Returns accumulated points and then
         * resets the counter to 0.
         *
         * \return Points gathered since last time this function was called
         */
        float fetchPointsScore();

        /**
         * \brief Gather point
         *
         * Increments mPointsScore and removes the
         * point, if it exists.
         *
         * \param point SceneNode pointer to point to be gathered
         */
        void gatherPoint(SceneNode* point);

        /**
         * \brief Get list of all points in the scene
         *
         * \return List of all points currently in the scene
         */
        const std::list<SceneNode*>& getPoints() const;

    private:
        /**
         * \brief Initialize strip's vertex array
         */
        void initializeStrip();

        /**
         * \brief Remove the quad inserted the longest time ago
         */
        void removeQuad();

        /**
         * \brief Insert quad into vertex array
         *
         * \param topLeft X-coordinate of top part
         * \param botLeft X-coordinate of bottom part
         * \param top Y-coordinate of top
         * \param bot Y-coordinate of bottom
         * \param isLeft Is this quad to the left or to the right of the strip's center?
         */
        void insertQuad(float topLeft, float botLeft, float top, float bot, bool isLeft);

        /**
         * \brief Get average position of obstacle nodes
         *
         * \return Average position of all obstacle nodes currently in the scene
         */
        float getBusiestPosition() const;

        /**
         * \brief Spawn a point
         *
         * Points always spawn in the front of the strip.
         *
         * \param x X-coordinate to spawn point at
         */
        void spawnPoint(float x);

        /**
         * \brief Loop all vertices back to avoid large numbers
         *
         * All vertices constantly move downwards. This results
         * in very large numbers if the track is long.
         */
        void loopBack();

    private:
        const VertexArrayNode&      M_OBSTACLES;                    ///< All obstacle primitives in the scene
        const sf::Vector2f          M_SIZE;                         ///< Size of world
        const float                 M_SCROLL_SPEED;                 ///< Game scrolling speed
        const float                 M_NOTE_WIDTH;                   ///< Width of obstacles
        std::queue<unsigned int>    mQuadIndexQueue;                ///< Queue of inserted quads. Those in front were inserted the longest time ago
        float                       mTimer;                         ///< Time counter for updates
        const float                 M_UPDATE_INTERVAL = 0.5f;       ///< Time interval to update bonus strip
        const float                 M_POINT_SPAWN_INTERVAL = 2.f;   ///< Time interval to spawn points
        float                       mPointsScore;                   ///< Points gathered since last time fetchPointsScore was called
        std::list<SceneNode*>       mPoints;                        ///< List of all points currently in the scene
        sf::Sound                   mPointSound;                    ///< Sound played when points are gathered
        float                       mPointTimer;                    ///< Time counter for point spawning
};

/************************************************
 * \class BonusStrip
 *
 * The strip in which the player gets bonus points
 * for being close to.
 *
************************************************/

#endif // HITIT_BONUSSTRIP_HPP
