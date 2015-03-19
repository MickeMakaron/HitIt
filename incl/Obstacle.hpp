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
// STD - C++ Standard Library

////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SceneNode.hpp"
class SoundPlayer;
class VertexArrayNode;
////////////////////////////////////////////////

class Obstacle : public SceneNode
{
    public:
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
         * \param texture texture to apply to sprite.
         * \param buffer sound buffer that contains sound to be played.
         */
        Obstacle(SoundPlayer& soundPlayer, VertexArrayNode& array, float playLine, float deathLine, int category = 0);


        /**
         * \brief Destructor
         */
        ~Obstacle();

		/**
		 * \brief Indicate whether this node is marked for removal.
		 *
		 * \return true if marked for removal, else false.
		 */
		 virtual bool isMarkedForRemoval() const;

        virtual void setPosition(float x, float y);
        virtual void setSize(float width, float height);

        virtual sf::Vector2f getWorldPosition() const;

        /**
		 * \brief Get bounding rectangle of node.
		 *
		 * \return bounding rectangle of node.
		 */
		virtual sf::FloatRect	getBoundingRect() const;

    private:
	    /**
	     * \brief Update this node.
	     */
		virtual void updateCurrent();

        void updateVertices();


    private:
        SoundPlayer&        mSoundPlayer;   ///< Use this to play sounds.
        VertexArrayNode&    mArray;
        sf::FloatRect       mRect;
        unsigned int        M_VERTEX_ARRAY_INDEX;
        const float         M_PLAYLINE;
        const float         M_DEATHLINE;
        State               mState;
        std::vector<std::function<void()>> mStateFuncs;


};


/************************************************
 * \class Obstacle
 *
 * Obstacle node that the player is supposed to
 * not collide with.
 *
************************************************/

#endif // HITIT_OBSTACLE_HPP
