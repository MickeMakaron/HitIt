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
        /**
         * \brief Constructor
         *
         * \param texture texture to apply to sprite.
         * \param buffer sound buffer that contains sound to be played.
         */
        Obstacle(const sf::SoundBuffer& buffer, float speed, float playDuration, float width, float lifeTime);

        ~Obstacle();

		/**
		 * \brief Indicate whether this node is marked for removal.
		 *
		 * \return true if marked for removal, else false.
		 */
		 virtual bool isMarkedForRemoval() const;

    private:
        /**
         * \brief Draw this node.
         *
         * \param target SFML RenderTarget object to draw this node to.
         * \param states SFML RenderStates object ot transform draw with.
         */
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	    /**
	     * \brief Update this node.
	     */
		virtual void updateCurrent();

    private:
        sf::RectangleShape  mShape;         ///< Rectangular drawing shape.
        SoundPlayer*        mSoundPlayer;   ///< Use this to play sounds.
        float               mSpeed;         ///< How fast the node moves.
        float               mPlayDuration;  ///< How long to play the sound.
        float               mLifeTime;      ///< How long until marked for removal.
        float               mTime;          ///< Elapsed time.
};


/************************************************
 * \class Obstacle
 *
 * Obstacle node that the player is supposed to
 * not collide with.
 *
************************************************/

#endif // HITIT_OBSTACLE_HPP
