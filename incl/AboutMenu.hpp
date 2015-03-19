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

#ifndef HITIT_ABOUTMENU_HPP
#define HITIT_ABOUTMENU_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "MenuState.hpp"
////////////////////////////////////////////////

////////////////////////////////////////////////
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
////////////////////////////////////////////////

class AboutMenu : public MenuState
{
	public:
        /**
         * \brief Constructor
         *
         * \param stack Stack to insert state into at construction
         * \param target SFML RenderTarget object to draw to
         */
        AboutMenu(StateStack& stack, sf::RenderTarget& target);

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

    private:
        /**
         * \brief Load buttons into GUIContainer
         */
        void loadButtons();

    private:
        sf::Sprite          mAbout;         ///< Player instructions
        sf::RectangleShape  mGUIBackground; ///< GUI background combined with mAbout sprite
};

/************************************************
 * \class AboutMenu
 *
 * About menu. Shows the player how to play the
 * game.
 *
************************************************/

#endif // HITIT_ABOUTMENU_HPP
