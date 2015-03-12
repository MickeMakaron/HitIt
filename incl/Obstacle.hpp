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
// SFML - Simple and Fast Media Library
namespace sf
{
    class SoundBuffer;
    class VertexArray;
}
#include "SFML/Graphics/RectangleShape.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SpriteNode.hpp"
#include "SoundPlayer.hpp"
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
        };
        /**
         * \brief Constructor
         *
         * \param texture texture to apply to sprite.
         * \param buffer sound buffer that contains sound to be played.
         */
        Obstacle(SoundPlayer& buffer, float speed, float playLine, sf::Vector2f size, float deathLine, unsigned int iVertexArray, sf::VertexArray& array, int category = 0);


		/**
		 * \brief Indicate whether this node is marked for removal.
		 *
		 * \return true if marked for removal, else false.
		 */
		 virtual bool isMarkedForRemoval() const;


        /**
		 * \brief Get bounding rectangle of node.
		 *
		 * \return bounding rectangle of node.
		 */
		virtual sf::FloatRect	getBoundingRect() const;

		/**
		 * \brief Get index in vertex array.
		 *
		 * \return index in vertex array.
		 */
		unsigned int getVertexArrayIndex() const;

    private:
	    /**
	     * \brief Update this node.
	     */
		virtual void updateCurrent();

    private:
        sf::RectangleShape  mShape;         ///< Rectangular drawing shape.
        SoundPlayer&        mSoundPlayer;   ///< Use this to play sounds.
        float               mSpeed;         ///< How fast the node moves.
        float               mPlayLine;
        float               mDeathLine;
        State               mState;
        unsigned int        mIVertexArray;
        sf::VertexArray&    mArray;
};


/************************************************
 * \class Obstacle
 *
 * Obstacle node that the player is supposed to
 * not collide with.
 *
************************************************/

#endif // HITIT_OBSTACLE_HPP
