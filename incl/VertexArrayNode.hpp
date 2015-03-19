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
// HitIt internal headers
#include "SceneNode.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <queue>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/VertexArray.hpp"
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

        /**
         * \brief Destructor
         */
        virtual ~VertexArrayNode();

        /**
         * \brief Get world position of node.
         *
         * \return absolute world position of node.
         */
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
         * \param target SFML RenderTarget object to draw vertex array to
         * \param states SFML RenderStates object to transform draw with
         */
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        /**
         * \brief Get vertex count
         *
         * \return Vertex count
         */
        unsigned int getCount() const;

        /**
         * \brief Get primitive count
         *
         * \return Primitive count
         */
        unsigned int getSize() const;

        /**
         * \brief Insert primitive into vertex array
         *
         * \param primitive Primitive to insert represented by a vector of vertices
         *
         * \return Index of inserted primitive
         */
        unsigned int insert(std::vector<sf::Vertex> primitive);

        /**
         * \brief Free primitive index in vertex array
         *
         * \param index Primitive index to free
         */
        void free(unsigned int index);

        /**
         * \brief Access operator
         *
         * \param index Index of vertex to access
         *
         * \return Reference to vertex at index
         */
        sf::Vertex& operator[](unsigned int index);

        /**
         * \brief Const access operator
         *
         * \param index Index of vertex to access
         *
         * \return Const reference to vertex at index
         */
        const sf::Vertex& operator[](unsigned int index) const;

    private:
        /**
         * \brief Update primitive size
         */
        void updatePrimitiveSize();

    private:
        sf::VertexArray             mArray;         ///< Vertex array to draw
        unsigned int                mPrimitiveSize; ///< Size of primitives
        std::queue<unsigned int>    mFreeIndices;   ///< Queue of currently free primitive indices
};

/************************************************
 * \class VertexArrayNode
 *
 * For batch drawing many nodes that share the same
 * drawing properties, i.e. texture, color, vertex count,
 * etc. . A prime example is particle systems.
 *
************************************************/

#endif // HITIT_VERTEXARRAYNODE_HPP
