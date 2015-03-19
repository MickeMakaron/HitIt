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

#ifndef HITIT_OBSTACLE_HPP
#define HITIT_OBSTACLE_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "SceneNode.hpp"
class SoundPlayer;
class VertexArrayNode;
////////////////////////////////////////////////

class Obstacle : public SceneNode
{
    public:
        /**
         * \enum State
         *
         * Current state of obstacle.
         */
        enum State
        {
            Waiting,
            Playing,
            Silent,
            Dead,
            StateCount,
        };

        /**
         * \brief Constructor
         *
         * \param soundPlayer SoundPlayer to play when crossing playline
         * \param array Reference to parent VertexArrayNode
         * \param playLine Y-coordinate that, when crossed, sets Obstacle to Playing state
         * \param deathLine Y-coordinate that, when crossed, sets Obstacle to Dead state
         */
        Obstacle(SoundPlayer& soundPlayer, VertexArrayNode& array, float playLine, float deathLine, int category = 0);

        /**
         * \brief Destructor
         */
        ~Obstacle();

		/**
		 * \brief Indicate whether this node is marked for removal
		 *
		 * \return true if marked for removal, else false
		 */
		 virtual bool isMarkedForRemoval() const;

        /**
         * \brief Set position of obstacle
         *
         * \param x X-coordinate
         * \param y Y-coordinate
         */
        virtual void setPosition(float x, float y);

        /**
         * \brief Set size of obstacle
         *
         * \param width Width of obstacle
         * \param height Height of obstacle
         */
        virtual void setSize(float width, float height);

        /**
         * \brief Get world position of node
         *
         * \return absolute world position of node
         */
        virtual sf::Vector2f getWorldPosition() const;

        /**
		 * \brief Get bounding rectangle of node
		 *
		 * \return bounding rectangle of node
		 */
		virtual sf::FloatRect getBoundingRect() const;

    private:
	    /**
	     * \brief Update this node.
	     */
		virtual void updateCurrent();

        /**
         * \brief Update vertices' positions
         */
        void updateVertices();

    private:
        SoundPlayer&        mSoundPlayer;               ///< Used to play note
        VertexArrayNode&    mArray;                     ///< Parent vertex array
        sf::FloatRect       mRect;                      ///< Bounding rectangle
        unsigned int        M_VERTEX_ARRAY_INDEX;       ///< Index in parent vertex array
        const float         M_PLAYLINE;                 ///< Y-coordinate of play line
        const float         M_DEATHLINE;                ///< Y-coordinate of death line
        State               mState;                     ///< Current state
        std::vector<std::function<void()>> mStateFuncs; ///< State update functions
};

/************************************************
 * \class Obstacle
 *
 * Obstacle node that the player is supposed to
 * NOT collide with.
 *
************************************************/

#endif // HITIT_OBSTACLE_HPP
