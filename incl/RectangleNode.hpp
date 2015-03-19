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

#ifndef HITIT_RECTANGLENODE_HPP
#define HITIT_RECTANGLENODE_HPP


////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Texture.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SceneNode.hpp"
////////////////////////////////////////////////


class RectangleNode : public SceneNode
{
    public:
        /**
         * \brief Constructor
         *
         * \param size size of rectangle.
         * \param category category of node.
         */
        RectangleNode(const sf::Vector2f& size = sf::Vector2f(0.f, 0.f), int category = 0);

        /**
         * \brief Constructor
         *
         * \param texture texture of rectangle.
         * \param category category of node.
         */
         RectangleNode(const sf::Texture& texture, int category = 0);


        /**
         * \brief Get bounding rectangle of shape.
         *
         * \return bounding rectangle of shape.
         */
        virtual sf::FloatRect getBoundingRect() const;

        /**
         * \brief Draw shape.
         *
         * \param target SFML RenderTarget object to draw shape to.
         * \param states SFML RenderStates object to transform draw with.
         */
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        void setFillColor(sf::Color color);


        void setOutlineColor(sf::Color color);

        void setOutlineThickness(float thickness);

        /**
         * \brief Set size of shape
         *
         * \param x width
         * \param y height
         */
        void setSize(float x, float y);

    protected:
        sf::RectangleShape mShape;
};

/************************************************
 * \class RectangleNode
 *
 * Rectangularly shaped scene node.
 *
************************************************/

#endif // HITIT_RECTANGLENODE_HPP
