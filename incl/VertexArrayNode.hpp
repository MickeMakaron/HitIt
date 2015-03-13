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

#ifndef HITIT_VERTEXARRAYNODE_HPP
#define HITIT_VERTEXARRAYNODE_HPP



////////////////////////////////////////////////
// STD - C++ Standard Library
#include <queue>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/VertexArray.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SceneNode.hpp"
////////////////////////////////////////////////


class VertexArrayNode : public SceneNode
{
    public:
        /**
         * \brief Constructor
         *
         * \param array vertex array to use.
         * \param category category of node.
         */
        VertexArrayNode(sf::VertexArray array, int category = 0);

        /**
         * \brief Constructor
         *
         * \param type primitive type of vertex array.
         * \param category category of node.
         */
        VertexArrayNode(sf::PrimitiveType type, int category = 0);

        virtual ~VertexArrayNode();

        virtual sf::Vector2f getWorldPosition() const;

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


        unsigned int getSize() const;

        unsigned int insert(std::vector<sf::Vertex> primitive);
        void free(unsigned int index);

        sf::Vertex& operator[](unsigned int index);

    private:
        void updatePrimitiveSize();

    private:
        sf::VertexArray             mArray;
        unsigned int                mPrimitiveSize;

        std::queue<unsigned int>    mFreeIndices;
};

/************************************************
 * \class VertexArrayNode
 *
 * Rectangularly shaped scene node.
 *
************************************************/

#endif // HITIT_VERTEXARRAYNODE_HPP
