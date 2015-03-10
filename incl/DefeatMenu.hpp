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

#ifndef HITIT_DEFEATMENU_HPP
#define HITIT_DEFEATMENU_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "MenuState.hpp"
#include "SoundPlayer.hpp"
////////////////////////////////////////////////

class DefeatMenu : public MenuState
{
	public:
        /**
         * \brief Constructor
         *
         * \param stack to insert state into at construction.
         * \param target SFML RenderTarget object to draw to.
         */
        DefeatMenu(StateStack& stack, sf::RenderTarget& target);


        /**
         * \brief Handle input events.
         *
         * \return indicate whether the state stack
         * should allow further states to handle events
         * (true) or not (false).
         */
		virtual bool handleEvent(const sf::Event& event);


    private:
        std::list<GUIElement*> getButtons();

    private:
        SoundPlayer mTaunt; ///< Taunt the player for losing with this annoying sound.
};

/************************************************
 * \class DefeatMenu
 *
 * Displayed on player defeat.
 *
************************************************/

#endif // HITIT_DEFEATMENU_HPP
