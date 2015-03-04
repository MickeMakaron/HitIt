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

#ifndef HITIT_WORLD_HPP
#define HITIT_WORLD_HPP

////////////////////////////////////////////////
// STD - C++ Standard Library
#include <memory>
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
namespace sf
{
    class RenderWindow;
}
////////////////////////////////////////////////

////////////////////////////////////////////////
// HitIt internal headers
#include "SceneGraph.hpp"
#include "AssetList.hpp"
////////////////////////////////////////////////

class World
{
    public:
        /**
         * \brief Constructor
         *
         * \param window SFML RenderWindow object to draw to.
         */
        World(sf::RenderWindow& window);

        /**
         * \brief Draw world.
         */
        void draw();

        /**
         * \brief Update world.
         */
        void update();

        /**
         * \brief Handle input event.
         *
         * \param event event ot handle.
         */
        void handleEvent(const sf::Event& event);

    private:
        /**
         * \brief Perform initialization of world.
         */
        void buildWorld();

    private:
        sf::RenderWindow& mWindow;  ///< SFML RenderWindow to draw to.
        SceneGraph mScene;          ///< Scene graph of all game objects.
        TextureList mTextures;      ///< Asset list for textures.
};


/************************************************
 * \class World
 *
 * Manager for the game world. Holds things like
 * the scene graph and connects user input to the
 * game world.
 *
************************************************/

#endif // HITIT_WORLD_HPP