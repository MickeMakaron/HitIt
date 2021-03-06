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
// HitIt internal headers
#include "SceneGraph.hpp"
#include "Spawner.hpp"
#include "AudioSampler.hpp"
class Player;
class BonusStrip;
class ScoreDisplay;
class Collission;
////////////////////////////////////////////////

class World
{
    public:
        /**
         * \enum State
         *
         * Current world state
         */
        enum State
        {
            Starting,
            Running,
            Paused,
            Victory,
            Defeat,
            StateCount,
        };

        /**
         * \brief Constructor
         *
         * \param target SFML RenderTarget object to draw to
         * \param midiFile File path to MIDI track
         */
        World(sf::RenderTarget& target, std::string midiFile);

        /**
         * \brief Destructor
         */
        ~World();

        /**
         * \brief Draw world
         */
        void draw();

        /**
         * \brief Update world
         */
        void update();

        /**
         * \brief Handle input event
         *
         * \param event event ot handle
         */
        void handleEvent(const sf::Event& event);

        /**
         * \brief Check world state
         *
         * \return current world state
         */
         State getState() const;

        /**
         * \brief Pause world
         *
         * Must be used when putting a state above this one
         */
        void pause();

        /**
         * \brief Resume world
         */
        void resume();

        /**
         * \brief Get current score
         *
         * \return Current score
         */
        unsigned int getScore() const;

        /**
         * \brief Perform initialization of world
         */
        void buildWorld();

    private:
        /**
         * \brief Start state update function
         */
        void updateStart();

        /**
         * \brief Run state update function
         */
        void updateRun();

        /**
         * \brief Victory state update function
         */
        void updateVictory();

        /**
         * \brief Enclose the player character in the view
         */
         void keepPlayerInBounds();

    private:
        sf::RenderTarget&   mTarget;            ///< SFML RenderTarget to draw to
        SceneGraph          mScene;             ///< Scene graph of all game objects
        AudioSampler        mSampler;           ///< Sampler to generate note sounds from raw audio data
        sf::FloatRect       mBounds;            ///< Area where player is allowed to reside
        Spawner             mSpawner;           ///< Spawn new obstacles
        Player*             mPlayer;            ///< Player controlled node
        BonusStrip*         mBonusStrip;        ///< Pointer to BonusStrip node
        ScoreDisplay*       mScoreDisplay;      ///< Pointer to ScoreDisplay node
        Collission*         mCollission;        ///< Collission manager
        State               mState;             ///< Current world state
        float               mTimer;             ///< Time counter
        bool                mPlayerIsDamaged;   ///< Player state

        std::vector<std::function<void()>> mStateFuncs; ///< State update functions
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
