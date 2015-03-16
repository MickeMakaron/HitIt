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
// SFML - Simple and Fast Media Library
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
////////////////////////////////////////////////


////////////////////////////////////////////////
// HitIt internal headers
#include "MenuState.hpp"
////////////////////////////////////////////////

class AboutMenu : public MenuState
{
	public:
        /**
         * \brief Constructor
         *
         * \param stack to insert state into at construction.
         * \param target SFML RenderTarget object to draw to.
         */
        AboutMenu(StateStack& stack, sf::RenderTarget& target);


		virtual void draw();
        virtual bool update();
    private:
        std::list<TextureList::Asset> getTextures() const;
        std::list<GUIElement*> getButtons();

    private:
        sf::Sprite              mAbout;
        sf::RectangleShape      mGUIBackground;
};

/************************************************
 * \class AboutMenu
 *
 * Main menu. Is displayed after title screen.
 *
************************************************/

#endif // HITIT_ABOUTMENU_HPP
