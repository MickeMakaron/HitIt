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

#ifndef HITIT_SPRITENODE_HPP
#define HITIT_SPRITENODE_HPP


////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Sprite.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SceneNode.hpp"
////////////////////////////////////////////////


class SpriteNode : public SceneNode
{
    public:
        /**
         * \brief Constructor
         *
         * \param texture texture to apply to sprite.
         */
        SpriteNode(const sf::Texture& texture, int category = 0);

        /**
         * \brief Get bounding rectangle of sprite.
         *
         * \return bounding rectangle of sprite.
         */
        virtual sf::FloatRect   getBoundingRect() const;

        /**
         * \brief Draw sprite.
         *
         * \param target SFML RenderTarget object to draw sprite to.
         * \param states SFML RenderStates object to transform draw with.
         */
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Sprite      mSprite; ///< SFML sprite object.
};

/************************************************
 * \class SpriteNode
 *
 * Scene node that makes use of SFML sprite object.
 *
************************************************/

#endif // HITIT_SPRITENODE_HPP
