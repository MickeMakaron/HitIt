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

#ifndef HITIT_GAMESTATE_HPP
#define HITIT_GAMESTATE_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "State.hpp"
#include "World.hpp"
#include "AssetList.hpp"
////////////////////////////////////////////////

class GameState : public State
{

	public:
        /**
         * \brief Constructor
         *
         * \param stack Stack to insert state into at construction
         */
        GameState(StateStack& stack, sf::RenderTarget& target, std::string midiFile);

        /**
         * \brief Draw state
         */
		virtual void draw();

        /**
         * \brief Update state
         *
         * \return Indicate whether the state stack
         * should continue updating further states
         * (true) or not (false)
         */
		virtual bool update();

        /**
         * \brief Handle input events
         *
         * \return Indicate whether the state stack
         * should allow further states to handle events
         * (true) or not (false)
         */
		virtual bool handleEvent(const sf::Event& event);

        /**
         * \brief Pause game
         */
		void pause();

		/**
		 * \brief Resume game
		 */
		void resume();

    private:
        /**
         * \brief Load resources into memory
         */
        void loadAssets();

    private:
        sf::RenderTarget&   mTarget;    ///< SFML RenderTarget object to draw to
        World               mWorld;     ///< The actual game world
        std::string         mMidiFile;  ///< Path to MIDI track being played
        TextureList         mTextures;  ///< Texture resources
        SoundList           mSounds;    ///< Sound resources
        FontList            mFonts;     ///< Font resources
};

/************************************************
 * \class GameState
 *
 * Program state for managing the "game state", i.e.
 * the gameworld, the game objects, input etc. .
 *
************************************************/

#endif // HITIT_GAMESTATE_HPP
