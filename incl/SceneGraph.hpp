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

#ifndef HITIT_SCENEGRAPH_HPP
#define HITIT_SCENEGRAPH_HPP

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <memory>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
namespace sf
{
    class RenderTarget;
}
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SceneNode.hpp"
////////////////////////////////////////////////

class SceneGraph
{
    public:
        /**
         * \enum Layer
         *
         * The scene graph is divided into different layers.
         * This is useful for layered rendering.
         */
        enum Layer
        {
            Background,
            Low,
            Middle,
            High,
            Foreground,
            LayerCount,
        };

    public:
        /**
         * \brief Constructor
         */
        SceneGraph();

        /**
         * \brief Update scene graph.
         */
        void update();

        /**
         * \brief Draw scene graph to target.
         *
         * \param target SFML RenderTarget object to draw to.
         */
        void draw(sf::RenderTarget& target) const;

        /**
         * \brief Remove nodes marked for removal.
         */
        void removeWrecks();

        /**
         * \brief Insert node into scene graph.
         *
         * \param node node to insert.
         * \param layer layer to insert to.
         */
        void insert(SceneNode* node, Layer layer);

        /**
         * \brief Clear entire graph
         */
        void clear();

    private:
        std::vector<SceneNode> mGraph; ///< Graph of SceneNode objects. Size of vector is based on LayerCount.
};

/************************************************
 * \class SceneGraph
 *
 * Manages the scene's nodes, i.e. their update,
 * draw, insertion and removal.
 *
************************************************/

#endif // HITIT_SCENEGRAPH_HPP
