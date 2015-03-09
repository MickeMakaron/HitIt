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
#include "Collission.hpp"
#include "Spawner.hpp"
class Player;
////////////////////////////////////////////////

class World
{
    public:
        enum State
        {
            Running,
            Paused,
            Victory,
            Defeat,
            StateCount,
        };

        /**
         * \brief Constructor
         *
         * \param window SFML RenderWindow object to draw to.
         */
        World(sf::RenderWindow& window);

        ~World();

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

        /**
         * \brief Check world state.
         *
         * \return current world state
         */
         State getState() const;

        /**
         * \brief Pause world.
         *
         * Must be used when putting a state above this one.
         */
        void pause();

        /**
         * \brief Resume world.
         */
        void resume();

    private:
        /**
         * \brief Perform initialization of world.
         */
        void buildWorld();

        /**
         * \brief Enclose the player character in the view.
         */
         void keepPlayerInBounds();

        /**
         * \brief Get required texture list.
         */
        std::list<TextureList::Asset> getTextures() const;



    private:
        sf::RenderWindow&   mWindow;        ///< SFML RenderWindow to draw to.
        sf::View            mView;          ///< View (what is actually shown to the player).
        SceneGraph          mScene;         ///< Scene graph of all game objects.
        TextureList         mTextures;      ///< Asset list for textures.
        Player*             mPlayer;        ///< Player controlled node.
        Collission          mCollission;    ///< Collission manager.
        Spawner             mSpawner;       ///< Spawn new obstacles.
        State               mState;         ///< Current world state.
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
