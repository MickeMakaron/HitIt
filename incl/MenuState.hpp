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

#ifndef HITIT_MENUSTATE_HPP
#define HITIT_MENUSTATE_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "State.hpp"
#include "AssetList.hpp"
#include "GUIContainer.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"
////////////////////////////////////////////////

class MenuState : public State
{
	public:
        /**
         * \brief Constructor
         *
         * \param stack Stack to insert state into at construction
         * \param target SFML RenderTarget object to draw to
         */
        MenuState(StateStack& stack, sf::RenderTarget& target);

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
         * \brief Set background texture
         *
         * \param texture background texture
         */
        void setBackground(const sf::Texture& texture);

        /**
         * \brief Set background color
         *
         * \param color background color
         */
        void setBackground(sf::Color color);

    private:
        /**
         * \brief Load resources into memory
         */
        void loadAssets();

    protected:
        sf::RenderTarget&   mTarget;        ///< SFML RenderTarget to draw to
        TextureList         mTextures;      ///< Texture resources
        SoundList           mSounds;        ///< Sound resources
        FontList            mFonts;         ///< Font resources
        GUIContainer        mMenu;          ///< GUI container for GUI elements
        sf::RectangleShape  mBackground;    ///< State background
        sf::Text            mWaterMark;     ///< Copyright watermark at the lower right corner
};

/************************************************
 * \class MenuState
 *
 * Program state menus.
 *
************************************************/

#endif // HITIT_MENUSTATE_HPP
