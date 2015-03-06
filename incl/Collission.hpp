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

#ifndef HITIT_COLLISSION_HPP
#define HITIT_COLLISSION_HPP

////////////////////////////////////////////////
// C++ Standard Library
#include <list>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Rect.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
class SceneNode;
class Player;
////////////////////////////////////////////////


class Collission
{
    public:
        /**
         * \brief Constructor
         *
         * \param player player node to track.
         */
        Collission(Player& player);

        /**
         * \brief Add node to collission checklist.
         *
         * \param node node to add.
         */
        void insert(SceneNode* node);

        /**
         * \brief Manage collissions.
         */
        void update();

        /**
         * \brief Remove nodes marked for removal.
         */
        void removeWrecks();

    private:
        /**
         * \struct CollissionData
         *
         * Simple wrapper for data relevant
         * to collissions.
         */
        struct CollissionData
        {
            /**
             * \brief Constructor
             *
             * \param hasCollission has a collission occured?
             * \param depth depth of collission.
             */
            CollissionData(bool hasCollission = false, sf::Vector2f depth = sf::Vector2f(0.f, 0.f));
            bool            hasCollission;  ///< Indicator of whether a collission has occured or not.
            sf::Vector2f    depth;          ///< Depth of collission.
        };

        /**
         * \brief Check if two non-rotated rectangles intersect.
         *
         * \param a first rectangle
         * \param b second rectangle
         *
         * \return collission data.
         */
        CollissionData checkCollission(sf::FloatRect a, sf::FloatRect b) const;

    private:
        Player&                 mPlayer;    ///< Player node
        std::list<SceneNode*>   mNodes;     ///< Nodes in scene graph.
};

/**
 * \class Collission
 * Collission manager for detecting and handling collissions
 * between player node and the rest of the scene graph.
 */

#endif // HITIT_COLLISSION_HPP
