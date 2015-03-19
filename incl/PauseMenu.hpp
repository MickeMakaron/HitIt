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

#ifndef HITIT_PAUSEMENU_HPP
#define HITIT_PAUSEMENU_HPP

////////////////////////////////////////////////
// HitIt internal headers
#include "MenuState.hpp"
class GameState;
////////////////////////////////////////////////

class PauseMenu : public MenuState
{
	public:
        /**
         * \brief Constructor
         *
         * \param stack Stack to insert state into at construction
         * \param target SFML RenderTarget object to draw to
         * \param game Reference to game state operating being paused behind this state
         */
        PauseMenu(StateStack& stack, sf::RenderTarget& target, GameState& game);

        /**
         * \brief Handle input events
         *
         * \return Indicate whether the state stack
         * should allow further states to handle events
         * (true) or not (false)
         */
		virtual bool handleEvent(const sf::Event& event);

    private:
        /**
         * \brief Load buttons into GUIContainer
         */
        void loadButtons();

    private:
        GameState& mGame; ///< Reference to paused game state
};

/************************************************
 * \class PauseMenu
 *
 * Pause screen. Displayed during paused game.
 *
************************************************/

#endif // HITIT_PAUSEMENU_HPP
