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

#ifndef HITIT_MENUTHEMESTATE_HPP
#define HITIT_MENUTHEMESTATE_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "State.hpp"
#include "AudioSampler.hpp"
#include "SceneNode.hpp"
#include "AssetList.hpp"
class Spawner;
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RectangleShape.hpp"
////////////////////////////////////////////////

class MenuThemeState : public State
{
	public:
        /**
         * \brief Constructor
         *
         * \param stack Stack to insert state into at construction
         * \param target SFML RenderTarget object to draw to
         */
        MenuThemeState(StateStack& stack, sf::RenderTarget& target);

        /**
         * \brief Destructor
         */
        ~MenuThemeState();

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
         * \param event event to handle
         *
         * \return Indicate whether the state stack
         * should allow further states to handle events
         * (true) or not (false)
         */
        virtual bool handleEvent(const sf::Event& event);

    private:
        /**
         * \brief Load resources into memory
         */
        void loadAssets();

    protected:
        const std::string       M_THEME_FILE_PATH = "assets/midi/Mikael Hernvall - HitIt OST.mid"; ///< File path to HitIt soundtrack

        TextureList             mTextures;      ///< Texture resources
        sf::RenderTarget&       mTarget;        ///< SFML RenderTarget object to draw to
        AudioSampler            mSampler;       ///< Sampler for playing the Spawner notes
        SceneNode               mNotes;         ///< Current notes in the scene
        Spawner*                mSpawner1;      ///< First spawner object before looping
        Spawner*                mSpawner2;      ///< Intermediate spawner object used when transgressing from track end to track begin
        sf::RectangleShape      mBackground;    ///< State background
};

/************************************************
 * \class MenuThemeState
 *
 * Program state for playing and displaying the theme
 * behind the menus.
 *
************************************************/

#endif // HITIT_MENUTHEMESTATE_HPP
